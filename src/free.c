/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:46:37 by tchampio          #+#    #+#             */
/*   Updated: 2026/06/18 14:47:23 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "types.h"
#include "utils.h"

void	free_file(void *file)
{
	t_file *f = (t_file *)file;
	free(f->ent);
	free(f->path);
	free(f);
}

void	free_tree(t_file_tree *tree)
{
	if (!tree)
		return ;
	t_list *current_files = tree->files;
	ft_lstclear(&current_files, free_file);
	free(current_files);
	t_list *current_branch = tree->subdirectories;
	while (current_branch != NULL)
	{
		t_file_tree *sub_tree = current_branch->content;
		free_tree(sub_tree);
		current_branch = current_branch->next;
	}
	ft_lstclear(&tree->subdirectories, free);
}
