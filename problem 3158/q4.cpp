#include <cstdio>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;


/*ideia do algoritmo

se o custo de Biblioteca e mais barato que o de estrada, e mais barato construir uma biblioteca em cada cidade e satisfazer a propriedade universal de acesso - custo N*B

caso contrario, cada componente do grafo tera uma biblioteca, e a configuracao mais barata de estradas em cada componente, de acordo com a estrutura da arvore geradora minima, e igual ao numero de cidades - 1, assim ligando todas as cidades do componente na mesma arvore

custo = C*B + E*somatorio_{i=1}^{num componentes} v_i - 1, onde v_i e o numero de vertices do atual componente

simplificando para C*B + E*(N-C) = C*(B-E) + N*E

*/

int main() {  
    int instance_iterator = 1;
    int T;
    long long int custo;
    scanf("%d",&T);        
    while (instance_iterator <= T) {
      long long int N,M,B,E;
      scanf("%lld %lld %lld %lld",&N,&M,&B,&E);
      //cout << N<<M<<B<<E<<endl;
      vector<vector<int>> matriz(N+1);
    
      int X,Y;
      int road_iterator = 1;
      
   
      if(B <= E or M==0){
          while(road_iterator <= M){          
              scanf("%d %d",&X,&Y);
              road_iterator += 1;
          }
          custo = N*B;
      }else {
          while(road_iterator <= M){          
              scanf("%d %d",&X,&Y);
              matriz[X].push_back(Y);
              matriz[Y].push_back(X);
              road_iterator += 1;
          }
          //fazer bfs, achar n de componentes e quantos vertices em cada componente
          long long int componentes = 0;
          //nos_atual_componente;
          //int total_nos_visitados = 0;
          vector<bool> visitados(N+1,false); int inf_lim=1;
          while(true){
		  int i; bool busca_pendente = false;
		  queue<int> Q;  
		  for(int i = inf_lim; i<=N; i++)
                      if(!visitados[i]){ inf_lim=i+1;
                          Q.push(i);
                          componentes += 1;
                          busca_pendente = true; 
                          break;
                      }
                  if(!busca_pendente) break;
		  while (!Q.empty()) {
		      i = Q.front();//cout << i << endl;
		      Q.pop();
		      if (visitados[i]) continue;
		      visitados[i] = true;
		      //cout << visitados[1] << visitados[2] << visitados[3] << visitados[4] << endl;
		      for (const auto& p : matriz[i]) {
			  
			  //cout << i << "adj"<< p << endl;            
			  if(!visitados[p]){    
			      Q.push(p);
			  }
			  //cout << "Q.empty()" << Q.empty() << endl;
		      }  
		  } 
          }
          custo = componentes*B + E*(N - componentes);
      }  
      cout << custo << endl;
      instance_iterator++;

    }
    return 0;
}
