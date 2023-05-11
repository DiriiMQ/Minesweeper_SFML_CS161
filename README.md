# CS161 - Minesweeper

## Requirements

- C++ 17 – GNU GCC 7.3.0+ ([MinGW64](https://github.com/niXman/mingw-builds-binaries/releases/download/12.2.0-rt_v10-rev2/x86_64-12.2.0-release-posix-seh-msvcrt-rt_v10-rev2.7z) for Windows)
- [SFML](https://www.sfml-dev.org/download/sfml/2.5.1/)
- [Cmake](https://cmake.org/download/)

## Preparation

- Clone GitHub repository.
- Build Cmake
  - ```cmake -DSFML_DIR:PATH=<path_to_SFML>/lib/cmake/SFML -G"MinGW Makefiles" -S . -B build``` for Windows.
  - ```cmake -DSFML_DIR:PATH=<path_to_SFML>/cmake/SFML -S . -B build``` for Linux.
- Build Makefile
  - ```make -C build```
- Run ```copy bin\* build``` (for Windows only).
- The executable file is created in `./build`.

## Features

- Saving high scores for each level.
- Saving the current state of the board.
- Customizable board dimensions and the number of bombs.
- All the basic features of this project’s requirements.

## Documentation

Read the documentation [here](https://studenthcmusedu-my.sharepoint.com/:w:/g/personal/22125083_student_hcmus_edu_vn/EYZTaYgKJk1Eg5KeJaezfZoBdkiB5-Ke6y5OWvXmoegIzw?e=LuciOr).
