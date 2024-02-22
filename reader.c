//
// Created by tergel93 on 22/2/24.
//

#include "reader.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define ZSH_FILE_NAME ".zsh_history"

static void reverse(char *chs, unsigned int len);

static bool ignore(Str **lines, unsigned int length, Str *str);

int read(Str *lines[], int max_count) {
    const char *homeDir = getenv("HOME");

    if (homeDir == NULL) {
        fprintf(stderr, "Error: Home env not set.\n");
        exit(1);
    }

    unsigned long path_len = strlen(homeDir) + 1 + strlen(ZSH_FILE_NAME) + 1;
    char file_path[path_len];
    snprintf(file_path, path_len, "%s/.zsh_history", homeDir);
    printf("reading from file: %s\n", file_path);
    FILE *file = fopen(file_path, "r");

    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    if (file_size == -1) {
        perror("Error getting file size");
        fclose(file);
        exit(1);
    }
    int line_count = 0;

    char line[512]; // TODO dynamic array?
    memset(line, '\0', sizeof(line));
    unsigned int length = 0;

    long file_pos_counter = file_size - 1;
    fseek(file, file_pos_counter--, SEEK_SET);
    char ch;
    while (line_count <= max_count && fread(&ch, 1, 1, file) > 0) {
        if (ch == '\n') {
            if (length == 0) {
                fseek(file, file_pos_counter--, SEEK_SET);
                continue;
            }
            reverse((char *) &line, length);
            line[length] = '\0';
            for (int i = 0; i < length; i++) {
                if (line[i] == ';') {
                    char *src = line + i + 1;
                    int count = length - 1;
                    memmove(line, src, count);

                    char *line_ptr = line;
                    Str *str = new_str(&line_ptr, count);
                    if (str == NULL) {
                        length = 0;
                        continue;
                    }
                    str->index = file_pos_counter;

                    if (ignore(lines, line_count, str)) {
                        free(str);
                    } else {
                        lines[line_count++] = str;
                        memset(line, '\0', count);
                    }
                }
            }
            length = 0;
        } else {
            line[length++] = ch;
        }
        fseek(file, file_pos_counter--, SEEK_SET);
    }
    return line_count;
}

static bool ignore(Str **lines, unsigned int length, Str *str) {
    if (length == 0) {
        return false;
    }
    if (strcmp(str->contents, "hisi") == 0) {
        return true;
    }
    for (int i = length - 1; i >= 0; i--) {
        Str *prev_str = lines[i];
        if (equals(str, prev_str)) {
            return true;
        }
    }
    return false;
}

static void reverse(char *chs, unsigned int len) {
    int l = 0, r = len - 1;
    while (l < r) {
        char val = chs[l];
        chs[l] = chs[r];
        chs[r] = val;
        r--;
        l++;
    }
}


