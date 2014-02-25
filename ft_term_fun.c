/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term_fun.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/04 14:15:38 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/02/06 15:37:14 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include			"42sh.h"

int					ft_set_term(void)
{
	char			*term_name;
	struct termios	term;

	if (!(term_name = getenv("TERM")))
		return (ft_putendl_fd("ft_select: restore env before execution", 2));
	tgetent(NULL, term_name);
	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &term);
	return (1);
}

int					ft_reset_term(void)
{
	struct termios	term;

	tputs(tgetstr("ei", NULL), 1, ft_putchar_tc);
	tcgetattr(0, &term);
	term.c_lflag |= (ICANON | ECHO);
	tcsetattr(0, 0, &term);
	return (1);
}
