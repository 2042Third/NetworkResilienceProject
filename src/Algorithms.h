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
       while (g.count(n) && parents[n] != n){
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
      if (n1 != n2) {
        if (sizes[n1] < sizes[n2]) {
          std::swap(n1, n2);
        }
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
      for ( auto&o:g) {
        auto i= o.second.id ;
        tmp.insert(find_set(i));
      }
      std::cout<< "Largest Connected Component     : "<< largest<<std::endl;
      std::cout<< "Largest Connected Components    : "<< tmp.size()<<std::endl;
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
      G_size x = 0;
      for (auto& i:sizes){
        if(x<=N)sizes[x] = 1;
        else sizes[x] = 0;
        parents[x] = x;
        x++;
      }
      largest = -1;
      largest_size=1;
    }

    void rerun() {
      reset();
      static G_size a,b;
      for (auto & i:g){
        a = i.second.id;
        if(a > N){continue;}
        for (auto & f: i.second.links){
          if(g.count(f) ) {
            b = f;
            if (b > N) { continue; }
            union_sets(a,b);
          }
        }
      }
    }


    int remove_all_disconnected(){
      if (largest<0)
        connected_components_count();
      for (auto i=0;i<parents.size();i++){
        if (i<=N && parents[i] != largest) {
          if (g.count(i)) {
            Node &a = g.find(i)->second;
            std::cout<<a.id<<std::endl;
            unlink_all(a);
            g.erase(i);
          }
        }
      }
      return 1;
    }

    void unlink_all(Node & n){
      if(n.links.begin() == n.links.end()){
        return;
      }
      for (auto& i:n.links){
        auto a = g.find(i);
        a->second.unlink(n.id);
      }
    }

    int random_rm(){
      G_size n = gen->nextInt() % N;
      if (!g.count(n)){
        return 0;
      }
      Node& a = g.find(n)->second;
      unlink_all( a );
      g.erase(n);
      if (second_layer) {
        Node& b = g.find(n+N)->second;
        unlink_all( b );
        g.erase(n + N);
      }
      return 1;
    }
  };
} // NetworkResilience


#endif //RESEARCH_ALGORITHMS_H
