/*Developer: Daisey Jaramillo*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#define MAX 17576

using namespace std;

//17576 possible symbols
//output format: <symbol>,<MaxTimeGap>,<Volume>,<WeightedAveragePrice>,<MaxPrice>
struct outputt
    {
        string symbol;
        int maxTimeGap;
        int volume=0;
        int weightedAvgPrice;
        int maxPrice;
        int howMany=0;
        int tmAmount=0;
    };    outputt structsOfout[MAX];

//prototypes
void readData(vector<string> &dataSeparated);
void separateString(string const &line ,const char delim,vector<string> &dataSeparated);
int calculateOutput(vector<string> &dataSeparated);
bool symbolExist(string symbol, int index, int &existingIndex);
void showResults(int numOfStructs);

int main()
{
    int numOfstructs;
    vector<string> dataSeparated;

    readData(dataSeparated);
    numOfstructs=calculateOutput(dataSeparated);
    showResults(numOfstructs);

    return 0;
}

void readData(vector<string> &dataSeparated)
{
    //gets data from the file

    ifstream filee;
    filee.open("input.csv");
    string line;

    const char delim = ',';

    while(!filee.eof())
    {
        filee>>line;
        separateString(line,delim,dataSeparated);

       // cout<<line<<endl;
    }

}
void separateString(string const &line ,const char delim,vector<string> &dataSeparated)
{
    //separates the strings according to the commas

    stringstream ss(line);
    string x;

    while(getline(ss,x,delim))
    {
        dataSeparated.push_back(x);
    }
}
int calculateOutput(vector<string> &dataseparated)
{
    //puts info into the structure

    //input format: <TimeStamp><Symbol><Quantity><Price>
    //output format: <symbol>,<MaxTimeGap>,<Volume>,<WeightedAveragePrice>,<MaxPrice>
    int index=0;
    int existingIndex;

    while(!dataseparated.empty())
    {
        if(symbolExist(dataseparated[1],index,existingIndex))
        {
            int timm = structsOfout[existingIndex].maxTimeGap;


            int otherTime = stoi(dataseparated[0],nullptr,0);
            structsOfout[existingIndex].maxTimeGap = otherTime - timm;


            int vol = stoi(dataseparated[2],nullptr,0);
            structsOfout[existingIndex].volume += vol;


            int cost = stoi(dataseparated[3],nullptr,0);
            if(structsOfout[existingIndex].maxPrice < cost)
            {
                structsOfout[existingIndex].maxPrice=cost;
            }
            structsOfout[existingIndex].tmAmount += cost*vol;
            structsOfout[existingIndex].weightedAvgPrice = structsOfout[existingIndex].tmAmount/structsOfout[existingIndex].volume;


            //delete the first 4 elements from the vector
            dataseparated.erase(dataseparated.begin());
            dataseparated.erase(dataseparated.begin());
            dataseparated.erase(dataseparated.begin());
            dataseparated.erase(dataseparated.begin());

          index--;
        }
        else
        {
            structsOfout[index].howMany++;


            int timee = stoi(dataseparated[0],nullptr,0);
            structsOfout[index].maxTimeGap= timee;
            structsOfout[index].symbol = dataseparated[1];


            int vol = stoi(dataseparated[2],nullptr,0);
            structsOfout[index].volume += vol;


            int cost = stoi(dataseparated[3],nullptr,0);
            structsOfout[index].maxPrice = cost;
            structsOfout[index].tmAmount += cost*vol;
            structsOfout[index].weightedAvgPrice = structsOfout[index].tmAmount/structsOfout[index].volume;

            //delete the first 4 elements from the vector
            dataseparated.erase(dataseparated.begin());
            dataseparated.erase(dataseparated.begin());
            dataseparated.erase(dataseparated.begin());
            dataseparated.erase(dataseparated.begin());
        }

        index++;
    }

    return index;

}
bool symbolExist(string symbol, int index, int &existingIndex)
{
    //tests to see if the symbol already exits
    for(int x=0;x<=index;x++)
    {
        if(structsOfout[x].symbol == symbol) // might have to change to compare
        {
            existingIndex = x;
            return true;
        }
    }
    return false;
}
void showResults(int numOfStructs)
{
    //outputs the results to a file
    ofstream myfile;
    myfile.open("output.csv");
    //TODO: make it in alphabetical order
    for(int x=0;x<=numOfStructs;x++)
    {
        myfile<<structsOfout[x].symbol<<","<<structsOfout[x].maxTimeGap<<",";
        myfile<<structsOfout[x].volume<<","<<structsOfout[x].weightedAvgPrice<<",";
        myfile<<structsOfout[x].maxPrice<<endl;
    }
    myfile.close();
}
