#include "node.h"

bool EmptyNode::Evaluate(const Date& date, const string& event) const 
{ 
	return true; 
}

DateComparisonNode::DateComparisonNode(Comparison cmp, Date date) :
	m_cmp(cmp),
	m_date(date)
{}

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const
{
	switch (m_cmp) 
	{
		case Comparison::Less:
			return date < m_date;
		case Comparison::LessOrEqual:
			return date <= m_date;
		case Comparison::Greater:
			return date > m_date;
		case Comparison::GreaterOrEqual:
			return date >= m_date;
		case Comparison::Equal:
			return date == m_date;
		case Comparison::NotEqual:
			return date != m_date;
		default:
			throw logic_error("Invalid Comparison value");
	}
	return false;
}

EventComparisonNode::EventComparisonNode(Comparison cmp, const string& event_name) :
	m_cmp(cmp),
	m_event_name(event_name)
{}

bool EventComparisonNode::Evaluate(const Date& date, const string& event) const
{
	switch (m_cmp) 
	{
		case Comparison::Less:
			return event < m_event_name;
		case Comparison::LessOrEqual:
			return event <= m_event_name;
		case Comparison::Greater:
			return event > m_event_name;
		case Comparison::GreaterOrEqual:
			return event >= m_event_name;
		case Comparison::Equal:
			return event == m_event_name;
		case Comparison::NotEqual:
			return event != m_event_name;
		default:
			throw logic_error("Invalid Comparison value");
	}
	return false;
}

LogicalOperationNode::LogicalOperationNode(LogicalOperation op, shared_ptr<Node> left, shared_ptr<Node> right) :
	m_op(op),
	m_left(left),
	m_right(right)
{}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const
{
	switch (m_op)
	{
	case LogicalOperation::And:
		return m_left->Evaluate(date, event) && m_right->Evaluate(date, event);
	case LogicalOperation::Or:
		return m_left->Evaluate(date, event) || m_right->Evaluate(date, event);
	default:
		throw logic_error("Invalid LogicalOperation value");
	}
}
