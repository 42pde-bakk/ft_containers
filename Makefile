# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: Peer <pde-bakk@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/25 17:28:30 by pde-bakk      #+#    #+#                  #
#    Updated: 2020/09/10 20:10:29 by peerdb        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = containers.out

ifeq ($(shell uname), Linux)
 CXX = clang++
else
 CXX = clang++
endif
ifdef REALG
 CXX = ~/.brew/bin/g++-10
endif

FLAGS = -W -Wall -Wextra -Werror -pedantic -std=c++98 -ansi
#-Weffc++ -Wshadow

FILES = main.cpp
ifdef STD
 FILES = stdmain.cpp
endif

all: $(NAME)

$(NAME):
	$(CXX) $(FILES) $(FLAGS) -o $(NAME)
	
clean:
	# rm -f std.txt ft.txt stdmain.cpp

fclean: clean
	rm -f $(NAME)

fuckingclean: fclean
	rm -f std.txt ft.txt stdmain.cpp

re: fclean all

