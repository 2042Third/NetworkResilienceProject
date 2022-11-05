//
// Created by Mike Yang for Network Resilience on 11/4/2022.
//

#ifndef RESEARCH_GRAPH_H
#define RESEARCH_GRAPH_H

#include <string>
#include <set>
#include <vector>
#include <map>
#include "Node.h"
#include "NetConstructs.h"

namespace NetworkResilience {

  class Graph {
  public:

    DegreeDistro dd = DegreeDistro();
    ConnectedComps cc = ConnectedComps();

    Graph(double NIn, double pIn);

    ConnectedComps getConnectedComponents();
    static int containsCC(const NODE_ID& incomingNodeId, const ConnectedComps& conComp);
    int addToConnectedComponents(const NODE_ID& incomingNodeId);
    ConnectedComp iterateConnectedComponent(const ConnectedComp& inputC);
    static void addAllLinks (ConnectedComp& c, const ConnectedComp& links);
    void randRmNodes(int n, double rmp);
    static float mersenneTwisterEngine();
    int rmNode(const NODE_ID& nodeId);

  protected:

    double p = 0.0;
    double N = 0.0;
    GraphRep g =  GraphRep();


  };

} // NetworkResilience

#endif //RESEARCH_GRAPH_H
