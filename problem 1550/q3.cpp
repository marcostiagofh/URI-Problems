#include "stdio.h"
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <tgmath.h>
using namespace std;

int T, A, B, steps[10000];

int main() {
    int line_number = 0;
    int instance_iterator = 1;
    int T;
    scanf("%d",&T);
    while (instance_iterator <= T) {
        //ler entrada
	int A, B;
        scanf("%d %d",&A,&B);
      
        int passos;

        memset(steps, -1, sizeof(steps));
        queue<int> q;
        q.push(A);
        steps[A] = 0;
        while (!q.empty()) {
            int cur = q.front(); q.pop();
            if (cur == B){ passos = steps[cur]; break;}
            int next1 = cur + 1;
            if (steps[next1] == -1) {
                steps[next1] = steps[cur] + 1;
                q.push(next1);
            }
            int inv_num = 0, num = cur;
            while (num > 0) {
	        inv_num = inv_num * 10 + num % 10;
	        num /= 10;
            }   
            if (steps[inv_num] == -1) {
                steps[inv_num] = steps[cur] + 1;
                q.push(inv_num);
            }
       }   
      	
      printf("%d\n",passos);
      instance_iterator += 1;
    }
    return 0;
}
