# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: Peer <pde-bakk@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/25 17:28:30 by pde-bakk      #+#    #+#                  #
#    Updated: 2020/09/24 14:42:18 by peerdb        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = containers.out

ifeq ($(shell uname), Linux)
 CXX = g++
else
 CXX = clang++
endif
ifdef REALG
 CXX = ~/.brew/bin/g++-10
endif
ifdef CLANG
 CXX = clang++
endif

FLAGS = -W -Wall -Wextra -Werror -pedantic -std=c++98 -ansi

FILES = main.cpp
ifdef STD
 FILES = stdmain.cpp
endif

# all: $(NAME)

# $(NAME):
# 	$(CXX) $(FILES) $(FLAGS) -o $(NAME)

list: fclean
	$(CXX) $(FLAGS) list_$(FILES) -o $(NAME)

vector: fclean
	$(CXX) $(FLAGS) vector$(FILES) -o $(NAME)
	
clean:

fclean: clean
	rm -f $(NAME)

fuckingclean: fclean
	rm -f std.txt ft.txt *stdmain.cpp diff.txt

re: fclean

