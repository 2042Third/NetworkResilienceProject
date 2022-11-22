#include <iostream>
#include "src/RandomGraph.h"

using net = NetworkResilience::RandomGraph ;

void first_test(){
  std::string filename = "t/first_test.csv";
  int k =10;
  net *g = new net(500, 0.0071);
//  net *g = new net(100, 0.71);
  g->run();
  g->check_connected();
  g->printStats(*(g->getDD()));
  delete g;
}
void first_test_n(){
  std::string filename = "t/first_test.csv";
  int k =10;
  net *g = new net(128000, 0.0000625); // p = 0.0000625
                                  // avg degree = 4
  g->run();
  g->check_connected();
  g->printStats(*(g->getDD()));
  delete g;
}
void test_large(){
  std::string filename = "t/first_test.csv";
  int k =10;
  net *g = new net(1000000, 0.00005);
  g->run();
  g->check_connected();
  g->printStats(*(g->getDD()));
  delete g;
}

int main() {
//   first_test_n();
//    test_large();
  first_test();
  return 0;
}
