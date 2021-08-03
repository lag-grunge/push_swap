#include "push_swap.h"

int	get_next_line(char **line)
{
	char *buf;
	int ret;
	size_t i;

	i = 0;
	buf = malloc(sizeof(char) * 4);
	*line = buf;
	ret = read(0, buf, 1);
	while (ret)
	{
		if (buf[i] ==  10)
				break ;
		ret = read(0, buf + ++i, 1);
	}
	buf[i] = 0;
	return (ret);
}
