#pragma once

#include <iostream>
#include <tuple>
#include <map>
#include <string>
#include <algorithm>

// ������������ ��� ��� ������� ������
enum class TaskStatus {
	NEW,          // �����
	IN_PROGRESS,  // � ����������
	TESTING,      // �� ������������
	DONE          // ���������
};

// ��������� ���-������� ��� map<TaskStatus, int>,
// ������������ ������� ���������� ����� ������� �������
using TasksInfo = std::map<TaskStatus, int>;

class TeamTasks {
public:
	// �������� ���������� �� �������� ����� ����������� ������������
	const TasksInfo& GetPersonTasksInfo(const std::string& person) const;

	// �������� ����� ������ (� ������� NEW) ��� ����������� �������������
	void AddNewTask(const std::string& person);

	// �������� ������� �� ������� ���������� ����� ����������� ������������,
	// ����������� ��. ����
	std::tuple<TasksInfo, TasksInfo> PerformPersonTasks(
		const std::string& person, int task_count);

private:
	std::map<std::string, TasksInfo> teamTasks;
	
	// �������� ������ ��������� � ������ TaskStatus ������
	TaskStatus next(TaskStatus status);

	// ������� �� ������� ������ � ������, ���� ���-�� ����� �� �������������
	void removeZero(TasksInfo& tasks, TaskStatus status);
};


