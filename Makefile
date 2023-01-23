# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/20 18:26:17 by gde-mora          #+#    #+#              #
#    Updated: 2023/01/23 15:30:30 by gde-mora         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = ./main.c

OBJ = $(SRC:.c=.o)

# MAKEFILE UTILS
LIBFT_A = ./libft/libft.a

HEADERS = ./headers/minishell.h ./headers/functions.h ./headers/structs.h

CCFLAGS = -Wall -Wextra -Werror

RM = rm -f

# RULES
all: $(NAME)

.c.o:
	cc $(CCFLAGS) -c $< -o $(<:.c=.o) 

# LIBFT COMPILE
$(LIBFT_A):
	make -C libft

# MANDATORY COMPILE
$(NAME): $(OBJ) $(HEADERS) $(LIBFT_A)
	cc $(CCFLAGS) -o $(NAME) $(OBJ) $(LIBFT_A)

# RULES CLEAN FCLEAN AND RE
clean:
	$(RM) $(OBJ)
	make clean -C libft

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT_A)

re: fclean all

.PHONY: all clean fclean re