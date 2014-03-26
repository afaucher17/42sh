/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_right.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinden <jlinden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 18:40:38 by jlinden           #+#    #+#             */
/*   Updated: 2014/03/26 18:40:38 by jlinden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
#include "ft_select.h"

static t_lst	*right_overflow(t_select *g_slct)
{
	t_lst	*cursor;
	t_lst	*save;
	int		i;
	int		max_iter;

	save = NULL;
	max_iter = (g_slct->size / ft_get_winsz()->ws_row);
	cursor = g_slct->current;
	while (max_iter--)
	{
		i = ft_get_winsz()->ws_row;
		while (cursor && i)
		{
			cursor = cursor->prev;
			i--;
		}
		if (cursor)
			save = cursor->next;
	}
	if (!save)
		save = (g_slct->current->next) ? g_slct->current->next : g_slct->list;
	return (save);
}

void			slct_key_right(t_select *g_slct, int *pfd)
{
	t_lst	*cursor;
	int		i;

	(void)pfd;
	i = ft_get_winsz()->ws_row;
	if ((cursor = g_slct->current))
	{
		while (cursor && i--)
			cursor = cursor->next;
		if (cursor)
			g_slct->current = cursor;
		else
		{
			g_slct->current = right_overflow(g_slct);
		}
		draw_list(g_slct);
	}
}
