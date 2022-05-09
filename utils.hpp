#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <fstream>

using namespace std;

#define print_vector(v) for_each(v.begin(),v.end(),[](const auto &e) { cout << e << " ";}); cout << endl;

int** create_graph(const string path, int* n);

void delete_graph(int** graph, int n);

void display_graph(int** graph, int n);

void write_in_file(vector<int> path, int weight, const string instance, const string method);

string get_instance(string path);

#endif