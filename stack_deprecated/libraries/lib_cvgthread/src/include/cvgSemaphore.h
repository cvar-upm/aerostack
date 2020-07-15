/*
 * Condition.h
 *
 *  Created on: 04/09/2011
 *      Author: Ignacio Mellado
 */

#ifndef CVGSEMAPHORE_H_
#define CVGSEMAPHORE_H_

#include "cvgMutex.h"
#include <atlante.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>

class cvgSemaphore {
private:
	pthread_cond_t handler;
	volatile cvg_int count;
public:
	inline cvgSemaphore() {
		count = 0;
		if (pthread_cond_init(&handler, NULL) != 0)
			throw cvgException("[Semaphore] Cannot initialize condition handler");
	}

	virtual ~cvgSemaphore() {
		pthread_cond_destroy(&handler);
	}

	inline void wait(cvgMutex *mutex) {
		while(count == 0) {
			if (pthread_cond_wait(&handler, &mutex->handler) != 0)
				throw cvgException("[Semaphore] Error waiting for condition");
		}
		if (count > 0) count--;
	}

	inline bool wait(cvgMutex *mutex, cvg_double timeoutSeconds) {
		timeval tv;
		gettimeofday(&tv, NULL);
		timespec ts;
		ts.tv_sec = tv.tv_sec + (cvg_ulong)floor(timeoutSeconds);
		ts.tv_nsec = 1000 * tv.tv_usec + (cvg_ulong)(1e9 * (timeoutSeconds - floor(timeoutSeconds)));
		if (ts.tv_nsec >= CVG_LITERAL_LONG(1000000000)) {
			ts.tv_sec++;  
			ts.tv_nsec -= CVG_LITERAL_LONG(1000000000);
		}
		int res = 0;
		while(count == 0 && res != ETIMEDOUT) {		
			res = pthread_cond_timedwait(&handler, &mutex->handler, &ts);
			if (res != 0 && res != ETIMEDOUT) {
				mutex->unlock();
				throw cvgException("[Semaphore] Error waiting for condition");
			}
		}
		bool result = count > 0;
		if (count > 0) count--;
		return result;
	}

	inline void signal() {
		count++;
		pthread_cond_signal(&handler);
	}
};

#endif /* CONDITION_H_ */
