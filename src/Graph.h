//
// Created by Mike Yang for Network Resilience on 11/4/2022.
//

#ifndef RESEARCH_GRAPH_H
#define RESEARCH_GRAPH_H

#include <string>
#include <set>
#include <vector>
#include <map>
#include <random>
#include "Node.h"
#include "NetConstructs.h"
#include "crypto.hpp"

namespace NetworkResilience {

  class Graph {
  public:

    std::shared_ptr<DegreeDistro> dd ; // Cached degree distribution
    std::shared_ptr<ConnectedComps> cc ; // Cached connected components

    Graph(double NIn, double pIn);
    Graph(Graph const &graph);
    std::shared_ptr<ConnectedComps>  getConnectedComponents();
    static int containsCC(const NODE_ID& incomingNodeId, const ConnectedComps& conComp);
    int addToConnectedComponents(const NODE_ID& incomingNodeId);
    std::shared_ptr<ConnectedComp> iterateConnectedComponent(const ConnectedComp& inputC);
    static void addAllLinks (const std::shared_ptr<ConnectedComp>& c, const ConnectedComp& links);
    void randRmNodes(int n, double rmp);
    double mersenneTwisterEngine();
    int rmNode(const NODE_ID& nodeId);
//    DegreeDistro runAndGetDD(int N, double p, int times, std::string outFile);
void printStats(const DegreeDistro& m) const;
    std::random_device rd;   // non-deterministic generator
    crypto gen;

  protected:
    double p = 0.0; // Degree probability, random network
    double N = 0.0; // Size
    GraphRep g =  GraphRep();
    void generateNodes();

    std::shared_ptr<DegreeDistro> getDD();

  };

} // NetworkResilience

#endif //RESEARCH_GRAPH_H
