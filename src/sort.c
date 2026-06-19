/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 14:02:48 by tchampio          #+#    #+#             */
/*   Updated: 2026/06/19 14:12:29 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "../libft/includes/libft.h"

int	compare_ascii(void *content_a, void *content_b)
{
	t_file	*a = (t_file *)content_a;
	t_file	*b = (t_file *)content_b;

	return (ft_strncmp(a->path, b->path, 256));
}

void	sort_entries_alpha(t_list *files)
{
	bool	swapped;
	t_list	*ptr1;

	if (!files)
		return ;
	do
	{
		swapped = false;
		ptr1 = files;
		while (ptr1->next != NULL)
		{
			if (compare_ascii(ptr1->content, ptr1->next->content) > 0)
			{
				t_file *tmp = (t_file *)ptr1->content;
				ptr1->content = ptr1->next->content;
				ptr1->next->content = tmp;
				swapped = true;
			}
			ptr1 = ptr1->next;
		}
	} while (swapped == true);
}

void	sort_entries_reverse(t_list *files)
{
	bool	swapped;
	t_list	*ptr1;

	if (!files)
		return ;
	do
	{
		swapped = false;
		ptr1 = files;
		while (ptr1->next != NULL)
		{
			if (compare_ascii(ptr1->content, ptr1->next->content) < 0)
			{
				t_file *tmp = (t_file *)ptr1->content;
				ptr1->content = ptr1->next->content;
				ptr1->next->content = tmp;
				swapped = true;
			}
			ptr1 = ptr1->next;
		}
	} while (swapped == true);
}

void	sort_tree(t_file_tree *tree)
{
	if (!tree)
		return ;
	t_list *current_files = tree->files;
	sort_entries_alpha(current_files);
	t_list *current_branch = tree->subdirectories;
	while (current_branch != NULL)
	{
		t_file_tree *sub_tree = current_branch->content;
		sort_tree(sub_tree);
		current_branch = current_branch->next;
	}
}
