ifndef NAME
NAME = push_swap
endif
NAME_2 = checker
NAME_DEBUG = push_swap_debug


LIB_DIR = ./libft
LIB_DLST_DIR = ${LIB_DIR}/ft_dlst
MERGE_DIR = ./merge
ASIPES_DIR = ./asipes
DISTANCE_DIR = ./distance
LIBFT = libft.a
LIB_SORT = libsort.a

SRCS = 	input.c input_utils.c \
		sorted_array.c \
	   	init_stack.c init_stack_utils.c \
	   	operations.c both_operations.c \
		commands.c \
		get_pos_val.c get_next_line.c

HEADER = push_swap.h

SMALL_SRCS = small_size.c 

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

DISTANCE_SRCS_LIST = distance.c distance_utils.c distance_utils_two.c
DISTANCE_SRCS = ${addprefix ${DISTANCE_DIR}/, ${DISTANCE_SRCS_LIST}}
DISTANCE_HEADER = ${DISTANCE_DIR}/distance.h

SORT_SRCS = sort.c

#DEBUG_SRCS = debug.c

OBJS = ${SRCS:.c=.o}
SMALL_OBJS = small_size.o
MERGE_OBJS = ${MERGE_SRCS:.c=.o}
DISTANCE_OBJS = ${DISTANCE_SRCS:.c=.o}
ASIPES_OBJS = ${ASIPES_SRCS:.c=.o}
SORT_OBJS = sort.o
RADIX_OBJS = radix_sort.o
#DEBUG_OBJS = debug.o

DEPS = ${OBJS:.o=.d} ${SMALL_OBJS:.o=.d} ${MERGE_OBJS:.o=.d} ${DISTANCE_OBJS:.o=.d} \
	${ASIPES_OBJS:.o=.d} ${SORT_OBJS:.o=.d} ${RADIX_OBJS:.o=.d} \
	${NAME}.d ${NAME_2}.d ${NAME_DEBUG}.d #${DEBUG_OBJS:.o=.d}

CFLAGS := -Wall -Wextra -Werror -MMD
INCLUDE = -I. -I${LIB_DIR} -I${LIB_DLST_DIR} -I${MERGE_DIR}
LIBRARIES = -L${LIB_DIR} -lft

all : ${LIBFT} ${LIB_SORT} ${NAME} ${NAME_2}
dbg : ${NAME_DEBUG} ${NAME_2}
dbg : CFLAGS += -g -fsanitize=address
dbg : DEBUG=1
dbg : LIBRARIES += -lasan

${NAME} : main.c ${OBJS} ${SORT_OBJS} ${LIB_SORT} #$(if DEBUG,${DEBUG_OBJS},)
	gcc ${CFLAGS} $^ -DIS_CHECKER=0 -o $@ ${LIBRARIES}
${NAME_DEBUG} : main.c ${OBJS} ${SORT_OBJS} ${LIB_SORT} #$(if DEBUG,${DEBUG_OBJS}) 
	gcc ${CFLAGS} $^ -DIS_CHECKER=0 -o $@ ${LIBRARIES}

${NAME_2} : checker.c ${OBJS}
	gcc ${CFLAGS} $^ -DIS_CHECKER=1 -o $@ ${LIBRARIES}

${LIB_SORT} : ${SMALL_OBJS} ${ASIPES_OBJS} ${MERGE_OBJS} ${RADIX_OBJS} ${DISTANCE_OBJS}
	ar rcs ${LIB_SORT} $^

${LIBFT} : ${LIB_DIR}
	make all -C ${LIB_DIR}

${RADIX_OBJS} ${OBJS} ${SMALL_OBJS} ${MERGE_OBJS} ${ASIPES_OBJS} ${DISTANCE_OBJS} : %.o : %.c
	gcc ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

#${DEBUG_OBJS} : %.o : %.c
#	gcc ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

${SORT_OBJS} : %.o : %.c
	gcc ${CFLAGS} ${INCLUDE} -DALGO_BORDER=385 -c $< -o ${<:.c=.o}

clean :
	@make clean -C ${LIB_DIR}
	@rm -rf ${OBJS} ${SMALL_OBJS} ${MERGE_OBJS} ${ASIPES_OBJS} ${SORT_OBJS} ${DISTANCE_OBJS} ${DEPS} ${RADIX_OBJS} #${DEBUG_OBJS}

fclean :
	@make clean
	@rm -rf ${LIBFT}
	@rm -rf ${NAME} ${NAME_2} ${LIB_SORT} ${NAME_DEBUG}

re :	fclean all

-include ${DEPS}

.PHONY : re clean fclean all dbg
