/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 16:04:17 by tchampio          #+#    #+#             */
/*   Updated: 2026/05/20 16:21:48 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include <dirent.h>
#include "../libft/includes/libft.h"

void	print_file(t_file *f)
{
	if (!f->dirent)
		return ;
		ft_printf("Info of t_file: %p\nInode: %d\nMode: %d\nRights: %s\nType: %d\nName: %s\n", f, f->dirent->d_ino, f->flags_rights, f->dirent->d_type, f->dirent->d_name);
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

void	get_flags(t_file *file)
{
	// man stat(3)
	struct stat *stat;

	if (stat())
}

t_file	*init_file(struct dirent *dirent)
{
	t_file	*to_return;

	to_return = malloc(sizeof(*to_return));
	if (!to_return)
		return (NULL);
	to_return->dirent = dirent;
	get_flags(to_return);
	return (to_return);
}
