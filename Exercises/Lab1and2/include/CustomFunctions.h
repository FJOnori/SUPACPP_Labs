#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#ifndef CUSTOMFUCTIONS_H
#define MATHUTILS_H

vector<vector<double>> ReadFileNEntries_task3(int N=-1, string filePath = "data/input2D_float.txt" );

vector<vector<string>> ReadFileNEntries_task3(unsigned N, unsigned filePath);

void PrintFileEntries_task3(vector<vector<double>>);

void FitLine_task6(string filePath = "data/input2D_float.txt", int entries = -1 );

void task8();

vector<double> computeExpectedValues(double p, double q, string inputFilePath = "data/input2D_float.txt");

double task8findChiSquared(double p, double q, string inputFilePath = "data/input2D_float.txt", string errorFilePath="data/error2D_float.txt");

double recursivePow(double x, double y);

#endif