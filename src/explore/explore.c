/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:46:13 by tchampio          #+#    #+#             */
/*   Updated: 2026/08/05 20:03:05 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "explore.h"
#include "../utils.h"
#include <sys/stat.h>

bool	is_link_slash(const char *full_path)
{
	struct stat statbuf;
	bool res = false;

	if (lstat(full_path, &statbuf) < 0)
		return (false);
	if (S_ISLNK(statbuf.st_mode))
		res = true;
	return (res);
}

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
	if (is_link_slash(name_buffer))
	{
		free(name_buffer);
		return ;
	}
	ddp = opendir(name_buffer);
	if (!errno)
	{
		t_file_tree	*new_branch;
		new_branch = ft_calloc(sizeof(*new_branch), 1);
		new_branch->statbuf = ft_calloc(sizeof(struct stat), 1);
		new_branch->width = ft_calloc(sizeof(t_width), 1);
		new_branch->name = ft_strdup(t->d_name);
		if (lstat(name_buffer, new_branch->statbuf) < 0)
		{
			free(new_branch->statbuf);
			free(new_branch);
			free(name_buffer);
			return ;
		}
		ft_lstadd_back(&(current->subdirectories), ft_lstnew((t_file_tree *)new_branch));
		recursively_explore(ddp, another, name_buffer, new_branch);
	}
	closedir(ddp);
	free(name_buffer);
}

void	recursively_explore(DIR *dp, struct dirent *t, const char *name, t_file_tree *branch)
{
	branch->path = ft_strdup(name);
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
