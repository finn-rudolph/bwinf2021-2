#include <vector>
#include <string>
#include <regex>
#include <iostream>
using namespace std;

vector<int> get_numbers(string s) {
    regex numbers("[0-9][0-9]*");
    smatch match;

    vector<int> res;
    while (regex_search(s, match, numbers)) {
        for (auto n: match) {
            res.push_back(stoi(n));
            s = match.suffix().str();
        }
    }
    return res;
}

void convert_edges(string line, char first_char) {
    while (line[0] == first_char) {
        vector<int> edge = get_numbers(line);
        cout << (edge[1] - 1) << " " << (edge[2] - 1) << " " << edge[3] << "\n";
        getline(cin, line);
    }
}

int main() {
    string line;

    while (line.substr(0, 6) != "#Nodes") getline(cin, line);
    
    int nodes = get_numbers(line)[0];
    getline(cin, line);
    int edges = get_numbers(line)[0];
    getline(cin, line);
    int arcs = get_numbers(line)[0];

    cout << nodes << " " << (edges + arcs) << "\n";

    // Get edges

    while (line.substr(0, 4) != "ReE.") getline(cin, line);
    getline(cin, line);
    convert_edges(line, 'E');

    while (line.substr(0, 4) != "EDGE") getline(cin, line);
    getline(cin, line);
    convert_edges(line, 'N');

    // Get arcs, treated as edges

    while (line.substr(0, 4) != "ReA.") getline(cin, line);
    getline(cin, line);
    convert_edges(line, 'A');

    while (line.substr(0, 3) != "ARC") getline(cin, line);
    getline(cin, line);
    convert_edges(line, 'N');
}