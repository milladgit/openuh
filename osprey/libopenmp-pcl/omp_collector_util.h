/*
 Collector Support for Open64's OpenMP runtime library

 Copyright (C) 2009 University of Houston.

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


#ifndef	_OMP_COLLECTOR_UTIL_H
#define	_OMP_COLLECTOR_UTIL_H


#ifdef __cplusplus
extern "C" {
#endif

extern char OMP_EVENT_NAME[22][50];
extern char OMP_STATE_NAME[11][50];

int __omp_collector_api(void *arg);

void __omp_collector_init(void);
    
#ifdef __cplusplus
}
#endif

#endif	/* _OMP_COLLECTOR_UTIL_H */

