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

namespace NetworkResilience {

  class Graph {
  public:

    DegreeDistro dd = DegreeDistro(); // Cached degree distribution
    ConnectedComps cc = ConnectedComps(); // Cached connected components

    Graph(double NIn, double pIn);
    Graph(Graph const &graph);
    ConnectedComps getConnectedComponents();
    static int containsCC(const NODE_ID& incomingNodeId, const ConnectedComps& conComp);
    int addToConnectedComponents(const NODE_ID& incomingNodeId);
    ConnectedComp iterateConnectedComponent(const ConnectedComp& inputC);
    static void addAllLinks (ConnectedComp& c, const ConnectedComp& links);
    void randRmNodes(int n, double rmp);
    float mersenneTwisterEngine();
    int rmNode(const NODE_ID& nodeId);
    DegreeDistro runAndGetDD(int N, double p, int times, std::string outFile);
    static void printStats(const DegreeDistro& m);
    std::random_device rd;   // non-deterministic generator
    std::mt19937 gen;
    std::uniform_real_distribution<> dis;

  protected:
    double p = 0.0; // Degree probability, random network
    double N = 0.0; // Size
    GraphRep g =  GraphRep();
    void generateNodes();

    DegreeDistro getDD();

  };

} // NetworkResilience

#endif //RESEARCH_GRAPH_H
