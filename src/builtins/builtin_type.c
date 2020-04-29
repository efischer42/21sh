/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/11 16:49:03 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

static const struct s_keywords	g_keywords[] =
{
	{ "{" },
	{ "}" },
	{ "!" },
	{ "do" },
	{ "if" },
	{ "fi" },
	{ "for" },
	{ "case" },
	{ "esac" },
	{ "then" },
	{ "else" },
	{ "done" },
	{ "until" },
	{ "while" },
	{ "select" },
	{ "function" },
	{ NULL }
};

static _Bool	is_a_keyword(char *word)
{
	int	i;

	i = 0;
	while (g_keywords[i].keyword)
	{
		if (!ft_strcmp(g_keywords[i].keyword, word))
			return (1);
		else
			++i;
	}
	return (0);
}

static char		*getbinpath(char *bin)
{
	char *cpy;

	if (!(cpy = ft_strdup(bin)))
		return (NULL);
	if (path_concat(&cpy, NULL, NULL, NULL) == e_success)
		return (cpy);
	else
	{
		ft_memdel((void**)&cpy);
		return (NULL);
	}
}

static void		display_err_msg(_Bool *error, int i, char **argv)
{
	*error |= 1;
	ft_dprintf(STDERR_FILENO, "%s: %s: %s: not found\n",
				g_progname, *argv, argv[i]);
}

int				cmd_type(int argc, char **argv)
{
	_Bool			error;
	int				i;
	t_hash_table	*path;
	char			*str;

	error = 0;
	i = 1;
	while (i < argc)
	{
		if (is_a_builtin(argv[i]))
			ft_printf("%s is a shell builtin\n", argv[i]);
		else if (is_a_keyword(argv[i]))
			ft_printf("%s is a shell keyword\n", argv[i]);
		else if ((path = find_occurence(argv[i])))
			ft_printf("%s is hashed (%s)\n", argv[i], path->command_path);
		else if ((str = getbinpath(argv[i])))
		{
			ft_printf("%s is %s\n", argv[i], str);
			ft_memdel((void**)&str);
		}
		else
			display_err_msg(&error, i, argv);
		++i;
	}
	return (error);
}
