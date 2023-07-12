# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 15:25:41 by alemarti          #+#    #+#              #
#    Updated: 2023/07/12 12:54:01 by alemarti         ###   ########.fr        #
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
CFLAGS		= -Wall -Werror -Wextra -g3 -fsanitize=address


all:		${NAME}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
			@${RM} ${OBJS}


fclean:		clean
			@${RM} ${NAME}

re:			fclean all

PHONY:		all clean fclean re test