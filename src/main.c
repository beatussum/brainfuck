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

static void free_resources(
    uint8_t*    __cells,
    const char* __input,
    const loop* __loops
)
{
    free_cells(__cells);
    free_input((char*) __input);
    free_loops((loop*) __loops);
}

static void print_on_failed_load(const char* __filename)
{
    fprintf(stderr, "Unable to load file `%s`!\n", __filename);
}

int main(int argc, char* argv[])
{
    if ((argc == 4) && (strcmp(argv[1], "compile") == 0)) {
        const char* input_filename  = argv[2];
        const char* output_filename = argv[3];

        FILE* input  = stdin;
        FILE* output = stdout;

        if (strcmp(input_filename, "-") != 0) {
            input = fopen(input_filename, "r");
        }

        if (strcmp(output_filename, "-") != 0) {
            output = fopen(output_filename, "r");
        }

        if (input == NULL) {
            print_on_failed_load(input_filename);

            return EXIT_FAILURE;
        }

        if (output == NULL) {
            print_on_failed_load(output_filename);

            return EXIT_FAILURE;
        }

        compile(input, output);

        fclose(input);
        fclose(output);

        return EXIT_SUCCESS;
    } else if ((argc == 3) && (strcmp(argv[1], "run") == 0)) {
        const char* filename = argv[2];
        FILE* file           = fopen(filename, "r");

        if (file == NULL) {
            print_on_failed_load(filename);

            return EXIT_FAILURE;
        }

        const char* input = get_input(file);

        fclose(file);

        size_t size        = 30000;
        uint8_t* cells     = build_cells(size);
        uint8_t* last_cell = cells + size - 1;

        const loop* loops = build_loops(input);

        uint8_t* current_cell     = cells;
        const char* current_input = input;
        const loop* current_loop  = loops->below;

        while (*current_input != '\0') {
            execute_instruction(&current_input, &current_cell, &current_loop);

            if ((current_cell < cells) || (current_cell > last_cell)) {
                fprintf(stderr, "The program leaves the allocated array!\n");
                free_resources(cells, input, loops);

                return EXIT_FAILURE;
            }
        }

        free_resources(cells, input, loops);

        return EXIT_SUCCESS;
    } else {
        char* program_name = argv[0];

        fprintf(
            stderr,

            "USAGE:\n"
            "\t%s compile <input> <output>\n"
            "\t%s run <input>\n"
            "\n"
            "For the `compile` command, you can replace:\n"
            "\t- `input` by `-` to set the standard input as input,\n"
            "\t- `output` by `-` to set the standard output as output.\n",

            program_name,
            program_name
        );

        return EXIT_FAILURE;
    }
}
