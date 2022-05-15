#!/bin/sh 

srcs=$(find ./src -name '*.c')
objectFiles=""
flags="-g -Wall -Wextra -std=c17 -O2"
libs="-lpthread -lSDL2main -lSDL2 -lSDL2_image -lSDL2_gfx -lm"

for i in $srcs
do
	
	objectFiles="${objectFiles} obj/$(basename ${i%.*}).o"

	gcc ${flags} -c ${i} -o "obj/$(basename ${i%.*}).o" 

done 

# for i in $srcs 
# do 


# done

gcc ${objectFiles} -o bin/NEAT ${libs}


 
