// Andrew Westlund
// 10/26/21
// Coalesce clusters of RNA strands iteratively

#include <cstdio>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <cmath>
#include "linkedLinkedListsSW.h"

using namespace std;

// Coalesce the list repeatedly until we get to out final threshold
void iterativeCoalescence(linkedLinkedLists &lLL, float firstThreshold, float finalThreshold, float difference) {
    float currThreshold = firstThreshold;           // Start from the beginning

    while (currThreshold > finalThreshold) {        // Until we have done all the iterations
        // cout << currThreshold << endl;
        lLL.coalesceAll(currThreshold);             // Coalesce the list at the current threshold
        currThreshold = currThreshold - difference; // Decrease by the amount passed
    }

    // Coalesce the list with the final threshold explicitly in case the decremental pattern chosen skips it
	lLL.coalesceAll(finalThreshold);
}


int main(int argc, char *argv[]) {

    float finalThreshold = 100;      // Stores the final threshold limit
    float firstThreshold = 100;     // Stores the first threshold that is being checked
    float difference = .0001;      // Stores the difference to be subtracted after each comparison

	cout << "Enter the first threshold : ";
	cin >> firstThreshold;
	cout << firstThreshold << endl;
	cout << "Enter the final threshold : ";
    cin >> finalThreshold;
	cout << finalThreshold << endl;
	cout << "How much to decrement : ";
    cin >> difference;
	cout << difference << endl;

	// Implement binary reading here
	fstream binFile;
	//binFile.open("/scratch/jbiederman/30kbin", ios::in | ios::binary);
	binFile.open("/scratch/swheat/covid2/out/binfile2", ios::in | ios::binary);

	binFile.seekg(0, ios::end);		// Go to the final byte
	// Squareroot the dividend of the number of bytes in the file and 4
	int strandCt = sqrt((binFile.tellg() / 4));
	binFile.seekg(0);				// Go back to the first byte of the file

	// Create a 2-dimensional matrix
	float **matrix = new float*[strandCt];

	for (int i = 0; i < strandCt; i++) {
        matrix[i] = new float[strandCt];
    }

	// Implement binary reading here
    FILE *fbinFile;
    //fbinFile = fopen("/scratch/jbiederman/30kbin", "r");
	fbinFile = fopen("/scratch/swheat/covid2/out/binfile2", "r");

	for (int x = 0; x < strandCt; x++) {
		fread(matrix[x], sizeof(float), strandCt, fbinFile);
	}

    linkedLinkedLists sickness(strandCt, matrix);

	iterativeCoalescence(sickness, firstThreshold, finalThreshold, difference);

    cout << "First Threshold : " << firstThreshold << "\tFinal Threshold : " << finalThreshold <<
	  "\tDifference of each coalescence : " << difference << endl;

	sickness.printList();

	
}
