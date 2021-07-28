NAME = push_swap

NAME_2 = checker

SRCS = input.c sorted_array.c \
	   init_stack.c operations.c \
		both_operations.c small_size.c \
		print_stack.c get_next_line.c

OBJS = ${SRCS:.c=.o}

LIB_DIR = ./libft

LIBFT = libft.a

CFLAGS = -g -Wall -Wextra -Werror

all : ${LIBFT} ${NAME} ${NAME_2}

${NAME} : main.c ${OBJS}
	gcc ${CFLAGS} $^ -o $@ -I${LIB_DIR} -L${LIB_DIR} -lft

${NAME_2} : checker.c ${OBJS}
	gcc ${CFLAGS} $^ -o $@ -I${LIB_DIR} -L${LIB_DIR} -lft
	
${OBJS} : %.o : %.c
	gcc ${CFLAGS} -c $< -o ${<:.c=.o} -I${LIB_DIR}

${LIBFT} : ${LIB_DIR}
	make -C ${LIB_DIR}

clean :
	rm ${OBJS}

fclean : clean 
	rm ${NAME}
