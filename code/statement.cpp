// It is used to set the number of threads to be used in the parallel region.
// omp_set_num_threads(4);

// It is used to fork the threads in the parallel region.
// #pragma omp parallel
 
// This function returns id of the thread
// omp_get_thread_num();

// In compiler (low level)
// void thunk()
// {
//     foobar();
// }

// pthread_t tid[4]
// for (int = 1; i < 4; i++)
// {
//     pthread_create(&tid[i], 0, &thunk, 0);
//     think();
// }

// for (int i = 1; i < 4; i++)
// {
//     pthread_join(tid[i], 0);
// }