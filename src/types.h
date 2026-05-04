/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 16:02:20 by tchampio          #+#    #+#             */
/*   Updated: 2026/05/04 19:10:55 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

/*
	0000.0000 0001.0100
              ^^^^ ^^^^
                 | |||\ -R
                 | ||\ -a
           	     | |\ -l
           	     | \ -r
                 \ -t
*/
typedef unsigned short t_args;
enum e_argument_flags {
	ARG_RECURSIVE = 0,
	ARG_HIDDEN = 1,
	ARG_LIST = 2,
	ARG_REVERSE = 3,
	ARG_TIME = 4
};

#endif // TYPES_H
