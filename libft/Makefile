# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/26 11:01:38 by vkuksa            #+#    #+#              #
#    Updated: 2018/05/22 17:35:35 by vkuksa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFILES = ft_atod.c ft_atoi.c ft_atoi_base.c ft_bzero.c ft_isalnum.c \
ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_itoa_base.c \
ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c \
ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c \
ft_memmove.c ft_memset.c ft_putchar.c ft_putchar_fd.c ft_putendl.c \
ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c \
ft_sort_int_tab.c ft_sort_str_tab.c ft_strcat.c ft_strchr.c ft_strclr.c \
ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c \
ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c \
ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c \
ft_strrchr.c ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c ft_swap.c \
ft_tolower.c ft_toupper.c get_next_line.c

INCFILES = libft.h get_next_line.h

SRC_DIR = src/
OBJ_DIR = obj/
D_INC = includes/

SRC = $(addprefix $(SRC_DIR), $(CFILES))
OBJ = $(addprefix $(OBJ_DIR), $(CFILES:.c=.o))
INC = $(addprefix $(D_INC), $(INCFILES))

CC = clang
FLAGS = -Wall -Werror -Wextra

C_RED = \033[31m
C_GREEN = \033[32m
C_CYAN = \033[36m
C_NONE = \033[0m

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf "%-10s%-25s$(C_GREEN)[done]$(C_NONE)\n" $(NAME): $@

$(OBJ_DIR):
	@mkdir $@
	@printf "%-10s%-25s$(C_GREEN)[done]$(C_NONE)\n" $(NAME): $@

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(INC)
	@$(CC) -c -I $(D_INC) $(FLAGS) $< -o $@
	@printf "%-10s%-25s$(C_GREEN)[done]$(C_NONE)\n" $(NAME): $@

clean:
	@/bin/rm -rf $(OBJ_DIR)
	@printf "%-10s%-25s$(C_RED)[done]$(C_NONE)\n" $(NAME): $@

fclean: clean
	@/bin/rm -rf $(NAME)
	@printf "%-10s%-25s$(C_RED)[done]$(C_NONE)\n" $(NAME): $@

re: fclean $(NAME)
