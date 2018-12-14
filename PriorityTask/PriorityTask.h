#ifndef PRIORITY_TASK_H
#define PRIORITY_TASK_H

struct Task
{
	enum TaskType {LAUNDRY, DISHES, MAKE_BED, VACUUM, MOP_FLOOR, ECE150};
	
	TaskType type;
	int taskID;
	int daysTillDue;
	char* description;
};

struct Node
{
	Task _data;
	Node* _next = 0;
};

class TaskQueue
{
	public:
		bool enqueue(const Task& t);
		Task* dequeue();
		const Task* peek() const;
		const Task* next(const Task::TaskType& t) const;
		bool remove(int t) const;
		bool isEmpty() const;
		
		TaskQueue();
		~TaskQueue();
		
	private:
		int _currentDay;
		static const int INITIAL_TASKQUEUE_SIZE = 10;
		Node* _front;
		Node* _back;
		int _numItems;
		int _queueSize;
		//Task* _tasks;
};

#endif