#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;


void displayAdjacencyMatrix(const vector<vector<int>>& matrix); // Displays the adjacency matrix
void displayAdjacencyList(const vector<vector<int>>& list); // Displays the adjacency list
void breadthFirstSearch(const vector<vector<int>>& adjList, int sourceChar);    // BFS function
void displayBfsState(const queue<int>& q, vector<string>& color, vector<int>& distance, const vector<int>& predecessor, int numVertices);   // Displays queue and tables for each state


int main() {
    int numVertices, numEdges;
    cout << "Enter the number of vertices and edges (with a space in between): ";
    cin >> numVertices >> numEdges;

    // Initializes adjacency matrix and list
    vector<vector<int>> adjMatrix(numVertices, vector<int>(numVertices, 0));
    vector<vector<int>> adjList(numVertices);

    // Takes in edges and populates matrix / list
    for (int i = 0; i < numEdges; ++i) {
        char uChar, vChar;
        cout << "Enter the vertices for edge " << i << " (example, A B): ";
        cin >> uChar >> vChar;
        int u = toupper(uChar) - 'A';   // In case user inputs lower case
        int v = toupper(vChar) - 'A';

        // Checks if the vertex is within the range of valid vertices characters
        if (u >= 0 && u < numVertices && v >= 0 && v < numVertices) {
            adjMatrix[u][v] = adjMatrix[v][u] = 1; // Undirected graph
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }
        else {
            cout << "Invalid vertex name. Please use letters A-" << char('A' + numVertices - 1) << endl;
            i--;
        }
    }

    displayAdjacencyMatrix(adjMatrix);
    displayAdjacencyList(adjList);

    char sourceChar;
    cout << "\nEnter the source character vertex for BFS (A-" << char('A' + numVertices - 1) << "): ";
    cin >> sourceChar;
    int sourceIndex = toupper(sourceChar) - 'A'; // Finds index based on reference letter input

    // Checks if the source index is in range to avoid out of bounds crashing
    if (sourceIndex < 0 || sourceIndex >= numVertices) {
        cout << "Error: Source vertex is out of range. Please enter a letter from A to " << char('A' + numVertices - 1) << ": ";
        cin >> sourceChar;
        sourceIndex = toupper(sourceChar) - 'A';

        if (sourceIndex < 0 || sourceIndex >= numVertices) {
            cout << "Error: Second wrong input. Exiting program." << endl;
            return 1;
        }
    }

    breadthFirstSearch(adjList, sourceChar);

    return 0;
}

void breadthFirstSearch(const vector<vector<int>>& adjList, int sourceIndex) {
    int source = toupper(sourceIndex) - 'A';
    int numVertices = adjList.size();
    vector<string> color(numVertices, "white");
    vector<int> distance(numVertices, INT_MAX);
    vector<int> predecessor(numVertices, -1);
    queue<int> q;

    // Source node initialized to start BFS
    color[source] = "grey";
    distance[source] = 0;
    q.push(source);

  cout << "& = infinity, w = white, g = grey, b = black" << endl << endl;

    displayBfsState(q, color, distance, predecessor, numVertices);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adjList[u]) {
            if (color[v] == "white") {
                color[v] = "grey";
                distance[v] = distance[u] + 1;
                predecessor[v] = u;
                q.push(v);
            }
        }
        color[u] = "black";
        // Displays the current state of the queue, color distance, and predecessor
        displayBfsState(q, color, distance, predecessor, numVertices);
    }

    // Checks for any vertices not connected to source
    for (int i = 0; i < numVertices; ++i) {
        if (color[i] == "white") {
            cout << "Vertex " << char('A' + i) << " is not connected to the source.\n";
        }
    }
}

void displayBfsState(const queue<int>& q, vector<string>& color, vector<int>& distance, const vector<int>& predecessor, int numVertices) {
    // Displays the queue
    cout << "Queue: ";
    queue<int> tempQ = q;
    while (!tempQ.empty()) {
        cout << char('A' + tempQ.front()) << " ";
        tempQ.pop();
    }
    cout << endl;

    // Displays vertex letters
    cout << "Vertex:       ";
    for (int i = 0; i < numVertices; ++i) {
        cout << char('A' + i) << " ";
    }
    cout << endl;

    // Displays the color of each vertex
    cout << "Colors:       ";
    for (int i = 0; i < numVertices; ++i) {
        cout << color[i][0] << " "; // Displays the first letter of color
    }
    cout << endl;

    // Displays the distance from the source for each vertex
    cout << "Distances:    ";
    for (int i = 0; i < numVertices; ++i) {
        if (distance[i] == INT_MAX) {
            cout << "& "; // & = infinity
        }
        else {
            cout << distance[i] << " ";
        }
    }
    cout << endl;

    // Displays the predecessor for each vertex
    cout << "Predecessors: ";
    for (int i = 0; i < numVertices; ++i) {
        if (predecessor[i] == -1) {
            cout << "^ ";
        }
        else {
            cout << char('A' + predecessor[i]) << " ";
        }
    }
    cout << endl << endl;
}

void displayAdjacencyMatrix(const vector<vector<int>>& matrix) {
    int numVertices = matrix.size();
    cout << "\nAdjacency Matrix:" << endl;

    // Prints the column header
    cout << "  ";
    for (int i = 0; i < numVertices; ++i) {
        cout << char('A' + i) << " ";
    }
    cout << endl;

    // Prints the matrix
    for (int i = 0; i < numVertices; ++i) {
        // Prints the row label
        cout << char('A' + i) << " ";
        for (int j = 0; j < numVertices; ++j) {
            // Prints each cell value
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void displayAdjacencyList(const vector<vector<int>>& list) {
    cout << "\nAdjacency List:" << endl;
    for (int i = 0; i < list.size(); ++i) {
        // Prints the current vertex
        cout << "Vertex " << char('A' + i) << ": ";

        // Prints all adjacent vertices
        for (int j : list[i]) {
            cout << char('A' + j) << " ";
        }
        cout << endl;
    }
}
