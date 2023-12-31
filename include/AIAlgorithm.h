//
// Created by patrick on 01/10/23.
//

#ifndef CASALCIUMENTO_AIALGORITHM_H
#define CASALCIUMENTO_AIALGORITHM_H
#include "GTree.h"

class AIAlgorithm {
public:
    static void backtrackingSearch(GTree &gtree, int &depth);
    static void irrevocableSearch(GTree& gtree);
    static void breadthFirstSearch(GTree& gtree, bool to_prune, int &depth);
    static void orderedSearch(GTree& gtree, bool to_prune, int &depth);
    static void depthFirstSearch(GTree& gtree, bool to_prune, int &depth);
    static void manualSearch(GTree& gtree, int &depth);
    static void greedySearch(GTree& gtree, bool to_prune, int &depth);
    static void aStarSearch(GTree& gtree, bool to_prune, int &depth);
};


#endif //CASALCIUMENTO_AIALGORITHM_H
