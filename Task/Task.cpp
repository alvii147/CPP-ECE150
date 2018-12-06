#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "Task.h"

using namespace std;

TaskQueue::TaskQueue()
{
	_tasks = new (std::nothrow) Task[INITIAL_TASKQUEUE_SIZE];
	_queueSize = INITIAL_TASKQUEUE_SIZE;
	_numItems = 0;
	_front = 0;
	_back = -1;
}

TaskQueue::~TaskQueue()
{
	delete[] _tasks;
	_queueSize = 0;
	_numItems = 0;
	_front = 0;
	_back = 0;
}

bool TaskQueue::enqueue(const Task& t)
{
	if(isFull())
	{
		return 0;
	}
	_back = (_back + 1)%_queueSize;
	_tasks[_back] = t;
	_numItems++;
	return 1;
}

Task* TaskQueue::dequeue()
{
	if(isEmpty())
	{
		return 0;
	}
	_front = (_front + 1)%_queueSize;
	_numItems--;
	return _tasks;
}

const Task* TaskQueue::peek() const
{
	return _tasks + _front;
}

const Task* TaskQueue::next(const Task::TaskType& t) const
{
	for(int i = _front; i<_numItems; i++)
	{
		if(_tasks[i].type == t)
		{
			return _tasks + i;
		}
	}
	return 0;
}

bool TaskQueue::isFull() const
{
	int rc = 0;
	if(_numItems == _queueSize)
	{
		rc = 1;
	}
	return rc;
}

bool TaskQueue::isEmpty() const
{
	int rc = 0;
	if(_numItems == 0)
	{
		rc = 1;
	}
	return rc;
}

bool TaskQueue::quarterFull() const
{
	int rc = 0;
	float size = _numItems/_queueSize;
	if(size<=0.25)
	{
		rc = 1;
	}
	return rc;
}

bool TaskQueue::doubleQueueSize()
{	
	Task* x;
	x = new(std::nothrow) Task[_queueSize];
	if(x == 0)
	{
		return 0;
	}
	for(int i = _front; i<_queueSize; i++)
	{
		x[i] = _tasks[i];
	}
	
	delete[] _tasks;
	_tasks = new (std::nothrow) Task[_queueSize*2];
	if(_tasks == 0)
	{
		delete[] x;
		return 0;
	}
	
	for(int i = _front; i<_queueSize; i++)
	{
		_tasks[i] = x[i];
	}
	
	_queueSize *= 2;
	delete[] x;
	return 1;
}

bool TaskQueue::halveQueueSize()
{
	int div = (_queueSize/2);
	if(_numItems>div)
	{
		return 0;
	}
	else
	{
		_queueSize = _queueSize/2;
		_back = _queueSize;
	}
	return 1;
}

#ifndef MARMOSET_TESTING

int main()
{
	
}

#endif