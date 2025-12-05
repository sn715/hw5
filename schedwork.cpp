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

bool setSched (
	size_t day, 
	size_t slot, 
	const AvailabilityMatrix& avail, 
	size_t dailyNeed, 
	size_t maxShifts, 
	vector<size_t>& shiftsWorked,
	DailySchedule& sched);

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

		size_t n = avail.size();
		size_t k = avail[0].size();

		sched.resize(n);

		for (size_t i = 0; i < n; i++) {
			sched[i].resize(dailyNeed);
		}

		std::vector<size_t> shiftsWorked(k, 0);

		return setSched(0, 0, avail, dailyNeed, maxShifts, shiftsWorked, sched);

}

bool setSched(
	size_t day, 
	size_t slot, 
	const AvailabilityMatrix& avail, 
	size_t dailyNeed, 
	size_t maxShifts, 
	vector<size_t>& shiftsWorked,
	DailySchedule& sched
)
{

	size_t n = avail.size();
	size_t k = avail[0].size();

	//base case
	if (day == n) {
		return true;
	}

	else if (slot == dailyNeed) {
		return setSched(day + 1, 0, avail, dailyNeed, maxShifts, shiftsWorked, sched);
	}

	for (Worker_T i = 0; i < k; i++) {
		//condition 1: must be avail
		if(avail[day][i]) {

			if(shiftsWorked[i] < maxShifts) {

				if(find(sched[day].begin(), sched[day].begin() + slot, i) ==
					sched[day].begin() + slot) {
						
						sched[day][slot] = i;
						shiftsWorked[i]++;

						if (setSched(day, slot + 1, avail, dailyNeed, maxShifts, shiftsWorked, sched)) {
							return true;
						}

						shiftsWorked[i]--;
					}
			}
		}
	}

	return false;

}
