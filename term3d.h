#ifndef TERM3D_H_
# define TERM3D_H_


# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>
# include "get_next_line.h"
# include "libft.h"


# define BUFFER_SIZE 512

# define ERROR -1
# define SUCCESS 1

typedef struct s_point {
  double x;
  double y;
  double z;
} t_point;

t_list	*get_point_list(char *file_path);

int     get_terminal_size(unsigned int *row, unsigned int *col);

#endif