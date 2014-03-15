/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slct_key_up.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinden <jlinden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/12 19:06:05 by jlinden           #+#    #+#             */
/*   Updated: 2014/03/15 14:05:00 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	slct_key_up(t_select *slct, int *pfd)
{
	t_lst	*cursor;

	(void)pfd;
	if ((cursor = slct->list))
	{
		if (!slct->current->prev)
		{
			while (cursor->next)
				cursor = cursor->next;
			slct->current = cursor;
		}
		else
			slct->current = slct->current->prev;
	}
	draw_list(slct);
}
