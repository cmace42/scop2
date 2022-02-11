# **************************************************************************** #
#																			  #
#														 :::	  ::::::::	#
#	Makefile										   :+:	  :+:	:+:	#
#													 +:+ +:+		 +:+	  #
#	By: cmace <cmace@student.42.fr>				+#+  +:+	   +#+		 #
#												 +#+#+#+#+#+   +#+			#
#	Created: 2018/02/16 18:35:57 by cmace			 #+#	#+#			  #
#	Updated: 2018/03/22 13:49:24 by cmace			###   ########.fr		#
#																			  #
# **************************************************************************** #

export CPPFLAGS="-I/Users/$(USER)/.brew/opt/readline/include"
export LDFLAGS="-L/Users/$(USER)/.brew/opt/readline/lib"

NAME		=	scop
# --   Directory   -- #
OBJ_DIR	 =   ./objs
LIB_DIR		=   ./libft
OBJLIB_DIR		= ./obj
INC_OBJLIB_DIR		= ./obj/inc
INC_DIR		=	./
INC_LIB_DIR =	./libft/incs

# --  Search All files in SRCS  -- #
SRC_DIR = ./ #$(shell find srcs -type d)
vpath %.c $(foreach dir, $(SRC_DIR), $(dir):)
# Grace a ca tu pourras faire autant de sous dossier 
# dans SRC_DIR, tout sera check


SRCS =	\
			main.c\
			window.c\
			loop.c\
			event.c\
			init.c\
			model.c\
			loadshader.c\
			mvp.c\
			tools.c\
			loadbmp.c\
			renderer.c\
			time.c\
			mat4_identity.c\
			mat4_mult.c\
			mat4_rotation.c\
			mat4_scaling.c\
			mat4_translation.c\
			vec3_add.c\
			vec3_cross.c\
			vec3_div.c\
			vec3_length.c\
			vec3_mult.c\
			vec3_new.c\
			vec3_normalisation.c\
			vec3_sub.c\
			toRadian.c\
			printMat4.c\
#		etc.. 
# #			loadObj.c
# #			#toolsParsing.c 
# #			objReader.c

GLSL = \
			vertexshader.glsl\
			fragmentshader.glsl\

# Seulement les fichiers donner explicitement ici
# seront chercher ( avec vpath ) et compiler

# SRCS = $(foreach dir, $(SRC_DIR), $(foreach file, $(wildcard $(dir)/*.c), $(notdir $(file))))

# Cette commande te permet de remplacer SRCS, elle compilera tout tes fichier .c 
# Dans SRC_DIR recursivement dans tout les sous dossier ( ATTENTION PAS SECU / et pas a la norme 42)

# --  Redirection in OBJS  -- #
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))
GLSLOBJ = $(addprefix $(OBJ_DIR)/,$(GLSL:.glsl=.o))
# OBJ = $(SRC:.c=.o) $(GLSL:.glsl=.o)

# addprefix permet de rediriger a la creation dans le dossier garbage

# --   Compilation flags  -- #
CC			=	gcc
CFLAGS	  =   -Wall -Wextra -Werror -fsanitize=address
# --  Animation Calcul %  -- #
T = $(words $(OBJS) 0)
N = 0
C = $(words $N)$(eval N := x $N)
ECHO = "[`expr $C '*' 100 / $T`%]"

# Tout ca c'est toi qui me la donner, normalement tu te rappelle comment ca marche

