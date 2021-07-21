#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

typedef struct s_stack	{
	int	*arr;
	size_t top;
	size_t cap;
	struct s_stack *peer;
}				t_stack;


#endif
