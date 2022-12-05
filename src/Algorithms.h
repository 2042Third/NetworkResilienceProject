//
// Created by Mike Yang on 11/29/2022.
//

#ifndef RESEARCH_ALGORITHMS_H
#define RESEARCH_ALGORITHMS_H
#include <vector>
#include <sstream>
#include "RandomGraph.h"
#include <iterator>
#include <filesystem>
namespace fs = std::filesystem;
namespace NetworkResilience{
  class Algorithms :public RandomGraph{

  public:
    std::vector<G_size> sizes;
    std::vector<G_size> parents;
    std::vector<G_size> unlinker;
    G_size largest, largest_size;
#ifdef DEBUG_NET

    std::ofstream dfile;
#endif
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
      while (g.find(n) != g.end() && parents[n] != n){
        parents[n] = parents[parents[n]];
        n = parents[n];
      }
      return n;
    }
    /**
     *  Find the parent of the input node.
     *  Not referencing the second layer of the graph.
     * */
    G_size find_set_second(G_size n){
      while (g.find(n) != g.end() && parents[n] != n && parents[n]<=N){
        parents[n] = parents[parents[n]];
        n = parents[n];
      }
      return n;
    }

    /**
     * Merge two connected components together.
     * */
    void union_sets(G_size n1, G_size n2, int ref_2nd=0){
      n1 = ref_2nd? find_set_second(n1):find_set(n1);
      n2 = ref_2nd? find_set_second(n2):find_set(n2);
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
        if(second_layer && o.second.id>=N)
          continue;
        auto i= o.second.id ;
        tmp.insert(find_set(i));
      }
      std::cout<< "Largest Connected Component     : "<< largest<<std::endl;
      std::cout<< "Largest Connected Components    : "<< tmp.size()<<std::endl;
      std::cout<< "Largest Connected Component size: "<< largest_size<<std::endl;
      std::cout<< "pn/p, fraction of nodes in largest: "<< largest_size/N<<std::endl;
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
        union_sets(a,b,1);
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
#ifdef DEBUG_NET
      dfile.open(fs::current_path().string()+"/debug_file.txt",	 ios::out);
      if (dfile.is_open())
        std::cout<<"debug file made "<<fs::current_path().string()+"/debug_file.txt"<<std::endl;
      else
        std::cout<<"debug file failed "<<fs::current_path()/fs::path("debug_file.txt")<<std::endl;
#endif
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

    void remove_fraction(double& f){

#ifdef DEBUG_NET
      dfile<<"FRACTIONAL REMOVAL:  "<<N*f<<"\n";
#endif
      G_size n = N*f, count = 0;
      while(count<n){
        random_rm();
        count++;
      }
      std::cout<<"Fraction of nodes removed: "<< count<<std::endl;
    }

    void rerun() {
      reset();
      static G_size a,b;
      for (auto & i:g){
        a = i.second.id;
        if(a >= N){continue;}
        for (auto & f: i.second.links){
          if(g.find(f) != g.end()) {
            b = f;
            if (b >= N) { continue; }
            union_sets(a,b,second_layer);
          }
        }
      }
    }


    int remove_all_disconnected(){
      if (largest<0)
        connected_components_count();
      for (auto i=0;i<parents.size();i++){
        if (i<N && parents[i] != largest) { // first layer removal
          if (g.find(i) != g.end()) {
            Node &a = g.find(i)->second;
            std::cout<<"<<<Disconnected removed>>> "<<a.id<<std::endl;
            unlink_all(a.id);
            g.erase(i);
          }
        }

      }
      return 1;
    }

    void unlink_all(G_size input){
      Node& n = g.find(input)->second;
      if(n.links.begin() == n.links.end())return;
      if(unlinker.capacity()<=n.links.size())
        unlinker.resize(n.links.size()+1);
      unlinker.clear();
      for (auto i:n.links){
        auto a = g.find(i);
        if(a!=g.end())
          unlinker.push_back( a->second.id );
#ifdef DEBUG_NET
        dfile<<" "<<unlinker[unlinker.size()-1];
#endif
      }
#ifdef DEBUG_NET
      dfile<<"\n";
      dfile.flush();
#endif
      for (auto i:unlinker) {
#ifdef DEBUG_NET
      dfile<<"\t unlinking "<<n.id
      <<" from "<<i<<"\n";
      dfile.flush();
#endif
        g.find(i)->second.unlink(n.id);
//        std::cout<<"Removed(unlink_all) removed "<<n.id<<" from "<<i->id<<std::endl;
      }
    }

    int random_rm(){
      G_size n = gen->nextInt() % N;
      auto itr = g.begin();
      Node& a = itr->second;
      Node &b = a;
      if (g.find(n)==g.end()){

#ifdef DEBUG_NET
      dfile<<"Original selection: "<<n<<"\n";
      dfile.flush();
#endif
        G_size c = 0;
        while (c!=n%g.size()) {
          itr++;
          if(itr==g.end()) {
#ifdef DEBUG_NET
      dfile<<"FAIL: NO MORE NODES"<<"\n";
      dfile.flush();
#endif
            return 0;
          }
          if(itr->second.id<N){ c++; }
        }
        a = itr->second;

#ifdef DEBUG_NET
        dfile<<"next selection: "<<a.id<<", "<<a.id+N<<"\n";
      dfile.flush();
#endif
      } else {

        a= g.find(n)->second;
#ifdef DEBUG_NET
        dfile<<"Exists: "<<a.id<<"\n\n";
      dfile.flush();
#endif
      }
#ifdef DEBUG_NET
      dfile<<"\tRemoving (first layer) "<<a.id<<", link count"<<a.link_count<<"\n";
      dfile.flush();
#endif
//      std::cout<<"Removing (first layer) "<<n<<std::endl;

      if (second_layer) {
#ifdef DEBUG_NET
        dfile<<"\tFinding: "<< a.id+N<<"\n";
      dfile.flush();
#endif
        b = g.find(a.id + N)->second;
#ifdef DEBUG_NET
        dfile<<"\tRemoving (second layer) "<<b.id<<", link count"<<b.link_count<<"\n";
      dfile.flush();
#endif
//        std::cout<<"Removing (second layer) "<<n + N<<std::endl;

      }
      if(a.link_count>0) {unlink_all(a.id);}
      if(second_layer) {
        if(b.link_count>0) {unlink_all(b.id);}
        g.erase(b.id);
      }
      g.erase(itr);
      return 1;
    }
  };
} // NetworkResilience


#endif //RESEARCH_ALGORITHMS_H
