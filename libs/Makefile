# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/23 14:42:57 by flemaitr          #+#    #+#              #
#    Updated: 2023/01/20 11:39:55 by cjunker          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =		src/ft_printf_fd.c \
			src/ft_printf_fd_tools.c \
			src/get_next_line.c \
			src/get_next_line_utils.c \
			src/ft_atoi.c \
			src/ft_bzero.c \
			src/ft_calloc.c \
			src/ft_isalnum.c \
			src/ft_isalpha.c \
			src/ft_isascii.c \
			src/ft_isdigit.c \
			src/ft_isprint.c \
			src/ft_itoa.c \
			src/ft_memchr.c \
			src/ft_memcmp.c \
			src/ft_memcpy.c \
			src/ft_memmove.c \
			src/ft_memset.c \
			src/ft_putchar_fd.c \
			src/ft_putendl_fd.c \
			src/ft_putnbr_fd.c \
			src/ft_putstr_fd.c \
			src/ft_split.c \
			src/ft_strchr.c \
			src/ft_strdup.c \
			src/ft_striteri.c \
			src/ft_strjoin.c \
			src/ft_strlcat.c \
			src/ft_strlcpy.c \
			src/ft_strlen.c \
			src/ft_strmapi.c \
			src/ft_strncmp.c \
			src/ft_strnstr.c \
			src/ft_strrchr.c \
			src/ft_strtrim.c \
			src/ft_substr.c \
			src/ft_tolower.c \
			src/ft_toupper.c \
			src/ft_lstnew.c \
			src/ft_lstadd_front.c \
			src/ft_lstsize.c \
			src/ft_lstlast.c \
			src/ft_lstadd_back.c \


			
OBJS =		$(SRCS:.c=.o)

CC = 		gcc
AR = 		ar rsc
CFLAGS = 	-Wall -Wextra -Werror -g
INCLUDES =	-I./includes

NAME =		libft.a

%.o:		%.c
			@printf '\033[1m\033[38;239;97;51m'"\r\033[KCompiling LIBFT objects... ⏳ "'\033[1m\033[38;217;0;83m'"<$<>"'\033[0m'
			@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<
			
all:		$(NAME)

$(NAME):  	$(OBJS)
			@$(AR) $(NAME) $(OBJS) 
			
clean:
			@rm -f $(OBJS)

fclean:		clean
			@rm -f $(NAME)
			
re:			fclean all

.PHONY: 	all test clean fclean re