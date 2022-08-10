#include "utrello_interface.hpp"
#include "User.h"
#include "List.h"
#include "Task.h"

#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <string>

using namespace std;

#define Done "Success";
#define R_user "‫‪‫‪User ‫‪already‬‬ ‫‪exists‬‬";
#define No_user "User does not exist";
#define R_list "‫‪‫‪List‬‬ ‫‪already‬‬ ‫‪exists‬‬";
#define No_list "List does not exist";
#define R_task "‫‪‫‪Task ‫‪already‬‬ ‫‪exists‬‬";
#define No_task "Task does not exist";
#define Unassigned "Unassigned";

UTrelloInterface::UTrelloInterface()
{
}

std::string UTrelloInterface::addUser(string username)
{
	User* new_user = new User(username);
	users.push_back(new_user);
	int n=users.size();
	for (int i = 0; i < n-1; ++i)
	{
		if (new_user->get_user_id() == users[i]->get_user_id())
		{
			
			users.pop_back();
			return R_user;
			break;
		}
	}
	
	if (users.size() == n)
		return Done;
}

std::string UTrelloInterface::addList(string name)
{
	List* new_list = new List(name);
	lists.push_back(new_list);
	int n=lists.size();
	for (int i = 0; i < n-1; ++i)
	{
		if (new_list->get_list_id() == lists[i]-> get_list_id())
		{
			
			lists.pop_back();
			return R_list;
			break;
		}
	}
	
	if (lists.size() == n)
		return Done;

}

std::string UTrelloInterface::addTask(string list, string name, unsigned int estimatedTime, unsigned int priority, string description)
{
	int temp = 0;
	for (int i = 0; i < lists.size(); ++i)
	{
		if (list == lists[i]-> get_list_id())
		{
			Task* new_task = new Task(lists[i], name, estimatedTime, priority, description);
			tasks.push_back(new_task);
			remained_tasks.push_back(new_task);
			return lists[i]->add_task(new_task);
		}

		else
			temp++;
	}

	if (temp == lists.size())
		return No_list;
}

std::string UTrelloInterface::deleteList(std::string list)
{
	int temp=0;
	vector<Task*> v;
	for (int i = 0; i < lists.size(); ++i)
	{
		if (list == lists[i]-> get_list_id())
		{
			v = lists[i]->get_tasks();
			lists.erase(lists.begin() + i);
	
			for (int j = 0; j < tasks.size(); ++j)
			{
				for (int k = 0; k < v.size(); ++k)
				{
					if (tasks[j]->get_task_id() == v[k]->get_task_id())
					{
						tasks.erase(tasks.begin() + j);
						remained_tasks.erase(remained_tasks.begin() + j);
						for (int l = 0; l < users.size(); ++l)
						{
							if (tasks[j]->get_user_id() == users[l]->get_user_id())
							{
								users[l]->delete_task(tasks[j]);
								break;
							}
						}
					}
				}
			}
			return Done;
		}
		else
		{
			temp++;
		}
		v.clear();
	}

	if (temp == lists.size())
		return No_list;
}

std::string UTrelloInterface::deleteTask(std::string task)
{
	int temp = 0;
	for (int i = 0; i < tasks.size(); ++i)
	{
		if (task == tasks[i]->get_task_id())
		{
			tasks.erase(tasks.begin()+i);
			for (int j = 0; j < remained_tasks.size(); ++j)
			{
				remained_tasks.erase(remained_tasks.begin()+j);
				for (int k = 0; k < users.size(); ++k)
				{
					if (tasks[i]->get_user_id() == users[k]->get_user_id())
					{
						users[k]->delete_task(tasks[i]);
						break;
					}
				}
				break;
			}
		}
	}

	for (int i = 0; i < lists.size(); ++i)
	{
		if (lists[i]->existance_tasks(task))
		{
			lists[i]->delete_task(task);
			return Done;
		}
		else
			temp++;
	}

	if (temp == lists.size())
		return No_task;
}

std::string UTrelloInterface::assignTask(string task,string user)
{
	int temp = 0, count = 0;
	for (int i = 0; i < users.size(); ++i)
	{
		if (user == users[i]->get_user_id())
		{
			for (int j = 0; j < tasks.size(); ++j)
			{
				if(task == tasks[j]->get_task_id())
				{
					users[i]->assign_task(tasks[j]);
					tasks[j]->set_user_id(user);
					assigned_tasks.push_back(tasks[j]);
					
					for (int k = 0; k < remained_tasks.size(); ++k)
					{
						if (task == remained_tasks[k]->get_task_id())
						{
							remained_tasks.erase(remained_tasks.begin()+k);
							break;
						}
					}
					return Done;
				}
				else
					temp++;
			}
			if (temp == tasks.size())
				return No_task;
		}
		else
			count++;
	}
	if (count == users.size())
		return No_user;
}

