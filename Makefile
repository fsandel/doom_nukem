NAME			=	doom-nukem

CC				=	cc
CFLAGS			=	-Wall -Wextra -g -Ofast -Werror #-fsanitize=address 
LINKFLAGS		= #-fsanitize=address -g
REDIRECT		=	2> /dev/null 1> /dev/null
OS				=	$(shell uname -s)
BREW			=	$(HOME)/.brew

################################################################################
################################################################################

SRC				=	$(addprefix $(SRC_DIR), $(SRC_FILES))
SRC_DIR			=	src/
SRC_FILES		=	main.c ft_put_pixel.c #utils.c keyboard_input.c doors.c movement.c start_end_screen.c endcondition.c setup.c setup_player.c sound.c

# PARSER			=	$(addprefix $(PARSER_DIR), $(PARSER_FILES))
# PARSER_DIR		=	src/parser/
# PARSER_FILES	=	parser.c validate_args.c validate_map.c parse_options.c check_syntax.c validate_options.c handle_errors.c parser_init.c

MEMORY			=	$(addprefix $(MEMORY_DIR), $(MEMORY_FILES))
MEMORY_DIR		=	src/memory/
MEMORY_FILES	=	collector.c ft_malloc.c garbage.c

PLAYER			=	$(addprefix $(PLAYER_DIR), $(PLAYER_FILES))
PLAYER_DIR		=	src/player/
PLAYER_FILES	=	player_access.c

WINDOW			=	$(addprefix $(WINDOW_DIR), $(WINDOW_FILES))
WINDOW_DIR		=	src/window/
WINDOW_FILES	=	window_access.c

MENU			=	$(addprefix $(MENU_DIR), $(MENU_FILES))
MENU_DIR		=	src/menu/
MENU_FILES		=	menu_item.c menu.c

TEXTURE			=	$(addprefix $(TEXTURE_DIR), $(TEXTURE_FILES))
TEXTURE_DIR		=	src/texture/
TEXTURE_FILES	=	ft_load_png.c

GRAFICS			=	$(addprefix $(GRAFICS_DIR), $(GRAFICS_FILES))
GRAFICS_DIR		=	src/grafics/
GRAFICS_FILES = grafics_utils.c draw_forms.c

VECTORS			=	$(addprefix $(VECTORS_DIR), $(VECTORS_FILES))
VECTORS_DIR		=	src/vectors/
VECTORS_FILES	=	vector_int.c vector_float.c

# HDR				=	$(addprefix $(HDR_DIR), $(HDR_FILES))
# HDR_DIR			=	include/
# HDR_FILES		=	cub3D.h design.h
# HDR_INCLUDE		=	-I $(HDR_DIR)

ALL_SRC			=	$(SRC) $(MEMORY) $(PLAYER) $(WINDOW) $(MENU) $(TEXTURE) $(GRAFICS) $(VECTORS)

################################################################################
################################################################################

OBJ_DIR			=	obj/
ALL_OBJ			=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(ALL_SRC))
ALL_OBJ_DIR		=	$(sort $(dir $(ALL_OBJ)))

################################################################################
################################################################################

all: libft mlx $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(HDR_INCLUDE) $(MLX_INCLUDE) $(LIBFT_INCLUDE)
	@echo $(LGREEN)"compiled "$^$(DEFAULT)

$(NAME): $(ALL_OBJ_DIR) $(ALL_OBJ)
	@$(CC) $(ALL_OBJ) -o $(NAME) $(LINK_FLAGS) $(LIBFT) $(MLX) $(GLFW)
	@echo $(GREEN)" compiled "$@$(DEFAULT)

clean:
	@echo $(RED)"cleaning:"
	@rm -rfv $(patsubst %/,%,$(OBJ_DIR))
	@echo "cleaned"$(DEFAULT)

fclean:
	@echo $(RED)"fcleaning:"
	@rm -rfv $(patsubst %/,%,$(OBJ_DIR)) $(NAME)
	@echo "fcleaned"$(DEFAULT)

re:	fclean all

bonus:
	@echo "make sure to implement bonus"

################################################################################
################################################################################

# test: $(ALL_OBJ_DIR) $(ALL_OBJ)
# 	@ar -rcs libcub3dtest.a $(ALL_OBJ) lib/libft/obj/*.o
# 	@cd tests && $(MAKE) run

