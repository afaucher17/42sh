/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinden <jlinden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/09 11:26:48 by jlinden           #+#    #+#             */
/*   Updated: 2014/03/15 12:27:21 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/ioctl.h>
#include <termios.h>
#include "ft_select.h"

static void	signal_handler(int sig)
{
	if (sig == SIGINT || sig == SIGQUIT || sig == SIGTERM)
		proper_exit(EXIT_FAILURE);
	else if (sig == SIGWINCH)
		draw_list(slct);
}

void	load_signals(void)
{
	signal(SIGTERM, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGWINCH, signal_handler);
}
