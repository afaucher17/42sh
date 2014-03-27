/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_slct_dep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinden <jlinden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/04 14:44:12 by jlinden           #+#    #+#             */
/*   Updated: 2014/03/27 14:13:05 by jlinden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <term.h>
#include <sys/ioctl.h>
#include "ft_select.h"
#include "libft.h"

t_select	*g_slct;

void		load_term(void)
{
	put_flag(TERM_INIT);
	put_flag(DELETE_LINE);
	put_flag(HIDE_CURSOR);
}

void		restore_term(void)
{
	put_flag(SHOW_CURSOR);
	put_flag(TERM_END);
}

void		proper_exit(int ret)
{
	restore_term();
	close(g_slct->fd);
	lst_free(&(g_slct->list));
	free(g_slct);
	exit(ret);
}

void		init_g_slct(t_select *obj, t_list *file_l)
{
	int		size;

	size = 0;
	obj->list = ft_convert(file_l, &size);
	obj->current = obj->list;
	obj->fd = open(ttyname(0), O_WRONLY);
	obj->margin = get_margin(obj);
	obj->size = size;
}

int			ft_slct_dep(t_list *file_l, int *pfd)
{
	int		buf;

	load_signals();
	g_slct = (t_select *)malloc(sizeof(t_select));
	init_g_slct(g_slct, file_l);
	load_term();
	draw_list(g_slct);
	while (42)
	{
		buf = 0;
		read(STDIN_FILENO, &buf, 4);
		key_dispatch(g_slct, buf, pfd);
	}
	restore_term();
	return (0);
}
