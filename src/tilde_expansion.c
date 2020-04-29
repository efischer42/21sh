/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:07:44 by abarthel          #+#    #+#             */
/*   Updated: 2019/08/27 14:53:43 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "error.h"

static int	replace_tilde(char **str, char *start, char *env)
{
	char	*cpy;

	if (!env)
	{
		if (!(cpy = ft_strjoin("", start)))
			return (e_cannot_allocate_memory);
	}
	else
	{
		if (!(cpy = ft_strjoin(env, start)))
			return (e_cannot_allocate_memory);
	}
	*str = cpy;
	return (e_success);
}

static void	test_syntax(size_t *index, char **str, int *ret)
{
	char	*env;

	if (!(*str)[1] || (*str)[1] == '/')
	{
		env = ft_getenv("HOME");
		*index = ft_strlen(env);
		*ret = replace_tilde(str, &(*str)[1], env);
	}
	else if ((*str)[1] == '-' && ((*str)[2] == '/' || !(*str)[2]))
	{
		env = ft_getenv("OLDPWD");
		*index = ft_strlen(env);
		*ret = replace_tilde(str, &(*str)[2], env);
	}
	else if ((*str)[1] == '+' && ((*str)[2] == '/' || !(*str)[2]))
	{
		env = ft_getenv("PWD");
		*index = ft_strlen(env);
		*ret = replace_tilde(str, &(*str)[2], env);
	}
	else
	{
		*ret = replace_tilde(str, &(*str)[1], "~");
		*index = 1;
	}
}

int			tilde_expansion(size_t *index, char **str, const char *opentag,
		const char *closetag)
{
	int	ret;

	(void)opentag;
	(void)closetag;
	ret = e_success;
	if (!*index)
		test_syntax(index, str, &ret);
	else
	{
		ret = replace_tilde(str, &(*str)[1], "~");
		*index = 1;
	}
	return (ret);
}
