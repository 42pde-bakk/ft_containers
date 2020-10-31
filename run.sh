#!/bin/bash
# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    run.sh                                             :+:    :+:             #
#                                                      +:+                     #
#    By: peerdb <peerdb@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/09/09 16:47:13 by peerdb        #+#    #+#                  #
#    Updated: 2020/10/21 00:01:45 by peerdb        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

RED='\033[0;31m'
GREEN='\033[0;32m'
ORANGE='\033[0;33m'
PURPLE='\033[0;35m'
LIGHTPURPLE='\033[1;35m'
CYAN='\033[0;36m'
LIGHTCYAN='\033[1;36m'
RESET='\033[0m'

function test {
	for var in "$@"
	do
		if [[ $var == "debug" ]]; then
			D="DEBUG=1"
		elif [[ $var == "g++" || $var == "clang++" ]]; then
			C="COMPILER=$var"
			echo -e "${LIGHPURPLE}COMPILER = $var ${RESET}"
			echo -e "OSTYPE = $OSTYPE"
			if [[ $OSTYPE == *"darwin"* && $var == "g++" ]]; then
				C="COMPILER=$(brew --prefix)/bin/g++-10"
			fi
		elif [[ $var == "time" ]]; then
			TIME=$var
		elif [[ $var == "leaks" ]]; then
			LEAKS=$var
		fi
	done
	make fuckingclean

	sed "s/ft::/std::/g" tests/"$1"_main.cpp > tests/"$1"_stdmain.cpp

  echo -e "${RED}Compiling and testing for the STL version of the $1 container${RESET}"
	make "$1" $C $D STD=1 && ./containers.out "$TIME" "$LEAKS" > tests/std.txt #2>&1
	STATUS_STL=$?

  echo -e "${GREEN}Compiling and testing for my FT version of the $1 container${RESET}"
	make "$1" $C $D && ./containers.out "$TIME" "$LEAKS" > tests/ft.txt #2>&1
	STATUS_FT=$?

#	echo -e "${ORANGE}Startin testing for $1${RESET}"
	echo -e "${PURPLE}STATUS_FT = ${STATUS_FT}, STATUS_STL = ${STATUS_STL}${RESET}"
	if [[ $STATUS_FT -ne 0 || $STATUS_STL -ne 0 ]]; then
		exit
	fi

	diff tests/ft.txt tests/std.txt > tests/diff.txt;
	if [ $? -eq 1 ]; then
		echo -e "${RED}Diff failed${RESET}"
		cat tests/diff.txt
		exit 1
	else
		echo -e "${LIGHTPURPLE}Diff found no differences${RESET}"
	fi	
}

declare -a arr=("list" "vector" "map" "stack" "queue" "deque" "set" "multiset" "multimap")
ARG="all"
for var in "$@"
do
	for container in "${arr[@]}"
	do
		if [[ $var == "$container" ]]; then
			ARG=$container
		fi
	done
done

if [[ $ARG == "all" ]]; then
	for i in "${arr[@]}"
	do
		test "$i" "$1" "$2" "$3"
	done
else
	test "$ARG" "$2" "$3" "$4"
fi	


