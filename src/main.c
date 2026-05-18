/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:49:59 by tchampio          #+#    #+#             */
/*   Updated: 2026/05/18 14:45:53 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "types.h"
#include "arguments/arguments.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

#include <sys/types.h>
#include <dirent.h>

void	recursively_explore(DIR *dp, struct dirent *t, const char *name);

void	enter_directory(struct dirent *t, const char *name)
{
	char			*name_buffer;
	int				errno;
	struct dirent	*another;
	DIR				*ddp;

	another = NULL;
	errno = 0;
	name_buffer = ft_calloc(sizeof(char), 1000);
	ft_strlcat(name_buffer, name, 1000);
	ft_strlcat(name_buffer, "/", 1000);
	ft_strlcat(name_buffer, t->d_name, 1000);
	ddp = opendir(name_buffer);
	if (!errno)
		recursively_explore(ddp, another, name_buffer);
	closedir(ddp);
	free(name_buffer);
}

void	recursively_explore(DIR *dp, struct dirent *t, const char *name)
{
	int				scanned_files;

	if (!dp)
		return ;
	ft_printf("exploring: %s\n", name);
	t = readdir(dp);
	scanned_files = 1;
	while (t != NULL)
	{
		ft_printf("%s\n", t->d_name);
		t = readdir(dp);
		scanned_files++;
		if (t && t->d_type == DT_DIR)
		{
			if (scanned_files > 2)
				enter_directory(t, name);
		}
	}
}

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
