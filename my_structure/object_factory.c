// ******************************************************
// import libraries
// ******************************************************
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "object_factory.h"
#include "thread_handler.h"



// ******************************************************
// create passenger threads
// ******************************************************
void* spawn_passengers(void* arg){
	// intialize random number generator
	srand(time(NULL));   
	while(1){
		// create passengers
		pthread_t passenger;
		pthread_create(&passenger, NULL, passenger_arrive, NULL);
		
		int interval = rand()%10;
		usleep(interval*PASSENGER_ARRIVE_FREQUENCY);
		//printf("\ninterval :%d -------------------------", interval);
	}
	pthread_exit(0);

}


// ******************************************************
// create train threads
// ******************************************************
void* spawn_trains(void* arg){
	// spawn train threads
	while(1){
		// create trains
		usleep(TRAIN_ARRIVE_TIME);
		pthread_t train;
		pthread_create(&train, NULL, train_arrive, NULL);
		pthread_join(train, NULL);
	}
	pthread_exit(0);

}