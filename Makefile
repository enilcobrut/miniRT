MAKEFLAGS = "-j 10"

HEADER = 		libs/includes/miniRT.h \
				libs/includes/ft_printf_fd.h \
				libs/includes/get_next_line.h \
				libs/includes/libft.h

HEADER_BONUS = libs/includes/miniRT_bonus.h

SRCS =			src/linked_lists/cylinder.c \
				src/linked_lists/obj.c \
				src/linked_lists/plane.c \
				src/linked_lists/sphere.c \
				src/parsing/get_id.c \
				src/parsing/get_objects.c \
				src/parsing/get_params.c \
				src/parsing/memory.c \
				src/parsing/parsing.c \
				src/parsing/tools_axis.c \
				src/parsing/tools_rgb.c \
				src/parsing/tools_rgb2.c \
				src/parsing/tools.c \
				src/color_tools.c \
				src/deal_keys_display.c \
				src/deal_keys_tools.c \
				src/deal_keys.c \
				src/deal_mouse.c \
				src/display_general.c \
				src/display_scene.c \
				src/hit_cylinder.c \
				src/hit_plane.c \
				src/hit_sphere.c \
				src/hit.c \
				src/main.c \
				src/maths_tools.c \
				src/tools.c \
				src/vector_tools.c \

SRCS_BONUS =	src_bonus/linked_lists/buf_bonus.c \
				src_bonus/linked_lists/cone_bonus.c \
				src_bonus/linked_lists/cylinder_bonus.c \
				src_bonus/linked_lists/light_bonus.c \
				src_bonus/linked_lists/obj_bonus.c \
				src_bonus/linked_lists/plane_bonus.c \
				src_bonus/linked_lists/sphere_bonus.c \
				src_bonus/parsing/get_id_bonus.c \
				src_bonus/parsing/get_objects_for_bonus.c \
				src_bonus/parsing/get_objects_bonus.c \
				src_bonus/parsing/get_params_bonus.c \
				src_bonus/parsing/memory_bonus.c \
				src_bonus/parsing/parsing_bonus.c \
				src_bonus/parsing/tools_axis_bonus.c \
				src_bonus/parsing/tools_rgb_bonus.c \
				src_bonus/parsing/tools_rgb2_bonus.c \
				src_bonus/parsing/tools_bonus.c \
				src_bonus/color_tools_bonus.c \
				src_bonus/deal_keys_bonus.c \
				src_bonus/deal_keys_display_bonus.c \
				src_bonus/deal_keys_tools_bonus.c \
				src_bonus/deal_mouse_bonus.c \
				src_bonus/display_general_bonus.c \
				src_bonus/display_scene_bonus.c \
				src_bonus/hit_bonus.c \
				src_bonus/hit_cylinder_bonus.c \
				src_bonus/hit_plane_bonus.c \
				src_bonus/hit_sphere_bonus.c \
				src_bonus/main_bonus.c \
				src_bonus/maths_tools_bonus.c \
				src_bonus/multi_threading_bonus.c \
				src_bonus/tools_bonus.c \
				src_bonus/vector_tools_bonus.c

OBJS =          $(SRCS:.c=.o)
OBJS_BONUS =	$(SRCS_BONUS:.c=.o)



INCLUDES =		-I./libs/includes

CPUS :=			$(shell sysctl -n hw.ncpu)
CC = 			gcc
AR = 			ar rsc
FLAGS =		 	-Wall -Wextra -Werror -DNUM_THREADS=$(CPUS) -Ofast -fno-strict-aliasing -fomit-frame-pointer -mtune=native -msse4.2 -mfpmath=sse -march=native -funsafe-math-optimizations -funroll-loops -ffast-math -flto -finline-functions
FLAGS_MLX = 	-L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit -g -lpthread -fsanitize=address  #-fsanitize=thread #

NAME =			miniRT

%.o:			%.c $(HEADER) $(HEADER_BONUS)
				@printf '\033[1m\033[38;95;13;64m'"\r\033[KCompiling miniRT objects... ⏳ "'\033[1m\033[38;217;0;83m'"<$<>"'\033[0m'
				@$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

all: 			$(NAME)
				

bonus: 			$(NAME)_bonus

$(NAME): 		$(OBJS) $(HEADER)
				@make all -C ./libs
				@$(CC) $(OBJS) ./libs/libft.a $(INCLUDES) $(FLAGS_MLX) -o $(NAME) 
					
$(NAME)_bonus: 	$(OBJS_BONUS) 
				@make all -C ./libs
				@$(CC) $(OBJS_BONUS) ./libs/libft.a $(INCLUDES) $(FLAGS_MLX) -o $(NAME)_bonus

