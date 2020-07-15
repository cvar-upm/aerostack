/**
 * Description: Objects of class cvgThread open a separate thread which constantly calls a virtual run() method 
 * that may be overloaded by the programmer to perform custom processing. 
 * start() and stop() methods are provided to control the execution of the thread.
 * Author: Ignacio Mellado (CVG)
 * Last revision: 22/11/2010
 */

#include "cvgThread.h"

#define DEFAULT_STOP_TIMEOUT	(5000)
#define DEFAULT_KILL_TIMEOUT	(5000)
#define WORKER_LOOP_WAIT	(0)

// By the time it's being written, ETIMEDOUT is not defined on Cygwin. Instead, WSAETIMEDOUT is used.
#ifndef ETIMEDOUT
#define ETIMEDOUT	116
#endif

#ifndef CVG_WINDOWS
#include <signal.h>
#endif

cvgThread::cvgThread(std::string *name) {
	created = false;
	started = false;
	setName(name);
	setStopTimeout(DEFAULT_STOP_TIMEOUT);
}

cvgThread::cvgThread(const char *name) {
	started = false;
	created = false;
	setName(name);
	setStopTimeout(DEFAULT_STOP_TIMEOUT);
}

cvgThread::~cvgThread() {
	destroy();
}

void cvgThread::create() {
	if (created) return;
#ifdef CVG_WINDOWS
	if ((endEvent = CreateEvent(NULL, FALSE, FALSE, NULL)) == NULL)
		throw cvgException("Unable to create end event");
	if ((endedEvent = CreateEvent(NULL, FALSE, FALSE, NULL)) == NULL) {
		CloseHandle(endEvent);
		throw cvgException("Unable to create ended event");
	}
#endif
	created = true;
}

void cvgThread::destroy() {
	if (!created) return;
    thread_stop();
#ifdef CVG_WINDOWS
	CloseHandle(endEvent);
	CloseHandle(endedEvent);
#endif
	created = false;
}

void cvgThread::thread_start() {
	create();
#ifdef CVG_WINDOWS
	ResetEvent(endedEvent);
	ResetEvent(endedEvent);
	if ((handle = CreateThread(NULL, 0, &worker, this, 0, &threadId)) == NULL)
		throw cvgException("Unable to create thread");
#else
	loop = true;
	if (pthread_create(&handle, NULL, worker, this) != 0)
		throw cvgException("Unable to create thread");
#endif
	started = true;
}

bool cvgThread::thread_kill() {
#ifndef CVG_WINDOWS
	if (!started) return false;
	if (pthread_cancel(handle) != 0) return false;
	timespec ts;
	setAbsoluteTimeout(&ts, DEFAULT_KILL_TIMEOUT);
	void *retval;
	return pthread_timedjoin_np(handle, &retval, &ts) != ETIMEDOUT;
#else
#warning "Atlante does not support kill() in Windows yet"
#endif
}

std::string cvgThread::cvg_int_to_string(int i) {
    static char buffer[16];
    snprintf ( buffer, 16, "%d", i);
    // itoa (i,buffer,16);
    std::string result_str(buffer);
    return result_str;
}

void cvgThread::thread_stop(bool killIfNecessary) {
	if (!started) return;
#ifdef CVG_WINDOWS
	if (GetCurrentThreadId() == threadId)
#else
	if (pthread_self() == handle)
#endif
		selfStop();	// This will stop the current thread, but it must be joined from another thread with stop() to free the resources 
	else {
		bool error = false;
#ifdef CVG_WINDOWS
#warning "Windows version of Atlante does not implement the 'kill if necessary' feature on cvgThread yet"
		SetEvent(endEvent);
		error = WaitForSingleObject(endedEvent, stopTimeout) != WAIT_OBJECT_0;
#else
		loop = false;

		timespec ts;
		setAbsoluteTimeout(&ts, stopTimeout);
		void *retval;
		error = pthread_timedjoin_np(handle, &retval, &ts) == ETIMEDOUT;
		if (error && killIfNecessary) {
            started = !thread_kill();
			if (!started) throw cvgException("The thread \"" + name + "\" had to be killed to stop!! Please review your code");
		}
#endif
		if (error) {
			if (!killIfNecessary)
                throw cvgException( (std::string("The thread \"") + name + "\" did not finish in " + cvg_int_to_string(stopTimeout) +
                                     " ms and it might still be running!!").c_str() );
			else
                throw cvgException( std::string("The thread \"") + name + "\" could not be stopped or killed!!");
		}
		started = false;
	}
}

#ifdef CVG_WINDOWS
DWORD WINAPI cvgThread::worker(void *p) {
#else
void *cvgThread::worker(void *p) {
#endif
#define cvg_this	((cvgThread *)p)
#ifndef CVG_WINDOWS
	try {
		pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
		// sigtimedwait() is not used to catch SIGKILL synchronously because it is not implemented in Cygwin
		while(cvg_this->loop) {
            cvg_this->thread_run();
#if defined(WORKER_LOOP_WAIT) && (WORKER_LOOP_WAIT > 0)
            usleep(WORKER_LOOP_WAIT * (1000));
#endif
		}
		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
	} catch(cvgException e) {
		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
		// Manage the error
	}
	cvg_this->started = false;
	return NULL;
#else
	try {
		while(WaitForSingleObject(cvg_this->endEvent, WORKER_LOOP_WAIT) != WAIT_OBJECT_0) {
			cvg_this->run();
#if defined(WORKER_LOOP_WAIT) && (WORKER_LOOP_WAIT > 0)
			Sleep(WORKER_LOOP_WAIT);
#endif
		} 
	} catch(cvgException e) {
		// Manage the error
	}
	SetEvent(cvg_this->endedEvent);
	cvg_this->started = false;
	return 0;
#endif
#undef cvg_this
}

#ifndef CVG_WINDOWS
#include <sys/time.h>

void cvgThread::setAbsoluteTimeout(timespec *ts, unsigned int absTimeoutMs) {
	timeval tv;
    gettimeofday(&tv, NULL);
    unsigned long absTimeUs = (unsigned long)tv.tv_sec * (1000000) + tv.tv_usec;
    absTimeUs += (unsigned long)absTimeoutMs * (unsigned long) (1000);
    ts->tv_sec = absTimeUs / (1000000);
    ts->tv_nsec = (absTimeUs % (1000000)) * (1000);
}
#endif
