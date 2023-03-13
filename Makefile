NAME = minishell

SRC = ${shell find ./parser -name "*.c" && find ./lexer_expander -name "*.c" && find ./builtins -name "*.c" && echo *.c}

OBJ = $(patsubst %.c, %.o, $(SRC))

READLINE = -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline

HEADER = minishell.h

LIBFT = ./libft/libft.a

CC = gcc

CFLAGS = -Werror -Wextra -Wall

all: $(NAME)

$(NAME) : $(OBJ) $(HEADER)
	(cd libft; make)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(READLINE) -o $(NAME)

clean:
	(cd libft; make clean)
	rm -f $(OBJ)

fclean: clean
	(cd libft; make fclean)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re