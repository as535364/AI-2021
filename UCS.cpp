#include "board.hpp"
#include <fstream>
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

    std::vector<bool> vis((n + 1) * m + 5);
    std::vector<int> parent((n + 1) * m + 5);
    std::priority_queue<Board> pq;
    Board a(n, m); vis[1 * m + 1] = 1;
    if(a.canMove(0, 0, s))pq.push(a);
    
    while(!pq.empty()){
        Board now = pq.top();
        if(now.getPos().first == n && now.getPos().second == m){
            cout << "Cost: " << now.getG() << endl;
            ans = true;
            break;
        }
        pq.pop();

        std::vector<Board> res = now.next(s);
        for(const Board &x : res){
            pii pos = x.getPos();
            pii pPos = x.getParentPos();
            if(vis[pos.first * m + pos.second])continue;
            else {
                // printf("Pos: %d %d pPos: %d %d parent[%d] = %d\n", pos.first, pos.second, pPos.first, pPos.second, pos.first * m + pos.second, pPos.first * m + pPos.second);
                parent[pos.first * m + pos.second] = pPos.first * m + pPos.second;
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
        for (auto &x:sol)cout << x.first << ' ' << x.second << ", ";
        cout << endl;
    }
    else cout << "No Solution!" << endl;
}