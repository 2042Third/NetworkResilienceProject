//
// Created by Mike Yang for Network Resilience on 11/4/2022.
//

#ifndef RESEARCH_GRAPH_H
#define RESEARCH_GRAPH_H
#include <iterator>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <random>
#include <fstream>
#include "Node.h"
#include "NetConstructs.h"
#include "crypto.hpp"
#include "output.h"

namespace NetworkResilience {

  class Graph {


  public:

    DegreeDistro* dd = nullptr; // Cached degree distribution
    ConnectedComps* cc = nullptr; // Cached connected components

    Graph(G_size NIn, double pIn);
    Graph(Graph const &graph);
    ConnectedComp* iterateConnectedComponent(const ConnectedComp& inputC);
    static void addAllLinks ( ConnectedComp* c, const ConnectedComp& links);
    void randRmNodes(int n, double rmp);
    double mersenneTwisterEngine();
    int rmNode(const NODE_ID& nodeId);
    void printStats(const DegreeDistro& m) const;

    std::random_device rd;   // non-deterministic generator
    crypto *gen = nullptr;
    ~Graph();
    std::ofstream file;
    void o_file(const std::string& of){file.open(of,	ios::in | ios::out);}
    void write_output(const std::string& a ){
      NetworkResilience::output::write_to(file,a);
    }

  protected:
    unordered_set<NODE_ID> itrd;
    double p = 0.0; // Degree probability, random network
    G_size N = 0.0; // Size
    G_size ttl = 0; // average degree
    std::vector<Node *>trashCan; // take out the trash when done!
    GraphRep g =  GraphRep();
    G_size totalDegree = 0;
    void generateNodes();

    DegreeDistro* getDD();

  };

} // NetworkResilience

#endif //RESEARCH_GRAPH_H
