#include <limits.h>
#include "scheduler.h"

Task _tasks[MAX_TASKS];

void InitScheduler() {
	for (TaskId i=0; i < MAX_TASKS; ++i)
	{
		_tasks[i].state = EMPTY;
	}
}

inline static TaskId _find(TaskState st) {
	for (TaskId i = 0; i < MAX_TASKS; ++i) 
	{
		if (_tasks[i].state==st) {
			return i;
		}
	}
	return NONE;
}

inline static Time _soonest_task() {
	Time minTime = INT_MAX;
	for (TaskId i = 0; i < MAX_TASKS; ++i) 
	{
		Task& t = _tasks[i];
		if (t.state==WAITING) {
			if (minTime>t.delay) {
				minTime = t.delay;
			}
		}
	}
	return minTime;
}

inline static void _updateTasks(Time elapsed) {
	for (TaskId i = 0; i < MAX_TASKS; ++i) 
	{
		Task& t = _tasks[i];
		if (t.state==WAITING) {
			if (t.delay <= elapsed) {
				// Call the func
				t.func(t.param);
				// Reschedule
				if (t.period) {
					t.state = WAITING;
					t.delay = t.period;
				} else {
					t.state = EMPTY;
				}
			}
			else
			{
				t.delay -= elapsed;
			}
		}
	}
	
}

TaskId AddSchedulerTask(
	TaskFunction func, 
	Time period, 
	Time delay, 
	void* param, 
	Time elapsedTime) 
{
	// Update the tasks in the queue
	// Fire the events if necessary
	if (elapsedTime) {
		_updateTasks(elapsedTime);
	}

	// Insert the new task to the queue
	TaskId i = _find(EMPTY);
	if (i == NONE) {
		return 0;
	}
	Task& t = _tasks[i];
	t.func = func;
	t.period = period;
	t.delay = delay;
	t.param = param;
	t.state = WAITING;

	return i; 

}

Time SchedulerTick(Time elapsed) {
	_updateTasks(elapsed);
	return _soonest_task();
}

Time GetNextSchedulerTime() {
	return _soonest_task();
}

void RemoveSchedulerTask(TaskId taskId) {
	_tasks[taskId].state = EMPTY;
}

