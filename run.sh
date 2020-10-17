# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    run.sh                                             :+:    :+:             #
#                                                      +:+                     #
#    By: peerdb <peerdb@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/09/09 16:47:13 by peerdb        #+#    #+#                  #
#    Updated: 2020/10/17 18:21:21 by peerdb        ########   odam.nl          #
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

function test {
	for var in $@
	do
		if [[ $var == "debug" ]]; then
			D="DEBUG=1"
		elif [[ $var == "g++" || $var == "clang" ]]; then
			C="COMPILER=$var"
			echo "OSTYPE = $OSTYPE"
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

	sed "s/ft::/std::/g" $1_main.cpp > $1_stdmain.cpp

	make $1 $C $D STD=1 && ./containers.out $TIME $LEAKS > std.txt #2>&1
	STATUS_STD=$?

	make $1 $C $D && ./containers.out $TIME $LEAKS > ft.txt #2>&1
	STATUS_FT=$?

	echo $ECHOARG "${ORANGE}Startin testing for $1${RESET}"
	echo $ECHOARG "${PURPLE}STATUS_FT = ${STATUS_FT}, STATUS_STD = ${STATUS_STD}${RESET}"
	if [[ $STATUS_FT -ne 0 || $STATUS_STD -ne 0 ]]; then
		exit
	fi

	echo "Container = $1" > diff.txt
	diff ft.txt std.txt >> diff.txt;
	if [ $? -eq 1 ]; then
		echo $ECHOARG "${RED}Diff failed${RESET}"
		cat diff.txt
		return 1
	else
		echo $ECHOARG "${LIGHTPURPLE}Diff found no differences${RESET}"
	fi	
}

if [[ $OSTYPE == *"linux"* ]]; then
	ECHOARG='-e'
else
	ECHOARG=''
fi

declare -a arr=("list" "vector" "map" "stack" "queue")
ARG="all"
for var in $@
do
	for container in "${arr[@]}"
	do
		if [[ $var == $container ]]; then
			ARG=$container
		fi
	done
done

if [[ $ARG == "all" ]]; then
	for i in "${arr[@]}"
	do
		test $i $2 $3 $4
		if [ $? -eq 1 ]; then
			exit 1
		fi
	done
else
	test $ARG $2 $3 $4
	if [ $? -eq 1 ]; then
		exit 1
	fi
fi	


