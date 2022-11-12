#include <iostream>
#include "src/RandomGraph.h"

using net = NetworkResilience::RandomGraph ;

void first_test(){
  std::string filename = "t/first_test.csv";
  int k =10;
  net *g = new net(500, 0.1);
  g->run();
  g->printStats(*(g->getDD()));
  delete g;
}
void first_test_n(){
  std::string filename = "t/first_test.csv";
  int k =10;
  net *g = new net(5000, 0.1);
  g->run();
  g->printStats(*(g->getDD()));
  delete g;
}
void test_large(){
  std::string filename = "t/first_test.csv";
  int k =10;
  net *g = new net(100000, 0.001);
  g->run();
  g->printStats(*(g->getDD()));
  delete g;
}

int main() {
  test_large();
  return 0;
}
