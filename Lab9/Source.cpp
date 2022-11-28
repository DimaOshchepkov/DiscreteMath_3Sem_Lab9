#include "Header.h"

void CreateFile(std::string name)
{
	std::ofstream fout(name);
	std::cout << "Inpute count tops\n";
	int countTop = 0;
	std::cin >> countTop;
	std::cout << "Input count edges\n";
	int countEdges = 0;
	std::cin >> countEdges;

	fout << countTop << ' ' << countEdges << '\n';

	std::cout << "Enter edges in format top - top";
	for (int i = 0; i < countEdges; i++)
	{
		int x, y;
		std::cin >> x >> y;
		fout << x << " " << y << '\n';
	}
	fout.close();
}

std::vector<std::list<int>> ReadFile(std::string name)
{
	std::ifstream fin(name);
	int countTop = 0, countEdges = 0;
	fin >> countTop >> countEdges;

	std::vector<std::list<int>> graph(countTop);
	for (int i = 0; i < countEdges; i++)
	{
		int x, y;
		fin >> x >> y;
		graph[x].push_back(y);
		graph[y].push_back(x);
	}
	fin.close();

	return graph;
}


std::vector<std::list<int>> CountConnectivityComponent(std::vector<std::list<int>> graph)
{
	std::vector<bool> visited(graph.size(), false);
	std::vector<int> parent(graph.size(), -1);
	std::list<int> q;

	std::vector<std::list<int>> components;
	int count = 0;
	for (int i = 0; i < graph.size(); i++)
	{
		if (!visited[i])
		{
			parent[i] = -1;
			q.push_front(i);
			visited[i] = true;
			while (q.size() != 0)
			{
				int front = q.front();
				q.pop_front();
				for (int top : graph[front]) {
					if (!visited[top])
					{
						parent[top] = front;
						q.push_front(top);
						
						visited[top] = true;
					}
					else if(parent[front] != top)
					{
						visited[top] = true;
						components.push_back({ });
						int sup = front;
						while (parent[sup] != top)
						{
							components.back().push_back(sup);
							sup = parent[sup];
						}
						components.push_back({ top });
					}
				}
			}
		}
	}

	return components;
}

void PrintDistance(std::vector<int> distances, int top)
{
	std::cout << "Distance from " << top << '\n';
	for (int i = 0; i < distances.size(); i++)
		std::cout << i << ' ' << distances[i] << '\n';
}

std::vector<std::list<int>> ShotestDistance(std::vector<std::list<int>> graph, int top)
{
	std::vector<bool> visited(graph.size(), false);
	std::list<int> q;

	std::vector<int> parent(graph.size());
	parent[top] = -1;
	q.push_back(top);
	visited[top] = true;
	while (q.size() != 0)
	{
		int front = q.back();
		q.pop_back();
		for (int t : graph[front]) {
			if (!visited[t])
			{
				q.push_back(t);
				parent[t] = front;
				visited[t] = true;
			}
		}
	}

	std::vector<std::list<int>> distances(graph.size());
	for (int i = 0; i < graph.size(); i++)
	{
		if (visited[i])
		{
			int cur = i;
			while (cur != top)
			{
				distances[i].push_back(cur);
				cur = parent[cur];
			}
			distances[i].push_back(top);
		}
		else
			distances[i].push_back(-1);
	}



	return distances;
}



void PrintGraph(std::vector<std::list<int>> graph)
{
	for (int i = 0; i < graph.size(); i++)
		std::cout << i << ": " << graph[i];
}
