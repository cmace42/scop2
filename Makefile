# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmace <cmace@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/16 18:35:57 by cmace             #+#    #+#              #
#    Updated: 2018/03/22 13:49:24 by cmace            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# BINAIRE
NAME = scop

# FLAGS DE COMPILE WOLLAH
CC = gcc
FLAGS = -g -fsanitize=address
# OTHERFLAGS = -O3
UNAME := $(shell uname)
LDFLAGS = -lSDL2

ifeq ($(UNAME), Linux)
LDFLAGS += -lm -lGL
endif
ifeq ($(UNAME), Darwin)
LDFLAGS += -framework OpenGl -framework GLUT
endif

LIBFTDIR = libft

# SOURCES
SRC = \
			main.c\
			window.c\
			loop.c\
			event.c\
			init.c\
			loadshader.c\
			mvp.c\
			tools.c\
			loadbmp.c\
			loadObj.c\
			objReader.c\
			toolsParsing.c\
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

GLSL = \
			vertexshader.glsl\
			fragmentshader.glsl\

OBJ = $(SRC:.c=.o) $(GLSL:.glsl=.o)

.PHONY: all
all: lib 
	make $(NAME)

$(NAME): $(OBJ)
	@echo "$(NAME) compilation : $(_CYAN)done$(_END)"
	@$(CC) $(OBJ) $(FLAGS) $(ADDFLAGS) -o $(NAME) -L $(LIBFTDIR) -lft $(LDFLAGS)

%.o: %.glsl
	@xxd -i $< | $(CC) -c -xc - -o $@

%.o: %.c
	@$(CC) $(FLAGS) $(ADDFLAGS) -I $(LIBFTDIR) -c $<

.PHONY: lib
lib:
	@make -C $(LIBFTDIR)

.PHONY: clean
clean:
	@$(RM) -f $(OBJ)
	@make clean -C $(LIBFTDIR)/
	@echo "clean $(NAME): $(_CYAN)done$(_END)"

.PHONY: fclean
fclean: clean
	@$(RM) -f $(NAME)
	@make fclean -C $(LIBFTDIR)
	@echo "fclean $(NAME): $(_CYAN)done$(_END)"

.PHONY: re
re: fclean all





# # BINARY
# NAME = scop

# # COMPILATION FLAGS
# CC = gcc
# FLAGS = -Wall -Wextra -Werror -O3
# ADDFLAGS =

# # DIRECTORIES


# # SOURCES
# SRC = \
# 			main.c\

# OBJ = $(SRC:.c=.o)

# # FILES

# # PROGRESS BAR
# T = $(words $(OBJ))
# N = 0
# C = $(words $N)$(eval N := x $N)
# ECHO = "[`expr $C  '*' 100 / $T`%]"

# #Colors
# _GREY=\x1b[30m
# _RED=\x1b[31m
# _GREEN=\x1b[32m
# _YELLOW=\x1b[33m
# _BLUE=\x1b[34m
# _PURPLE=\x1b[35m
# _CYAN=\x1b[36m
# _WHITE=\x1b[37m
# _END=\x1b[0m

# all: $(NAME)

# $(NAME): $(OBJ)
# 	@echo "\n$(NAME) compilation : $(_CYAN)done$(_END)"
# 	@$(CC) $(FLAGS) $(ADDFLAGS) -o $(NAME) $(OBJ)

# %.o: %.c
# 	@printf "%-60b\r" "$(ECHO) $(_CYAN) Compiling $@ $(_END)"
# 	@$(CC) $(FLAGS) $(ADDFLAGS) -c $<

# # $(LIBFT):
# # 	@make -C $(LIBFT_DIR)

# # $(MLIBX):
# # 	@make -C $(MLIBX_DIR)

# clean:
# 	@$(RM) -f $(OBJ)
# 	@echo "clean fillit: $(_CYAN)done$(_END)"

# fclean: clean
# 	@$(RM) -f $(NAME)
# 	@echo "fclean fdf: $(_CYAN)done$(_END)"

# re: fclean all

# .PHONY: all clean fclean re