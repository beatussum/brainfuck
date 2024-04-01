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

#include <stdint.h>
#include <stdlib.h>

typedef struct loop {
    const char* begin;
    const char* end;

    const struct loop* below;
    const struct loop* next;
} loop;

/**
 * @brief Alloue le tableau dans lequel le programme Brainfuck stocke des
 * valeurs
 *
 * @param __size la taille du tableau à allouer
 * @return le pointeur sur le tableau alloué (nul en cas d'échec d'allocation)
 *
 * @see execute_instruction() free_cells()
 */
static inline uint8_t* build_cells(size_t __size)
    { return calloc(sizeof(uint8_t), __size); }

/**
 * @brief Libère ce qui a été alloué par `build_cells()`
 *
 * @param __cells les cases à libérer
 *
 * @see build_cells()
 */
static inline void free_cells(uint8_t* __cells) { free(__cells); }

/**
 * @brief Récupère le programme Brainfuck à interpréter depuis un fichier
 *
 * @param __filename le nom du fichier Brainfuck à récupérer
 * @return un tableau de caractère terminé par le caractère `'\0'` ou `NULL` si
 * `input_filename` n'existe pas dans le répertoire courant
 *
 * @see execute_instruction() free_input()
 */
const char* get_input(const char* __filename);

/**
 * @brief Libère ce qui a été alloué par `get_input()`
 *
 * @param __input l'entrée à libérer
 *
 * @see get_input()
 */
static inline void free_input(char* __input) { free(__input); }

/**
 * @brief Construit le tableau des boucles
 *
 * Analyse le programme Brainfuck passé en paramètre pour construire un `loop`
 * qui représente les boucles du programme. Celui-ci sera ensuite utilisé lors
 * de l'exécution des instructions.
 *
 * @param __input le programme Brainfuck à analyser
 * @return un `loop` qui représente les boucles du programme
 *
 * @see get_input() free_loops() loop execute_instruction()
 */
const loop* build_loops(const char* __input);

/**
 * @brief Libère ce qui a été alloué par `build_loops`.
 *
 * @param loops L'instance `loop` à libérer
 *
 * @see loop build_loops()
 */
void free_loops(loop* __loops);

/**
 * @brief Passe à la boucle suivante.
 *
 * @param __loop L'instance `loop` à incrémenter
 *
 * @see loop build_loops()
 */
const loop* next_loop(const loop* __loop);

/**
 * @brief Exécute l'instruction pointée et passe à la suivante.
 *
 * @param __current_instruction un pointeur vers le pointeur d'instructions
 * @param __current_cell un pointeur vers le pointeur de données
 * @param __current_loop un pointeur vers le pointeur de la boucle courante
 *
 * @see get_input() loop build_loops()
 */
void execute_instruction(
    const char** __current_instruction,
    uint8_t** __current_cell,
    const loop** __current_loop
);

#endif // BRAINFUCK_BRAINFUCK_H
