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
    cc = new ConnectedComps();
    ttl = std::floor(p * N * (N - 1) / 2);
    gen = new crypto();
  }


  /**
   * Iterate through all nodes in a set, and return a set of nodes that are connected to it
   * by one edge.
   * @param inputC ; connected component
   * @return a set of nodes that are at most one edge away from one of the input nodes.
   * */
  ConnectedComp* Graph::iterateConnectedComponent(const ConnectedComp& inputC){
    ConnectedComp* c =new ConnectedComp();
    for (const NODE_ID& s: inputC){
      c->insert(s);
      addAllLinks(c, g.find(s)->second.getLinksSet());
    }
    return c;
  }

  /**
   * Add all Links
   * */
   void Graph::addAllLinks ( ConnectedComp* c, const ConnectedComp& links){
     for (const std::string& s : links){
       c->insert(s);
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
  double Graph::mersenneTwisterEngine(){
    return gen->next();
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


  DegreeDistro* Graph::getDD() {
    dd = new DegreeDistro();
    for (const auto& s: g){
      size_t degree = s.second.getDegree();
      totalDegree+=degree;
      if(!dd->count(degree)){
        dd->insert({degree, 1});
      }
      else {
        (*dd)[degree] = degree+1;
      }
    }
    return dd;
  }


  /**
     * Generates unconnected N nodes.
     * */
  void Graph::generateNodes(){
    const size_t exp_degree = (ttl / N);
    for (int i=0 ; i<N ; i++){
      NODE_ID nodeid = std::to_string(i);
      trashCan.push_back(new Node(nodeid,exp_degree));
      Node nd = *(trashCan.back());
      g.insert({nodeid,nd});
    }
  }

  void Graph::printStats(const DegreeDistro& m) const{
    std::cout<<"Calculating statistics..."<<std::endl;

    size_t totalNodes = g.size();

    size_t avgDegree = (totalDegree/2)/totalNodes;

    std::printf("Total nodes connectors: %zu\n"
                "Total degrees:%zu\n"
                "Average degree:%zu\n"
                "\n Expected number of links: %zu\n"
                "Expected average degree: %f\n"
                , totalNodes
                ,totalDegree/2
                , avgDegree
                , ttl
                , ttl / N
                );

  }

  Graph::Graph(const Graph &graph) {
    p=graph.p;
    N=graph.N;
    ttl = std::floor(p * N * (N - 1) / 2);

    gen = new crypto();
  }

  Graph::~Graph(){
    delete gen;
    delete dd;
    for (auto & i : *cc)
      delete i;
    delete cc;
    for (auto & i : trashCan)
      delete i;
  }

} // NetworkResilience