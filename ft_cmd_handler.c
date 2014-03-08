/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/15 14:46:12 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/08 21:33:12 by afaucher         ###   ########.fr       */
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

static void		ft_son(char **cmd, char **charenv, t_node *tree,
						t_list **fdlist)
{
	if (!ft_red_handler(tree->left, fdlist))
		exit(EXIT_FAILURE);
	signal(SIGINT, SIG_DFL);
	if (!cmd)
		exit(EXIT_SUCCESS);
	execve(cmd[0], cmd, charenv);
	ft_notfnd(cmd[0]);
	exit(EXIT_FAILURE);
}

static int		ft_father(int *pfd, int pid, char ***charenv, int *pfd2)
{
	int			waitvar;

	waitvar = 0;
	signal(SIGINT, ft_sighand2);
	signal(SIGUSR1, ft_sighandler);
	ft_pfd_close(pfd);
	if (!pfd2)
		waitpid(pid, &waitvar, 0);
	ft_clear_tab(*charenv);
	if (WIFSIGNALED(waitvar))
		return (0);
	return (!WEXITSTATUS(waitvar));	
}

int				ft_cmd_handler(t_node *tree, t_list **env, int *pfd, int *pfd2)
{
	pid_t		pid;
	char		**cmd;
	char		**charenv;
	t_list		*fdlist;

	fdlist = NULL;
	charenv = ft_tochar(*env);
	if (!ft_is_builtin(tree->data))
		cmd = ft_arg_handler(tree, ft_checkpath(tree->data, charenv));
	else
	{
		ft_clear_tab(charenv);
		return (ft_builtin(env, &fdlist, tree));
	}
	if ((pid = fork()) < 0)
		return (0);
	if (pid == 0)
	{
		ft_pfd_manage(pfd, pfd2);
		ft_son(cmd, charenv, tree, &fdlist);
	}
	else
		return (ft_father(pfd, pid, &charenv, pfd2));
	return (0);
}
