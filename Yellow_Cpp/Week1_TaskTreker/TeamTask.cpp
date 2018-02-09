#include "TeamTask.h"


const TasksInfo& TeamTasks::GetPersonTasksInfo(const std::string& person) const {
	return teamTasks.at(person);
}

void TeamTasks::AddNewTask(const std::string& person) {
	++teamTasks[person][TaskStatus::NEW];
}

TaskStatus TeamTasks::next(TaskStatus status) {
	return static_cast<TaskStatus>(static_cast<int>(status) + 1);
}

void TeamTasks::removeZero(TasksInfo& tasks, TaskStatus status) {
	if (tasks[status] <= 0) {
		tasks.erase(status);
	}
}

std::tuple<TasksInfo, TasksInfo> TeamTasks::PerformPersonTasks(const std::string& person, int task_count) {
	TasksInfo updated, untouched;
	if (teamTasks.count(person) == 0) return std::make_tuple(updated, untouched);
	// ������������� ������ ������������ �� ���� ��������, ����� DONE, �.�. �� �� ����� ���������
	// ������ ����������� � ������� �� ��������: NEW, IN PROGRESS, TESTING, DONE
	TasksInfo& personTasks = teamTasks.at(person);	
	for (auto iter = personTasks.begin(); iter != personTasks.end(); ++iter) {
		TaskStatus status = iter->first;
		int taskCountForStatus = iter->second;		
		if (status == TaskStatus::DONE) break;		
		// ��������� ����������  �� ����������� ������� � ������ updated
		int minTaskCount = std::min(taskCountForStatus, task_count);
		TaskStatus nextStatus = next(status);
		updated[nextStatus] = minTaskCount;
		removeZero(updated, nextStatus);
		// ��������� ���������� � ������ ������� � ������ untouched
		untouched[status] = taskCountForStatus - task_count;
		removeZero(untouched, status);
		// ��������� ���������� ���������� ��� ���������� ������
		task_count -= minTaskCount;
	}
	// ��������� ���������� � ������ ����� ������������ �� ������ �� ������� updated
	for (auto iter = updated.begin(); iter != updated.end(); ++iter) {
		TaskStatus status = iter->first;
		int count = iter->second;
		personTasks[status] += count;
		TaskStatus prevStatus = static_cast<TaskStatus>(static_cast<int>(status) - 1);
		personTasks[prevStatus] -= count;
		// ���� ����� ����� ����� ����� 0, �� ����� ������ ������ � ����� �������� �� ������� personTasks
		removeZero(personTasks, prevStatus);
	}
	return std::make_tuple(updated, untouched);
}