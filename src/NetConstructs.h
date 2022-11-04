//
// Created by 18604 on 11/4/2022.
//

#ifndef RESEARCH_NETCONSTRUCTS_H
#define RESEARCH_NETCONSTRUCTS_H

#include <string>
#include <set>
#include <vector>
#include <map>
#include "Node.h"

namespace NetworkResilience {


/**
 * Graph types.
 * */
  typedef std::set<NODE_ID> ConnectedComp;
  typedef std::vector<ConnectedComp> ConnectedComps;
  typedef std::map<int, int> DegreeDistro;
  typedef std::map<NODE_ID, NetworkResilience::Node> GraphRep;


} // NetworkResilience
#endif //RESEARCH_NETCONSTRUCTS_H
