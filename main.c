#include "term3d.h"

void	ft_show_point_list(t_list *point_list);

int	main(int argc, char **argv)
{
	t_list *point_list;

	if (argc == 1)
		return (0);
	point_list= get_point_list(argv[1]);
	ft_show_point_list(point_list);
	ft_lstclear(&point_list, &free);
	return (0);
}


void	ft_show_point_list(t_list *point_list)
{
	t_list *current;
	t_point *point;

	current = point_list;
	while (current) {
		point = (t_point*)current->content;
		printf("x: %lf, y: %lf, z: %lf\n", point->x, point->y, point->z);
		current = current->next;
	}
}

//ファイル読み込みについて
	//

//画素数圧縮
	//x,y,zの情報がきちんと取れるようにしておく→回転とかへの対応のため
	//