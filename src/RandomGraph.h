//
// Created by 18604 on 11/6/2022.
//

#ifndef RESEARCH_RANDOMGRAPH_H
#define RESEARCH_RANDOMGRAPH_H

#include "Graph.h"

namespace NetworkResilience {

  class RandomGraph :  Graph {
  public:
    using Graph::Graph;
    int run ();
    int run (int k);
    std::shared_ptr<std::string> getCSV ();

  protected:
    void randEdges (int k);
    int randEdge();
    int randEdge(int k);

    void linkTwo(int i, int f);
  };

} // NetowrkResilience

#endif //RESEARCH_RANDOMGRAPH_H
