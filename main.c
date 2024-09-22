//
// Created by Pavel Baltov on 16.01.23.
//
#include "coord_t.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <sys/mman.h>
#include "hilbertV2.h"

extern void hilbert(unsigned degree, coord_t* x, coord_t* y);

extern void hilbertV1(unsigned degree, coord_t* x, coord_t* y);

    // ---------- TIME MEASUREMENT ----------
static inline double currentTime(void) {
	struct timespec t;
	clock_gettime(CLOCK_MONOTONIC, &t);
	return t.tv_sec + t.tv_nsec * 1e-9;
}
int main(int argc, char *argv[]) {

    // ---------- NEEDED VARIABLES ----------
    int implementation = 0;
    int numberOfCallingImplementation = 1;
    int degree = 1;
    int width = 512;
    double time = 0;
    _Bool showTime = 0;
    char outputName[32] = {"coordinates"};
    char helpOutput[] = {"Description: Generates the coordinates of a n-degree Hilbert's curve."
			"Afterwards it creates .svg file that visualizes the curve.\n\n"
	   
	               "Usage:    ./runhilbert [options] [target]\n\n"
                       "Options: \n"
		       "	-V [N]		Chooses the Nth implementation. If it is left behind, it is chosen by default the main implementation which equals 0.\n"
                       "	-B [N]		It measures the execution time of the chosen implementation and prints it out. N is optional and determines how many times the function is called.\n"
                       "	-n [N]		N determines the degree of the Hilbert's curve.\n"
                       "	-o [S]		S determines the output's file name. You should write it without the file extension. By default it's \"coordinates.svg\"\n"
                       "	-w [N]		N determines the width of the canvas in the .svg file. By default it is 512.\n"};

    // ---------- OPTIONS FROM CONSOLE ---------

    for (int i = 1; i < argc; i+=2) {
            // "-h" / "--help" options
            if ((strcmp(argv[1],"-h") == 0) || (strcmp(argv[1],"--help") == 0)) {
                if (argc > 2) {
                    fprintf( stderr, "Too many arguments. After --help/-h are expected no other arguments!");
                    exit(0);
                }
                //Print - how to use commands
                printf("%s", helpOutput);
                exit(1);
            }
            // "-V" option
            else if (strcmp(argv[i],"-V") == 0) {

                if (i+1 >= argc) {
                    fprintf(stderr, "Not enough arguments to \"-V\" option.");
                    exit(1);
                }
                implementation = atoi(argv[i + 1]);
            }
            // "-B" option
            else if (strcmp(argv[i],"-B") == 0) {
                
		if ((i+1 < argc) && (isdigit(*argv[i+1]))) {
                    numberOfCallingImplementation = atoi(argv[i+1]);
		 }
		else {
		i--;
		}
		showTime = 1;
            }
            // "-n" option
            else if (strcmp(argv[i],"-n") == 0) {
                if (i+1 >= argc) {
                    fprintf(stderr, "Not enough arguments to the \"-n\" option.");
                    exit(1);
                }
                degree = atoi(argv[i+1]);
            }
            // "-" option
            else if (strcmp(argv[i],"-o") == 0) {
                if (i+1 >= argc) {
                    fprintf(stderr, "Not enough arguments to the \"-o\" option.");
                    exit(1);
                }
                strncpy(outputName, argv[i+1], sizeof(outputName));
            }
            // "-w" option
            else if (strcmp(argv[i],"-w") == 0) {
                if (i+1 >= argc) {
                    fprintf(stderr, "Not enough arguments to the \"-w\" option.");
                    exit(1);
                }
                width = atoi(argv[i+1]);
            }
            // error message if option doesn't match
            else {
                fprintf(stderr, "Unknown option. Note: try running with -h/--help for more information");
                exit(1);
            }
    }

    // ---------- CALLS THE FUNCTION DEPENDING ON _IMPLEMENTATION ----------

    unsigned int totalPoints = pow(2, degree) * pow(2,degree);
    coord_t* x = malloc(totalPoints * sizeof(coord_t));
    coord_t* y = malloc(totalPoints * sizeof(coord_t));
    if ((x == NULL) || (y == NULL)) {
        printf("Could not create the arrays. Total points: %d\n", totalPoints);
	exit(0);
    }
    for (int i = 0; i < numberOfCallingImplementation; i++) {
	double start = currentTime();
	switch (implementation) {
        	case 0:
            	hilbert(degree, x, y);
            	break;
		case 1:
		hilbertV1(degree, x, y);
		break;
		case 2:
		hilbertV2(degree, x, y);
        	default:
        	    break;
    	}
	double end = currentTime();
	time += end - start;
    }

    // ---------- TIME MEASSUREMENT OUTPUT -----------
    
    if (showTime == 1) {
	printf("The implementation number %d needed %f seconds to execute\n",implementation, time);

    }

    // ---------- GENERATES .SVG FILE ----------
    printf("Generating .svg file named %s.svg...\n", outputName);
    FILE *fptr;
    fptr = fopen(strcat(outputName, ".svg"),"w");
    int length = width / (int)(pow(2, degree));
    int offsetFactor = length/2;
    fprintf(fptr, "<svg width=\"%d\" height=\"%d\" viewBox=\"0 0 %d %d\">\n", width, width, width, width);
    for (unsigned int i = 1; i < totalPoints; i++) {
//	 printf("point %d: (%d, %d)\n", i-1, x[i-1].value, y[i-1].value);
	fprintf(fptr, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />\n",
               width - ((x[i].value * length) + offsetFactor),
               width - ((y[i].value * length) + offsetFactor),
               width - ((x[i-1].value * length) + offsetFactor),
               width - ((y[i-1].value * length) + offsetFactor));
    }
    fprintf(fptr, "</svg>");

    // ---------- FREES MEMORY ----------

    fclose(fptr);
    free(x);
    free(y);
    return 0;
}
