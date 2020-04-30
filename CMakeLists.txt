cmake_minimum_required(VERSION 3.15)
project(ProgettoBiblioteca C)

set(CMAKE_C_STANDARD 99)

add_executable(ProgettoBiblioteca main.c Biblioteca.c Biblioteca.h Error.c Error.h)