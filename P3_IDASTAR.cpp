#include "node.hpp"
#include <fstream>

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
        for (const auto &x:sol)cout << x.first << ' ' << x.second << ", ";
        cout << endl;
    }
    else cout << "No Solution!" << endl;
}