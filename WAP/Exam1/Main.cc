#include<iostream>

using namespace std;

struct Pos {
        int r;
        int c;
};

struct State {
public:
	Pos c;
	Pos p;
	long long score;
};

struct Node {
	State state;
	struct Node *next;
};

class LinkedList {
private:
	// Method to create a new node
	Node * createNode(State);
public:
	// Method for inserting a new node
	Node * insertNode(State, Node *);
};

// Methods for the above class
Node * LinkedList :: createNode(State data) {
	// Allocate memory to new node
	struct Node *temp;
	temp = new(struct Node);
	// Check if memory is allocated
	if (temp == NULL) {
		cout<<"Memory not allocated "<<endl;
		return 0;
	} else {
		// Initialize the node with values
		temp->state = data;
		temp->next = NULL;     
		return temp;
	}
}

Node * LinkedList :: insertNode(State data, Node * p) {
	// Create the node
	Node * temp = this->createNode(data);

	// Adjust the pointers in the linked list
	temp->next = p;
	
	// return the new top
	return temp;
}

// class defining the stack rules
class Queue{
private:
	Node * front = NULL;
	Node * rear = NULL;
public:
        // Method to enqueue
        void enqueue(State);

        // Method to dequeue
        State dequeue();

	// Method to check if queue is empty
	bool empty();
};

// Methods of above mentioned class
void Queue :: enqueue(State state) {
	LinkedList l;
	if(this->empty()) {
		rear = l.insertNode(state, NULL);
		front = rear;
	} else {
		rear->next = l.insertNode(state, NULL);
		rear = rear->next;
	}
}

State Queue :: dequeue() {
	// Adjust the pointers
	Node * temp;
	temp = front;
	front = temp->next;
	if(front == NULL) rear = NULL;
	return temp->state;
}

bool Queue :: empty() {
	if(front == NULL)
		return (true);
	else
		return (false);
}

class Game {
private:
	// Array to store the game board
	long ** b;
	int rowNum;
	int colNum;
public:
	long long score = 0;

	// Init constructor
	Game(int, int);

	// Method update element of board
	void updateElement(int, int, long);

	// Defining all possible moves of the game
	State moveUp(State);
	State moveDown(State);
	State moveRight(State);

	// Method to findout the max achieveable score
	long long highScore();
};

// Methods for the above class
Game :: Game(int r, int c) {
	b = new long *[r];
	for(int i=0; i<r; i++)
		b[i] = new long [c];
	rowNum = r;
	colNum = c;
}

void Game :: updateElement(int r, int c, long v) {
	b[r][c] = v;
}

State Game :: moveUp(State s) {
	State o;
	if(s.c.r > 0 && b[s.c.r-1][s.c.c] != -1) {
		o.c.r = s.c.r - 1;
		o.c.c = s.c.c;
		o.score = s.score + b[o.c.r][o.c.c];
	}
	else if(s.c.r == 0 && b[rowNum-1][s.c.c] != -1) {
		o.c.r = rowNum - 1;
		o.c.c = s.c.c;
		o.score = b[o.c.r][o.c.c];
	}
	else
		o.score = -1;
	if(o.c.r == s.p.r && o.c.c == s.p.c)
		o.score = -1;
	o.p.r = s.c.r;
	o.p.c = s.c.c;
	return o;
}

State Game :: moveRight(State s) {
	State o;
	if(s.c.c < colNum-1 && b[s.c.r][s.c.c+1] != -1) {
		o.c.r = s.c.r;
		o.c.c = s.c.c + 1;
		o.score = s.score + b[o.c.r][o.c.c];
	} else
		o.score = -1;
	if(o.c.r == s.c.r && o.c.c == s.c.c)
		o.score = -1;
	o.p.r = s.c.r;
	o.p.c = s.c.c;
	return o;
}

State Game :: moveDown(State s) {
	State o;
	if(s.c.r < rowNum-1 && b[s.c.r+1][s.c.c] > -1) {
		o.c.r = s.c.r + 1;
		o.c.c = s.c.c;
		o.score = s.score + b[o.c.r][o.c.c];
	} else if(s.c.r == rowNum-1 && b[0][s.c.c] > -1) {
		o.c.r = 0;
		o.c.c = s.c.c;
		o.score = b[o.c.r][o.c.c];
	} else
		o.score = -1;
	if(o.c.r == s.p.r && o.c.c == s.p.c)
		o.score = -1;
	o.p.r = s.c.r;
	o.p.c = s.c.c;
	return o;
}

long long Game :: highScore() {
	long long score = -1;
	// Loop for each starting point in left most column
	for (int k=0; k<rowNum; k++) {
		// Initialize the curr state
		State curr;
		curr.c.c = 0;
		curr.p.r = curr.p.c = -1;
		if(b[k][curr.c.c] > -1) {
			curr.c.r = k;
			curr.score = b[curr.c.r][curr.c.c];

		        // Initialize a temporary board to keep track of score and visit
		        long long s[rowNum][colNum];
		        for(int i=0; i<rowNum; i++)
	        	        for(int j=0; j<colNum; j++)
	                	        s[i][j] = -1;
			s[curr.c.r][curr.c.c] = b[curr.c.r][curr.c.c];

			// Apply BFS to traverse each node on the board
			Queue q;

			// Enqueue the current position on the stack
			q.enqueue(curr);

			// Loop until the queue is not empty
			while(!q.empty()) {
				// Extract an element from queue
				curr = q.dequeue();
				if(s[curr.c.r][curr.c.c] == curr.score) {
					// Move in all directions
					State temp;
					temp = this->moveUp(curr);
					if(s[temp.c.r][temp.c.c] < temp.score) {
						s[temp.c.r][temp.c.c] = temp.score;
						q.enqueue(temp);
					}
					temp = this->moveDown(curr);
					if(s[temp.c.r][temp.c.c] < temp.score) {
						s[temp.c.r][temp.c.c] = temp.score;
						q.enqueue(temp);
					}
					temp = this->moveRight(curr);
					if(s[temp.c.r][temp.c.c] < temp.score) {
						s[temp.c.r][temp.c.c] = temp.score;
						q.enqueue(temp);
					}
				}
			}

			// Find the best score
			int j = colNum-1;
			long long tScore = s[0][j];
			for(int i=1; i<rowNum; i++) {
				if(tScore < s[i][j])
					tScore = s[i][j];
			}
			// Update the master score
			if(score < tScore)
				score = tScore;
		}
	}
	// Return the highest score
	return score;
}


// Main function for execution of the program
int main() {
	// Input for nodes and queries
	int r, c;
	cin>>r>>c;

	Game g = Game(r, c);

	// Game board construction
	for(int i=0; i<r ; i++) {
		for(int j=0; j<c; j++) {
			long temp;
			cin>>temp;
			g.updateElement(i, j, temp);
		}
	}

	// Output the highest score
	cout<<g.highScore()<<endl;

	return 0;
}
