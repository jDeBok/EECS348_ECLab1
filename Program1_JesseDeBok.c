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
    int whichProgrammer;
    int confArray[5];
    //dep[i][0];
	for (int i = 0; i < Rd; i++) {  //going to run once for each department, by end of each loop iteration I will add the correct programmer to dpref
	    if (dpref[i] != 0) {    //found this correct programmer in an earlier loop, don't run this loop
	        continue;
	    }
	    bool conflict = false;
	    for (int k = 0; k < 5; k++) {
	        confArray[k] = 0;
	    }
	    confArray[i] = 1;
	    for (int k = i+1; k < Rd; k++) {   //goes over the all the departments past the current one (as the previous ones have their programmers) and finds if there is a conflict
	        if (dep[i][0] == dep[k][0]) {
	            conflict = true;
	            confArray[k] = 1;
	        }
	    }
	    whichProgrammer = dep[i][0];    //number of programmer, starts at 1
	    if (conflict) {
	        for (int k = 0; k < Cp; k++) {  //checks programmer's preference
	            int on = pro[whichProgrammer - 1][k];   //on is which department the programmer wants
	            if (confArray[on - 1] == 1) {   //if the programmer and the department want the person
	                dpref[on - 1] = whichProgrammer;    //then set that department in dpref to this programmer
	                break;
	            } 
	        
	        }
	    }
	    else {
	        dpref[i] = dep[i][0];   //no conflict, so first choice is correct choice
	    }
	    clearFoundProgrammer(dep, whichProgrammer);  //moves whichever Programmer I am on to the end of everybody's list, since I use index 0 for the next programmer choice


	    
	    bool cont = false;
	    for (int k = 0; k < 5; k++) {   //check if confArray is full
	        if (confArray[k] == 0) {
	            cont = true;
	        }
	    }
	    if (!(cont)) {
	        break;
	    }
	    if (dpref[i] == 0) {    //filled a different department, so need to try this one again
	        i--;
	    }
	}
	
	//output
	for(int i = 1; i < 6; i++) {
	    printf("Department #%d will get Programmer #%d\n", i, dpref[i-1]);
	}
}
int main() {
    int departments[Rd][Cd];
    int programmers[Rp][Cp];
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
    algorithm(departments, programmers);
}
