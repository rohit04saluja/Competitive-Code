#include<iostream>

using namespace std;

struct Node {
	long data;
	struct Node *next;
};

class LinkedList {
private:
	// Method to create a new node
	Node * createNode(long);
public:
	// Method for inserting a new node
	Node * insertNode(long, Node *);
};

// Methods for the above class
Node * LinkedList :: createNode(long v) {
	// Allocate memory to new node
	struct Node *temp;
	temp = new(struct Node);
	// Check if memory is allocated
	if (temp == NULL) {
		cout<<"Memory not allocated "<<endl;
		return 0;
	} else {
		// Initialize the node with values
		temp->data = v;
		temp->next = NULL;     
		return temp;
	}
}

Node * LinkedList :: insertNode(long v, Node * p) {
	// Create the node
	Node * temp = this->createNode(v);

	// Adjust the pointers in the linked list
	temp->next = p;
	
	// return the new top
	return temp;
}

// class defining the stack rules
class Stack{
public:
        // Variable to point to top of stack
        Node * top = NULL;

        // Method to push
        void push(long);

        // Method to pop
        long pop();
};

// Methods of above mentioned class
void Stack :: push(long v) {
        // Create a new node
        LinkedList l;
        top = l.insertNode(v, top);
}

long Stack :: pop() {
        if(top == NULL)
                return -1;
        else {
                Node * temp = top;
                top = temp->next;
                return temp->data;
        }
}

class Graph {
private:
	// Array to store a graph in dictionary form
	Node ** g;
	long size;

public:
	// Array to store the distances from the festive city
	long * d;

	// Prototype of the  constructor function
	Graph(long);

	// Method to add edge
	void addEdge(long, long);

	// Method to update the festCity
	void updateFestCity(long);

	// Method to assign a value to all elements in array till a limit
	void assignAll(long, long);

	// Method to ge the distance of given city from festive city
	long distance(long);

	// Method to initialize the distances before queries
	void initQ();
};

// Methods for the above class
Graph :: Graph(long size) {
	g = new Node * [size];
	d = new long [size];
	for(long i=0; i<size; i++) {
		g[i] = NULL;
	}
	this->size = size;
}

void Graph :: addEdge(long s, long d) {
	// Insert in the current linked list at both the places
	LinkedList l = LinkedList();
	this->g[s] = l.insertNode(d, this->g[s]);
	this->g[d] = l.insertNode(s, this->g[d]);
}

void Graph :: updateFestCity(long r) {
	// Prepare variables for the graph traversal
	long visit[this->size];
	Stack s;
	s.push(r);
	this->d[r] = 0;
	visit[r] = 1;
	// Loop over the stack until its empty similar to DFS
	while(s.top != NULL) {
		long i = s.pop();
		Node * t = this->g[i];
		// Examine all the neighbours of the node
		for(; t != NULL ; t=t->next) {
			// Check if the node gets and update and its not visited
			if(visit[t->data] != 0 && this->d[t->data]>this->d[i]+1) {
				s.push(t->data);
				visit[t->data] = 0;
				this->d[t->data] = this->d[i] + 1;
			}
		}
	}
}

long Graph :: distance(long n) {
	return this->d[n];
}

void Graph :: initQ() {
	for(long i=0 ; i<this->size ; i++) {
		this->d[i] = this->size;
	}
}


// Main function for execution of the program
int main() {
	// Input for nodes and queries
	long n, m;
	scanf("%ld %ld", &n, &m);

	Graph g = Graph(n);

	// Graph construction
	for(long i=1; i<n ; i++) {
		long temp1, temp2;
		cin>>temp1>>temp2;
//		scanf("%ld %ld", &temp1, &temp2);
		temp1--;
		temp2--;
		g.addEdge(temp1, temp2);
	}

	// Initialize the festive city
	g.initQ();
	g.updateFestCity(0);
	long out[m];

	for(long i=0 ; i<m ; i++)
		out[i] = -1;

	// Loop for each query by the user
	for(long i=0 ; i<m ; i++) {
		int temp1; long temp2;
		scanf("%d %ld", &temp1, &temp2);
		temp2--;
		if(temp1 == 1)
			g.updateFestCity(temp2);
		else
			out[i] = g.distance(temp2);
	}

	// Output all the queries
	for(long i=0 ; i<m ; i++)
		if(out[i]>-1)
			cout<<out[i]<<"\n";

	return 0;
}
