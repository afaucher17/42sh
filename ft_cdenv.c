/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cdenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/15 12:22:48 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/02/19 12:06:27 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include			"42sh.h"

static int			ft_cdexceptions(char **cmd, t_list **env)
{
	t_list			*tmp;

	tmp = *env;
	if (cmd && cmd[1] == 0)
	{
		while (tmp && !ft_strnequ(tmp->content, "HOME", 4))
			tmp = tmp->next;
		if (tmp)
			cmd[1] = ft_strsub(tmp->content, 5, ft_strlen(tmp->content) - 5);
	}
	if (cmd && cmd[1][0] == '-' && cmd[1][1] == '\0')
	{
		while (tmp && !ft_strnequ(tmp->content, "OLDPWD", 6))
			tmp = tmp->next;
		if (tmp)
			cmd[1] = ft_strsub(tmp->content, 7, ft_strlen(tmp->content) - 7);
	}
	return (1);
}

int					ft_cdenv(char **cmd, t_list **env)
{
	char			*buf;
	t_list			*tmp;
	char			*pwd;

	buf = (char*)malloc(sizeof(char) * 4096);
	tmp = *env;
	pwd = '\0';
	ft_cdexceptions(cmd, env);
	if (cmd && ft_chdir(cmd[1]))
	{
		while (tmp && !ft_strnequ(tmp->content, "PWD", 3))
			tmp = tmp->next;
		if (tmp)
		{
			pwd = ft_strsub(tmp->content, 4, ft_strlen(tmp->content) - 4);
			tmp->content = ft_strjoin("PWD=", getcwd(buf, 4096));
		}
		free(buf);
		tmp = *env;
		while (tmp && !ft_strnequ(tmp->content, "OLDPWD", 6))
			tmp = tmp->next;
		if (tmp && pwd)
			tmp->content = ft_strjoin("OLDPWD=", pwd);
	}
	return (1);
}
