# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/19 18:51:25 by gsmereka          #+#    #+#              #
#    Updated: 2023/01/22 22:39:03 by gsmereka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	my_tester

HEADERS			=	./headers/tester.h ./headers/structs.h

# CFLAGS			=	-Wall -Wextra -Werror

OBJ_DIR			=	./obj

SRC_DIR			=	src

SRC				=	main.c

OBJ				=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: mk_obj_dir $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(HEADERS) $(OBJ)
	cc $(CFLAGS) -o $(NAME) $(OBJ)

mk_obj_dir:
	@mkdir -p $(OBJ_DIR)

git: fclean
	git add . && clear && git status

clear: $(NAME) clean
	clear

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: bonus all clean fclean re clear
