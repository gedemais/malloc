SRC_PATH=src/

SRC_NAME=	malloc.c\
		 	free.c\
		 	realloc.c\
			show_alloc_mem.c\
			dispatch.c\
		 	first_call.c\
		 	singletons.c

SRC=$(addprefix $(SRC_PATH), $(SRC_NAME))
