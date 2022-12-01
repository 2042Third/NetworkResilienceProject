//
// Created by Mike Yang on 11/29/2022.
//

#ifndef RESEARCH_ALGORITHMS_H
#define RESEARCH_ALGORITHMS_H
#include <vector>
#include <sstream>
#include "RandomGraph.h"

namespace NetworkResilience{
  class Algorithms :public RandomGraph{

  public:
    std::vector<G_size> sizes;
    std::vector<G_size> parents;
    G_size largest, largest_size;
    int second_layer = 0;

    /**
     * Make each node its own parent.
     * */
    void make_set() {
      for (auto i=0; i<= N;i++){
        parents[i] = i;
        sizes[i] = 1;
      }
    }
    /**
     * Make each node its own parent.
     * */
    void make_set_second() {
      for (auto i=0; i<= N*2+1;i++){
        parents[i] = i;
        sizes[i] = 1;
      }
    }

    /**
     *  Find the parent of the input node.
     * */
    G_size find_set(G_size n){
       while (parents[n] != n){
         parents[n] = parents[parents[n]];
         n = parents[n];
       }
      return n;
    }

    /**
     * Merge two connected components together.
     * */
    void union_sets(G_size n1, G_size n2){
      n1 = find_set(n1);
      n2 = find_set(n2);
      if(n1!=n2){
        if (sizes[n1]<sizes[n2]) std::swap(n1,n2);
        parents[n2] = n1;
        sizes[n1] += sizes[n2];
        if(sizes[n1]>largest_size){
          largest = n1;
          largest_size = sizes[n1];
        }
      }
    }

    /**
     * Get the number of connected components.
     * */
    G_size connected_components_count(){
      std::unordered_set<G_size> tmp;
      for (auto i=0 ; i<N ;i++) tmp.insert(find_set(i));
      std::cout<< "Largest Connected Component     : "<< largest<<std::endl;
      std::cout<< "Largest Connected Component size: "<< largest_size<<std::endl;
      return tmp.size();
    }

    /**
   * Randomly connects nodes
   * */
    void randConnection()override{
      size_t i =0;
      while(i<ttl){
        const G_size a = gen->nextInt() % N;
        const G_size b = gen->nextInt() % N;
        if(a == b) // Don't connect on the diagonal
          continue;
        if(g.find(a)->second.isLinkedWith(g.find(b)->first))
          continue;
        // Link
        union_sets(a,b);
        linkTwo(a,b);
        i++;
      }
      std::cout<<"Total random iteration: "<<i<<std::endl;
    }

    /**
  * Randomly connects nodes
  * */
    void randConnection_second()override{
      size_t i =0;
      while(i<ttl){
        const G_size a = gen->nextInt() % N + N;
        const G_size b = gen->nextInt() % N + N;
        if(a == b) // Don't connect on the diagonal
          continue;
        if(g.find(a)->second.isLinkedWith(g.find(b)->first))
          continue;
        // Link
        union_sets(a,b);
        linkTwo(a,b);
        i++;
      }
      std::cout<<"Total random iteration: "<<i<<std::endl;
    }

    /**
   * Generates unconnected N nodes for the second layer.
   * */
    void generateNodes_second() override{
      const G_size exp_degree = (ttl / N);
      for (auto i=0 ; i<N ; i++){
        NODE_ID nodeid = i+N;
        trashCan.push_back(new Node(nodeid,exp_degree));
        Node nd = *(trashCan.back());
        g.insert({nodeid,nd});
        union_sets(nodeid,nodeid-N);
        linkTwo(nodeid,nodeid-N);
      }
    }

    std::string get_connected_component_csv(){
      std::stringstream out ;
      out<< "Parent, Size \n";
      for ( auto i  =0;i<sizes.size();i++) {
        out<< i << ", "<< sizes[i]<<"\n";
      }
      return out.str();
    }

    void add_second_layer (){
      second_layer = 1;
      // Resize for the second layer
      sizes.resize(N*2+2);
      parents.resize(N*2+2);
      make_set_second();
      largest = -1;
      largest_size=1;
    }

    Algorithms(G_size nIn, double pIn) : RandomGraph(nIn, pIn) {
      sizes.resize(N+1);
      parents.resize(N+1);
      make_set();
      largest = -1;
      largest_size=1;
    }

    void reset (){
      make_set();
    }
  };
} // NetworkResilience


#endif //RESEARCH_ALGORITHMS_H
