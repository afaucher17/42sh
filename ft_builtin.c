/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 17:22:09 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/08 21:33:26 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include			"42sh.h"

static int				ft_env(char **cmd, t_list **env, t_list **fdlist)
{
	t_list				*tmp;

	(void)cmd;
	(void)fdlist;
	tmp = *env;
	while (tmp)
	{
		ft_putendl((char*)tmp->content);
		tmp = tmp->next;
	}
	return (1);
}

static int				ft_setenv(char **cmd, t_list **env, t_list **fdlist)
{
	int					i;
	t_list				*tmp;
	char				*join;

	i = 0;
	if ((i = ft_count_tab(cmd)) == 1)
		return (ft_env(cmd, env, fdlist));
	if (i > 3)
		return (!ft_putendl_fd("setenv: Too many arguments.", 2));
	join = ft_strjoinx(3, cmd[1], "=", cmd[2]);
	if ((tmp = ft_get_env(cmd[1], *env)) != NULL)
	{
		free(tmp->content);
		tmp->content = join;
		return (1);
	}
	ft_lstpushback(env, join, ft_strlen(join));
	free(join);
	return (1);
}

static int				ft_unsetenv(char **cmd, t_list **env, t_list **fdlist)
{
	t_list				*tmp;
	t_list				*cur;

	cur = *env;
	(void)fdlist;
	if (ft_count_tab(cmd) == 1)
		return (!ft_putendl_fd("unsetenv: Too few arguments.", 2));
	if ((tmp = ft_get_env(cmd[1], *env)) == NULL)
		return (1);
	while (cur && cur->next && cur->next != tmp)
		cur = cur->next;
	if (*env && tmp == *env)
		*env = (*env)->next;
	else if (cur && tmp)
		cur->next = tmp->next;
	free(tmp->content);
	free(tmp);
	return (1);
}

static int				ft_exit(char **cmd, t_list **env, t_list **fdlist)
{
	ft_close_fdlist(fdlist);
	ft_clear_tab(cmd);
	ft_list_clear(env);
	exit(EXIT_SUCCESS);
	return (1);
}

int						ft_builtin(t_list **env, t_list **fdlist, t_node *tree)
{
	int					i;
	int					ret;
	char				**cmd;
	static t_builtin	builtin[6] = {
		{"exit", ft_exit}, {"env", ft_env}, {"setenv", ft_setenv},
		{"unsetenv", ft_unsetenv}, {"cd", ft_cd}, {"echo", ft_echo}};

	cmd = ft_arg_handler(tree, ft_strdup(tree->data));
	if (env && ft_red_handler(tree->left, fdlist))
	{
		i = 0;
		while (i < 6)
		{
			if (ft_strequ(cmd[0], builtin[i].cmd))
			{
				ret = builtin[i].f(cmd, env, fdlist);
				ft_close_fdlist(fdlist);
				ft_clear_tab(cmd);
				dup2(ft_reset_std()[0], 0);
				dup2(ft_reset_std()[1], 1);
				return (ret);
			}
			i++;
		}
	}
	return (0);
}
