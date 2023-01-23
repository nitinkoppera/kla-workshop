#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
int main(){
    fstream inputFile;
    inputFile.open("Format_Source.txt",ios::in);

    string fileText="";

    vector<vector<vector<int>>> polygonList;
    vector<vector<int>> polygon;
    vector<int> coordinates;
    
    if (inputFile.is_open()){
        string line;
        string word;
        
        int boundCount = 0;
        bool canPrint = true;
        while(inputFile >> word){
            string firstWord = word;

            if(word=="boundary"){
                if(boundCount>=2){
                    while(line.size()<6 || line.substr(0,6)!="endstr"){
                        getline(inputFile, line);
                    }
                    fileText += line;
                    fileText += '\n';
                    if(getline(inputFile, line)){
                        fileText += line;
                        fileText += '\n';
                    }
                    break;
                }
                boundCount++;
            }
            
            if(word=="xy"){
                fileText += word;
                fileText += "  ";
                inputFile >> word;
                int n = stoi(word);
                fileText += to_string(n);
                fileText += "  ";
                polygon.clear();
                for(int i=0; i<n; i++){
                    inputFile >> word;
                    int x = stoi(word);
                    inputFile >> word;
                    int y = stoi(word);
                    {
                        fileText += to_string(x);
                        fileText += " ";
                        fileText += to_string(y);
                        fileText += "  ";
                    }
                    polygon.push_back({x,y});
                }
                polygonList.push_back(polygon);
                getline(inputFile, line);
                fileText += line;
                fileText += '\n';
            }
            else{
                fileText += word;
                getline(inputFile, line);
                fileText += line;
                fileText += '\n';
            }
            if(firstWord == "units" || firstWord == "strname"){
                fileText += '\n';
            }
        }
        inputFile.close();
    }

    fstream outputFile;
    outputFile.open("milestone-1.txt",ios::out);
    if(outputFile.is_open())
    {
        outputFile<<fileText;
        outputFile.close();
    }
}