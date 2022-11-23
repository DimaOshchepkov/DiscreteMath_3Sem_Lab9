#pragma once
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>

void CreateFile(std::string name = "graph.txt");

std::vector<std::list<int>> ReadFile(std::string name = "graph.txt");

std::vector<std::list<int>> CountConnectivityComponent(std::vector<std::list<int>> graph);

std::vector<std::list<int>> ShotestDistance(std::vector<std::list<int>> graph, int top);

void PrintDistance(std::vector<int> distances, int top);
