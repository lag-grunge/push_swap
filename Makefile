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
		radix_sort.c

HEADER = push_swap.h

MERGE_SRCS_LIST = merge_sort.c flags.c flags_two.c \
		init_pair_chunks.c oper_n_chunks.c \
		find_size.c execute_n_command.c \
		init_data_flags_and_stacks.c
MERGE_SRCS = ${addprefix ${MERGE_DIR}/, ${MERGE_SRCS_LIST}}
MERGE_HEADER = ${MERGE_DIR}/merge_sort.h

OBJS = ${SRCS:.c=.o}
MERGE_OBJS = ${MERGE_SRCS:.c=.o}

CFLAGS = -g -Wall -Wextra -Werror
INCLUDE = -I. -I${LIB_DIR} -I${LIB_DLST_DIR} -I${MERGE_DIR}
LIBRARIES = -L${LIB_DIR} -lft

all : ${LIBFT} ${NAME}

${NAME} : main.c ${OBJS} ${MERGE_OBJS}
	gcc ${CFLAGS} $^ ${LIBRARIES} -o $@

${NAME_2} : checker.c ${OBJS} ${MERGE_OBJS}
	gcc ${CFLAGS} $^ ${LIBRARIES} -o $@

${MERGE_OBJS} : %.o : %.c ${MERGE_HEADER}
	gcc ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

${OBJS} : %.o : %.c ${HEADER}
	gcc ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

${LIBFT} : ${LIB_DIR}
	make all bonus -C ${LIB_DIR}

clean :
	rm ${OBJS} ${MERGE_OBJS}

fclean : clean 
	rm ${NAME} ${NAME_2}

re :	fclean all

.PHONY : re clean fclean all
