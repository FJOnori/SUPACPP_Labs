#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "CustomFunctions.h"

using namespace std;

vector<vector<double>> ReadFileNEntries_task3(int N, string filePath){

    string line;
    ifstream File(filePath);
    char delimiter = ',';

    vector<double> dataX;
    vector<double> dataY;
    double Xval;
    double Yval;
    
    int NumOfLinesRead = 0;

    getline(File, line);

    while (getline(File, line)) {

        Xval = stod(line.substr(0, line.find(delimiter)));
        Yval = stod(line.substr(line.find(delimiter)+1, line.find(delimiter)));

        dataX.push_back(Xval);
        dataY.push_back(Yval);

        if ( (NumOfLinesRead >= N) and (N != -1) )
        {
            break;
        }

        NumOfLinesRead++;
    }

    vector<vector<double>> data = {dataX, dataY};
    File.close(); 

    return data;
    
}

vector<vector<string>> ReadFileNEntries_task3(unsigned N, unsigned filePath){
    return ReadFileNEntries_task3(N, filePath);
}

void PrintFileEntries_task3(vector<vector<double>> data){    
    cout << 'x' << ',' << 'y' << endl;
    for (int i = 0; i < data[0].size(); i++){
        cout << data[0][i] << ',' << data[1][i] << endl;
    }
}

vector<double> computeExpectedValues(double p, double q, string inputFilePath){
    
    vector<double> expectedValues;
    vector<vector<double>> data = ReadFileNEntries_task3(-1, inputFilePath);
    vector<double> Xdata = data[0];

    int N = Xdata.size();
    for (int index = 0; index < N; index++){
        double eval = p*Xdata[index] + q;
        expectedValues.push_back(q);
    }
    
    return expectedValues;
}

double task8findChiSquared(double p, double q, string inputFilePath, string errorFilePath){

    double chi2;
    
    vector<vector<double>> data  = ReadFileNEntries_task3(-1, inputFilePath);
    vector<vector<double>> error = ReadFileNEntries_task3(-1, errorFilePath);
    vector<double> expectedVals  = computeExpectedValues(p, q, inputFilePath);
    vector<double> Ydata =  data[1];
    vector<double> Yerr  =  error[1];


    int N = expectedVals.size();
    for (int index = 0; index < N; index++){

        double diff = (Ydata[index] - expectedVals[index]);
        double err2 = (Yerr[index]);

        chi2 +=  pow(diff, 2) / pow(err2,2);
    }

    return chi2/data.size();
} 

void FitLine_task6(string filePath, int entries){
    
    vector<vector<double>> data = ReadFileNEntries_task3(entries, filePath);

    vector<double> Xdata = data[0];
    vector<double> Ydata = data[1];

    int N = Xdata.size();
    double p, q, denominator;
    double Xsum, Ysum, Xsum2, XYsum = 0;

    for (int index = 0; index < N; index++){
        Xsum  += Xdata[index];
        Ysum  += Ydata[index];
        Xsum2 += pow(Xdata[index], 2);
        XYsum +=  Xdata[index]*Ydata[index];
    }

    denominator = N*Xsum2 - Xsum*Xsum;

    p = (N*XYsum - Xsum*Ysum)/denominator;
    q = (Xsum2*Ysum - XYsum*Xsum)/denominator;

    ofstream outputFile("data/BestFit.txt");

    double chi2 = task8findChiSquared(p,q);

    cout << "q,p,chi2"<< endl;
    cout << q << ',' << p << ',' << to_string(chi2) << endl;
    
    outputFile << "q,p,chi2" << endl;
    outputFile << q << ',' << p << ',' << to_string(chi2) << endl;

}

double recursivePow(double x, double y){

    double roundedY = round(y);

    if (roundedY == 0.0){
        return 1.0;
    } else {
        return x*recursivePow(x, y - 1.0);
    }

}

