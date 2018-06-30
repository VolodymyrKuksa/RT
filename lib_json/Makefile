AR = ar
CC = gcc
CFLAGS ?= -Wall -Os -fPIC

NAME = json
A_TARGETS = lib$(NAME).a
HEADERS = $(NAME).h

TARGETS = $(A_TARGETS)

C_RED = \033[31m
C_GREEN = \033[32m
C_CYAN = \033[36m
C_NONE = \033[0m

all: $(TARGETS)

lib$(NAME).a: $(NAME).o
	@$(AR) rc $@ $+
	@printf "%-10s%-25s$(C_GREEN)[done]$(C_NONE)\n" $(NAME): $@

%.o: %.c %.h
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf "%-10s%-25s$(C_GREEN)[done]$(C_NONE)\n" $(NAME): $@

clean:
	@rm -rf *.o $(TARGETS)
	@printf "%-10s%-25s$(C_RED)[done]$(C_NONE)\n" $(NAME): $@

fclean: clean
	@rm -rf $(NAME)
	@printf "%-10s%-25s$(C_RED)[done]$(C_NONE)\n" $(NAME): $@

re: fclean all