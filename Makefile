# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/18 13:19:13 by dantonik          #+#    #+#              #
#    Updated: 2022/12/24 05:29:53 by dantonik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=thread
SRC =	main.c \
		main_thread.c \
		minilibft.c \
		parse.c \
		print.c \
		routine.c \
		time.c

VPATH = src

OBJDIR = .bin

all: $(NAME)

OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))


$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) -c $^ -o $@

$(OBJDIR):
	mkdir .bin

$(NAME): $(OBJ) inc/philo.h
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

r: re
	printf "\e[1;1H\e[2J";
	./philo 5 800 200 200

clean:
	rm -rf $(OBJDIR)

fclean:
	make clean
	rm -f $(NAME)

re: fclean all

nice n: fclean all clean

.PHONY:
	clean fclean re nice