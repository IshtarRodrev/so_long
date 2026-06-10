# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akechedz <akechedz@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/13 17:43:40 by akechedz          #+#    #+#              #
#    Updated: 2026/06/05 22:28:22 by akechedz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# This Makefile example contains some variables and automatic variables
# Below is the same Makefile without the variables and automatic variables
# NAME is a variable containing the name of the executable
# we want to create.
NAME = libft.a

CC = cc

CCFLAGS = -Wall -Wextra -Werror -g

# SRC is a variable containing all .c files required to build the project
	# Note that every file name has to be separated by a space and that I 
	# didn't use a wildcard (*.c) to get every file.
	# While the usage of a wildcard would be simpler, it is not authorized by
	# the 42 Norm as it is easier to input an unwanted file in the build 
	# process by simply adding it in the src folder.
SRC = ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_memset.c\
	ft_bzero.c\
	ft_memcpy.c\
	ft_memmove.c\
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_memchr.c\
	ft_memcmp.c\
	ft_strnstr.c\
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_strmapi.c \
	ft_putnbr_fd.c \
	ft_printf/ft_printf.c \
	ft_printf/ft_puthex_unsigned.c \
	ft_printf/ft_putnbr_unsigned.c \
	ft_printf/ft_putnbr.c \
	ft_printf/ft_putptr_ul.c \
	get_next_line/get_next_line.c

HEADER = libft.h


OBJ := $(SRC:.c=.o)

BONUS_OBJ = $(BONUS_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CCFLAGS) -I. -Ift_printf -c $< -o $@

clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME) $(BONUS_OBJ)

re: fclean all

.PHONY: all clean fclean re #test debug