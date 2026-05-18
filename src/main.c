/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:49:59 by tchampio          #+#    #+#             */
/*   Updated: 2026/05/18 15:50:25 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "types.h"
#include "arguments/arguments.h"
#include "explore/explore.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

int	main(int argc, char **argv)
{
	int				i;
	t_arguments		args;
	DIR				*dp;
	struct dirent	*direc;

	init_arguments(&args, argc, argv);
	i = 0;
	dp = opendir(args.filenames[0]);
	ft_printf("Dir pointer: %p\n", dp);
	direc = NULL;
	recursively_explore(dp, direc, args.filenames[0]);
	while (i < args.number_of_files)
	{
		printf("%s ", args.filenames[i]);
		if (args.filenames[i])
			free(args.filenames[i]);
		i++;
	}
	free(args.filenames);
	closedir(dp);
}
