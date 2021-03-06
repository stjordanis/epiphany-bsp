/*
File: e_bsp_private.h

This file is part of the Epiphany BSP library.

Copyright (C) 2014 Buurlage Wits
Support e-mail: <info@buurlagewits.nl>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License (LGPL)
as published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
and the GNU Lesser General Public License along with this program,
see the files COPYING and COPYING.LESSER. If not, see
<http://www.gnu.org/licenses/>.
*/

#pragma once
#include "e_bsp.h"
#include "ebsp_common.h"
#include <e-lib.h>
#include <stdint.h>

// Use this define to place functions or variables in external memory
// TEXT is for functions and normal variables
// RO is for read only globals
#define EXT_MEM_TEXT __attribute__((section("EBSP_TEXT")))
#define EXT_MEM_RO __attribute__((section("EBSP_RO")))

// All internal bsp variables for this core
// 8-bit variables (mutexes) are grouped together
// to avoid unnecesary padding
typedef struct {
    // ARM core will set this, epiphany will poll this
    volatile int8_t syncstate;

    int32_t pid;
    int32_t nprocs;

    uint16_t coreids[NPROCS]; // pid to coreid mapping

    // time_passed is epiphany cpu time (so not walltime) in seconds
    float time_passed;

    // BSP variable list
    void* bsp_var_list[MAX_BSP_VARS];

    // counter for ebsp_combuf::data_requests[pid]
    uint32_t request_counter;

    // message_index is an index into an epiphany<->epiphany queue and
    // when it reached the end, it is an index into the arm->epiphany queue
    uint32_t tagsize;
    uint32_t tagsize_next; // next superstep
    uint32_t read_queue_index;
    uint32_t message_index;

    // bsp_sync barrier
    volatile e_barrier_t sync_barrier[NPROCS];
    volatile e_barrier_t* sync_barrier_tgt[NPROCS];

    // Mutex is used for message_queue (send) and data_payloads (put)
    e_mutex_t payload_mutex;

    // Mutex for ebsp_message
    e_mutex_t ebsp_message_mutex;

    // Mutex for opening a stream
    e_mutex_t stream_mutex;

    // Mutex for ebsp_ext_malloc (internal malloc does not have mutex)
    e_mutex_t malloc_mutex;

    // Base address of malloc table for internal malloc
    void* local_malloc_base;

    // Location of local copy of combuf.extmem_in_streams
    ebsp_stream_descriptor* local_streams;

    unsigned local_nstreams;

    // Start and end of chain of DMA descriptors
    // cur_dma_desc is updated in the interrupt when the DMA finishes a task
    // last_dma_desc is updated in ebsp_dma_push
    e_dma_desc_t* cur_dma_desc;
    e_dma_desc_t* last_dma_desc;

    // Global-space pointer to local DMA1CONFIG and DMA1STATUS cpu registers
    unsigned* dma1config;
    unsigned* dma1status;
} ebsp_core_data;

extern ebsp_core_data coredata;

// The define is faster; it saves a pointer lookup
#define combuf ((ebsp_combuf*)E_COMBUF_ADDR)
// ebsp_combuf * const combuf = (ebsp_combuf*)E_COMBUF_ADDR;

void _init_local_malloc();

