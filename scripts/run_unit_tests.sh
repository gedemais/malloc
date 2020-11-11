#!/bin/bash
#gcc -L./  -Iinclude/ -Ilibft/ -o unit_tests/malloc_free unit_tests/malloc_free.c -lmalloc libft/libft.a
#unit_tests/malloc_free

gcc -L./  -Iinclude/ -Ilibft/ -o unit_tests/main_rand unit_tests/main_rand.c -lmalloc libft/libft.a
unit_tests/main_rand
