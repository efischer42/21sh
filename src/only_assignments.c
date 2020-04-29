/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_assignments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 11:52:47 by efischer          #+#    #+#             */
/*   Updated: 2020/03/12 09:41:20 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

int		only_assignments(t_process *p)
{
	int				ret;
	int				i;

	i = 0;
	ret = FALSE;
	while (i < p->argc)
	{
		if (ft_strchr(p->argv[i], '=') == NULL)
			break ;
		i++;
	}
	if (i == p->argc)
		ret = TRUE;
	return (ret);
}
