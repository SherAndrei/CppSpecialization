#pragma once
#include <string>
#include <vector>
#include <memory>
#include "date.h"

using namespace std;

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation {
    Or = 1,
    And
};

class Node {
 public:
    virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

class EmptyNode : public Node {
 public:
    EmptyNode();
    bool Evaluate(const Date& date, const string& event) const override;
};

class DateComparisonNode : public Node {
 public:
    DateComparisonNode(Comparison cmp, const Date& date);
    bool Evaluate(const Date& date, const string& event) const override;
 private:
    const Comparison m_cmp;
    const Date       m_date;
};

class EventComparisonNode : public Node {
 public:
    EventComparisonNode(Comparison cmp, const string& value);
    bool Evaluate(const Date& date, const string& event) const override;
 private:
    const Comparison m_cmp;
    const string     m_event;
};

class LogicalOperationNode : public Node {
 public:
    LogicalOperationNode(LogicalOperation op, shared_ptr<Node> left, shared_ptr<Node> right);
    bool Evaluate(const Date& date, const string& event) const override;
 private:
    const LogicalOperation m_op;
    const shared_ptr<Node> m_left;
    const shared_ptr<Node> m_right;
};
