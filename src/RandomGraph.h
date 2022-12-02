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

  class RandomGraph : public Graph {
  public:
    RandomGraph(G_size NIn, double pIn);

    RandomGraph(RandomGraph const &graph);

    int run (int k);
    std::string  getCSV ();
    using Graph::printStats;
    using Graph::getDD;
    DegreeDistro* getDD(int in_n, double in_p);
    size_t size=0;
    virtual void randConnection();
    virtual void randConnection_second();
    RandomGraph* gph = nullptr;
    ~RandomGraph();

    int run ();
    int run_second_layer();

  protected:
    void randEdges (int k=0);
    int randEdge();
    int randEdge(int k);
    void linkTwo(const NODE_ID& i, const NODE_ID& f);
  };

} // NetowrkResilience

#endif //RESEARCH_RANDOMGRAPH_H
