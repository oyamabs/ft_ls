/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:49:59 by tchampio          #+#    #+#             */
/*   Updated: 2026/05/04 18:43:17 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "types.h"
#include <stdlib.h>
#include <stdbool.h>

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
				args |= get_full_arg_value(av[current_arg]);
			if (av[current_arg][1] == 'a')
				args |= 1 << 1;
			if (av[current_arg][1] == 'l')
				args |= 1 << 2;
			if (av[current_arg][1] == 'r')
				args |= 1 << 3;
			if (av[current_arg][1] == 't')
				args |= 1 << 4;
			if (av[current_arg][1] == 'R')
				args |= 1 << 0;
		}
		current_arg++;
	}
	return (args);
}

int	main(int argc, char **argv)
{
	t_args	args;
	
	args = check_arguments(argc, argv);
	ft_printf("%d\n", args);
}
