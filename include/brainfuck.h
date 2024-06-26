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
#include <stdio.h>

/**
 * @file
 * @brief L'entête principale
 */

/**
 * @brief Représente une boucle _Brainfuck_
 *
 * Le programme `[[[][]][[][]]]` sera représenté de la manière suivante :
 *
 * ```
 *     R O O T
 *        ↕
 * [[[][]] [[][]]]
 *    ↙       ↖
 * [[][]]-->[[][]]
 *  ↙  ↖     ↙  ↖
 * []->[]   []->[]
 * ```
 */

typedef struct loop {
    const char* begin; ///< L'emplacement du caractère '['
    const char* end; ///< L'emplacement du caractère ']'

    /**
     * @brief Un pointeur vers la boucle fille.
     *
     * @remark Ce membre est nul dans le cas où la boucle n'admet pas de boucle
     * fille.
     */

    const struct loop* below;

    const struct loop* next; ///< La sœur immédiatement à droite
} loop;

/**
 * @brief Compile un programme _Brainfuck_
 *
 * Cette fonction construit un code C équivalent à celui d'un programme
 * _Brainfuck_ donné.
 *
 * @param __input programme _Brainfuck_ passé en entrée
 * @param __output sortie de la fonction
 */

void compile(FILE* __input, FILE* __output);

/**
 * @brief Alloue le tableau dans lequel le programme _Brainfuck_ stocke des
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
 * @brief Récupère le programme _Brainfuck_ à interpréter depuis un fichier
 *
 * @param __file le fichier _Brainfuck_ à lire
 * @return un tableau de caractère terminé par le caractère '\0' ou `NULL` si
 * `__filename` n'existe pas dans le répertoire courant
 *
 * @see execute_instruction() free_input()
 */

const char* get_input(FILE* __file);

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
 * Analyse le programme _Brainfuck_ passé en paramètre pour construire un
 * `loop` qui représente les boucles du programme. Celui-ci sera ensuite
 * utilisé lors de l'exécution des instructions.
 *
 * @param __input le programme _Brainfuck_ à analyser
 * @return un `loop` qui représente les boucles du programme
 *
 * @remark Pour des raisons d'implémentation, avoir plus de 255 boucles
 * imbriquées les unes dans les autres n'est pas possible. Dans le cas où cette
 * condition n'est pas respectée, le comportement est indéfini.
 *
 * @see get_input() free_loops() loop execute_instruction()
 */

const loop* build_loops(const char* __input);

/**
 * @brief Libère ce qui a été alloué par `build_loops`.
 *
 * @param __loops L'instance `loop` à libérer
 *
 * @see loop build_loops()
 */

void free_loops(loop* __loops);

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
    uint8_t**    __current_cell,
    const loop** __current_loop
);

#endif // BRAINFUCK_BRAINFUCK_H
