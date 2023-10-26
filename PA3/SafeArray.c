#include "SafeArray.h" //our little Safearray header file
#include "semaphore.h"
#include "stdlib.h"
#include "string.h"
#include "pthread.h"
#include "stdio.h"

#define ARRAY_SIZE 10 //Max elements in the stack
#define MAX_NAME_LENGTH 255 //Maximum size of a hostname including the null terminator


//MAN FILES
//STDLIB: https: //man7.org/linux/man-pages/man0/stdlib.h.0p.html
//STRING: https://man7.org/linux/man-pages/man3/string.3.html
//PTHREAD: https://man7.org/linux/man-pages/man7/pthreads.7.html
//SEMAPHORE: https://man7.org/linux/man-pages/man7/sem_overview.7.html
//STDIO: https://man7.org/linux/man-pages/man3/stdio.3.html


//CREATE MUTEX, SEMAPHORE, AND CONDITION VARIABLES



sem_t canRead;
sem_t canWrite;
int readCount = 0;
int writeCount = ARRAY_SIZE;


pthread_mutex_t mutex;

//if x_waiting, y locks. Vice versa
pthread_cond_t writers_waiting;
pthread_cond_t readers_waiting;

pthread_mutex_t writers_waiting_mutex;
pthread_mutex_t readers_waiting_mutex;


//FUNCTIONS TO BUILD - - - - - - - - - - - - - - - - - - - - - - - - - - - -

//input: a safearray structure
//processing: initialize safearray structure, set pointer to 0
//output: returns 1 on success
int  create(safearray *array){
	array->pointer = 0;

	//init semaphores
	sem_init(canRead, 1, readCount);
	sem_init(canWrite, 1, canWrite);


	//init conditionals
	pthread_cond_init(writers_waiting, writers_waiting_mutex);
	pthread_cond_init(readers_waiting, readers_waiting_mutex);

	//init mutex not necessary


	return 1;
} // init the stack



//input: a safearray structure
//processing: set pointer to 0. Set all values to "0" for security reasons?
//output: returns 1 on success
int destroy(SafeArray *array){
	array->pointer = 0;


	//destroy semaphores
	sem_destroy(&canRead);
	sem_destroy(&canWrite);


	//destroy conditionals
	pthread_cond_destroy(&writers_waiting);
	pthread_cond_destroy(&readers_waiting);

	return 1;
} // free the stack's resources



//processsing: acquire pointer SAFELY
//output: returns the pointer
int get_pointer(SafeArray *array){
	//lock()
	 pthread_mutex_lock(&mutex);

	int i = array->pointer;

	//unlock()
	pthread_mutex_unlock(&mutex);

	return i;
} //returns pointer index



//input: a safe array structure, and offset to adjust pointer position
//processing: increment pointer by offset
//return: 1 on success and inside bounds. 0 on success and outside bounds
int offset_pointer(SafeArray *array, int offset){
	int inside = 1; 
	//lock()
	pthread_mutex_lock(&mutex);

	array->pointer = array->pointer + offset;
	if ((array->pointer < 0) || (array->pointer >= 10)){
		inside = 0;
	}

	//unlock()
	pthread_mutex_unlock(&mutex);

	return inside;
} // update the pointer of stack



//input: a safe array structure.
//processing: acquire string from pointer. Decrement pointer.
//return: String of hostname
const char* read(SafeArray *array){

	char *content = "initial content";

	//signal want to read to writers
	pthread_cond_wait(readers_waiting);

	//enter semaphore reading queue
	sem_wait(canRead);

	//do reading. assign String to content
	memcpy(content, &array[get_pointer(&array)], MAX_NAME_LENGTH);


	//decrement pointer
	offset_pointer(&array, -1);

	//release lock for potential writers
	pthread_cond_signal(writers_waiting);

	return content;
} //returns top of safeArray. decrements pointer


//input: a safe array structure, a string of characters.
//processing: increment pointer. Insert string of characters.
//return: 1 on success. 0 on failure.
int write(SafeArray *array, char * content){



	return 1;
} //inserts into safeArray. increments pointer






int main(){
	return 0;
}







