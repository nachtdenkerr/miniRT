NAME := miniRT

LIB_DIR 	:=	lib
BONUS_DIR	:=	src/bonus
MLX_DIR		:=	src/mlx
PARS_DIR	:=	src/parser
RENDER_DIR	:=	src/render
UTILS_DIR	:=	src/utils
OBJ_DIR 	:=	obj

CC 		:=	cc 
CFLAGS	:= -Wall -Wextra -Werror


LIBFT_DIR	:= $(LIB_DIR)/libft
LIBFT_A		:= $(LIBFT_DIR)/libft.a

MLX42_DIR 	:= $(LIB_DIR)/MLX42
MLX42_A 	:= $(MLX42_DIR)/build/libmlx42.a

LIBS	:= $(LIBFT_A) $(MLX42_A) -ldl -lglfw -lpthread -lm
IFLAGS	:= -Iinclude -I$(LIBFT_DIR)/include -I$(MLX42_DIR)/include/MLX42

SRCS	:= 	\
			src/main.c\
			src/print.c\
			$(PARS_DIR)/error.c\
			$(PARS_DIR)/error_two.c\
			$(PARS_DIR)/gnl_helper.c\
			$(PARS_DIR)/gnl.c\
			$(PARS_DIR)/init.c\
			$(PARS_DIR)/parse_elements.c\
			$(PARS_DIR)/parse_objects.c\
			$(PARS_DIR)/parse_scene.c\
			$(PARS_DIR)/parse_utils.c\
			$(PARS_DIR)/parse_utils_two.c\
			$(RENDER_DIR)/checker_board.c\
			$(RENDER_DIR)/cone_triangle_helper.c\
			$(RENDER_DIR)/intersection.c\
			$(RENDER_DIR)/intersection_cylinder.c\
			$(RENDER_DIR)/intersection_wrapper.c\
			$(RENDER_DIR)/intersection_helper.c\
			$(RENDER_DIR)/sky_box_model.c\
			$(RENDER_DIR)/lighting.c\
			$(RENDER_DIR)/init_ray.c\
			$(RENDER_DIR)/minirt.c\
			$(UTILS_DIR)/cleanup.c\
			$(UTILS_DIR)/vector_utils.c\
			$(UTILS_DIR)/vector_math_utils.c\
			$(UTILS_DIR)/error_exit.c\
			$(UTILS_DIR)/color_utils.c\

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Reset
NC=\033[0m

# Regular Colors
Black :=\033[0;30m
Red :=\033[0;31m
Green :=\033[0;32m
Yellow :=\033[0;33m
Blue= :=\033[0;34m
Purple =\033[0;35m
Cyan :=\033[0;36m
White :=\033[0;37m

all: $(NAME)

$(LIBFT_A):
	@make -C $(LIBFT_DIR) > /dev/null

$(MLX42_A):
	@git clone --quiet https://github.com/codam-coding-college/MLX42.git $(MLX42_DIR)
	@cmake $(MLX42_DIR) -B $(MLX42_DIR)/build > /dev/null
	@cmake --build $(MLX42_DIR)/build -j4 > /dev/null

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(NAME): $(LIBFT_A) $(MLX42_A) $(PRINTF_A) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "${Green}miniRT ${Black}Build successful!"

clean:
	@make -C $(LIBFT_DIR) clean > /dev/null
	@rm -rf $(OBJ_DIR)
	@rm -rf	$(MLX42_DIR)/build
	@rm -rf $(MLX42_DIR)
	@echo "${Green}CLEAN ${Black}successful!"

fclean:
	@make -C $(LIBFT_DIR) fclean > /dev/null
	@rm -rf	$(MLX42_DIR)/build
	@rm -rf $(MLX42_DIR)
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)
	@echo "${Green}FCLEAN ${Black}successful!"

re: fclean all

.PHONY: all clean fclean re