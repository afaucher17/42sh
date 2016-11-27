/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkpath.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 13:49:34 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/26 20:54:13 by jlinden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		"sh42.h"

static char		*checkpath_dep(t_list *save, char *cmd)
{
	char		*res;
	char		*join;

	res = ft_strdup(save->content);
	join = ft_strjoin(res, "/");
	free(res);
	res = ft_strjoin(join, cmd);
	free(join);
	if (!access(res, F_OK))
		return (res);
	free(res);
	return (NULL);
}

static char		*checkpath_dep_loop(t_list *split, char *cmd)
{
	char		*res;

	while (split)
	{
		if ((res = checkpath_dep(split, cmd)) != NULL)
		{
			ft_list_clear(&split);
			return (res);
		}
		split = split->next;
	}
	return (NULL);
}

char			*ft_checkpath(char *cmd, char **environ)
{
	t_list		*split;
	char		*res;
	int			i;

	i = 0;
	if (!cmd)
		return (NULL);
	if (!access(cmd, F_OK))
		return (ft_strdup(cmd));
	while (environ[i] && !ft_strnequ(environ[i], "PATH=", 5))
		i++;
	if (!environ[i])
		return (ft_strdup(cmd));
	split = ft_strsplit(environ[i] + 5, ":");
	if ((res = checkpath_dep_loop(split, cmd)))
		return (res);
	else
		ft_list_clear(&split);
	return (ft_strdup(cmd));
}
