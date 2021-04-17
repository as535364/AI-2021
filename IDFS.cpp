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

std::tuple<bool, int> dfsLimit(Node init, string &s, int n, int m,
                             int depthLimit, std::vector<bool> &vis, std::vector<int> &parent){
	// init
    bool ans = false;
    int cost = -1;
	vis.clear(), parent.clear();
    std::stack<Node> st;
    init.setDepth(depthLimit);

    if (init.canMove(0, 0, s))st.push(init);

    while (!st.empty()){
        Node now = st.top();
        if (now.getPos().first == n && now.getPos().second == m){
            cost = now.getG();
            ans = true;
            break;
        }
        st.pop();
		if (now.getDepth()<= 0) continue;
		std::vector<Node> res = now.next(s);
		for (const Node &x : res){
			pii pos = x.getPos();
			pii pPos = x.getParentPos();
			// use set
			// if(vis.count(std::make_pair(pos.first, pos.second)))continue;
			// use array
			if (vis[pos.first * m + pos.second])continue;
			else {
				// printf("Pos: %d %d pPos: %d %d parent[%d] = %d\n", pos.first, pos.second, pPos.first, pPos.second, pos.first * m + pos.second, pPos.first * m + pPos.second);
				parent[pos.first * m + pos.second] = pPos.first * m + pPos.second;
				// use set
				// vis.insert(std::make_pair(pos.first, pos.second));
				// use array
				vis[pos.first * m + pos.second] = 1;
				st.push(x);
			}
		}
    }
	return std::make_tuple(ans, cost);
}

std::tuple<bool, int> IDFS(Node init, int cutOff){
	return std::make_tuple(0, 0);
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
    // use set
    // std::set<pii> vis;
    // use array
    std::vector<bool> vis((n + 1) * m + 5);
    std::vector<int> parent((n + 1) * m + 5);

    Node a(n, m);
	bool ans;
	int cost;
	std::tie(ans, cost) = dfsLimit(a, s, n, m, 1000000000, vis, parent);

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
        // for (auto &x : sol)cout << x.first << ' ' << x.second << ", ";
        // cout << endl;
    }
    else cout << "No Solution!" << endl;
}