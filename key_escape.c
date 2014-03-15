/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slct_key_escape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinden <jlinden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/12 19:00:50 by jlinden           #+#    #+#             */
/*   Updated: 2014/03/15 15:02:43 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
#include "ft_select.h"

void	slct_key_escape(t_select *slct, int *pfd)
{
	(void)slct;
	dup2(pfd[1], 1);
	write(1, "", 1);
	proper_exit(EXIT_SUCCESS);
}
