# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/27 14:53:18 by tdieumeg          #+#    #+#              #
#    Updated: 2014/03/27 15:02:15 by jlinden          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 42sh

CC		= gcc

DEPS	= sh42.h

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
		  ft_cd.o \
		  ft_cd_fun.o \
		  ft_echo.o \
		  ft_echo_utf.o \
		  ft_checkpath.o \
		  ft_envman.o \
		  ft_notfnd.o \
		  ft_sighandler.o \
		  ft_token_handler.o \
		  ft_pfd_manage.o \
		  ft_cmd_handler.o \
		  ft_red_handler.o \
		  ft_get_bquote.o \
		  ft_red_open.o \
		  ft_term_fun.o \
		  ft_read_keys.o \
		  ft_keys_fun.o \
		  ft_keys_fun2.o \
		  ft_keys_fun3.o \
		  ft_keys_fun4.o \
		  ft_putchar_tc.o \
		  ft_log.o \
		  ft_error.o \
		  ft_utility_fun.o \
		  ft_autocomp.o \
		  ft_autocomp_fun.o \
		  ft_select.o \
		  ft_slct_dep.o \
		  ft_slct_convert.o \
		  draw_list.o \
		  key_down.o \
		  key_up.o \
		  key_escape.o \
		  key_return.o \
		  key_right.o \
		  key_left.o \
		  keys.o \
		  list.o \
		  move.o \
		  signals.o \
		  write.o \
		  get_next_line.o

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
