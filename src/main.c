/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:49:59 by tchampio          #+#    #+#             */
/*   Updated: 2026/05/04 22:28:37 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "types.h"
#include "arguments/arguments.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int	main(int argc, char **argv)
{
	int	i;
	t_arguments	args;
	init_arguments(&args, argc, argv);
	ft_printf("%d\n", args.flags);
	bool l, a, r, R, t;
	l = args.flags & (1 << ARG_LIST);
	a = args.flags & (1 << ARG_HIDDEN);
	r = args.flags & (1 << ARG_REVERSE);
	t = args.flags & (1 << ARG_TIME);
	R = args.flags & (1 << ARG_RECURSIVE);
	ft_printf("l ? %d\n", l);
	ft_printf("r ? %d\n", r);
	ft_printf("a ? %d\n", a);
	ft_printf("t ? %d\n", t);
	ft_printf("R ? %d\n", R);
	i = 0;
	while (i < args.number_of_files)
	{
		printf("%s ", args.filenames[i]);
		if (args.filenames[i])
			free(args.filenames[i]);
		i++;
	}
	free(args.filenames);
}
