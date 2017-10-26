// spawn passegners
// ************************************************
void* spawn_passengers(void* arg){

	while(1){
		// create passengers
		pthread_t passenger;
		pthread_create(&passenger, NULL, passenger_arrive, NULL);
		pthread_join(passenger, NULL);
	}

	pthread_exit(0);

}


// spawn trains
// ************************************************
void* spawn_trains(void* arg){

	while(1){
		// create passengers
		pthread_t train;
		pthread_create(&train, NULL, train_arrive, NULL);
		pthread_join(train, NULL);
	}

	pthread_exit(0);

}