/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 16:04:17 by tchampio          #+#    #+#             */
/*   Updated: 2026/06/22 16:03:04 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include "../libft/includes/libft.h"

void	print_file(void *file)
{
	t_file	*f;

	f = (t_file *)file;
	if (!f || !f->ent)
		return ;
	struct passwd* passbuf;
	passbuf = getpwuid(f->statbuf->st_uid);
	ft_printf("%s %d %s %s %d %d %d %d:%d %s\n", f->flags_rights, f->statbuf->st_nlink , passbuf->pw_name, "prout", 69, "Pet", 1, 20, 9, f->path);

}

void print_file_tree(t_file_tree *tree, int level)
{
    if (!tree)
        return;

    t_list *current_file = tree->files;
    while (current_file != NULL)
    {
        t_file *file = (t_file *)current_file->content;
        if (file)
        {
            for (int i = 0; i < level; i++)
                ft_printf("    ");
            if (file->points_to)
                ft_printf("📄 %s -> %s\n", file->path, file->points_to);
            else
                print_file(file);// ft_printf("📄 %s\n", file->path);
        }
        current_file = current_file->next;
    }

    t_list *current_sub = tree->subdirectories;
    while (current_sub != NULL)
    {
        t_file_tree *subtree = (t_file_tree *)current_sub->content;
        if (subtree)
        {
            for (int i = 0; i < level; i++)
                ft_printf("    ");
            ft_printf("📁 [Dossier: %s]:\n", subtree->path);
            print_file_tree(subtree, level + 1);
        }
        current_sub = current_sub->next;
    }
}

/*
   man inode(7)
           S_IRWXU     00700   owner has read, write, and execute permission
           S_IRUSR     00400   owner has read permission
           S_IWUSR     00200   owner has write permission
           S_IXUSR     00100   owner has execute permission

           S_IRWXG     00070   group has read, write, and execute permission
           S_IRGRP     00040   group has read permission
           S_IWGRP     00020   group has write permission
           S_IXGRP     00010   group has execute permission

           S_IRWXO     00007   others (not in group) have  read,  write,  and
                               execute permission
           S_IROTH     00004   others have read permission
           S_IWOTH     00002   others have write permission
           S_IXOTH     00001   others have execute permission
*/

char		get_file_type(int mode)
{
	mode = (mode & S_IFMT);
	if (S_ISREG(mode))
		return ('-');
	else if (S_ISDIR(mode))
		return ('d');
	else if (S_ISLNK(mode))
		return ('l');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISSOCK(mode))
		return ('s');
	else if (S_ISFIFO(mode))
		return ('p');
	else
		return ('-');
}


void	get_flags(t_file *file)
{
	// man stat(2)
	int			mode;

	mode = file->statbuf->st_mode;
	file->flags_rights[0] = get_file_type(mode);
	file->flags_rights[1] = (S_IRUSR & mode) ? 'r' : '-';
	file->flags_rights[2] = (S_IWUSR & mode) ? 'w' : '-';
	file->flags_rights[3] = (S_IXUSR & mode) ? 'x' : '-';
	file->flags_rights[4] = (S_IRGRP & mode) ? 'r' : '-';
	file->flags_rights[5] = (S_IWGRP & mode) ? 'w' : '-';
	file->flags_rights[6] = (S_IXGRP & mode) ? 'x' : '-';
	file->flags_rights[7] = (S_IROTH & mode) ? 'r' : '-';
	file->flags_rights[8] = (S_IWOTH & mode) ? 'w' : '-';
	file->flags_rights[9] = (S_IXOTH & mode) ? 'x' : '-';
	file->flags_rights[10] = '\0';
}

char	*ft_basename(char *name)
{
	char	*last_slash;
	int		i;

	if (!name)
		return (NULL);
	last_slash = NULL;
	i = 0;
	while (name[i])
	{
		if (name[i] == '/')
		{
			last_slash = name;
			ft_printf("Found slash\n");
		}
		i++;
	}
	if (last_slash)
		return (last_slash + 1);
	return (name);
}

t_file	*init_file(struct dirent *dirent, const char *path)
{
	t_file	*to_return;
	char	*full_path;

	to_return = ft_calloc(sizeof(*to_return), 1);
	if (!to_return)
		return (NULL);
	if (dirent)
	{
		to_return->ent = ft_calloc(sizeof(struct dirent), 1);
		if (!to_return->ent)
		{
			free(to_return);
			return (NULL);
		}
		to_return->ent = ft_memcpy(to_return->ent, dirent, sizeof(*dirent));
		to_return->path = ft_strdup(dirent->d_name);

		full_path = ft_calloc(sizeof(char), 1000);
		ft_strlcat(full_path, path, 1000);
		ft_strlcat(full_path, "/", 1000);
		ft_strlcat(full_path, dirent->d_name, 1000);
	}
	else
	{
		to_return->path = ft_strdup(ft_basename((char *)path));
		full_path = ft_strdup(path);
	}
	to_return->statbuf = ft_calloc(sizeof(struct stat), 1);
	if (!to_return->statbuf)
	{
		free(to_return->ent);
		free(full_path);
		free(to_return);
		return (NULL);
	}
	int lstatres = lstat(full_path, to_return->statbuf);
	if (lstatres < 0)
	{
		free(to_return->ent);
		free(to_return->statbuf);
		free(full_path);
		free(to_return);
		return (NULL);
	}
	ft_bzero(to_return->flags_rights, 12);
	get_flags(to_return);
	free(full_path);
	return (to_return);
}
