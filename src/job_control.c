/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:32:42 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/10 18:57:18 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "builtins.h"

t_job	*first_job = NULL;

void	put_job_in_foreground(t_job *j, int cont)
{
	tcsetpgrp(shell_terminal, j->pgid);
	if (cont)
	{
		tcsetattr(shell_terminal, TCSADRAIN, &j->tmodes);
		if (kill(-j->pgid, SIGCONT) < 0)
			ft_perror("kill failed sending (SIGCONT)");
	}
	wait_for_job(j);
	tcsetpgrp(shell_terminal, shell_pgid);
	tcgetattr(shell_terminal, &j->tmodes);
	tcsetattr(shell_terminal, TCSADRAIN, &shell_tmodes);
}

void	put_job_in_background(t_job *j, int cont)
{
	if (cont)
	{
		if (kill(-j->pgid, SIGCONT) < 0)
			ft_perror("kill failed sending (SIGCONT)");
	}
}

t_job	*find_job(pid_t pgid)
{
	t_job	*j;

	j = first_job;
	while (j)
	{
		if (j->pgid == pgid)
			return (j);
		j = j->next;
	}
	return (NULL);
}

int		job_is_stopped(t_job *j)
{
	t_process	*p;

	p = j->first_process;
	while (p)
	{
		if (!p->completed && !p->stopped)
			return (0);
		p = p->next;
	}
	return (1);
}

int		job_is_completed(t_job *j)
{
	t_process	*p;

	p = j->first_process;
	while (p)
	{
		if (!p->completed)
			return (0);
		p = p->next;
	}
	return (1);
}
