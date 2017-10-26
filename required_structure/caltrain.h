#include <pthread.h>

struct station {
	
	int passenger_count;
	int train_in_station; // boolean

	pthread_mutex_t station_key;

	pthread_cond_t train_arrived;
	pthread_cond_t seats_available;
	pthread_cond_t train_loaded;

	pthread_mutex_t seats_key;
	int seats_count;
};

void station_init(struct station *station);

void station_load_train(struct station *station, int count);

void station_wait_for_train(struct station *station);

void station_on_board(struct station *station);