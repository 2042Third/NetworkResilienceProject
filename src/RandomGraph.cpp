//
// Created by 18604 on 11/6/2022.
//

#include <random>
#include <memory>
#include "Graph.h"
#include "RandomGraph.h"



namespace NetworkResilience {
  RandomGraph::RandomGraph(double NIn, double pIn): Graph(NIn,pIn){
//    p = pIn;
//    N = NIn;
//    gen = std::mt19937(rd());
//    dis = std::uniform_real_distribution<>(0,1.0);
  }
  /**
 *  Run the simulation adn return the degree distribution.
 * @param in_n ; number of nodes
 * @param in_p ; edge probability
 * @return degree distribution
 * */
  DegreeDistro* RandomGraph::getDD(int in_n, double in_p){
    gph = new RandomGraph(in_n, in_p) ;
    gph->run();
    return gph->getDD();
  }

  int RandomGraph::run () {
    std::cout<<"Begin generation of "<<N << " nodes"<<std::endl;
    this->generateNodes();
    std::cout<<"Generation done.\n Begin linking with p="<<p<<std::endl;
//    randEdges();
    randConnection();
    std::cout<<"Linking done."<<std::endl;
    return false;
  }

  int RandomGraph::run (int k) {
    this->generateNodes();
    randEdges(k);
    return false;
  }

  /**
   * Converts and outputs the graph as a .csv string.
   * */
  std::string* RandomGraph::getCSV(){
    auto* out = new std::string();
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
  void RandomGraph::randEdges (int k) {
    for (int i=0; i<N ;i++){
// Change #1
      for (int f=i+1;f<N;f++){ // every node links to average degree number of nodes
        if(k){
          if(randEdge(k)){
            linkTwo(i, f);
          }
        }
        else{
          if(randEdge()){
            linkTwo(i,f);
//            std::cout<<"Made link #"<<size<<" between node#"<<i<<" and node#"<<f<<std::endl;
          }
        }
      }
    }
  }

  /**
   * Randomly connects nodes
   * */
  void RandomGraph::randConnection(){
    size_t i =0;
    while(i<ttl){
      const NODE_ID a = std::to_string(gen->nextInt() % (uint32_t)N);
      const NODE_ID b = std::to_string(gen->nextInt() % (uint32_t)N);
      if(a == b) // Don't connect on the diagonal
        continue;
      if(g.find(a)->second.isLinkedWith(g.find(b)->first))
        continue;
      // Link
      linkTwo(a,b);
      // Only called in the first time
//      if(!i){
//        (*cc)[0]->insert(a);
//        (*cc)[0]->insert(b);
//        i++;
//        continue;
//      }
      i++;
      // Fill connected component
//      const size_t fd_a = (*cc)[0]->count(a);
//      const size_t fd_b = (*cc)[0]->count(b);
//      if(fd_a){
//        (*cc)[0]->insert(b);
//      }
//      else if(fd_b){
//        (*cc)[0]->insert(a);
//      }
    }
    std::cout<<"Total random iteration: "<<i<<std::endl;
  }

  /**
   * Links the two nodes
   * @param f node
   * @param i node
   * */
  void RandomGraph::linkTwo(size_t i, size_t f) {
    size+=1;
    const std::string a = std::to_string(i);
    const std::string b = std::to_string(f);
    g.find(a)->second.link(b);
    g.find(b)->second.link(a);
  }
  /**
   * Links the two nodes
   * @param f node
   * @param i node
   * */
  void RandomGraph::linkTwo(const NODE_ID& i, const NODE_ID& f) {
    size+=1;
    g.find(i)->second.link(f);
    g.find(f)->second.link(i);
  }

  /**
   * Generate a random number between 0 and 1.
   * If the number exceeds p return true, else false.
   * @return true, if random number greater than p.
   * */
  int RandomGraph::randEdge(int k) {
    return mersenneTwisterEngine() < k/(N-1);
  }

  RandomGraph::~RandomGraph() {
      delete gph;
  }

  RandomGraph::RandomGraph(const RandomGraph &graph): Graph(graph) {

  }


} // NetowrkResilience