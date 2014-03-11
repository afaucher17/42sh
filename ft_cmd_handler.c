/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/15 14:46:12 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/11 16:25:58 by tdieumeg         ###   ########.fr       */
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

static void		ft_son(t_fdlist *fdlist, char **charenv, t_node *tree, int builtin)
{
	t_list		*env;
	int			ret;
	char		**cmd;

	env = ft_duplicate(charenv);
	cmd = NULL;
	signal(SIGINT, SIG_DFL);
	if (!builtin)
		cmd = ft_arg_handler(tree, ft_checkpath(tree->data, charenv));
	if (!cmd && !builtin)
		exit(EXIT_SUCCESS);
	if (!builtin)
	{
		execve(cmd[0], cmd, charenv);
		ft_notfnd(cmd[0]);
	}
	else
	{
		ft_clear_tab(charenv);
		ret = ft_builtin(&env, &fdlist, tree);
		ft_list_clear(&env);
		ft_clear_tab(cmd);
		exit(ret);
	}
	exit(EXIT_FAILURE);
}

static int		ft_father(int pid, char **charenv, int **tpfd)
{
	int			waitvar;

	waitvar = 0;
	signal(SIGINT, ft_sighand2);
	signal(SIGUSR1, ft_sighandler);
	ft_pfd_close(tpfd[0]);
	if (!tpfd[1])
		waitpid(pid, &waitvar, 0);
	ft_clear_tab(charenv);
	if (WIFSIGNALED(waitvar))
		return (0);
	return (!WEXITSTATUS(waitvar));	
}

int				ft_cmd_handler(t_node *tree, t_list **env, int **tpfd, t_fdlist *fdlist)
{
	pid_t		pid;
	char		**charenv;
	int			builtin;

	charenv = ft_tochar(*env);
	if ((builtin = ft_is_builtin(tree->data)) && !tpfd[0] && !tpfd[1])
	{
		ft_clear_tab(charenv);
		return (ft_builtin(env, &fdlist, tree));
	}
	if ((pid = fork()) < 0)
		return (0);
	if (pid == 0)
	{
		ft_pfd_manage(tpfd[0], tpfd[1]);
		if (!ft_red_handler(tree->left, fdlist, 1))
			exit(EXIT_FAILURE);
		ft_son(fdlist, charenv, tree, builtin);
	}
	else
	{
		ft_red_handler(tree->left, fdlist, 0);
		return (ft_father(pid, charenv, tpfd));
	}
	return (0);
}
