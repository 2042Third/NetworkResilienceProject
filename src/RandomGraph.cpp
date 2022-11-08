//
// Created by 18604 on 11/6/2022.
//

#include "RandomGraph.h"

namespace NetworkResilience {

  int RandomGraph::run () {
    this.generateNodes();
    randEdges();
    return false;
  }

  int RandomGraph::run (int k) {
    this.generateNodes();
    randEdges(k);
    return false;
  }

  /**
   * Converts and outputs the graph as a .csv string.
   * */
  std::shared_ptr<std::string> RandomGraph::getCSV(){
    std::shared_ptr<std::string> out (new std::string());
    for (const auto& s : g) {
      out->append(*(s.second.getCSVString()));
    }
    return out;
  }


  /**
   * Generate a random number between 0 and 1.
   * If the number exceeds p return true, else false.
   * @return true, if random number greater than p.
   * */
  int RandomGraph::randEdge() {
    return mersenneTwisterEngine() < p;
  }


  /**
   * For all N(N-1)/2 possible edges, link if a random
   * number generated is greater than p.
   * */
  void RandomGraph::randEdges (int k=0) {
    for (int i=0; i<N ;i++){
      for (int f=i+1;f<N;f++){
        if(k){if(randEdge(k)){linkTwo(i, f);}}
        else{if(randEdge()){ linkTwo(i,f);}}
      }
    }
  }

  /**
   * Links the two nodes
   * @param f node
   * @param i node
   * */
  void RandomGraph::linkTwo(int i, int f) {
    std::string a = std::to_string(i);
    std::string b = std::to_string(f);
    g.find(a)->second.link(b);
    g.find(b)->second.link(a);
  }

  /**
   * Generate a random number between 0 and 1.
   * If the number exceeds p return true, else false.
   * @return true, if random number greater than p.
   * */
  int RandomGraph::randEdge(int k) {
    return mersenneTwisterEngine() < k/(N-1);
  }
} // NetowrkResilience