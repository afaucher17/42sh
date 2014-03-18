/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 18:19:05 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/18 19:01:01 by jlinden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

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

char			*ft_son(char *cmd, t_mlist *mlist)
{
	int			i;
	int			special[6] = {0, 0, 0, 0, 0, 0};

	i = 0;
	while (cmd[i])
	{
		special[0] ^= (cmd[i] == '\"' && !special[1]);
		special[1] ^= (cmd[i] == '\'' && !special[0]);
		special[2] ^= (cmd[i] == '`' && !special[1]);
		if (!special[0] && !special[1])
		{
			special[3] -= (cmd[i] == ')');
			special[3] += (cmd[i] == '(');
			special[4] -= (cmd[i] == ']');
			special[4] += (cmd[i] == '[');
		}
		i++;
	}
	if (special[0] || special[1] || special[2]
		|| special[3] > 0 || special[4] > 0)
	{
		cmd = ft_wait_finish(cmd, mlist);
		return (ft_son(cmd, mlist));
	}
	return (cmd);
}

char			*ft_analyser(char *cmd, t_mlist *mlist)
{
	int			pid;
	char		*res;
	char		buf[BUFF_SIZE];
	int			len;
	int			pfd[2];

	ft_bzero(buf, BUFF_SIZE);
	pipe(pfd);
	pid = fork();
	if (pid == 0)
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
	{
		signal(SIGINT, ft_sighand2);
		close(pfd[1]);
		dup2(pfd[0], 0);
		while ((len = read(0, buf, BUFF_SIZE - 1)) > 0)
			buf[len] = '\0';
		wait(NULL);
		close(pfd[0]);
		dup2((ft_reset_std())[0], 0);
		if (buf[0] == '\0')
			return (NULL);
		return (ft_strdup(buf));
	}
	return (NULL);
}
