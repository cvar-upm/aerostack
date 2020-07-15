/*
 * Mutex.h
 *
 *  Created on: 02/09/2011
 *      Author: Ignacio Mellado
 *      Notes: This is class is currently only implemented for Linux. 
 */

#ifndef CVGMUTEX_H_
#define CVGMUTEX_H_

#include <pthread.h>
#include "cvgException.h"

class cvgMutex {
	friend class cvgCondition;
	friend class cvgSemaphore;
private:
	pthread_mutex_t handler;

public:
    cvgMutex(bool recursive = true);
	virtual ~cvgMutex();

    bool lock();
    bool unlock();
};

#endif /* MUTEX_H_ */
