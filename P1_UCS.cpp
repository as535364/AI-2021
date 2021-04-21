#include "node.hpp"
#include <fstream>
#include <algorithm>
#include <queue>
#include <tuple>
#include <map>
#define X first
#define Y second

using std::string;
using std::cout;
using std::cerr;
using std::endl;
typedef std::pair<int, int> pii;
typedef std::tuple<int, int, int> Tiii;


int main(int argc, char *argv[]){
    if(argc != 2){
        cerr << "Usage: " << argv[0] << " filepath" << endl;
        return -1;
    }
    int n, m;
    bool ans = false;
    std::map<pii, int> costs;
    string filename(argv[1]), tmp, s;
    std::ifstream inFile(filename);

    inFile >> n >> m;
    while (std::getline (inFile, tmp)) {
        s += tmp;
    }

    std::vector<bool> vis((n + 1) * m + 5);
    std::vector<int> parent((n + 1) * m + 5);
    std::priority_queue<Tiii, std::vector<Tiii>, std::greater<>> pq;
    
    Node a(n, m);
   
    if(a.canMove(0, 0, s)){
        pq.push(Tiii(0, 1 , 1));
        costs[pii(1, 1)] = 0;
        pii pos = a.getPos();
        vis[pos.X * m + pos.Y] = true;
    }
    
    while(!pq.empty()){
        Tiii pqNow = pq.top();
        Node now = Node(n, m, std::get<1>(pqNow), std::get<2>(pqNow));
        pii pos = now.getPos();
        if(pos.X == n && pos.Y == m){
            cout << "Cost: " << costs[pii(n, m)] << endl;
            ans = true;
            break;
        }
        pq.pop();

        std::vector<std::pair<int, Node>> res = now.nextWithCost(s);
        for(const auto &nextNode : res){
            int spendCost;
            Node x(0, 0);
            std::tie(spendCost, x) = nextNode;
            pii nextPos = x.getPos();
            pii pPos = pos;

            if(vis[nextPos.X * m + nextPos.Y] && costs[pii(nextPos.X, nextPos.Y)] > costs[pii(pos.X, pos.Y)] + spendCost){
                // Visited
                costs[pii(nextPos.X, nextPos.Y)] = costs[pii(pos.X, pos.Y)] + spendCost;
                parent[nextPos.X * m + nextPos.Y] = pPos.X * m + pPos.Y;
                pq.push(Tiii(costs[pii(nextPos.X, nextPos.Y)], nextPos.X, nextPos.Y));
            }
            else if(!vis[nextPos.X * m + nextPos.Y]){
                // Not visited
                costs[pii(nextPos.X, nextPos.Y)] = costs[pii(pos.X, pos.Y)] + spendCost;
                parent[nextPos.X * m + nextPos.Y] = pPos.X * m + pPos.Y;
                vis[nextPos.X * m + nextPos.Y] = true;
                pq.push(Tiii(costs[pii(nextPos.X, nextPos.Y)], nextPos.X, nextPos.Y));
            }
        }
    }
    if(ans){
        cout << "Sol for " << filename << ": " << endl;
        std::vector<pii> sol;
        int nowX = n, nowY = m;
        while(nowX != 1 || nowY != 1){
            sol.emplace_back(pii(nowX, nowY));
            int p = parent[nowX * m + nowY];
            nowY = (p % m == 0 ? m : p % m);
            nowX = (p - nowY) / m;
        }
        sol.emplace_back(pii(1, 1));
        std::reverse(sol.begin(), sol.end());
        for (const auto &x:sol)cout << x.X << ' ' << x.Y << endl;
    }
    else cout << "No Solution!" << endl;
}