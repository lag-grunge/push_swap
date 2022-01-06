# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    benchmark7.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbrazhni <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/29 17:15:18 by vbrazhni          #+#    #+#              #
#    Updated: 2022/01/06 04:21:18 by sdalton          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

MAX=0
ITERATIONS=0
LIMIT=700
FILE=problem_100
SUM=0

for i in $(seq 1 $2)
do
		export ARG="$(ruby -e "puts (1..$1).to_a.shuffle.join(' ')")"
		if ./$3 $ARG | ./checker $ARG | grep -q KO
		then
			echo "Error!"
			echo $ARG
			break
		fi
		NUMBER="$(./$3 $ARG | wc -l | sed 's/ //g')"
		if [ "$NUMBER" -gt "$LIMIT" ]
			then
			echo $NUMBER >> $FILE
			echo $ARG >> $FILE
		fi
		if [ "$NUMBER" -gt "$MAX" ]
			then
			MAX=$NUMBER;
		fi
		echo $i ":" $NUMBER
		SUM=$(($SUM+$NUMBER));
		ITERATIONS=$((ITERATIONS+1));
done

echo "AVG: $(($SUM / $ITERATIONS))"
echo "MAX: " $MAX
