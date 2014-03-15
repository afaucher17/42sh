/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slct_key_down.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinden <jlinden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/12 18:56:43 by jlinden           #+#    #+#             */
/*   Updated: 2014/03/15 14:04:37 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	slct_key_down(t_select *slct, int *pfd)
{
	(void)pfd;
	if (slct->list)
	  slct->current = (slct->current->next) ? slct->current->next : slct->list;
	draw_list(slct);
}
