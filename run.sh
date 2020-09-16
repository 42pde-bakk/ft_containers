# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    run.sh                                             :+:    :+:             #
#                                                      +:+                     #
#    By: peerdb <peerdb@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/09/09 16:47:13 by peerdb        #+#    #+#                  #
#    Updated: 2020/09/16 22:38:48 by pde-bakk      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

make re && ./containers.out > ft.txt

sed "s/ft::/std::/g" main.cpp > stdmain.cpp

make re STD=1 && ./containers.out > std.txt

diff ft.txt std.txt

if [ $? -eq 1 ]; then
	echo "Diff failed"
else
	echo "Diff found no differences"
fi
