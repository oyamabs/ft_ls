/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:47:30 by tchampio          #+#    #+#             */
/*   Updated: 2026/05/20 12:53:04 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPLORE_H
# define EXPLORE_H

# include <sys/types.h>
# include <dirent.h>
# include "../../libft/includes/libft.h"
# include <stdlib.h>
# include "../types.h"

void	enter_directory(struct dirent *t, const char *name, t_file_tree *tree);
void	recursively_explore(DIR *dp, struct dirent *t, const char *name, t_file_tree *tree);

#endif // EXPLORE_H