std::string UTrelloInterface::editTask(string task, unsigned int estimatedTime, unsigned int priority, string description)
{
	int temp = 0, count = 0;
	for (int i = 0; i < tasks.size(); ++i)
	{
		if (task == tasks[i]->get_task_id())
		{
			for (int j = 0; j < lists.size(); ++j)
			{
				if (tasks[i]->get_list_id() == lists[j]->get_list_id())
				{
					Task* new_task = new Task(lists[j], task, estimatedTime, priority, description);
					lists[j]->delete_task(task);
					lists[j]->add_task(new_task);

					for (int k = 0; k < tasks.size(); ++k)
					{
						if (new_task->get_task_id() == tasks[i]->get_task_id())
						{
							tasks[i] = new_task;
							return Done;
						}
					}
					break;
				}
				else
					count++;
			}
			if (count == lists.size())
				return No_list;
		}
		else
			temp++;
	}

	if (temp == tasks.size())
		return No_task;
}

std::string UTrelloInterface::moveTask(string task, string list)
{
	int temp = 0, count = 0;
	for (int j = 0; j < tasks.size(); ++j)
	{
		if (task == tasks[j]->get_task_id())
		{
			for (int i = 0; i < lists.size(); ++i)
			{
				if (tasks[j]->get_list_id() == lists[i]->get_list_id())
				{
					lists[i]->delete_task(tasks[j]->get_task_id());
					break;
				}
			}

			for (int k = 0; k < lists.size(); ++k)
			{
				if (list == lists[k]->get_list_id())
				{
					return lists[k]->add_task(tasks[j]);
				}
				else
					temp++;
			}
		}
		else 
			count++;
	}

	
	if (temp == lists.size())
	{	
		return No_list;
	}
	else if (count == tasks.size())
	{
		return No_task;
	}
}

std::string UTrelloInterface::completeTask(string task)
{
	int temp = 0;
	for (int i = 0; i < tasks.size(); ++i)
	{
		if (task == tasks[i]->get_task_id())
		{
			string list_id = tasks[i]->get_list_id();
			for (int j = 0; j < lists.size(); ++j)
			{
				if (list_id == lists[j]->get_list_id())
				{
					for (int k = 0; k < users.size(); ++k)
					{
						if (tasks[i]->get_user_id() == users[k]->get_user_id())
						{
							users[k]->done_task(task);
							break;
						}
					}
					return lists[j]->complete_task(task);
				}
			}
		}
		else
			temp++;
	}
	if (temp == tasks.size())
	{
		return No_task;
	}
}

int UTrelloInterface::printTotalEstimatedTime()
{
	int temp = 0;
	for (int i = 0; i < users.size(); ++i)
	{
		temp = temp + users[i]->totalEstimatedTime();
	}
	return temp;
}

int UTrelloInterface::printTotalRemainingTime()
{
	int temp = 0;
	for (int i = 0; i < users.size(); ++i)
	{
		temp = temp + users[i]->totalReamainingTime();
	}
	return temp;
}

int UTrelloInterface::printUserWorkload(std::string user)
{
	int temp = 0, user_worked;
	for (int i = 0; i < users.size(); ++i)
	{
		if (user == users[i]->get_user_id())
		{
			user_worked = users[i]->totalEstimatedTime();
			return user_worked;
		}
		else
			temp++;
	}
	if (temp == users.size())
		return 0;
}

std::string UTrelloInterface::printTask(std::string task)
{
	int temp = 0, count = 0;
	for (int i = 0; i < tasks.size(); ++i)
	{
		if (task == tasks[i]->get_task_id())
		{
			for (int j = 0; j < assigned_tasks.size(); ++j)
			{
				if (task == assigned_tasks[j]->get_task_id())
				{
					return tasks[i]->get_task_id() + "\n" +
						   tasks[i]->get_description() + "\n" +
						   "Priority: " + to_string(tasks[i]->get_priority()) + "\n" +
						   "Estimated Time: " + to_string(tasks[i]->get_estimated_Time()) + "\n" +
						   "Assigned to " + tasks[i]->get_user_id() + "\n";
				}
				else 
					temp++;
			}
			if (temp == assigned_tasks.size())
			{
				return tasks[i]->get_task_id() + "\n" + tasks[i]->get_description() + "\n" +
					   "Priority: " + to_string(tasks[i]->get_priority()) + "\n" +
					   "Estimated Time: " + to_string(tasks[i]->get_estimated_Time()) + "\n" +
					   "Unassigned" + "\n";
			}
		}
		else
			count++;
	}
	if (count == tasks.size())
		return No_task;
}

