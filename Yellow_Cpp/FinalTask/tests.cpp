#include "condition_parser.h"
#include "test_runner.h"
#include "tests.h"
#include "database.h"
#include <ctime>

#include <sstream>
using namespace std;

extern std::string ParseEvent(std::istream& is);

void TestAll() {
	TestRunner tr;
	tr.RunTest(TestParseEvent, "TestParseEvent");
	tr.RunTest(TestParseCondition, "TestParseCondition");
	tr.RunTest(TestTime, "TestTime");
}

void TestTime() {
	Database db;

	{
		std::clock_t start;
		double duration;
		start = std::clock();
		for (int i = 1; i < 10000; ++i)
		{
			Date date(i%1000, 1, 1);
			db.Add(date, "some event");
		}
		duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
		std::cerr << "printf: " << duration << '\n';
	}
	/*{
		std::clock_t start;
		double duration;
		start = std::clock();
		for (int i = 1; i < 10000; ++i)
		{
			std::ostringstream ss;
			db.Print(std::cout);
		}
		duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
		std::cout << "printf: " << duration << '\n';
	}*/
	{
		std::clock_t start;
		double duration;
		start = std::clock();
		for (int i = 1; i < 10000; ++i)
		{
			Date date(i % 1000, 1, 1);
			db.Last(date);
		}
		duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
		std::cerr << "printf: " << duration << '\n';
	}
	
}

void TestParseEvent() {
	{
		istringstream is("event");
		AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
	}
	{
		istringstream is("   sport event ");
		AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
	}
	{
		istringstream is("  first event  \n  second event");
		vector<string> events;
		events.push_back(ParseEvent(is));
		events.push_back(ParseEvent(is));
		AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
	}
}

void TestParseCondition() {
	{
		istringstream is("date != 2017-11-18");
		shared_ptr<Node> root = ParseCondition(is);
		Assert(root->Evaluate({ 2017, 1, 1 }, ""), "Parse condition 1");
		Assert(!root->Evaluate({ 2017, 11, 18 }, ""), "Parse condition 2");
	}
	{
		istringstream is(R"(event == "sport event")");
		shared_ptr<Node> root = ParseCondition(is);
		Assert(root->Evaluate({ 2017, 1, 1 }, "sport event"), "Parse condition 3");
		Assert(!root->Evaluate({ 2017, 1, 1 }, "holiday"), "Parse condition 4");
	}
	{
		istringstream is("date >= 2017-01-01 AND date < 2017-07-01");
		shared_ptr<Node> root = ParseCondition(is);
		Assert(root->Evaluate({ 2017, 1, 1 }, ""), "Parse condition 5");
		Assert(root->Evaluate({ 2017, 3, 1 }, ""), "Parse condition 6");
		Assert(root->Evaluate({ 2017, 6, 30 }, ""), "Parse condition 7");
		Assert(!root->Evaluate({ 2017, 7, 1 }, ""), "Parse condition 8");
		Assert(!root->Evaluate({ 2016, 12, 31 }, ""), "Parse condition 9");
	}
	{
		istringstream is(R"(event != "sport event" AND event != "Wednesday")");
		shared_ptr<Node> root = ParseCondition(is);
		Assert(root->Evaluate({ 2017, 1, 1 }, "holiday"), "Parse condition 10");
		Assert(!root->Evaluate({ 2017, 1, 1 }, "sport event"), "Parse condition 11");
		Assert(!root->Evaluate({ 2017, 1, 1 }, "Wednesday"), "Parse condition 12");
	}
	{
		istringstream is(R"(event == "holiday AND date == 2017-11-18")");
		shared_ptr<Node> root = ParseCondition(is);
		Assert(!root->Evaluate({ 2017, 11, 18 }, "holiday"), "Parse condition 13");
		Assert(!root->Evaluate({ 2017, 11, 18 }, "work day"), "Parse condition 14");
		Assert(root->Evaluate({ 1, 1, 1 }, "holiday AND date == 2017-11-18"), "Parse condition 15");
	}
	{
		istringstream is(R"(((event == "holiday" AND date == 2017-01-01)))");
		shared_ptr<Node> root = ParseCondition(is);
		Assert(root->Evaluate({ 2017, 1, 1 }, "holiday"), "Parse condition 16");
		Assert(!root->Evaluate({ 2017, 1, 2 }, "holiday"), "Parse condition 17");
	}
	{
		istringstream is(R"(date > 2017-01-01 AND (event == "holiday" OR date < 2017-07-01))");
		shared_ptr<Node> root = ParseCondition(is);
		Assert(!root->Evaluate({ 2016, 1, 1 }, "holiday"), "Parse condition 18");
		Assert(root->Evaluate({ 2017, 1, 2 }, "holiday"), "Parse condition 19");
		Assert(root->Evaluate({ 2017, 1, 2 }, "workday"), "Parse condition 20");
		Assert(!root->Evaluate({ 2018, 1, 2 }, "workday"), "Parse condition 21");
	}
	{
		istringstream is(R"(date > 2017-01-01 AND event == "holiday" OR date < 2017-07-01)");
		shared_ptr<Node> root = ParseCondition(is);
		Assert(root->Evaluate({ 2016, 1, 1 }, "event"), "Parse condition 22");
		Assert(root->Evaluate({ 2017, 1, 2 }, "holiday"), "Parse condition 23");
		Assert(root->Evaluate({ 2017, 1, 2 }, "workday"), "Parse condition 24");
		Assert(!root->Evaluate({ 2018, 1, 2 }, "workday"), "Parse condition 25");
	}
	{
		istringstream is(R"(((date == 2017-01-01 AND event == "holiday")))");
		shared_ptr<Node> root = ParseCondition(is);
		Assert(root->Evaluate({ 2017, 1, 1 }, "holiday"), "Parse condition 26");
		Assert(!root->Evaluate({ 2017, 1, 2 }, "holiday"), "Parse condition 27");
	}
	{
		istringstream is(R"(((event == "2017-01-01" OR date > 2016-01-01)))");
		shared_ptr<Node> root = ParseCondition(is);
		Assert(root->Evaluate({ 1, 1, 1 }, "2017-01-01"), "Parse condition 28");
		Assert(!root->Evaluate({ 2016, 1, 1 }, "event"), "Parse condition 29");
		Assert(root->Evaluate({ 2016, 1, 2 }, "event"), "Parse condition 30");
	}
}
