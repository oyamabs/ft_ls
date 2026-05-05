/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:49:59 by tchampio          #+#    #+#             */
/*   Updated: 2026/05/05 17:24:20 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "types.h"
#include "arguments/arguments.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <sys/types.h>
#include <dirent.h>

void	recursively_explore(DIR *dp, bool *finished_exploring, struct dirent *t)
{
	if (*finished_exploring)
		return ;
	
	t = readdir(dp);
	while (t)
	{
		t = readdir(dp);
		ft_printf("dirent: %p\ninode: %s\n",t , t->d_name);
	}
}

int	main(int argc, char **argv)
{
	int	i;
	t_arguments	args;
	init_arguments(&args, argc, argv);
	i = 0;
	// test opendir
	DIR *dp = opendir(".");
	ft_printf("Dir pointer: %p\n", dp);
	bool explore = true;
	struct dirent *direc = NULL;
	recursively_explore(dp, &explore, direc);
	while (i < args.number_of_files)
	{
		printf("%s ", args.filenames[i]);
		if (args.filenames[i])
			free(args.filenames[i]);
		i++;
	}
	free(args.filenames);
	free(dp);
}
