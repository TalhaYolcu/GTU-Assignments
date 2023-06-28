#ifndef TIMERENTRY_H
#define TIMERENTRY_H

#include "ITimer.h"

// timer entry for each register timer is created
class TimerEntry {
    private:
        // when timer should work, updated on every period if any
        Timepoint timepoint;

        //for register type 2, end timepoint
        Timepoint endpoint;

        // what is the period of the timer
        Millisecs period;

        //what is termination predicate for this timer
        TPredicate predicate;

        //what code will work at this time
        TTimerCallback callback;       

        //determine the register type
        //default = -1, single timepoint = 0, period forever = 1
        //period until timepoint = 2, period with a predicate = 3
        int registerType=-1;

public:
        // > operator overload for comparing two TimerEntries
        // priority queues priority depends on this operator
        bool operator> (const TimerEntry& other) const;   

        // give access to Timer class
        friend class Timer;

        // run once, just callback and timepoint is given.
        TimerEntry(const Timepoint& tp, const TTimerCallback& cb);
        
        // run forever with a period.
        TimerEntry(const Millisecs& period, const TTimerCallback& cb);
        
        // run until given timepoint with period.
        TimerEntry(const Timepoint& tp, const Millisecs& period, const TTimerCallback& cb);
        
        // run periodically, after run check predicate.
        TimerEntry(const Millisecs& period,const TPredicate& pred,  const TTimerCallback& cb);
};
#endif