# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 15:25:41 by alemarti          #+#    #+#              #
#    Updated: 2022/03/22 16:47:20 by alemarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	pipex.c				\
				file_utils.c		\
				libft_utils.c		\
				ft_split.c			\
				exec_utils.c		\
				children_utils.c


OBJS		= ${SRCS:.c=.o}

NAME		= pipex

CC			= gcc
RM			= rm -f
CFLAGS		= -Wall -Werror -Wextra


all:		${NAME}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
			@${RM} ${OBJS}


fclean:		clean
			@${RM} ${NAME}

test:		${OBJS}
			${CC} ${OBJS} -o ${NAME}

re:			fclean all

PHONY:		all clean fclean re test