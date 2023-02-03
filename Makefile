# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/20 18:26:17 by gde-mora          #+#    #+#              #
#    Updated: 2023/02/03 14:14:29 by gsmereka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	=	minishell

SRC 	=	src/main.c \
			src/repl/init_repl.c \
			src/repl/init_repl_signals_handling.c \
			src/expander/init_expander.c \
			src/lexer/init_lexer.c \
			src/parser/init_parser.c \
			src/executor/init_executor.c \

OBJ 	=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

OBJ_DIR	=	./obj

# MAKEFILE UTILS 
LIBFT_A =	./libft/libft.a

HEADERS =	./headers/minishell.h ./headers/functions.h ./headers/structs.h

CCFLAGS =	-Wall -Wextra -Werror

READLINE_FLAG	=	-lreadline

RM		=	rm -f

# RULES
all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	make create_obj_dir
	cc $(CCFLAGS) -c $< -o $@

# LIBFT COMPILE
$(LIBFT_A):
	make -C libft

# MANDATORY COMPILE
$(NAME): $(OBJ) $(HEADERS) $(LIBFT_A)
	cc $(CCFLAGS) -o $(NAME) $(OBJ) $(LIBFT_A) $(READLINE_FLAG)

# RULES CLEAN FCLEAN AND RE
clean:
	$(RM) $(OBJ)
	$(RM) -r $(OBJ_DIR)
	make clean -C libft

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT_A)

re: fclean all

# CREATE OBJECTS DIR
create_obj_dir:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/src
	@mkdir -p $(OBJ_DIR)/src/repl
	@mkdir -p $(OBJ_DIR)/src/lexer
	@mkdir -p $(OBJ_DIR)/src/parser
	@mkdir -p $(OBJ_DIR)/src/expander
	@mkdir -p $(OBJ_DIR)/src/executor

## FULL CLEAN ALL OBJECTS AND TESTERS
git: fclean
	make fclean -C tester
	git add . && clear && git status

valgrind: $(NAME)
	valgrind --suppressions=tester/readline.supp --leak-check=full --show-leak-kinds=all  ./minishell

.PHONY: all clean fclean re create_obj_dir git valgrind
