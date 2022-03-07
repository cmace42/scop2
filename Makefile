export CPPFLAGS="-I/Users/$(USER)/.brew/opt/readline/include"
export LDFLAGS="-L/Users/$(USER)/.brew/opt/readline/lib"

NAME		=	scop
# --   Directory   -- #
OBJ_DIR	 =   ./objs
OBJLIB_DIR		= ./obj
INC_OBJLIB_DIR		= ./obj/inc
INC_DIR		=	./incs/

# --  Search All files in SRCS  -- #
SRC_DIR = $(shell find srcs -type d)
vpath %.c $(foreach dir, $(SRC_DIR), $(dir):)
# Grace a ca tu pourras faire autant de sous dossier 
# dans SRC_DIR, tout sera check

# GLSL_DIR = $(shell find srcs/glsl -type d)
# vpath %.glsl $(foreach dir, $(GLSL_DIR), $(dir):)

##############################
###      DEPENDENCIES      ###
##############################
DEP_DIR			=	dependencies
DEP				=	$(addprefix $(DEP_DIR)/, $(SRCS:.c=.d))
vpath				%.d $(DEP_DIR)

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
			interaction.c\
			mouse.c\
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
			vec3_dot.c\
			toRadian.c\
			printMat4.c\

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
DEPFLAGS		=	-MT $@ -MMD -MP -MF $(DEP_DIR)/$*.d -I $(INC_DIR)/ -I $(INC_OBJLIB_DIR)
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
LDFLAGS = -L $(OBJLIB_DIR) -lobj -lSDL2

ifeq ($(UNAME), Linux)
LDFLAGS += -lm -lGL
endif
ifeq ($(UNAME), Darwin)
LDFLAGS += -framework OpenGl -framework GLUT
endif


# ici un petit bloque de compile si jamais tu as besoin de diff OS

.PHONY: all
all : lib
	@make $(NAME) --no-print-directory
.PHONY: lib
lib:
	make -C $(OBJLIB_DIR) --no-print-directory

# No print directory c'est pour ne pas afficher les deplacement de dossier entre les different Makefile
# ( pour mute certaine lignes )

$(NAME): $(GLSLOBJ) $(OBJS)  $(INC_OBJLIB_DIR)/*.h $(INC_DIR)/*.h $(LIBFT_A)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(GLSLOBJ)  $(OSFLAG) $(LDFLAGS)
	echo "$(_GREEN)[100%] $(NAME) Compilation Success$(_ENDL)"

# J'ajoute en dependance les .h pour ne pas avec a faire make re quand je les change
# c'est pas encore super optimiser, mais cest un debut

$(OBJ_DIR)/%.o : %.c | $(OBJ_DIR) $(DEP_DIR)
	$(CC) $(CFLAGS) -o $@ -c $< $(DEPFLAGS) $(CPPFLAGS)
	@printf "%-65b\r" "$(_GREEN)$(ECHO)$(_CYAN) Compilation $(notdir $@)"

$(OBJ_DIR)/%.o: %.glsl | $(OBJ_DIR)
	@xxd -i $< | $(CC) -c -xc - -o $@

$(DEP_DIR)		:
				mkdir -p $(DEP_DIR)

# dependance indirecte de la regle OBJ_DIR pour que l'appelle a la regle ce fasse uniquement dans le cas ou elle n'existe pas

$(OBJ_DIR) :
	mkdir -p $@

# La regle de creation du dossier OBJ_DIR

.PHONY: clean
clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(_RED)[100%]$(_CYAN)  $(NAME) *.o has been cleaned"


.PHONY: dclean
dclean:
	@rm -rf $(dependencies)
	@echo "$(_RED)[100%]$(_CYAN)  $(NAME) *.d has been cleaned"

.PHONY: fclean
fclean: clean
	@make fclean -C $(OBJLIB_DIR) 
	@rm -f $(NAME)
	@echo "$(_RED)$(NAME) $(_CYAN)   has been cleaned"

.PHONY: remake
remake: fclean dclean all

.PHONY: re
re: fclean all