# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/20 18:26:17 by gde-mora          #+#    #+#              #
#    Updated: 2023/03/29 22:06:24 by gde-mora         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	=	minishell

SRC 	=	src/main.c \
			src/end_program.c \
			src/repl/init_repl.c \
			src/repl/init_repl_signals_handling.c \
			src/envp/dict_env_utils.c \
			src/envp/find_env.c \
			src/envp/set_initial_envp.c \
			src/envp/att_virtual_envp.c \
			src/envp/att_envp_exitstatus_var.c \
			src/expander/init_expander.c \
			src/expander/handle_quotes.c \
			src/expander/handle_quotes_utils.c \
			src/expander/split_with_char.c \
			src/lexer/init_lexer.c \
			src/lexer/handle_quotes.c \
			src/lexer/token_utils.c \
			src/lexer/redirect_token_utils.c \
			src/parser/init_parser.c \
			src/executor/execute_built_in.c \
			src/executor/init_executor.c \
			src/built_in/ft_cd.c \
			src/built_in/ft_cd_error_msg.c \
			src/built_in/ft_echo.c \
			src/built_in/ft_env.c \
			src/built_in/ft_export_error_msg.c \
			src/built_in/ft_exit.c \
			src/built_in/ft_export.c \
			src/built_in/ft_pwd.c \
			src/built_in/ft_unset.c \

OBJ 	=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

OBJ_DIR	=	./obj

# MAKEFILE UTILS 
LIBFT_A =	./libft/libft.a

HEADERS =	./headers/minishell.h ./headers/functions.h ./headers/structs.h

# CCFLAGS =	-Wall -Wextra -Werror

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
	@mkdir -p $(OBJ_DIR)/src/envp
	@mkdir -p $(OBJ_DIR)/src/lexer
	@mkdir -p $(OBJ_DIR)/src/parser
	@mkdir -p $(OBJ_DIR)/src/expander
	@mkdir -p $(OBJ_DIR)/src/executor
	@mkdir -p $(OBJ_DIR)/src/built_in

## FULL CLEAN ALL OBJECTS AND TESTERS
git: fclean
	make fclean -C tester
	git add . && clear && git status

valgrind: $(NAME)
	valgrind --suppressions=tester/readline.supp --leak-check=full --show-leak-kinds=all  ./minishell

.PHONY: all clean fclean re create_obj_dir git valgrind
