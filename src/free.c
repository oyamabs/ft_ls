/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:46:37 by tchampio          #+#    #+#             */
/*   Updated: 2026/06/30 19:38:44 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "types.h"
#include "utils.h"

void	free_file(void *file)
{
	t_file *f = (t_file *)file;
	if (!f)
		return ;
	if (f->ent != NULL)
		free(f->ent);
	if (f->statbuf != NULL)
		free(f->statbuf);
	if (f->path != NULL)
		free(f->path);
	if (f->points_to != NULL)
		free(f->points_to);
	free(f);
}

void	free_tree(t_file_tree *tree)
{
	if (!tree)
		return ;
	if (tree->statbuf)
		free(tree->statbuf);
	t_list *current_files = tree->files;
	ft_lstclear(&current_files, free_file);
	free(current_files);
	t_list *current_branch = tree->subdirectories;
	while (current_branch != NULL)
	{
		t_file_tree *sub_tree = current_branch->content;
		free(sub_tree->path);
		free_tree(sub_tree);
		current_branch = current_branch->next;
	}
	ft_lstclear(&tree->subdirectories, free);
}
