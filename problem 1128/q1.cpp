#include "stdio.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
using namespace std;

/*
o algoritmo se baseia na seguinte ideia:
- Se o no 1 conecta os demais
- basta que todos os outros conectem a 1
para isso, no primeiro rodo um BFS normal, o tamanho do vetor de visitados deve ser o numero de vertices
para o segundo ponto, rodo um BFS, só que ao inves de detectar se o no 1 conecta um no v, eu verifico quais nos v1,v2,..,vn conectam a 1 e coloco estes na fila para serem visitados. Ao final o vetor de visitados deve ter tamanho do num de vertices
*/

bool BFS(int i, vector<vector<int>>& matriz, int N) {
  vector<bool> visitados(N+1,false);
  unsigned int vecSize = 0;
  queue<int> Q;
  Q.push(i);

  while (!Q.empty()) {
      i = Q.front();
      Q.pop();
      visitados[i] = true;
      vecSize += 1;
      if(vecSize == N)
          return true;
      //cout << visitados[1] << visitados[2] << visitados[3] << visitados[4] << endl;
      for (const auto& p : matriz[i]) {          
          //cout << i << "adj"<< node << endl;            
          if(!visitados[p]){    
              Q.push(p);
          }
      }       
  }
  return false;
}

bool reverse_BFS(int i, vector<vector<int>>& matriz, int N) {
  vector<int> visitados(N+1,false);
  unsigned int vecSize = 0;
  queue<int> Q;
  Q.push(i);

  while (!Q.empty()) {
      int u = Q.front();
      Q.pop();
      visitados[u] = true;
      vecSize += 1;
      if(vecSize == N)
          return true;
      //cout << visitados[1] << visitados[2] << visitados[3] << visitados[4] << endl;      
      for(int i = 1; i <= N; i++){
          for (const auto& p : matriz[i]) {
              if(p==u){
                  //cout << i << "adj"<< u << endl;            
                  if(!visitados[i]){    
                      Q.push(i);
                  }
              }
          }
      }  
  }
  return false;
}

int main() {
  int line_number = 0;
  while (true) {    
    int N, M;
    scanf("%d %d",&N,&M);
    if (N == 0 and M == 0) {
      return 0;
    }
    int end_test_case = line_number + M;    
    line_number += 1;
    vector<vector<int>> matriz(N+1);
    while (line_number <= end_test_case) {
      int V, W, P;
      scanf("%d %d %d",&V,&W,&P);
      matriz[V].push_back(W);
      if (P == 2) {
        matriz[W].push_back(V);
      }
      line_number += 1;
    }
      
    if(BFS(1,matriz,N) and reverse_BFS(1,matriz,N))
      cout << 1 << endl;
    else
      cout << 0 << endl;
   
  }
}
