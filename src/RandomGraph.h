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
    std::string* getCSV ();
    using Graph::printStats;
    using Graph::getDD;
    DegreeDistro* getDD(int in_n, double in_p);
    size_t size=0;
    void randConnection();
    RandomGraph* gph = nullptr;
    ~RandomGraph();
  protected:
    void randEdges (int k=0);
    int randEdge();
    int randEdge(int k);
    void linkTwo(size_t i, size_t f);
    void linkTwo(const NODE_ID& i, const NODE_ID& f);
  };

} // NetowrkResilience

#endif //RESEARCH_RANDOMGRAPH_H
