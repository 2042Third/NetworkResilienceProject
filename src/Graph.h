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

    DegreeDistro* dd = nullptr; // Cached degree distribution
    ConnectedComps* cc = nullptr; // Cached connected components

    void add_connected(const size_t &a,const basic_string<char> &b);
    int add_connected(const basic_string<char> &a);
    Graph(double NIn, double pIn);
    Graph(Graph const &graph);
    ConnectedComp* iterateConnectedComponent(const ConnectedComp& inputC);
    static void addAllLinks ( ConnectedComp* c, const ConnectedComp& links);
    void randRmNodes(int n, double rmp);
    double mersenneTwisterEngine();
    int rmNode(const NODE_ID& nodeId);
    void printStats(const DegreeDistro& m) const;

    void iterate_nodes(const NODE_ID& n) ;
    std::random_device rd;   // non-deterministic generator
    crypto *gen = nullptr;
    ~Graph();

    void check_connected( );

  protected:
    unordered_set<NODE_ID> itrd;
    double p = 0.0; // Degree probability, random network
    double N = 0.0; // Size
    size_t ttl = 0; // average degree
    std::vector<Node *>trashCan; // take out the trash when done!
    GraphRep g =  GraphRep();
    size_t totalDegree = 0;
    void generateNodes();

    DegreeDistro* getDD();

  };

} // NetworkResilience

#endif //RESEARCH_GRAPH_H
