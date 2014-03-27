/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 18:19:05 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/27 15:31:35 by jlinden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static char		*ft_wait_finish(char *str, t_mlist *mlist)
{
	char		*buf;
	char		*complete;

	ft_putstr("> ");
	ft_set_term();
	buf = ft_read_keys(ft_log_to_dlist(), 1, mlist);
	ft_reset_term();
	ft_bzero(g_cmd, BUFF_SIZE);
	g_idx = 0;
	complete = ft_strjoin(str, buf);
	free(str);
	free(buf);
	return (complete);
}

static int		ft_son_init(int spec[5], int *count)
{
	int		i;

	i = 0;
	*count = -1;
	while (i < 5)
	{
		spec[i] = 0;
		i++;
	}
	return (1);
}

char			*ft_son(char *cmd, t_mlist *mlist)
{
	int			i;
	int			spec[5];

	ft_son_init(spec, &i);
	while (cmd[++i])
	{
		if (cmd[i] == '\\' && (i = i + 2))
			continue ;
		spec[0] ^= (cmd[i] == '\"' && !spec[1]);
		spec[1] ^= (cmd[i] == '\'' && !spec[0]);
		spec[2] ^= (cmd[i] == '`' && !spec[1]);
		if (!spec[0] && !spec[1])
		{
			spec[3] -= (cmd[i] == ')');
			spec[3] += (cmd[i] == '(');
			spec[4] -= (cmd[i] == ']');
			spec[4] += (cmd[i] == '[');
		}
	}
	if (spec[0] || spec[1] || spec[2] || spec[3] > 0 || spec[4] > 0)
	{
		cmd = ft_wait_finish(cmd, mlist);
		return (ft_son(cmd, mlist));
	}
	return (cmd);
}

static char		*ft_anal_father(int pfd[2])
{
	int		len;
	char	buf[BUFF_SIZE + 1];

	signal(SIGINT, ft_sighand2);
	close(pfd[1]);
	dup2(pfd[0], 0);
	while ((len = read(0, buf, BUFF_SIZE)) > 0)
		buf[len] = '\0';
	wait(NULL);
	close(pfd[0]);
	dup2((ft_reset_std())[0], 0);
	if (buf[0] == '\0')
		return (NULL);
	return (ft_strdup(buf));
}

char			*ft_analyser(char *cmd, t_mlist *mlist)
{
	int			pid;
	char		*res;
	char		buf[BUFF_SIZE];
	int			pfd[2];

	ft_bzero(buf, BUFF_SIZE);
	pipe(pfd);
	if ((pid = fork()) == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(pfd[0]);
		res = ft_son(cmd, mlist);
		dup2(pfd[1], 1);
		ft_putstr(res);
		free(res);
		exit(EXIT_SUCCESS);
	}
	else
		return (ft_anal_father(pfd));
	return (NULL);
}
