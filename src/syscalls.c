/*
 * Copyright 2015 Erik Van Hamme
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <sys/types.h>

#ifdef stm32f3
#include "stm32f3xx.h"
#endif

#ifdef stm32f4
#include "stm32f4xx.h"
#endif

/* TODO: Find out what other NewLib syscalls should be implemented. (List: http://wiki.osdev.org/Porting_Newlib#newlib.2Flibc.2Fsys.2Fmyos.2Fsyscalls.c ) */

extern int _heap_start;

inline void abort(void) {
	while (1) {
	}
}

caddr_t _sbrk(int incr) {
	static unsigned char *heap_end = NULL;
	unsigned char *prev_heap;

	if (heap_end == NULL) {
		heap_end = (unsigned char *) &_heap_start;
	}
	
	unsigned char *stack_bottom = (unsigned char *) __get_MSP();
	
	if (heap_end + incr >  stack_bottom) {
		abort(); /* Heap and stack collision. */
	}
	
	prev_heap = heap_end;
	heap_end += incr;

	return (caddr_t) prev_heap;
}

/* 
 * _init() is implemented here to allow linking with -nostartfiles. Doing this avoids that the startup of the application
 * builds support for destruction of the static C++ objects. Destruction support is not needed because embedded apps should
 * never return from main().
 */
void _init() {
}

