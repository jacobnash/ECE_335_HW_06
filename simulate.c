#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dllist.h"// this is a Dynamically linked list. i may or may not need. 
#include "simulate.h"

#define talloc(ty, sz) (ty *) malloc ((sz) * sizeof(ty))

void usage(char *s)
{
    fprintf(stderr, "./simulate <cache size(in bytes)> , <block size (in bytes)>, <type of allocation 1-3>, <write type>, <src i>, <src j>\n");
    if (s != NULL) fprintf(stderr, "%s\n", s);
    exit(1);
}

main(int argc, char **argv)
{
    Cache_Simulation *cs, CS;

    cs = &CS;

    if (argc != 6) usage(NULL);

    if (sscanf(argv[1], "%d", &cs->c_sz) != 1 || cs->c_sz <= 1) {
        usage("cache size in bytes");
    }
    if (sscanf(argv[2], "%d", &cs->b_sz) != 1 || cs->b_sz <= 0) {
        usage("block size in bytes");
    }
    if (sscanf(argv[3], "%d", &cs->a_ty) != 1 || cs->a_ty <= 0) {
        usage("direct mapped:1 two-way set associative:2 four-way set associative:3");
    }
    if (sscanf(argv[4], "%d", &cs->w_ty) != 1 || cs->w_ty<= 0) {
        usage("write through:1 write allocate:2");
    }
    if (sscanf(argv[5], "%d", &cs->i_j[0]) != 1 || cs->i_j[0]<= 0) {
        usage("src i");
    }
    if (sscanf(argv[6], "%d", &cs->i_j[1]) != 1 || cs->i_j[1]<= 0) {
        usage("src j");
    }
}
