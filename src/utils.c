/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 16:04:17 by tchampio          #+#    #+#             */
/*   Updated: 2026/06/01 18:18:58 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../libft/includes/libft.h"

void	print_file(t_file *f)
{
	if (!f || !f->ent)
		return ;
	//ft_printf("Info of t_file: %p\nInode: %d\nMode: %d\nRights: %s\nType: %d\nName: %s\n", f, f->ent->d_ino, f->ent->d_type, f->flags_rights,  f->ent->d_type, f->path);
	ft_printf("%s %d %s %s %d %d %d %d:%d %s\n", f->flags_rights, 420, "caca", "prout", 69, "Pet", 1, 20, 9, f->ent->d_name);
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
	struct stat *statbuf;
	int			mode;

	statbuf = malloc(sizeof(*statbuf));
	if (stat(file->path, statbuf) < 0)
	{
		perror("ft_ls");
		return ;
	}
	mode = statbuf->st_mode;
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

t_file	*init_file(struct dirent *dirent, const char *path)
{
	t_file	*to_return;
	char	*tmp;

	if (!dirent)
		return (NULL);
	to_return = malloc(sizeof(*to_return));
	if (!to_return)
		return (NULL);
	to_return->ent = dirent;
	tmp = ft_calloc(sizeof(char), 1000);
	ft_strlcat(tmp, path, 1000);
	ft_strlcat(tmp, "/", 1000);
	ft_strlcat(tmp, dirent->d_name, 1000);
	to_return->path = ft_strdup(tmp);
	free(tmp);
	ft_bzero(to_return->flags_rights, 12);
	get_flags(to_return);
	return (to_return);
}
