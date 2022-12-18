#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int V = 8;

void addedge(vector<int> graph[V], int source, int destination) {
	graph[source].push_back(destination);
	graph[destination].push_back(source);
}

void BFS(vector<int> graph[V], vector<bool> &visited, int currentnode) {
	queue<int> q;
	
	q.push(currentnode);
	visited[currentnode] = true;
	while (!q.empty()) {
		currentnode = q.front();
		q.pop();

		cout << currentnode << " ";

		for (int neighbour : graph[currentnode]) {
			if (!visited[neighbour]) {
				q.push(neighbour);
			}
			visited[neighbour] = true;
		}

	}
}

void DFS(vector<int> graph[V], vector<bool> &visited, int currentnode) {
	cout << currentnode << " ";
	visited[currentnode] = true;
	for (int neighbour : graph[currentnode]) {
		if (!visited[neighbour]) {
			DFS(graph, visited, neighbour);
		}
	}
	
}



int main() {
	vector<int> graph[V];
	vector<bool> visited(V, false);

	addedge(graph, 0, 1);
	addedge(graph, 0, 2);
	addedge(graph, 0, 3);
	addedge(graph, 2, 4);
	addedge(graph, 2, 5);
	addedge(graph, 3, 6);
	addedge(graph, 7, 6);

	BFS(graph, visited, 2);
	cout << endl;
	vector<bool> visited2(V, false);
	DFS(graph, visited2, 2);
}
