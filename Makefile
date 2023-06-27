# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aantonio <aantonio@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/07 22:50:02 by aantonio          #+#    #+#              #
#    Updated: 2023/06/27 13:39:53 by aantonio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := gcc
CFLAGS := -Wall -Wextra -Werror
RM = rm -rf
PROGRAM1    := server
PROGRAM2    := client
SRC1 := server.c
SRC2 := client.c

OBJ1 := $(SRC1:.c=.o)
OBJ2 := $(SRC2:.c=.o)

all: $(PROGRAM1) $(PROGRAM2)

$(PROGRAM1): $(OBJ1)
		ar rc $(PROGRAM1) $(OBJ1)

$(PROGRAM2): $(OBJ2)
		ar rc $(PROGRAM2) $(OBJ2)

clean:
		$(RM) $(OBJ1) $(OBJ2)
		
fclean: clean
		$(RM) $(PROGRAM1) $(PROGRAM2)
re: fclean all

.PHONY = all clean fclean re


