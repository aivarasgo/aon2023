/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <cmath>

#define INF -1

using namespace std;

struct Point {
    int r, c;
    int straight;
    char direction;
    int cost;
    friend std::ostream& operator<< (std::ostream& stream, const Point& p) {
        return stream << p.r << " " << p.c << " " << p.straight << " " << p.direction;
    }
    friend bool operator < (const Point& left, const Point& right)
    {
        return std::tie(left.r, left.c) < std::tie(right.r, right.c);
    }
};
void printMoves(const vector<vector<string>>& moves){
    for(const auto& p : moves){
        for(const auto& dist: p){
            cout << dist << " ";
        }
        cout << endl;
    }
}
void printDistances(const vector<vector<int>>& distances){
    for(const auto& p : distances){
        for(const auto& dist: p){
            cout << dist << " ";
        }
        cout << endl;
    }
}
void printMatrix(const vector<vector<pair<Point, int>>>& matrix){
    for(const auto& p : matrix){
        for(const auto& points: p){
            cout << points.first << " (" << points.second << ") ";
        }
        cout << endl;
    }
}
void printAdjMatrix(const map <Point, vector<pair<Point, int>>>& adjMatrix){
    for(const auto&p : adjMatrix){
        cout << p.first << ":";
        for(const auto & points: p.second){
            cout << points.first << " (" << points.second << ") ";
        }
        cout << endl;
    }
}
vector<Point> getNeightbours(const Point& current, const vector<vector<pair<Point, int>>>& matrix, const int& minStraight, const int& maxStraight){
    vector<Point> neighbours;
    //direction bottom, right, top, left 
    vector<vector<int>> dir = {{1,0}, {0,1}, {-1,0}, {0,-1}};
    //cout << "from: " << current << endl;
    for(auto&d: dir){
        
        //else if(pos.direction != dijkstra::direction::NONE && pos.direction != dir && pos.straight < minStraight) continue;
        
        int nr = current.r+d[0];
        int nc = current.c+d[1];
        
        int rd = nr - current.r;
        int cd = nc - current.c;
        char direction;
        if(rd == -1) direction = 't'; //top
        else if(rd == 1) direction = 'b'; //bot
        else if(cd == -1) direction = 'l'; //left
        else if(cd == 1) direction = 'r'; //right
        
        if(direction == current.direction && current.straight >= maxStraight) continue;
        else if(current.direction != '.' && current.direction != direction && current.straight < minStraight) continue;
                
        if(nr >= 0 && nr < matrix.size() && nc >= 0 && nc < matrix[0].size()){
            //cout << current << endl;
            if(direction == current.direction){
                //cout << "same dir: " << nr << " " << nc << " dir:" << direction << endl;
                neighbours.push_back(Point{nr,nc,current.straight + 1,direction,matrix[nr][nc].second});
            } else {
                //cout << "diff dir: " << nr << " " << nc << " dir:" << direction << endl;
                neighbours.push_back(Point{nr,nc,1,direction,matrix[nr][nc].second});
            }
           
        }
    }
    //cout << endl;
    return neighbours;
}
void dijkstra(const vector<vector<pair<Point, int>>>& matrix, vector<vector<int>>& distances, vector<vector<int>>& visited, const int& minStraight, const int& maxStraight){
    priority_queue<pair<int, Point>, vector<pair<int, Point>>, greater<pair<int, Point>>> pq;
    
    pq.push(make_pair(0, Point{0,0,1,'.',0}));
    
    while(!pq.empty()){
        pair<int, Point> current = pq.top();
        pq.pop();
        
        if(visited[current.second.r][current.second.c]) continue;
        if(current.second.r == matrix.size()-1 && current.second.c == matrix[0].size()-1) {
            cout << current.first;
        }
        visited[current.second.r][current.second.c] = 1;
        // go via current neighbours
        for(auto& n: getNeightbours(current.second, matrix, minStraight, maxStraight)){
            //int dist = distances[current.second.r][current.second.c] + matrix[n.r][n.c].second;
            //if((dist < distances[n.r][n.c] || distances[n.r][n.c] == INF)){
                n.cost += current.second.cost;
                //cout << n.r << " " << n.c << endl;
                pq.push(make_pair(n.cost, n));
                
            //}
        }
       
    }
    
}
int main()
{
    ifstream file;
    file.open("input");
    string line = "";
    int row = 0;
    map <Point, vector<pair<Point, int>>> adjMatrix; 
    vector<vector<pair<Point, int>>> matrix;
    
    while(file >> line){
        vector<pair<Point, int>> p;
        
        //cout << line << "-" << line.size() << "\n";
        for(int col = 0; col < line.size(); col++){
            //cout << line[col]-'0' << endl;
           p.push_back(make_pair(Point{row,col,1,'.',0}, line[col]-'0'));
        }
        matrix.push_back(p);
        row++;
        
    }
   // printMatrix(matrix);
    vector<vector<int>> distances(matrix.size(), vector<int>(matrix[0].size(), INF));
    vector<vector<int>> visited(matrix.size(), vector<int>(matrix[0].size(), 0));
    // distance to source node is 0, we are already here :)
    distances[0][0] = 0;
    //printDistances(distances);
    int minStraight = 1, maxStraight = 3;
    dijkstra(matrix, distances, visited, minStraight, maxStraight);
    printDistances(distances);
    //printDistances(visited);
    //printMoves(moves);
    return 0;
}
