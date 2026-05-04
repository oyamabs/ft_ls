/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 19:42:47 by tchampio          #+#    #+#             */
/*   Updated: 2026/05/04 21:22:53 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/includes/libft.h"
#include "../types.h"
#include <stdlib.h>
#include <stdbool.h>

void	double_dash_args(char *argv, t_flags *args)
{
	if (!ft_strncmp(argv, "--all", 5))
		*args |= 1 << ARG_HIDDEN;
	if (!ft_strncmp(argv, "--list", 6))
		*args |= 1 << ARG_LIST;
	if (!ft_strncmp(argv, "--recursive", 11))
		*args |= 1 << ARG_RECURSIVE;
	if (!ft_strncmp(argv, "--time", 6))
		*args |= 1 << ARG_TIME;
	if (!ft_strncmp(argv, "--reverse", 9))
		*args |= 1 << ARG_REVERSE;
}

void	single_dash_args(char *argv, t_flags *args)
{
	size_t	arglen;
	size_t	i;

	arglen = ft_strlen(argv);
	i = 1;
	while (i < arglen)
	{
		if (argv[i] == 'a')
			*args |= 1 << ARG_HIDDEN;
		if (argv[i] == 'l')
			*args |= 1 << ARG_LIST;
		if (argv[i] == 'r')
			*args |= 1 << ARG_REVERSE;
		if (argv[i] == 't')
			*args |= 1 << ARG_TIME;
		if (argv[i] == 'R')
			*args |= 1 << ARG_RECURSIVE;
		i++;
	}
}

t_flags	check_flags_arguments(int ac, char **av)
{
	int		current_arg;
	t_flags	args;

	if (ac == 1)
		return (0);
	current_arg = 1;
	args = 0;
	while (av[current_arg])
	{
		if (av[current_arg][0] == '-')
		{
			if (av[current_arg][1] == '-')
				double_dash_args(av[current_arg], &args);
			else
				single_dash_args(av[current_arg], &args);
		}
		current_arg++;
	}
	return (args);
}
