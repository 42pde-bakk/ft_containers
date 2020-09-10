# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    run.sh                                             :+:    :+:             #
#                                                      +:+                     #
#    By: peerdb <peerdb@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/09/09 16:47:13 by peerdb        #+#    #+#                  #
#    Updated: 2020/09/10 13:28:42 by peerdb        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

sed "s/ft/std/g" main.cpp > stdmain.cpp

make re && ./containers.out > ft.txt

make re STD=1 && ./containers.out > std.txt

diff ft.txt std.txt
