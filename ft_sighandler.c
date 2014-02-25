/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sighandler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 16:29:19 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/02/24 18:30:05 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include			"42sh.h"

void				ft_sighandler(int signal)
{
	if (signal == SIGINT)
	{
		ft_end(NULL, 0);
		tputs(tgetstr("do", NULL), 1, ft_putchar_tc);
		ft_bzero(g_cmd, BUFF_SIZE);
		g_idx = 0;
		ft_putstr(PROMPT);
	}
}

void				ft_sighand2(int signal)
{
	if (signal == SIGINT)
		ft_putendl("");
}
