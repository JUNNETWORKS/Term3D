#include "term3d.h"
#include <sys/ioctl.h>
#include <unistd.h>

int get_terminal_size(unsigned int *row, unsigned int *col)
{
	struct winsize w;
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
		return (-1);
	*row = w.ws_row;
	*col = w.ws_col;
	return (0);
}