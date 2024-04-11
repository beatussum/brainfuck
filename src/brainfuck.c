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

#include <stdbool.h>
#include <string.h>

static long get_size_of_file(FILE* __file)
{
    fseek(__file, 0, SEEK_END);
    long ret = ftell(__file);
    rewind(__file);

    return ret;
}

static void print_tabs(size_t __tab_level, FILE* __output)
{
    for (; __tab_level != 0; --__tab_level) {
        fputc('\t', __output);
    }
}

void compile(FILE* __input, FILE* __output)
{
    bool first            = true;
    bool last_is_new_line = false;

    size_t tab_level = 1;

    fputs(
        "/* THIS FILE WAS AUTOMATICALLY GENERATED */\n"
        "\n"
        "\n"
        "#include <stdint.h>\n"
        "#include <stdio.h>\n"
        "#include <stdlib.h>\n"
        "\n"
        "int main() {\n"
        "\tuint8_t* array = malloc(30000 * sizeof(uint8_t));\n"
        "\n"
        "\tif (array == NULL) {\n"
        "\t\tfprintf(stderr, \"Unable to allocate the initial array!\");\n"
        "\t\treturn EXIT_FAILURE;\n"
        "\t}\n"
        "\n"
        "\tuint8_t* ptr = array;\n"
        "\n",

        __output
    );

    for (char input; (input = fgetc(__input)) != EOF; ) {
        switch (input) {
            case '[':
                if (!first) {
                    fputc('\n', __output);
                }

                print_tabs(tab_level++, __output);

                break;

            case ']':
                last_is_new_line = true;
                print_tabs(--tab_level, __output);

                break;

            case '>':
            case '<':
            case '+':
            case '-':
            case '.':
            case ',':
                last_is_new_line = false;
                print_tabs(tab_level, __output);

                break;

            default:
                break;
        }

        switch (input) {
            case '>':
                fprintf(__output, "++ptr;\n");

                break;
            case '<':
                fprintf(__output, "--ptr;\n");

                break;
            case '+':
                fprintf(__output, "++(*ptr);\n");

                break;
            case '-':
                fprintf(__output, "--(*ptr);\n");

                break;
            case '.':
                fprintf(__output, "putchar(*ptr);\n");

                break;
            case ',':
                fprintf(__output, "(*ptr) = getchar();\n");

                break;
            case '[':
                fprintf(__output, "while (*ptr) {\n");

                break;
            case ']':
                fputs("}\n\n", __output);

                break;
            default:
                break;
        }

        first = false;
    }

    if (!last_is_new_line) {
        fputc('\n', __output);
    }

    fputs(
        "\tfree(array);\n"
        "\n"
        "\treturn EXIT_SUCCESS;\n"
        "}\n",

         __output
    );
}

const char* get_input(FILE* __file)
{
    long size = get_size_of_file(__file);
    char* ret = malloc(sizeof(char) * (size + 1));

    fread(ret, sizeof(char), size, __file);
    ret[size] = '\0';

    return ret;
}

const loop* build_loops(const char* __input)
{
    loop* root = malloc(sizeof(loop));

    *root = (loop) {
        .begin = NULL,
        .end   = NULL,
        .below = NULL,
        .next  = NULL
    };

    loop* ancestors[256];
    loop* current_previous  = root;
    loop** current_ancestor = (ancestors - 1);

    for (; *__input != '\0'; ++__input) {
        switch (*__input) {
            case '[':
                loop* new = malloc(sizeof(loop));

                *new = (loop) {
                    .begin = __input,
                    .end   = NULL,
                    .below = NULL,
                    .next  = NULL
                };

                if (current_previous->end == NULL) {
                    current_previous->below = new;
                    *(++current_ancestor)   = current_previous;

                } else {
                    current_previous->next = new;
                }

                current_previous = new;

                break;
            case ']':
                if (current_previous->end == NULL) {
                    current_previous->end = __input;
                } else {
                    (*current_ancestor)->end = __input;
                    current_previous->next   = *current_ancestor;
                    current_previous         = *current_ancestor;

                    --current_ancestor;
                }

                break;
            default:
                break;
        }
    }

    current_previous->next = root;

    return root;
}

void free_loops(loop* __loops)
{
    if (__loops->below != NULL) {
        loop* i = __loops;

        do {
            const loop* next;

            if (i->below == NULL) {
                next = i->next;
                free(i);
            } else {
                next     = i->below;
                i->below = NULL;
            }

            i = (loop*) next;
        } while (i != __loops);
    }

    free(__loops);
}

void execute_instruction(
    const char** __current_instruction,
    uint8_t**    __current_cell,
    const loop** __current_loop
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
            ++(**__current_cell);

            break;
        case '-':
            --(**__current_cell);

            break;
        case '.':
            putchar(**__current_cell);

            break;
        case ',':
            **__current_cell = getchar();

            break;
        case '[':
            if (**__current_cell == 0) {
                *__current_instruction = (*__current_loop)->end;
                *__current_loop        = (*__current_loop)->next;
            } else if ((*__current_loop)->below != NULL) {
                *__current_loop = (*__current_loop)->below;
            }

            break;
        case ']':
            *__current_instruction = ((*__current_loop)->begin - 1);

            break;
        default:
            break;
    }

    ++(*__current_instruction);
}
