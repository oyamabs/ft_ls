/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 14:02:48 by tchampio          #+#    #+#             */
/*   Updated: 2026/06/22 12:30:29 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "../libft/includes/libft.h"
#include <dirent.h>
#include "utils.h"

void	lower_string(char *s)
{
	for (size_t i = 0; i < ft_strlen(s); i++)
		s[i] = ft_tolower(s[i]);
}

int	compare_ascii(void *content_a, void *content_b)
{
	t_file	*a = (t_file *)content_a;
	t_file	*b = (t_file *)content_b;

	char	*name_a = (a->ent) ? a->ent->d_name : ft_basename(a->path);
	char	*name_b = (b->ent) ? b->ent->d_name : ft_basename(b->path);

	lower_string(name_a);
	lower_string(name_b);

	int	is_dot_a = (ft_strncmp(name_a, ".", 2) == 0 || ft_strncmp(name_a, "..", 3) == 0);
	int	is_dot_b = (ft_strncmp(name_b, ".", 2) == 0 || ft_strncmp(name_b, "..", 3) == 0);

	if (is_dot_a && !is_dot_b)
		return (-1);
	if (!is_dot_a && is_dot_b)
		return (1);
	if (is_dot_a && is_dot_b)
		return (ft_strlen(name_b) - ft_strlen(name_b));

	if (name_a[0] == '.' && name_a[1] != '\0')
		name_a++;
	if (name_b[0] == '.' && name_b[1] != '\0')
		name_b++;

	int retcode = ft_strncmp(name_a, name_b, 256);
	return (retcode);
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
