/*
File: e_bsp_memory.c

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
#define DYNMEM_START   DYNMEM_EADDR
#define MALLOC_FUNCTION_PREFIX  EXT_MEM_TEXT

#include "extmem_malloc_implementation.cpp"

void* EXT_MEM_TEXT ebsp_ext_malloc(unsigned int nbytes)
{
    void *ret = 0;
    e_mutex_lock(0, 0, &coredata.malloc_mutex);
    ret = _malloc(nbytes);
    e_mutex_unlock(0, 0, &coredata.malloc_mutex);
    return ret;
}

void EXT_MEM_TEXT ebsp_free(void* ptr)
{
    e_mutex_lock(0, 0, &coredata.malloc_mutex);
    _free(ptr);
    e_mutex_unlock(0, 0, &coredata.malloc_mutex);
}
