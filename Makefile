# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/14 15:10:33 by aribeiro          #+#    #+#              #
#    Updated: 2016/03/14 15:10:38 by aribeiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = 	ft_bzero.c \
		ft_longlongtoa_base.c \
		ft_memdel.c \
		ft_memset.c \
		ft_printf.c \
		ft_printf_char.c \
		ft_printf_define.c \
		ft_printf_display.c \
		ft_printf_errors.c \
		ft_printf_int.c \
		ft_printf_int_uint_bis.c \
		ft_printf_len_nbc.c \
		ft_printf_oint.c \
		ft_printf_search_parse.c \
		ft_printf_str.c \
		ft_printf_str_null.c \
		ft_printf_tools.c \
		ft_printf_uint.c \
		ft_printf_wide.c \
		ft_printf_xint.c \
		ft_putchar.c \
		ft_putnbr.c \
		ft_putstr.c \
		ft_set_reset_bit.c \
		ft_strcat.c \
		ft_strcpy.c \
		ft_strlen.c \
		ft_strncpy.c \
		ft_strnew_exit.c \

OBJ = $(SRC:.c=.o)

INC = ./includes

all: $(NAME)

$(NAME):
	gcc -c $(SRC) -I $(INC)
	@echo
	ar rc $(NAME) $(OBJ)
	@echo
	ranlib $(NAME)
	@echo "\033[1;33m--> $(NAME) created\033[0m\033[22;37m"
	@echo

clean:
	rm -rf $(OBJ)
	@echo "\033[1;33m--> Obj deleted\033[0m\033[22;37m"
	@echo

fclean: clean
	rm -rf $(NAME)
	@echo "\033[1;33m--> $(NAME) deleted\033[0m\033[22;37m"
	@echo

re: fclean all
