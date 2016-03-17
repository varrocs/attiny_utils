#pragma once

#ifndef F_CPU
#error F_CPU is needed for correct delays
#endif

// Constants
#define MAX_TASKS 10
#define NONE 0xff

// Types
typedef void (*TaskFunction)(void* param);
typedef int Time;
typedef enum {EMPTY, WAITING} TaskState;
typedef unsigned char TaskId;

// Interface
void InitScheduler();
TaskId AddSchedulerTask(
		TaskFunction func, 
		Time delay, 
		Time period = 0, 
		void* param = (void*)0, 
		Time elapsedTime = 0);
Time SchedulerTick(Time millis);
Time GetNextSchedulerTime();
void RemoveSchedulerTask(TaskId taskId);

// Private
typedef struct Task {
	TaskFunction func;	// The function to run
	// If not null this means the running period
	Time period;
	// Time till the next run
	Time delay;
	void* param;
	TaskState state;
} Task;

