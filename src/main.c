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

static void free_resources(
    uint8_t* __cells,
    const char* __input,
    const loop* __loops
)
{
    free_cells(__cells);
    free_input((char*) __input);
    free_loops((loop*) __loops);
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        fprintf(stderr, "USAGE: %s <input file>\n", argv[0]);

        return EXIT_FAILURE;
    }

    const char* filename = argv[1];
    const char* input    = get_input(filename);

    if (input == NULL) {
        fprintf(stderr, "Unable to load input file `%s`!\n", filename);

        return EXIT_FAILURE;
    }

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
}
