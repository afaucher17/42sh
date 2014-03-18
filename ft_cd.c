/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/07 16:51:33 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/18 18:25:47 by jlinden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include			"42sh.h"

static int			ft_chdir(char *str)
{
	struct stat	s;

	if (!access(str, F_OK))
	{
		if (!stat(str, &s) && s.st_mode & S_IFDIR && !access(str, X_OK))
		{
			chdir(str);
			return (1);
		}
		ft_putstr_fd(str, 2);
		if (!(s.st_mode & S_IFDIR))
			ft_putendl_fd(": Not a directory", 2);
		else
			ft_putendl_fd(": Permission denied.", 2);
		return (0);
	}
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": No such file or directory.", 2);
	return (0);
}

static void			ft_cdassist(t_mlist *mlist, char *path)
{
	t_list			*tmp;
	char			*sub;

	tmp = mlist->env;
	sub = NULL;
	while (tmp && !ft_strnequ(tmp->content, path, ft_strlen(path)))
		tmp = tmp->next;
	if (tmp)
		sub = ft_strsub(tmp->content, ft_strlen(path) + 1,
				ft_strlen(tmp->content) - ft_strlen(path) + 1);
	ft_chdir(sub);
	free(sub);
}

static void			ft_createoldpwd(char *pwd, t_mlist *mlist)
{
	char			*join;

	join = ft_strjoin("OLDPWD=", pwd);
	ft_lstpushback(&(mlist->env), join, ft_strlen(join));
	free(join);
}

static int			ft_cdexceptions(char **cmd, t_mlist *mlist)
{
	if (cmd && cmd[1] == 0)
	{
		ft_cdassist(mlist, "HOME");
		return (1);
	}
	if (cmd && cmd[1][0] == '-' && cmd[1][1] == '\0')
	{
		ft_cdassist(mlist, "OLDPWD");
		return (1);
	}
	return (0);
}

int					ft_cd(char **cmd, t_mlist *mlist)
{
	char			*ret;
	t_list			*tmp;
	char			*pwd;

	pwd = NULL;
	if (cmd && (ft_cdexceptions(cmd, mlist) || ft_chdir(cmd[1])))
	{
		if ((tmp = ft_get_env("PWD", mlist->env)) != NULL)
		{
			pwd = ft_strsub(tmp->content, 4, ft_strlen(tmp->content) - 4);
			free(tmp->content);
			ret = getcwd(NULL, 0);
			tmp->content = ft_strjoin("PWD=", ret);
			ft_strdel(&ret);
		}
		if ((tmp = ft_get_env("OLDPWD", mlist->env)) != NULL && pwd)
		{
			free(tmp->content);
			tmp->content = ft_strjoin("OLDPWD=", pwd);
		}
		else if (pwd)
			ft_createoldpwd(pwd, mlist);
		free(pwd);
		return (1);
	}
	return (0);
}
