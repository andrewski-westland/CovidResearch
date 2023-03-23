# CovidResearch
Software that Compares the DNA of People Infected by COVID via Coalescence.

The program would read in a binary file (that Andrew did not feel would be appropriate to include, due to potential privacy violations) that consisted of ratios of the extent that two samples of DNA matched. The program creates a linked lists of linked lists, then compares the samples against each other to see if their matching ratio is high enough to coalesce, i.e. the second linked list would be appended to the end of the first linked list. 

The threshold for how high the match has to be is up to the user; it would start at the given starting threshold, then the threshold would decrease by a given amount repeatedly, coalescing along the way, until it reached the given final threshold. A group of samples could be able to coalesce with another group of samples if and only if every sample in one group matched every sample in the other group to the level of the threshold.

Input: Starting Threshold (%), Final Threshold (%), Size of Decrease (%)

Output: The coalesced clusters with each sampleID that fit within the cluster and the number of samples within the cluster, as well as the number of total clusters and the number of clusters with multiple samples.

Compile: g++ lLLm.cpp linkedLinkedLists.cpp -O2 -o coal

Execution: ./coal  (User input will be requested)