#palmi:
#		@echo
#			@echo
#			@echo  "  $(green)▄▀▀▀▄ $(green)▄▄    $(d1)██████$(bg)╗  $(d1)█████$(bg)╗ $(d1)██$(bg)╗     $(d1)███$(bg)╗   $(d1)███$(bg)╗$(d1)██$(bg)╗$(d1)███$(bg)╗   $(d1)██$(bg)╗$(d1)██$(bg)╗$(d1)███████$(bg)╗$(d1)██$(bg)╗  $(d1)██$(bg)╗$(d1)███████$(bg)╗$(d1)██$(bg)╗     $(d1)██$(bg)╗     $(RESET) "
#			@echo  "   $(green)▄▀▀▄█▄ $(green)▀▄  $(d2)██$(bg)╔══$(d2)██$(bg)╗$(d2)██$(bg)╔══$(d2)██$(bg)╗$(d2)██$(bg)║     $(d2)████$(bg)╗ $(d2)████$(bg)║$(d2)██$(bg)║$(d2)████$(bg)╗  $(d2)██$(bg)║$(d2)██$(bg)║$(d2)██$(bg)╔════╝$(d2)██$(bg)║  $(d2)██$(bg)║$(d2)██$(bg)╔════╝$(d2)██$(bg)║     $(d2)██$(bg)║     $(RESET) "
#			@echo  "  $(green)▀   $(brown)█ $(green)▀▄    $(d3)██████$(bg)╔╝$(d3)███████$(bg)║$(d3)██$(bg)║     $(d3)██$(bg)╔$(d3)████$(bg)╔$(d3)██$(bg)║$(d3)██$(bg)║$(d3)██$(bg)╔$(d3)██$(bg)╗ $(d3)██$(bg)║$(d3)██$(bg)║$(d3)███████$(bg)╗$(d3)███████$(bg)║$(d3)█████$(bg)╗  $(d3)██$(bg)║     $(d3)██$(bg)║     $(RESET) "
#			@echo  "      $(brown)▐▌      $(d4)██$(bg)╔═══╝ $(d4)██$(bg)╔══$(d4)██$(bg)║$(d4)██$(bg)║     $(d4)██$(bg)║╚$(d4)██$(bg)╔╝$(d4)██$(bg)║$(d4)██$(bg)║$(d4)██$(bg)║╚$(d4)██$(bg)╗$(d4)██$(bg)║$(d4)██$(bg)║╚════$(d4)██$(bg)║$(d4)██$(bg)╔══$(d4)██$(bg)║$(d4)██$(bg)╔══╝  $(d4)██$(bg)║     $(d4)██$(bg)║     $(RESET) "
#			@echo  "  $(yellow)▄██████▄    $(d5)██$(bg)║     $(d5)██$(bg)║  $(d5)██$(bg)║$(d5)███████$(bg)╗$(d5)██$(bg)║ ╚═╝ $(d5)██$(bg)║$(d5)██$(bg)║$(d5)██$(bg)║ ╚$(d5)████$(bg)║$(d5)██$(bg)║$(d5)███████$(bg)║$(d5)██$(bg)║  $(d5)██$(bg)║$(d5)███████$(bg)╗$(d5)███████$(bg)╗$(d5)███████$(bg)╗$(RESET) "
#			@echo  "$(bg)              ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝$(RESET)"
#			@echo
#			@cat palmi.txt
#			@echo

clean:
				@rm -f $(OBJS) $(OBJS_BONUS)
				@make clean -C ./libs

fclean:			clean
				@rm -f $(NAME) $(NAME)_bonus
				@make fclean -C ./libs

re:
	make fclean
	make all

re_bonus:
	make fclean
	make bonus

run:
	./$(NAME) example.rt
run_bonus:
	./$(NAME)_bonus example.rt

rr:
	make re
	make run
r:
	make all
	make run
bb:
	make re_bonus
	make run_bonus
b:
	make bonus
	make run_bonus

.PHONY: 		all bonus clean fclean re re_bonus run rr r b bb

# Reset
RESET		=\033[0m

# Background
bg_black	=\033[40m

# Regular Colors
black		=\033[0;30m
red			=\033[0;31m
green		=\033[38;2;23;99;41m
yellow		=\033[38;2;238;153;47m
blue		=\033[0;34m
purple		=\033[0;35m
cyan		=\033[0;36m
blue_c		=\033[38;2;153;238;251m
white		=\033[0;37m
brown		=\033[38;2;158;72;29m
