// ******************************************************
// import libraries
// ******************************************************
#include <pthread.h>
#include <stdio.h>
#include "caltrain.h"


// ******************************************************
// initilize station
// ******************************************************
void station_init(struct station *station){
	// initialize station object
	station->waiting_passenger_count=0;
	station->available_seat_count=0;
	station->allowed_passenger_count=0;
	station->train_left=0;

	pthread_mutex_init(&station->station_key, NULL);

	pthread_cond_init(&station->train_arrived, NULL);
	pthread_cond_init(&station->train_loaded, NULL);
}

// ******************************************************
// train arrives ---> load passengers
// ******************************************************
void station_load_train(struct station *station, int count){
	// 01 - announce train has arrived
	pthread_mutex_lock(&station->station_key);
	station->train_left=0;
	station->available_seat_count=count;
	station->allowed_passenger_count=count;
	pthread_cond_broadcast(&station->train_arrived);

	// 02 - no passengers or no empty seats
	if(station->waiting_passenger_count==0||count==0){
		//station->available_seat_count=0;
		station->train_left=1;
		pthread_mutex_unlock(&station->station_key);
		return;
	}

	// 03 - passengers are in station
	pthread_cond_wait(&station->train_loaded, &station->station_key);
	station->train_left=1;
	printf("\nWaiting Passenger Count : %d\n", station->waiting_passenger_count);
	printf("\nTrain Left\n");
	pthread_mutex_unlock(&station->station_key);

	return;
}

// ******************************************************
// passenger arrives ---> wait for train % empty seats
// ******************************************************
void station_wait_for_train(struct station *station){
	// 01 - add yourself to station
	pthread_mutex_lock(&station->station_key);
	station->waiting_passenger_count+=1;
	// 02 - wait on train & available seats
	while(1){
		if((station->available_seat_count<=0)||(station->train_left==1)){
			// wait for next train (no seats available)
			pthread_cond_wait(&station->train_arrived, &station->station_key);
			continue;
		}else{
			// seats are available for this passenger
			station->waiting_passenger_count-=1;
			station->available_seat_count-=1;
			pthread_mutex_unlock(&station->station_key);
			printf("\nNew Creep Boarded\n");
			return;
		}
	}
	
}

// ******************************************************
// passenger boarding ---> infrom train
// ******************************************************
void station_on_board(struct station *station){
	// count each passenger as they board
	pthread_mutex_lock(&station->station_key);
	station->allowed_passenger_count-=1;

	if(station->waiting_passenger_count==0||station->allowed_passenger_count==0){
		// signal train to leave
		station->train_left=1;
		pthread_cond_signal(&station->train_loaded);
	}
	pthread_mutex_unlock(&station->station_key);
	return;


}
