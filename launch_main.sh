#!/bin/bash
gcc -L./  -Iinclude/ -Ilibft/ -o malloc main.c -lmalloc libft/libft.a && ./malloc
