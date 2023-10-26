//testfield
#include <string.h>
#include <stdio.h>
#include "SafeArray.h"
#include <stdlib.h>

int main() {
    SafeArray array;
    int i;


    if (create(&array) < 0) exit(-1); // init stack, exit if failed

	// push random numbers until full
    while ( get_pointer(&array) >= 0){
    	write(&array, "hello world");

    }
    
    char* content;

 	// pop and print until empty
    while ( get_pointer(&array) <= 10){
    	content = read(&array);

    	printf("%s", content);


    }

    destroy(&array); // destroy stack
    printf("\n- - - - - - - - - - - - - -\n[Bounds test complete]\n");


    return 0;
}

