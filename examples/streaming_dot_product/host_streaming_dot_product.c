/*
File: host_streaming_dot_product.c

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

#include <host_bsp.h>
#include <host_bsp_inspector.h>
#include <stdlib.h>
#include <stdio.h> 
#include <stdint.h> 

int main(int argc, char **argv)
{
    bsp_init("e_streaming_dot_product.srec", argc, argv);
    bsp_begin(bsp_nprocs());

    // allocate two random vectors of length 512 each
    int l = 409600;
    int* a = (int*)malloc(sizeof(int) * l);
    int* b = (int*)malloc(sizeof(int) * l);
    for (int i = 0; i < l; ++i) {
        a[i] = i;
        b[i] = 2*i;
    }

    // partition and write to processors
    
    int big_chunk_nints = (l + bsp_nprocs() - 1) / bsp_nprocs();
    int small_chunk_nints = big_chunk_nints-1;
    int n_big = l + bsp_nprocs() * ( 1 - big_chunk_nints );
    
    int current_chunk_nints = big_chunk_nints;
    unsigned a_cursor = (unsigned) a;
    unsigned b_cursor = (unsigned) b;
    for (int pid = 0; pid < bsp_nprocs(); pid++)
    {
        if (pid == n_big)
            current_chunk_nints = small_chunk_nints;

        int current_chunk_size = sizeof(int) * current_chunk_nints;

        ebsp_send_buffered((void*) a_cursor, pid, current_chunk_size, 100);
        ebsp_send_buffered((void*) b_cursor, pid, current_chunk_size, 100);
        
        a_cursor += current_chunk_size;
        b_cursor += current_chunk_size;
    }
    //TODO write client side
    //TODO malloc the first time ebsp_get_chunk is used

    // run dotproduct
    ebsp_spmd();

    // read output
    int tag;
    int packets, accum_bytes;
    ebsp_qsize(&packets, &accum_bytes);

    int status;
    int result;
    int sum = 0;
    printf("proc \t partial_sum\n");
    printf("---- \t -----------\n");
    for (int i = 0; i < packets; i++)
    {
        ebsp_get_tag(&status, &tag);
        ebsp_move(&result, sizeof(int));
        printf("%i: \t %i\n", tag, result);
        sum += result;
    }

    printf("SUM: %i\n", sum);

    free((void*)a);
    free((void*)b);

    // finalize
    bsp_end();

    return 0;
}
