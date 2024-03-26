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


#ifndef BRAINFUCK_BRAINFUCK_H
#define BRAINFUCK_BRAINFUCK_H

#include <stddef.h>

typedef struct
{
    const char* begin;
    const char* end;
} loop;

typedef struct {
    loop* first;
    size_t size;
} loops;

/**
 * @brief Récupère le programme Brainfuck à interpréter depuis un fichier
 *
 * @param __filename le nom du fichier Brainfuck à récupérer
 * @return un tableau de caractère terminé par le caractère `'\0'` ou `NULL` si
 * `input_filename` n'existe pas dans le répertoire courant
 */
const char* get_input(const char* __filename);

/**
 * @brief Libère ce qui a été alloué par `get_input_prog()`
 *
 * @param __input l'entrée à libérer
 */
void free_input(char* __input);

/**
 * @brief Construit le tableau des boucles
 *
 * Analyse le programme Brainfuck passé en paramètre pour construire un `loops`
 * qui représente les boucles du programme. Celui-ci sera ensuite utilisé lors
 * de l'exécution des instructions.
 *
 * @param __input le programme BrainFuck à analyser
 * @return un `loops` qui représente les boucles du programme
 *
 * @see execute_instruction
 */
loops build_loops(const char* __input);

#endif // BRAINFUCK_BRAINFUCK_H
