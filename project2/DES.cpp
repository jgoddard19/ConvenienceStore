//
//  DES.cpp
//  Queueing Model
//  Starter code provided by A. Hornof and Y. Zhang - 2015-04-14
//  Modified by Jared Goddard - 4/21/15
//

#include "DES.h"
#include <queue>
#include <random>
double sum_between_arrivals;
double idle;
double wait_count;
double total_wait_time;
double avg_time_waiting;

void DES::initialize() {
    current_time = 0;
    idle = 0;
    wait_count = 0;
    arrival_count = 0;
    departure_count = 0;
    total_wait_time = 0;
    sum_between_arrivals=0;
    idle=0;
    wait_count=0;
    total_wait_time=0;
    avg_time_waiting =0;
    busy = false;
    // avg_queue = 0; // avg customers in queue
    
    while(!event_queue.empty()) {
        event_queue.pop();
    }
    
    Event e;
    e.time = current_time;
    arrive(e);
    
};

double DES::avg_wait_time(double t) {
    double ret = t/arrival_count;
    return ret;
}
double DES::probability_of_wait(double t) {
    double ret = t/arrival_count;
    return ret;
}
double DES::avg_service_time(double t) {
    double ret = t/arrival_count;
    return ret;
}
double DES::percent_idle(double i) {
    double ret = i/current_time;
    return ret;
}
double DES::avg_time_between_arrivals(double t) {
    double ret = t/(arrival_count - 1);
    return ret;
}
double DES::avg_wait_time_waiting(double t) {
    double ret = t/wait_count;
    return ret;
}
double DES::avg_time_spent(double t) {
    double ret = t;
    return ret;
}

void DES::run() {
    
    // The event loop, run until all the events are processed
    while (!event_queue.empty() && arrival_count < 100) {
        Event e = event_queue.top();
        event_queue.pop();
        
        // set the current time to the event time
        current_time = e.time;
        
        switch (e.type) {
            case ARRIVAL:
                arrive(e);
                break;
            case DEPARTURE:
                depart(e);
                break;
            default:
                break;
        }
    }
//    printf("Departure count: %d\n", departure_count);
//    printf("Arrival count: %d\n", arrival_count);
    
    trial_num++;
    
    printf("Trial number : %d, Average Waiting Time: %f, Probability customer has to wait: %f, Percent of time server is idle: %f, Average service time: %f, Average time between arrivals: %f, Average waiting time of those that wait: %f, Average time spent in system: %f \n",trial_num, avg_wait_time(total_wait_time), probability_of_wait(wait_count), percent_idle(idle), avg_service_time(current_time), avg_time_between_arrivals(sum_between_arrivals), avg_wait_time_waiting(avg_time_waiting), avg_time_spent(avg_wait_time_waiting(avg_time_waiting)+avg_service_time(current_time)));
}

void DES::arrive(Event e) {
    if (event_queue.size() <= 1) {
//        printf("Customer arrives at: %d\n", current_time);
        e.type = DEPARTURE;
        int s_time = generate_service_time();
        e.time = current_time + s_time;
//        printf("Customer now being serviced. Current time: %d\n", current_time);
//        printf("Departure scheduled for: %d\n", e.time);
        if(e.time - s_time != current_time) {
            avg_time_waiting += current_time - e.time;
        }
        busy = true;
        depart(e);
        Event e1;
        e1.type = ARRIVAL;
        e1.time = current_time + generate_inter_arrival_time();
//        printf("Next arrival scheduled for: %d\n", e1.time);
        event_queue.push(e1);
        arrival_count++;
        if (e.time < e1.time) {
            sum_between_arrivals += e1.time - e.time;
        } else {
            sum_between_arrivals += e.time - e1.time;
        }
    } else if (!event_queue.empty()) {
        event_queue.push(e);
        Event e1;
        e1.type = ARRIVAL;
        e1.time = current_time + generate_inter_arrival_time();
//        printf("Next arrival scheduled for: %d\n", e1.time);
        event_queue.push(e1);
        arrival_count++;
    } else if (e.time == current_time && busy == true) {
        Event e1;
        e1.type = ARRIVAL;
        e1.time = current_time + generate_inter_arrival_time();
//        printf("Next arrival scheduled for: %d\n", e1.time);
        event_queue.push(e1);
        arrival_count++;
        if (e.time < e1.time) {
            sum_between_arrivals += e1.time - e.time;
        } else {
            sum_between_arrivals += e.time - e1.time;
        }
    } else {
        event_queue.push(e);
    }
}

void DES::depart(Event e) {
    if (e.time == current_time) {
//        printf("Customer departs, time: %d\n", current_time);
        avg_time_waiting += current_time - (e.time - generate_service_time());
        departure_count++;
        busy = false;
    } else {
        total_wait_time += e.time - current_time;
        wait_count++;
        idle++;
        event_queue.push(e);
    }
}

int DES::generate_inter_arrival_time() {
    std::uniform_int_distribution<> arrive_time(1,10);
    int arrive = arrive_time(generator);
    return arrive;
}

int DES::generate_service_time() {
    std::uniform_int_distribution<> service_time(1,100);
    int val = service_time(generator);
    int service;
    if (val >= 1 && val <= 10) {
        service = 1;
        return service;
    } else if (val >= 11 && val <= 30) {
        service = 2;
        return service;
    } else if (val >= 31 && val <= 60) {
        service = 3;
        return service;
    } else if (val >= 61 && val <= 85) {
        service = 4;
        return service;
    } else if (val >= 86 && val <= 95) {
        service = 5;
        return service;
    } else if (val >= 96 && val <= 100) {
        service = 6;
        return service;
    }
    return service;
}
