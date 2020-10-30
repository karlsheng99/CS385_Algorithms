/*******************************************************************************
 * Name    : waterjugpuzzle.cpp
 * Author  : Zikang Sheng & Keye Li
 * Version : 1.0
 * Date    : Oct 19, 2020
 * Description : Solving the water jug puzzle using breadth-first search.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <queue>
#include <string>
#include <cmath>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    string directions;
    State *parent;



    State(int _a, int _b, int _c, string _directions) :
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }

    State(int _a, int _b, int _c, string _directions, State *_parent) :
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{_parent} { }

    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << " (" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }

};


void display(State s) {
	if (s.a == -1) {
		cout << s.directions << endl;
		return;
	}
	if (s.parent != nullptr) {
		display(*s.parent);
	}
	cout << s.directions << s.to_string() << endl;
}


State bfs(int cap_a, int cap_b, int cap_c, int goal_a, int goal_b, int goal_c){
    int a = 0, b = 0, c = cap_c;
    queue<State> states;
    states.push(State(a, b, c, "Initial state."));

    State ***visited = new State **[cap_a+1];
    for (int i = 0; i <= cap_a; ++i) {
        visited[i] = new State*[cap_b+1];
        fill(visited[i], visited[i] + cap_b + 1, nullptr);
    }

    State *current;

    while(states.size() != 0){
    	current = new State(states.front());
        states.pop();

        int val_a = current->a;
        int val_b = current->b;
        int val_c = current->c;

        if (visited[val_a][val_b] != nullptr) {
			delete current;
			continue;
		}
		visited[val_a][val_b] = current;

        if ((val_a == goal_a) && (val_b == goal_b) && (val_c == goal_c)){
        	State output = *current;
        	display(output);

        	for (int i = 0; i <= cap_a; i++) {
        		for (int j = 0; j <= cap_b; j++) {
        			current = visited[i][j];
        			delete current;
        		}
        		delete [] visited[i];
        	}
        	delete [] visited;

            return output;
        }

        // 1) Pour from C to A
        if ((val_a != cap_a) && (val_c != 0)){
            int pour = min(cap_a-val_a, val_c);
            if (visited[val_a+pour][val_b] == nullptr) {
            	string str = "Pour " + to_string(pour);
            	if (pour == 1)
            		str += " gallon ";
            	else
            		str += " gallons ";
            	str += "from C to A.";
                states.push(State(val_a+pour, val_b, val_c-pour, str, current));
            }
        }

        // 2) Pour from B to A
        if (val_a != cap_a && val_b != 0){
            int pour = min(cap_a-val_a, val_b);
            if (visited[val_a+pour][val_b-pour] == nullptr) {
            	string str = "Pour " + to_string(pour);
            	if (pour == 1)
					str += " gallon ";
				else
					str += " gallons ";
            	str += "from B to A.";
                states.push(State(val_a+pour, val_b-pour, val_c, str, current));
            }
        }

        // 3) Pour from C to B
        if (val_b != cap_b && val_c != 0){
            int pour = min(cap_b-val_b, val_c);
            if (visited[val_a][val_b+pour] == nullptr){
            	string str = "Pour " + to_string(pour);
            	if (pour == 1)
					str += " gallon ";
				else
					str += " gallons ";
				str += "from C to B.";
                states.push(State(val_a, val_b+pour, val_c-pour, str, current));
            }
        }

        // 4) pour from A to B
        if (val_b != cap_b && val_a != 0){
            int pour = min(cap_b-val_b, val_a);
            if (visited[val_a-pour][val_b+pour] == nullptr){
            	string str = "Pour " + to_string(pour);
            	if (pour == 1)
					str += " gallon ";
				else
					str += " gallons ";
				str += "from A to B.";
                states.push(State(val_a-pour, val_b+pour, val_c, str, current));
            }
        }

        // 5) Pour from B to C
        if (val_c != cap_c && val_b != 0){
            int pour = min(cap_c-val_c, val_b);
            if (visited[val_a][val_b-pour] == nullptr) {
            	string str = "Pour " + to_string(pour);
            	if (pour == 1)
					str += " gallon ";
				else
					str += " gallons ";
				str += "from B to C.";
                states.push(State(val_a, val_b-pour, val_c+pour, str, current));
            }
        }

        // 6) pour from A to C
        if(val_c != cap_c && val_a !=0){
            int pour = min(cap_c-val_c, val_a);
            if (visited[val_a-pour][val_b] == nullptr) {
            	string str = "Pour " + to_string(pour);
            	if (pour == 1)
					str += " gallon ";
				else
					str += " gallons ";
				str += "from A to C.";
                states.push(State(val_a-pour, val_b, val_c+pour, str, current));
            }
        }
    }


    for (int i = 0; i <= cap_a; i++) {
		for (int j = 0; j <= cap_b; j++) {
			current = visited[i][j];
			delete current;
		}
		delete [] visited[i];
	}
	delete [] visited;

	State output = State(-1, -1, -1, "No solution.");
	display(output);
    return output;
}



int main(int argc, char * const argv[]) {
	istringstream iss;
	int value[6] = {};

	//Case 1: Not 6 command line arguments
	if (argc != 7) {
		cerr << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
				return 1;
	}

	//Case 2: Error check on each inputs
	for (int i = 0; i < 6; i++) {
		iss.str(argv[i+1]);
		if (! (iss >> value[i]) || (i < 3 && (value[i] <= 0)) || (i >= 3 && (value[i] < 0))) {
			cerr << "Error: Invalid ";
			if (i < 3)
				cerr << "capacity '";
			else
				cerr << "goal '";
			cerr << iss.str() << "' for jug " << (char)('A' + i%3) << "." << endl;
			return 1;
		}
		iss.clear();
	}

	//Case 3: The goal for a given jug can never exceed its capacity.
	for (int i = 0; i < 3; i++) {
		if (value[i] < value[i+3]) {
			cerr << "Error: Goal cannot exceed capacity of jug " << (char)('A' + i) << "." << endl;
			return 1;
		}
	}

	//Case 4: The sum of goal states is not equal to initial water volume.
	if (value[2] != (value[3] + value[4] + value[5])) {
		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
		return 1;
	}

	//Valid inputs
	State s = bfs(value[0], value[1], value[2], value[3], value[4], value[5]);
    return 0;
}
