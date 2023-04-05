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
bool trace(
  AvailabilityMatrix &avail,
  size_t n, // day
  size_t d, // need position
  const size_t dailyNeed,
  const size_t maxShifts,
  DailySchedule &sched,
  vector<int>& worker_work_days
) {
  int num_workers = avail[0].size();
  int num_days = avail.size();

  size_t n_cpy = n;
  size_t d_cpy = d;
  DailySchedule sched_cpy = sched;
  vector<int> worker_work_days_cpy = worker_work_days;

  bool res = false;

  for (int i = 0; i < num_workers; i++) {
    n = n_cpy;
    d = d_cpy;
    sched = sched_cpy;
    worker_work_days = worker_work_days_cpy;

    if (avail[n][i] && worker_work_days[i] < maxShifts) {
      sched[n][d] = i;
      worker_work_days[i]++;
      avail[n][i] = false;
      d++;

      if (d < dailyNeed) {
        res = trace(avail, n, d, dailyNeed, maxShifts, sched, worker_work_days);
        if (res) {
          return res;
        }
      } else if (d == dailyNeed && n + 1 != num_days) {
        res = trace(avail, n+1, 0, dailyNeed, maxShifts, sched, worker_work_days);
        if (res) {
          return res;
        }
      } else if (d == dailyNeed && n + 1 == num_days) { 
        return true;
      }
      avail[n][i] = true;
    } 
  }

  return false;
}

// Add your implementation of schedule() and other helper functions here
void workdayFill(vector<int>& workerDay, int n) {
  if (workerDay.size() < n) {
    workerDay.push_back(0);
    workdayFill(workerDay, n);
  }
}


void workersFill(vector<Worker_T>& workers, int n) {
  if (workers.size() < n) {
    workers.push_back(INVALID_ID);
    workersFill(workers, n);
  }
}

void schedFill(DailySchedule& sched, int avail_size, int n, int dailyNeed) {
  if (n < avail_size) {
    vector<Worker_T> workers;
    workersFill(workers, dailyNeed);
    sched.push_back(workers);
    n++;
    schedFill(sched, avail_size, n, dailyNeed);

  }
}

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

  int num_workers = avail[0].size();
  vector<int> worker_work_days;

  workdayFill(worker_work_days, num_workers);

  schedFill(sched, avail.size(), 0, dailyNeed);

  AvailabilityMatrix avail_cpy = avail;

  return trace(avail_cpy, 0, 0, dailyNeed, maxShifts, sched, worker_work_days);
}

