# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    setpaths.sh                                        :+:    :+:             #
#                                                      +:+                     #
#    By: pde-bakk <pde-bakk@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/10/20 12:14:16 by pde-bakk      #+#    #+#                  #
#    Updated: 2020/10/20 12:46:29 by pde-bakk      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

declare -a arr=("list" "vector" "map" "stack" "queue")
for container in "${arr[@]}"
do
	R=$(find . -iname $container.hpp 2>/dev/null)
	# echo "Find: $F, Replace with $R" 
	sed "s?mycontainerpath?${R}?g" -i ./tests/"$container"_main.cpp
done
			
