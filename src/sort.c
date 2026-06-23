/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 14:02:48 by tchampio          #+#    #+#             */
/*   Updated: 2026/06/23 12:28:04 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "../libft/includes/libft.h"
#include <dirent.h>
#include "utils.h"

int	ft_strcasecmp_ls(const char *s1, const char *s2)
{
	size_t	i = 0;
	size_t	j = 0;

	if (s1[i] == '.' && s1[i + 1] != '\0')
		s1++;
	if (s2[j] == '.' && s2[j + 1] != '\0')
		s2++;

	while (s1[i] && s2[i])
	{
		if (ft_tolower((unsigned char)s1[i]) != ft_tolower((unsigned char)s2[i]))
			return (ft_tolower((unsigned char)s1[i]) - ft_tolower((unsigned char)s2[i]));
		i++;
	}
	if (ft_tolower((unsigned char)s1[i]) != ft_tolower((unsigned char)s2[i]))
		return (ft_tolower((unsigned char)s1[i]) - ft_tolower((unsigned char)s2[i]));

	// reverse the comparison to respect how `ls` sorts filenames
	return (ft_strncmp(s2, s1, 256));
}

int	compare_ascii(void *content_a, void *content_b, bool isdir)
{
	char	*name_a, *name_b;
	if (!isdir)
	{
		t_file	*a = (t_file *)content_a;
		t_file	*b = (t_file *)content_b;

		name_a = (a->ent) ? a->ent->d_name : ft_basename(a->path);
		name_b = (b->ent) ? b->ent->d_name : ft_basename(b->path);
	}
	else
	{
		t_file_tree	*a = (t_file_tree *)content_a;
		t_file_tree	*b = (t_file_tree *)content_b;

		name_a = ft_basename(a->path);
		name_b = ft_basename(b->path);
	}

	int is_dot_a = (ft_strncmp(name_a, ".", 2) == 0 || ft_strncmp(name_a, "..", 3) == 0);
	int is_dot_b = (ft_strncmp(name_b, ".", 2) == 0 || ft_strncmp(name_b, "..", 3) == 0);

	if (is_dot_a && !is_dot_b)
		return (-1);
	if (!is_dot_a && is_dot_b)
		return (1);
	if (is_dot_a && is_dot_b) // Force '.' à être au dessus de '..'
		return ((int)ft_strlen(name_a) - (int)ft_strlen(name_b));

	return (ft_strcasecmp_ls(name_a, name_b));
}

void	sort_entries_alpha(t_list *files, bool isdir)
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
			if (compare_ascii(ptr1->content, ptr1->next->content, isdir) > 0)
			{
				if (isdir)
				{
					t_file *tmp = (t_file *)ptr1->content;
					ptr1->content = ptr1->next->content;
					ptr1->next->content = tmp;
				}
				else
				{
					t_file_tree *tmp = (t_file_tree *)ptr1->content;
					ptr1->content = ptr1->next->content;
					ptr1->next->content = tmp;
				}
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
			if (compare_ascii(ptr1->content, ptr1->next->content, false) < 0)
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
	sort_entries_alpha(current_files, false);
	t_list *current_branch = tree->subdirectories;
	sort_entries_alpha(current_branch, true);
	while (current_branch != NULL)
	{
		t_file_tree *sub_tree = current_branch->content;
		sort_tree(sub_tree);
		current_branch = current_branch->next;
	}
}
