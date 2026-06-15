/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:49:59 by tchampio          #+#    #+#             */
/*   Updated: 2026/06/15 14:54:05 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "types.h"
#include "arguments/arguments.h"
#include "explore/explore.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "utils.h"

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
	t_file_tree	tree = { 0 };
	recursively_explore(dp, direc, args.filenames[0], &tree);
	while (i < args.number_of_files)
	{
		//ft_printf("%s ", args.filenames[i]);
		if (args.filenames[i])
			free(args.filenames[i]);
		i++;
	}
	print_file_tree(&tree, 0);
	free(args.filenames);
	closedir(dp);
}
