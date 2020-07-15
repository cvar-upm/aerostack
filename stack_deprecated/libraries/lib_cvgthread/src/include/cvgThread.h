#include <string>
#include "cvgException.h"
#include <stdio.h>

#ifndef CVG_THREAD_INCLUDED__
#define CVG_THREAD_INCLUDED__

#ifdef CVG_WINDOWS
#	include <windows.h>
#else
#	include <pthread.h>
#	include <errno.h> 
#endif

class cvgThread {
private:
	std::string name;
	volatile bool started;
    unsigned int stopTimeout;
	bool created;
#ifdef CVG_WINDOWS
	HANDLE handle;
	HANDLE endEvent, endedEvent;
	DWORD threadId;
#else
	pthread_t handle;
	pthread_mutex_t endMutex;
	pthread_cond_t endedCondition;
#endif

protected:
	void create();
	void destroy();
#ifdef CVG_WINDOWS
	static DWORD WINAPI worker(void *p);
#else
	volatile bool loop;
    void setAbsoluteTimeout(timespec *ts, unsigned int absTimeout);
	static void *worker(void *p);
#endif

public:
	cvgThread(std::string *name);
	cvgThread(const char *name);
	virtual ~cvgThread();

	inline void setName(std::string *name) { this->name = *name; }
	inline void setName(const char *name) { this->name = name; }
	inline std::string &getName() { return name; }

    inline void setStopTimeout(unsigned int tm) { stopTimeout = tm; }
    inline unsigned int getStopTimeout() { return stopTimeout; }

    void thread_start();
    void thread_stop(bool killIfNecessary = true);
    bool thread_kill();
	inline void selfStop() { loop = false; }
    virtual void thread_run() { }

    inline bool thread_isStarted() { return started; }

    std::string cvg_int_to_string(int i);
};

#endif
