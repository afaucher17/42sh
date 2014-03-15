/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slct_key_right.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinden <jlinden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/12 19:04:10 by jlinden           #+#    #+#             */
/*   Updated: 2014/03/15 14:06:22 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
#include "ft_select.h"

static t_lst	*right_overflow(t_select *slct)
{
	t_lst	*cursor;
	t_lst	*save;
	int		i;
	int		max_iter;

	save = NULL;
	max_iter = (slct->size / ft_get_winsz()->ws_row);
	cursor = slct->current;
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
		save = (slct->current->next) ? slct->current->next : slct->list;
	return (save);
}

void			slct_key_right(t_select *slct, int *pfd)
{
	t_lst	*cursor;
	int		i;

	(void)pfd;
	i = ft_get_winsz()->ws_row;
	if ((cursor = slct->current))
	{
		while (cursor && i--)
			cursor = cursor->next;
		if (cursor)
			slct->current = cursor;
		else
		{
			slct->current = right_overflow(slct);
		}
		draw_list(slct);
	}
}
