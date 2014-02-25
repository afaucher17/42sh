/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cdenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/15 12:22:48 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/02/25 14:12:36 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include			"42sh.h"

static void			ft_cdassist(t_list **env, char *path)
{
	t_list			*tmp;
	char			*sub;

	tmp = *env;
	sub = NULL;
	while (tmp && !ft_strnequ(tmp->content, path, ft_strlen(path)))
		tmp = tmp->next;
	if (tmp)
		sub = ft_strsub(tmp->content, ft_strlen(path) + 1,
				ft_strlen(tmp->content) - ft_strlen(path) + 1);
	ft_chdir(sub);
	free(sub);
}

static int			ft_cdexceptions(char **cmd, t_list **env)
{
	if (cmd && cmd[1] == 0)
	{
		ft_cdassist(env, "HOME");
		return (1);
	}
	if (cmd && cmd[1][0] == '-' && cmd[1][1] == '\0')
	{
		ft_cdassist(env, "OLDPWD");
		return (1);
	}
	return (0);
}

int					ft_cdenv(char **cmd, t_list **env)
{
	char			buf[4096];
	t_list			*tmp;
	char			*pwd;

	tmp = *env;
	pwd = NULL;
	if (cmd && (ft_cdexceptions(cmd, env) || ft_chdir(cmd[1])))
	{
		while (tmp && !ft_strnequ(tmp->content, "PWD", 3))
			tmp = tmp->next;
		if (tmp)
		{
			pwd = ft_strsub(tmp->content, 4, ft_strlen(tmp->content) - 4);
			free(tmp->content);
			tmp->content = ft_strjoin("PWD=", getcwd(buf, 4096));
		}
		tmp = *env;
		while (tmp && !ft_strnequ(tmp->content, "OLDPWD", 6))
			tmp = tmp->next;
		if (tmp && pwd)
		{
			free(tmp->content);
			tmp->content = ft_strjoin("OLDPWD=", pwd);
			free(pwd);
		}
	}
	return (1);
}	
