#include "hilbertV2.h"
#include "coord_t.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void hilbertV2(unsigned degree, coord_t* x, coord_t* y) {
    hilbertHelper(degree, x, y, 0);
}

void hilbertHelper(unsigned degree, coord_t* x, coord_t* y, unsigned currentPointIndex) {

    if (degree == 1) {
        x[currentPointIndex].value = 0;
        x[currentPointIndex+1].value = 0;
        x[currentPointIndex+2].value = 1;
        x[currentPointIndex+3].value = 1;

        y[currentPointIndex].value = 0;
        y[currentPointIndex+1].value = 1;
        y[currentPointIndex+2].value = 1;
        y[currentPointIndex+3].value = 0;

        return;
    }

    hilbertHelper(degree-1, x, y,currentPointIndex);
    //SWAP COORDINATES:
    for (int i = currentPointIndex; i < currentPointIndex + pow(2, 2*(degree-1)) ; i++) {
        int tmp = x[i].value;
        x[i].value = y[i].value;
        y[i].value = tmp;
    }

    currentPointIndex += pow(2, 2*(degree-1));
    hilbertHelper(degree-1, x, y, currentPointIndex);

    //INCREASE Y:
    for (int i = currentPointIndex; i < currentPointIndex + pow(2, 2*(degree-1)) ; i++) {
        y[i].value += pow(2, degree-1);
    }

    currentPointIndex += pow(2, 2*(degree-1));
    hilbertHelper(degree-1, x, y, currentPointIndex);

    //INCREASE X AND Y:
    for (int i = currentPointIndex; i < currentPointIndex + pow(2, 2*(degree-1)) ; i++) {
        x[i].value += pow(2, degree-1);
        y[i].value += pow(2, degree-1);
    }

    currentPointIndex += pow(2, 2*(degree-1));
    hilbertHelper(degree-1, x, y, currentPointIndex);
    
    // SWAP, FLIP HORIZONTALLY, ADD TO X
    for (int i = currentPointIndex; i < currentPointIndex + pow(2, 2*(degree-1)); i++) {
        int tmp = pow(2, degree-1) - 1 - x[i].value;
        x[i].value = pow(2, degree-1) - 1 - y[i].value;
        y[i].value = tmp;
        x[i].value += pow(2, degree-1);
    }
}
