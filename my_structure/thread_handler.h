#ifndef THREAD_HANDLER_H_   /* Include guard */
#define THREAD_HANDLER_H_

/* 
	- This function should be responsible for generating trains and passengers
*/
// ******************************************************
// global variables
// ******************************************************
struct station {
	
	int waiting_passenger_count;
	int available_seat_count;
	int boarded_passenger_count;
	int max_allowed_passengers;
	int train_left; // boolean

	pthread_mutex_t station_key;

	pthread_cond_t train_arrived;
	pthread_cond_t train_loaded;

};
// ************************************************
#define TRAIN_ARRIVE_TIME 500000 // micro-seconds = 0.5 secods
#define PASSENGER_ARRIVE_FREQUENCY 15000 // 150		15000
#define TRAIN_AVAILABLE_SEATS 5 // 500		5
struct station station;

// ******************************************************
// interface methods
// ******************************************************
void* passenger_arrive(void* arg);
void* train_arrive(void* arg);


#endif // COMMANDS_H_