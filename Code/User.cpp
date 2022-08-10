#include "User.h"
#include "Task.h"
#include "List.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

User::User(string _user_id)
: user_id(_user_id)
{
}

string User::get_user_id()
{
    return user_id;
}

void User::assign_task(Task* new_task)
{
    assigning_task.push_back(new_task);
    remained_task.push_back(new_task);
}

void User::delete_task(Task* new_task)
{
	for (int i = 0; i < assigning_task.size(); ++i)
	{
		if (new_task->get_task_id() == assigning_task[i]->get_task_id())
		{
			assigning_task.erase(assigning_task.begin() + i);
			break;
		}
	}
	for (int i = 0; i < remained_task.size(); ++i)
	{
		if (new_task->get_task_id() == remained_task[i]->get_task_id())
		{
			remained_task.erase(remained_task.begin() + i);
			break;
		}
	}
}

vector<Task*> User::existance_task()
{
	return assigning_task;
}

void User::done_task(string task)
{
	for (int i = 0; i < remained_task.size(); ++i)
	{
		if (task == remained_task[i]->get_task_id())
		{
			done_tasks.push_back(remained_task[i]);
			remained_task.erase(remained_task.begin() + i);
		}
	}
}

vector<Task*> User::remaining_task()
{
	return remained_task;
}

int User::totalEstimatedTime()
{
	int temp = 0;
	for (int i = 0; i < assigning_task.size(); ++i)
	{
		temp = temp + assigning_task[i]->get_estimated_Time();
	}
	return temp;
}

int User::totalReamainingTime()
{
	int temp = 0;
	for (int i = 0; i < remained_task.size(); ++i)
	{
		temp = temp + remained_task[i]->get_estimated_Time();
	}
	return temp;
}

int User::userWorked()
{
	int total = 0;
	for (int i = 0; i < assigning_task.size(); ++i)
	{
		total = total + assigning_task[i]->get_estimated_Time();
	}
	return total;
}

int User::userPerformance()
{
	int total = 0;
	for (int i = 0; i < done_tasks.size(); ++i)
	{
		total = total + done_tasks[i]->get_estimated_Time();
	}
	return total;
}

string User::print_User_Tasks()
{
	string output = "";
	for (int i = 0; i < assigning_task.size(); ++i)
	{
		output = output + to_string(assigning_task[i]->get_priority()) + " | " +
			     assigning_task[i]->get_task_id() + " | " + 
				 user_id + " | " +
				 to_string(assigning_task[i]->get_estimated_Time()) + "h" + "\n";
	}
	return output;
}

string User::print_unfinished_Tasks()
{
	string output = "";
	for (int i = 0; i < remained_task.size(); ++i)
	{
		output = output + to_string(remained_task[i]->get_priority()) + " | " +
			     remained_task[i]->get_task_id() + " | " + 
				 user_id + " | " +
				 to_string(remained_task[i]->get_estimated_Time()) + "h" + "\n";
	}
	if (output == "")
	{
		return "NO more unfinished task!";
	}
	else
		return output;

}