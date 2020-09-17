# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    run.sh                                             :+:    :+:             #
#                                                      +:+                     #
#    By: peerdb <peerdb@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/09/09 16:47:13 by peerdb        #+#    #+#                  #
#    Updated: 2020/09/17 18:46:01 by pde-bakk      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#!/bin/bash
RED='\033[0;31m'
GREEN='\033[0;32m'
ORANGE='\033[0;33m'
PURPLE='\033[0;35m'
LIGHTPURPLE='\033[1;35m'
CYAN='\033[0;36m'
LIGHTCYAN='\033[1;36m'
RESET='\033[0m'
# echo "Passed" $# "arguments to run.sh" 
ARG=""
if [[ $1 == "REALG" ]]; then
	ARG="REALG=1"
fi

make fuckingclean

make re $ARG && ./containers.out > ft.txt

sed "s/ft::/std::/g" main.cpp > stdmain.cpp

make re STD=1 $ARG && ./containers.out > std.txt

diff ft.txt std.txt

if [ $? -eq 1 ]; then
	echo "${RED}Diff failed${RESET}"
else
	echo "${LIGHTPURPLE}Diff found no differences${RESET}"
fi
