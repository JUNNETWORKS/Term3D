/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 02:22:45 by jtanaka           #+#    #+#             */
/*   Updated: 2022/02/16 01:07:41 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# define GNL_SUCCESS		1
# define GNL_END_OF_FILE	0
# define GNL_ERROR			-1
# define GNL_CONTINUE_READ	-2

# define GNL_BUFFER_SIZE 256

typedef struct s_gnl_list
{
	int					fd;
	char				*save;
	struct s_gnl_list	*next;
}				t_gnl_list;

int				get_next_line(int fd, char **line);
t_gnl_list		*create_fd_elem(t_gnl_list **lst, int fd);
void			remove_fd_elem(t_gnl_list **list_head, t_gnl_list *target_elem);

#endif
