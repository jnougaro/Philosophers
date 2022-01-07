# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnougaro <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/17 10:14:36 by jnougaro          #+#    #+#              #
#    Updated: 2022/01/06 17:40:13 by jnougaro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

SRCS	= srcs/main.c \
			srcs/utils.c \
			srcs/parsing.c \
			srcs/create_philo.c \
			srcs/init_struct.c \
			srcs/philo_routine.c \
			srcs/philo_status.c \
			srcs/philo_routine_utils.c \
			srcs/global_check_die.c

OBJS	= ${SRCS:.c=.o}

CC 	= clang
RM	= rm -f

CFLAGS	= -pthread -Wall -Werror -Wextra

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:		${NAME}

$(NAME):	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o $(NAME)

clean:
		${RM} ${OBJS}

fclean:		clean
		${RM} ${NAME}

re:		fclean all

.PHONY:		all clean fclean re
