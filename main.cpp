#include <iostream>
#include "src/Algorithms.h"

using net = NetworkResilience::Algorithms ;

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
  std::string filename = "t/first_test.csv";
  int k =10;
  net *g = new net(128000, 0.0000625); // p = 0.0000625
                                  // avg degree = 4
  g->run();
  uint32_t cc = g->connected_components_count();
  std::cout<<"Connected Components: "<<cc<<std::endl;
  g->printStats(*(g->getDD()));
  delete g;
}
void test_large(){
  std::string filename = "t/first_test.csv";
  int k =10;
  net *g = new net(1000000, 0.0000082);
  g->run();
  uint32_t cc = g->connected_components_count();
  std::cout<<"Connected Components: "<<cc<<std::endl;
  g->printStats(*(g->getDD()));
  delete g;
}

int main() {
//  first_test_n();
  test_large();
//  first_test();
  return 0;
}
