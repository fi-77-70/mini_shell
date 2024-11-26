NAME = minishell

SRC = main.c ./parsing/lexer.c ./parsing/expander.c ./parsing/input_parsing.c \
		./executer/execute.c	./parsing/input_divider.c	./executer/exe_bui.c ./parsing/expand_utils.c	\
		./builtins/cd.c	\

LIBS = ./libs/libft/libft.a	./libs/ft_printf/libftprintf.a

CC = cc -Wall -Werror -Wextra -g

all: $(NAME)

$(NAME): $(SRC) $(LIBS)
		$(CC) $(SRC) $(LIBS) -lreadline -o $(NAME)

re: fclean all

$(LIBS):
		make -C ./libs/libft
		make -C ./libs/ft_printf

valgrind: 
	@echo "{\n   leak readline\n   Memcheck:Leak\n...\n   fun:readline\n}\n{\n   leak add_history\n   Memcheck:Leak\n...\n   fun:add_history\n}" > readline.supp
	@valgrind --suppressions=readline.supp --leak-check=full -s --show-leak-kinds=all ./$(NAME)

clean:
		rm	readline.supp
		make clean -C ./libs/libft
		make clean -C ./libs/ft_printf
fclean:
		make fclean -C ./libs/libft
		make fclean -C ./libs/ft_printf
		rm -f minishell
