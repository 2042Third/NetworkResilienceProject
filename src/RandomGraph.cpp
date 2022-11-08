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
  std::shared_ptr<DegreeDistro> RandomGraph::getDD(int in_n, double in_p){
    std::shared_ptr<RandomGraph> gph = std::make_shared<RandomGraph>(in_n, in_p) ;
    gph->run();
    return gph->getDD();
  }
  int RandomGraph::run () {
    std::cout<<"Begin generation of "<<N << " nodes"<<std::endl;
    this->generateNodes();
    std::cout<<"Generation done.\n Begin linking with p="<<p<<std::endl;
    randEdges();
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
  void RandomGraph::randEdges (int k) {
    for (int i=0; i<N ;i++){
      for (int f=i+1;f<N;f++){
        if(k){if(randEdge(k)){linkTwo(i, f);}}
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
   * Links the two nodes
   * @param f node
   * @param i node
   * */
  void RandomGraph::linkTwo(int i, int f) {
    size+=1;
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

  RandomGraph::~RandomGraph() = default;

  RandomGraph::RandomGraph(const RandomGraph &graph): Graph(graph) {

  }


} // NetowrkResilience