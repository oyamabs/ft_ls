/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:46:13 by tchampio          #+#    #+#             */
/*   Updated: 2026/06/30 18:49:59 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "explore.h"
#include "../utils.h"
#include <sys/stat.h>

void	enter_directory(struct dirent *t, const char *name, t_file_tree *current)
{
	char			*name_buffer;
	int				errno;
	struct dirent	*another;
	DIR				*ddp;

	another = NULL;
	errno = 0;
	name_buffer = ft_calloc(sizeof(char), 1000);
	ft_strlcat(name_buffer, name, 1000);
	ft_strlcat(name_buffer, "/", 1000);
	ft_strlcat(name_buffer, t->d_name, 1000);
	ddp = opendir(name_buffer);
	if (!errno)
	{
		t_file_tree	*new_branch;
		new_branch = ft_calloc(sizeof(*new_branch), 1);
		new_branch->statbuf = ft_calloc(sizeof(struct stat), 1);
		if (lstat(name_buffer, new_branch->statbuf) < 0)
		{
			free(new_branch->statbuf);
			free(new_branch);
			free(name_buffer);
			return ;
		}
		new_branch->path = ft_strdup(t->d_name);
		ft_lstadd_back(&(current->subdirectories), ft_lstnew((t_file_tree *)new_branch));
		recursively_explore(ddp, another, name_buffer, new_branch);
	}
	closedir(ddp);
	free(name_buffer);
}

void	recursively_explore(DIR *dp, struct dirent *t, const char *name, t_file_tree *branch)
{
	if (!dp || !branch)
		return ;
	while ((t = readdir(dp)) != NULL)
	{
		t_file *f = NULL;
		f = init_file(t, name, false);
		if (ft_strncmp(t->d_name, ".", 2) == 0 || ft_strncmp(t->d_name, "..", 3) == 0)
		{
			ft_lstadd_back(&(branch->files), ft_lstnew(f));
			continue ;
		}
		if (!f)
			break ;
		if (t->d_type == DT_DIR)
		{
			ft_lstadd_back(&(branch->files), ft_lstnew(f));
			enter_directory(t, name, branch);
		}
		else
			ft_lstadd_back(&(branch->files), ft_lstnew(f));
	}
}
