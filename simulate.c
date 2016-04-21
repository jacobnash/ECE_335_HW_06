#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dllist.h"// this is a Dynamically linked list. i may or may not need. 
#include "simulate.h"

#define mmalloc(ty, sz) (ty *) malloc ((sz) * sizeof(ty))

int DEBUG = 1;

void usage(char *s)
{
    fprintf(stderr, "simulate <cache size(in bytes)>, <block size (in bytes)>, <mapping 1,2,4,ect.>, <src i>, <src j>\n");
    if (s != NULL) fprintf(stderr, "%s\n", s);
    exit(0);
}
int hit_miss(int address){
//check if memorty is resident
//
//do we care if it is a read or not? 
    return 0;
}

int main(int argc, char **argv)
{
    Cache_Simulation *cs, CS;

    cs = &CS;
    //get information that the user needs to provide
    if (argc != 6) usage(NULL);

    if (sscanf(argv[1], "%d", &cs->c_sz) != 1 || cs->c_sz <= 1) {
        usage("cache size in bytes");
    }
    if (sscanf(argv[2], "%d", &cs->b_sz) != 1 || cs->b_sz <= 0) {
        usage("block size in bytes");
    }
    if (sscanf(argv[3], "%d", &cs->w_ty) != 1 || cs->w_ty<= 0) {
        usage("direct mapped:1 two-way set associative:2 four-way set associative:4");
    }
    if (sscanf(argv[4], "%d", &cs->i_j[0]) != 1 || cs->i_j[0]<= 0) {
        usage("src i");
    }
    if (sscanf(argv[5], "%d", &cs->i_j[1]) != 1 || cs->i_j[1]<= 0) {
        usage("src j");
    }
    if ((cs->c_sz/cs->b_sz) % cs->w_ty)
        usage("inconsistant data.");
    //pre print to tell user what they did. 
    if(DEBUG)
        fprintf(stderr," cache size: %d\n block size: %d\n associations: %d\n i: %d \n j: %d\n",cs->c_sz, cs->b_sz, cs->w_ty, cs->i_j[0],cs->i_j[1] );
    //set up cache. 
    //// each block times the associations is a unit in the array. 
    //     which points to a block of data 
    //
    int db_sz = cs->c_sz/(cs->b_sz * cs->w_ty);
    if (DEBUG) fprintf(stderr," data block size: %d\n" ,db_sz);
    

    for(int i = 0; i < cs->i_j[0]; i++){
        for(int j = 0; j <cs->i_j[1]; j++){
            //dst[j][i] = src[i][j];
            if(DEBUG){
                fprintf(stderr, "R: 0x%x\n", (j + i*cs->i_j[1]));
                fprintf(stderr, "W: 0x%x\n", (i + j*cs->i_j[0]));
            }
            hit_miss(j + i*cs->i_j[1]);
            hit_miss(i + j*cs->i_j[0]);
        }
    }

    return 0;
}
