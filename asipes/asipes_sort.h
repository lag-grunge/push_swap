#ifndef ASIPES_SORT_H
# define ASIPES_SORT_H

typedef struct s_cmn_asip_data {
	size_t	size;
	size_t	max;
	size_t	mid;
	size_t	next;
	size_t	flag;
	t_comnd	*cmd_array;
	char	**op_lines;
	t_dlist	**stack_A;
	t_dlist	**stack_B;
}				t_cmn_asip_data;

void	asip_fl_change(t_dlist **stack_A);
void	restore_data_max_mid(t_cmn_asip_data *data);
int		correctAchain(t_dlist **stack_A, t_cmn_asip_data *data);
int		operBelem(t_cmn_asip_data *data, int sec);
void	init_data(t_cmn_asip_data *cmn_data, t_stck_data *data);
void	restore_size(t_cmn_asip_data *cmn_data, t_stck_data *data);
void	exec_n_cmd_asip(int cmd_num, size_t n, t_cmn_asip_data *data);

#endif
