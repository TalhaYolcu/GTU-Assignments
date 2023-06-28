
#include "Timer.h"
#include "ITimer.h"
#include <iostream>
#include "TimerEntry.h"
#include <queue>

using namespace std;

//constructor
Timer::Timer() {
    single_thread=std::thread(&Timer::singleThreadFunction,this);
}

void Timer::singleThreadFunction() {
    std::cout<<"Timer::thread function starting..."<<endl;
    std::unique_lock<std::mutex> lock(mutex);
    while (!halt_program) {
        if (!queue.empty()) {
            //queue is not empty
            auto now = CLOCK::now();
            auto next = queue.top();
            if(next.timepoint<=now) {
                //closest timepoint is reached
                switch (next.registerType)
                {
                case 0:
                    //timepoint reached, do the task
                    queue.pop();
                    lock.unlock();
                    next.callback();
                    lock.lock();
                    break;
                case 1:
                    //run with a period until forever
                    queue.pop();
                    lock.unlock();
                    next.callback();
                    registerTimer(next.period,next.callback);
                    lock.lock();
                    break;
                case 2:
                    //run with a period until tp
                    queue.pop();
                    lock.unlock();
                    next.callback();
                    if((next.period+now)<=next.endpoint) {
                        registerTimer(next.timepoint,next.period,next.callback);
                    }
                    lock.lock();
                    break;
                case 3:
                    //run with a period until predicate is false
                    queue.pop();
                    lock.unlock();
                    next.callback();
                    if(next.predicate()) {
                        registerTimer(next.predicate,next.period,next.callback);
                    }
                    lock.lock();
                    break;
                default:
                    std::cout<<"Unintented operation\n";
                    break;
                }
            }
            else {
                //there is time for the next timepoint
                cond_var.wait_until(lock,next.timepoint);
            }
        }
        else {
            //queue is empty, wait for the addition
            cond_var.wait(lock);
        }
    }
    std::cout<<"Timer::thread function terminating"<<endl;
}

//destructor
Timer::~Timer() {
    {
        std::unique_lock<std::mutex> lock(mutex);
        halt_program= true;
    }
    cond_var.notify_all();
    if (single_thread.joinable()) {
        single_thread.join();
    }
}

// run the callback once at time point tp.
void Timer::registerTimer(const Timepoint& tp, const TTimerCallback& cb) {
    std::unique_lock<std::mutex> lock(mutex);
    queue.push(TimerEntry(tp,cb));
    cond_var.notify_all();
}

// run the callback periodically forever. The first call will be executed after the first period.
void Timer::registerTimer(const Millisecs& period, const TTimerCallback& cb) {
    std::unique_lock<std::mutex> lock(mutex);
    queue.push(TimerEntry(period,cb));
    cond_var.notify_all();
}   

// Run the callback periodically until time point tp. The first call will be executed after the first period.
void Timer::registerTimer(const Timepoint& tp, const Millisecs& period, const TTimerCallback& cb) {
    std::unique_lock<std::mutex> lock(mutex);
    queue.push(TimerEntry(tp,period,cb));
    cond_var.notify_all();
}

// Run the callback periodically. After calling the callback every time, call the predicate to check if the
//termination criterion is satisfied. If the predicate returns false, stop calling the callback.
void Timer::registerTimer(const TPredicate& pred, const Millisecs& period, const TTimerCallback& cb) {
    std::unique_lock<std::mutex >lock(mutex);
    queue.push(TimerEntry(period,pred,cb));
    cond_var.notify_all();
}