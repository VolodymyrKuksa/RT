CC = clang

NAME = libJSON.a
PNAME = libJSON

DIR_S = src

DIR_O = obj

HEADER = include

SOURCES = json.c

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

C_RED = \033[31m
C_GREEN = \033[32m
C_CYAN = \033[36m
C_NONE = \033[0m

all: $(NAME)

$(NAME): $(DIR_O) $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@printf "%-10s%-25s$(C_GREEN)[done]$(C_NONE)\n" $(PNAME): $@

$(DIR_O):
	@mkdir -p obj
	@printf "%-10s%-25s$(C_GREEN)[done]$(C_NONE)\n" $(PNAME): $@


$(DIR_O)/%.o: $(DIR_S)/%.c $(HEADER)/json.h
	@$(CC) $(FLAGS) -I $(HEADER) -o $@ -c $<
	@printf "%-10s%-25s$(C_GREEN)[done]$(C_NONE)\n" $(PNAME): $@

clean:
	@rm -f $(OBJS)
	@rm -rf $(DIR_O)
	@printf "%-10s%-25s$(C_RED)[done]$(C_NONE)\n" $(PNAME): $@

fclean: clean
	@rm -f $(NAME)
	@printf "%-10s%-25s$(C_RED)[done]$(C_NONE)\n" $(PNAME): $@

re: fclean all

.PHONY: all obj clean fclean re
.NOTPARALLEL: all obj clean fclean re
