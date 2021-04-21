#include <string>
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

const int WALL = '*';

class Node{
public:
    Node(int n, int m): n_(n), m_(m){};
    Node(int n, int m, int x, int y): n_(n), m_(m), x_(x), y_(y){};
    int get(int x, int y, const std::string &b) const{
        char tmp = b[x * (m_ + 2) + y];
        return tmp == WALL ? -1 : tmp - '0';
    };
    bool canMove(int diffX, int diffY, const std::string &b) const{
        return this->get(x_ + diffX, y_ + diffY, b) != -1;
    };
    double getG() const{
        return g_;
    };
    double getF() const{
        return g_ + h_;
    }
    int getDepth() const{
        return depth_;
    };
    std::pair<int, int> getParentPos() const{
        return std::pair<int, int>(this->px_, this->py_);
    };
    std::pair<int, int> getPos() const{
        return std::pair<int, int>(this->x_, this->y_);
    };
    bool operator<(const Node &rhs) const{
        return g_ + h_ > rhs.g_ + rhs.h_;
    };
    void move(int diffX, int diffY, const std::string &b){
        int diff = this->get(x_, y_, b) - this->get(x_ + diffX, y_ + diffY, b);
        g_ += 10 + diff * diff;
        px_ = x_, py_ = y_;
        x_ += diffX, y_ += diffY;
        // --depth_;
        depth_ -= 10 + diff * diff;
    };
    void plot(const std::string &b) const{
        std::cout << "Cost: " << this->getG() << std::endl;
        for(int i = 1; i <= n_; ++i){
            for(int j = 1; j <= m_; ++j){
                if(i == x_ && j == y_)std::cout << this->get(i, j, b) << 'x' << '\t';
                else std::cout << this->get(i, j, b) << '\t';
            }
            std::cout << std::endl;
        }
        std::cout << "------------------------------------\n";
    };
    std::vector<Node> next(const std::string &b, bool sort=false){
        std::vector<Node> res;
        int dir[][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
        for(auto & i : dir){
            int dirX = i[0], dirY = i[1];
            if(this->canMove(dirX, dirY, b)){
                Node tmp(*this);
                tmp.move(dirX, dirY, b);
                res.push_back(tmp);
            }
        }
        if(sort)std::sort(res.begin(), res.end());
        return res;
    };
    std::vector<std::pair<int, Node>> nextWithCost(const std::string &b, bool sort=false){
        std::vector<std::pair<int, Node>> res;
        int dir[][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
        for(auto & i : dir){
            int dirX = i[0], dirY = i[1];
            if(this->canMove(dirX, dirY, b)){
                Node tmp(*this);
                tmp.move(dirX, dirY, b);
                res.emplace_back(std::make_pair(tmp.g_ - this->g_, tmp));
            }
        }
        if(sort)std::sort(res.begin(), res.end());
        return res;
    };
    void setDepth(int depth){
        depth_ = depth;
    };
    void calH(const std::string &s){
        if(average == -1){
            average = 0;
            for(int i = 1; i <= n_; ++i){
                for(int j = 1; j <= m_; ++j){
                    double now = this->get(i, j, s);
                    now *= now;
                    average += now;
                }
            }
            average /= (n_ * m_);
        }
        h_ = (n_ - x_) + (m_ - y_) * (10 + average);
    };
private:
    double g_ = 0, h_ = 0; // h for IDA*
    double average = -1;
    int n_, m_;
    int x_ = 1, y_ = 1; // person pos
    int px_ = -1, py_ = -1; // parent pos
    int depth_; // for Iterative Deepening Search
};