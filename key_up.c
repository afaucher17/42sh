/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_up.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinden <jlinden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 18:40:58 by jlinden           #+#    #+#             */
/*   Updated: 2014/03/26 18:40:59 by jlinden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	slct_key_up(t_select *g_slct, int *pfd)
{
	t_lst	*cursor;

	(void)pfd;
	if ((cursor = g_slct->list))
	{
		if (!g_slct->current->prev)
		{
			while (cursor->next)
				cursor = cursor->next;
			g_slct->current = cursor;
		}
		else
			g_slct->current = g_slct->current->prev;
	}
	draw_list(g_slct);
}
