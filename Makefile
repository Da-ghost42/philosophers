SRCS = philo_utils.c philo.c routine.c philos_actions.c parsing.c

OBJS = ${SRCS:.c=.o}

NAME = philo

HEADER = philo.h

CC = cc

CFLAGS = -Wall -Werror -Werror

RM = rm -rf

OPTION_FLAG =  #-g -fsanitize=thread


all:${NAME}

${NAME}:${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}
%.o:%.c ${HEADER}
	 @echo "compiling .." 
	${CC} ${CFLAGS} -c $< -o $@

re : fclean all


clean : 
	${RM} ${OBJS}
fclean :
	${RM} ${OBJS} ${NAME}
.PHONY : all re fclean clean