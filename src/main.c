/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:49:59 by tchampio          #+#    #+#             */
/*   Updated: 2026/05/07 16:57:50 by tchampio         ###   ########.fr       */
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

void	recursively_explore(DIR *dp, struct dirent *t)
{
	int	scanned_files;

	if (!dp)
		return ;
	t = readdir(dp);
	if (t == NULL)
		return ;
	scanned_files = 1;
	while (t != NULL)
	{
		ft_printf("dirent: %p\ninode: %d\nname: %s\n",t, t->d_ino, t->d_name);
		t = readdir(dp);
		scanned_files++;
		if (t && t->d_type == DT_DIR)
		{
			if (scanned_files > 2)
			{
				ft_printf("-> Opening directory: %s\n", t->d_name);
				struct dirent *another = NULL;
				DIR *ddp = opendir(t->d_name);
				recursively_explore(ddp, another);
			}
		}
	}
}

int	main(int argc, char **argv)
{
	int	i;
	t_arguments	args;
	init_arguments(&args, argc, argv);
	i = 0;
	// test opendir
	DIR *dp = opendir(args.filenames[0]);
	ft_printf("Dir pointer: %p\n", dp);
	struct dirent *direc = NULL;
	recursively_explore(dp, direc);
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
