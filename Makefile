# MAKEFLAGS += silent

CC = gcc -Wall -Wextra -Werror -lreadline -g -fsanitize=address -I ~/.brew/opt/readline/include -L ~/.brew/opt/readline/lib -lreadline

NAME = minishell

HEADER = includes

DEPS = $(shell find $(HEADER) -type f -name *.h)

LIBFT = Libft

LIBS = -L./$(LIBFT) -lft

SRC = $(wildcard ./parsing/*.c) $(wildcard ./environment/*.c) $(wildcard ./heredoc/*.c) $(wildcard ./executor/*.c) $(wildcard ./builtins/*.c) main.c

OBJ = $(SRC:Obj/%.o=%.c)

INC = -I$(HEADER) -I$(LIBFT) 

Obj/%.o: %.c
	mkdir -p Obj
	$(CC) $(INC) -o $@ -c $<

all: $(NAME)

$(NAME):  $(OBJ) $(DEPS)
	test -s $(LIBFT)/libft.a || $(MAKE) -C Libft
	$(CC) $(OBJ) $(INC) -o $@ $(LIBS)

clean:  
	$(MAKE) clean -C Libft
	rm -rf Obj

fclean: clean
	$(MAKE) fclean -C Libft
	rm -f minishell

re: fclean all

.PHONY: all clean fclean re
