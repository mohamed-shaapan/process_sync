// ******************************************************
// import libraries
// ******************************************************
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "thread_handler.h"


// ******************************************************
// passenger arrive thread function
// ******************************************************
void* passenger_arrive(void* arg){

	// 01 - add yourself to station
	pthread_mutex_lock(&station.station_key);
	station.waiting_passenger_count+=1;
	printf("\npassenger arrived, \twaiting list = %d", station.waiting_passenger_count);
	// 02 - wait on train & available seats
	while(1){
		if((station.available_seat_count<=0)||(station.train_left==1)){
			// wait for next train (no seats available)
			pthread_cond_wait(&station.train_arrived, &station.station_key);
			continue;
		}else{
			// seats are available for this passenger
			station.available_seat_count-=1;
			station.boarded_passenger_count+=1;
			station.waiting_passenger_count-=1;
			if((station.boarded_passenger_count==station.max_allowed_passengers)||(station.waiting_passenger_count==0)){
				// signal train to leave
				station.train_left=1;
				pthread_cond_signal(&station.train_loaded);
			}
			printf("\n\t\tpassenger boarded");
			pthread_mutex_unlock(&station.station_key);
			pthread_exit(0);;
		}
	}


}

// ******************************************************
// train arrives thread function
// ******************************************************
void* train_arrive(void* arg){

	int count=TRAIN_AVAILABLE_SEATS;
	// 01 - announce train has arrived
	pthread_mutex_lock(&station.station_key);
	printf("\n****************************************************************");
	printf("\nTRAIN ARRIVED");
	printf("\n****************************************************************");
	station.train_left=0;
	station.available_seat_count=count;
	station.boarded_passenger_count=0;
	station.max_allowed_passengers=count;
	pthread_cond_broadcast(&station.train_arrived);

	// 02 - no passengers or no empty seats
	if(station.waiting_passenger_count==0||count==0){
		station.train_left=1;
		printf("\n****************************************************************");
		printf("\nTRAIN LEFT");
		printf("\n****************************************************************");
		pthread_mutex_unlock(&station.station_key);
		pthread_exit(0);
	}

	while(1){
		// 03 - passengers are in station
		if((station.waiting_passenger_count==0)||(station.available_seat_count==0)){
			//printf("\n\t\tTrain Leaving\n");
			station.train_left=1;
			printf("\n****************************************************************");
			printf("\nTRAIN LEFT");
			printf("\n****************************************************************");
			pthread_mutex_unlock(&station.station_key);
			pthread_exit(0);
		}else{
			pthread_cond_wait(&station.train_loaded, &station.station_key);
			continue;
		}
	}


}