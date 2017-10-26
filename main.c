// import libraries
// ************************************************
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// global variables
// ************************************************
struct station {

	int passenger_count;
	int passenger_list[];

	//int train_pointer;

}

// ************************************************
struct station cal_station;
pthread_mutex_t station_key;

pthread_cond_t train_arrived;
pthread_cond_t seats_available;
pthread_cond_t train_loaded;

pthread_mutex_t seats_key;
int availble_seats;


// thread function
// ************************************************
int main(){

	// initialize keys
	// ***************************************
	pthread_mutex_init(&station_key, NULL);
	pthread_mutex_init(&train_arrived, NULL);
	pthread_mutex_init(&seats_available, NULL);

	// spawn passengers
	// ***************************************
	while(1){

		// 01 - create passenger
		pthread_t passenger;
		pthread_create(&passenger, NULL, passenger_arrive, NULL);

		// 02 - 

	}

	// spawn trains
	// ***************************************
	while(1){

		pthread_t train;
		pthread_create(&train, NULL, train_arrive, NULL);

	}


	return 0;
}




void* passenger_arrive(void* arg){

	struct station *station = (struct station*)arg;

	// 01 - add yourself to station
	pthread_mutex_lock(&station_key);
	station->passenger_list.add(this);
	station->passenger_count+=1;

	// 02 - wait on train
	pthread_cond_wait(&train_arrived, &station_key);
	pthread_mutex_lock(&seats_key);
	passenger_count-=1;
	seats_available+=1;
	if(passenger_count==0||seats_available==0){
		pthread_cond_signal(&train_loaded);
	}
	pthread_mutex_unlock(&station_key);
	pthread_mutex_unlock(&seats_key);
	pthread_exit(0);


}



void* train_arrive(void* arg){

	struct station *station = (struct station*)arg;

	// 01 - announce train has arrived
	pthread_mutex_lock(&station_key);
	if(station->passenger_count==0){
		pthread_mutex_unlock(&station_key);
		pthread_exit(0);
	}
	pthread_cond_broadcast(&train_arrived);
	pthread_cond_wait(&train_loaded, &station_key);

	pthread_exit(0);


}