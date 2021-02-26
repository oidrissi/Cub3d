# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/17 02:25:49 by oidrissi          #+#    #+#              #
#    Updated: 2021/02/26 15:04:47 by oidrissi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libmlx.a

SRCS = *.c

OBJECTS = $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I ./mlx/mlxx 
LIBS			= -L ./mlx -lmlx -framework OpenGL -framework AppKit

NAME			= cub3D

all:			$(NAME)

$(NAME):		$(OBJS)
				gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}

clean:
				@$(MAKE) -C mlx clean
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME) $(MLX)

re:				fclean $(NAME)

.PHONY:			all clean fclean re