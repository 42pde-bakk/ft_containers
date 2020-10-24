# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: Peer <pde-bakk@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/25 17:28:30 by pde-bakk      #+#    #+#                  #
#    Updated: 2020/10/22 17:36:41 by peerdb        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = containers.out

ifdef COMPILER
 CXX = $(COMPILER)
endif

CXXFLAGS = -W -Wall -Wextra -Werror -pedantic -ansi -std=c++98
ifdef DEBUG
 CXXFLAGS += -g -fsanitize=address
else
 CXXFLAGS += -Ofast
endif

TESTDIR = tests
FILES = main.cpp
ifdef STD
 FILES = stdmain.cpp
endif

list vector map stack queue deque set multiset multimap: fclean
	$(CXX) $(CXXFLAGS) $(TESTDIR)/$@_$(FILES) -Isrcs/$@ -o $(NAME)
	
clean:

fclean: clean
	@rm -rf $(NAME) $(NAME).dSYM

fuckingclean: fclean
	@rm -f $(TESTDIR)/std.txt $(TESTDIR)/ft.txt $(TESTDIR)/*stdmain.cpp $(TESTDIR)/diff.txt

re: fclean

 