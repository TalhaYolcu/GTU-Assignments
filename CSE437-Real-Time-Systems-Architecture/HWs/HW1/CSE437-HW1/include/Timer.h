#ifndef Timer_H
#define Timer_H

#include <ITimer.h>
#include <thread>
#include <queue>
#include <chrono>
#include <functional>
#include <mutex>
#include <condition_variable>
#include "TimerEntry.h"
class Timer : public ITimer {
    public:
        //constructor
        Timer();

        //destructor
        ~Timer();

        // run the callback once at time point tp.
        void registerTimer(const Timepoint& tp, const TTimerCallback& cb);

        // run the callback periodically forever. The first call will be executed after the first period.
        void registerTimer(const Millisecs& period, const TTimerCallback& cb);

        // Run the callback periodically until time point tp. The first call will be executed after the first period.
        void registerTimer(const Timepoint& tp, const Millisecs& period, const TTimerCallback& cb);

        // Run the callback periodically. After calling the callback every time, call the predicate to check if the
        //termination criterion is satisfied. If the predicate returns false, stop calling the callback.
        void registerTimer(const TPredicate& pred, const Millisecs& period, const TTimerCallback& cb);

        //Thread function
        void singleThreadFunction();

    private:
        // single thread
        std::thread single_thread;    

        // priority queue for TimerEntries
        std::priority_queue<TimerEntry, std::vector<TimerEntry>, std::greater<TimerEntry>> queue;

        //mutex to wait
        std::mutex mutex;

        //condition variable to wait and wake up
        std::condition_variable cond_var;

        //flag to end program
        bool halt_program=false;
};
#endif