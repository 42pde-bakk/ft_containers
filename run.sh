# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    run.sh                                             :+:    :+:             #
#                                                      +:+                     #
#    By: peerdb <peerdb@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/09/09 16:47:13 by peerdb        #+#    #+#                  #
#    Updated: 2020/09/26 14:45:13 by peerdb        ########   odam.nl          #
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

function test {
	if [[ $1 == "" ]]; then
		exit
	fi
	make fuckingclean

	sed "s/ft::/std::/g" $1_main.cpp > $1_stdmain.cpp

	make $1 STD=1 && ./containers.out > std.txt
	STATUS_STD=$?

	make $1 DEBUG=1 && ./containers.out > ft.txt
	STATUS_FT=$?

	echo $ECHOARG "${ORANGE}Startin testing for $1${RESET}"
	echo $ECHOARG "${PURPLE}STATUS_FT = ${STATUS_FT}, STATUS_STD = ${STATUS_STD}${RESET}"
	if [[ $STATUS_FT -ne 0 || $STATUS_STD -ne 0 ]]; then
		exit
	fi

	diff ft.txt std.txt > diff.txt;
	if [ $? -eq 1 ]; then
		echo $ECHOARG "${RED}Diff failed${RESET}"
	else
		echo $ECHOARG "${LIGHTPURPLE}Diff found no differences${RESET}"
	fi	
}

ARG=""
if [[ $1 == "list" || $1 == "vector" || $1 == "map" ]]; then
	ARG=$1
else
	ARG="all"
fi

if [[ $OSTYPE == *"linux"* ]]; then
	ECHOARG='-e'
else
	ECHOARG=''
fi

declare -a arr=("list" "vector" "map" "stack" "queue")
if [[ $ARG == "all" ]]; then
	for i in "${arr[@]}"
	do
		test $i
	done
else
	test $ARG
fi	
