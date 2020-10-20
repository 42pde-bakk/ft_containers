# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: Peer <pde-bakk@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/25 17:28:30 by pde-bakk      #+#    #+#                  #
#    Updated: 2020/10/20 15:04:27 by pde-bakk      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = containers.out

ifdef COMPILER
 CXX = $(COMPILER)
endif

CXXFLAGS = -W -Wall -Wextra -Werror -pedantic -ansi -std=c++98 -O3
ifdef DEBUG
 CXXFLAGS += -g -fsanitize=address
endif

TESTDIR = tests
FILES = main.cpp
ifdef STD
 FILES = stdmain.cpp
endif

list vector map stack queue: fclean
	$(CXX) $(CXXFLAGS) $(TESTDIR)/$@_$(FILES) -Isrcs/$@ -o $(NAME)
	
clean:

fclean: clean
	@rm -rf $(NAME) $(NAME).dSYM

fuckingclean: fclean
	@rm -f std.txt ft.txt *stdmain.cpp diff.txt

re: fclean

 