# testclean:
# 	rm libcub3dtest.a
# 	rm tests/*.out

$(ALL_OBJ_DIR):
	@mkdir -p $(ALL_OBJ_DIR)

# norm:
# 	@norminette $(ALL_SRC) $(HDR) | grep -v "Missing or invalid 42 header"

# r: all
# 	./$(NAME) maps/enemy.cub

################################################################################
################################################################################

#help:
#	@make check_brew

#check_brew:
#ifeq ($(shell which brew ),$(BREW)/bin/brew)
#	@echo "brew is installed"
#	@make check_glfw
#else
#	@echo "no brew found in standard path."
#	@echo "use make brew to install"
#endif

#check_glfw:
#ifeq ($(shell brew list | grep glfw), glfw)
#	@echo "glfw is installed"
#	@make check_cmake
#else
#	@echo "no glfw found"
#	@echo "use make glfw to install"
#endif

#check_cmake:
#ifeq ($(shell which cmake), $(BREW)/bin/cmake)
#	@echo "cmake is installed in the default directory"
#else
#	@echo "no cmake found in the default directory"
#	@echo "use make cmake to install"
#endif

################################################################################
################################################################################

# brew:
# 	rm -rf $$HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $$HOME/.brew && echo 'export PATH=$$HOME/.brew/bin:$$PATH' >> $$HOME/.zshrc && source $$HOME/.zshrc && brew update

# glfw:
# 	brew install glfw

# cmake:
# 	brew install cmake

################################################################################
################################################################################

MLX				=	$(MLX_DIR)/build/$(MLX_LIB)
MLX_LIB			=	libmlx42.a
MLX_DIR			=	lib/MLX42
MLX_INCLUDE		=	-I ./$(MLX_DIR)/include/MLX42

ifeq ($(OS), Darwin)
	GLFW			=	-lglfw -L"$(BREW)/opt/glfw/lib/"
endif
ifeq ($(OS), Linux)
	GLFW			=	-ldl -lglfw -pthread -lm
endif

mlx: $(MLX)

$(MLX):
	@git submodule init $(MLX_DIR) $(REDIRECT)
	@git submodule update $(MLX_DIR) $(REDIRECT)
	@cd $(MLX_DIR) && cmake -B build $(REDIRECT)
	@cd $(MLX_DIR)/build && make $(REDIRECT)
	@echo $(GREEN)"created $(MLX_LIB)"$(DEFAULT)

################################################################################
################################################################################

LIBFT			=	$(LIBFT_DIR)$(LIBFT_LIB)
LIBFT_LIB		=	libft.a
LIBFT_DIR		=	lib/libft/
LIBFT_INCLUDE	=	-I ./$(LIBFT_DIR)

libft: $(LIBFT)

$(LIBFT):
	@git submodule init $(LIBFT_DIR) $(REDIRECT)
	@git submodule update $(LIBFT_DIR) $(REDIRECT)
	@make -C lib/libft

################################################################################
################################################################################

LSAN			=	lib/LeakSanitizer
LSANLIB			=	$(LSAN)/liblsan.a

ifeq ($(OS),Linux)
	LSANLFLAGS := -rdynamic -Llib/LeakSanitizer -llsan -ldl -lstdc++
endif
ifeq ($(OS),Darwin)
	LSANLFLAGS := -Llib/LeakSanitizer -llsan -lc++
endif

lsan: CFLAGS += -I $(LSAN) -Wno-gnu-include-next
lsan: LINK_FLAGS += $(LSANLFLAGS)
lsan: fclean $(LSANLIB)
lsan: all

$(LSAN):
	@git submodule init $(LSAN) $(REDIRECT)
	@git submodule update $(LSAN) $(REDIRECT)

$(LSANLIB): $(LSAN)
	@$(MAKE) -C $(LSAN) $(REDIRECT)
	@echo $(GREEN)"created liblsan.a"$(DEFAULT)


################################################################################
################################################################################

GREEN			= "\033[32m"
LGREEN			= "\033[92m"
DEFAULT			= "\033[39m"
RED				= "\033[31m"

################################################################################
################################################################################

.PHONY: all clean fclean ffclean re libft readline lsan tester env