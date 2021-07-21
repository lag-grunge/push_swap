NAME = push_swap

SRCS = main.c

LIB_DIR = ./libft

LIBFT = libft.a

CFLAGS = -g -Wall -Wextra -Werror

${NAME} : ${LIBFT}
	gcc ${CFLAGS} main.c -o $@ -I${LIB_DIR} -L${LIB_DIR} -lft

${LIBFT} : ${LIB_DIR}
	make -C ${LIB_DIR}
