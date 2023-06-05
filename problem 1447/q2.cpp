#include "stdio.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <cmath>
using namespace std;

int normal_BFS(vector<vector<pair<int,int>>>& matriz, const int N) {  
  int i,dinheiro_gasto = 0;  
  queue<int> Q;  
  vector<bool> visitados;
  vector<int> d_custo;
  vector<int> antec;
  visitados = vector<bool>(N+1,false);
  d_custo = vector<int>(N+1,10000000);
  antec = vector<int>(N+1,0);
  Q.push(1);
  d_custo[1] = 0;
  while (!Q.empty()) {
      i = Q.front();
      Q.pop();
      if (visitados[i]) continue;
      visitados[i] = true;
      //cout << visitados[1] << visitados[2] << visitados[3] << visitados[4] << endl;
      //cout << d_custo[1] << d_custo[2] << d_custo[3] << d_custo[4] << endl;
      //cout << antec[1] << antec[2] << antec[3] << antec[4] << endl;
      for (const auto& p : matriz[i]) {
          int no = p.first;
          int custo_aresta = p.second;
          int d_custo_atual = d_custo[i]+custo_aresta;
          if(d_custo_atual < d_custo[no]){
              d_custo[no] = d_custo_atual;
              antec[no] = i;
          }
	  //cout << i << "adj"<< no << endl;            
	  if(!visitados[no]){    
	      Q.push(no);
	  }
          //cout << "Q.empty()" << Q.empty() << endl;
      }  
  }
  
  if(antec[N]==0) return 0;
  return d_custo[N];
}

