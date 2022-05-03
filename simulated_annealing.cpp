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
    int latest = path.at(0);
    for(size_t i = 1; i<path.size(); i++){
        int current = path.at(i);
        cost += graph[latest][current];
        latest=current;
    }
    return cost;
}

vector<int> random_solution(const int N, mt19937& gen){
    vector<int> s(N);
    iota(s.begin(), s.end(), 0);
    shuffle(s.begin(), s.end(), gen);
    s[N-1] = s[0];
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

vector<int> simulated_annealing(const string path, mt19937& gen, bool& error){
    if(path.length() <= 0){
        error=true;
        return {};
    }

    int n = 0;
    int** graph = create_graph(path, &n);
    if(graph == nullptr){
        error=true;
        return {};
    }

    /* DEBUG */ //display_graph(graph, n);
  
    string instance = get_instance(path);
    if(instance.length() <= 0){
        error=true;
        return {};
    }

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

    /* DEBUG */ cout << "Initial: ";
    /* DEBUG */ print_vector(s);

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

    /* DEBUG */ cout << "Final (energy:" << e << "): ";
    /* DEBUG */ print_vector(s);

    delete_graph(graph, n);

    return s;
}

int main(){
    
    mt19937 gen(time(nullptr));

    const string path = "instances/10_100.in";
    bool error = false;
    vector<int> out = simulated_annealing(path, gen, error);

    return 0;
}