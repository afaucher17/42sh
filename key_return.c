/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_return.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinden <jlinden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 18:40:16 by jlinden           #+#    #+#             */
/*   Updated: 2014/03/26 18:40:18 by jlinden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_select.h"
#include "libft.h"

void	slct_key_return(t_select *g_slct, int *pfd)
{
	t_lst	*list;

	list = g_slct->current;
	dup2(pfd[1], 1);
	if (!list)
		proper_exit(EXIT_SUCCESS);
	write(1, list->label, list->length);
	proper_exit(EXIT_SUCCESS);
}