int full_analysis(vector<vector<pair<int,int>>>& matriz, const int N, const int num_viagens,const int D, const int K) {  
  int i,dinheiro_gasto = 0;
  queue<int> Q;  
  vector<bool> visitados;
  vector<int> d_custo;
  vector<int> antec;
  int num_amigos_pendentes = D;
  /*nivel 1 = {1}
  ...
  nivel k = {vertices alcancados diretamente pelos vertices do nivel k-1, exceto os vertices ja descobertos nos niveis anteriores}

  se para cada nivel k, o numero de arestas que conecta este nivel com o nivel seguinte k+1 for menor que ceil(D/K), a solucao e impossivel
  alem disso, se o vertice N esta presente no mesmo nivel de outros vertices ou se o vertice N esta em nivel anterior ao ultimo nivel, basta que os vertices de mesmo nivel que N, alem dos vertices de niveis anteriores, que alcancem N diretamente, alcancem juntos o vertice N com ceil(D/K) arestas diferentes*/
  bool terminar = false;
  vector<int> nivel_k = {1};
  vector<int> nivel_k_1 = {};
  vector<bool> descobertos(N+1,false); 
  vector<bool> descobertos_k_1(N+1,false); 
  descobertos[1] = true;
  int arestas_entre_niveis = 0;
  int arestas_conectam_N = 0;
  int niveis = 1;
  while(true){
	  for (const auto& i : nivel_k)
		  for (const auto& p : matriz[i]) {		      
			  int no = p.first;
			  if(no == N){
				  arestas_conectam_N += 1;
				  terminar = true;
			  }
			  if(descobertos[no] == false){
				  arestas_entre_niveis += 1;
				  if(descobertos_k_1[no] == false){
				  nivel_k_1.push_back(no);
					  descobertos_k_1[no] = true;
				  }
			  }
		  }
	  for (const auto& i : nivel_k_1)
		  descobertos[i] = true;

	  //cout << "num_viagens " << num_viagens << " arestas_entre_niveis " << niveis << " e " << niveis+1 << ": " << arestas_entre_niveis << endl;
	  niveis += 2;

	  if(arestas_entre_niveis < num_viagens) return 0;

	  if(terminar){
		  for (const auto& i : nivel_k_1)
			  for (const auto& p : matriz[i])
				  if(p.first == N)
					  arestas_conectam_N += 1;      
				  
		  if(arestas_conectam_N < num_viagens)  return 0; 
		  
		  break;
	  }	                    

	  arestas_entre_niveis = 0;
	  nivel_k = nivel_k_1;
	  nivel_k_1 = {};  
  }
  //cout << "num_viagens " << num_viagens << " arestas_conectam_N " << arestas_conectam_N << endl;
  
  int index,no_atual = 1, proximo_no, custo_caminho = 0, custo_total = 0, custo_total_minimo = 10000000;
  vector<bool> vertices_usados(N+1,false);
  antec = vector<int>(N+1,0);  
  vector<int> indice_aresta = vector<int>(N+1,1);  
  vector<vector<bool>> arestas_desativadas(N+1,vector<bool>(N+1,false));
  
  while(true){
        vertices_usados[no_atual] = true;
        proximo_no = 0;
        index = 0;
        //cout << "no atual: " << no_atual << " ";
	for (const auto& p : matriz[no_atual]) {		     
                index += 1; 

                if(index == indice_aresta[no_atual]){
                    if(vertices_usados[p.first]){ 
		            indice_aresta[no_atual]++;
                            
		            //cout << "vertices_usados[" << p.first << "] = true,  indice: " << index << " indice_aresta[" << no_atual << "]:" << indice_aresta[no_atual] << endl;
                            continue;

		    }
                    proximo_no = p.first;
		    antec[proximo_no] = no_atual;
                    indice_aresta[no_atual] += 1;
		    //cout << "index == indice_aresta["<<no_atual<<"] proximo_no: " << p.first << " antec["<<proximo_no<<"]: "<<no_atual <<" indice_aresta["<<no_atual<<"]: "<< indice_aresta[no_atual] << endl;
                    break;
		}
	}
	if(proximo_no == 0){
                //cout << "proximo_no == 0 "; 
		if(no_atual == 1) {
			//cout << "no_atual == 1" << endl; 
			break;
		}
                vertices_usados[no_atual] = false;
                indice_aresta[no_atual] = 1;
                //cout << " vertices_usados["<<no_atual<<"] = false indice_aresta["<<no_atual<<"] = 1 no_atual = "<<antec[no_atual]<<endl;
		no_atual = antec[no_atual];
        } else {
                //cout<<"proximo_no != 0 ";
		no_atual = proximo_no;
                //cout << "no_atual = "<<no_atual<<endl; 
		if(no_atual == N){
                        //cout<<"no_atual == N";
			//arestas_desativadas.resize(N+1,vector<bool>(N+1,false)); 
                        for (i = 1; i<= N; i++)
                	    for (int j=1; j<=N; j++)
                                arestas_desativadas[i][j] = false;
			custo_caminho = 0;
			
			//percorrer antecessores dos vertices ate chegar a 1 e somar custo do caminho
			while(no_atual != 1){
				proximo_no = antec[no_atual];
				for (const auto& p : matriz[proximo_no])	
					if(p.first == no_atual){
						custo_caminho += p.second;
						arestas_desativadas[proximo_no][no_atual] = true;
						break;
					}
			        no_atual = proximo_no;
                                //cout<<" "<<no_atual<<" ";
			}   
                        //cout << "custo_caminho: " << custo_caminho << endl;
                        custo_total = custo_caminho*min(D,K); num_amigos_pendentes= D- K;
                        vector<bool> visitados1(N+1,false);
                        vector<int> d_custo1(N+1,10000000);
                        vector<int> antec1(N+1,0);
                        queue<int> Q1;  
                        int viagem_atual = 2;
			while(viagem_atual<=num_viagens){
				  visitados1 = vector<bool>(N+1,false);
				  d_custo1 = vector<int>(N+1,10000000);
				  antec1 = vector<int>(N+1,0);
				  Q1.push(1);
				  d_custo1[1] = 0;
				  while (!Q1.empty()) {
				      i = Q1.front();
				      Q1.pop();
				      if (visitados1[i]) continue;
				      visitados1[i] = true;
				      //cout << visitados1[1] << visitados1[2] << visitados1[3] << visitados1[4] << endl;
				      //cout << d_custo1[1] << d_custo1[2] << d_custo1[3] << d_custo1[4] << endl;
				      //cout << antec1[1] << antec1[2] << antec1[3] << antec1[4] << endl;
				      for (const auto& p : matriz[i]) {
					  int no = p.first;
					  //cout<<"arestas_desativadas["<<i<<"]["<<no<<"] = "<<arestas_desativadas[i][no]<<endl;
                                          if(!arestas_desativadas[i][no]){
		                                  int custo_aresta = p.second;
						  int d_custo_atual = d_custo1[i]+custo_aresta;
						  if(d_custo_atual < d_custo1[no]){
						      d_custo1[no] = d_custo_atual;
						      antec1[no] = i; 
                                                      //cout << i << "adj"<< no << endl; 
						  }
							     
						  if(!visitados1[no]){    
						      Q1.push(no);
						  }
						  //cout << "Q1.empty()" << Q1.empty() << endl;
                                          }
				      }  
				  }
				  
				  if(antec1[N]==0) break;
				  
				  custo_total += d_custo1[N]*min(num_amigos_pendentes,K); num_amigos_pendentes-= K;
				  //cout << "custo_caminho: " << d_custo1[N] <<" custo total: "<<custo_total << endl;
				  int no_atual = N;
				  while(no_atual != 1){
			              int antec_atual = antec1[no_atual];
				      for (auto it = matriz[antec_atual].begin(); it != matriz[antec_atual].end(); ++it) {
				          if (it->first == no_atual) {
					      arestas_desativadas[antec_atual][no_atual] = true;
					      //cout << "erase " << antec_atual << "adj" << no_atual << endl;                         
					      break;
				          }
				      }
				      no_atual = antec_atual;
				  }
				  
                                  viagem_atual += 1;
			}
                        if(custo_total < custo_total_minimo) custo_total_minimo = custo_total;
                        no_atual = antec[N];
                        //cout << endl;
                        //cout << "custo_total: " << custo_total << endl;
                        //cout<<" no_atual = "<<no_atual<<endl;
			//aqui nos iremos rodar um bfs pra achar o caminho minimo sem passar pelas arestas desativadas, anotar o custo do caminho e desativando as arestas percorridas
            //repetindo os passos, ate ter percorrido tantos caminhos quanto o valor num_viagens, que e ceil(D/K)			
		}
        
        }
	  
  } 
  return custo_total_minimo;
  

}

