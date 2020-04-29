/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 22:06:23 by snunes            #+#    #+#             */
/*   Updated: 2020/03/11 19:12:20 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

char	*g_needed_arg = NULL;

int		cmd_hash(int argc, char **argv)
{
	char	**args;
	int		options_list;
	int		status;

	args = (argv) ? argv + 1 : argv;
	options_list = 0;
	g_builtin_name = (argv) ? argv[0] : NULL;
	while (args && argc > 1 && (status = get_next_opt(&args, "dlp:rt")) != -1)
	{
		if (status == 'd')
			options_list |= HASH_D_OPTION;
		else if (status == 'l')
			options_list |= HASH_L_OPTION;
		else if (status == 'p')
			options_list |= HASH_P_OPTION;
		else if (status == 'r')
			options_list |= HASH_R_OPTION;
		else if (status == 't')
			options_list |= HASH_T_OPTION;
		else
			return (print_usage(*args));
	}
	if (!args)
		return (e_invalid_input);
	return (check_for_needed_arguments(options_list, args) > 0);
}

char	get_next_opt(char ***args, const char *options_list)
{
	static int	x = 0;

	x++;
	if (!args || !*args || !**args)
	{
		x = 0;
		return (-1);
	}
	if ((**args)[0] == '-' && !(**args)[1])
	{
		x = 0;
		return (-1);
	}
	if (!(**args)[x] && (**args)[0] == '-')
	{
		x = 1;
		*args += 1;
	}
	if (!(**args))
		return (get_next_opt(NULL, NULL));
	if ((**args)[0] == '-')
		return (return_next_opt(args, &x, options_list));
	return (get_next_opt(NULL, NULL));
}

int		print_usage(char *args)
{
	int	x;

	x = 0;
	while (args[x] && ft_strchr("-dlprt", args[x]))
		x += 1;
	print_error("[-lr] [-p pathname] [-dt] [name ...]", args[x], 3);
	return (e_invalid_input);
}

int		check_for_needed_arguments(int options_list, char **args)
{
	int	status;

	if (!*args && options_list & HASH_T_OPTION)
	{
		ft_dprintf(STDERR_FILENO, \
				"./21sh: hash: -t: option requires an argument\n");
		return (e_invalid_input);
	}
	status = exec_hash_builtin(options_list, args);
	if (g_needed_arg)
	{
		free(g_needed_arg);
		g_needed_arg = NULL;
	}
	return (status);
}

int		exec_hash_builtin(int options_list, char **args)
{
	int	status;

	status = e_success;
	if ((!*args && !(options_list & HASH_R_OPTION)) \
			|| (*args && !(*args + 1) && options_list & HASH_P_OPTION))
		return (print_hashed_commands(options_list));
	if (options_list & HASH_R_OPTION)
		del_hashed_commands();
	if (options_list & HASH_T_OPTION)
		return (print_hashed_targets(options_list, args));
	while (status != e_cannot_allocate_memory && *args)
	{
		if (options_list & HASH_P_OPTION)
			status = change_hash_entry(g_needed_arg, *args);
		else if (options_list & HASH_D_OPTION || find_occurence(*args))
			remove_hash_entry(*args);
		if ((*args)[0] != '.' && !(options_list & HASH_P_OPTION) \
				&& !(options_list & HASH_D_OPTION))
			status = add_name_hash_table(*args, 0);
		if (status == e_command_not_found || (*args)[0] == '.')
			ft_dprintf(STDERR_FILENO, "./21sh: hash: %s: not found\n", *args);
		args++;
	}
	return (status);
}
