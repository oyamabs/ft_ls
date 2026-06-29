/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 16:44:29 by tchampio          #+#    #+#             */
/*   Updated: 2026/06/29 17:38:32 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include "../libft/includes/libft.h"

char	*pad_right(char *str, int max_len)
{
	int		len;
	int		spaces_needed;
	char	*res;

	len = ft_strlen(str);
	spaces_needed = max_len - len;
	if (spaces_needed <= 0)
		return (ft_strdup(str));
	res = ft_calloc(sizeof(char), max_len + 1);
	if (!res)
		return (NULL);
	ft_memset(res, ' ', spaces_needed);
	ft_strlcat(res, str, max_len + 1);
	return (res);
}

char	*pad_left(char *str, int max_len)
{
	int		len;
	char	*res;

	len = ft_strlen(str);
	if (max_len < len)
		max_len = len;
	res = ft_calloc(sizeof(char), max_len + 1);
	if (!res)
		return (NULL);
	ft_strlcat(res, str, max_len + 1);
	while (len < max_len)
	{
		res[len] = ' ';
		len++;
	}
	return (res);
}

t_width	get_widths(t_list *files)
{
	t_width	w;
	t_list	*current;
	char	*tmp;

	ft_bzero(&w, sizeof(w));
	current = files;
	while (current != NULL)
	{
		t_file	*f = (t_file *)current->content;
		if (f && f->statbuf)
		{
			tmp = ft_itoa(f->statbuf->st_nlink);
			if ((int)ft_strlen(tmp) > w.max_nlink) w.max_nlink = ft_strlen(tmp);
			free(tmp);

			struct passwd *pw = getpwuid(f->statbuf->st_size);
			struct group *gw = getgrgid(f->statbuf->st_gid);
			if (pw && (int)ft_strlen(pw->pw_name) > w.max_user) w.max_user = ft_strlen(pw->pw_name);
			if (gw && (int)ft_strlen(gw->gr_name) > w.max_group) w.max_group = ft_strlen(gw->gr_name);
			
			tmp = ft_itoa(f->statbuf->st_size);
			if ((int)ft_strlen(tmp) > w.max_size) w.max_size = ft_strlen(tmp);
			free(tmp);
		}
		current = current->next;
	}
	return (w);
}

void	print_file_aligned(t_file *f, t_width w, char *time_str)
{
	struct passwd *passbuf = getpwuid(f->statbuf->st_uid);
	struct group  *groupbuf = getgrgid(f->statbuf->st_gid);
	char *u_name = (passbuf) ? passbuf->pw_name : "unknown";
	char *g_name = (groupbuf) ? groupbuf->gr_name : "unknown";

	char *s_nlink = ft_itoa(f->statbuf->st_nlink);
	char *pad_nlink = pad_right(s_nlink, w.max_nlink);

	char *pad_user = pad_left(u_name, w.max_user);
	char *pad_group = pad_left(g_name, w.max_group);

	char *s_size = ft_itoa(f->statbuf->st_size);
	char *pad_size = pad_right(s_size, w.max_size);

	if (f->points_to)
	{
		ft_printf("%s %s %s %s %s %s %s -> %s\n", 
			f->flags_rights, pad_nlink, pad_user, pad_group, 
			pad_size, time_str, f->path, f->points_to);
	}
	else
	{
		ft_printf("%s %s %s %s %s %s %s\n", 
			f->flags_rights, pad_nlink, pad_user, pad_group, 
			pad_size, time_str, f->path);
	}

	free(s_nlink);
	free(pad_nlink);
	free(pad_user);
	free(pad_group);
	free(s_size);
	free(pad_size);
}

void print_file_tree(t_file_tree *tree, int level)
{
    if (!tree)
        return;

    t_list *current_file = tree->files;
	t_width widths = get_widths(current_file);
    while (current_file != NULL)
    {
        t_file *file = (t_file *)current_file->content;
        if (file)
		{
			for (int i = 0; i < level; i++)
				ft_printf("    ");
			char time_str[30];
			time_t now;
			time_t file_time;
			char	*date_ctime;

			file_time = file->statbuf->st_mtim.tv_sec;
			date_ctime = ctime(&file_time);
			time(&now);

			// if file is older than 6 months
			if ((now - file_time) > 15778800 || (file_time - now) > 15778800)
			{
				ft_memcpy(time_str, date_ctime + 4, 7);
				time_str[6] = ' ';
				time_str[7] = ' ';
				ft_memcpy(time_str + 8, date_ctime + 20, 4);
				time_str[12] = '\0';
			}
			else
			{
				ft_memcpy(time_str, date_ctime + 4, 12);
				time_str[12] = '\0';
			}
			print_file_aligned(file, widths, time_str);
        }
        current_file = current_file->next;
    }
    t_list *current_sub = tree->subdirectories;
    while (current_sub != NULL)
    {
        t_file_tree *subtree = (t_file_tree *)current_sub->content;
        if (subtree)
        {
            for (int i = 0; i < level; i++)
                ft_printf("    ");
            ft_printf("📁 [Dossier: %s]:\n", subtree->path);
            print_file_tree(subtree, level + 1);
        }
        current_sub = current_sub->next;
    }
}
