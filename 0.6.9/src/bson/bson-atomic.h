/*
 * Copyright 2013-2014 MongoDB, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef BSON_ATOMIC_H
#define BSON_ATOMIC_H


#include "bson-config.h"
#include "bson-compat.h"
#include "bson-macros.h"


BSON_BEGIN_DECLS


#if defined(__sun) && defined(__SVR4)
# include <atomic.h>
# define bson_atomic_int_add(p,v)   atomic_add_32_nv((volatile uint32_t *)p, (v))
# define bson_atomic_int64_add(p,v) atomic_add_64_nv((volatile uint64_t *)p, (v))
#elif defined(_WIN32)
extern __declspec(dllexport) LONGLONG __cdecl __PORTING__InterlockedExchangeAdd64(
  _Inout_  LONGLONG volatile *Addend,
  _In_     LONGLONG Value
);
# define bson_atomic_int_add(p, v)   (InterlockedExchangeAdd((volatile LONG *)(p), (LONG)(v)) + (LONG)(v))
# define bson_atomic_int64_add(p, v) (__PORTING__InterlockedExchangeAdd64((volatile LONGLONG *)(p), (LONGLONG)(v)) + (LONGLONG)(v))
#elif defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 1)))
# define bson_atomic_int_add(p,v)   __sync_add_and_fetch((p),(v))
# if defined(BSON_HAVE_ATOMIC_64_ADD_AND_FETCH)
#  define bson_atomic_int64_add(p,v) __sync_add_and_fetch((volatile int64_t*)(p),(int64_t)(v))
# else
#  define __BSON_NEED_ATOMIC_64 1
# endif
#else
# warning "Unsupported Compiler/OS combination, please add support for atomics in bson-atomic.h. Using Mutex to emulate atomics."
# define __BSON_NEED_ATOMIC_32 1
# define __BSON_NEED_ATOMIC_64 1
#endif


#ifdef __BSON_NEED_ATOMIC_32
  int32_t bson_atomic_int_add   (volatile int32_t *p, int32_t n);
#endif
#ifdef __BSON_NEED_ATOMIC_64
  int64_t bson_atomic_int64_add (volatile int64_t *p, int64_t n);
#endif


#if defined(__GNUC__)
# if __GNUC__ >= 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 1)
#  define bson_memory_barrier() __sync_synchronize()
# else
#  warning "GCC Pre-4.1 discovered, using inline assembly for memory barrier."
#  define bson_memory_barrier() __asm__ volatile ("":::"memory")
# endif
#elif defined(__SUNPRO_C)
# include <mbarrier.h>
# define bson_memory_barrier() __machine_rw_barrier()
#elif defined(_WIN32)
# define bson_memory_barrier() MemoryBarrier()
#else
# define __BSON_NEED_BARRIER 1
# warning "Unknown compiler, using lock for compiler barrier."
void bson_memory_barrier (void);
#endif


BSON_END_DECLS


#endif /* BSON_ATOMIC_H */
