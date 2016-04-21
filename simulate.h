/*
 * =====================================================================================
 *
 *       Filename:  MMU.h
 *
 *    Description:  this is the header file for the cache_simulator 
 *
 *        Version:  1.0
 *        Created:  04/14/2016 18:28:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jacob Loyd Nash (JLN), JacobLoydNash@gmail.com
 *        Company:  Student
 *
 * =====================================================================================
 */
#include "Dllist.h"

typedef struct {
unsigned int c_sz;// cache size
unsigned int b_sz;// block size in bytes
int w_ty;// write through type
int i_j[2];// i and j val. this will be able to change.
} Cache_Simulation;

typedef struct {
    int valid;
    int test; 
} cache;
typedef struct { 
    int *map;
} map;



