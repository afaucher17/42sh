/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 17:22:09 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/26 17:00:45 by jlinden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include			"sh42.h"

static int				ft_env(char **cmd, t_mlist *mlist)
{
	t_list				*tmp;

	(void)cmd;
	tmp = mlist->env;
	while (tmp)
	{
		ft_putendl((char*)tmp->content);
		tmp = tmp->next;
	}
	return (1);
}

static int				ft_setenv(char **cmd, t_mlist *mlist)
{
	int					i;
	t_list				*tmp;
	char				*bis;
	char				*join;

	i = 0;
	if ((i = ft_count_tab(cmd)) == 1)
		return (ft_env(cmd, mlist));
	if (i > 3)
		return (!ft_putendl_fd("setenv: Too many arguments.", 2));
	join = ft_strjoin(cmd[1], "=");
	bis = join;
	free(join);
	join = ft_strjoin(bis, cmd[2]);
	free(bis);
	if ((tmp = ft_get_env(cmd[1], mlist->env)) != NULL)
	{
		free(tmp->content);
		tmp->content = join;
		return (1);
	}
	ft_lstpushback(&(mlist->env), join, ft_strlen(join) + 1);
	free(join);
	return (1);
}

static int				ft_unsetenv(char **cmd, t_mlist *mlist)
{
	t_list				*tmp;
	t_list				*cur;

	cur = mlist->env;
	if (ft_count_tab(cmd) == 1)
		return (!ft_putendl_fd("unsetenv: Too few arguments.", 2));
	if ((tmp = ft_get_env(cmd[1], mlist->env)) == NULL)
		return (1);
	while (cur && cur->next && cur->next != tmp)
		cur = cur->next;
	if (mlist->env && tmp == mlist->env)
		mlist->env = mlist->env->next;
	else if (cur && tmp)
		cur->next = tmp->next;
	free(tmp->content);
	free(tmp);
	return (1);
}

static int				ft_exit(char **cmd, t_mlist *mlist)
{
	(void)mlist;
	ft_clear_tab(cmd);
	ft_list_clear(&(mlist->env));
	ft_close_fdlist(&(mlist->fdlist));
	free(mlist);
	mlist = NULL;
	exit(EXIT_SUCCESS);
	return (1);
}

int						ft_builtin(t_mlist *mlist, t_node *tree)
{
	int					i;
	int					ret;
	char				**cmd;
	static t_builtin	builtin[6] =

	{
	{"exit", ft_exit}, {"env", ft_env}, {"setenv", ft_setenv},
	{"unsetenv", ft_unsetenv}, {"cd", ft_cd}, {"echo", ft_echo}
	};
	cmd = ft_arg_handler(tree, ft_strdup(tree->data));
	if (mlist->env && ft_red_handler(tree->left, mlist, 1))
	{
		i = -1;
		while (++i < 6)
			if (ft_strequ(cmd[0], builtin[i].cmd))
			{
				ret = builtin[i].f(cmd, mlist);
				ft_clear_tab(cmd);
				dup2(ft_reset_std()[0], 0);
				dup2(ft_reset_std()[1], 1);
				return (ret);
			}
	}
	return (0);
}
