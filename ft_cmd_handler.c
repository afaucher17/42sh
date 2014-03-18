/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/15 14:46:12 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/17 20:47:13 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		"42sh.h"

char			**ft_arg_handler(t_node *tree, char *cmd)
{
	char		**com;
	t_node		*save;
	int			i;

	if (!cmd)
		return (NULL);
	save = tree;
	i = 0;
	while ((save = save->right) != NULL)
		i++;
	com = (char**)malloc(sizeof(char*) * (i + 2));
	i = 1;
	com[0] = ft_strdup(cmd);
	free(cmd);
	while ((tree = tree->right) != NULL)
	{
		com[i] = ft_strdup(tree->data);
		i++;
	}
	com[i] = NULL;
	return (com);
}

static void		ft_son(t_mlist *mlist, char **charenv, t_node *tree, int builtin)
{
	int			ret;
	char		**cmd;

	cmd = NULL;
	signal(SIGINT, SIG_DFL);
	if (!builtin)
		cmd = ft_arg_handler(tree, ft_checkpath(tree->data, charenv));
	if (!cmd && !builtin)
		exit(EXIT_SUCCESS);
	if (!builtin && ft_red_handler(tree->left, mlist, 1))
	{
		execve(cmd[0], cmd, charenv);
		ft_notfnd(cmd[0]);
	}
	else if (builtin)
	{
		ft_clear_tab(charenv);
		ret = ft_builtin(mlist, tree);
		ft_list_clear(&(mlist->env));
		ft_clear_tab(cmd);
		exit(ret);
	}
	exit(EXIT_FAILURE);
}

static int		ft_father(int pid, char **charenv, int **tpfd)
{
	int			waitvar;

	waitvar = 0;
	(void)pid;
	signal(SIGINT, ft_sighand2);
	signal(SIGUSR1, ft_sighandler);
	ft_pfd_close(tpfd[0]);
	if (!tpfd[1])
		while (waitpid(-1, &waitvar, 0) >= 0)
			;
	ft_clear_tab(charenv);
	if (WIFSIGNALED(waitvar))
		return (0);
	return (!WEXITSTATUS(waitvar));	
}

int				ft_cmd_handler(t_node *tree, t_mlist *mlist, int **tpfd)
{
	pid_t		pid;
	char		**charenv;
	int			builtin;

	charenv = ft_tochar(mlist->env);
	if ((builtin = ft_is_builtin(tree->data)) && !tpfd[0] && !tpfd[1])
	{
		ft_clear_tab(charenv);
		return (ft_builtin(mlist, tree));
	}
	if ((pid = fork()) < 0)
		return (0);
	if (pid == 0)
	{
		ft_pfd_manage(tpfd[0], tpfd[1]);
		ft_son(mlist, charenv, tree, builtin);
	}
	else
	{
		ft_red_handler(tree->left, mlist, 0);
		return (ft_father(pid, charenv, tpfd));
	}
	return (0);
}
