# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: Peer <pde-bakk@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/25 17:28:30 by pde-bakk      #+#    #+#                  #
#    Updated: 2020/10/16 15:59:04 by peerdb        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = containers.out

ifdef COMPILER
 CXX = $(COMPILER)
endif

CXXFLAGS = -W -Wall -Wextra -Werror -pedantic -ansi -std=c++98 -Ofast
ifdef DEBUG
 CXXFLAGS += -g -fsanitize=address
endif

FILES = main.cpp
ifdef STD
 FILES = stdmain.cpp
endif

# all: $(NAME)

# $(NAME):
# 	$(CXX) $(FILES) $(CXXFLAGS) -o $(NAME)

list vector map stack queue: fclean
	$(CXX) $(CXXFLAGS) $@_$(FILES) -o $(NAME)
	
clean:

fclean: clean
	@rm -rf $(NAME) $(NAME).dSYM

fuckingclean: fclean
	@rm -f std.txt ft.txt *stdmain.cpp diff.txt

re: fclean

 