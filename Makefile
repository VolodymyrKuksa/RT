# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/22 18:23:38 by vkuksa            #+#    #+#              #
#    Updated: 2018/07/18 18:19:54 by vkuksa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT
CLIENT = client
N_LFT = libft.a
N_LVEC = libvec.a
N_JSON = libJSON.a

#---------------DIRECTORIES-----------------------------------------------------

D_LFT = libft/
D_LVEC = libvec/
D_JSON = libJSON/

D_SRC = src/
D_OBJ = obj/

D_INC = includes/
D_LFTINC = $(D_LFT)includes/
D_LVECINC = $(D_LVEC)includes/
D_JSONINC = $(D_JSON)include/

D_FRW = frameworks/
D_SDL2 = $(D_FRW)SDL2.framework/
D_IMG = $(D_FRW)SDL2_image.framework/
D_TTF = $(D_FRW)SDL2_ttf.framework/

#--------------LIBRARIES--------------------------------------------------------

LFT = $(D_LFT)$(N_LFT)
LVEC = $(D_LVEC)$(N_LVEC)
LJSON = $(D_JSON)$(N_JSON)

#--------------FILES------------------------------------------------------------

HEAD_FILES = rt.h rt_types.h parser.h keys.h rt_textures.h server_client.h gui.h

C_FILES = cl_exec.c\
cl_initialization.c\
events/keyboard_events.c\
events/movement_events.c\
events/mouse_event.c\
events/mv_obj.c\
events/mv_obj2.c\
events/rot_obj.c\
events/rot_obj2.c\
events/rotate.c\
events/window_event.c\
events/write_png.c\
events/write_ppm.c\
parser/check_params1.c\
parser/check_params2.c\
parser/default_objs.c\
parser/default_objs2.c\
parser/fill_each_obj.c\
parser/fill_each_obj2.c\
parser/fill_each_obj3.c\
parser/fill_each_obj4.c\
parser/fill_each_obj5.c\
parser/init_cam.c\
parser/init_cam2.c\
parser/parse.c\
parser/ftoa.c\
parser/write_to_file.c\
parser/write_to_file2.c\
parser/write_to_file3.c\
parser/write_to_file4.c\
parser/write_to_file5.c\
parser/scene_init.c\
parser/scene_init2.c\
parser/scene_init3.c\
parser/scene_init4.c\
scene_utils.c\
sdl_utils.c\
textures/compress_texture.c\
textures/load_texture.c\
server-client/run_server.c\
server-client/thread_pool.c\
server-client/socket_utils.c\
server-client/tpool_new_msg.c\
server-client/tpool_read_send_msg.c\
server-client/tpool_cleanup.c\
server-client/tpool_client.c\
server-client/tpool_threads.c\
server-client/tpool_client_logic.c\
gui/label.c\
gui/button.c\
gui/menu.c\
gui/common_staff.c\
gui/controller.c\
gui/radio.c\
gui/gui.c\
client_read_data.c\
main_loop.c

C_FILES_RT = server_main.c $(C_FILES)

C_FILES_CLIENT = client_main.c $(C_FILES)

SRC_RT = $(addprefix $(D_SRC), $(C_FILES_RT))
OBJ_RT = $(addprefix $(D_OBJ), $(C_FILES_RT:.c=.o))

SRC_CLIENT = $(addprefix $(D_SRC), $(C_FILES_CLIENT))
OBJ_CLIENT = $(addprefix $(D_OBJ), $(C_FILES_CLIENT:.c=.o))

HEADERS = $(addprefix $(D_INC), $(HEAD_FILES))

#--------------COMPILATION------------------------------------------------------

CC = clang
#CFLAGS = -Wall -Werror -Wextra -O1

INC = -I $(D_INC) -I $(D_LFTINC) -I $(D_LVECINC) -I $(D_JSONINC) -I $(D_SDL2)Headers -I $(D_IMG)Headers -I $(D_TTF)Headers
FRW = -framework OpenCL -F $(D_FRW) -rpath $(D_FRW) -framework SDL2 -framework SDL2_image -framework SDL2_ttf

#--------------COLORS-----------------------------------------------------------

C_RED = \033[31m
C_GREEN = \033[32m
C_CYAN = \033[36m
C_NONE = \033[0m

#--------------RULES------------------------------------------------------------

all: $(NAME) $(CLIENT)

$(NAME): $(D_OBJ) $(OBJ_RT)
	@make -C $(D_LFT)
	@printf "$(C_CYAN)%-10s$(C_NONE)%-25s$(C_GREEN)[done]$(C_NONE)\n" $(NAME): $(N_LFT)
	@make -C $(D_LVEC)
	@printf "$(C_CYAN)%-10s$(C_NONE)%-25s$(C_GREEN)[done]$(C_NONE)\n" $(NAME): $(N_LVEC)
	@make -C $(D_JSON)
	@printf "$(C_CYAN)%-10s$(C_NONE)%-25s$(C_GREEN)[done]$(C_NONE)\n" $(NAME): $(N_JSON)
	@$(CC) $(OBJ_RT) $(LFT) $(LVEC) $(LJSON) $(FRW) -o $(NAME)
	@printf "$(C_CYAN)%-10s$(C_NONE)%-25s$(C_GREEN)[done]$(C_NONE)\n" $(NAME): $@

$(CLIENT): $(D_OBJ) $(OBJ_CLIENT)
	@make -C $(D_LFT)
	@printf "$(C_CYAN)%-10s$(C_NONE)%-25s$(C_GREEN)[done]$(C_NONE)\n" $(CLIENT): $(N_LFT)
	@$(CC) $(OBJ_CLIENT) $(LFT) $(LVEC) $(LJSON) $(FRW) -o $(CLIENT)
	@printf "$(C_CYAN)%-10s$(C_NONE)%-25s$(C_GREEN)[done]$(C_NONE)\n" $(CLIENT): $@

$(D_OBJ):
	@mkdir $(D_OBJ)
	@mkdir $(D_OBJ)textures
	@mkdir $(D_OBJ)parser
	@mkdir $(D_OBJ)events
	@mkdir $(D_OBJ)gui
	@mkdir $(D_OBJ)server-client
	@printf "$(C_CYAN)%-10s$(C_NONE)%-25s$(C_GREEN)[done]$(C_NONE)\n" $(NAME): $@

$(D_OBJ)%.o: $(D_SRC)%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $(INC) $< -o $@
	@printf "$(C_CYAN)%-10s$(C_NONE)%-25s$(C_GREEN)[done]$(C_NONE)\n" $(NAME): $@

clean:
	@rm -rf $(D_OBJ)
	@make -C $(D_LFT) clean
	@make -C $(D_LVEC) clean
	@make -C $(D_JSON) clean
	@printf "$(C_CYAN)%-10s$(C_NONE)%-25s$(C_RED)[done]$(C_NONE)\n" $(NAME): $@

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(CLIENT)
	@rm -rf $(D_SDL)
	@make -C $(D_LFT) fclean
	@make -C $(D_LVEC) fclean
	@make -C $(D_JSON) fclean
	@printf "$(C_CYAN)%-10s$(C_NONE)%-25s$(C_RED)[done]$(C_NONE)\n" $(NAME): $@

re: fclean all

norm: clean
	@norminette $(D_SRC) $(D_INC)

allnorm: norm
	@norminette $(D_LFT)
	@norminette $(D_LVEC)
