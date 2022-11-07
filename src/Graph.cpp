//
// Created by 18604 on 11/4/2022.
//

#include "Graph.h"
#include "RandomGraph.h"
#include <memory>
#include <random>

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
        for (auto & i : cc) {
          ConnectedComp current = ConnectedComp();
          current = iterateConnectedComponent(i);
          while (i.size() != current.size()) {
            i = current;
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
   * @param incomingNodeId: input node id
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
  ConnectedComp Graph::iterateConnectedComponent(const ConnectedComp& inputC){
    ConnectedComp c = ConnectedComp();
    for (const NODE_ID& s: inputC){
      c.insert(s);
      addAllLinks(c, g.find(s)->second.getLinksSet());
    }
    return c;
  }

  /**
   * Add all Links
   * */
   void Graph::addAllLinks (ConnectedComp& c, const ConnectedComp& links){
     for (const auto& s : links){
       c.insert(s);
     }
   }

  /**
    * Randomly removes n nodes from the graph.
    * @param n ; number of nodes to be removed.
    * @param rmp ; removal probability, suggests the probability of a node tobe removed.
    * */
  void Graph::randRmNodes(int n, double rmp){
    int rmd = 0; // # of nodes removed
    while(rmd<n){
      if(mersenneTwisterEngine()<rmp){
        int idx = (int) ((int)(mersenneTwisterEngine()*N)) % ((int)N);
        if(rmNode(std::to_string(idx)))
          rmd++;
      }
    }
  }
  /**
   * Use Mersenne Twister to spread the distribution of random
   * device. Return the random number between 0 and 1.0.
   * @return random number between 0 and 1.0
   * */
  float Graph::mersenneTwisterEngine(){
    std::random_device rd;   // non-deterministic generator
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0,1.0);
    return (float )dis(gen);
  }


  /**
   * Removes the input node and all links that connects to it.
   * @param nodeId ; node to be removed.
   * */
  int Graph::rmNode(const NODE_ID& nodeId){
    if (!g.count(nodeId)){
      return false;
    }
    for (const NODE_ID& s : g.find(nodeId)->second.getLinksSet()){
      g.find(s)->second.unlink(nodeId);
    }
    return g.erase(nodeId);
  }

  /**
    * Run the graph generation x times, and return the accumulated
    * */
  DegreeDistro Graph::runAndGetDD(int N, double p, int times, std::string outFile) {
//    BlockingQueue<Integer> queue = new LinkedBlockingQueue<Integer>();
//      Thread pgs = progressPrint(queue);
//      pgs.start();
//      Map<Integer,Integer> dd = getDD(N,p);
//      queue.add((int)(1/times)*100);
//      if (times < 1){
//        return dd;
//      }
//      for (int i=0 ;i< times-1;i++){
//        dd = getDD(N,p,dd);
//        queue.add((int)(i/times)*100);
//      }
//      queue.add(100);
//      new GraphOutput().writeMap(outFile,dd);
//      return dd;
  }

  DegreeDistro Graph::getDD() {
    dd = *(std::make_shared<DegreeDistro>());
    for (String s: g.keySet()){
      Integer degree = g.get(s).getDegree();
      if(!dd.containsKey(degree)){
        dd.put(degree,1);
      }
      else {
        dd.replace(degree,dd.get(degree)+1);
      }
    }
    return dd;
  }


  /**
   *  Run the simulation adn return the degree distribution.
   * @param N ; number of nodes
   * @param p ; edge probability
   * @return degree distribution
   * */
  DegreeDistro getDD(int N, double p){
    RandomGraph g = *(std::make_shared<RandomGraph>(N,p)) ;
    g.run();
    return g.getDD();
  }



} // NetworkResilience