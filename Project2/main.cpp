#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

int pickup_forks(int, int);
int return_forks(int, int);

int main(int argc, char** argv) {
    srand(time(nullptr));

    //5 professors
    int philo0 = 0;
    int philo1 = 1;
    int philo2 = 2;
    int philo3 = 3;
    int philo4 = 4;
    //4 forks
    int currForkUsed = 0;


    //have one pick up 2 forks
    //currForkUsed = pickup_forks(prof0, 2);

    //setting up locks and threads
    pthread_mutex_t mutex;
    pthread_cond_t cond_Var;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_Var, NULL);


    currForkUsed = pickup_forks(philo0, rand() % 4);
    pthread_mutex_lock(&mutex);
    while (currForkUsed <= 4) {
        cout << "forkused " << currForkUsed << endl;
        currForkUsed = return_forks(philo0, currForkUsed);
        pthread_cond_wait(&cond_Var, &mutex);
    }
    pthread_mutex_unlock(&mutex);


}

int pickup_forks(int philosopher_number, int forksUsed) {
    //set random seed
    srand(time(nullptr));
    //pick up forks
    cout << "philosopher " << philosopher_number << " has picked up " << forksUsed << " forks." << endl;
    //thinking
    int sleepTimeMS = (rand() % 4) * 1000;
    cout << "philosopher " << philosopher_number << " was thinking for " << sleepTimeMS << " ms." << endl;
    usleep(sleepTimeMS);
    //eating
    sleepTimeMS = (rand() % 4) * 1000;
    cout << "philosopher " << philosopher_number << " was eating for " << sleepTimeMS << " ms." << endl;
    usleep(sleepTimeMS);

    //forksUsed is returns so the program can keep track of how many are used
    return forksUsed;
}

int return_forks(int philosopher_number, int forkUsed) {
    cout << "philosopher " << philosopher_number << " has dropped the fork." << endl;
    return forkUsed;
}