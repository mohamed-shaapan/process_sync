int main()
{ pthread_t producer, consumer;
//initialize mutex and condition variables

pthread_cond_init(&cond_availData, NULL); /* Initialize consumer condition variable */
pthread_cond_init(&cond_availSpace, NULL); /* Initialize producer condition variable */
//create producer thread
pthread_create(&producer, NULL, produce, NULL);
//create consumer thread
pthread_create(&consumer, NULL, consume, NULL);
//wait for threads to finish
pthread_join(producer, NULL);
pthread_join(consumer, NULL);
//cleanup
 /*free up the mutex*/
pthread_cond_destroy(&cond_availData); /* Free up consumer condition variable */
pthread_cond_destroy(&cond_availSpace); /* Free up producer condition variable */
//exit main thread
pthread_exit(NULL);
}





void condition_api(){

	// create mutex & initialize mutex
	pthread_cond_t condition;
	pthread_condattr_t attr;

	pthread_condattr_init(&attr);
	pthread_cond_init(&condition, attr);

	pthread_cond_wait(&condition, &key);
	pthread_cond_signal(&train_loaded);
	pthread_cond_broadcast(&train_loaded);

	pthread_condattr_destroy(&attr);
	pthread_cond_destroy(&key);


}


void mutex_api(){

	// create mutex & initialize mutex
	pthread_mutex_t key;
	pthread_mutexattr_t attr;
	
	pthread_mutexattr_init(&attr);
	pthread_mutex_init(&key, attr);

	pthread_mutex_lock(&key);
	pthread_mutex_unlock(&key);

	pthread_mutexattr_destroy(&attr);
	pthread_mutex_destroy(&key);


}