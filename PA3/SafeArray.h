#ifndef SAFEARRAY_H
#define SAFEARRAY_H

#define ARRAY_SIZE 10 //max elements in the stack
#define MAX_INPUT_FILES 100 //- Maximum number of hostname file arguments allowed
#define MAX_REQUESTER_THREADS 10 //- Maximum number of concurrent requester threads allowed
#define MAX_RESOLVER_THREADS 10 //- Maximum number of concurrent resolver threads allowed
#define MAX_NAME_LENGTH 255 //- Maximum size of a hostname including the null terminator
#define MAX_IP_LENGTH INET6_ADDRSTRLEN //- INET6_ADDRSTRLEN is the maximum size IP address string util.c will return



typedef struct{
	//10 entries, with each entry being
	//a sequence of 255 characters representing a hostname
	char array[ARRAY_SIZE][MAX_NAME_LENGTH]; //[hostnames][hostname characters]
	int pointer; //current position of hostnames
} SafeArray;

int  create(SafeArray *array); // init the array
int destroy(SafeArray *array); // free the array's resources

int get_pointer(SafeArray *array); //returns pointer index
int offset_pointer(SafeArray *array, int offset); //shifts pointer


const char* read(SafeArray *array); //returns top of safeArray. decrements pointer
int write(SafeArray *array, char * content); //inserts into safeArray. increments pointer

#endif