#include <iostream>
#include <stack>
#include <vector>

using namespace std;

#define MAX 100

char* INPUT = new char[5]{'a', 'b', 'x', 'b', 'a'};
char* INPUT2 = new char[5]{'a', 'e', 'x', 'c', 'd'};
char* INPUT3 = new char[5]{'a', 'b', 'x', 'c', 'd'};

struct Node{
	char c;
	Node* pNext;
};

class LinkedList{
public:
	Node* pHead = NULL;

	Node* createNode(char c)
	{
		Node* node = new Node();
		node->c = c;
		node->pNext = NULL;

		return node;
	}

	void addNode(Node* node)
	{
		if (node == NULL){
			return;
		}
		if (pHead == NULL){
			pHead = node;
			return;
		}
		Node* p = pHead;
		while (p->pNext != NULL) {
			p = p->pNext;
		}

		p->pNext = node;
	}
	void addHead(Node* node)
	{
		if (node == NULL)
		{
			return;
		}
		if (pHead == NULL)
		{
			pHead = node;
			return;
		}
		node->pNext = pHead;
		pHead = node;
	}
	void printList()
	{
		Node* p = pHead;
		while (p != NULL)
		{
			cout << p->c << " ";
			p = p->pNext;
		}
	}
};

bool KiemTraDoiXung(LinkedList myList)
{
	Node* p = myList.pHead;
	if (p == NULL)
	{
		return false;
	}

	stack<Node*> myStack = stack<Node*>();
	bool isCheckX = false;

	while (p != NULL)
	{
		if (!isCheckX && p->c != 'x'){
			myStack.push(p);
		}
		else
		{
			if (!isCheckX && p->c == 'x')
			{
				isCheckX = true;
			}
			else
			{
				if (myStack.empty()){
					return false;
				}

				Node* top = myStack.top();
				myStack.pop();

				if (top->c != p->c)
				{
					return false;
				}
			}
		}

		p = p->pNext;
	}
	
	if (!myStack.empty())
	{
		return false;
	}
	
	return true;
}

bool KiemTraDoiXung_2(LinkedList myList)
{
	LinkedList list;
	Node* p = myList.pHead;
	while (p != NULL)
	{
		Node* node = list.createNode(p->c);
		list.addHead(node);

		p = p->pNext;
	}

	Node* p1 = myList.pHead;
	Node* p2 = list.pHead;
	
	while (p1 != NULL && p2 != NULL)
	{
		if (p1->c != p2->c)
		{
			return false;
		}
		if (p1->c == 'x' && p2->c == 'x')
		{
			return true;
		}

		p1 = p1->pNext;
		p2 = p2->pNext;
	}

	return false;
}

void _Cau1()
{
	LinkedList list;
	for (int i = 0; i < 5; i++)
	{
		char c = INPUT[i];
		Node* node = list.createNode(c);
		list.addNode(node);
	}

	list.printList();

	cout << endl;
	bool is = KiemTraDoiXung(list);
	cout << "Cach 1: " << is << endl;

	bool is2 = KiemTraDoiXung_2(list);
	cout << "Cach 2: " << is2 << endl;
	
}

int Elector[9] = {123, 456, 123, 456, 789, 123, 456, 234, 456};



void swap(int& a, int& b)
{
	int c(a); a = b; b = c;
}

int partition(int arr[], int low, int high)
{
	int pivot = arr[high];
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{
		if (arr[j] <= pivot)
		{
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);
	return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		int pi = partition(arr, low, high);

		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

int WinnerElector(int a[], int size)
{
	// Quicksort : O(n*log_2(n))
	quickSort(a, 0, size-1);
	int* Elector = new int[size];
	int* countElector = new int[size];
	for (int i = 0; i < size; i++)
	{
		countElector[i] = 0;
	}

	// O(n)
	int pos = 0;
	Elector[pos] = a[pos];
	countElector[pos] = 1;
	for (int i = 1; i < size; i++)
	{
		if (a[i] != Elector[pos])
		{
			pos++;
			Elector[pos] = a[i];
			countElector[pos]++;
		}
		else
		{
			countElector[pos]++;
		}
	}

	// O(n)
	int idx = 0;
	int maxCount = countElector[0];
	for (int i = 1; i < pos; i++)
	{
		if (countElector[i] > maxCount)
		{
			maxCount = countElector[i];
			idx = i;
		}
	}

	return Elector[idx];
	// O(n*log_2(n)) + O(n) + O(n) = O(n*log_2(n) < O(n^2)
}

struct Data{
	int key;
	int value;
};

void WinnerElector_2(int a[], int size)
{
	//// Quicksort : O(n*log_2(n))
	//int* Elector = new int[size];
	//int* countElector = new int[size];
	//for (int i = 0; i < size; i++)
	//{
	//	countElector[i] = 0;
	//}

	//// O(n)
	//int pos = 0;
	//Elector[pos] = a[pos];
	//countElector[pos] = 1;
	//for (int i = 1; i < size; i++)
	//{
	//	if (a[i] != Elector[pos])
	//	{
	//		pos++;
	//		Elector[pos] = a[i];
	//		countElector[pos]++;
	//	}
	//	else
	//	{
	//		countElector[pos]++;
	//	}
	//}

	//// O(n)
	//int idx = 0;
	//int maxCount = countElector[0];
	//for (int i = 1; i < pos; i++)
	//{
	//	if (countElector[i] > maxCount)
	//	{
	//		maxCount = countElector[i];
	//		idx = i;
	//	}
	//}

	//return Elector[idx];
	//// O(n*log_2(n)) + O(n) + O(n) = O(n*log_2(n) < O(n^2)
}
void _Cau2()
{
	cout << "Elector: " << endl;
	for (int i = 0; i < 9; i++)
	{
		cout << Elector[i] << " ";
	}
	int winner = WinnerElector(Elector, 9);
	cout << endl << "Sorted : " << endl;
	for (int i = 0; i < 9; i++)
	{
		cout << Elector[i] << " ";
	}
	cout << endl << "Winner : " ;
	cout << winner << endl;
}

void main()
{
	_Cau2();

}