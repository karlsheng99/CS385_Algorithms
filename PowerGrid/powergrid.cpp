/*******************************************************************************
 * Name    : powergrid.cpp
 * Author  : Zikang Sheng
 * Version : 1.0
 * Date    : December 14, 2020
 * Description : Compute the minimum set of roads on which to install power lines
 *              using Kruskal's Algorithm.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct Edge {
    int start, end, weight;
    string name;

    Edge(int start, int end, int weight, string name) :
        start{start}, end{end}, weight{weight}, name{name} {}
};

struct Vertex {
    Vertex *next;
    const int value;

    Vertex(int value) :
        next{nullptr}, value{value} {}
};

vector<Edge> edges;
vector<Edge> result;
Vertex **set;
int num_vertex;
int total_length;

bool create_list(string line, int line_number) {
    if (line.find('\r') < line.length()) {
        line.pop_back();
    }
    stringstream line_str(line);
    vector<string> temp;
    while (line_str.good()) {
        string sub_str;
        getline(line_str, sub_str, ',');
        temp.push_back(sub_str);
     }


    //  Check number of components.
    if (temp.size() != 4) {
        cerr << "Error: Invalid edge data '" << line << "' on line " << line_number << "." << endl;
        return false;
    }

    int start, end, weight;
    string name = temp.at(3);
    istringstream iss;

    // Starting vertex error.
    iss.str(temp.at(0));
    if (!(iss >> start) || start < 1 || start > num_vertex) {
        cerr << "Error: Starting vertex '" << temp.at(0) << "' on line " << line_number << " is not among valid values 1-" << num_vertex << "." << endl;
        return false;
    }
    iss.clear();

    // Ending vertex error.
    iss.str(temp.at(1));
    if (!(iss >> end) || end < 1 || end > num_vertex) {
        cerr << "Error: Ending vertex '" << temp.at(1) << "' on line " << line_number << " is not among valid values 1-" << num_vertex << "." << endl;
        return false;
    }
    iss.clear();

    // Edge weight error.
    iss.str(temp.at(2));
    if (!(iss >> weight) || weight < 1) {
        cerr << "Error: Invalid edge weight '" << temp.at(2) << "' on line " << line_number << "." << endl;
        return false;
    }
    iss.clear();
    
    // Sort vertex letter.
    if (end < start) {
        swap(start, end);
    }
    edges.push_back(Edge(start, end, weight, name));
    return true;
}

void merge_sort(Edge array[], Edge *scratch[], int low, int high, bool sort_weight = true) {
    if(low < high){

		int mid = low + (high - low)/2;
        merge_sort(array, scratch, low, mid, sort_weight);
		merge_sort(array, scratch, mid+1, high, sort_weight);

		int L = low;
		int H = mid + 1;
		for (int k = low; k <= high;k++){
			
            if(L <= mid && (H > high || 
                (sort_weight ? array[L].weight <= array[H].weight : array[L].name.compare(array[H].name) < 0))){
				scratch[k] = new Edge(array[L]);
				L++;
			}
			else{
				scratch[k] = new Edge(array[H]);
				H++;
			}
		}

		for(int k = low; k <= high; k++){
			array[k] = *scratch[k];
            delete scratch[k];
		}
	}
}

//  Sort the array by the weights, parameter: sort_what = true;
//  sort the array by the street names, parameter: sort_what = false.
void sort(const bool sort_what = true){
    size_t length;
    Edge *array;

    if (sort_what) {
        length = edges.size();
        array = &edges[0];
    }
    else {
        length = result.size();
        array = &result[0];
    }

    Edge **scratch = new Edge*[length];
    int low = 0;
	int high = length - 1;
	sort_what ? merge_sort(array, &scratch[0], low, high) : 
                merge_sort(array, &scratch[0], low, high, false);
    delete [] scratch;
}

void makeset() {
    set = new Vertex*[num_vertex];
    for (int i = 0; i < num_vertex; i++) {
        set[i] = new Vertex(i+1);
    }
}

void deleteset() {
    for (int i = 0; i < num_vertex; i++) {
        delete set[i];
    }
    delete [] set;
}

void union_v(int x, int y) {
    set[x-1]->next = set[y-1];
}

int find(int vertex) {
    if (set[vertex - 1]->next == nullptr) {
        return set[vertex - 1]->value;
    }
    return find(set[vertex - 1]->next->value);
}

void kruskal() {
    for (size_t i = 0;  i < edges.size(); i++) {
        int start = find(edges.at(i).start);
        int end = find(edges.at(i).end);
        if (start != end) {
            result.push_back(edges.at(i));
            total_length += edges.at(i).weight;
            union_v(end, start);
        }
    }
}

void display() {
    for (int i = 2; i <= num_vertex; i++) {
        if (find(i) != find(i-1)) {
            cout << "No solution." << endl;
            return;
        }
    }

    // Sort "Result" by the street names.
    sort(false);
    cout << "Total wire length (meter";
        if (total_length > 1) {
            cout << "s";
        }
        cout << "): " << total_length << endl;
    for (size_t i = 0; i < result.size(); i++) {
        cout << result.at(i).name << " [" << result.at(i).weight << "]" << endl;
    }
}

int main(int argc, const char *argv[]) {
    // Make sure the right number of command line arguments exist.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input file>" << endl;
        return 1;
    }
    // Create an ifstream object.
    ifstream input_file(argv[1]);
    // If it does not exist, print an error message.
    if (!input_file) {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }
    // Add read errors to the list of exceptions the ifstream will handle.
    input_file.exceptions(ifstream::badbit);
    string line;
    try {
        unsigned int line_number = 1;
        // Use getline to read in a line.
        while (getline(input_file, line)) {
            if (line_number == 1) {
                istringstream iss(line);
                int num;
                if (!(iss >> num) || num < 1 || num > 1000) {
                    if (line.find('\r') < line.length()) {
                        line.pop_back();
                    }
                    cerr << "Error: Invalid number of vertices '" << line << "' on line 1." << endl;
                    return 1;
                }
                else if (num == 1) {
                    cout << "No solution." << endl;
                    return 0;
                }
                else {
                    num_vertex = num;
                    total_length = 0;
                }
            }
            else {
                if (!create_list(line, line_number)) {
                    return 1;
                }
            }
            ++line_number;
        }
        // Don't forget to close the file.
        input_file.close();

        sort();
        makeset();
        kruskal();
        display();
        deleteset();
    }
    catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }

    return 0;
}