/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 14:12:55 by tchampio          #+#    #+#             */
/*   Updated: 2026/08/04 17:35:13 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORT_H
# define SORT_H

# include "types.h"

void	sort_tree(t_file_tree *tree, t_arguments args);
void	reverse_tree(t_file_tree *tree);

#endif // SORT_H
