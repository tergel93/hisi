//
// Created by tergel93 on 22/2/24.
//

#ifndef HISI_STR_H
#define HISI_STR_H

#include <stdbool.h>

typedef struct Str {
    int length;
    long index;
    unsigned long hash;
    char contents[];
} Str;

Str *new_str(char **line_ptr, unsigned int length);

bool equals(Str *s1, Str *s2);

#endif //HISI_STR_H
