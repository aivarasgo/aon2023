/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

void navigateInDesert(map<string, vector<string>>& desert, const string& instructions, vector<string>& startNodes, map<string,int>& endNodes){
    int zToHit = startNodes.size();
    int steps = 0;
    int nodesOnZ = 0;
    while(nodesOnZ != zToHit){
        for(int i = 0; i < instructions.size(); i++){
            
            if(nodesOnZ == zToHit) break;
            
            // reset z count
            nodesOnZ = 0;
            
            char direction = instructions[i];
            // move 1 step
            for(int j = 0; j < startNodes.size(); j++){
                //cout << "before: " << startNodes[j] << endl;
                if(direction == 'L'){
                    startNodes[j] = desert[startNodes[j]][0];
                } else if (direction == 'R'){
                    startNodes[j] = desert[startNodes[j]][1];
                }
                //increment Z count
                if(endNodes.find(startNodes[j]) != endNodes.end()){
                    //cout << "end reached: " << startNodes[j] << endl;
                    nodesOnZ++;
                }
                //cout << "after: " << startNodes[j] << " count:" << nodesOnZ << endl;
            }
            // increment steps
            steps++;
        }
    }
    cout << "steps:" << steps << endl;
    
}
int main()
{
    //input file variables
    string line;
    ifstream file("input.txt");
    stringstream stream;
    //task variables
    string instructions;
    map<string, vector<string>> desertMap;
    
    
    getline(file, instructions); //line containing l-r instructions
    instructions.pop_back();
    
    //cout << "instructions:" << instructions << "." << endl;
    
    getline(file, line); //empty line skip
    
    while(getline(file, line)){
        desertMap[line.substr(0,3)] = {line.substr(7,3), line.substr(12,3)};
        //cout << line.substr(0,3) << " "<< line.substr(7,3) << " " << line.substr(12,3) << endl;
    }
    vector<string> startNodes;
    map<string, int> endNodes;
    for(auto&m:desertMap){
        char lastChar = m.first[2];
        if(lastChar == 'A'){
            startNodes.push_back(m.first);
        } else if(lastChar == 'Z'){
            endNodes[m.first] = 0;
        }
    }
    for(auto&n: startNodes){
        cout << n << " ";
    }
    navigateInDesert(desertMap, instructions, startNodes, endNodes);
    return 0;
}
