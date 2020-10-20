NAME=libmalloc.so

CC=gcc
FLAGS=-Wall -Werror -Wextra -Weverything

SCRIPT_PATH=scripts/
include $(SCRIPT_PATH)/srcs.mk
include $(SCRIPT_PATH)/includes.mk

OBJ=$(SRC:.c=.o)

LIB_PATH=libft/
LIB=$(LIB_PATH)/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -shared -o $(NAME) $(OBJ)

$(SRC_PATH)%.o: $(SRC_PATH)%.c $(INC)
	$(CC) $(FLAGS) -I$(INC_PATH) -I$(LIB_PATH) -o $@ -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
