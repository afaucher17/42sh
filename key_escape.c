/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_escape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinden <jlinden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 18:38:53 by jlinden           #+#    #+#             */
/*   Updated: 2014/03/26 18:38:54 by jlinden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
#include "ft_select.h"

void	slct_key_escape(t_select *g_slct, int *pfd)
{
	(void)g_slct;
	dup2(pfd[1], 1);
	write(1, "", 1);
	proper_exit(EXIT_SUCCESS);
}
