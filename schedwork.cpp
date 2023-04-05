#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool recurse(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched

) {
  int num_workers = avail[0].size();
  int num_days = avail.size();

  vector<int> worker_work_days;
  worker_work_days.resize(num_workers);

  for (int i = 0; i < num_days; i++) { // i indicates the day
    if (sched[i].size() != dailyNeed) {
      for (int worker_id = 0; worker_id < num_workers; worker_id++) {
        if (avail[i][worker_id]) {
          sched[i].push_back(worker_id);
          worker_work_days[worker_id]++;
          if (worker_work_days[worker_id] > maxShifts) {
            recurse(avail, dailyNeed, maxShifts, sched);// TODO:: parameters need to be updated to skip the already explored case
          }
        }
      }
    }
  }
}


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below




}

