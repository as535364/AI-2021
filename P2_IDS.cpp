#include "node.hpp"
#include <fstream>
#include <algorithm>
#include <stack>
#include <tuple>

using std::cerr;
using std::cout;
using std::endl;
using std::string;
typedef std::pair<int, int> pii;

std::tuple<bool, bool, int> dfsLimit(Node init, const string &s, int n, int m,
                             int depthLimit, std::vector<bool> &vis, std::vector<int> &parent){
	// init
    bool ans = false, cutOff = false;
    int cost = -1;
	std::fill(vis.begin(), vis.end(), 0), std::fill(parent.begin(), parent.end(), 0);
	init.setDepth(depthLimit);
    std::stack<Node> st;
    if (init.canMove(0, 0, s)){
        st.push(init);
        vis[init.getPos().first * m + init.getPos().second] = 1;
    }
    

    while (!st.empty()){
        Node now = st.top();
        if (now.getPos().first == n && now.getPos().second == m){
            cost = now.getG();
            ans = true;
            break;
        }
        st.pop();
		if (now.getDepth()<= 0){
            cutOff = true;
            continue;
        }
		std::vector<Node> res = now.next(s, true);
		for (const Node &x : res){
			pii pos = x.getPos();
			pii pPos = x.getParentPos();
			if (vis[pos.first * m + pos.second])continue;
			else {
				// printf("Pos: %d %d pPos: %d %d parent[%d] = %d\n", pos.first, pos.second, pPos.first, pPos.second, pos.first * m + pos.second, pPos.first * m + pPos.second);
				parent[pos.first * m + pos.second] = pPos.first * m + pPos.second;
				vis[pos.first * m + pos.second] = 1;
				st.push(x);
			}
		}
    }
	return std::make_tuple(ans, cutOff, cost);
}

std::tuple<bool, int> IDFS(int cutOffLimit, Node init, const string &s, int n, int m,
                        	 std::vector<bool> &vis, std::vector<int> &parent){
	int nowLimit = 0, cost = -1;
	bool ans = false, cutOff = false;
	while(nowLimit <= cutOffLimit){
		// cerr << "Now Depth: " << nowLimit << "\r";
		std::tie(ans, cutOff, cost) = dfsLimit(init, s, n, m, nowLimit, vis, parent);
		if(ans)return std::make_tuple(ans, cost);
        if(!ans && !cutOff)return std::make_tuple(false, -1); // without cutoff -> failure
		// ++nowLimit;
        nowLimit += 100;
	}
	return std::make_tuple(false, -1);
}


int main(int argc, char *argv[]){
    if (argc != 2){
        cerr << "Usage: ./UCS filepath" << endl;
        return -1;
    }
    int n, m;
    string filename(argv[1]), tmp, s;
    std::ifstream inFile(filename);

    inFile >> n >> m;
    while (std::getline(inFile, tmp)){
        s += tmp;
    }
    

    std::vector<bool> vis((n + 1) * m + 5);
    std::vector<int> parent((n + 1) * m + 5);

    Node a(n, m);
	bool ans;
	int cost;
	
	std::tie(ans, cost) = IDFS(std::min(1000000000, 100 * n * m), a, s, n, m, vis, parent);

    if (ans){
		cout << "Cost: " << cost << endl;
        cout << "Sol for " << filename << ": " << endl;
        std::vector<pii> sol;
        int nowX = n, nowY = m;
        while (nowX != 1 || nowY != 1)
        {
            sol.push_back(pii(nowX, nowY));
            int p = parent[nowX * m + nowY];
            nowY = (p % m == 0 ? m : p % m);
            nowX = (p - nowY) / m;
        }
        sol.push_back(pii(1, 1));
        std::reverse(sol.begin(), sol.end());
        for (const auto &x : sol)cout << x.first << ' ' << x.second << endl;
        cout << endl;
    }
    else cout << "No Solution!" << endl;
}