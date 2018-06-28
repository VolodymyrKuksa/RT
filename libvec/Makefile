# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/13 17:33:46 by vkuksa            #+#    #+#              #
#    Updated: 2018/03/18 18:12:54 by vkuksa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libvec.a
CFILES = \
	vec_new.c\
	vec_scale.c\
	vec_add.c\
	vec_sub.c\
	vec_magn.c\
	vec_norm.c\
	vec_dot.c\
	vec_cross.c\
	vec_rot_x.c\
	vec_rot_y.c\
	vec_rot_z.c\
	vec_rot_xyz.c\
	vec_rot_zyx.c\
	clvec_rot_x.c\
	clvec_rot_y.c\
	clvec_rot_z.c\
	clvec_add.c\
	vec_print.c

HFILES = libvec.h

D_SRC = ./src/
D_OBJ = ./obj/
D_INC = ./includes/

SRC = $(addprefix $(D_SRC), $(CFILES))
OBJ = $(addprefix $(D_OBJ), $(CFILES:.c=.o))
INC = $(addprefix $(D_INC), $(HFILES))

CC = gcc
CFLAGS = -Wall -Werror -Wextra

C_RED = \033[31m
C_GREEN = \033[32m
C_CYAN = \033[36m
C_NONE = \033[0m

all: $(NAME)

$(NAME): $(INC) $(D_OBJ) $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf "%-10s%-25s$(C_GREEN)[done]$(C_NONE)\n" $(NAME): $@

$(D_OBJ):
	@mkdir $(D_OBJ)
	@printf "%-10s%-25s$(C_GREEN)[done]$(C_NONE)\n" $(NAME): $@

$(D_OBJ)%.o:$(D_SRC)%.c $(INC)
	@$(CC) $(CFLAGS) -c -I $(D_INC) $< -o $@
	@printf "%-10s%-25s$(C_GREEN)[done]$(C_NONE)\n" $(NAME): $@

clean:
	@rm -rf $(D_OBJ)
	@printf "%-10s%-25s$(C_RED)[done]$(C_NONE)\n" $(NAME): $@

fclean: clean
	@rm -rf $(NAME)
	@printf "%-10s%-25s$(C_RED)[done]$(C_NONE)\n" $(NAME): $@

re: fclean all

norm:
	@norminette $(D_INC) $(D_SRC)
