//
// Created by 18604 on 11/4/2022.
//

#include "Graph.h"

namespace NetworkResilience {
  /**
   * Initialize the graph class.
   * @param NIn N; number of nodes.
   * @param pIn p; edge probability.
   * */
  Graph::Graph(double NIn, double pIn){
    p = pIn;
    N = NIn;
  }

  /**
     * Iterate through the net, returns a list of connected components.
     * */
  ConnectedComps Graph::getConnectedComponents(){
    for (auto const& s : g){
      if(!containsCC(s.first,cc)){
        addToConnectedComponents(s.first);
        for (int i=0 ;i<cc.size();i++) {
          ConnectedComp current = ConnectedComp();
          current = iterateConnectedComponent(cc[i]);
          while (cc.get(i).size() != current.size()) {
            cc.set(i,current);
            current = iterateConnectedComponent(current);
          }
        }
      }
    }
    return cc;
  }

  /**
   * Checks if the node is in any of the recorded connected components.
   * @param incomingNodeId: input node id
   * @param conComp: connected components
   * @return 1 if the node exists in one of them.
   *          0 if the node doesn't exist in any of the existing component,
   * */
  int Graph::containsCC(const NODE_ID& incomingNodeId, const ConnectedComps& conComp){
    for (const ConnectedComp& c: conComp){
      if(c.count(incomingNodeId)){
        return true;
      }
    }
    return false;
  }

  /**
     * Adds the input node to a new connected component.
     * @return 1 if the node doesn't exist in any of the existing component,
     *          0 if the node exists in one of them.
     * */
  int Graph::addToConnectedComponents(const NODE_ID& incomingNodeId){
    // Check if it exists.
    for (const ConnectedComp& c: cc){
      if(c.count(incomingNodeId)){
        return 0;
      }
    }
    // Add new connected component
    ConnectedComp set = ConnectedComp ();
    set.insert(incomingNodeId);
    cc.push_back(set);
    return 1;
  }

  /**
     * Iterate through all nodes in a set, and return a set of nodes that are connected to it
     * by one edge.
     * @param inputC ; connected component
     * @return a set of nodes that are at most one edge away from one of the input nodes.
     * */
  ConnectedComp iterateConnectedComponent(ConnectedComp inputC){
    ConnectedComp c = ConnectedComp();
    for (NODE_ID s: inputC){
      c.insert(s);
      c.addAll(g.get(s).getLinksSet());
    }
    return c;
  }


} // NetworkResilience