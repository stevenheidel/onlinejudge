#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <cassert>
#include <cstdlib>
#include <climits>

using namespace std;


const int MAX_TASKS = 100;
const int MAX_NODES = MAX_TASKS+1;
const int DISCONNECT = INT_MAX;

ifstream infile("task.in");
ifstream outfile("task.out");
ofstream vfyfile("task-verifier.out");
ofstream tempfile("task.tmp");




bool bellmanford(int graph[MAX_NODES][MAX_NODES], int n, int src,
		 int D[])
{
  int v, w, k;

  for (v = 0; v < n; v++) {
    D[v] = INT_MAX;
  }
  D[src] = 0;

  for (k = 0; k < n-1; k++) {
    for (v = 0; v < n; v++) {
      for (w = 0; w < n; w++) {
	if (graph[v][w] != DISCONNECT && D[v] != INT_MAX) {
	  if (D[w] == INT_MAX || D[w] > D[v] + graph[v][w]) {
	    D[w] = D[v] + graph[v][w];
	  }
	}
      }
    }
  }

  for (v = 0; v < n; v++) {
    for (w = 0; w < n; w++) {
      if (graph[v][w] != DISCONNECT && D[v] != INT_MAX) {
        if (D[w] == INT_MAX || D[w] > D[v] + graph[v][w]) {
	  return false;
	}
      }
    }
  }
  return true;
}

bool do_case(int n, int m)
{
  // clear graph
  int graph[MAX_NODES][MAX_NODES];
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      graph[i][j] = DISCONNECT;
    }
  }

  for (int i = 1; i <= n; i++) {
    graph[0][i] = 0;
  }
    
  // read constraints
  for (int i = 0; i < m; i++) {
    int task1, task2, A;
    string garbage;
    string key;
    infile >> garbage >> task1 >> garbage;
    infile >> key;
    if (key == "at") {
      infile >> garbage >> A >> garbage >> garbage >> garbage >> garbage >> task2;
      graph[task1][task2] = min(graph[task1][task2], -A);
    } else {
      assert(key == "within");
      infile >> A >> garbage >> garbage >> garbage >> garbage >> garbage
	  >> garbage >> garbage >> task2;
      graph[task2][task1] = min(graph[task2][task1], A);
      graph[task1][task2] = min(graph[task1][task2], 0);
    }
  }

  int D[MAX_NODES];
  if (bellmanford(graph, n+1, 0, D)) {
    // try to read some integers
    long long times[MAX_NODES];
    for (int i = 1; i <= n; i++) {
      if (!(outfile >> times[i])) {
	vfyfile << "EXPECTING starting times but cannot read them" << endl;
	vfyfile << "WRONG ANSWER" << endl;
	exit(1);
      }
      if (!(1 <= times[i] && times[i] <= 1000000)) {
	vfyfile << "starting times out of range" << endl;
	vfyfile << "WRONG ANSWER" << endl;
	exit(1);
      }
    }

    // check constraints
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
	if (i == j || graph[i][j] == DISCONNECT) continue;
	int A = graph[i][j];
	if (!(times[i] + A >= times[j])) {
	  vfyfile << "WRONG ANSWER" << endl;
	  vfyfile << "task " << i << " starts at " << times[i] << endl;
	  vfyfile << "task " << j << " starts at " << times[j] << endl;
	  vfyfile << "constraint is " << A << endl;
	  exit(1);
	}
      }
    }
    string line;
    getline(outfile, line);
    for (int i = 1; i < n; i++) {
      tempfile << times[i] << ' ';
    }
    tempfile << times[n] << endl;
  } else {
    string line;
    getline(outfile, line);       // check this later with diff
    tempfile << "Impossible." << endl;
  }

  return true;
}

int main(void)
{
  int N, M;

  while (infile >> N >> M) {
    do_case(N, M);
  }

  if (system("diff -HiBbw task.out task.tmp > /dev/null 2>&1") != 0) {
    vfyfile << "Probably giving starting times instead of impossible, or overflow" << endl;
    vfyfile << "WRONG ANSWER" << endl;
    return 2;
  }
  if (system("diff task.out task.tmp > /dev/null 2>&1") != 0) {
    vfyfile << "PRESENTATION ERROR" << endl;
    return 2;
  }
  
  vfyfile << "CORRECT!" << endl;

  return 0;
}
