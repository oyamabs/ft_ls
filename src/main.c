/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:49:59 by tchampio          #+#    #+#             */
/*   Updated: 2026/05/04 19:46:02 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "types.h"
#include "arguments/flags.h"
#include <stdlib.h>
#include <stdbool.h>

int	main(int argc, char **argv)
{
	t_args	args;
	
	args = check_flags_arguments(argc, argv);
	bool l, a, r, t, R;
	l = args & (1 << 2);
	a = args & (1 << 1);
	r = args & (1 << 3);
	t = args & (1 << 4);
	R = args & (1 << 0);
	ft_printf("Flags value: %d\n", args);
	ft_printf("-l ? %d\n", l);
	ft_printf("-r ? %d\n", r);
	ft_printf("-a ? %d\n", a);
	ft_printf("-t ? %d\n", t);
	ft_printf("-R ? %d\n", R);
}
