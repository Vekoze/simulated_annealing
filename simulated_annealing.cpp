/*
 * TSP solved with simulated annealing algorithm
 *
 * @author vkze (Victor ENJALBERT)
 * Contact: victxr.enjalbert@gmail.com
 */

#include <iostream>
#include <math.h>   
#include <numeric>
#include <algorithm>
#include <random>
#include <ctime>
#include "utils.hpp"

enum SolutionType {
    Inverse,
    Insert,
    Swap,
};

int cost(int** graph, const vector<int> path){
    int cost = 0;
    int latest = path.at(0)-1;
    for(size_t i = 1; i<path.size(); i++){
        int current = path.at(i)-1;
        cost += graph[latest][current];
        latest=current;
    }
    return cost;
}

vector<int> random_solution(const int N, mt19937& gen){
    vector<int> s(N+1);
    iota(s.begin(), s.end()-1, 1);
    shuffle(s.begin(), s.end()-1, gen);
    s[N] = s[0];
    return s;
}

vector<int> candidate_solution(vector<int> path, SolutionType type){
    int size = path.size();
    pair<int,int> random_index = make_pair( rand()%(size-2) + 1 , rand()%(size-2) + 1 );

    switch (type){
    case Inverse:
        return path;
    case Insert:
        return path;
    case Swap:
        swap(path[random_index.first], path[random_index.second]);
        return path;
    default:
        return {};
    }
}

vector<int> simulated_annealing(int** graph, int n, const string path, mt19937& gen, bool& error){
    if(path.length() <= 0){
        error=true;
        return {};
    }

    if(graph == nullptr){
        error=true;
        return {};
    }

    /* DEBUG */ //display_graph(graph, n);
    /* DEBUG */ //cout << "Input name: " << instance << endl << endl;

    /* Simulated Annealing - Parameters
    * N         : number of cities
    * T0        : initial temperature
    * R         : cooling ratio
    * MAX_ITER  : max iteration per permutation
    */
    const int N = n;
    const double T0 = N;
    const double R = 0.99;
    const int MAX_ITER = 200;

    vector<int> s = random_solution(N, gen);

    /* DEBUG */ //cout << "Initial: ";
    /* DEBUG */ //print_vector(s);

    double t = T0;
    int e = cost(graph, s);
    bool frozen = false;
    uniform_real_distribution<double> dist(0.0,1.0);

    while(!frozen){
        for(int i = 0; i<MAX_ITER; i++){
            vector<int> cs = candidate_solution(s, SolutionType::Swap);
            int ecs = cost(graph, cs);
            int delta = ecs - e;
            if(delta < 0 || dist(gen) <= exp(-delta/t)){
                e = ecs;
                s = cs;
            }
        }
        t*=R;
        if(t<1E-8)
            frozen=true;
    }

    /* DEBUG */ //cout << "Final (energy:" << e << "): ";
    /* DEBUG */ //print_vector(s);
    
    return s;
}

int main(int argc, const char* argv[]){

    if(argc<2) return -1;

    mt19937 gen(time(nullptr));
    const string path = argv[1];
    bool error = false;
    int n;

    int** graph = create_graph(path, &n);
    vector<int> f_path = simulated_annealing(graph, n, path, gen, error);
    write_in_file(f_path, cost(graph, f_path), get_instance(path), "sim_annealing");

    delete_graph(graph, n);

    return 0;
}