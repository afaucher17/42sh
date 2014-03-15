/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slct_key_left.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinden <jlinden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/12 19:01:36 by jlinden           #+#    #+#             */
/*   Updated: 2014/03/15 14:09:19 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
#include "ft_select.h"

static t_lst	*left_overflow(t_select *slct)
{
	t_lst	*cursor;
	t_lst	*save;
	int		i;
	int		max_iter;

	save = NULL;
	max_iter = (slct->size / ft_get_winsz()->ws_row) + 1;
	cursor = slct->current;
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
		save = slct->current->prev;
	return (save);
}
void			slct_key_left(t_select *slct, int *pfd)
{
	t_lst	*cursor;
	int		i;

	(void)pfd;
	if ((cursor = slct->current) == slct->list)
		return ;
	i = ft_get_winsz()->ws_row;
	if (cursor)
	{
		while (cursor && i--)
			cursor = cursor->prev;
		if (cursor)
			slct->current = cursor;
		else
		{
			slct->current = left_overflow(slct);
		}
		draw_list(slct);
	}
}
