// Andrew Westlund
// 11/11/21
// Coalesce clusters of RNA strands iteratively

#include <iostream>                // Provides cout
#include "linkedLinkedListsSW.h"   // Provides header file containing definitions

using namespace std;

// Constructor for strand node that takes in a key index to store
strand::strand(int k) {
    strand *nextStrand = NULL;  // Points to the next strand (NULL by default)
    key = k;                    // Stores the strand's index on the matrix
}


// Constructor for head node that takes in a strand to point to
head::head() {
    head *nextHead = NULL;       // The next head will start as NULL
    strand *firstStrand = NULL;  // The first strand it points to will be passed in
    numOfStrands = 1;            // Each head starts with one strand
}


// The linked list is set
void linkedLinkedLists::setLinkedLinkedList(head *currHead) {
    int i;

	// Repeat through all of the strands but the last one
	for (i = 0; i < strandCount - 1; i++) {
        currHead->nextHead = new head();
        currHead->firstStrand = new strand(i);
        currHead = currHead->nextHead;
		numOfClusters++;
    }

	// Assign the last head a firstStrand but no a non-NULL nextHead
	currHead->firstStrand = new strand(i);
	numOfClusters++;
}

// Performs the action of coalescing the two individual linked lists of strands
void linkedLinkedLists::coalesce(head *&m, head *&n, head *&j) {
    strand *s1 = m->firstStrand;    // Sets s1 to the first strand of m's strand list
    while (s1->nextStrand) {        // Make s1 become the last element of the strand list
        s1 = s1->nextStrand;
    }

	// Set s1's next strand to the first strand of the coalesced list
	s1->nextStrand = n->firstStrand;
    m->numOfStrands = m->numOfStrands + n->numOfStrands;
    j->nextHead = n->nextHead;
	numOfClusters--;
    delete n;                       // Prevents memory leaks
}


// Constructor for the linkedLinkedLists object
linkedLinkedLists::linkedLinkedLists(int strandCt, float **mat) {
    root = new head();              // Points to the first head of the list
    strandCount = strandCt;         // Stores the number of strands there are
    matrix = mat;                   // The two-dimensional array for the scores
    numOfClusters = 0;				// Set the number of clusters to 0
	setLinkedLinkedList(root);      // The linked list is set
}


// Coalesce all of the elements of the list at the given threshold
void linkedLinkedLists::coalesceAll(float thresh) {
    threshold = thresh;  // Keeps track of the current threshold passed
    head *m = root;      // Start with the beginning of the list
    head *n;             // n will be after m and the two nodes' strands are compared
    head *j;
    bool check;          // If one strand does not match, the two lists cannot coalesce
    strand *s1;          // Moves through the strands of head m
    strand *s2;          // Moves through the strands of head n

    while (m != NULL && (m->nextHead) != NULL) {    // While m is not the last head or NULL
        j = m;                      // The first head before the first n is m
        n = m->nextHead;            // Start with n being the first head after m

        while (n != NULL) {         // While n is not NULL
            check = true;           // Before the two nodes compare, reset check to true
            s1 = m->firstStrand;    // Set s1 as the first strand of m's list
            s2 = n->firstStrand;    // Set s2 as the first strand of n's list

            // Go through all of m's strands
            while (s1 != NULL) {
				// Go through all of n's strands
				while (s2 != NULL) {
					// If s1 compared to s2 has too small a score or vice versa, move on
					if (matrix[s1->key][s2->key] < threshold ||
                      matrix[s2->key][s1->key] < threshold) {
                        check = false;  // Makes sure no comparisons happen until n changes
                        break;
                    }
					// The score was compatible, so go to n's next strand
					s2 = s2->nextStrand;
				}

				if (!check) {				// Makes sure no comparisons happen until n changes
					break;
				}
				// The scores were compatible, so go to m's next strand
				s1 = s1->nextStrand;
			}

	        if (!check) {           // If not all of the strands matched, move on
    	        j = n;
        	    n = n->nextHead;

	        } else {
				// If all the strands of m and n matched each other's thresholds, coalesce the
				// lists into m's list
				coalesce(m, n, j);
				// Do this whole process again with the same m but with n's next head
				n = j->nextHead;
			}
		}
		// Move on to the next m
		m = m->nextHead;
	}
}


void linkedLinkedLists::printDates(int headNum) const {

}


// The linked linked list is printed out by groups and strands
void linkedLinkedLists::printList() const {
    head *m = root;                     // Start from the beginning of the list
    // cout << "Print List" << endl;

	strand *s1;                         // Start from the root's first strand
    int index = 0;                      // Keeps track of which group we are at
	int numOfMultClusters = 0;

    // For all the heads
    while (m != NULL) {
        // fprintf(stderr, "%d\n", index);
		cout << index << " : ";         // Prints out the group's number
        if (m->numOfStrands > 1) {
			numOfMultClusters++;
		}
		s1 = (m->firstStrand);          // Set s1 to the head's first strand
        // cout << "s1 == NULL : " << ((s1->nextStrand) == NULL) << endl;

		// For all of the strands but the the last the current m
		while ((s1->nextStrand) != NULL) {
            cout << (s1->key) << " ";   // Print out that strand's key
            s1 = s1->nextStrand;        // Move to the next strand
            // fprintf(stderr, "%.2f \n", (s1->key));
        }

		// Print out the last strand's key and how many strands there were
		cout << (s1->key) << "\nNumber of Strands : " << m->numOfStrands << endl << endl;
        m = (m->nextHead);              // Move on to the next group
        index ++;                       // Increase the numeric representation of the group
    }
	cout << "Number of Class Clusters : " << numOfClusters << endl;
    cout << "Number of Clusters with Multiple Files : " << numOfMultClusters << endl;
	cout << endl;                       // Print an empty line afterwards
}