/*ideia do algoritmo
dinheiro_gasto = 0

while(true)
    fazer busca do caminho mais barato
    registrar antecedente de cada vertice e custo total do caminho
    quando achar o caminho, ir do no final, de antecedente em antecedente, até o nó inicial, apagando as arestas percorridas, pois uma rota so e usada uma vez

    se num_amigos <= num_assentos, 
        dinheiro_gasto += custo total do caminho encontrado
        break
    c.c.,
        num_amigos -= num_assentos
lendo as mensagens do forum do link
descobri que essa ideia nao e suficiente para se descobrir a minima quantia de dinheiro necessaria pra viajar de 1 a N, em ceil(D/K) viagens, percorrendo arestas diferentes em cada viagem

nova ideia
passo 0 - verificacao se a solucao e impossivel
	vamos considerar os vertices organizados em niveis, da seguinte forma:
	nivel 1 = {1}
	...
	nivel k = {vertices alcancados diretamente pelos vertices do nivel k-1, exceto os vertices ja descobertos nos niveis anteriores}

	se para cada nivel k, o numero de arestas que conecta este nivel com o nivel seguinte k+1 for menor que ceil(D/K), a solucao e impossivel
	alem disso, se o vertice N esta presente no mesmo nivel de outros vertices ou se o vertice N esta em nivel anterior ao ultimo nivel, basta que os vertices de mesmo nivel que N, alem dos vertices de niveis anteriores, que alcancem N diretamente, alcancem juntos o vertice N com ceil(D/K) arestas diferentes
	
passo 1
	se ceil(D/K) = 1, 
		procurar custo do caminho minimo e retornar
	c.c.,
		1.1 gerar todos os caminhos possiveis de 1 a N, que nao repitam vertices.
		ex: D = 20; K = 10; 
		caminho 1 a 4;
		1 adj a 2,3,4;
		4 adj a 2,3
		
		ceil(20/10) = 2
		nivel 1 = {1} nivel 2 = {2,3,4}
		nivel 1 alcanca nivel 2 com 3 arestas diferentes
		vertices do nivel 2 alcancam o vertice 4 com 2 arestas diferentes
		vertice de nivel anterior 1 alcanca 4 diretamente, total 3 arestas alcancam N
		assim, o problema teria solucao mesmo se D fosse 30 e K 10, pois ceil(30/10) = 3
		
		caminhos = 
		1 _ N = 
		1-4 ou
		1-{2,3}-4
		
		1.2 para os caminhos possiveis, ordenar por custo ascendente 
		1) 1 4 / 1
		2) 1 2 4 / 7
		3) 1 3 4 / 7
		estrutura de dados: {list<pair<int,int>> caminho, int custo}
		
		passo 1.3 iterar do primeiro item (1) até o ultimo (caminho P) - ceil(D/K)+1, nesse caso de 1 a 3-2+1 (1 a 2)
		passo 1.4 escolher ceil(D/K)-1 elementos priorizando por menor custo, mas sem repetir nenhum vertice do 1º caminho escolhido; e ao escolher algum caminho intermediario, para os proximos, nao escolher os que tenham aresta em comum com o intermediario, fazendo assim para todos os outros
		passo 1.5 se a escolha for possivel, salvar combinacao de caminho e somar custo total
		passo 1.6 repetir os passos 1.3 a 1.5, mas considerando os caminhos possiveis, exceto o primeiro; e ao terminar os 3 passos, fazer novamente, desconsiderando os 2 primeiros caminhos ordenados com custo minimo
		fazer assim ate obter todas as combinacoes de caminhos com seu custo total armazendo
		passo 1.7 escolher a combinacao de caminhos com menor custo total, retornar valor
		

*/

int main() {
  int line_number = 0;
  int instance_iterator = 1;
  int N, M;
  while (scanf("%d %d",&N,&M) != EOF) {        
    //int num_args = scanf("%d %d",&N,&M);
    int end_test_case = line_number + M;    
    line_number += 1;
    vector<vector<pair<int,int>>> matriz(N+1);
    while (line_number <= end_test_case) {
      int A, B, C;
      scanf("%d %d %d",&A,&B,&C);
      matriz[A].push_back(make_pair(B,C));
      matriz[B].push_back(make_pair(A,C));
      
      line_number += 1;
    }
    int D,K;
    scanf("%d %d",&D,&K);
    int numero_viagens = ceil((float)D/K);
    int dinheiro_gasto = 0;
    if(numero_viagens == 1)
        dinheiro_gasto = normal_BFS(matriz,N) * D;
    else
        dinheiro_gasto = full_analysis(matriz,N,numero_viagens,D,K);
    cout << "Instancia " << instance_iterator << endl;  
    instance_iterator++;
    
    if(dinheiro_gasto != 0)
      cout << dinheiro_gasto << endl << endl;
    else
      cout << "impossivel" << endl << endl;
  }
  return 0;
}
