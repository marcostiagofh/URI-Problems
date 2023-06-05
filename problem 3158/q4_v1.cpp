#include <cstdio>
#include <vector>
#include <queue>

int main() {
    int T;
    std::scanf("%d", &T);
    while (T--) {
        long long int N, M, B, E;
        std::scanf("%lld %lld %lld %lld", &N, &M, &B, &E);
        std::vector<std::vector<int>> matriz(N + 1);
        for (int i = 0; i < M; i++) {
            int X, Y;
            std::scanf("%d %d", &X, &Y);
            matriz[X].emplace_back(Y);
            matriz[Y].emplace_back(X);
        }
        if (B < E) {
            std::printf("%d\n", N * B);
        } else {
            long long int componentes = 0;
            int total_nos_visitados = 0;
            std::vector<bool> visitados(N + 1, false);
            while (total_nos_visitados < N) {
                int i;
                std::queue<int> Q;
                for (int j = 1; j <= N; j++) {
                    if (!visitados[j]) {
                        Q.push(j);
                        componentes++;
                        break;
                    }
                }
                while (!Q.empty()) {
                    i = Q.front();
                    Q.pop();
                    if (visitados[i]) {
                        continue;
                    }
                    visitados[i] = true;
                    total_nos_visitados++;
                    for (const auto& p : matriz[i]) {
                        if (!visitados[p]) {
                            Q.push(p);
                        }
                    }
                }
            }
            std::printf("%d\n", componentes * B + E * (total_nos_visitados - componentes));
        }
    }
    return 0;
}

