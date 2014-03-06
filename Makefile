# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/27 14:53:18 by tdieumeg          #+#    #+#              #
#    Updated: 2014/03/05 16:51:29 by tdieumeg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 42sh

CC		= /usr/bin/cc

DEPS	= 42sh.h

OBJ		= main.o \
		  ft_analyser.o \
		  ft_lexer.o \
		  ft_lexer_fun.o \
		  ft_parser.o \
		  ft_parse_fun.o \
		  ft_token.o \
		  ft_node.o \
		  ft_builtin.o \
		  ft_is_builtin.o \
		  ft_cdenv.o \
		  ft_echo.o \
		  ft_chdir.o \
		  ft_checkpath.o \
		  ft_envman.o \
		  ft_notfnd.o \
		  ft_sighandler.o \
		  ft_token_handler.o \
		  ft_cmd_handler.o \
		  ft_red_handler.o \
		  ft_get_bquote.o \
		  ft_red_open.o \
		  ft_term_fun.o \
		  ft_read_keys.o \
		  ft_keys_fun.o \
		  ft_keys_fun2.o \
		  ft_keys_fun3.o \
		  ft_putchar_tc.o \
		  ft_log.o \
		  ft_error.o \
		  ft_utility_fun.o 

CFLAGS	= -Wall -Wextra -Werror -g

HEADERS	= -I. -Ilibft/

LIB		= -L libft/ -lft -ltermcap

all: $(NAME)

%.o: %.c $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS) $(HEADERS)

libft:
	@$(MAKE) -C libft/

$(NAME): $(OBJ)
	@$(MAKE) -C libft/
	$(CC) -o $(NAME) $^ $(CFLAGS) $(LIB)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re libft
