/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 17:22:09 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/02 18:50:27 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include			"42sh.h"

static int			ft_printenv(t_list *env)
{
	t_list			*tmp;

	tmp = env;
	while (tmp)
	{
		ft_putendl((char*)tmp->content);
		tmp = tmp->next;
	}
	return (1);
}

static int			builtin_dep(char **cmd, t_list *tmp)
{
	if ((ft_strnequ(cmd[1], tmp->content, ft_strlen(cmd[1])))
	&& (ft_strlen(tmp->content) >= ft_strlen(cmd[1]) + 1)
	&& (((char*)tmp->content)[ft_strlen(cmd[1])] == '='))
		return (1);
	return (0);
}

static int			ft_addenv(char **cmd, t_list **env)
{
	int				i[1] = {0};
	t_list			*tmp;
	char			*join;
	char			*join2;

	tmp = *env;
	while (cmd[i[0]])
		i[0]++;
	if (i[0] > 3)
		return (ft_putendl_fd("setenv: Too many arguments.", 2));
	join2 = ft_strjoin(cmd[1], "=");
	join = ft_strjoin(join2, cmd[2]);
	free(join2);
	while (tmp)
	{
		if (builtin_dep(cmd, tmp))
		{
			free(tmp->content);
			return ((tmp->content = join) != NULL);
		}
		tmp = tmp->next;
	}
	ft_lstpushback(env, join, ft_strlen(join));
	free(join);
	return (1);
}

static int			ft_remenv(char **cmd, t_list **env)
{
	t_list			*prev;
	t_list			*cur;

	prev = *env;
	cur = *env;
	while (cur)
	{
		if (builtin_dep(cmd, cur))
		{
			if (cur == *env)
				*env = (*env)->next;
			prev->next = cur->next;
			free(cur);
			return (1);
		}
		if (cur == *env)
			cur = cur->next;
		else
		{
			prev = prev->next;
			cur = cur->next;
		}
	}
	return (1);
}

int					ft_builtin(char **cmd, t_list **env, t_node *tree,
									t_list **fdlist)
{
	(void)tree;
	(void)fdlist;
	if (env)
	{
		if (ft_strequ(cmd[0], "exit"))
		{
			ft_list_clear(env);
			ft_reset_term();
			exit(EXIT_SUCCESS);
		}
		if (ft_strequ(cmd[0], "env"))
			return (ft_printenv(*env));
		if (ft_strequ(cmd[0], "setenv") && !cmd[1])
			return (ft_printenv(*env));
		if (ft_strequ(cmd[0], "setenv") && cmd[1])
			return (ft_addenv(cmd, env));
		if (ft_strequ(cmd[0], "unsetenv") && !cmd[1])
			return (ft_putendl_fd("unsetenv: Too few arguments.", 2));
		if (ft_strequ(cmd[0], "unsetenv") && cmd[1])
			return (ft_remenv(cmd, env));
		if (ft_strequ(cmd[0], "cd"))
			return (ft_cdenv(cmd, env));
		if (ft_strequ(cmd[0], "echo"))
			return (ft_echo(cmd, env, tree, fdlist));
	}
	return (0);
}
