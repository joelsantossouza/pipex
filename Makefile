# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/26 12:16:12 by joesanto          #+#    #+#              #
#    Updated: 2025/11/26 20:25:00 by joesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
FLAGS = -Wall -Wextra -Werror -g

SRCS_DIR = srcs

EXEC_DIR = $(SRCS_DIR)/exec
EXEC = $(addprefix $(EXEC_DIR)/, execve_pipe.c)

MAIN = $(addprefix $(SRCS_DIR)/, main.c)

HEADERS_DIR = includes
HEADERS = $(addprefix $(HEADERS_DIR)/, pipex.h)

OBJS = $(MAIN:.c=.o) $(EXEC:.c=.o)
LIBS_DIR = libs
LIBFT = $(LIBS_DIR)/libft/libft.a
INCLUDES = $(addprefix -I, $(LIBS_DIR)/libft $(HEADERS_DIR))

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