# --  Color   -- #
_CYAN  = \033[36m
_GREEN = \033[32m
_RED   = \033[31m
_ENDL  = \033[0m

UNAME = $(shell uname)
# --  Check OS for Additional Flags %  -- #
LDFLAGS = -L $(OBJLIB_DIR) -lobj -L $(LIB_DIR) -lft -lSDL2

ifeq ($(UNAME), Linux)
LDFLAGS += -lm -lGL
endif
ifeq ($(UNAME), Darwin)
LDFLAGS += -framework OpenGl -framework GLUT
endif

LIBOBJ_A = ./obj/libobj.a
LIBFT_A = ./libft/libft.a


# ici un petit bloque de compile si jamais tu as besoin de diff OS

.PHONY: all
all : lib
	@make $(NAME) --no-print-directory
.PHONY: lib
lib:
	@make -C $(LIB_DIR) --no-print-directory
	make -C $(OBJLIB_DIR) --no-print-directory

# No print directory c'est pour ne pas afficher les deplacement de dossier entre les different Makefile
# ( pour mute certaine lignes )

$(NAME): $(GLSLOBJ) $(OBJS)  $(INC_OBJLIB_DIR)/*.h $(INC_DIR)/*.h $(LIBOBJ_A) $(LIBFT_A)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(GLSLOBJ)  $(OSFLAG) $(LDFLAGS)
	echo "$(_GREEN)[100%] $(NAME) Compilation Success$(_ENDL)"

# J'ajoute en dependance les .h pour ne pas avec a faire make re quand je les change
# c'est pas encore super optimiser, mais cest un debut

$(OBJ_DIR)/%.o : %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $< -I $(INC_DIR)  -I $(INC_LIB_DIR) -I $(INC_OBJLIB_DIR) $(CPPFLAGS)
	@printf "%-65b\r" "$(_GREEN)$(ECHO)$(_CYAN) Compilation $(notdir $@)"

$(OBJ_DIR)/%.o: %.glsl | $(OBJ_DIR)
	@xxd -i $< | $(CC) -c -xc - -o $@

# dependance indirecte de la regle OBJ_DIR pour que l'appelle a la regle ce fasse uniquement dans le cas ou elle n'existe pas

$(OBJ_DIR) :
	mkdir -p $@



# La regle de creation du dossier OBJ_DIR

.PHONY: clean
clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIB_DIR) --no-print-directory
	@echo "$(_RED)[100%]$(_CYAN)  $(NAME) *.o has been cleaned"

.PHONY: fclean
fclean: clean
	@make fclean -C $(LIB_DIR) --no-print-directory
	@make fclean -C $(OBJLIB_DIR) 
	@rm -f $(NAME)
	@echo "$(_RED)$(NAME) $(_CYAN)   has been cleaned"

.PHONY: re
re: fclean all

# # BINAIRE
# NAME = scop

# # FLAGS DE COMPILE WOLLAH
# CC = gcc
# FLAGS = -g -fsanitize=address
# # OTHERFLAGS = -O3
# UNAME := $(shell uname)
# LDFLAGS = -lSDL2

# ifeq ($(UNAME), Linux)
# LDFLAGS += -lm -lGL
# endif
# ifeq ($(UNAME), Darwin)
# LDFLAGS += -framework OpenGl -framework GLUT
# endif

# LIBFTDIR = libft

# # SOURCES
# SRC = \
# 			main.c\
# 			window.c\
# 			loop.c\
# 			event.c\
# 			init.c\
# 			loadshader.c\
# 			mvp.c\
# 			tools.c\
# 			loadbmp.c\
# 			renderer.c\
# 			time.c\
# 			mat4_identity.c\
# 			mat4_mult.c\
# 			mat4_rotation.c\
# 			mat4_scaling.c\
# 			mat4_translation.c\
# 			vec3_add.c\
# 			vec3_cross.c\
# 			vec3_div.c\
# 			vec3_length.c\
# 			vec3_mult.c\
# 			vec3_new.c\
# 			vec3_normalisation.c\
# 			vec3_sub.c\
# 			toRadian.c\
# 			printMat4.c\

# #			loadObj.c
# #			#toolsParsing.c 
# #			objReader.c
# GLSL = \
# 			vertexshader.glsl\
# 			fragmentshader.glsl\

# OBJ = $(SRC:.c=.o) $(GLSL:.glsl=.o)

# .PHONY: all
# all: lib 
# 	make $(NAME)

# $(NAME): $(OBJ)
# 	@echo "$(NAME) compilation : $(_CYAN)done$(_END)"
# 	$(CC) $(OBJ) $(FLAGS) $(ADDFLAGS) -o $(NAME) -L obj -lobj -L $(LIBFTDIR) -lft $(LDFLAGS)

# %.o: %.glsl
# 	@xxd -i $< | $(CC) -c -xc - -o $@

# %.o: %.c
# 	$(CC) $(FLAGS) $(ADDFLAGS) -I obj/inc -I $(LIBFTDIR) -c $<

# .PHONY: lib
# lib:
# 	@make -C $(LIBFTDIR)
# 	@make -C obj/

# .PHONY: clean
# clean:
# 	@$(RM) -f $(OBJ)
# 	@make clean -C $(LIBFTDIR)/
# 	@echo "clean $(NAME): $(_CYAN)done$(_END)"

# .PHONY: fclean
# fclean: clean
# 	@$(RM) -f $(NAME)
# 	@make fclean -C $(LIBFTDIR)
# 	@echo "fclean $(NAME): $(_CYAN)done$(_END)"

# .PHONY: re
# re: fclean all





# # # BINARY
# # NAME = scop

# # # COMPILATION FLAGS
# # CC = gcc
# # FLAGS = -Wall -Wextra -Werror -O3
# # ADDFLAGS =

# # # DIRECTORIES


# # # SOURCES
# # SRC = \
# # 			main.c\

# # OBJ = $(SRC:.c=.o)

# # # FILES

# # # PROGRESS BAR
# # T = $(words $(OBJ))
# # N = 0
# # C = $(words $N)$(eval N := x $N)
# # ECHO = "[`expr $C  '*' 100 / $T`%]"

# # #Colors
# # _GREY=\x1b[30m
# # _RED=\x1b[31m
# # _GREEN=\x1b[32m
# # _YELLOW=\x1b[33m
# # _BLUE=\x1b[34m
# # _PURPLE=\x1b[35m
# # _CYAN=\x1b[36m
# # _WHITE=\x1b[37m
# # _END=\x1b[0m

# # all: $(NAME)

# # $(NAME): $(OBJ)
# # 	@echo "\n$(NAME) compilation : $(_CYAN)done$(_END)"
# # 	@$(CC) $(FLAGS) $(ADDFLAGS) -o $(NAME) $(OBJ)

# # %.o: %.c
# # 	@printf "%-60b\r" "$(ECHO) $(_CYAN) Compiling $@ $(_END)"
# # 	@$(CC) $(FLAGS) $(ADDFLAGS) -c $<

# # # $(LIBFT):
# # # 	@make -C $(LIBFT_DIR)

# # # $(MLIBX):
# # # 	@make -C $(MLIBX_DIR)

# # clean:
# # 	@$(RM) -f $(OBJ)
# # 	@echo "clean fillit: $(_CYAN)done$(_END)"

# # fclean: clean
# # 	@$(RM) -f $(NAME)
# # 	@echo "fclean fdf: $(_CYAN)done$(_END)"

# # re: fclean all

# # .PHONY: all clean fclean re