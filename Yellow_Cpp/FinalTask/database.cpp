#include "database.h"
#include <algorithm>
#include <sstream>
#include <iterator>

using namespace std;

void Database::Add(const Date& date, const string& event)
{
	vector<string>& events_list = m_db[date];
	if (events_list.empty() || (find(events_list.begin(), events_list.end(), event) == events_list.end()))
		    m_db[date].push_back(event);
}

void Database::Print(ostream & os) const
{
	for (const auto& field : m_db)
		for (const string& event : field.second)
			os << field.first << ' ' << event << endl;
}

int Database::RemoveIf(function<bool(const Date&, const string&)> condition)
{
	int removed_count = 0;

	for (auto m_db_it = m_db.begin(); m_db_it != m_db.end(); )
	{
		vector<string>& events = m_db_it->second;
		auto it = remove_if(events.begin(), events.end(), [&] (const string& event) {
			return condition(m_db_it->first, event);
		});
		removed_count += distance(it, events.end());
		if (it != events.end())
			events.erase(it, events.end());
		// remove date with empty events list
		if (m_db_it->second.empty())
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
		for (const auto& event : field.second)
			if (condition(field.first, event))
			{
				stringstream ss;
				ss << field.first << ' ' << event;
				found.push_back(ss.str());
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
	ss << it->first << ' ' <<it->second.back();
	return ss.str();
}