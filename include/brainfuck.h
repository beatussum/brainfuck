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

/**
 * @brief Récupère le programme Brainfuck à interpréter depuis un fichier
 *
 * @param __filename le nom du fichier Brainfuck à récupérer
 * @return un tableau de caractère terminé par le caractère `'\0'` ou `NULL` si
 * `input_filename` n'existe pas dans le répertoire courant
 */
char* get_input(char* __filename);

#endif // BRAINFUCK_BRAINFUCK_H
