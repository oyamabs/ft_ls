/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 16:04:17 by tchampio          #+#    #+#             */
/*   Updated: 2026/05/26 16:51:28 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include <dirent.h>
#include "../libft/includes/libft.h"

void	print_file(t_file *f)
{
	if (!f || !f->ent)
		return ;
	ft_printf("Info of t_file: %p\nInode: %d\nMode: %d\nRights: %s\nType: %d\nName: %s\n", f, f->ent->d_ino, f->ent->d_type,/* f->flags_rights */ "caca",  f->ent->d_type, f->path);
	ft_printf("THIS IS THE NAME FFS: %s\n", f->path);
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

// void	get_flags(t_file *file)
// {
// 	// man stat(3)
// 	struct stat *stat;
// 
// 	if (stat())
// }

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

	//get_flags(to_return);
	return (to_return);
}
