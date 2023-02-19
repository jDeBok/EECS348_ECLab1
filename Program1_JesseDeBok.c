#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
const int Rd = 5, Cd = 5, Rp = 5, Cp = 5;   //sizes of my preference/department/programmer list, for the input I am taking in these are constants as I assume valid input of size 5 for everyone
//didn't say in assignment to be any size, but I would just need to change these values for different sizes
//R = rows, C = columns, d = department, p = programmer
void clearFoundProgrammer(int dep [Rd][Cd], int whichp) {
    /*
    purpose: move the programmer I have assigned to a department to the end of every preference list.  This is because I use the first index to indicate first choice,
    so if I have already assigned a programmer to a department they should be removed from the prefrence list as they are no longer an option.
    inputs: dep is department array, whichp is which programmer to move to the end of each preference list
    outputs: none, changes values in my department array
    */
    int temp;      //temp value to hold my first value to shift to the end of the array
    for (int i = 0; i < Rd; i++) {  //i is which department I am on, goes through all 5 departments
        for (int k = 0; k < Cd; k++) {  //k is which preference, used to keep checking until I find my programmer to move
            if (dep[i][k] == whichp) {  //found my programmer to move to the end, then I need to shift the ones after this programmer up one
                temp = dep[i][k];   //holds value as I will overwrite it
                for (int j = k; j < Cd - 1; j++) {  //starts at k, moves all the values up one index value
                    dep[i][j] = dep[i][j+1];    //moves up one index value
                }   //end for loop
                dep[i][Cd-1] = temp;    //set last value to my programmer I have moved
            }   //end if
        }   //end for
    }   //end for
}   //end clearFoundProgammer
void algorithm(int dep[Rd][Cd], int pro[Rp][Cp]) {  
    /*
    Purpose: algorithm that this lab is about. 
    Inputs: 2 2d arrays, one with departments and preferences, the other with programmers and preferences
    Output: Prints assignments of programmers to departments
    */
	int dpref[5] = {0,0,0,0,0}; //my array for department preferences, 0 means I haven't found that preference yet
    int whichProgrammer;    //keeps track of which programmer I am choosing
    int confArray[5];   //conflict array, is used to find which departments have programmer conflicts, so my programmer can choose from those options
    bool cont, conflict;    //two bools I use
    //readability space
	for (int i = 0; i < Rd; i++) {  //going to run once for each department, by end of each loop iteration I will add the correct programmer to dpref
	    if (dpref[i] != 0) {    //found this correct programmer in an earlier loop, don't run this loop
	        continue;   //go to next i
	    }   //end if
	    conflict = false;  //start with no conflict
	    for (int k = 0; k < 5; k++) {   //make my conflict array full of 0's
	        confArray[k] = 0;   //set each index to 0
	    }   //end for loop
	    confArray[i] = 1;   //the current department set to 1 as I don't check it in my conflict loop
	    for (int k = i+1; k < Rd; k++) {   //goes over the all the departments past the current one (as the previous ones have their programmers) and finds if there is a conflict - doesn't check previous departments
	        if (dep[i][0] == dep[k][0]) {   //use index 0 as only one I need to check, as I move already assigned programmers to the end
	            conflict = true;    //found a conflict
	            confArray[k] = 1;   //note in conflict array
	        }   //end if
	    }   //end for loop
	    whichProgrammer = dep[i][0];    //number of programmer, starts at 1.  If I use as an index need to subtract 1
	    if (conflict) { //conflict found earlier
	        for (int k = 0; k < Cp; k++) {  //checks programmer's preference, starting with the first one
	            int on = pro[whichProgrammer - 1][k];   //on is which department the programmer wants, 1 through 5, if used as index need to subtract 1
	            if (confArray[on - 1] == 1) {   //check the conflict array, since I am starting at the programmer's first preference whichever one I find first this programmer will be hired for.
	                dpref[on - 1] = whichProgrammer;    //then set that department in dpref to this programmer, use on-1 as it's an index
	                break;  //since I made dpref correct, end for loop.  This might set a different department than the i I am on, so later I will check and redo loop if needed
	            }   //end if
	        }   //end for
	    }   //end if
	    else {  //no conflict
	        dpref[i] = dep[i][0];   //no conflict, so first choice is correct choice
	    }   //end else
	    clearFoundProgrammer(dep, whichProgrammer);  //moves whichever Programmer I am on to the end of everybody's list, since I use index 0 for the next programmer choice
	    //readability space
	    cont = false;  //start with not continuing, as it is easier to say cont = true and break
	    for (int k = 0; k < 5; k++) {   //check if confArray is full
	        if (confArray[k] == 0) {    //found a department with no programmer
	            cont = true;    //continue towards the next i
	            break;  //leave this for loop
	        }   //end if
	    }   //end for loop
	    if (!(cont)) {  //don't continue, leave this for loop and print out which programmer went to each department
	        break;  //leave for loop
	    }   //end if
	    if (dpref[i] == 0) {    //filled a different department, so need to try this one again
	        i--;    //redo this i, since i++ at end of loop
	    }   //end if
	}   //end for loop
	//output
	for(int i = 1; i < 6; i++) {    //start at department 1, end at department 5
	    printf("Department #%d will get Programmer #%d\n", i, dpref[i-1]);  //print output as directed
	}   //end for
}   //end algorithm
int main() {    //start main, read in from file then call algorithm
    int departments[Rd][Cd];    //size as directed in assignment description
    int programmers[Rp][Cp];    //if differenct size, just need to change constants
	FILE* fp = fopen("matching-data.txt", "r+");  //opens a file, reading
	if (fp == NULL) {   //invalid file or didn't find file
		printf("Please check your file again.\n");  //error catch
	}   //end if
	//first loop is to populate the Departments
	for (int i = 0; i < 5; ++i) {   //read the  first 5 lines of file 
		fscanf(fp, "%d %d %d %d %d\n", &departments[0][i], &departments[1][i], &departments[2][i], &departments[3][i], &departments[4][i]);  //each line has preference for every department, splitting so I can keep preferences together
	}   //end for loop
	//second loop populates programmers
	for (int i = 0; i < 5; ++i) {   //read the last 5 lines of file
		fscanf(fp, "%d %d %d %d %d\n", &programmers[0][i], &programmers[1][i], &programmers[2][i], &programmers[3][i], &programmers[4][i]);  //populate programmers with their preferences
	}   //end for loop

	printf("EECS 348 Lab #EC1 Jesse DeBok\n");    //Header text
    algorithm(departments, programmers);    //call algorithm with the two arrays
}   //end main
