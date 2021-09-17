#include "push_swap.h"

void	free_split(void *data)
{
	size_t	i;
	char 	**arg_sp;

	i = 0;
	arg_sp = (char **)data;
	while (arg_sp[i])
	{
		free(arg_sp[i]);
		i++;
	}
	free(arg_sp);
}

void	free_stack(void *data)
{
	t_dlist	*stack;

	stack = (t_dlist *)data;
    ft_dlst_clear(&stack, &free);
}

void exit_error(size_t err, void *strct, free_func f, t_stck_data *data)
{
	if (strct)
		f(strct);
	if (data)
	{
		if (data->arr_sorted)
			free(data->arr_sorted);
		free(data);
	}
	exit (err);
}

void	check_input(int argc, char *argv[], t_stck_data *data)
{
	int		i;
	int		j;
	char	**arg_sp;
    int     ovflw;
	
	i = 0;
	data->size = 0;
	while (++i < argc)
	{
		arg_sp = ft_split(argv[i], ' ');
		if (!arg_sp)
			exit_error(3, NULL, NULL, data);
		j = -1;
		while (arg_sp[++j])
		{
			ft_atoi_base(arg_sp[j], "0123456789", "\0", &ovflw);
            if (ovflw)
                exit_error(1, (void *)arg_sp, &free_split, data);
		}
		data->size += j;
		free_split(arg_sp);
	}
	if (!data->size)
		exit_error(0, NULL, NULL, data);
	data->i_A = data->size;
	data->i_B = 0;
}

