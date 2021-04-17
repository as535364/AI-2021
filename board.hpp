#include <string>
#include <iostream>
#include <utility>
#include <vector>

const int WALL = '*';

class Board{
public:
    Board(int n, int m): n_(n), m_(m){};
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
    double getH() const{
        return h_;
    };
    std::pair<int, int> getParentPos() const{
        return std::pair<int, int>(this->px_, this->py_);
    };
    std::pair<int, int> getPos() const{
        return std::pair<int, int>(this->x_, this->y_);
    };
    bool operator<(const Board &rhs) const{
        return g_ + h_ > rhs.g_ + h_;
    };
    void move(int diffX, int diffY, const std::string &b){
        int diff = this->get(x_, y_, b) - this->get(x_ + diffX, y_ + diffY, b);
        g_ += 10 + diff * diff;
        px_ = x_, py_ = y_;
        x_ += diffX, y_ += diffY;
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
    std::vector<Board> next(const std::string &b){
        std::vector<Board> res;
        int dir[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        for(int i = 0; i < 4; ++i){
            int dirx = dir[i][0], diry = dir[i][1];
            if(this->canMove(dirx, diry, b)){
                Board tmp(*this);
                tmp.move(dirx, diry, b);
                res.push_back(tmp);
            }
        }
        return res;
    };
private:
    double g_ = 0, h_ = 0;
    int n_, m_;
    int x_ = 1, y_ = 1;
    int px_ = -1, py_ = -1;
};