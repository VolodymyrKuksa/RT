# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/22 18:23:38 by vkuksa            #+#    #+#              #
#    Updated: 2018/05/22 18:23:42 by vkuksa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT
N_LFT = libft.a
N_LVEC = libvec.a

#---------------DIRECTORIES-----------------------------------------------------

D_LFT = libft/
D_LVEC = libvec/
D_SRC = src/
D_OBJ = obj/
D_INC = includes/
D_LFTINC = $(D_LFT)includes/
D_LVECINC = $(D_LVEC)includes/
D_FRW = /Library/Frameworks/
D_SDL2 = $(D_FRW)SDL2.framework/

#--------------LIBRARIES--------------------------------------------------------

LFT = $(D_LFT)$(N_LFT)
LVEC = $(D_LVEC)$(N_LVEC)

#--------------FILES------------------------------------------------------------

HEAD_FILES = rt.h rt_types.h

C_FILES = main.c read_file.c


SRC = $(addprefix $(D_SRC), $(C_FILES))
OBJ = $(addprefix $(D_OBJ), $(C_FILES:.c=.o))
HEADERS = $(addprefix $(D_INC), $(HEAD_FILES))

#--------------COMPILATION------------------------------------------------------

CC = clang
#CFLAGS = -Wall -Werror -Wextra -O1

INC = -I $(D_INC) -I $(D_LFTINC) -I $(D_LVECINC) -I $(D_SDL2)Headers
FRW = -framework OpenCL -framework SDL2 -F $(D_FRW)

#--------------COLORS-----------------------------------------------------------

C_RED = \033[31m
C_GREEN = \033[32m
C_CYAN = \033[36m
C_NONE = \033[0m

#--------------RULES------------------------------------------------------------

all: $(NAME)

$(NAME): $(D_OBJ) $(OBJ)
	@make -C $(D_LFT)
	@printf "$(C_CYAN)%-10s$(C_NONE)%-25s$(C_GREEN)[done]$(C_NONE)\n" $(NAME): $(N_LFT)
	@make -C $(D_LVEC)
	@printf "$(C_CYAN)%-10s$(C_NONE)%-25s$(C_GREEN)[done]$(C_NONE)\n" $(NAME): $(N_LVEC)
	@$(CC) $(OBJ) $(LFT) $(LVEC) $(FRW) -o $(NAME)
	@printf "$(C_CYAN)%-10s$(C_NONE)%-25s$(C_GREEN)[done]$(C_NONE)\n" $(NAME): $@

$(D_OBJ):
	@mkdir $(D_OBJ)
	@printf "$(C_CYAN)%-10s$(C_NONE)%-25s$(C_GREEN)[done]$(C_NONE)\n" $(NAME): $@

$(D_OBJ)%.o: $(D_SRC)%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $(INC) $< -o $@
	@printf "$(C_CYAN)%-10s$(C_NONE)%-25s$(C_GREEN)[done]$(C_NONE)\n" $(NAME): $@

clean:
	@rm -rf $(D_OBJ)
	@make -C $(D_LFT) clean
	@make -C $(D_LVEC) clean
	@printf "$(C_CYAN)%-10s$(C_NONE)%-25s$(C_RED)[done]$(C_NONE)\n" $(NAME): $@

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(D_SDL)
	@make -C $(D_LFT) fclean
	@make -C $(D_LVEC) fclean
	@printf "$(C_CYAN)%-10s$(C_NONE)%-25s$(C_RED)[done]$(C_NONE)\n" $(NAME): $@

re: fclean all

norm: clean
	@norminette $(D_SRC) $(D_INC)

allnorm: norm
	@norminette $(D_LFT)
	@norminette $(D_LVEC)