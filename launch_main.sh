#!/bin/bash
gcc -L./ -o malloc main.c -lmalloc libft/libft.a && ./malloc
