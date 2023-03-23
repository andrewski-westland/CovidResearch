// Andrew Westlund
// 11/11/21
// Coalesce COVID strands together

#ifndef LLL_H
#define LLL_H

class strand {
    public:
        strand(int k);        // Constructor
        strand *nextStrand;   // Points to the next strand
        int key;              // Stores the strand's index on the matrix
        friend class head;
};

class head {
    public:
        head();               // Constructor
        head *nextHead;       // Points to the next element of the head list
        strand *firstStrand;  // Points to the first element of the strand list
        int numOfStrands;     // Stores the number
};

class linkedLinkedLists {
    private:
        /*
        class strand {
            public:
                strand(int k);        // Constructor
                strand *nextStrand;   // Points to the next strand
                int key;              // Stores the strand's index on the matrix
                // Maybe include a pointer to the actual COVID strand object
                friend class head;
                friend class linkedLinkedLists;
                                                                                        };
        class head {
            public:
                head();               // Constructor
                head *nextHead;       // Points to the next element of the head list
                strand *firstStrand;  // Points to the first element of the strand list
                friend class strand;
                friend class linkedLinkedLists;
        };
        */

        head *root;                   // Points to the first head of the list

        float threshold;              // Stores the current threshold value

        float **matrix;               // The two-dimensional array for the scores

        int strandCount;              // Stores the number of strands there are

		int numOfClusters;			  // Stores the number of clusters there are

        // Preconditions: None
        // Postconditions: The linked list is recursively set
        void setLinkedLinkedList(head *currHead);

		// Preconditions: None
		// Postconditions: The linked List is recursively set
		void coalesce(head *&m, head *&n, head *&j);

		// Preconditions: The number being passed must be less than the number of clusters
		// Postconditions: The dates of the ith cluster are printed
		void printDates(int headNum) const;

	public:
		// Constructor
		linkedLinkedLists(int strandCount, float **mat);

		// Preconditions: the both of the matrix's dimensions lengths must be greater than
		// or equal to the passed strand count
		// Postconditions: Coalsece all of the elements of the list at the given threshold
		void coalesceAll(float thresh);

		// Preconditions: None
		// Postconditions: The linked linked list is printed out by groups and strands
		void printList() const;

		friend class head;
		friend class strand;
};

#endif
