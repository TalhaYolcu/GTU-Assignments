#include "ITimer.h"
#include "TimerEntry.h"
#include <chrono>

using CLOCK = std::chrono::high_resolution_clock;

// run once, just callback and timepoint is given.
TimerEntry::TimerEntry(const Timepoint& tp, const TTimerCallback& cb) {
    this->timepoint=tp;
    this->callback=cb;
    this->registerType=0;
}

// run forever with a period.
TimerEntry::TimerEntry(const Millisecs& period, const TTimerCallback& cb) {
    auto current_time=CLOCK::now();
    this->timepoint=current_time+period;
    this->period=period;
    this->callback=cb;
    this->registerType=1;
}


// run until given timepoint with period.
TimerEntry::TimerEntry(const Timepoint& tp, const Millisecs& period, const TTimerCallback& cb) {
    auto current_time=CLOCK::now();    
    this->timepoint=current_time+period;
    this->period=period;
    this->callback=cb;
    this->registerType=2;
    this->endpoint=tp;
}


// run periodically, after run check predicate.
TimerEntry::TimerEntry(const Millisecs& period, const TPredicate& pred,  const TTimerCallback& cb) {
    auto current_time=CLOCK::now();
    this->predicate=pred;
    this->timepoint=current_time+period;
    this->callback=cb;
    this->period=period;
    this->registerType=3;
}

// operator overload
bool TimerEntry::operator> (const TimerEntry& other) const {
    return timepoint> other.timepoint;
}
