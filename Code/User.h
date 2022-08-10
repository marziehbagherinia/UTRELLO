#ifndef USER_H_
#define USER_H_

#include <vector>
#include <string>

using namespace std;

class Task;

class User
{
public:
    User(string _user_id);

    string get_user_id();
    string print_User_Tasks();
    string print_unfinished_Tasks();

    void assign_task(Task* new_task);
    void done_task(string task);
    void delete_task(Task* new_task);
    
    int totalEstimatedTime();
    int totalReamainingTime();
    int userWorked();
    int userPerformance();

    vector<Task*> existance_task();
    vector<Task*> remaining_task();

private:
    string user_id;
    vector<Task*> assigning_task;
    vector<Task*> remained_task;
    vector<Task*> done_tasks;
};

#endif