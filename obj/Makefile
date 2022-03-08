# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmace <cmace@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/16 18:35:57 by cmace             #+#    #+#              #
#    Updated: 2022/03/08 11:25:25 by cmace            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

export CPPFLAGS="-I/Users/$(USER)/.brew/opt/readline/include"
export LDFLAGS="-L/Users/$(USER)/.brew/opt/readline/lib"

NAME		=	libobj.a

##############################
###      DEPENDENCIES      ###
##############################
DEP_DIR			=	dependencies
DEP				=	$(addprefix $(DEP_DIR)/, $(SRCS:.c=.d))
vpath				%.d $(DEP_DIR)

##############################
###         SOURCES        ###
##############################
SRC_DIR = $(shell find srcs -type d)
vpath %.c $(foreach dir, $(SRC_DIR), $(dir):)
SRCS =	reader.c type.c append.c create.c obj.c tools.c vertex.c triangle.c groupe.c

INC_DIR		=	./inc/
		
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
FLAG		= -Wall -Werror -Wextra
DEPFLAGS	= -MT $@ -MMD -MP -MF $(DEP_DIR)/$*.d -I $(INC_DIR)/ 

.PHONY: all
all :
	@make $(NAME) --no-print-directory

$(NAME): $(OBJS) $(INC_DIR)/*.h
	ar -rc $(NAME) $(OBJS)
	ranlib $(NAME)

$(OBJ_DIR)/%.o : %.c | $(OBJ_DIR) $(DEP_DIR)
	$(CC) $(FLAG) -o $@ -c $< $(DEPFLAGS) 
	@printf "%-65b\r" "$(_GREEN)$(ECHO)$(_CYAN) Compilation $(notdir $@)"

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
	@rm -f $(NAME)
	@echo "$(_RED)$(NAME) $(_CYAN)   has been cleaned"

.PHONY: remake
remake: fclean dclean all

.PHONY: re
re: fclean all