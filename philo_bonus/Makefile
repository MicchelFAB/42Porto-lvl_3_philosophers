# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/20 11:23:00 by mamaral-          #+#    #+#              #
#    Updated: 2023/12/15 13:28:08 by mamaral-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
RM = rm -rf

NAME = philo_bonus

CFLAGS = -Wall -Wextra -Werror -pthread -g

INCLUDES = -I ./inc/
SRC_DIR = ./src

SRCS =  philo_b cul_str gastr_act tbl_gov tbl_serv

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

err: override CFLAGS := -Wall -Werror -Wextra -pthread -g -fsanitize=thread
err: fclean $(NAME)

.PHONY: all clean fclean re