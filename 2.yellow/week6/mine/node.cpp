#include "node.h"

#include <algorithm>
#include <memory>

using namespace std;

template <typename T>
bool CompareTo(const T& lhs, const T& rhs, Comparison cmp) {
    switch (cmp) {
    case Comparison::Less:           return lhs <  rhs;
    case Comparison::LessOrEqual:    return lhs <= rhs;
    case Comparison::Equal:          return lhs == rhs;
    case Comparison::NotEqual:       return lhs != rhs;
    case Comparison::Greater:        return lhs >  rhs;
    case Comparison::GreaterOrEqual: return lhs >= rhs;
    }
    return false; // make compiler happy
}

EmptyNode::EmptyNode() {}

bool EmptyNode::Evaluate(const Date& date, const string& event) const {
    return true;
}

DateComparisonNode::DateComparisonNode(Comparison cmp, const Date& date) : m_cmp(cmp), m_date(date) {}

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const {
    return CompareTo(date, m_date, m_cmp);
}

EventComparisonNode::EventComparisonNode(Comparison cmp, const string& value) : m_cmp(cmp), m_event(value) {}

bool EventComparisonNode::Evaluate(const Date& date, const string& event) const {
    return CompareTo(event, m_event, m_cmp);
}

LogicalOperationNode::LogicalOperationNode(LogicalOperation op, shared_ptr<Node> left, shared_ptr<Node> right) : m_op(op), m_left(left), m_right(right) {}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
    switch (m_op) {
    case LogicalOperation::And: return m_left->Evaluate(date, event) && m_right->Evaluate(date, event);
    case LogicalOperation::Or:  return m_left->Evaluate(date, event) || m_right->Evaluate(date, event);
    default:
        return false;
    }
}

