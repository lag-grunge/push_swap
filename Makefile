NAME = push_swap

NAME_2 = checker

SRCS = 	ft_dlst/ft_dlst.c \
		input.c sorted_array.c \
	   	init_stack.c operations.c \
		both_operations.c \
		commands.c get_pos_val.c \
		small_size.c \
		print_stack.c get_next_line.c \
		sort.c \
		asipes_sort.c asipes_utils.c asipes_utils_two.c \
		merge_sort.c \
		radix_sort.c \

OBJS = ${SRCS:.c=.o}

LIB_DIR = ./libft

LIBFT = libft.a

CFLAGS = -g -Wall -Wextra -Werror

INCLUDE = -I${LIB_DIR} -I./ft_dlst

all : ${LIBFT} ${NAME} ${NAME_2}

${NAME} : main.c ${OBJS}
	gcc ${CFLAGS} ${INCLUDE} $^ -L${LIB_DIR} -lft -o $@

${NAME_2} : checker.c ${OBJS}
	gcc ${CFLAGS} ${INCLUDE} $^ -L${LIB_DIR} -lft -o $@

${OBJS} : %.o : %.c
	gcc ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o} -I${LIB_DIR} 

${LIBFT} : ${LIB_DIR}
	make all bonus -C ${LIB_DIR}

clean :
	rm ${OBJS}

fclean : clean 
	rm ${NAME} ${NAME_2}

re :	fclean all

.PHONY : re clean fclean all
