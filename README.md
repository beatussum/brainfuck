# Brainfuck

## Quel est ce projet ?

Ce projet consiste en un interpréteur _Brainfuck_. Il s'agit d'un projet donné lors de mes études à [l'ENSIMAG](https://ensimag.grenoble-inp.fr/), une école d'ingénieur française en informatique, durant l'année scolaire **2023-2024**.

## Qu'est-ce que le Brainfuck ?

Brainfuck est un langage de programmation exotique, inventé par Urban Müller en 1993. Il tire son nom de l’union de deux mots anglais, brain (« cerveau ») et fuck (« niquer »), et joue sur les mots, puisque ce langage est volontairement simpliste, et parce que l'expression Brain Fuck évoque, en argot, ce qui met le cerveau dans un état de confusion par sa complexité apparente. Ce vocabulaire peu flatteur lui a d'ailleurs valu d'être écrit sous d'autres orthographes plus prudes, telles que Brainf\*ck, Brainf\*\*\* ou encore BF. [^1]

## Construction depuis les sources

### Dépendances

Pour construire `brainfuck`, les dépendances suivantes sont nécessaires (**uniquement lors de la construction**) :

- [CMake](https://cmake.org/)
- [Doxygen](https://www.doxygen.nl/) [^2]
- [Git](https://git-scm.com/)

### Instructions

1. Récupérer les sources.

    ```bash
    git clone "https://github.com/beatussum/brainfuck.git"
    ```

1. Se placer dans le répertoire.

    ```bash
    cd brainfuck
    ```

1. Créer le dossier de construction.

    ```bash
    mkdir build
    cd build
    ```

1. Lancer **CMake**.

    ```bash
    cmake -DCMAKE_BUILD_TYPE:STRING="Release" -G Ninja ..
    ```

    Pour construire en plus la documentation, rajouter l'option `-DWITH_DOCS:BOOL=YES`.

1. Construire l'exécutable.

    ```bash
    ninja
    ```

    Pour construire la documentation, appeler

    ```bash
    ninja docs
    ```

## Licence

Le code de ce logiciel est sous licence GPL-3 ou toute version ultérieure.

[^1]: https://fr.wikipedia.org/wiki/Brainfuck
[^2]: seulement si vous souhaitez construire la documentation
