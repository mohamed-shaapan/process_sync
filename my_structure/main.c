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
// run main application
// ******************************************************
int main(){

	// initialize keys
	station.waiting_passenger_count=0;
	station.available_seat_count=0;
	station.boarded_passenger_count=0;
	station.max_allowed_passengers=0;
	station.train_left=0;
	pthread_mutex_init(&station.station_key, NULL);
	pthread_cond_init(&station.train_arrived, NULL);
	pthread_cond_init(&station.train_loaded, NULL);

	// spawn passengers
	pthread_t passenger_factory;
	pthread_create(&passenger_factory, NULL, spawn_passengers, NULL);
	// spawn trains
	pthread_t train_factory;
	pthread_create(&train_factory, NULL, spawn_trains, NULL);

	// wait on factory threads
	pthread_join(passenger_factory, NULL);
	pthread_join(train_factory, NULL);

	return 0;
}