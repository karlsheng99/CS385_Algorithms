/*******************************************************************************
 * Name    : shortestpaths.cpp
 * Author  : Zikang Sheng & Keye Li
 * Version : 1.0
 * Date    : December 5, 2020
 * Description : Solve the all pairs shortest paths problem with Floyd’s algorithm.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <climits>
#include <vector>
#include <string>

using namespace std;

const long INF = LONG_MAX;
int num_vertices = 0;
long** dist;
long** path;
long** intermediate;

int len(long val) {
    int count = 1;
    while (val >= 10) {
        val /= 10;
        count++;
    }
    return count;
}

bool fill_distance(string line, int line_num) {
    istringstream iss(line);
    vector<string> temp;
    for (string s; iss >> s; ) {
        temp.push_back(s);
    }

    if (temp.size() != 3) {
        cerr << "Error: Invalid edge data '" << line << "' on line " << line_num << "." << endl;
        return false;
    }

    int start = temp.at(0).at(0) - 'A';
    int end = temp.at(1).at(0) - 'A';
    int weight;
    istringstream w(temp.at(2));

    if (temp.at(0).length() != 1 || start < 0 || start > num_vertices) {
        cerr << "Error: Starting vertex '" << temp.at(0) << "' on line " << line_num <<  " is not among valid values A-" << static_cast<char>('A' + num_vertices - 1) << "." <<endl;
        return false;
    }
    if (temp.at(1).length() != 1 || end < 0 || end > num_vertices) {
        cerr << "Error: Ending vertex '" << temp.at(1) << "' on line " << line_num <<  " is not among valid values A-" << static_cast<char>('A' + num_vertices - 1) << "." << endl;
        return false;
    }
    if(!(w >> weight) || weight <= 0){
        cerr << "Error: Invalid edge weight '" << temp.at(2) <<"' on line "<< line_num << "." << endl;
        return false;
    }

    dist[start][end] = weight;
    
    return true;
}

void init_matrices() {
    path = new long*[num_vertices];
    for (int i = 0; i < num_vertices; i++) {
        path[i] = new long[num_vertices];
        for (int j = 0; j < num_vertices; j++) {
            path[i][j] = dist[i][j];
        }
    }

    intermediate = new long*[num_vertices];
    for (int i = 0; i < num_vertices; i++) {
        intermediate[i] = new long[num_vertices];
        fill(intermediate[i], intermediate[i] + num_vertices, INF);
    }
}

void floyd() {
    for (int n = 0; n < num_vertices; n++){
        for (int i = 0; i < num_vertices; i++) {
            for (int j = 0; j < num_vertices; j++) {
                if (i != n && j != n && i != j) {
                    long old_value = path[i][j];
                    long new_value;
                    if (path[i][n] == INF || path[n][j] == INF) {
                        new_value = INF;
                    }
                    else {
                        new_value = path[i][n] + path[n][j];
                    }
                    if (new_value < old_value) {
                        path[i][j] = new_value;
                        intermediate[i][j] = n;
                    }
                }
            }
        }
    }
}

string backtrack(int start, int end, long &dis) {
    if (path[start][end] == INF) {
        dis = INF;
        return "none";
    }
    if (start == end) {
        return "";
    }
    if (intermediate[start][end] == INF) {
        dis += path[start][end];
        string str = " -> ";
        str += static_cast<char>('A' + end);
        return str;
    }
    return backtrack(start, intermediate[start][end], dis) +
        backtrack(intermediate[start][end], end, dis);
}

void display_result() {
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            long dis = 0;
            string path = backtrack(i, j, dis);
            string distance;
            if (dis == INF) {
                distance = "infinity";
            }
            else {
                distance = to_string(dis);
                path = static_cast<char>('A' + i) + path;
            }
            cout << static_cast<char>('A' + i) << " -> " << static_cast<char>('A' + j) << ", distance: " << distance << ", path: " << path << endl;
        }
    }
}

/**
* Displays the matrix on the screen formatted as a table.
*/
void display_table(long** const matrix, const string &label, const bool use_letters = false) {
    cout << label << endl;
    long max_val = 0;
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            long cell = matrix[i][j];
            if (cell < INF && cell > max_val) {
                max_val = matrix[i][j];
            }
        }
    }

    int max_cell_width = use_letters ? len(max_val) :
        len(max(static_cast<long>(num_vertices), max_val));
    cout << ' ';
    for (int j = 0; j < num_vertices; j++) {
        cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
    }
    cout << endl;
    for (int i = 0; i < num_vertices; i++) {
        cout << static_cast<char>(i + 'A');
        for (int j = 0; j < num_vertices; j++) {
            cout << " " << setw(max_cell_width);
            if (matrix[i][j] == INF) {
                cout << "-";
            }
            else if (use_letters) {
                cout << static_cast<char>(matrix[i][j] + 'A');
            }
            else {
                cout << matrix[i][j];
            }
        }
        cout << endl;
    }
    cout << endl;
}

int main(int argc, const char *argv[]) {
    // Make sure the right number of command line arguments exist.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
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

        if (getline(input_file, line)) {
            istringstream iss(line);
            int num;

            if(!(iss >> num)) {
                cerr << "Error: Invalid number of vertices '" << line << "' on line " << line_number << "." << endl;
                return 1;
            }
            if (num < 1 || num > 26) {
                cerr << "Error: Invalid number of vertices '" << num << "' on line " << line_number << "." << endl;
                return 1;
            }
            else {
                num_vertices = num;
            }

            dist = new long*[num_vertices];
            for (int i = 0; i < num_vertices; i++){
                dist[i] = new long[num_vertices];
                for (int j = 0; j < num_vertices; j++) {
                    if (i == j) {
                        dist[i][j] = 0;
                    }
                    else {
                        dist[i][j] = INF;
                    }
                }
            }

            line_number++;
        }

        while (getline(input_file, line)) { 
            if (!fill_distance(line, line_number)){
                for (int i = 0; i < num_vertices; i++) {
                    delete [] dist[i];
                }
                delete [] dist;
                return 1;
            }
            
            ++line_number;
        }
        // Don't forget to close the file.
        input_file.close();

        init_matrices();
        floyd();
        display_table(dist, "Distance matrix:");
        display_table(path, "Path lengths:");
        display_table(intermediate, "Intermediate vertices:", true);
        display_result();

        for (int i = 0; i < num_vertices; i++) {
            delete [] dist[i];
            delete [] path[i];
            delete [] intermediate[i];
        }
        delete [] dist;
        delete [] path;
        delete [] intermediate;
    } 
    catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }

    return 0;
}
