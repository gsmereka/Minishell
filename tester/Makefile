# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/27 12:56:10 by gsmereka          #+#    #+#              #
#    Updated: 2023/01/27 18:19:20 by gsmereka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TESTERS_DIR		=	0_repl \
					# 1_lexer	\

$(MAKE_ALL):
	make -C $(TESTERS_DIR)

all: $(TESTERS_DIR)
	make -C 0_repl
	# make -C 1_lexer

clean: $(TESTERS_DIR)
	make clean -C 0_repl
	# make clean -C 1_lexer

fclean: $(TESTERS_DIR)
	make fclean -C 0_repl
	# make fclean -C 1_lexer

git: fclean
	git add . && clear && git status