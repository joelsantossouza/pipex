# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/26 12:16:12 by joesanto          #+#    #+#              #
#    Updated: 2025/11/28 16:27:50 by joesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
FLAGS = -Wall -Wextra -Werror -g

SRCS_DIR = srcs

EXEC_DIR = $(SRCS_DIR)/exec
EXEC = $(addprefix $(EXEC_DIR)/, exec_pipe.c exec_pipe_chain.c)

GET_DIR = $(SRCS_DIR)/get
GET = $(addprefix $(GET_DIR)/, get_cmd.c)

FREES_AND_CLOSES_DIR = $(SRCS_DIR)/frees_and_closes
FREES_AND_CLOSES = $(addprefix $(FREES_AND_CLOSES_DIR)/, free_cmd.c close_pipe.c)

MAIN = $(addprefix $(SRCS_DIR)/, main.c)

HEADERS_DIR = includes
HEADERS = $(addprefix $(HEADERS_DIR)/, pipex.h)

OBJS = $(MAIN:.c=.o) $(EXEC:.c=.o) $(GET:.c=.o) $(FREES_AND_CLOSES:.c=.o)
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
