# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/05 09:22:22 by ecolin            #+#    #+#              #
#    Updated: 2022/10/10 14:48:11 by ecolin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -rf

HEADER = philosopher.HEADER

SRC = main.c new.c utils.c ft_atoi.c ft_isdigit.c clean.c
SOBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(SOBJ)
		$(CC) $(CFLAGS) $^ -o $(NAME)

clean:
	$(RM) $(SOBJ)

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all