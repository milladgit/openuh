/*
 ARMCI Communication Layer for supporting Coarray Fortran

 Copyright (C) 2009-2012 University of Houston.

 This program is free software; you can redistribute it and/or modify it
 under the terms of version 2 of the GNU General Public License as
 published by the Free Software Foundation.

 This program is distributed in the hope that it would be useful, but
 WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 Further, this software is distributed without any warranty that it is
 free of the rightful claim of any third person regarding infringement
 or the like.  Any license provided herein, whether implied or
 otherwise, applies only to this software file.  Patent licenses, if
 any, provided herein do not apply to combinations of this program with
 other software, or any other product whatsoever.

 You should have received a copy of the GNU General Public License along
 with this program; if not, write the Free Software Foundation, Inc., 59
 Temple Place - Suite 330, Boston MA 02111-1307, USA.

 Contact information:
 http://www.cs.uh.edu/~hpctools
*/


#ifndef ARMCI_COMM_LAYER_H
#define ARMCI_COMM_LAYER_H

#include "mpi.h"
#include "armci.h"
#include "trace.h"
#include "caf_rtl.h"

#define ENABLE_LOCAL_MEMCPY
#define MAX_DIMS 15

#define DEFAULT_SHARED_MEMORY_SIZE 31457280L
#define DEFAULT_GETCACHE_LINE_SIZE 65536L

/* init */
void comm_init();


/* critical support */
void comm_get_signal(int** signal);
void comm_critical();
void comm_end_critical();



/* inline functions */
unsigned long comm_get_proc_id();
unsigned long comm_get_num_procs();

/* coarray read/write */
void comm_read(void *src, void *dest, unsigned long xfer_size, unsigned long proc);
void comm_write(void *dest, void *src, unsigned long xfer_size, unsigned long proc);
void comm_read_src_str(void *src, void *dest, unsigned int ndim,
                    unsigned long *src_strides, unsigned long *src_extents,
                    unsigned long proc);
void comm_read_src_str2(void *src, void *dest, unsigned int ndim,
                    unsigned long *src_str_mults, unsigned long *src_extents,
                    unsigned long *src_strides,
                    unsigned long proc);
void comm_write_dest_str(void *dest, void *src, unsigned int ndim,
                    unsigned long *dest_strides, unsigned long *dest_extents,
                    unsigned long proc);
void comm_write_dest_str2(void *dest, void *src, unsigned int ndim,
                    unsigned long *dest_str_mults,
                    unsigned long *dest_extents,
                    unsigned long *dest_strides,
                    unsigned long proc);
void comm_read_full_str (void * src, void *dest, unsigned int src_ndim,
        unsigned long *src_strides, unsigned long *src_extents, 
        unsigned int dest_ndim, unsigned long *dest_strides,
        unsigned long *dest_extents, unsigned long proc);
void comm_read_full_str2 (void * src, void *dest, unsigned int src_ndim,
        unsigned long *src_str_mults, unsigned long *src_extents, 
        unsigned long *src_strides,
        unsigned int dest_ndim, unsigned long *dest_str_mults,
        unsigned long *dest_extents, unsigned long *dest_strides,
        unsigned long proc);
void comm_write_full_str (void * dest, void *src, unsigned int dest_ndim,
        unsigned long *dest_strides, unsigned long *dest_extents, 
        unsigned int src_ndim, unsigned long *src_strides,
        unsigned long *src_extents, unsigned long proc);
void comm_write_full_str2 (void * dest, void *src, unsigned int dest_ndim,
        unsigned long *dest_str_mults, unsigned long *dest_extents, 
        unsigned long *dest_strides,
        unsigned int src_ndim, unsigned long *src_str_mults,
        unsigned long *src_extents, unsigned long *src_strides,
        unsigned long proc);

/* shared memory management */
unsigned long allocate_static_coarrays(); /*TBD */
static void *get_remote_address(void *src, unsigned long img);

/* GET CACHE OPTIMIZATION */
struct cache
{
    void *remote_address;
    void *cache_line_address;
    armci_hdl_t *handle;
};
static void clear_all_cache();
static void clear_cache(unsigned long node);
static void cache_check_and_get(unsigned long node, void *remote_address,
                            unsigned long xfer_size, void *local_address);
static void update_cache(unsigned long node,void *remote_address,
                    unsigned long xfer_size, void *local_address);

/* NONBLOCKING PUT OPTIMIZATION */
static int address_in_nbwrite_address_block(void *remote_addr,
        unsigned long proc, unsigned long size);
static void update_nbwrite_address_block(void *remote_addr,
        unsigned long proc, unsigned long size);
static void check_wait_on_pending_puts(unsigned long proc,
        void* remote_address, unsigned long size);
static void wait_on_pending_puts(unsigned long proc);
static void wait_on_all_pending_puts();

/* malloc & free */
void* comm_malloc(size_t size);
void comm_free(void* ptr);
void comm_free_lcb(void* ptr);

/* barriers */
void comm_barrier_all();
void comm_sync_images(int *image_list, int image_count);

/* exit */
void comm_memory_free();
void comm_exit(int status);
void comm_finalize();

#endif
