export CPPFLAGS="-I/Users/$(USER)/.brew/opt/readline/include"
export LDFLAGS="-L/Users/$(USER)/.brew/opt/readline/lib"

NAME		=	scop

##############################
###      DEPENDENCIES      ###
##############################
DEP_DIR			=	dependencies
DEP				=	$(addprefix $(DEP_DIR)/, $(SRCS:.c=.d))
vpath				%.d $(DEP_DIR)

##############################
###         LIBRARY        ###
##############################
OBJLIB_DIR		= ./obj
INC_OBJLIB_DIR		= ./obj/inc

##############################
###         SOURCES        ###
##############################
SRC_DIR = $(shell find srcs -type d)
vpath %.c $(foreach dir, $(SRC_DIR), $(dir):)
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

INC_DIR		=	./incs/
		
##############################
###          OBJS          ###
##############################
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))
GLSLOBJ = $(addprefix $(OBJ_DIR)/,$(GLSL:.glsl=.o))
OBJ_DIR	 =   ./objs

##############################
###         FLAGS          ###
##############################
CC			=	gcc
DEPFLAGS		=	-MT $@ -MMD -MP -MF $(DEP_DIR)/$*.d -I $(INC_DIR)/ -I $(INC_OBJLIB_DIR)
CFLAGS	  =   -Wall -Wextra -Werror #-fsanitize=address
UNAME = $(shell uname)
LDFLAGS = -L $(OBJLIB_DIR) -lobj -lSDL2
ifeq ($(UNAME), Linux)
LDFLAGS += -lm -lGL
endif
ifeq ($(UNAME), Darwin)
LDFLAGS += -framework OpenGl -framework GLUT
endif

.PHONY: all
all : lib
	@make $(NAME) --no-print-directory
.PHONY: lib
lib:
	make -C $(OBJLIB_DIR) --no-print-directory

$(NAME): $(GLSLOBJ) $(OBJS)  $(INC_OBJLIB_DIR)/*.h $(INC_DIR)/*.h $(LIBFT_A)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(GLSLOBJ)  $(OSFLAG) $(LDFLAGS)

$(OBJ_DIR)/%.o : %.c | $(OBJ_DIR) $(DEP_DIR)
	$(CC) $(CFLAGS) -o $@ -c $< $(DEPFLAGS) $(CPPFLAGS)
	@printf "%-65b\r" "$(_GREEN)$(ECHO)$(_CYAN) Compilation $(notdir $@)"

$(OBJ_DIR)/%.o: %.glsl | $(OBJ_DIR)
	@xxd -i $< | $(CC) -c -xc - -o $@

$(DEP_DIR)		:
				mkdir -p $(DEP_DIR)

$(OBJ_DIR) :
	mkdir -p $@

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