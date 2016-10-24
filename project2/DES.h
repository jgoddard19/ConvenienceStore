//
//  DES.h
//  Queueing Model
//  Starter code provided by A. Hornof and Y. Zhang - 2015-04-14
//  Modified by Jared Goddard - 4/21/15
//

#ifndef __Queueing_Model__DES__
#define __Queueing_Model__DES__

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <random>

// Only two event types
enum EventType {ARRIVAL, DEPARTURE};



typedef unsigned int Time;

struct Event {
    Time time;
    EventType type;
    
    bool operator< (const Event& y) const {
        return y.time < time;
    }
};


class DES {
public:
    void initialize();
    void run();
    
    // __ Students: Add your statistic variables here.
    // int avg_customers = 0; // avg customers in queue
    int arrival_count;
    int departure_count;
    bool busy;
    int trial_num = 0;
    double sum_between_arrivals;
    double idle;
    double wait_count;
    double total_wait_time;
    double avg_time_waiting;
    
private:
    
    // __ Students: You  need to implement the following methods.
    void arrive(Event e);
    void depart(Event e);
    
    // Use std::uniform_int_distribution<> to generate random numbers.
    int generate_inter_arrival_time();
    int generate_service_time();
    
    double avg_wait_time(double t);
    double probability_of_wait(double t);
    double avg_service_time(double t);
    double percent_idle(double i);
    double avg_time_between_arrivals(double t);
    double avg_wait_time_waiting(double t);
    double avg_time_spent(double t);
    
    Time current_time = 0;
    
    // Seed the random number generator as follows.
    std::linear_congruential_engine<std::uint_fast32_t, 48271, 0, 2147483647> generator =
    std::linear_congruential_engine<std::uint_fast32_t, 48271, 0, 2147483647>(410510);
    
    // Create an event queue with C++'s priority_queue data structure.
    // priority_queue is an abstract interface to provide a standardization of the methods for all priority_queues.
    // The abstract interface insures that methods (in this case such as pop(), push(), and empty()) will be implemented.
    // Behind the scenes, priority_queue is implemented as a heap.
    // This particularly priority queue uses a vector as a container for the elements.
    std::priority_queue<Event, std::vector<Event>> event_queue;
    
};

#endif /* defined(__Queueing_Model__DES__) */
