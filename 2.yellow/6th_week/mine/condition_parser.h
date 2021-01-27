#pragma once
#include <memory>
#include <iostream>
#include <string>

#include "node.h"

template <class It>
std::shared_ptr<Node> ParseComparison(It& current, It end);

template <class It>
std::shared_ptr<Node> ParseExpression(It& current, It end, unsigned precedence);

std::shared_ptr<Node> ParseCondition(std::istream& is);
std::string           ParseEvent(std::istream& is);
