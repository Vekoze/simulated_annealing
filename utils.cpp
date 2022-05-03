#include "utils.hpp"

int** create_graph(const string path, int* n){
    ifstream input(path);
    if(input.is_open()){
        string line;
        getline(input, line);
        const int N = stoi(line);
        int** graph = new int*[N];

        if(graph==nullptr)
            return nullptr;

        for(int i = 0; i<N; i++){
            graph[i] = new int[N];
            for(int j = 0; j<N; j++){
                graph[i][j] = 0;
            }
        }

        int i = 0;
        while(getline(input, line)){
            vector<int> numbers{};
            unsigned int pos = 0;
            while ((pos = line.find(' ')) != string::npos) {
                numbers.push_back(stoi(line.substr(0, pos)));
                line.erase(0, pos + 1);
            }
            for(size_t j = 0; j<numbers.size(); j++){
                graph[i][j] = numbers.at(j);
            }
            i++;
        }

        input.close();
        *n = N;
        return graph;

    }
    return nullptr;
}

void delete_graph(int** graph, int n){
    for(int i = 0; i<n; i++){
        delete[] graph[i];
    }
    delete[] graph;
}

void display_graph(int** graph, int n){
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            cout << graph[i][j];
            if(j!=n-1) cout << " ";
        }
        cout << endl;
    }
    cout << endl;
}

string get_instance(string path){
    const regex query("/(.*).in$");
    smatch m;
    if(regex_search(path, m, query)){
        return m[1];
    }
    return string();
}