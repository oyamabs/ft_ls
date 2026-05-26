/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:46:13 by tchampio          #+#    #+#             */
/*   Updated: 2026/05/26 16:18:31 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "explore.h"
#include "../utils.h"

t_file	*init_file(struct dirent *dirent, const char *path); // FIXME: delete this line

void	enter_directory(struct dirent *t, const char *name)
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
		recursively_explore(ddp, another, name_buffer);
	closedir(ddp);
	free(name_buffer);
}

void	recursively_explore(DIR *dp, struct dirent *t, const char *name)
{
	int				scanned_files;

	if (!dp)
		return ;
	ft_printf("exploring: %s\n", name);
	t = readdir(dp);
	scanned_files = 1;
	while (t != NULL)
	{
		t = readdir(dp);
		t_file *f = NULL;
		f = init_file(t, name);
		print_file(f);
		scanned_files++;
		if (t && t->d_type == DT_DIR)
		{
			if (scanned_files > 2)
				enter_directory(t, name);
		}
	}
}
