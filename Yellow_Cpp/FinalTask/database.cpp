#include "database.h"
#include <algorithm>
#include <sstream>
#include <iterator>

using namespace std;

void Database::Add(const Date& date, const string& event)
{
	auto& field = m_db[date];
	unordered_set<string>& events_names = field.first;
	map<unsigned, string>& events = field.second;
	bool has_event = (events_names.find(event) != events_names.end());
	unsigned order = 0;
	if (!events.empty())
		order = events.rbegin()->first + 1;
	if (events.empty() || !has_event)
	{
		events.emplace(order, event);
		events_names.insert(event);
	}
}

void Database::Print(ostream & os) const
{
	for (const auto& field : m_db)
	{
		const map<unsigned, string>& events = field.second.second;
		for (const auto& event : events)
			os << field.first << ' ' << event.second<< endl;
	}
}

int Database::RemoveIf(function<bool(const Date&, const string&)> condition)
{
	int removed_count = 0;

	for (auto m_db_it = m_db.begin(); m_db_it != m_db.end(); )
	{
		map<unsigned, string>& events = m_db_it->second.second;
		for (auto event_it = events.begin(); event_it != events.end(); )
		{
			if (condition(m_db_it->first, event_it->second))
			{
				m_db_it->second.first.erase(event_it->second);
				event_it = events.erase(event_it);
				++removed_count;
			} else
				++event_it;
		}

		// remove date with empty events list
		if (m_db_it->second.second.empty())
			m_db_it = m_db.erase(m_db_it);
		else
			++m_db_it;
	}

	return removed_count;
}

vector<string> Database::FindIf(function<bool(const Date&, const string&)> condition) const
{
	vector<string> found;
	for (auto& field : m_db)
	{
		const map<unsigned, string>& events = field.second.second;
		for (const auto& event : events)
			if (condition(field.first, event.second))
			{
				stringstream ss;
				ss << field.first << ' ' << event.second;
				found.push_back(ss.str());
			}
	}
	return found;
}

string Database::Last(const Date& date)
{
	auto it = m_db.upper_bound(date);
	if (m_db.begin() == it)
		throw invalid_argument("Date was not found");
	--it;
	
	stringstream ss;
	ss << it->first << ' ' << it->second.second.rbegin()->second;
	return ss.str();
}