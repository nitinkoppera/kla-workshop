#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

int dist(vector<int> p1, vector<int> p2){
    int res = sqrt( (p1[0]-p2[0])*(p1[0]-p2[0]) + (p1[1]-p2[1])*(p1[1]-p2[1]) );
    return res;
}

vector<float> polyValue(vector<vector<int>> polygon){
    vector<float> val;
    for(int i=0; i<polygon.size(); i++){
        float num = dist(polygon[i],polygon[(i+1)%polygon.size()]);
        // cout<<"num === "<<num<<endl;
        val.push_back(num);
    }
    return val;
}

bool checkPoly(vector<vector<int>> polygon,vector<vector<vector<int>>> list){
    // cout<<"list size = "<<list.size()<<endl;
    // for(int j=0; j<polygon.size(); j++){
        vector<float> polygonValue;
        polygonValue = polyValue(polygon);
        vector<float> polygonValue1 = polyValue(polygon);
        polygonValue1.insert(polygonValue1.end(), polygonValue.begin(), polygonValue.end());

        for(int i=0; i<list.size(); i++)
        {
                vector<float> listValue = polyValue(list[i]);
                // cout<<"poly array count = "<<polygonValue1[listValue.size()]<<endl;
                // cout<<"listValue count = "<<listValue[0]<<endl;
                // cout<<"listValue count = "<<list[i][0][0]<<endl;
                bool check=false;
                for(int i1 = 0; i1 < polygonValue1.size()/2; i1++) {
                    for(int j1=0; j1 < listValue.size(); j1++) {
                        if((i1+j1) <= polygonValue1.size()) {
                            if(polygonValue1[(i1+j1)] == listValue[j1]){
                                check = true;
                            }
                            else{
                                check = false;
                                break;
                            }
                        }
                    }
                    if(check) return true;
                }
        }
    // }
    return false;
}

int main(){
    int polyCount=0;
    fstream inputFile;
    inputFile.open("Format_Source.txt",ios::in);

    string fileText="";

    vector<vector<vector<int>>> polygonList;
    vector<vector<int>> polygon;
    
    // Source input
    vector<vector<vector<int>>> poiList;
    inputFile.open("POI.txt",ios::in);
    if (inputFile.is_open()){
        string line;
        string word;
        
        // getline(inputFile, line);
        while(inputFile >> word && word!="boundary"){
            string firstWord = word;
            fileText += word;
            getline(inputFile, line);
            fileText += line;
            fileText += '\n';
            
            if(firstWord == "units" || firstWord == "strname"){
                fileText += '\n';
            }
        }
        // fileText += word;
        // getline(inputFile, line);
        // fileText += line;
        // fileText += "\n\n";
        
        int boundCount = 0;
        while(inputFile >> word && word != "endstr"){
            string firstWord = word;
            
            if(word=="xy"){
                // fileText += word;
                // fileText += "  ";
                inputFile >> word;
                int n = stoi(word);
                // fileText += to_string(n);
                // fileText += "  ";
                polygon.clear();
                for(int i=0; i<n; i++){
                    inputFile >> word;
                    int x = stoi(word);
                    inputFile >> word;
                    int y = stoi(word);
                    {
                        // fileText += to_string(x);
                        // fileText += " ";
                        // fileText += to_string(y);
                        // fileText += "  ";
                    }
                    polygon.push_back({x,y});
                }
                polygonList.push_back(polygon);
                getline(inputFile, line);
                // fileText += line;
                // fileText += '\n';
            }
            else{
                // fileText += word;
                getline(inputFile, line);
                // fileText += line;
                // fileText += '\n';
            }
            if(firstWord == "units" || firstWord == "strname"){
                // fileText += '\n';
            }
        }
        inputFile.close();
    }
    
    poiList = polygonList;
    cout<<"poi list - "<<poiList.size()<<endl;
    polygonList.clear();
    
    // POI input
    vector<vector<vector<int>>> srcList;
    inputFile.open("Source.txt",ios::in);
    if (inputFile.is_open()){
        string line;
        string word;

        getline(inputFile, line);
        while(line!="strname top"){
            getline(inputFile, line);
        }
        
        int boundCount = 0;
        while(inputFile >> word && word != "endstr"){
            string firstWord = word;
            
            if(word=="xy"){
                string poly="boundary\nlayer 1\ndatatype 0\n";
                poly += word;
                poly += "  ";
                inputFile >> word;
                int n = stoi(word);
                poly += to_string(n);
                poly += "  ";
                polygon.clear();
                for(int i=0; i<n; i++){
                    inputFile >> word;
                    int x = stoi(word);
                    inputFile >> word;
                    int y = stoi(word);
                    {
                        poly += to_string(x);
                        poly += " ";
                        poly += to_string(y);
                        poly += "  ";
                    }
                    polygon.push_back({x,y});
                }
                polygonList.push_back(polygon);
                getline(inputFile, line);
                poly += line;
                poly += '\n';
                poly += "endel\n";
                if(checkPoly(polygon,poiList))
                {
                    
                    fileText += poly;
                    polyCount++;
                }
            }
            else{
                // fileText += word;
                getline(inputFile, line);
                // fileText += line;
                // fileText += '\n';
            }
            if(firstWord == "units" || firstWord == "strname"){
                // fileText += '\n';
            }
        }
        inputFile.close();
    }
    
    srcList = polygonList;
    cout<<"src list - "<<srcList.size()<<endl;



    fileText += "endstr\nendlib\n";
    cout<<"polyCount - "<<polyCount<<endl;
    // Final output
    fstream outputFile;
    outputFile.open("milestone-2.txt",ios::out);
    if(outputFile.is_open())
    {
        outputFile<<fileText;
        outputFile.close();
    }
}