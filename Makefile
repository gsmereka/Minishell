# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/20 18:26:17 by gde-mora          #+#    #+#              #
#    Updated: 2023/03/19 12:13:23 by gsmereka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	=	minishell

SRC 	=	src/main.c \
			src/end_program.c \
			src/ft_strjoin_with_free.c \
			src/signals/init_repl_signals_handling.c \
			src/signals/heredoc_signals_handling.c \
			src/signals/child_signals_handling.c \
			src/repl/init_repl.c \
			src/envp/dict_env_utils.c \
			src/envp/find_env.c \
			src/envp/set_initial_envp.c \
			src/envp/att_virtual_envp.c \
			src/envp/att_envp_exitstatus_var.c \
			src/expander/init_expander.c \
			src/lexer/init_lexer.c \
			src/lexer/token_utils.c \
			src/parser/init_parser.c \
			src/executor/execute_built_in.c \
			src/executor/init_executor.c \
			src/executor/set_processes.c \
			src/executor/execute.c \
			src/executor/set_files.c \
			src/executor/redirect.c \
			src/executor/get_commands_info/commands_info_utils.c \
			src/executor/get_commands_info/format_cmd.c \
			src/executor/get_commands_info/get_commands_info.c \
			src/executor/get_commands_info/get_inputs.c \
			src/executor/get_commands_info/get_outputs.c \
			src/executor/get_commands_info/get_env_paths.c \
			src/executor/get_commands_info/set_cmds_paths.c \
			src/executor/get_commands_info/get_next_line_with_free.c \
			src/executor/heredoc/set_heredoc.c \
			src/executor/heredoc/heredoc_cmd_loop.c \
			src/executor/heredoc/heredoc_interrupt.c \
			src/executor/heredoc/close_heredoc_pipes.c \
			src/built_in/ft_cd.c \
			src/built_in/ft_cd_error_msg.c \
			src/built_in/ft_echo.c \
			src/built_in/ft_env.c \
			src/built_in/ft_export_error_msg.c \
			src/built_in/ft_exit.c \
			src/built_in/ft_export.c \
			src/built_in/ft_pwd.c \
			src/built_in/ft_unset.c \
			src/built_in/is_built_in.c \

OBJ 	=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

OBJ_DIR	=	./obj

# MAKEFILE UTILS 
LIBFT_A =	./libft/libft.a

HEADERS =	./headers/minishell.h ./headers/functions.h ./headers/structs.h

CCFLAGS =	-g3
# -Wall -Wextra -Werror 
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
	@mkdir -p $(OBJ_DIR)/src/executor/get_commands_info
	@mkdir -p $(OBJ_DIR)/src/executor/heredoc
	@mkdir -p $(OBJ_DIR)/src/signals

## FULL CLEAN ALL OBJECTS AND TESTERS
git: fclean
	make fclean -C tester
	git add . && clear && git status

valgrind: $(NAME)
	valgrind --suppressions=tester/readline.supp --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes ./minishell

.PHONY: all clean fclean re create_obj_dir git valgrind