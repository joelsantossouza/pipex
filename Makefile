# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/26 12:16:12 by joesanto          #+#    #+#              #
#    Updated: 2025/11/26 12:37:45 by joesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
FLAGS = -Wall -Wextra -Werror -g

SRCS_DIR = srcs
MAIN = $(addprefix $(SRCS_DIR)/, main.c)

OBJS = $(MAIN:.c=.o)
LIBS_DIR = libs
LIBFT = $(LIBS_DIR)/libft/libft.a
INCLUDES = $(addprefix -I, $(LIBS_DIR)/libft)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) -o $@

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@if [ ! -d "$(dir $@)" ]; then \
		git clone git@github.com:joelsantossouza/libft.git $(dir $@); \
	fi
	make -C $(dir $@)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -rf $(LIBS_DIR)

re: fclean all
