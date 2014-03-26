/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinden <jlinden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/07 08:45:39 by jlinden           #+#    #+#             */
/*   Updated: 2014/03/15 14:16:50 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <term.h>
#include "ft_select.h"
#include "libft.h"

int		tputs_putc(int c)
{
	write(g_slct->fd, &c, 1);
	return (1);
}

void	put_flag(const char *flag)
{
	tputs(tgetstr((char *)flag, NULL), 1, tputs_putc);
}

void	putstr_flag(char *str, const int style)
{
	if (style & UNDERLINE)
		put_flag(UNDERLINE_S);
	if (style & REV_VIDEO)
		put_flag(REV_VIDEO_S);
	ft_putstr_fd(str, g_slct->fd);
	if (style & UNDERLINE)
		put_flag(UNDERLINE_E);
	if (style & REV_VIDEO)
		put_flag(REV_VIDEO_E);
}

void	put_error(const char *str)
{
	ft_putendl_fd(str, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
