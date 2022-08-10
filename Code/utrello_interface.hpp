#ifndef __INTERFACE_HPP__
#define __INTERFACE_HPP__

#include <string>
#include <vector>
using namespace std;

class User;
class List;
class Task;
class UTrelloInterface
{
public:
	UTrelloInterface();

	std::string addUser(std::string username);
	std::string addTask(std::string list, std::string name, unsigned int estimatedTime, unsigned int priority, std::string description);
	std::string editTask(std::string task, unsigned int estimatedTime, unsigned int priority, std::string description);
	std::string deleteTask(std::string task);
	std::string assignTask(std::string task, std::string user);
	std::string moveTask(std::string task, std::string list);
	std::string completeTask(std::string task);
	std::string printTask(std::string task);

	std::string addList(std::string name);
	std::string deleteList(std::string list);
	std::string printList(std::string list);

	std::string printUserTasks(std::string user);
	std::string printUserUnfinishedTasks(std::string user);

	int printTotalEstimatedTime();
	int printTotalRemainingTime();
    int printUserWorkload(std::string user);

	std::string printUsersByWorkload();
	std::string printUsersByPerformance();

    std::string printAllLists();
    std::string printUnassignedTasksByPriority();
	std::string printAllUnfinishedTasksByPriority();
	
	
private:
	std::vector<User*> users;
	std::vector<List*> lists;
	std::vector<Task*> tasks;
	std::vector<Task*> assigned_tasks;
	std::vector<Task*> remained_tasks;
};

#endif
