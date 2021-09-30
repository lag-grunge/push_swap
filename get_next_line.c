#include "push_swap.h"

int	get_next_line(char **line)
{
	char	*buf;
	int		ret;
	size_t	i;

	i = 0;
	buf = ft_calloc((MAX_COMMAND_LENGTH + 2), sizeof(char));
	if (!buf)
		return (-1);
	ret = read(0, buf, 1);
	if (ret == -1)
		return (-1);
	while (ret == 1)
	{
		if (buf[i] == 10)
			break ;
		ret = read(0, buf + ++i, 1);
	}
	if (ret == -1)
		return (-1);
	if (i > MAX_COMMAND_LENGTH + 1)
		i = MAX_COMMAND_LENGTH + 1;
	buf[i] = 0;
	*line = buf;
	return (ret);
}
