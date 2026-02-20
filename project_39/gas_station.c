#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex_fuel;
pthread_cond_t cond_fuel;
int fuel = 0;

#define NUM_CARS 40
#define FUEL_FILL 20
#define FUEL_CONSUMPTION 100

struct car_info {
    pthread_t fn;
    int car_id;
};

static void* gas_station(void *arg)
{
    for (int i = 0; i < 200; i++) {    
        pthread_mutex_lock(&mutex_fuel);
        fuel += FUEL_FILL;
        printf("Filled fuel.. fuel = %d\n", fuel);
        pthread_mutex_unlock(&mutex_fuel);
        pthread_cond_broadcast(&cond_fuel);
        sleep(1);
    }
}

static void* car(void *arg)
{
    struct car_info *info = (struct car_info *)arg;
    int car_id = info->car_id;

    pthread_mutex_lock(&mutex_fuel);
    while (fuel < FUEL_CONSUMPTION) {
        printf("Car %d - Not enough fuel...\n", car_id);
        pthread_cond_wait(&cond_fuel, &mutex_fuel);
    }
    printf("Car %d: using fuel\n", car_id);
    fuel -= FUEL_CONSUMPTION;
    pthread_mutex_unlock(&mutex_fuel);
}

int main()
{
    struct car_info info[NUM_CARS];
    pthread_t gas_station_th;

    pthread_mutex_init(&mutex_fuel, NULL);

    pthread_create(&gas_station_th, NULL, &gas_station, NULL);

    for (int i = 0; i < NUM_CARS; i++) {
        info[i].car_id = i+1; 
        pthread_create(&info[i].fn, NULL, &car, &info[i]);
    }

    for (int i = 0; i < NUM_CARS; i++) {
        pthread_join(info[i].fn, NULL);
    }

    pthread_join(gas_station_th, NULL);

    pthread_mutex_destroy(&mutex_fuel);

    return 0;
}