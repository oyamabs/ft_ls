/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:49:59 by tchampio          #+#    #+#             */
/*   Updated: 2026/06/16 14:35:29 by tchampio         ###   ########.fr       */
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

int	compare_ascii(void *content_a, void *content_b)
{
	t_file	*a = (t_file *)content_a;
	t_file	*b = (t_file *)content_b;

	return (ft_strncmp(a->ent->d_name, b->ent->d_name, 256));
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
	sort_entries_alpha(tree.files);
	print_file_tree(&tree, 0);
	free(args.filenames);
	closedir(dp);
}
