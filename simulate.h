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
    int  t;
    int  v;
    int  c;
} Cache_Block;

typedef struct {
unsigned int c_sz;// cache size
unsigned int t_ms;// tah mask
unsigned int b_sz;// block size in bytes
unsigned int b_ms;// block mask
unsigned int d_sz;// data size int is 4
unsigned int s_ms;// Set mask
int w_ty;// write through type
int i_j[2];// i and j val. this will be able to change.
Cache_Block *blks; 
} Cache_Simulation;

typedef struct { 
    int h;
    int m;
} Stats;



