#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 10010;
int T, A, B, steps[MAXN], reverse_num[MAXN];

int reverse(int num) {
    int rev = 0;
    while (num > 0) {
        rev = rev * 10 + num % 10;
        num /= 10;
    }
    return rev;
}

int bfs(int start, int end) {
    memset(steps, -1, sizeof(steps));
    queue<int> q;
    q.push(start);
    steps[start] = 0;
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        if (cur == end) return steps[cur];
        int next1 = cur + 1;
        if (steps[next1] == -1) {
            steps[next1] = steps[cur] + 1;
            q.push(next1);
        }
        int rev = reverse(cur);
        if (steps[rev] == -1) {
            steps[rev] = steps[cur] + 1;
            q.push(rev);
        }
    }
    return -1;
}

int main() {
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        scanf("%d%d", &A, &B);
        printf("%d\n", bfs(A, B));
    }
    return 0;
}

