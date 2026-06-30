/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 14:02:48 by tchampio          #+#    #+#             */
/*   Updated: 2026/06/30 20:13:05 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "../libft/includes/libft.h"
#include <dirent.h>
#include <sys/stat.h>
#include "utils.h"

int	ft_strcasecmp_ls(const char *s1, const char *s2)
{
	size_t	i = 0;
	size_t	j = 0;

	if (s1 == s2)
		return 0;
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
	char	*name_a;
	char	*name_b;

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

int	compare_time(void *content_a, void *content_b, bool isdir)
{
	long	sec_a = 0, nsec_a = 0;
	long	sec_b = 0, nsec_b = 0;

	if (!isdir)
	{
		t_file	*file_a = (t_file *)content_a;
		t_file	*file_b = (t_file *)content_b;

		if (file_a && file_a->statbuf)
		{
			sec_a = file_a->statbuf->st_mtim.tv_sec;
			nsec_a = file_a->statbuf->st_mtim.tv_nsec;
		}
		if (file_b && file_b->statbuf)
		{
			sec_b = file_b->statbuf->st_mtim.tv_sec;
			nsec_b = file_b->statbuf->st_mtim.tv_nsec;
		}
	}
	else
	{
		t_file_tree	*tree_a = (t_file_tree *)content_a;
		t_file_tree	*tree_b = (t_file_tree *)content_b;

		if (tree_a && tree_a->statbuf)
		{
			sec_a = tree_a->statbuf->st_mtim.tv_sec;
			nsec_a = tree_a->statbuf->st_mtim.tv_nsec;
		}
		if (tree_b && tree_b->statbuf)
		{
			sec_b = tree_b->statbuf->st_mtim.tv_sec;
			nsec_b = tree_b->statbuf->st_mtim.tv_nsec;
		}
	}

	// Comparaison temporelle : Plus récent d'abord (b avant a si b > a)
	if (sec_a != sec_b)
		return (sec_b > sec_a ? 1 : -1);
	if (nsec_a != nsec_b)
		return (nsec_b > nsec_a ? 1 : -1);

	// Fallback : Si égalité parfaite, l'alphabet décide (gère . et .. naturellement ici)
	return (compare_ascii(content_a, content_b, isdir));
}

void	swap(t_list *ptr, bool isdir)
{
	if (isdir)
	{
		t_file *tmp = (t_file *)ptr->content;
		ptr->content = ptr->next->content;
		ptr->next->content = tmp;
	}
	else
	{
		t_file_tree *tmp = (t_file_tree *)ptr->content;
		ptr->content = ptr->next->content;
		ptr->next->content = tmp;
	}
}

t_list	*part(t_list *head, t_list *end, bool isdir)
{
	t_list	*pivot = end;
	t_list	*i = head;
	t_list	*j = head;
	void	*tmp;

	while (j != end && j != NULL)
	{
		if (compare_ascii(j->content, pivot->content, isdir) < 0)
		{
			tmp = i->content;
			i->content = j->content;
			j->content = tmp;
			i = i->next;
		}
		j = j->next;
	}
	tmp = i->content;
	i->content = end->content;
	end->content = tmp;
	return (i);
}

void	quicksort(t_list *files, t_list *end, bool isdir)
{
	if (!files || files == end || files == end->next)
		return ;
	t_list *pivot = part(files, end, isdir);
	t_list *prev = files;

	if (pivot != files)
	{
		while (prev != NULL && prev->next != pivot)
			prev = prev->next;
		quicksort(files, prev, isdir);
	}

	if (pivot != NULL && pivot->next != NULL)
		quicksort(pivot->next, end, isdir);
}

void	sort_entries_alpha(t_list *files, bool isdir)
{
	if (!files || !files->next)
		return ;

	t_list	*end = ft_lstlast(files);
	quicksort(files, end, isdir);
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

t_list	*reverse_list(t_list *lst)
{
	t_list	*prev;
	t_list	*current;
	t_list	*next;

	prev = NULL;
	current = lst;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	return (prev);
}

void	reverse_tree(t_file_tree *tree)
{
	if (!tree)
		return ;

	tree->files = reverse_list(tree->files);

	tree->subdirectories = reverse_list(tree->subdirectories);

	t_list *current_branch = tree->subdirectories;
	while (current_branch != NULL)
	{
		t_file_tree *sub_tree = (t_file_tree *)current_branch->content;
		reverse_tree(sub_tree);
		current_branch = current_branch->next;
	}
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
