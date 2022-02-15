#include "term3d.h"

static t_list		*get_list_of_point_from_fd(int fd);
static t_point*		parse_point(char *line);

t_list	*get_point_list(char *file_path)
{
	int		fd;
	t_list	*list_head;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	list_head = get_list_of_point_from_fd(fd);
	close(fd);
	return (list_head);
}

static t_list *get_list_of_point_from_fd(int fd)
{
	char	*line;
	int		status;
	t_point	*point;
	t_list	*list_head;
	
	status = SUCCESS;
	list_head = NULL;
	while (status == SUCCESS)
	{
		status = get_next_line(fd, &line);
		if (line)
			point = parse_point(line);
		if (line == NULL || point == NULL) 
			return (ft_lstclear_and_return_null(&list_head, &free));
		free(line);
		ft_lstadd_back_new(&list_head, point);
	}
	if (status == ERROR)
		return (ft_lstclear_and_return_null(&list_head, &free));
	return (list_head);
}

static t_point* parse_point(char *line)
{
	char	**str_arr;
	char	*endptr;
	size_t	i;
	double	xyz[3];
	t_point	*point;
	
	str_arr = ft_split(line, ',');
	i = 0;
	while (str_arr && i < 3)
	{
		xyz[i] = strtod(str_arr[i], &endptr);
		if (*endptr != '\0')
			break;
		i++;
	}
	free_ptrarr((void**)str_arr);
	if (str_arr == NULL || i != 3)
		return (NULL);
	point = malloc(sizeof(t_point));
	if (point == NULL)
		return (NULL);
	point->x = xyz[0];
	point->y = xyz[1];
	point->z = xyz[2];
	return (point);
}

