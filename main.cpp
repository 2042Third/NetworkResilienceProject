#include <iostream>
#include "src/Algorithms.h"
#include "src/output.h"

using net = NetworkResilience::Algorithms ;
using out = NetworkResilience::output;

void first_test(){
  std::string filename = "t/first_test.csv";
  int k =10;
  net *g = new net(5000, 0.00071);
//  net *g = new net(100, 0.71);
  g->run();
  uint32_t cc = g->connected_components_count();
  std::cout<<"Connected Components: "<<cc<<std::endl;
  g->printStats(*(g->getDD()));
  delete g;
}
void first_test_n(){

  int k =10;
  uint32_t N = 128000;
  double p = 0.0000625;
  net *g = new net(128000, 0.0000625); // p = 0.0000625, avg degree = 4
  std::string of = "../dataOut/out_"+ to_string(N)+"_"+ to_string(p)+".txt";
  g->o_file(of);
  g->run();
  uint32_t cc = g->connected_components_count();
  std::cout<<"Connected Components: "<<cc<<std::endl;
  g->printStats(*(g->getDD()));
  g->write_output( g->get_connected_component_csv());
  delete g;
}
void test_large(){
  std::string filename = "t/first_test.csv";
  int k =10;
  net *g = new net(1000000, 0.0000142);
  g->run();
  uint32_t cc = g->connected_components_count();
  std::cout<<"Connected Components: "<<cc<<std::endl;
  g->printStats(*(g->getDD()));
  delete g;
}

int main() {
  first_test_n();
//  test_large();
//  first_test();
  return 0;
}
