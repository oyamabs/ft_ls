/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:49:59 by tchampio          #+#    #+#             */
/*   Updated: 2026/05/05 14:51:33 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "types.h"
#include "arguments/arguments.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int	main(int argc, char **argv)
{
	int	i;
	t_arguments	args;
	init_arguments(&args, argc, argv);
	i = 0;
	while (i < args.number_of_files)
	{
		printf("%s ", args.filenames[i]);
		if (args.filenames[i])
			free(args.filenames[i]);
		i++;
	}
	free(args.filenames);
}
