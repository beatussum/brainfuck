/*
 * Copyright (C) 2024 Mattéo Rossillol‑‑Laruelle <beatussum@protonmail.com>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <https://www.gnu.org/licenses/>.
 */


#include "brainfuck.h"

#include <stdio.h>
#include <stdlib.h>

static long get_size_of_file(FILE* __file)
{
    fseek(__file, 0, SEEK_END);
    long ret = ftell(__file);
    rewind(__file);

    return (ret + 1);
}

const char* get_input(const char* __filename)
{
    FILE* file = fopen(__filename, "r");

    if (file == NULL) {
        return NULL;
    } else {
        long size = get_size_of_file(file);
        char* ret = malloc(sizeof(char) * size);

        fread(ret, sizeof(char), size, file);
        fclose(file);

        return ret;
    }
}

void free_input(char* __input)
{
    free(__input);
}

loops build_loops(const char* __input)
{
    size_t n = 0;

    for (const char* i = __input; *i != '\0'; ++i) {
        if (*i == '[') {
            ++n;
        }
    }

    loops ret = { .begin = malloc(sizeof(loop) * n) };

    loop* i = ret.begin;

    for (; *__input != '\0'; ++__input) {
        switch (*__input) {
            case '[':
                i->begin = __input;

                break;
            case ']':
                i->end = __input;
                ++i;

                break;
            default:
                break;
        }
    }

    ret.end = (i + 1);

    return ret;
}

void free_loops(loops* __loops)
{
    for (loop* i = __loops->begin; i != __loops->end; ++i) {
        free(i);
    }

    *__loops = (loops) { .begin = NULL, .end = NULL };
}

void execute_instruction(
    const char** __current_instruction,
    uint8_t** __current_cell,
    loop** __current_loop
)
{
    switch (**__current_instruction) {
        case '>':
            ++(*__current_cell);

            break;
        case '<':
            --(*__current_cell);

            break;
        case '+':
            ++(*(*__current_cell));

            break;
        case '-':
            --(*(*__current_cell));

            break;
        case '.':
            putchar(**__current_cell);

            break;
        case ',':
            **__current_cell = getchar();

            break;
        case '[':
            break;
        case ']':
            if (**__current_cell == 0) {
                ++(*__current_loop);
            } else {
                *__current_instruction = (*__current_loop)->begin;
            }

            break;
        default:
            break;
    }

    ++(*__current_instruction);
}
