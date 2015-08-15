/*
File: e_bsp_buffer.c

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

#include "e_bsp_private.h"
#include <string.h>




/*
void* ebsp_get_in_chunk() {//TODO rewrite
    coredata.exmem_next_in_chunk += IN_CHUNK_SIZE;

    void* tmp = coredata.buffer_in_current;
    coredata.buffer_in_current = coredata.buffer_in_next;
    coredata.buffer_in_next    = tmp;

    ebsp_dma_copy_parallel( E_DMA_0, coredata.buffer_in_next, coredata.exmem_next_in_chunk, (size_t) IN_CHUNK_SIZE );//REPLACE BY QUEUE
    return coredata.buffer_in_current;
}

void* ebsp_get_out_chunk() {
    coredata.exmem_current_out_chunk += OUT_CHUNK_SIZE;//TODO Change OUT_CHUNK_SIZE to var passed down 
    //FIXME check for overflow

    void* tmp = coredata.buffer_out_current;//TODO support slow mode?
    coredata.buffer_out_current  = coredata.buffer_out_previous;
    coredata.buffer_out_previous = tmp;

    ebsp_dma_copy_parallel( E_DMA_1, coredata.exmem_current_out_chunk, coredata.buffer_out_previous, (size_t) OUT_CHUNK_SIZE );//TODO REPLACE BY QUEUE

    return coredata.buffer_out_current;
}
*/
