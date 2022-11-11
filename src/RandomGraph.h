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
    RandomGraph(double NIn, double pIn);

    RandomGraph(RandomGraph const &graph);

    int run ();
    int run (int k);
    std::shared_ptr<std::string> getCSV ();
    using Graph::printStats;
    using Graph::getDD;
    static std::shared_ptr<DegreeDistro> getDD(int in_n, double in_p);
    size_t size=0;
    void randConnection();
    ~RandomGraph();
  protected:
    void randEdges (int k=0);
    int randEdge();
    int randEdge(int k);
    void linkTwo(size_t i, size_t f);
    void linkTwo(NODE_ID i, NODE_ID f);
  };

} // NetowrkResilience

#endif //RESEARCH_RANDOMGRAPH_H
