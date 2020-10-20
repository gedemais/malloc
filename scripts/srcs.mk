SRC_PATH=src/

SRC_NAME=	malloc.c\
		 	free.c\
		 	realloc.c\
		 	first_call.c\
		 	singletons.c\
			tools.c

SRC=$(addprefix $(SRC_PATH), $(SRC_NAME))
