#include <pthread.h>

struct station {
	
	int waiting_passenger_count;
	int available_seat_count;
	int allowed_passenger_count;
	int train_left; // boolean

	pthread_mutex_t station_key;

	pthread_cond_t train_arrived;
	pthread_cond_t train_loaded;

	
};

void station_init(struct station *station);

void station_load_train(struct station *station, int count);

void station_wait_for_train(struct station *station);

void station_on_board(struct station *station);