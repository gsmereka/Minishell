# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/20 18:26:17 by gde-mora          #+#    #+#              #
#    Updated: 2023/04/08 03:10:29 by gde-mora         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	=	minishell

SRC 	=	src/main.c \
			src/end_program.c \
			src/ft_strjoin_with_free.c \
			src/close_fds.c \
			src/signals/init_repl_signals_handling.c \
			src/signals/heredoc_signals_handling.c \
			src/signals/child_signals_handling.c \
			src/repl/init_repl.c \
			src/repl/set_prompt.c \
			src/envp/dict_env_utils.c \
			src/envp/find_env.c \
			src/envp/set_initial_envp.c \
			src/envp/att_virtual_envp.c \
			src/envp/att_exit_status.c \
			src/expander/init_expander.c \
			src/expander/separe_quotes.c \
			src/expander/expand_content.c \
			src/expander/expand_envp_value.c \
			src/expander/handle_quotes_utils.c \
			src/expander/split_with_char.c \
			src/lexer/init_lexer.c \
			src/lexer/slice_tokens.c \
			src/lexer/token_utils.c \
			src/parser/init_parser.c \
			src/parser/check_syntax.c \
			src/parser/is_redirect.c \
			src/executor/execute_built_in.c \
			src/executor/init_executor.c \
			src/executor/get_commands_info/clear_execution_data.c \
			src/executor/get_commands_info/is_reserved.c \
			src/executor/get_commands_info/0_get_commands_info.c \
			src/executor/get_commands_info/2_get_files.c \
			src/executor/get_commands_info/1_format_cmd.c \
			src/executor/get_commands_info/3_get_env_paths.c \
			src/executor/get_commands_info/4_set_cmds_paths.c \
			src/executor/heredoc/get_next_line_with_free.c \
			src/executor/heredoc/set_heredoc.c \
			src/executor/heredoc/heredoc_cmd_loop.c \
			src/executor/heredoc/heredoc_eof_delimitation.c \
			src/executor/heredoc/close_heredoc_pipes.c \
			src/executor/set_processes/set_processes.c \
			src/executor/set_processes/execute.c \
			src/executor/set_processes/set_files.c \
			src/executor/set_processes/redirect.c \
			src/built_in/ft_litoa.c \
			src/built_in/ft_atoli.c \
			src/built_in/ft_cd.c \
			src/built_in/ft_cd_error_msg.c \
			src/built_in/ft_echo.c \
			src/built_in/ft_env.c \
			src/built_in/ft_export_error_msg.c \
			src/built_in/ft_exit.c \
			src/built_in/ft_exit_utils.c \
			src/built_in/ft_export.c \
			src/built_in/ft_pwd.c \
			src/built_in/ft_unset.c \
			src/built_in/is_built_in.c \

OBJ 	=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

OBJ_DIR	=	./obj

# MAKEFILE UTILS 
LIBFT_A =	./libft/libft.a

HEADERS =	./headers/minishell.h ./headers/functions.h ./headers/structs.h

# CCFLAGS =	-Wall -Wextra -Werror

READLINE_FLAG	=	-lreadline

RM		=	rm -f

# RULES
all: $(NAME) ascii

ascii:
	@echo "\033[1;35m"
	@echo "░░┌──┐░░░░░░░░░░┌──┐░░░░░░┌──┐░░░░░░░░░░┌──┐░░░░░░┌──┐░░░░░░░░░░┌──┐░░"
	@echo "░╔╡▐▐╞╝░░┌──┐░░╔╡▐▐╞╝░░░░╔╡▐▐╞╝░░┌──┐░░╔╡▐▐╞╝░░░░╔╡▐▐╞╝░░┌──┐░░╔╡▐▐╞╝░"
	@echo "░░└╥╥┘░░╚╡▌▌╞╗░░└╥╥┘░░░░░░└╥╥┘░░╚╡▌▌╞╗░░└╥╥┘░░░░░░└╥╥┘░░╚╡▌▌╞╗░░└╥╥┘░░"
	@echo "░░░╚╚░░░░└╥╥┘░░░░╚╚░░░░░░░░╚╚░░░░└╥╥┘░░░░╚╚░░░░░░░░╚╚░░░░└╥╥┘░░░░╚╚░░░"
	@echo "░░░░░░░░░░╝╝░░░░░░░░░░░░░░░░░░░░░░╝╝░░░░░░░░░░░░░░░░░░░░░░╝╝░░░░░░░░░░"
	@echo "\033[0m"

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
	@mkdir -p $(OBJ_DIR)/src/executor/get_commands_info
	@mkdir -p $(OBJ_DIR)/src/executor/heredoc
	@mkdir -p $(OBJ_DIR)/src/executor/set_processes
	@mkdir -p $(OBJ_DIR)/src/signals

## FULL CLEAN ALL OBJECTS AND TESTERS
git: fclean
	make fclean -C tester
	git add . && clear && git status

valgrind: $(NAME)
	valgrind --suppressions=$$PWD/tester/readline.supp --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes ./minishell

.PHONY: all clean fclean re create_obj_dir git valgrind
