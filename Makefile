MAKEFLAGS = "-j 10"

HEADER = 		libs/includes/miniRT.h \
				libs/includes/ft_printf_fd.h \
				libs/includes/get_next_line.h \
				libs/includes/libft.h


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
				src/deal_keys.c \
				src/display_general.c \
				src/display_scene.c \
				src/get_buffer.c \
				src/main.c \
				src/maths_tools.c \
				src/tools.c \
				src/vector_tools.c \

SRCS_BONUS =	src/main.c \

OBJS =          $(SRCS:.c=.o)
OBJS_BONUS =	$(SRCS_BONUS:.c=.o)

INCLUDES =		-I./libs/includes
INCLUDES/MLX =  -I./user/local/include

CC = 			gcc
AR = 			ar rsc

ifeq ($(USER), aroard)
	FLAGS = 		-Imlx -g -I ./libs/mlx -Ofast #-Wall -Wextra -Werror
	FLAGS_MLX =		-I ./libs/mlx -L ./libs/mlx -lmlx -lXext -lX11 -lm
else
	FLAGS =		 	-Wall -Wextra -Werror -g -O3
	FLAGS_MLX = 	-L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit -fsanitize=address
endif

NAME =			miniRT

%.o:			%.c $(HEADER)
				@printf '\033[1m\033[38;95;13;64m'"\r\033[KCompiling miniRT objects... ⏳ "'\033[1m\033[38;217;0;83m'"<$<>"'\033[0m'
				@$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $< 

all: 			$(NAME)

bonus: 			$(NAME)_bonus

mlx:			
				@make -C ./libs/mlx

$(NAME): 		$(OBJS) $(HEADER)
				@make all -C ./libs
				@$(CC) $(OBJS) ./libs/libft.a $(INCLUDES) $(FLAGS_MLX) -o $(NAME) 
					
$(NAME)_bonus: 	$(OBJS_BONUS) $(HEADER)
				@make all -C ./libs
				@$(CC) $(OBJS) ./libs/libft.a $(INCLUDES) $(FLAGS_MLX) -o $(NAME)_bonus

$(NAME)_debug: 	$(SRCS) #lldb minishell_debug -o "run"
				@make all -C ./libs
				$(CC) $(SRCS) -o $(NAME)_debug ./libs/libft.a -g $(INCLUDES) 

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

debug:      	$(NAME)_debug

run:
	./$(NAME) example_2.rt

rr:
	make re
	make run

r:
	make all
	make run

.PHONY: 		all bonus mlx clean fclean re re_bonus debug run rr r

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


#d1 =\033[38;2;192;66;138m
#d2 =\033[38;2;183;81;137m
#d3 =\033[38;2;174;93;135m
#d4 =\033[38;2;164;103;134m
#d5 =\033[38;2;153;113;132m
#d6 =\033[38;2;142;121;131m
#d7 =\033[0;37m

#d1 =\033[38;2;179;62;222m
#d2 =\033[38;2;149;74;226m
#d3 =\033[38;2;118;87;230m
#d4 =\033[38;2;88;99;233m
#d5 =\033[38;2;57;111;237m
#bg		=\033[38;2;192;66;138m

