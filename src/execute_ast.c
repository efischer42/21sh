/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:31:22 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/10 17:37:56 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

#define ASTERROR 125

int			execute_pipeline(t_ast *node, int foreground)
{
	return (execute_job(node->content, foreground));
}

int			execute_semi(t_ast *node, int foreground)
{
	if (node->left)
		execute_node(node->left, foreground);
	if (node->right)
		return (execute_node(node->right, foreground));
	return (ASTERROR);
}

static int	parent_shell(int foreground, pid_t pid)
{
	t_job	*j;
	int		status;

	status = 0;
	if (foreground)
	{
		waitpid(pid, &status, WUNTRACED);
		return (get_exit_value(status));
	}
	else
	{
		j = (t_job*)ft_memalloc(sizeof(t_job));
		j->pgid = pid;
		j->first_process = (t_process*)ft_memalloc(sizeof(t_process));
		j->first_process->pid = pid;
		add_job_to_queue(j);
		return (0);
	}
}

int			execute_subshell(t_ast *node, int foreground)
{
	pid_t	pid;

	if ((pid = fork()) == 0)
	{
		pid = getpid();
		g_subshell = 1;
		restore_procmask();
		setpgid(pid, pid);
		exit(execute_node(node, foreground));
	}
	else if (pid < 0)
	{
		ft_printf("Fork subshell failed\n");
		exit(0);
	}
	return (parent_shell(foreground, pid));
}
