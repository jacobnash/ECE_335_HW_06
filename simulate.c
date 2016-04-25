#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>     /* strcat */
#include "dllist.h"// this is a Dynamically linked list. i may or may not need. 
#include "simulate.h"

#define mmalloc(ty, sz) (ty *) malloc ((sz) * sizeof(ty))
#define M_SZ 31

int DEBUG = 0;

void usage(char *s)
{
    fprintf(stderr, "simulate <cache size(in bytes)>, <block size (in bytes)>, <mapping 1,2,4,ect.>, <Size of data>, <src i>, <src j>\n");
    if (s != NULL) fprintf(stderr, "%s\n", s);
    exit(0);
}
const char *byte_to_binary(unsigned int x)
{
    static char b[33];
    b[0] = '\0';

    unsigned int z;
    for (z = (pow(2, M_SZ)); z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}
int hit_miss(int address,Cache_Simulation *cs)
{   int section, tag;
    //check if memorty is resident
    int i = (int)log2(cs->b_sz);
    int s = ((cs->c_sz / cs->b_sz)/cs->w_ty);
    address = address >> i;
    section = address & (s-1);
    tag = address >>(int)log2(s);
    int max = 0;
    for(int j = 0; j < cs->w_ty; j++)
    {
        if (max < ++cs->blks[j+section].c)
            max = cs->blks[j+section].c;

        if(cs->blks[j+section].v == 0)
        {
            if(DEBUG) fprintf(stderr,"miss\n");
            cs->blks[j+section].v = 1;
            cs->blks[j+section].t = tag;
            cs->blks[j+section].c = 0;
            return 0; 
        }
        else if(cs->blks[j+section].t == tag)
        {
            if(DEBUG) fprintf(stderr,"hit\n");
            return 1;
        }
    }
    for(int j = 0; j < cs->w_ty; j++)
    {
        if (max  == cs->blks[j+section].c){
            if(DEBUG)  fprintf(stderr,"miss\n");
            cs->blks[j+section].v = 1;
            cs->blks[j+section].t = tag;
            cs->blks[j+section].c = 0;
            return 0; 
        }
    }

    //do we care if it is a read or not? 
    return 0;
}


int main(int argc, char **argv)
{
    Cache_Simulation *cs, CS;

    cs = &CS;
    //get information that the user needs to provide
    if (argc != 7) usage(NULL);

    if (sscanf(argv[1], "%d", &cs->c_sz) != 1 || cs->c_sz <= 1) {
        usage("cache size in bytes");
    }
    if (sscanf(argv[2], "%d", &cs->b_sz) != 1 || cs->b_sz <= 0) {
        usage("block size in bytes");
    }
    if (sscanf(argv[3], "%d", &cs->w_ty) != 1 || cs->w_ty<= 0) {
        usage("direct mapped:1 two-way set associative:2 four-way set associative:4");
    }
    if (sscanf(argv[4], "%d", &cs->d_sz) != 1 || cs->d_sz<= 0) {
        usage("Size of data.");
    }
    if (sscanf(argv[5], "%d", &cs->i_j[0]) != 1 || cs->i_j[0]<= 0) {
        usage("src i");
    }
    if (sscanf(argv[6], "%d", &cs->i_j[1]) != 1 || cs->i_j[1]<= 0) {
        usage("src j");
    }
    if ((cs->c_sz/cs->b_sz) % cs->w_ty)
        usage("inconsistant data.");
    //pre print to tell user what they did. 
    if(DEBUG)
        fprintf(stderr," cache size: %d\n block size: %d\n associations: %d\n SIZEOF(): %d\n i: %d \n j: %d\n",cs->c_sz, cs->b_sz, cs->w_ty,cs->d_sz, cs->i_j[0],cs->i_j[1] );
    //set up cache. 
    int blk_cnt = cs->c_sz / cs->b_sz;
    cs->blks = mmalloc(Cache_Block, blk_cnt);
    for (int i = 0; i < blk_cnt; i++){
        cs->blks[i].v = 0; 
        cs->blks[i].t = 0; 
        cs->blks[i].c = 0; 
    }
    //set up stats.
    Stats r,w;
    r.m = 0;
    r.h = 0;
    w.m = 0;
    w.h = 0;
    if(DEBUG) fprintf(stderr, "number of blocks: %d\n", blk_cnt);
    char* SRC = "";
    char* DST = "";
    for(int i = 0; i < cs->i_j[0]; i++){
        for(int j = 0; j <cs->i_j[1]; j++){
            //dst[j][i] = src[i][j];
            if(DEBUG) fprintf(stderr, "R: 0x%s\n", byte_to_binary((j + i*cs->i_j[1])*cs->d_sz));
            if( hit_miss((j + i*cs->i_j[1])*cs->d_sz,cs)) 
            {
                asprintf(&SRC, "%s\tH",SRC);

            }
            else
            {
                ++r.m;
                asprintf(&SRC, "%s\tM",SRC); 
            }
            if(DEBUG) fprintf(stderr, "W: 0x%s\n", byte_to_binary(((i + j*cs->i_j[0])*cs->d_sz) + (cs->i_j[0]*cs->i_j[1] * cs->d_sz)));
            if (hit_miss(((i + j*cs->i_j[0])*cs->d_sz) + (cs->i_j[0]*cs->i_j[1] * cs->d_sz),cs)){
                ++w.h;
                asprintf(&DST, "%s\tH",DST); 
            }
            else 
            {
                ++w.m;
                asprintf(&DST,  "%s\tM",DST); 
            }
        }

                asprintf(&SRC, " %s\n",SRC); 
                asprintf(&DST, " %s\n",DST); 
    }
    float avg = (float)r.h/(float)(r.h+r.m);
    fprintf(stdout, "SRC: \n %s", SRC);
    fprintf(stdout, "Read stats:\n\t Hits:%d \n\t Misses:%d \n\t Hit percent: %f\n\n",r.h,r.m,avg);
    avg = (float)w.h/(float)(w.h+w.m);
    fprintf(stdout, "DST: \n %s", DST);
    fprintf(stdout, "Write stats:\n\t Hits:%d \n\t Misses:%d \n\t Hit percent: %f\n",w.h,w.m,avg);

    return 0;
}
