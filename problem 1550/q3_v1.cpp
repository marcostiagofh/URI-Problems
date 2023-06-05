#include "stdio.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void somar_1(vector<int>& arr_num1, int& start_num1, vector<int>& inv_arr_num1, int& num1, int& inv_num1){
    num1 += 1;
    int aux = num1;
    int i = 4;
    while(num1 > 0){
        arr_num1[i] = num1%10;        
        num1 -= num1%10;
        num1 /= 10;
        i -= 1;
    }
    num1 = aux;
    start_num1 = i+1;
    int pot_10 = 1;
    inv_num1 = 0;
    for(i = 4; i>=start_num1; i--){
        inv_arr_num1[i] = arr_num1[start_num1+(4-i)];
        inv_num1 += inv_arr_num1[i]*pot_10;
        pot_10 *= 10;
    }
     
}

int subtrair(vector<int>& arr_num2, int start_num2, vector<int>& arr_num1, int start_num1){
    int common_start = min(start_num1,start_num2);
    int pot_10 = 1, res = 0;
    for(int i = 4; i >= common_start; i--){
        if(arr_num1[i] > arr_num2[i] and arr_num2[i-1] >= 1){
            res += pot_10 * (10 + arr_num2[i] - arr_num1[i]);
            arr_num2[i-1] -= 1;
        } else {
            res += pot_10 * (arr_num2[i] - arr_num1[i]);
        }
        pot_10 *= 10;
    }
    return res;        
}

bool comp_arr_eq(vector<int>& arr_num1, int start_num1, vector<int>& arr_num2,int start_num2){
    int common_start = min(start_num1,start_num2);
    for(int i = common_start; i <= 4; i++)
        if(arr_num1[i]!=arr_num2[i])
            return false;

    return true;
}

bool check_pallindrome(vector<int>& arr_num1,int start_num1){
    int final_position = (int)(4+start_num1)/2;
    for(int i = start_num1; i <= final_position; i++)
        if(arr_num1[i] != arr_num1[4-(i-start_num1)])
            return false;

    return true;
}

void inverter(vector<int>& arr_num1, int start_num1, vector<int>& inv_arr_num1, int& num1, int& inv_num1){
    int aux, final_position = (int)(4+start_num1)/2;
    for(int i = start_num1; i <= final_position; i++){
        aux = arr_num1[i];
        arr_num1[i] = arr_num1[4-(i-start_num1)];
        arr_num1[4-(i-start_num1)] = aux;
    }
    aux = num1;
    num1 = inv_num1;
    inv_num1 = aux;
}

/*ideia do algoritmo
ler entrada
num1
num2
criar arr arr_num1 a partir de num1
criar inv_arr_num1
criar arr arr_num2 a partir de num2
criar inv_arr_num2
bool num1_pallindrome = false
bool num2_pallindrome = false
char acao //I - inverter; S - somar + 1
while num1 != num 2:
    custo_minimo = 10000
    inv_arr_num1 = inverter(arr_num1)
    inv_arr_num2 = inverter(arr_num2)
    num1_pallindrome = check_pallindrome(arr_num1)
    num2_pallindrome = check_pallindrome(arr_num2)
    
    if(arr_num1[size-1] != 0) {
    	acao = S;
    } else{
	D = subtrair(arr_num2,arr_num1)

	if(D > 0 and D < custo_minimo){custo_minimo = D; acao = S;}

	if(!num1_pallindrome and !num2_pallindrome) {
		IDI = subtrair(inv_arr_num2,inv_arr_num1)
		if(IDI > 0 and IDI < custo_minimo) {custo_minimo = IDI; acao = I;}
	} else if(!num1_pallindrome) {
		ID = subtrair(arr_num2,inv_arr_num1)
		if(ID > 0 and ID < custo_minimo) {custo_minimo = ID; acao = I;}
	} else if(!num2_pallindrome) {
		DI = subtrair(inv_arr_num2,arr_num1)
		if(DI > 0 and DI < custo_minimo) {custo_minimo = DI; acao = S;}

	}
    
    }   	

*/

