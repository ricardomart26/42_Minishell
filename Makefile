# MAKEFLAGS += silent

CC = gcc -lreadline -g -I ~/.brew/opt/readline/include -L ~/.brew/opt/readline/lib -lreadline -fsanitize=address

NAME = minishell

HEADER = includes

DEPS = $(shell find $(HEADER) -type f -name *.h)

LIBFT = Libft

LIBS = -L./$(LIBFT) -lft

SRC = $(wildcard ./parsing/*.c) $(wildcard ./environment/*.c) $(wildcard ./heredoc/*.c) $(wildcard ./executor/*.c) $(wildcard ./builtins/*.c) $(wildcard ./init_shell/*.c)

OBJ = $(SRC:Obj/%.o=%.c)

INC = -I$(HEADER) -I$(LIBFT) 

Obj/%.o: %.c
	mkdir -p Obj
	$(CC) $(INC) -o $@ -c $<

all: $(NAME)

$(NAME):  $(OBJ) $(DEPS)
	test -s $(LIBFT)/libft.a || $(MAKE) -C Libft
	$(CC) $(OBJ) $(INC) -o $@ $(LIBS) $(LIBFT)/libft.a

clean:  
	$(MAKE) clean -C Libft
	rm -rf Obj

fclean: clean
	$(MAKE) fclean -C Libft
	rm -f minishell

re: fclean all

.PHONY: all clean fclean re
