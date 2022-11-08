//
// Created by 18604 on 11/6/2022.
//

#ifndef RESEARCH_RANDOMGRAPH_H
#define RESEARCH_RANDOMGRAPH_H

#include "NetConstructs.h"
#include "Node.h"
#include <map>
#include <vector>
#include <set>
#include <string>
#include "Graph.h"

namespace NetworkResilience {

  class RandomGraph : private Graph {
  public:
    using Graph::Graph;
    int run ();
    int run (int k);
    std::shared_ptr<std::string> getCSV ();

  protected:
    void randEdges (int k=0);
    int randEdge();
    int randEdge(int k);
    void linkTwo(int i, int f);
    using Graph::getDD;
    DegreeDistro getDD(int in_n, double in_p);
  };

} // NetowrkResilience

#endif //RESEARCH_RANDOMGRAPH_H
