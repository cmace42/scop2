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

libobj.rootdir := $(dir $(lastword $(MAKEFILE_LIST)))

libobj.objects := reader.o type.o append.o create.o obj.o tools.o vertex.o triangle.o groupe.o
libobj.objects := $(addprefix $(libobj.rootdir)src/, $(libobj.objects))

$(libobj.objects): CFLAGS   ?= -Wall -Wextra -Werror
$(libobj.objects): CPPFLAGS += -MMD -MP -I$(libobj.rootdir)inc

# $(pointD) = reader.d type.d

.PHONY: all
all: libobj.a

libobj.a: libobj.a($(libobj.objects))

.PHONY: clean
clean::
	@$(RM) $(libobj.objects:.o=.{o,d,gcno,gcna})

.PHONY: fclean
fclean:: clean
	@$(RM) libobj.a

.PHNOY: re
re: fclean all

-include $(wildcard $(libobj.rootdir)src/*.d)