int main() {
    int line_number = 0;
    int instance_iterator = 1;
    int T;
    scanf("%d",&T);
    line_number += 1;
    while (instance_iterator <= T) {
        //ler entrada
	int A, B;
        scanf("%d %d",&A,&B);
      
        int pot_10, num1 = A, num2 = B, inv_num1=0, inv_num2=0;

	//criar arr arr_num1 e inv_arr_num1 a partir de num1
        vector<int> arr_num1(5,0);
        int index = 4;
        while(num1 > 0){
            arr_num1[index] = num1%10;
            num1 -= num1%10;
            num1 /= 10;
            index -= 1;
        }
        int start_num1 = index+1; num1 = A;
        vector<int> inv_arr_num1(5,0); pot_10 = 1;
        for(int i = start_num1; i < 5; i++){
            inv_arr_num1[4-(i-start_num1)] = arr_num1[i];
            inv_num1 += arr_num1[i]*pot_10;
            pot_10 *= 10;
        }
        //criar arr arr_num2 e inv_arr_num2 a partir de num2
	vector<int> arr_num2(5,0);
        index = 4;
        while(num2 > 0){
            arr_num2[index] = num2%10;
            num2 -= num2%10;
            num2 /= 10;
            index -= 1;
        }
        int start_num2 = index+1; num2 = B;
        vector<int> inv_arr_num2(5,0); pot_10 = 1;
        for(int i = start_num2; i < 5; i++){
            inv_arr_num2[4-(i-start_num2)] = arr_num2[i];
            inv_num2 += arr_num2[i]*pot_10;
            pot_10 *= 10;
        }

        /*for(int i = start_num1; i < 5; i++)
            cout << arr_num1[i];
        cout << endl;

        for(int i = start_num1; i < 5; i++)
            cout << inv_arr_num1[i];
        cout << endl;

        for(int i = start_num2; i < 5; i++)
            cout << arr_num2[i];
        cout << endl;

        for(int i = start_num2; i < 5; i++)
            cout << inv_arr_num2[i];
        cout << endl;*/

        //cout << num1 << " " << inv_num1 << " " << num2 << " " << inv_num2 << endl;

        bool num1_pallindrome;
	bool num2_pallindrome = num2 == inv_num2;

	char acao; //I - inverter; S - somar + 1
        int passos = 0;
        int D,ID,IDI,DI; //I antes do D e num1 invertido, depois do D e num2 invertido, D e distancia entre os 2
	while(num1 != num2){
	    int custo_minimo = 10000;
	    num1_pallindrome = num1 == inv_num1;
	    //cout << "num1_pallindrome: " << num1_pallindrome << " ";

	    if(arr_num1[4] == 0) {
	    	acao = 'S';
	    } else{
		D = num2 - num1; //cout << "D: " << D << " ";

		if(D >= 0 and D < custo_minimo){custo_minimo = D; acao = 'S';}

		if(!num1_pallindrome and !num2_pallindrome) {
			IDI = inv_num2-inv_num1; //cout << "IDI: " << IDI << " "; 
			if(IDI >= 0 and IDI < custo_minimo) {custo_minimo = IDI; acao = 'I';}
		} 
                if(!num1_pallindrome) {
			ID = num2-inv_num1; //cout << "ID: " << ID << " "; 
			if(ID >= 0 and ID < custo_minimo) {custo_minimo = ID; acao = 'I';}
		} 
                if(!num2_pallindrome) {
			DI = inv_num2-num1; //cout << "DI: " << DI << " "; 
			if(DI >= 0 and DI < custo_minimo) {custo_minimo = DI; acao = 'S';}

		}
	    
	    }  
            //cout << "acao: " << acao << endl;
            if(acao == 'S'){
                somar_1(arr_num1,start_num1,inv_arr_num1,num1,inv_num1);
            }else{
                inverter(arr_num1,start_num1,inv_arr_num1,num1,inv_num1);
            }
            passos += 1;
            
            /*cout << num1 << " " << inv_num1 << " " << num2 << " " << inv_num2 << endl;
            
            for(int i = start_num1; i < 5; i++)
	        cout << arr_num1[i];
	    cout << endl;

	    for(int i = start_num1; i < 5; i++)
	        cout << inv_arr_num1[i];
	    cout << endl;      */
      } 	
      printf("%d\n",passos);
      instance_iterator += 1;
    }
    return 0;
  
  //return 0;
}
