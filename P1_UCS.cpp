#include "node.hpp"
#include <fstream>
// #include <set>
#include <algorithm>
#include <queue>

using std::string;
using std::cout;
using std::cerr;
using std::endl;
typedef std::pair<int, int> pii;

int main(int argc, char *argv[]){
    if(argc != 2){
        cerr << "Usage: ./UCS filepath" << endl;
        return -1;
    }
    int n, m;
    bool ans = false;
    string filename(argv[1]), tmp, s;
    std::ifstream inFile(filename);

    inFile >> n >> m;
    while (std::getline (inFile, tmp)) {
        s += tmp;
    }
    // use set
    // std::set<pii> vis;
    // use array
    std::vector<bool> vis((n + 1) * m + 5);
    std::vector<int> parent((n + 1) * m + 5);
    std::priority_queue<Node> pq;
    
    Node a(n, m);
    // use set
    // vis.insert(std::make_pair(1, 1));
    // use array
    
    if(a.canMove(0, 0, s)){
        pq.push(a);
        pii pos = a.getPos();
        vis[pos.first * m + pos.second] = 1;
    }
    
    while(!pq.empty()){
        Node now = pq.top();
        pii pos = now.getPos();
        if(pos.first == n && pos.second == m){
            cout << "Cost: " << now.getG() << endl;
            ans = true;
            break;
        }
        pq.pop();

        std::vector<Node> res = now.next(s);
        for(const Node &x : res){
            pii pos = x.getPos();
            pii pPos = x.getParentPos();
            // use set
            // if(vis.count(std::make_pair(pos.first, pos.second)))continue;
            // use array
            if(vis[pos.first * m + pos.second])continue;
            else {
                // printf("Pos: %d %d pPos: %d %d parent[%d] = %d\n", pos.first, pos.second, pPos.first, pPos.second, pos.first * m + pos.second, pPos.first * m + pPos.second);
                parent[pos.first * m + pos.second] = pPos.first * m + pPos.second;
                // use set
                // vis.insert(std::make_pair(pos.first, pos.second));
                // use array
                vis[pos.first * m + pos.second] = 1;
                pq.push(x);
            }
        }
    }
    if(ans){
        cout << "Sol for " << filename << ": " << endl;
        std::vector<pii> sol;
        int nowX = n, nowY = m;
        while(nowX != 1 || nowY != 1){
            sol.push_back(pii(nowX, nowY));
            int p = parent[nowX * m + nowY];
            nowY = (p % m == 0 ? m : p % m);
            nowX = (p - nowY) / m;
        }
        sol.push_back(pii(1, 1));
        std::reverse(sol.begin(), sol.end());
        for (const auto &x:sol)cout << x.first << ' ' << x.second << endl;
    }
    else cout << "No Solution!" << endl;
}