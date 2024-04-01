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

project(
    brainfuck
    VERSION 0.9.0
    DESCRIPTION "A Brainfuck interpreter"
    HOMEPAGE_URL "https://github.com/beatussum/brainfuck/"
    LANGUAGES C
)

option(WITH_DOCS "Enable building of documentation" OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(CompilerFlags)

find_package(Ccache MODULE)
enable_ccache()

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED TRUE)
set(CMAKE_C_EXTENSIONS FALSE)

add_gcc_c_flags(
    -fmessage-length=75
    -fno-gnu-keywords
    -fno-operator-names
    -funsigned-char
    -pipe
    -Wall
    -Wconversion
    -Wdouble-promotion
    -Wduplicated-branches
    -Wduplicated-cond
    -Wfloat-equal
    -Wignored-qualifiers
    -Wimplicit-fallthrough=5
    -Wmissing-field-initializers
    -Wmissing-include-dirs
    -Wno-div-by-zero
    -Wnoexcept
    -Wold-style-cast
    -Woverloaded-virtual
    -Wpedantic
    -Wsuggest-attribute=const
    -Wsuggest-attribute=noreturn
    -Wsuggest-attribute=pure
    -Wsuggest-final-methods
    -Wsuggest-final-types
    -Wsuggest-final-types
    -Wsuggest-override
    -Wsuggest-override
    -Wundef
    -Wuninitialized
)

set(BRAINFUCK_C main.c brainfuck.c)
list(TRANSFORM BRAINFUCK_C PREPEND "src/")

set(BRAINFUCK_H brainfuck.h)
list(TRANSFORM BRAINFUCK_H PREPEND "include/")

find_package(Doxygen)

if(DOXYGEN_FOUND AND WITH_DOCS)
    set(DOCS_DIR "${CMAKE_BINARY_DIR}/docs" CACHE PATH "The path where the documention is built")
    set(DOCS_NAMESPACE "fr.beatussum.brainfuck")

    set(DOXYGEN_ALLOW_UNICODE_NAMES YES)
    set(DOXYGEN_EXTRACT_STATIC YES)
    set(DOXYGEN_INLINE_INHERITED_MEMB YES)
    set(DOXYGEN_OUTPUT_DIRECTORY "${DOCS_DIR}")
    set(DOXYGEN_OUTPUT_LANGUAGE "French")
    set(DOXYGEN_WARN_LOGFILE "${DOCS_DIR}/log")
    set(DOXYGEN_WARN_NO_PARAMDOC YES)

    doxygen_add_docs(docs "${BRAINFUCK_H}" COMMENT "Generating documentation…")
endif()

include_directories(include)

add_executable(brainfuck "${BRAINFUCK_C}" "${BRAINFUCK_H}")

if (WIN32)
    set_target_properties(brainfuck PROPERTIES WIN32_EXECUTABLE TRUE)
endif()
