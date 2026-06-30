/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 14:08:28 by tchampio          #+#    #+#             */
/*   Updated: 2026/06/30 16:07:15 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "types.h"

t_file	*init_file(struct dirent *dirent, const char *path, bool is_individual_file);
void	print_file(t_file *f);
void	print_file_tree(t_file_tree *tree, int level, t_width global_width);
char	*ft_basename(char *name);
void    accumulate_widths(t_width *w, t_list *files);

#endif // UTILS_H
