//
// Created by 18604 on 11/4/2022.
//

#ifndef RESEARCH_NETCONSTRUCTS_H
#define RESEARCH_NETCONSTRUCTS_H

#include <string>
#include <set>
#include <vector>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include "Node.h"

namespace NetworkResilience {


/**
 * Graph types.
 * */
  typedef uint32_t G_size;
  typedef std::unordered_set<NODE_ID> ConnectedComp;
  typedef std::vector<ConnectedComp*> ConnectedComps;
  typedef std::unordered_map<G_size, G_size> DegreeDistro;
  typedef std::unordered_map<NODE_ID, NetworkResilience::Node> GraphRep;


} // NetworkResilience
#endif //RESEARCH_NETCONSTRUCTS_H
