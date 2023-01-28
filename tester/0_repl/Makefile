# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/19 18:51:25 by gsmereka          #+#    #+#              #
#    Updated: 2023/01/27 22:35:44 by gsmereka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	../0_tester_repl

HEADERS			=	./headers/tester.h ./headers/structs.h

CFLAGS			=	-Wall -Wextra -Werror

OBJ_DIR			=	./obj

SRC_DIR			=	src

SRC				=	main.c finalize.c redirect.c  test_loop.c \
					free_program_memory.c \
					set_valgrind_path.c \
					initialize/initialize.c \
					initialize/set_files.c \
					verify_results/verify_results.c \
					verify_results/check_leaks.c \
					utils/ft_split.c \
					utils/ft_substr.c \
					utils/ft_itoa.c \
					utils/ft_strjoin.c \

OBJ				=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

## Esta regra define a quantidade de testes realizados dependendo do numero de arquivos na pasta
GET_TESTS_AMOUNT	=	$(shell find $(GET_LOCAL_PATH)/tests/input_tests/ -type f | wc -l) 

## Esta regra define o Local Padrão dos arquivos
GET_LOCAL_PATH			=	$(shell pwd)

## Esta regra define as variaveis utilizadas
VARIABLE_FLAGS		=	-D LOCAL_PATH='"$(GET_LOCAL_PATH)"' -D TESTS_AMOUNT=$(GET_TESTS_AMOUNT) 

all: mk_obj_dir $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	cc $(CFLAGS) $(VARIABLE_FLAGS) -c $< -o $@

$(NAME): $(HEADERS) $(OBJ)
	cc $(CFLAGS) $(VARIABLE_FLAGS) -o $(NAME) $(OBJ)

mk_obj_dir:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/initialize
	@mkdir -p $(OBJ_DIR)/utils
	@mkdir -p $(OBJ_DIR)/verify_results

git: fclean
	git add . && clear && git status

clear: mk_obj_dir $(NAME) clean
	clear

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: bonus all clean fclean re clear
