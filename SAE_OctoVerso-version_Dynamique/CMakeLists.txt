cmake_minimum_required(VERSION 3.30)
project(Projet C)

set(CMAKE_C_STANDARD 11)

add_executable(Projet main.c
        chevalet.h
        chevalet.c
        joueur.h
        joueur.c
        jeu.h
        jeu.c
        rail.h
        rail.c)
