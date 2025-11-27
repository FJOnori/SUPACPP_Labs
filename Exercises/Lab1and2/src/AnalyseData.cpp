#include <iostream>
#include <fstream>
#include <string>

#include "CustomFunctions.h"

using namespace std;

void ReadFileByLine_task1( string filePath = "data/input2D_float.txt" ){

    string line;
    ifstream File(filePath);

    while (getline(File, line)) {
        cout << line << endl;
    }
    File.close(); 
}

void ReadFileByLineAsDouble_task2( string filePath = "data/input2D_float.txt" ){

    string line;
    ifstream File(filePath);
    char delimiter = ',';

    vector<double> dataX;
    vector<double> dataY;
    double Xval;
    double Yval;

    getline(File, line);

    while (getline(File, line)) {

        Xval = stod(line.substr(0, line.find(delimiter)));
        Yval = stod(line.substr(line.find(delimiter)+1, line.find(delimiter)));

        dataX.push_back(Xval);
        dataY.push_back(Yval);

    }

    vector<vector<double>> data = {dataX, dataY};
    File.close(); 

    cout << 'x' << ',' << 'y' << endl;
    for (int i = 0; i < data[0].size(); i++){
        cout << data[0][i] << ',' << data[1][i] << endl;
    }

}

void ReadFileSepreated_task3( int N = -1, string filePath = "data/input2D_float.txt"){

    vector<vector<double>> data = ReadFileNEntries_task3(N, filePath);

    if (N > data[0].size()){
        cout << "ERROR: N is out of range, printing only first five lines." << endl;
        data = ReadFileNEntries_task3(5, filePath);
    }

    PrintFileEntries_task3(data);
}

vector<double> CalculateMagnitudes_task4(string filePath = "data/input2D_float.txt" ){

    double magVal;
    vector<double> magnitudes;
    vector<vector<double>> data = ReadFileNEntries_task3(-1, filePath);

    for (int i = 0; i < data[0].size(); i++){
        magVal = sqrt( pow(data[0][i], 2) + pow(data[1][i], 2) );
        cout << magVal << endl;
        magnitudes.push_back(magVal);
    }

    return magnitudes;
}

void Notice_task5(){
    cout << "See .h and .cpp files" << endl;
}

void Wrapper_task6(string filePath = "data/input2D_float.txt", int entries = -1){
    FitLine_task6(filePath, entries);
}

void Notice_task7(){
    cout << "See overloaded ReadFileNEntries_task3 fucntion in CustomFunctions.cpp" << endl;
}

void Wrapper_task8(double p, double q, string inputFilePath, string errorFilePath){
    cout << task8findChiSquared(p,q,inputFilePath,errorFilePath) << endl;
}

string task9recur(ifstream &File){

    string line;
    char delimiter = ',';

    getline(File, line);
    string Xval = (line.substr(0, line.find(delimiter)));
    string Yval = (line.substr(line.find(delimiter)+1, line.find(delimiter)));

    if (Xval == ""){
        return "";
    } else {
        return to_string(recursivePow( stod(Xval), stod(Yval)) ) + "\n" + task9recur(File);
    }

}

void Wrapper_task9(string filePath = "data/input2D_float.txt"){
    
    string line;
    ifstream File(filePath);
    getline(File, line);

    cout << task9recur(File) << endl;

}

void SaveToFile_task10(int task, string inputFilePath = "data/input2D_float.txt"){

    string line;
    ifstream inputFile(inputFilePath);
    getline(inputFile, line);

    if  ( task == 9 ){
        cout << "executing x^y" << endl;

        ofstream outputFile("data/x^y.txt");
        outputFile << "x^y" << endl;
        outputFile << task9recur(inputFile) << endl;

    } else if ( task == 8 ){

        double p;
        double q;
        
        cout << "Type a number p: ";
        cin >> p;
        
        cout << "Type a number q: ";
        cin >> q;

        cout << "executing chi2" << endl;

        double chi2 = task8findChiSquared(p,q);

        ofstream outputFile("data/chi2.txt");
        outputFile << "chi2" << endl;
        outputFile << task9recur(inputFile) << endl;

    } else if ( task == 6 ) {

        Wrapper_task6(inputFilePath);

    } else if ( task == 4 ){

        cout << "executing magnitudes" << endl;

        ofstream outputFile("data/magnitudes.txt");
        outputFile << "magnitudes" << endl;
        vector<double> magnitudes = CalculateMagnitudes_task4(inputFilePath);

        for (double m : magnitudes){
            outputFile << m << endl;
        }

    } else {

        cout << "enter valid command" << endl;

    }
}

int main(){

    string userInput;

    while (true){
     
        cout << endl << "Select function:" << endl;
        cin >> userInput;

        if (userInput == "exit"){
            cout << "Exiting Code" << endl;
            break;
        }

        try{
            SaveToFile_task10(stoi(userInput));      
        }
        catch(exception &err){
            cout<<"enter valid command"<<endl;
        }

    }
}