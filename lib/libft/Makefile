NAME = libft.a

SRC_DIR	:= src/

SRCS := $(SRC_DIR)/ft_is.c\
		$(SRC_DIR)/ft_bc.c\
		$(SRC_DIR)/ft_mem.c\
		$(SRC_DIR)/ft_put.c\
		$(SRC_DIR)/ft_aiia.c\
		$(SRC_DIR)/ft_strl.c\
		$(SRC_DIR)/ft_strnstr.c\
		$(SRC_DIR)/ft_strchr.c\
		$(SRC_DIR)/ft_to.c\
		$(SRC_DIR)/ft_strdup.c\
		$(SRC_DIR)/ft_substr.c\
		$(SRC_DIR)/ft_strjoin.c\
		$(SRC_DIR)/ft_strtrim.c\
		$(SRC_DIR)/ft_strmapi.c\
		$(SRC_DIR)/ft_striteri.c\
		$(SRC_DIR)/ft_split.c\
		$(SRC_DIR)/ft_lst_a.c\
		$(SRC_DIR)/ft_lst_b.c\
		$(SRC_DIR)/ft_check_flag.c \
		$(SRC_DIR)/ft_print_flag.c \
		$(SRC_DIR)/ft_putchar_we.c \
		$(SRC_DIR)/ft_print_hex.c \
		$(SRC_DIR)/ft_print_ptr.c \
		$(SRC_DIR)/ft_print_uint.c \
		$(SRC_DIR)/ft_printf.c

OBJ_DIR := obj
OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)

CC := 	cc
LIBC := 	ar rcs
RM := 	rm -f
INCS := 	include
CFLAGS +=  -Wall -Werror -Wextra -Iincludes -I$(INCS)

# Reset
NC=\033[0m

# Regular Colors
Black :=\033[0;30m
Red :=\033[0;31m
Green :=\033[0;32m
Yellow := '\033[0;33m'       # Yellow
Blue= := '\033[0;34m'         # Blue
Purple = '\033[0;35m'       # Purple
Cyan := '\033[0;36m'         # Cyan
White := '\033[0;37m'        # White

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(SRCS)
	@$(LIBC) $(NAME) $(OBJS)
	@echo "${Green}$(NAME) ${Black}Build successful!"

clean:
	@$(RM) $(OBJS)
	@rm -rf $(OBJ_DIR)
	@echo "${Green}$(NAME) ${Black}Clean successful!"

fclean: clean
	@$(RM) $(NAME)
	@echo "${Green}$(NAME) ${Black}Fclean successful!"

re: fclean all

.PHONY: fclean clean all re