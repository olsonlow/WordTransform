/*
Jon Martin

functions for the storage allocation version of class JCSQue.
*/

#include "JCSQue.h"

JCSQue::JCSQue()
{    
	MAX_ITEMS = 40001;
	front = MAX_ITEMS -1;
	rear = MAX_ITEMS -1;
	items = new QUENODE[MAX_ITEMS];		
}


JCSQue::JCSQue(int n)
{    
	MAX_ITEMS = n+1;
	front = MAX_ITEMS -1;
	rear = MAX_ITEMS -1;
	items = new QUENODE[MAX_ITEMS];	
}


JCSQue::JCSQue(const JCSQue& anotherQue)
{
	int i;
	if (this == &anotherQue) return;

    if (anotherQue.items == NULL) items = NULL;
	else 
	{
		MAX_ITEMS = anotherQue.MAX_ITEMS;
        front = anotherQue.front;
        rear = anotherQue.rear;
    	
		items = new QUENODE[MAX_ITEMS];
		if (rear >= front)
        {
			for (i = front+1;i <= rear;i++)
  			  items[i] = anotherQue.items[i];
		} 
		else 
		{
			for (i = 0;i <= rear;i++)
  			  items[i] = anotherQue.items[i];
			for ( i = front+1;i <= MAX_ITEMS;i++)
  			  items[i] = anotherQue.items[i];
		}
	}
}

JCSQue::~JCSQue()
{    
	delete [] items;
}

void JCSQue::MakeEmpty()
{
    front = MAX_ITEMS - 1;
	rear = MAX_ITEMS - 1;
}

bool JCSQue::IsEmpty() const
{
    return (rear == front);
}

void JCSQue::operator =(const JCSQue& originalQue)
{
	int i;
	if (this == &originalQue) return;

    if (originalQue.items == NULL) items = NULL;
	else 
	{
		MAX_ITEMS = originalQue.MAX_ITEMS;
        front = originalQue.front;
        rear = originalQue.rear;        
	
		items = new QUENODE[MAX_ITEMS];
		if (rear >= front)
        {
			for (i = front+1;i <= rear;i++)
  			  items[i] = originalQue.items[i];
		} else 
		{
			for (i = 0;i <= rear;i++)
  			  items[i] = originalQue.items[i];
			for (i = front+1;i <= MAX_ITEMS;i++)
  			  items[i] = originalQue.items[i];
		}
	}		
}

bool JCSQue::IsFull() const
{
    return ((rear + 1) % MAX_ITEMS == front);
}


void JCSQue::enqueue(QUENODE a)
{
	rear = (rear + 1) % MAX_ITEMS;
	items[rear] = a;
}

void JCSQue::dequeue(QUENODE& a)
{
	front = (front + 1) % MAX_ITEMS;
	a = items[front];
}

