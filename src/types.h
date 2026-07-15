/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 16:02:20 by tchampio          #+#    #+#             */
/*   Updated: 2026/07/15 15:43:32 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "../libft/includes/libft.h"

/*
    t_flags binary definition
    0000.0000 0001.0100
              ^^^^ ^^^^
                 | |||\ -R
                 | ||\ -a
           	     | |\ -l
           	     | \ -r
                 \ -t
*/
typedef unsigned short	t_flags;

enum e_argument_flags
{
	ARG_RECURSIVE = 0,
	ARG_HIDDEN = 1,
	ARG_LIST = 2,
	ARG_REVERSE = 3,
	ARG_TIME = 4
};

typedef struct s_arguments
{
	t_flags	flags;
	int		number_of_files;
	char	**filenames;
}	t_arguments;

typedef struct s_file
{
	char			flags_rights[12];
	struct dirent	*ent;
	struct stat		*statbuf;
	char			*points_to; //symlink?
	char			*path;
}	t_file;

typedef struct s_width
{
	int	max_nlink;
	int	max_user;
	int	max_group;
	int	max_size;
}	t_width;

typedef struct s_file_tree
{
	char				*path;
	t_width				*width;
	struct stat			*statbuf;
	t_list				*files;
	t_list				*subdirectories;
}	t_file_tree;

#endif // TYPES_H
