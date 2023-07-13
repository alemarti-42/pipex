# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 15:25:41 by alemarti          #+#    #+#              #
#    Updated: 2023/07/13 18:13:54 by alemarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	file_utils.c		\
				libft_utils.c		\
				ft_split.c			\
				exec_utils.c		\
				children_utils.c
SRCS_OG		=	pipex.c
SRCS_BONUS	=	pipex_bonus.c

OBJS		= ${SRCS:.c=.o}
OBJS_OG		= ${SRCS_OG:.c=.o}
OBJS_BONUS	= ${SRCS_BONUS:.c=.o}

NAME		= pipex

CC			= gcc
RM			= rm -f
CFLAGS		= -Wall -Werror -Wextra


all:		${NAME}

${NAME}:	${OBJS} ${OBJS_OG}
			${CC} ${CFLAGS} ${OBJS} ${OBJS_OG} -o ${NAME}

bonus:		fclean ${OBJS} ${OBJS_BONUS}
			${CC} ${CFLAGS} ${OBJS} ${OBJS_BONUS} -o ${NAME}

clean:
			@${RM} ${OBJS} ${OBJS_OG} ${OBJS_BONUS}


fclean:		clean
			@${RM} ${NAME}

re:			fclean all

PHONY:		all clean fclean re bonus