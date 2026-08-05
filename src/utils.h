/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 14:08:28 by tchampio          #+#    #+#             */
/*   Updated: 2026/08/05 20:03:24 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# define PROGNAME "ft_ls" // FIXME: change to ft_ls

# include "types.h"

t_file	*init_file(struct dirent *dirent, const char *path, bool is_individual_file);
void	print_file(t_file *f);
void	print_file_tree(t_file_tree *tree, int level, t_width global_width, t_arguments arguments);
char	*ft_basename(char *name);
void    accumulate_widths(t_file_tree *tree, t_arguments args);

#endif // UTILS_H
