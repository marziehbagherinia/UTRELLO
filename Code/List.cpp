#include "List.h"
#include "Task.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define Done "Success";
#define R_task "‫‪‫‪Task ‫‪already‬‬ ‫‪exists‬‬";
#define No_task "Task does not exist";

List::List(string _list_id)
:list_id(_list_id)
{
}

string List::add_task(Task* new_task)
{
    tasks.push_back(new_task);
    remaining_tasks.push_back(new_task);
    int n = tasks.size();
    for (int i = 0; i < n-1; ++i)
    {
    	if (new_task->get_task_id()== tasks[i]->get_task_id())
    	{
			tasks.pop_back();
            remaining_tasks.pop_back();
            return R_task;
    	}
    }
    if (tasks.size() == n)
		return Done;
}

vector<Task*> List::get_tasks()
{
    return tasks;
}

bool List::existance_tasks(string task)
{
    int temp = 0;
    for (int i = 0; i < tasks.size(); ++i)
    {
        if (task == tasks[i]->get_task_id())
        {
            return true;
        }
        else 
            temp++;
    }
    if (temp == tasks.size())
        return false;
}

vector<string> List::get_task_id()
{
    vector<string> id;
    for (int i = 0; i < tasks.size(); ++i)
    {
        id.push_back(tasks[i]->get_task_id());   
    }
    return id;
}

string List::get_list_id()
{
    return list_id;
}

void List::set_list_id(string _list_id)
{
    list_id = _list_id;
}

void List::delete_task(string task)
{
    for (int i = 0; i < tasks.size(); ++i)
    {
        if (task == tasks[i]->get_task_id())
        {
            tasks.erase(tasks.begin()+i);
            break;
        }
    }
}

string List::complete_task(string task)
{
    int temp = 0;
    for (int i = 0; i < remaining_tasks.size(); ++i)
    {
        if (task == remaining_tasks[i]->get_task_id())
        {
            completed_tasks.push_back(remaining_tasks[i]);
            remaining_tasks.erase(remaining_tasks.begin()+i);
            return Done;
        }
        else
            temp++;

    }
    if (temp == remaining_tasks.size())
        return No_task;
}

int List::remaining_task_time()
{
    int temp = 0;
    for (int i = 0; i < remaining_tasks.size(); ++i)
    {
        temp = temp + remaining_tasks[i]->get_estimated_Time();
    }

    return temp;
}

string List::bargardon()
{
    string user_id ;
    string output = "List " + list_id + "\n";
    for (int i = 0; i < tasks.size(); ++i)
    {
        
        if (tasks[i]->get_user_id() == "")
        {
            output = output + output = output + to_string(tasks[i]->get_priority()) +
                        " | " + tasks[i]->get_task_id() + 
                        " | " + "Unassigned" +
                        " | " + to_string(tasks[i]->get_estimated_Time()) + "h" + "\n";
        }

        else
        {
            output = output + to_string(tasks[i]->get_priority()) +
                        " | " + tasks[i]->get_task_id() + 
                        " | " + tasks[i]->get_user_id() +
                        " | " + to_string(tasks[i]->get_estimated_Time()) + "h" + "\n";
        }
        
    }
    return output;
}