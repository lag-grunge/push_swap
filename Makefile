NAME = push_swap

NAME_2 = checker

LIB_DIR = ./libft
LIB_DLST_DIR = ${LIB_DIR}/ft_dlst
MERGE_DIR = ./merge
LIBFT = libft.a

SRCS = 	input.c sorted_array.c \
	   	init_stack.c init_stack_utils.c \
	   	operations.c both_operations.c \
		commands.c get_pos_val.c \
		small_size.c \
		print_stack.c get_next_line.c \
		sort.c \
		asipes_sort.c asipes_utils.c asipes_utils_two.c \
		${MERGE_DIR}/merge_sort.c ${MERGE_DIR}/merge_utils.c \
		${MERGE_DIR}/merge_utils_two.c ${MERGE_DIR}/merge_utils_3rd.c \
		radix_sort.c \

OBJS = ${SRCS:.c=.o}

CFLAGS = -g -Wall -Wextra -Werror

INCLUDE = -I. -I${LIB_DIR} -I${LIB_DLST_DIR} -I${MERGE_DIR}

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
