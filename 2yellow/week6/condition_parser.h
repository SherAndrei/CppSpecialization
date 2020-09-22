#pragma once
#include "node.h"

#include <memory>
#include <iostream>

using namespace std;

template <class It>
shared_ptr<Node> ParseComparison(It& current, It end);

template <class It>
shared_ptr<Node> ParseExpression(It& current, It end, unsigned precedence);

shared_ptr<Node> ParseCondition(istream& is);
string           ParseEvent(istream& is);