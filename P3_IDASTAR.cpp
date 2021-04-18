#include "node.hpp"
#include <fstream>
#include <queue>
#include <tuple>
#include <algorithm>
#include <cfloat>

using std::string;
using std::cout;
using std::cerr;
using std::endl;
typedef std::pair<int, int> pii;


std::tuple<bool, bool, int, double> Astar(Node init, const string &s, int n, int m,
                             double threshold, std::vector<bool> &vis, std::vector<int> &parent){
	// init
    bool ans = false, cutOff = false;
    int cost = -1;
    double beCut = DBL_MAX;
	std::fill(vis.begin(), vis.end(), 0), std::fill(parent.begin(), parent.end(), 0);
    init.calH(s);
    std::priority_queue<Node> pq;
    if (init.canMove(0, 0, s)){
        pq.push(init);
        vis[init.getPos().first * m + init.getPos().second] = 1;
    }

    while (!pq.empty()){
        Node now = pq.top();
        if (now.getPos().first == n && now.getPos().second == m){
            cost = now.getG();
            ans = true;
            break;
        }
        pq.pop();

        now.calH(s);
		if (now.getF() > threshold){
            cutOff = true;
            beCut = std::min(now.getF(), beCut);
            continue;
        }
		std::vector<Node> res = now.next(s, true);
		for (Node &x : res){
			pii pos = x.getPos();
			pii pPos = x.getParentPos();
			if (vis[pos.first * m + pos.second])continue;
			else {
				// printf("Pos: %d %d pPos: %d %d parent[%d] = %d\n", pos.first, pos.second, pPos.first, pPos.second, pos.first * m + pos.second, pPos.first * m + pPos.second);
				parent[pos.first * m + pos.second] = pPos.first * m + pPos.second;
				vis[pos.first * m + pos.second] = 1;
                x.calH(s);
				pq.push(x);
			}
		}
    }
	return std::make_tuple(ans, cutOff, cost, beCut);
}

std::tuple<bool, int> IDAstar(double cutOffLimit, Node init, const string &s, int n, int m,
                        	 std::vector<bool> &vis, std::vector<int> &parent){
	int cost = -1;
	bool ans = false, cutOff = false;
    init.calH(s);
    double nowflimit = init.getF();
	while(nowflimit <= cutOffLimit){
        // cerr << "nowLimit: " << nowflimit << '\r';
		std::tie(ans, cutOff, cost, nowflimit) = Astar(init, s, n, m, nowflimit, vis, parent);
		if(ans)return std::make_tuple(ans, cost);
        if(!ans && !cutOff)return std::make_tuple(false, -1); // without cutoff -> failure
	}
	return std::make_tuple(false, -1);
}

int main(int argc, char *argv[]){
    if(argc != 2){
        cerr << "Usage: ./UCS filepath" << endl;
        return -1;
    }
    int n, m;
    string filename(argv[1]), tmp, s;
    std::ifstream inFile(filename);

    inFile >> n >> m;
    while (std::getline (inFile, tmp)) {
        s += tmp;
    }
    
    std::vector<bool> vis((n + 1) * m + 5);
    std::vector<int> parent((n + 1) * m + 5);


    Node a(n, m);
	bool ans;
	int cost;
    std::tie(ans, cost) = IDAstar(1000000000, a, s, n, m, vis, parent);
    

    if(ans){
        cout << "Cost: " << cost << endl;
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