# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/20 11:23:00 by mamaral-          #+#    #+#              #
#    Updated: 2023/12/07 13:26:02 by mamaral-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
RM = rm -rf

NAME = philo

CFLAGS = -Wall -Wextra -Werror -pthread -g #-fsanitize=thread

INCLUDES = -I ./inc/
SRC_DIR = ./src

SRCS = philosophers utils init

SRCS := $(SRCS:%=$(SRC_DIR)/%.c)

OBJS = $(SRCS:%.c=%.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	
clean: 
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re : fclean all

vg: override CFLAGS := -Wall -Werror -Wextra -pthread -g
vg: fclean $(NAME)

.PHONY: all clean fclean re