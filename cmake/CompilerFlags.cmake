# Copyright (C) 2024 Mattéo Rossillol‑‑Laruelle <beatussum@protonmail.com>
#
# This program is free software: you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option) any later
# version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
# details.
#
# You should have received a copy of the GNU General Public License along with
# this program. If not, see <https://www.gnu.org/licenses/>.


cmake_minimum_required(VERSION 3.28.3)

macro(add_gcc_c_flags __flags)
    if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
        foreach (flag IN LISTS __flags)
            string(APPEND CMAKE_C_FLAGS " ${__flags}")
        endforeach()
    endif()
endmacro()
