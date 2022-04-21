NAME = shell

SRCS = $(shell find "." -name "*.c")

OBJS = $(SRCS:.c=.o)

LDFLAGS = -L /Users/akhachat/lib
CPPFLAGS = -I /Users/akhachat/include

CC = gcc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME} : ${OBJS}
	${CC} ${CFLAGS} ${CPPFLAGS}  -o ${NAME} ${LDFLAGS}  $(OBJS)   -lreadline

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
