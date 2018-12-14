#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "PriorityTask.h"

using namespace std;

TaskQueue::TaskQueue()
{
	//_tasks = new (std::nothrow) Task[INITIAL_TASKQUEUE_SIZE];
	_currentDay = 0;
	_numItems = 0;
	_queueSize = INITIAL_TASKQUEUE_SIZE;
	_front = NULL;
	_back = NULL;
}

TaskQueue::~TaskQueue()
{
	//delete[] _tasks;
	_currentDay = 0;
	_currentDay = 0;
	_numItems = 0;
	_queueSize = 0;
	_front = NULL;
	_back = NULL;
}

bool TaskQueue::enqueue(const Task& t)
{
	if(_currentDay>t.daysTillDue)
	{
		return 0;
	}
	Node* tmp = new Node;
	int days = t.daysTillDue;
	tmp->_data = t;
	if(_front == NULL)
	{
		tmp->_next = NULL;
		_front = tmp;
		_back = tmp;
	}
	else
	{
		Node* iterator1 = _front;
		int deadline1 = iterator1->_data.daysTillDue;
		if(days<=deadline1)
		{
			tmp->_next = iterator1;
			_front = tmp;
		}
		else
		{
			Node* iterator2 = _front->_next;
			int deadline2 = iterator2->_data.daysTillDue;
			int cond = 0;
			while(iterator2 != NULL)
			{
				if(deadline1<days && days<=deadline2)
				{
					tmp->_next = iterator2;
					iterator1->_next = tmp;
					cond = 1;
				}
				iterator1 = iterator1->_next;
				iterator2 = iterator2->_next;
				deadline1 = iterator1->_data.daysTillDue;
				deadline2 = iterator2->_data.daysTillDue;
			}
			if(cond == 0)
			{
				_back->_next = tmp;
				_back = tmp;
			}
		}
	}
	_numItems++;
	return 1;
}

Task* TaskQueue::dequeue()
{
	Node* tmp = _front;
	_front = _front->_next;
	_currentDay = tmp->_data.daysTillDue;
	tmp->_data.daysTillDue = 0;
	_numItems++;
	return &tmp->_data;
}

const Task* TaskQueue::peek() const
{
	return &_front->_data;
}

const Task* TaskQueue::next(const Task::TaskType& t) const
{
	Node* tmp = _front;
	int i = 1;
	while(i<=_numItems)
	{
		if(tmp->_data.type == t)
		{
			return &tmp->_data;
		}
		tmp = _front->_next;
	}
	return &tmp->_data;
}

bool TaskQueue::remove(int t) const
{
	Node* tmp = _front;
	int i = 1;
	while(i<t || i<=_numItems)
	{
		tmp = _front->_next;
		i++;
	}
	return &tmp->_data;
}

bool TaskQueue::isEmpty() const
{
	if(_numItems == 0)
	{
		return 1;
	}
	return 0;
}

#ifndef MARMOSET_TESTING

int main()
{
	
}

#endif