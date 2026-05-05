/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 22:05:17 by tchampio          #+#    #+#             */
/*   Updated: 2026/05/05 14:56:34 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flags.h"
#include <stdio.h>
#include <stdlib.h>
#include "../types.h"
#include "../../libft/includes/libft.h"

void	copy_filenames(t_arguments *args, int ac, char **av)
{
	int			i;
	int			j;

	if (args->number_of_files == 0)
	{
		args->filenames[0] = ft_strdup(".");
		args->number_of_files = 1;
		return ;
	}
	i = 1;
	j = 0;
	while (i < ac)
	{
		if (av[i][0] != '-')
			args->filenames[j++] = ft_strdup(av[i]);
		i++;
	}
}

void	init_arguments(t_arguments *arguments, int ac, char **av)
{
	int	filenum;
	int	current_ac;

	filenum = 0;
	current_ac = 1;
	ft_bzero(arguments, sizeof(*arguments));
	while (current_ac < ac)
	{
		if (av[current_ac][0] != '-')
			filenum++;
		current_ac++;
	}
	arguments->number_of_files = filenum;
	ft_printf("number of files: %d\n", filenum);
	if (filenum > 0)
		arguments->filenames = malloc(sizeof(*arguments->filenames) * filenum);
	else
		arguments->filenames = malloc(sizeof(*arguments->filenames));
	if (!arguments->filenames)
	{
		perror("ft_ls");
		exit(1);
	}
	arguments->flags = check_flags_arguments(ac, av);
	copy_filenames(arguments, ac, av);
}
