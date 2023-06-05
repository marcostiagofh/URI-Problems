'''>>tipo de estrutura de dados
    intersecao{
	    int i;
	}
	rua{
	    intersecao i1, i2;
		int tipo_via; //1 ou 2
	}
	
N - numero de intersecoes
M - numero de ruas

criar matriz M[i][f] = P, onde i,j entre 1 e N e P e 0 (nao ha rua de i pra j) ou 1 (ha rua de i pra j)
'''

def BFS(f,matriz,N,C):
  achou_caminho = False
  Q = [f]
  while len(Q) > 0:
      u = Q.pop()
      v = 1
      while v <= N:
        if matriz[u][v] == 1 and u != v:
          if v in C:
              return True
              break
          Q.append(v)
        v += 1
  return False


#>>funcionamento do programa
#processar entrada
#text = input()
#lines = text.splitlines()
line_number = 0

#enquanto M !=0 e N != 0
while True:
    line = input()
    if line == '0 0':
        break
    #ler primeira linha, gravar valores N e M
    line = line.split(' ')
    N,M = [int(x) for x in line]
    #print(N,M)
    
    #testar N entre 2 e 2000, inclusive; caso contrario, falha
		#testar M entre 2 e N*(N-1)/2, inclusive; caso contrario, falha
    end_test_case = line_number+M
    
    if N < 2 or N > 2000 or M < 2 or M > N*(N-1)/2:
      print(0)
      line_number = end_test_case + 1

    else:      
      #avancar pra proxima linha
      line_number += 1

      matriz = [[0 for i in range(N+2)]for i in range(N+1)]

      #enquanto le as proximas M linhas do caso de teste,
      while line_number <= end_test_case:

        #gravar valores V, W e P
        line = input().split(' ')
        V,W,P = [int(x) for x in line]
        #print(V,W,P)   

        #criar rua que sai da intersecao V para a W, de via unica (se P = 1) ou mao dupla se (P = 2)
        matriz[V][W] = 1
        if P == 2:
          matriz[W][V] = 1
        
        #avancar pra proxima linha
        line_number += 1
      '''i = 1
      while i<= N:
        print(M[i][1:N+1])
        i += 1'''
      '''
      finalizou leitura do caso de teste, iniciar busca de arvore geradora	
      implem. algoritmo generic-mst, com modificacao:
      se houver uma aresta u->v de mao unica, usar bfs pra achar caminho que conecte v a u; se nao achar, falha
      '''

      conexo = True #e True se as intersecoes sao conexas como inicio ou fim de um caminho para todas as outras
      inters = 1 #intersecao inicial analisada
      C = [1] #conj. dos componentes conexos

      while len(C) < N:
        tem_adj = 0 #=1 se inters tem adjacencia
        #para f entre 1 e N:
        f = 1
        while f <= N:
          if f != inters and f not in C and matriz[inters][f] == 1:
            tem_adj = 1
            if matriz[f][inters] == 0 and BFS(f,matriz,N,C) == False:
              conexo = False
              break

            C.append(f)
            inters = f
            break
          f += 1
        if conexo == False:
          break
        if tem_adj == 0:
          if inters == 1:
            conexo = False
            break
          else:
            #para antec entre 1 e N:
            antec = 1
            while antec <= N:
              if antec != inters and matriz[antec][inters] == 1 and antec in C:
                inters = antec
                break
              antec += 1
      if conexo:
        print(1)
      else:
        print(0)

