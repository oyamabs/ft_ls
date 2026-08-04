/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:49:59 by tchampio          #+#    #+#             */
/*   Updated: 2026/08/05 01:25:44 by tchampio         ###   ########.fr       */
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

void	clean_file_list(t_list **files_head)
{
	t_list	**curr;
	t_list	*to_del;
	t_file	*file;

	if (!files_head || !*files_head)
		return ;

	curr = files_head;
	while (*curr != NULL)
	{
		file = (t_file *)(*curr)->content;
		if (!file || !file->statbuf)
		{
			to_del = *curr;
			*curr = (*curr)->next;
			ft_lstdelone(to_del, free_file);
		}
		else
			curr = &((*curr)->next);
	}
}

void	clean_tree(t_file_tree *tree)
{
	t_list	*current_sub;

	if (!tree)
		return ;

	clean_file_list(&(tree->files));
	current_sub = tree->subdirectories;
	while (current_sub != NULL)
	{
		t_file_tree *subtree = (t_file_tree *)current_sub->content;
		clean_tree(subtree);
		current_sub = current_sub->next;
	}
}

void	check_and_clean_trees(t_file_tree *individual_files, t_file_tree **trees, int number_of_files)
{
	int	i;

	if (individual_files)
		clean_tree(individual_files);

	if (trees)
	{
		i = 0;
		while (i < number_of_files)
		{
			if (trees[i])
				clean_tree(trees[i]);
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	int				i;
	t_arguments		args;
	DIR				**dps;
	struct dirent	*direc;
	t_file_tree		**trees;
	t_file_tree		*individual_files;
	t_width			global_width;
	bool			has_printed_newline_after_single_files;

	init_arguments(&args, argc, argv);
	i = 0;
	trees = ft_calloc(sizeof(*trees), args.number_of_files);
	if (!trees)
		return 1;
	dps = ft_calloc(sizeof(*dps), args.number_of_files);
	if (!dps)
		return (free(trees), 1);
	individual_files = ft_calloc(sizeof(*individual_files), 1);
	individual_files->width = ft_calloc(sizeof(t_width), 1);
	individual_files->is_individual_files = true;
	ft_bzero(&global_width, sizeof(global_width));
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
			ft_lstadd_back(&(individual_files->files), ft_lstnew((t_file *)individual_file));
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
	check_and_clean_trees(individual_files, trees, args.number_of_files);
	ft_bzero(&global_width, sizeof(global_width));
	sort_tree(individual_files, args);
	if (args.flags & (1 << ARG_REVERSE))
		reverse_tree(individual_files);
	accumulate_widths(individual_files, args);
	while (i < args.number_of_files)
	{
		sort_tree(trees[i], args);
		if (args.flags & (1 << ARG_REVERSE))
			reverse_tree(trees[i]);
		accumulate_widths(trees[i], args);
		i++;
	}
	i = 0;
	print_file_tree(individual_files, -2, global_width, args);
	if (individual_files->files)
		has_printed_newline_after_single_files = true;
	while (i < args.number_of_files)
	{
		if (trees[i]->path && (args.number_of_files > 1 || args.flags & (1 << ARG_RECURSIVE)))
		{
			if (has_printed_newline_after_single_files)
				ft_printf("\n");
			ft_printf("%s:\n", trees[i]->path);
		}
		print_file_tree(trees[i], 0, global_width, args);
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
	free_tree(individual_files);
	free(individual_files);
	free(dps);
	free(trees);
}
