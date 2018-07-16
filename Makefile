# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/09 23:21:55 by psprawka          #+#    #+#              #
#    Updated: 2018/07/11 11:40:09 by psprawka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ft_ssl
FLAGS		= -g -Wall -Wextra -Werror
FLAGS		+=  -fsanitize=address

HEADERS		= includes/
SRCS_DIR	= srcs/
HANDLE		= handle/

SRCS =	$(SRCS_DIR)main.c \
			$(SRCS_DIR)tools.c \
			$(SRCS_DIR)get.c \
			$(SRCS_DIR)print.c \
			$(SRCS_DIR)reset_data.c \
			$(SRCS_DIR)$(HANDLE)md5.c \
			$(SRCS_DIR)$(HANDLE)sha256.c \
			$(SRCS_DIR)$(HANDLE)padding.c \


OBJS = $(SRCS:.c=.o)
LIBFT = libft/libft.a

BUILD_PRINT = @echo "\r\033[K\033[0;38;5;206m[FT_SSL_MD5] \033[38;5;80mBuilding $<"
DONE = @echo "\033[K\033[1;38;5;200mFT_SSL_MD5 ready to use!"
CLEAN_O = @echo "\033[38;5;246mObject files removed! [FT_SSL_MD5]"
CLEAN_A = @echo "\033[38;5;246mExecutable removed! [FT_SSL_MD5]"

all: $(NAME)

$(NAME) : $(LIBFT) $(OBJS) $(HEADERS)
	@gcc $(FLAGS) -I $(HEADERS) $(OBJS) $(LIBFT) -lncurses -o $(NAME)
	$(DONE)

$(LIBFT):
	@make -C libft
	@echo ""

%.o: %.c
	$(BUILD_PRINT)
	@gcc $(CFLAGS) -I $(HEADERS) -c $< -o $@

clean:
	@$(MAKE) -C libft/ clean
	@rm -f $(OBJS)
	$(CLEAN_O)

fclean: clean
	@$(MAKE) -C libft/ fclean
	@rm -f $(NAME)
	$(CLEAN_A)

re: fclean all
