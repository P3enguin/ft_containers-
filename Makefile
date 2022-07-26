# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/11 09:01:37 by ybensell          #+#    #+#              #
#    Updated: 2022/11/14 17:02:00 by ybensell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = container

STL = stl
STL_SRC = stl.cpp

SRC = main.cpp

OBJ = ${SRC:.cpp=.o}

CC = c++

CPPFLAGS = -Wall -Wextra -Werror -std=c++98

HEADER = map.hpp Vector.hpp stack.hpp set.hpp

RM = rm -rf

%.o:%.c $(HEADER)
	$(CC) $(CPPFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJ) $(HEADER)
	$(CC) $(CPPFLAGS) $(OBJ) -o $(NAME)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME) $(STL)

stl : $(SRC)
	$(CC) $(CPPFLAGS) $(STL_SRC) -o $(STL)

re : fclean all