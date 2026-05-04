/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:49:59 by tchampio          #+#    #+#             */
/*   Updated: 2026/05/04 19:40:54 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "types.h"
#include <stdlib.h>
#include <stdbool.h>

void	double_dash_args(char *argv, t_args *args)
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

void	single_dash_args(char *argv, t_args *args)
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

t_args	check_arguments(int ac, char **av)
{
	int		current_arg;
	bool	stop;
	t_args	args;

	if (ac == 1)
		return (0);
	current_arg = 1;
	stop = false;
	args = 0;
	while (av[current_arg] && !stop)
	{
		if (av[current_arg][0] != '-')
			stop = true;
		else
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

int	main(int argc, char **argv)
{
	t_args	args;
	
	args = check_arguments(argc, argv);
	bool l, a, r, t, R;
	l = args & (1 << 2);
	a = args & (1 << 1);
	r = args & (1 << 3);
	t = args & (1 << 4);
	R = args & (1 << 0);
	ft_printf("Flags value: %d\n", args);
	ft_printf("-l ? %d\n", l);
	ft_printf("-r ? %d\n", r);
	ft_printf("-a ? %d\n", a);
	ft_printf("-t ? %d\n", t);
	ft_printf("-R ? %d\n", R);
}
