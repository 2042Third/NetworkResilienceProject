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
    std::vector<int> removal;
    std::vector<G_size> unlinker;
//    G_size largest;
#ifdef DEBUG_NET

    std::ofstream dfile;
#endif
    /**
     * Make each node its own parent.
     * */
    void make_set() {
      for (auto i=0; i<= N;i++){
        parents[i] = i;
        removal[i] = 0;
        sizes[i] = 1;
      }
    }
    /**
     * Make each node its own parent.
     * */
    void make_set_second() {
      for (auto i=0; i<= N*2+1;i++){
        parents[i] = i;
        removal[i] = 0;
        sizes[i] = 1;
      }
    }

    /**
     *  Find the parent of the input node.
     * */
    G_size find_set(G_size n){
      while (!removal[n] && parents[n] != n){
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
      while (!removal[n] && parents[n] != n && parents[n]<=N){
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
      }
    }

    /**
     * Get the number of connected components.
     * */
    G_size connected_components_count(){
      std::unordered_set<G_size> tmp;
      G_size num_e = 0;
      for ( auto o=0 ;o<N;o++) {
        if(removal[o])
          continue;
        tmp.insert(find_set(o));
        num_e ++;
      }
      G_size largest = find_largest();
      std::cout<< "Largest Connected Component     : "<< largest<<std::endl;
      std::cout<< "Largest Connected Components    : "<< tmp.size()<<std::endl;
      std::cout<< "Largest Connected Component size: "<< sizes[largest]<<std::endl;
      std::cout<< "Existing size: "<< num_e<<std::endl;
      std::cout<< "Removed : "<< num_removal()<<std::endl;
      std::cout<< "pn, fraction of nodes in largest: "<< (double)(sizes[largest]/N)<<std::endl;
      return tmp.size();
    }


    G_size num_removal () {
      G_size a = 0;
      for (auto i:removal){
        if(i)a++;
      }
      return a;
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
      removal.resize(N*2+2);
      make_set_second();
    }

    Algorithms(G_size nIn, double pIn) : RandomGraph(nIn, pIn) {
      sizes.resize(N+1);
      parents.resize(N+1);
      removal.resize(N+1);
      make_set();
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
        sizes[x] = 1;
        parents[x] = x;
        x++;
      }
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
        if(removal[a]){continue;} // not in first layer or removed, then continue
        for (auto & f: i.second.links){ // all links of the node
          b = f;
          if(a<N&b<N&!removal[b]){ // both are from the first layer
            union_sets(a,b,second_layer); // connect the two (both first layer)
          }
          else if (a>=N&b>=N&!removal[b]){ // both are from the second layer
            union_sets(a,b,second_layer); // connect the two (both first layer)
          }
        }
      }
    }


    int remove_all_disconnected(int second=0){
      G_size largest = find_largest(second);

      G_size a=second?N:0,  max_size=second?2*N:N;
      for (;a<parents.size();a++){
        if (a<max_size && parents[a] != largest) { // first layer removal
          if (!removal[a]) {
            Node &nd = g.find(a)->second;
            unlink_all(nd.id);
            removal[a] = 1;
            sizes[parents[a]]--;
          }
        }
      }
      return 1;
    }

    void unlink_all(G_size input){
      Node& n = g.find(input)->second;
      if(removal[n.id])return;
      if(unlinker.capacity()<=n.links.size())
        unlinker.resize(n.links.size()+1);
      unlinker.clear();
      for (auto i:n.links){
        auto a = g.find(i);
        unlinker.push_back( a->second.id );
      }
      for (auto i:unlinker) {
        g.find(i)->second.unlink(n.id);
      }
    }

    G_size find_largest(int second=0){
      G_size a=second?N:0, i=second?N:0, max_size=second?2*N:N;
      while (i<max_size){
        if(sizes[i]>sizes[a])
          a=i;
        i++;
      }
      return a;
    }

    int random_rm(){
      G_size n = gen->nextInt() % N;
      Node& a = g.begin()->second;
      Node &b = a;
      if (removal[n]) { // if removed, find another one
        G_size c = 0;
        while (c < N) {c++;if (!removal[(c+n)%N]) {break;}}
        n=(c+n)%N;
      }
      a= g.find(n)->second; // get the first layer selected node
      unlink_all(a.id); // remove all links to the first selected node
      removal[a.id] = 1; // mark the first node removed
      sizes[parents[a.id]]--; // decrease the size of it's connected comp
      if (second_layer ) { // if has a second layer
        b = g.find(a.id + N)->second; // get the second layer selected node
        unlink_all(b.id); // remove all links to this node
        removal[b.id] = 1; // mark the node removed
        sizes[parents[b.id]]--; // decrease the size of it's connected comp.
      }
      return 1;
    }

    double average_degree () {
      double k = 1;
      G_size degrees=0,num=0;
      for ( auto i  =0;i<N;i++) {
        if(!removal[i]){
          degrees+=g.find(i)->second.link_size();
          num++;
        }
      }
      k = (double)degrees/(double)num;
      return k;
    }
    double degree_prob () {
      double k = 1;
      G_size degrees=0,num=0;
      for ( auto i  =0;i<N;i++) {
        if(!removal[i]){
          degrees+=g.find(i)->second.link_size();
          num++;
        }
      }
      k = (double)degrees/(double)(N*(N-1)/2);
      return k;
    }

    void auto_run(double p){

      std::ofstream output;
      output.open(fs::current_path().string()+"/dout/out"+to_string(p)+"N"+to_string(N)+".csv",	 ios::out);
      output<< "gcc_size, pn/p, pc,p, avg_degree \n";
      G_size largest=0;
      connected_components_count();
      int idx =0;
      largest = find_largest(0);
      while (sizes[largest]>10 ){ // run until largest is less than 10 nodes
        remove_fraction(p);
        rerun();
        connected_components_count();
        remove_all_disconnected(0);
        remove_all_disconnected(1);

        largest = find_largest(0);
        output<< sizes[largest]<<", "<<((double)sizes[largest]/(double)N)/(2.4554/average_degree ())
            <<", "<<(degree_prob())<<", "<<(average_degree ())<<", "<<(average_degree ())<<"\n";
        idx++;
        std::cout<<"Iteration: "<<idx<<std::endl;
      }
      output.close();
    }

  };
} // NetworkResilience


#endif //RESEARCH_ALGORITHMS_H
