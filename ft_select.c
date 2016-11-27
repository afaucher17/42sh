/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/13 15:06:34 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/27 11:11:14 by jlinden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include			"sh42.h"
#include			"ft_select.h"

static char			*ft_father(int *pfd)
{
	char			*line;
	char			*tmp;
	char			*ret;

	tmp = NULL;
	ret = NULL;
	close(pfd[1]);
	dup2(pfd[0], 0);
	signal(SIGINT, SIG_IGN);
	while (get_next_line(0, &line) > 0)
	{
		tmp = ret;
		ret = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
	}
	wait(NULL);
	close(pfd[0]);
	dup2((ft_reset_std())[0], 0);
	return (ret);
}

char				*ft_select(t_list *file_l, char *filename)
{
	int				pid;
	int				pfd[2];
	char			*ret;
	char			*tmp;

	ret = NULL;
	tmp = NULL;
	pipe(pfd);
	if ((pid = fork()) == 0)
	{
		load_signals();
		close(pfd[0]);
		ft_slct_dep(file_l, pfd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		tmp = ft_father(pfd);
		signal(SIGINT, ft_sighandler);
	}
	ft_list_clear(&file_l);
	ret = (tmp) ? ft_strdup(tmp + ft_strlen(filename)) : ret;
	free(tmp);
	free(filename);
	return (ret);
}
