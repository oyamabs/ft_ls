/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 14:08:28 by tchampio          #+#    #+#             */
/*   Updated: 2026/06/22 12:00:07 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "types.h"

t_file	*init_file(struct dirent *dirent, const char *path);
void	print_file(t_file *f);
void	print_file_tree(t_file_tree *tree, int level);
char	*ft_basename(char *name);

#endif // UTILS_H
