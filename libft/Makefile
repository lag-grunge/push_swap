NAME = libft.a

SRCS = 	ft_memset.c ft_bzero.c ft_memcpy.c  ft_memchr.c \
		ft_strlen.c ft_strlcpy.c ft_strchr.c ft_strncmp.c \
		ft_substr.c	ft_strjoin.c ft_strtrim.c ft_split.c ft_split_utils.c \
		ft_isdigit.c ft_calloc.c ft_strdup.c \
		ft_atoi.c ft_atoi_base.c

DLST_SRCS = ft_dlst/ft_dlst.c ft_dlst/ft_dlst_two.c

HEADER = libft.h
DLST_HEADER = ft_dlst/ft_dlst.h

OBJS = $(SRCS:.c=.o)
DLST_OBJS = $(DLST_SRCS:.c=.o)

INCLUDE = -I./  -I./ft_dlst/

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all : ${NAME}

$(NAME) : ${OBJS}	$(DLST_OBJS)
	ar rcs ${NAME} $?

${OBJS} :%.o	: 	%.c ${HEADER}
	${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@
$(DLST_OBJS) : %.o : %.c ${DLST_HEADER}
	${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@

clean:
	@rm -f ${OBJS} $(DLST_OBJS)

fclean: clean
	@rm -f ${NAME}

re	: fclean all

.PHONY: all clean fclean re
