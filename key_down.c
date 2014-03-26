/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_down.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinden <jlinden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 18:37:43 by jlinden           #+#    #+#             */
/*   Updated: 2014/03/26 18:38:13 by jlinden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	slct_key_down(t_select *g_slct, int *pfd)
{
	(void)pfd;
	if (g_slct->list)
	{
		if (g_slct->current->next)
			g_slct->current = g_slct->current->next;
		else
			g_slct->current = g_slct->list;
	}
	draw_list(g_slct);
}
