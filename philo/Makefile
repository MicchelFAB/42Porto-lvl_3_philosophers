# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/20 11:23:00 by mamaral-          #+#    #+#              #
#    Updated: 2023/11/20 11:35:07 by mamaral-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
RM = rm -rf

NAME = philo

CFLAGS = -Wall -Wextra -Werror
THREAD = -lpthread
DEBUG = -g -fsanitize=thread

INCLUDES = -I ./inc/
SRC_DIR = ./src/

SRCS = 

SRCS := $(SRCS:%=$(SRC_DIR)/%.c)

OBJS = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREAD) $(OBJS) -o $(NAME)

.o=.c:
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean: 
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re