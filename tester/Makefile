# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/27 12:56:10 by gsmereka          #+#    #+#              #
#    Updated: 2023/01/27 23:06:49 by gsmereka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	for dir in */; do \
		$(MAKE) -C $$dir; \
	done

clean:
	for dir in */; do \
		$(MAKE) clean -C $$dir; \
	done

fclean:
	for dir in */; do \
		$(MAKE) fclean -C $$dir; \
	done

git: fclean
	git add . && clear && git status