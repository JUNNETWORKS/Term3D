/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 02:22:38 by jtanaka           #+#    #+#             */
/*   Updated: 2022/02/16 01:07:49 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	join_line_from_save(char **line, char **save)
{
	char	*tmp;

	if (ft_strchr(*save, '\n'))
	{
		tmp = *line;
		*line = ft_substr(*save, 0, ft_strchr(*save, '\n') - *save);
		free(tmp);
		if (!(*line))
			return (GNL_ERROR);
		tmp = *save;
		*save = ft_substr(ft_strchr(*save, '\n') + 1, 0,
				ft_strlen(ft_strchr(*save, '\n') + 1));
		free(tmp);
		if (!(*save))
			return (GNL_ERROR);
		return (GNL_SUCCESS);
	}
	else
	{
		tmp = *line;
		*line = *save;
		*save = NULL;
		free(tmp);
		return (GNL_CONTINUE_READ);
	}
}

static int	split_by_newline(char **line, char **save, char *buf)
{
	char	*old_line;
	char	*tmp;

	tmp = ft_substr(buf, 0, ft_strchr(buf, '\n') - buf);
	if (!tmp)
		return (GNL_ERROR);
	old_line = *line;
	*line = ft_strjoin(*line, tmp);
	free(old_line);
	free(tmp);
	if (!(*line))
		return (GNL_ERROR);
	*save = ft_substr(ft_strchr(buf, '\n') + 1, 0,
			ft_strlen(ft_strchr(buf, '\n') + 1));
	if (!(*save))
		return (GNL_ERROR);
	return (GNL_SUCCESS);
}

static int	join_line_and_buf(char **line, char *buf)
{
	char	*tmp;

	tmp = *line;
	*line = ft_strjoin(*line, buf);
	free(tmp);
	if (!(*line))
		return (GNL_ERROR);
	return (GNL_CONTINUE_READ);
}

static int	read_process(int fd, char **line, char **save)
{
	ssize_t		read_size;
	int			ret;
	char		*buf;

	ret = GNL_CONTINUE_READ;
	buf = malloc(GNL_BUFFER_SIZE + 1);
	if (!buf)
		return (GNL_ERROR);
	while (ret == GNL_CONTINUE_READ)
	{
		read_size = read(fd, buf, GNL_BUFFER_SIZE);
		if (read_size <= 0)
			break ;
		buf[read_size] = '\0';
		if (ft_strchr(buf, '\n'))
			ret = split_by_newline(line, save, buf);
		else
			ret = join_line_and_buf(line, buf);
	}
	free(buf);
	if (ret == GNL_CONTINUE_READ && read_size == 0)
		ret = GNL_END_OF_FILE;
	else if (ret == GNL_CONTINUE_READ && read_size == -1)
		ret = GNL_ERROR;
	return (ret);
}

int	get_next_line(int fd, char **line)
{
	int					ret;
	static t_gnl_list	*save_list_head;
	t_gnl_list			*target_save_list;

	*line = ft_calloc(1, sizeof(char));
	if (fd < 0 || !line || GNL_BUFFER_SIZE <= 0 || !(*line))
		return (GNL_ERROR);
	target_save_list = save_list_head;
	while (target_save_list && target_save_list->fd != fd)
		target_save_list = target_save_list->next;
	if (!target_save_list)
	{
		target_save_list = create_fd_elem(&save_list_head, fd);
		if (!target_save_list)
			return (GNL_ERROR);
	}
	ret = GNL_CONTINUE_READ;
	if (target_save_list->save)
		ret = join_line_from_save(line, &target_save_list->save);
	if (ret == GNL_CONTINUE_READ)
		ret = read_process(fd, line, &target_save_list->save);
	if (ret == GNL_END_OF_FILE || ret == GNL_ERROR)
		remove_fd_elem(&save_list_head, target_save_list);
	return (ret);
}
