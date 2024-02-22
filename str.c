//
// Created by tergel93 on 22/2/24.
//

#include "str.h"

#include <string.h>
#include <stdlib.h>

static void hash(Str *);

Str *new_str(char **line_ptr, unsigned int length) {
    size_t size = sizeof(Str) + (length + 1) * sizeof(char);
    Str *s = (Str *) malloc(size);
    if (s != NULL) {
        s->length = length;
        strcpy(s->contents, *line_ptr);
        hash(s);
    }
    return s;
}

bool equals(Str *s1, Str *s2) {
    if (s1 == NULL || s2 == NULL) {
        return false;
    }
    if (s1->length != s2->length
        || s1->hash != s2->hash) {
        return false;
    }
    return strcmp(s1->contents, s2->contents) == 0 ? true : false;
}

static void hash(Str *s) {
    const char *chs = s->contents;

    unsigned long hash = 5381;
    int c;
    while ((c = (int) *chs++)) {
        hash = ((hash << 5) + hash) + c;
    }
    s->hash = hash;
}
