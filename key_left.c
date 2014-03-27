/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_left.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinden <jlinden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 18:39:35 by jlinden           #+#    #+#             */
/*   Updated: 2014/03/26 18:39:52 by jlinden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "ft_select.h"

static t_lst	*left_overflow(t_select *g_slct)
{
	t_lst	*cursor;
	t_lst	*save;
	int		i;
	int		max_iter;

	save = NULL;
	max_iter = (g_slct->size / ft_get_winsz()->ws_row) + 1;
	cursor = g_slct->current;
	while (max_iter--)
	{
		i = ft_get_winsz()->ws_row;
		while (cursor && i)
		{
			if (!cursor->next && i == 1)
				return (cursor);
			cursor = cursor->next;
			i--;
		}
		if (cursor)
			save = cursor->prev;
	}
	if (!save && !cursor)
		save = g_slct->current->prev;
	return (save);
}

void			slct_key_left(t_select *g_slct, int *pfd)
{
	t_lst	*cursor;
	int		i;

	(void)pfd;
	if ((cursor = g_slct->current) == g_slct->list)
		return ;
	i = ft_get_winsz()->ws_row;
	if (cursor)
	{
		while (cursor && i--)
			cursor = cursor->prev;
		if (cursor)
			g_slct->current = cursor;
		else
		{
			g_slct->current = left_overflow(g_slct);
		}
		draw_list(g_slct);
	}
}
