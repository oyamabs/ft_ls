/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:47:30 by tchampio          #+#    #+#             */
/*   Updated: 2026/05/18 15:50:42 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include "../../libft/includes/libft.h"
#include <stdlib.h>

#ifndef EXPLORE_H
# define EXPLORE_H

void	enter_directory(struct dirent *t, const char *name);
void	recursively_explore(DIR *dp, struct dirent *t, const char *name);

#endif // EXPLORE_H
