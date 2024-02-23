//
// Created by tergel93 on 22/2/24.
//

#include "interface.h"

#include <ncurses.h>
#include <stdbool.h>
#include "str.h"
#include "reader.h"
#include "writer.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define DISTANCE(a, b) ((a) > (b) ? (a)-(b) : (b) -(a))

static void print_lines(Str **lines, unsigned int height);

static void pre_render(void);

static void render(void);

static void handle_input(Str **lines);

void init(void) {
    initscr();
    cbreak(); // disable line buffering
    noecho(); // don't echo when we do getch()
    pre_render();
    render();
    endwin();
}

static struct window {
    unsigned int cursor_y;
    unsigned int height;
    int maxY, maxX;
    bool keep_rendering;
} window;

static struct input {
    unsigned int step_counter;
    char last_input;
} input;

static void pre_render(void) {
    window.keep_rendering = true;
    input.step_counter = 0;
    input.last_input = '0';
    curs_set(1); // display cursor
    getmaxyx(stdscr, window.maxY, window.maxX); // get window size
}

static void print_lines(Str **lines, unsigned int height) {
    for (int i = 0; i < height; i++) {
        mvprintw(i, 0, "%2u", DISTANCE(window.cursor_y, i));
        mvprintw(i, 5, "%s", lines[height - 1 - i]->contents);
    }
}

static void render(void) {
    Str *lines[window.maxY];
    int count = read(lines, window.maxY);

    window.height = MIN(count, window.maxY);
    window.cursor_y = window.height - 1;

    while (window.keep_rendering) {
        getmaxyx(stdscr, window.maxY, window.maxX);
        window.height = MIN(count, window.maxY);

        print_lines(lines, window.height);

        move(window.cursor_y, 0);
        refresh();

        handle_input(lines);
    }
}

static unsigned int calculate_steps(void) {
    unsigned int step = MAX(input.step_counter, 1);
    input.step_counter = 0;
    return MIN(window.height - 1, step);
}

static void handle_input(Str **lines) {
    char in = getch();
    if (in <= '9' && in >= '0') {
        input.step_counter = input.step_counter * 10 + (in - '0');
    } else {
        switch (in) {
            case 'j': {
                unsigned int steps = calculate_steps();
                if (window.cursor_y < window.height - 1) {
                    window.cursor_y = MIN(window.cursor_y + steps, window.height - 1);
                }
                break;
            }
            case 'k': {
                unsigned int steps = calculate_steps();
                if (window.cursor_y > 0) {
                    window.cursor_y = MAX(window.cursor_y - steps, 0);
                }
                break;
            }
            case 'G':
                window.cursor_y = window.height - 1;
                break;
            case 'g':
                if (input.last_input == 'g') {
                    window.cursor_y = 0;
                }
                break;
            case 'q':
                window.keep_rendering = false;
                break;
            case 'y': {
                Str *line = lines[window.height - 1 - window.cursor_y];
                copy_to_clipboard(line->contents);
                window.keep_rendering = false;
            }
            default:
                break;
        }
    }
    input.last_input = in;
}

