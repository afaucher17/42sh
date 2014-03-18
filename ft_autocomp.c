/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_autocomp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 13:12:31 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/17 21:27:58 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include			"42sh.h"

static char			*ft_uniformize(char *dirname, char *d_name, int exec)
{
	struct stat		s_stat;
	char			*join;

	join = ft_strjoin(dirname, d_name);
	if (lstat(join, &s_stat) == -1)
	{
		free(join);
		return (NULL);
	}
	free(join);
	if ((s_stat.st_mode & S_IFMT) == S_IFDIR)
		return (ft_strjoin(d_name, "/"));
	if (!exec || (s_stat.st_mode & S_IXUSR) == S_IXUSR
			|| (s_stat.st_mode & S_IXGRP) == S_IXGRP
			|| (s_stat.st_mode & S_IXOTH) == S_IXOTH)
		return (ft_strdup(d_name));
	return (NULL);
}

static char			*ft_get_file(char *fullpath)
{
	int				i;
	int				save;

	i = 0;
	save = -1;
	while (fullpath[i])
	{
		if (fullpath[i] == '/')
			save = i;
		i++;
	}
	if (save != -1)
		return (ft_strsub(fullpath, save + 1, ft_strlen(fullpath + save + 1)));
	return (ft_strdup(fullpath));
}

static char			*ft_get_dir(char *fullpath)
{
	int				i;
	int				save;

	i = 0;
	save = -1;
	while (fullpath[i])
	{
		if (fullpath[i] == '/')
			save = i;
		i++;
	}
	if (save != -1)
		return (ft_strsub(fullpath, 0, save + 1));
	return (NULL);
}

static void			ft_path_exec(t_list **file_l, t_mlist *mlist,
									DIR *pDir, struct dirent *pDirent)
{
	char			*sub;
	char			*str;
	t_list			*env;
	char			*dirname;

	if ((env = ft_get_env("PATH", mlist->env)) == NULL)
		return ;
	sub = ft_strsub(env->content, 5, ft_strlen(env->content + 5));
	env = ft_strsplit(sub, ":");
	free(sub);
	while (env)
	{
		dirname = ft_strjoin(env->content, "/");
		if ((pDir = opendir(env->content)) == NULL)
		{
			free(dirname);
			env = env->next;
			continue ;
		}
		while ((pDirent = readdir(pDir)) != NULL)
		{
			if ((str = ft_uniformize(dirname, pDirent->d_name, 1)))
				ft_lstpushback(file_l, str, ft_strlen(str) + 1);
			free(str);
		}
		env = env->next;
		free(dirname);
	}
	ft_list_clear(&env);
}

char				*ft_autocomp(char *fullpath, int exec, t_mlist *mlist)
{
	DIR				*pDir;
	struct dirent	*pDirent;
	char			*dirname;
	t_list			*file_l;
	char			*str;

	file_l = NULL;
	pDir = NULL;
	pDirent = NULL;
	dirname = ft_get_dir(fullpath);
	if (exec && !dirname)
		ft_path_exec(&file_l, mlist, pDir, pDirent);
	else
	{
		if (!dirname)
			dirname = ft_strdup("./");
		if ((pDir = opendir(dirname)) == NULL)
		{
			free(dirname);
			return (NULL);
		}
		while ((pDirent = readdir(pDir)) != NULL)
		{
			if ((str = ft_uniformize(dirname, pDirent->d_name, exec)))
				ft_lstpushback(&file_l, str, ft_strlen(str) + 1);
			free(str);
		}
		closedir(pDir);
	}
	free(dirname);
	return (ft_complete(file_l, ft_get_file(fullpath)));
}
