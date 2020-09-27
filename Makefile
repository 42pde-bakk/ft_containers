# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: Peer <pde-bakk@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/25 17:28:30 by pde-bakk      #+#    #+#                  #
#    Updated: 2020/09/28 01:47:41 by peerdb        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = containers.out

ifdef realg
 CXX = ~/.brew/bin/g++-10
endif
ifdef clang
 CXX = clang++
endif
ifdef g++
 CXX = clang++
endif

FLAGS = -W -Wall -Wextra -Werror -pedantic -std=c++98 -ansi 
ifdef DEBUG
 FLAGS += -g -fsanitize=address
endif

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
	$(CXX) $(FLAGS) vector_$(FILES) -o $(NAME)
	
clean:

fclean: clean
	@rm -f $(NAME)

fuckingclean: fclean
	@rm -f std.txt ft.txt *stdmain.cpp diff.txt

re: fclean

