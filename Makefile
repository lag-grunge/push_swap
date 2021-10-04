ifndef NAME
NAME = push_swap
endif
NAME_2 = checker

LIB_DIR = ./libft
LIB_DLST_DIR = ${LIB_DIR}/ft_dlst
MERGE_DIR = ./merge
ASIPES_DIR = ./asipes
LIBFT = libft.a
LIB_SORT = libsort.a

SRCS = 	input.c input_utils.c \
		sorted_array.c \
	   	init_stack.c init_stack_utils.c \
	   	operations.c both_operations.c \
		commands.c get_pos_val.c \
		small_size.c get_next_line.c

HEADER = push_swap.h

ASIPES_SRCS_LIST = asipes_sort.c asipes_utils.c asipes_utils_two.c
ASIPES_SRCS = ${addprefix ${ASIPES_DIR}/, ${ASIPES_SRCS_LIST}}
ASIPES_HEADER = ${ASIPES_DIR}/asipes_sort.h

MERGE_SRCS_LIST = merge_sort.c flags.c flags_two.c \
		init_pair_chunks.c oper_n_chunks.c \
		find_size.c execute_n_command.c \
		init_data_flags_and_stacks.c
MERGE_SRCS = ${addprefix ${MERGE_DIR}/, ${MERGE_SRCS_LIST}}
MERGE_HEADER = ${MERGE_DIR}/merge_sort.h

RADIX_SRCS = radix_sort.c

SORT_SRCS = sort.c

OBJS = ${SRCS:.c=.o}
MERGE_OBJS = ${MERGE_SRCS:.c=.o}
ASIPES_OBJS = ${ASIPES_SRCS:.c=.o}
SORT_OBJS = ${SORT_SRCS:.c=.o}
RADIX_OBJS = ${RADIX_SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I. -I${LIB_DIR} -I${LIB_DLST_DIR} -I${MERGE_DIR}
LIBRARIES = -L${LIB_DIR} -lft

all : ${LIBFT} ${LIB_SORT} ${NAME} ${NAME_2}

${NAME} : main.c ${OBJS} ${SORT_OBJS} ${LIB_SORT}
	gcc ${CFLAGS} $^ ${LIBRARIES} -lsort -L. -DIS_CHECKER=0 -o $@

${NAME_2} : checker.c ${OBJS}
	gcc ${CFLAGS} $^ ${LIBRARIES} -DIS_CHECKER=1 -o $@

${MERGE_OBJS} : %.o : %.c ${MERGE_HEADER} ${HEADER}
	gcc ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}
	ar rcs ${LIB_SORT} $@

${ASIPES_OBJS} : %.o : %.c ${ASIPES_HEADER} ${HEADER}
	gcc ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

${LIB_SORT} : ${ASIPES_OBJS} ${MERGE_OBJS} ${RADIX_OBJS}
	ar rcs ${LIB_SORT} $^

${OBJS} : %.o : %.c ${HEADER}
	gcc ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

${SORT_OBJS} : %.o : %.c ${HEADER}
	gcc ${CFLAGS} ${INCLUDE} -DALGO_BORDER=385 -c $< -o ${<:.c=.o}

${LIBFT} : ${LIB_DIR}
	make all -C ${LIB_DIR}

clean :
	@make clean -C ${LIB_DIR}
	@rm -rf ${OBJS} ${MERGE_OBJS} ${ASIPES_OBJS} ${SORT_OBJS}

fclean :
	@make clean
	@rm -rf ${LIBFT}
	@rm -rf ${NAME} ${NAME_2} ${LIB_SORT}

re :	fclean all

.PHONY : re clean fclean all
