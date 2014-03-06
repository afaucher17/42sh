# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/21 16:00:53 by tdieumeg          #+#    #+#              #
#    Updated: 2014/03/06 15:17:12 by tdieumeg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

CC		= /usr/bin/gcc

DEPS	= libft.h

OBJ		= ft_atoi.o \
		  ft_atoi_base.o \
		  ft_bzero.o \
		  ft_clear_tab.o \
		  ft_concat.o \
		  ft_isalnum.o \
		  ft_isalpha.o \
		  ft_isascii.o \
		  ft_isdigit.o \
		  ft_isprint.o \
		  ft_itoa.o \
		  ft_itoa_base.o \
		  ft_memalloc.o \
		  ft_memccpy.o \
		  ft_memchr.o \
		  ft_memcmp.o \
		  ft_memcpy.o \
		  ft_memdel.o \
		  ft_memmove.o \
		  ft_memset.o \
		  ft_dlstnew.o \
		  ft_dlstpushfront.o \
		  ft_dlist_clear.o \
		  ft_list_clear.o \
		  ft_lstadd.o \
		  ft_lstaddend.o \
		  ft_lstdel.o \
		  ft_lstdelone.o \
		  ft_lstiter.o \
		  ft_lstmap.o \
		  ft_lstnew.o \
		  ft_lstpushback.o \
		  ft_putchar.o \
		  ft_putchar_fd.o \
		  ft_putendl.o \
		  ft_putendl_fd.o \
		  ft_putnbr.o \
		  ft_putnbr_fd.o \
		  ft_putnbr_endl.o \
		  ft_putnbr_endl_fd.o \
		  ft_putstr.o \
		  ft_putstr_fd.o \
		  ft_strcat.o \
		  ft_strchr.o \
		  ft_strclr.o \
		  ft_strcmp.o \
		  ft_strcpy.o \
		  ft_strdel.o \
		  ft_strdup.o \
		  ft_strequ.o \
		  ft_striter.o \
		  ft_striteri.o \
		  ft_strjoin.o \
		  ft_strlcat.o \
		  ft_strlcpy.o \
		  ft_strlen.o \
		  ft_strmap.o \
		  ft_strmapi.o \
		  ft_strncat.o \
		  ft_strncmp.o \
		  ft_strncpy.o \
		  ft_strnequ.o \
		  ft_strnew.o \
		  ft_strnstr.o \
		  ft_strrchr.o \
		  ft_strsplit.o \
		  ft_strstr.o \
		  ft_strsub.o \
		  ft_strtrim.o \
		  ft_tolower.o \
		  ft_lstnew.o \
		  ft_nmatch.o \
		  ft_toupper.o

CFLAGS	= -Wall -Wextra -Werror -g

all: $(NAME)

%.o: %.c $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS)

$(NAME): $(OBJ)
		@echo "\033[32m[build] " | tr -d '\n'
		ar -rc $(NAME) $(OBJ)
		ranlib $(NAME)
		@echo "\033[0m" | tr -d '\n'
clean:
		@echo "\033[31m[clean]  " | tr -d '\n'
		rm -f $(OBJ)
		@echo "\033[0m" | tr -d '\n'

fclean: clean
		@echo "\033[31m[clear]  " | tr -d '\n'
		@echo "[fclean] " | tr -d '\n'
		rm -f $(NAME)
		@echo "\033[0m" | tr -d '\n'

re: fclean all

.PHONY: clean fclean re libft
