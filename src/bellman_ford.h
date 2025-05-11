#pragma once
#include "graph.h"

template <typename GraphType>
class BellmanFord {
public:
    vector<int> run(const GraphType& graph, int source);
};