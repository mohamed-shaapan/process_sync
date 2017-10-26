// import libraries
// ***********************************************************************
// ***********************************************************************
// ***********************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


// global variables
// ***********************************************************************
// ***********************************************************************
// ***********************************************************************
struct station {

	int passenger_count;
	int train_in_station;
	//int passenger_list[];
	//int train_pointer;

};
// ************************************************
#define TRAIN_ARRIVE_TIME 500000 // micro-seconds = 0.5 secods
#define PASSENGER_ARRIVE_FREQUENCY 150 // 150		15000
#define TRAIN_AVAILABLE_SEATS 500 // 500		5

struct station cal_station;
pthread_mutex_t station_key;

pthread_cond_t train_arrived;
pthread_cond_t seats_available;
pthread_cond_t train_loaded;

pthread_mutex_t seats_key;
int seats_count;


// ***********************************************************************
// ***********************************************************************
// ***********************************************************************
// passenger function
// ************************************************
void* passenger_arrive(void* arg){

	//printf("\npassenger created");

	struct station *station = (struct station*)arg;

	// 01 - add yourself to station
	pthread_mutex_lock(&station_key);
	station->passenger_count+=1;
	pthread_mutex_unlock(&station_key);

	printf("\npassenger arrived,\t passenger_count=%d", station->passenger_count);

	// 02 - wait on train
	pthread_mutex_lock(&seats_key);
	while(1){

		if(seats_count>0){
			
			pthread_mutex_lock(&station_key);
			station->passenger_count-=1;
			seats_count-=1;
			printf("\npassenger boarded");

			if(station->passenger_count==0||seats_count==0){
				pthread_cond_signal(&train_loaded);
			}
			pthread_mutex_unlock(&seats_key);
			pthread_mutex_unlock(&station_key);
			break;

		}else{
			// wait for next train
			pthread_cond_wait(&train_arrived, &seats_key);
			continue;
		}

	}
	
	pthread_exit(0);


}


// train function
// ************************************************
void* train_arrive(void* arg){

	struct station *station = (struct station*)arg;

	// 01 - announce train has arrived
	pthread_mutex_lock(&station_key);
	seats_count=TRAIN_AVAILABLE_SEATS;
	station->train_in_station=1;

	printf("\n****************************************************************");
	printf("\nTRAIN ARRIVED");
	printf("\n****************************************************************");

	if(station->passenger_count==0){
		printf("\n****************************************************************");
		printf("\nTRAIN LEFT");
		printf("\n****************************************************************");

		pthread_mutex_unlock(&station_key);
		pthread_exit(0);
	}
	pthread_cond_broadcast(&train_arrived);
	pthread_cond_wait(&train_loaded, &station_key);

	printf("\n****************************************************************");
	printf("\nTRAIN LEFT");
	printf("\n****************************************************************");

	station->train_in_station=0;
	pthread_mutex_unlock(&station_key);

	pthread_exit(0);


}


// ***********************************************************************
// ***********************************************************************
// ***********************************************************************
// spawn passegners
// ************************************************
void* spawn_passengers(void* arg){

	srand(time(NULL));   // intialize random number generator

	while(1){
		// create passengers
		pthread_t passenger;
		pthread_create(&passenger, NULL, passenger_arrive, &cal_station);
		
		int interval = rand()%10;
		usleep(interval*PASSENGER_ARRIVE_FREQUENCY);
		//printf("\ninterval :%d -------------------------", interval);
	}

	pthread_exit(0);

}


// spawn trains
// ************************************************
void* spawn_trains(void* arg){

	while(1){
		// create trains
		usleep(TRAIN_ARRIVE_TIME);

		pthread_t train;
		pthread_create(&train, NULL, train_arrive, &cal_station);

		//printf("\ntrain left");

		pthread_join(train, NULL);
		
	}

	pthread_exit(0);

}

// ***********************************************************************
// ***********************************************************************
// ***********************************************************************
// main function
// ************************************************
int main(){

	// initialize keys
	// ***************************************
	cal_station.passenger_count=0;
	cal_station.train_in_station=0;

	pthread_mutex_init(&station_key, NULL);
	pthread_mutex_init(&seats_key, NULL);

	
	pthread_cond_init(&train_arrived, NULL);
	pthread_cond_init(&seats_available, NULL);
	pthread_cond_init(&train_loaded, NULL);

	// spawn passengers
	// ***************************************
	pthread_t passenger_factory;
	pthread_create(&passenger_factory, NULL, spawn_passengers, NULL);

	pthread_t train_factory;
	pthread_create(&train_factory, NULL, spawn_trains, NULL);

	pthread_join(passenger_factory, NULL);
	pthread_join(train_factory, NULL);


	// spawn trains
	// ***************************************



	return 0;
}