#include <iostream>
#include <deque>
using namespace std;

struct Edge {
    int v;
    int flow;
    int capacity;
    int reverse_edge;
};

class Graph {
public:
    explicit Graph(int V)
    {
        adj = new vector<Edge>[V];
        this->vs = V;
        levels = new int[V];
    }

    void addEdge(int u, int v, int C)
    {
        // стартовый поток
        Edge forward { v, 0, C, (int)adj[v].size() };
        // изначальный остаточный путь
        Edge reverse { u, 0, 0, (int)adj[u].size() };

        adj[u].push_back(forward);
        adj[v].push_back(reverse);
    }

    // BFS для понимания, есть ли еще какой-то путь от истока к стоку и расставления уровней вершин
    bool BFSlevels(int s, int t) {
        for (int i = 0; i < vs; i++)
        {
            levels[i] = -1;
        }

        levels[s] = 0;

        std::deque<int> visited;
        visited.push_back(s);

        vector<Edge>::iterator i;
        while (!visited.empty()) {
            int u = visited.front();
            visited.pop_front();

            for (i = adj[u].begin(); i != adj[u].end(); i++) {
                Edge& e = *i;
                if (levels[e.v] < 0 && e.flow < e.capacity) {
                    levels[e.v] = levels[u] + 1;

                    visited.push_back(e.v);
                }
            }
        }

        // если в для t уровень будет -1, то из истока в сток попасть не получится
        return levels[t] >= 0;
    }

    // DFS для поиска увеличивающегося пути в графе + поиск блокирующего потока
    int DFSflow(int u, int flow, int t, int visited[]) {
        if (u == t)
            return flow;

        for (int i = visited[u]; i < adj[u].size(); i++) {
            Edge& e = adj[u][i];

            if (levels[e.v] == levels[u] + 1 && e.flow < e.capacity) {
                int curr_flow = min(flow, e.capacity - e.flow); // поиск доступного потока

                int temp_flow = DFSflow(e.v, curr_flow, t, visited);

                if (temp_flow > 0) { // удалось ли отправить поток
                    e.flow += temp_flow;

                    // обновление остаточного пути
                    adj[e.v][e.reverse_edge].flow -= temp_flow;
                    return temp_flow;
                }
            }
        }

        return 0;
    }

    int Dinic(int s, int t) {
        if (s == t)
            return -1;

        int result = 0;

        // проверка, что из s в t все еще есть путь
        while (BFSlevels(s, t)) {
            // посещенные ребра. в visited[i] i - это вершина-начала текущего ребра
            int* visited = new int[vs + 1] {0};

            while (int flow = DFSflow(s, 1000000, t, visited)) {
                result += flow;
            }
        }

        return result;
    }

private:
    int vs;
    int* levels;

    vector<Edge>* adj;
};

int main()
{
    Graph graph(6);

    graph.addEdge(0, 1, 5);
    graph.addEdge(0, 2, 5);
    graph.addEdge(1, 3, 2 );
    graph.addEdge(1, 4, 4 );
    graph.addEdge(1, 2, 1 );
    graph.addEdge(2, 4, 4 );
    graph.addEdge(3, 5, 5 );
//    graph.addEdge(4, 3, 3 );
    graph.addEdge(4, 5, 10 );

    cout << graph.Dinic(0, 5);
    return 0;
}
