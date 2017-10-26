#include <pthread.h>
#include "caltrain.h"


// initilize station
// ************************************************
// ************************************************
void station_init(struct station *station){
	// FILL ME IN
	station.passenger_count=0;
	station.train_in_station=0;

	pthread_mutex_init(&station_key, NULL);
	pthread_mutex_init(&seats_key, NULL);

	pthread_cond_init(&train_arrived, NULL);
	pthread_cond_init(&seats_available, NULL);
	pthread_cond_init(&train_loaded, NULL);
}



// train arrives -> load passengers
// ************************************************
// ************************************************
void station_load_train(struct station *station, int count){

	// 01 - announce train has arrived
	pthread_mutex_lock(&station->station_key);
	station->seats_count=count;
	station->train_in_station=1;

	printf("\n****************************************************************");
	printf("\nTRAIN ARRIVED");
	printf("\n****************************************************************");

	// 01 - no passenger in station
	if(station->passenger_count==0){
		printf("\n****************************************************************");
		printf("\nTRAIN LEFT");
		printf("\n****************************************************************");
		pthread_mutex_unlock(&station->station_key);
		return;
	}

	// 02 - passengers are in station
	pthread_cond_broadcast(&station->train_arrived);
	pthread_cond_wait(&station->train_loaded, &station->station_key);

	station->train_in_station=0;
	printf("\n****************************************************************");
	printf("\nTRAIN LEFT");
	printf("\n****************************************************************");

	pthread_mutex_unlock(&station->station_key);

	return;
}



// passenger arrives -> wait for train
// ************************************************
// ************************************************
void station_wait_for_train(struct station *station){

	// 01 - add yourself to station
	pthread_mutex_lock(&station->station_key);
	//station->passenger_list.add(this);
	station->passenger_count+=1;

	printf("\npassenger arrived,\t passenger_count=%d", station->passenger_count);

	// 02 - wait on train
	// handle train already in station condition
	if(station->train_in_station==0){
		pthread_cond_wait(&station->train_arrived, &station->station_key);
	}

	pthread_mutex_lock(&station->seats_key);
	if(station->seats_count!=0){

		station->passenger_count-=1;
		station->seats_count-=1;
		printf("\npassenger boarded");

		if(station->passenger_count==0||station->seats_count==0){
			pthread_cond_signal(&station->train_loaded);
		}

	}
	
	pthread_mutex_unlock(&station->seats_key);
	pthread_mutex_unlock(&station->station_key);
	

}

// passenger boarding -> infrom train
// ************************************************
// ************************************************
void station_on_board(struct station *station){
	// FILL ME IN
}
