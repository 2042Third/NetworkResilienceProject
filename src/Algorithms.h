//
// Created by Mike Yang on 11/29/2022.
//

#ifndef RESEARCH_ALGORITHMS_H
#define RESEARCH_ALGORITHMS_H
#include <vector>
#include "RandomGraph.h"

namespace NetworkResilience{
  class Algorithms :public RandomGraph{

  public:
    std::vector<G_size> sizes;
    std::vector<G_size> parents;
    G_size largest;
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
        sizes[n1] += n2;
      }
    }

    /**
     * Get the number of connected components.
     * */
    G_size connected_components_count(){
      std::unordered_set<G_size> tmp;
      for (auto i=0 ; i<N ;i++) tmp.insert(find_set(i));
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

    Algorithms(double nIn, double pIn) : RandomGraph(nIn, pIn) {
      sizes.resize(N+1);
      parents.resize(N+1);
      make_set();
      largest = 1;
    }

    void reset (){
      make_set();
    }
  };
}


#endif //RESEARCH_ALGORITHMS_H
