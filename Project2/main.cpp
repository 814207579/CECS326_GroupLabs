#include <iostream>
#include <pthread.h>
#include <cstdlib>

using namespace std;

void pickup_forks(int);
void return_forks(int);

int main(int argc, char** argv) {
    int num;

    for (int i = 0; i < 5; i++) {
        num = rand() % 3000;
        cout << num << endl;
    }

    //5 professors
    int prof0 = 0;
    int prof1 = 1;
    int prof2 = 2;
    int prof3 = 3;
    int prof4 = 4;
    //4 forks
    int currForkUsed = 0;


    pthread_mutex_t mutex;
    pthread_cond_t cond_Var;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_Var, NULL);

}

void pickup_forks(int philosopher_number) {
    //cout something about picking up the forks
}

void return_forks(int philosopher_number) {

}