/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:49:59 by tchampio          #+#    #+#             */
/*   Updated: 2026/07/15 15:46:07 by tchampio         ###   ########.fr       */
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
#include "free.h"
#include "sort.h"

int	main(int argc, char **argv)
{
	int				i;
	t_arguments		args;
	DIR				**dps;
	struct dirent	*direc;
	t_file_tree		**trees;
	t_width			global_width;

	init_arguments(&args, argc, argv);
	i = 0;
	trees = ft_calloc(sizeof(*trees), args.number_of_files);
	if (!trees)
		return 1;
	dps = ft_calloc(sizeof(*dps), args.number_of_files);
	if (!dps)
		return (free(trees), 1);
	while (i < args.number_of_files)
	{
		dps[i] = opendir(args.filenames[i]);
		trees[i] = ft_calloc(sizeof(*trees[i]), 1);
		if (!trees[i])
			exit(1); // dangerous ! OOOoooohhh! 👻👻👻
		trees[i]->width = ft_calloc(sizeof(t_width), 1);
		t_file_tree *current_tree = trees[i];
		if (!dps[i])
		{
			t_file *individual_file = init_file(NULL, args.filenames[i], true);
			ft_lstadd_back(&(current_tree->files), ft_lstnew((t_file *)individual_file));
			i++;
			continue ;
		}
		direc = NULL;
		recursively_explore(dps[i], direc, args.filenames[i], current_tree);
		i++;
	}
	i = 0;
	while (i < args.number_of_files)
	{
		if (args.filenames[i])
			free(args.filenames[i]);
		i++;
	}
	i = 0;
	ft_bzero(&global_width, sizeof(global_width));
	while (i < args.number_of_files)
	{
		sort_tree(trees[i]);
		accumulate_widths(trees[i]);
		i++;
	}
	i = 0;
	while (i < args.number_of_files)
	{
		ft_printf("%s:\n", trees[i]->path);
		print_file_tree(trees[i], 0, global_width);
		i++;
	}
	free(args.filenames);
	i = 0;
	while (i < args.number_of_files)
	{
		free_tree(trees[i]);
		free(trees[i]);
		if (dps[i])
			closedir(dps[i]);
		i++;
	}
	free(dps);
	free(trees);
}
