#pragma once

/* ��� ����� ������ ��������� ���������� � ����������� ������ Node, 
� ����� ���� ��� �������� (��. ����), 
������� ������������ ����� ���� ������������ ��������������� ������, 
������������ �������� ParseCondition;*/

/* � ������� Database � Node ������� � ������� ������ �� ���������, ������� ������������ � ������� main.*/

enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};

enum class LogicalOperation {
	Or,
	And
};

class Node {
public:
	virtual void Evaluate(const Date& date, const std::string& event) = 0;
};

class EmptyNode : public Node {
public:
	void Evaluate(const Date& date, const std::string& event) override {};
};

class DateComparisonNode : public Node {
public:
	DateComparisonNode(Comparison cmp, Date date);
};

class EventComparisonNode : public Node {
public:
	EventComparisonNode(Comparison cmp, std::string event_name);
};

class LogicalOperationNode : public Node {
public:
	LogicalOperationNode(LogicalOperation op, shared_ptr<Node> left, shared_ptr<Node> right);

private:
	shared_ptr<Node> m_left;
	shared_ptr<Node> m_right;
};