std::string UTrelloInterface::printList(std::string list)
{
	int temp = 0;
	string output = "";
	for (int i = 0; i < lists.size(); ++i)
	{
		if (list == lists[i]->get_list_id())
		{
			return lists[i]->bargardon();
		}
		else
		{
			temp++;
		}
	}
	if (temp == lists.size())
	{
		return No_list;
	}
	else 
		return to_string(lists.size()) + to_string(temp);
}

std::string UTrelloInterface::printAllLists()
{
	string output = "";
	for (int i = 0; i < lists.size(); ++i)
	{
		output = output + lists[i]->bargardon();
	}
	return output;
}

std::string UTrelloInterface::printUserTasks(std::string user)
{
	int temp = 0;
	for (int i = 0; i < users.size(); ++i)
	{
		if (user == users[i]->get_user_id())
		{
			return users[i]->print_User_Tasks();
		}
		else temp++;
	}

	if (temp == users.size())
		return No_user;					
}

std::string UTrelloInterface::printUserUnfinishedTasks(std::string user)
{
	string output = "";
	int count = 0;
	for (int i = 0; i < users.size(); ++i)
	{
		if (user == users[i]->get_user_id())
		{
			return users[i]->print_unfinished_Tasks();
		}
		else count++;
	}
	if (count == users.size())
		return No_user;	
}

std::string UTrelloInterface::printUnassignedTasksByPriority()
{
	string output = "";
	for (int i = 0; i < remained_tasks.size(); ++i)
	{
		for (int j = 0; j < remained_tasks.size()-i-1; ++j)
		{
			if (remained_tasks[j]->get_priority() > remained_tasks[j+1]->get_priority())
				swap(remained_tasks[j], remained_tasks[j+1]);
		}
	}

	for (int i = 0; i < remained_tasks.size(); ++i)
	{
		output = output + to_string(remained_tasks[i]->get_priority()) + " | " + 
			   remained_tasks[i]->get_task_id() + " | " +
		       Unassigned + " | " +
			   to_string(remained_tasks[i]->get_estimated_Time()) + "h" + "\n";
	}

	return output;
}

std::string UTrelloInterface::printAllUnfinishedTasksByPriority()
{
	vector<Task*> unfinished_task;
	string output = "";
	for (int i = 0; i < users.size(); ++i)
	{
		std::vector<Task*> v = users[i]->remaining_task();
		for (int j = 0; j < v.size(); ++j)
		{
			unfinished_task.push_back(v[j]);
		}
		v.clear();
	}
	for (int i = 0; i < unfinished_task.size(); ++i)
	{
		for (int j = 0; j < unfinished_task.size()-i-1; ++j)
		{
			if (unfinished_task[j]->get_priority() > unfinished_task[j+1]->get_priority())
				swap(unfinished_task[j], unfinished_task[j+1]);
		}
	}
	for (int i = 0; i < unfinished_task.size(); ++i)
	{
		output = output + to_string(unfinished_task[i]->get_priority()) + " | " + 
			     unfinished_task[i]->get_task_id() + " | " +
		         unfinished_task[i]->get_user_id() + " | " +
			     to_string(unfinished_task[i]->get_estimated_Time()) + "h" + "\n";
	}
	return output;
}

std::string UTrelloInterface::printUsersByWorkload()
{
	string finalusers = "";
	for (int i = 0; i < users.size(); ++i)
	{
		for (int j = 0; j < users.size()-i-1; ++j)
		{
			if (users[j]->userWorked() > users[j+1]->userWorked())
				swap(users[j], users[j+1]);
		}
	}

	for (int i = 0; i < users.size(); ++i)
	{
		finalusers = finalusers + users[i]->get_user_id() + "\n";
	}
	return finalusers;
}

std::string UTrelloInterface::printUsersByPerformance()
{
	string finalusers = "";
	for (int i = 0; i < users.size(); ++i)
	{
		for (int j = 0; j < users.size()-i-1; ++j)
		{
			if (users[j]->userPerformance() < users[j+1]->userPerformance())
				swap(users[j], users[j+1]);
		}
	}
	for (int i = 0; i < users.size(); ++i)
	{
		finalusers = finalusers + users[i]->get_user_id() + "\n";
	}
	return finalusers;
}