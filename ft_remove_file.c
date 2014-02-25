/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/25 20:07:05 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/02/04 14:11:25 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include			"42sh.h"

void				ft_remove_file(char *filename)
{
	char			**rem;
	pid_t			pid;

	rem = (char**)malloc(sizeof(char*) * 3);
	rem[0] = "/bin/rm";
	rem[1] = filename;
	rem[2] = NULL;
	if ((pid = fork()) < 0)
		return ;
	if (pid == 0)
		execve(rem[0], rem, NULL);
	else
		wait(&pid);
}
