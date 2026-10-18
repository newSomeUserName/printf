# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgerman <tgerman@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/10/18 16:00:00 by tgerman           #+#    #+#              #
#    Updated: 2026/10/18 16:00:00 by tgerman          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = ft_printf.c \
	ft_print_chars.c \
	ft_print_nums.c

SRCS_BONUS = ft_printf_bonus.c \
	ft_parse_bonus.c \
	ft_print_chars_bonus.c \
	ft_print_nums_bonus.c \
	ft_utils_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

BONUS_STAMP = .bonus

all: libft $(NAME)

libft:
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(RM) $(BONUS_STAMP)
	cp $(LIBFT) $(NAME)
	$(AR) $(NAME) $(OBJS)

bonus: libft $(BONUS_STAMP)

$(BONUS_STAMP): $(OBJS_BONUS) $(LIBFT)
	cp $(LIBFT) $(NAME)
	$(AR) $(NAME) $(OBJS_BONUS)
	touch $(BONUS_STAMP)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

%_bonus.o: %_bonus.c ft_printf_bonus.h $(LIBFT_DIR)/libft.h
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c ft_printf.h $(LIBFT_DIR)/libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME) $(BONUS_STAMP)
	$(RM) $(LIBFT)

re: fclean all

.PHONY: all bonus libft clean fclean re
