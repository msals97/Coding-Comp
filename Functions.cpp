//
//  Functions.cpp
//  Test
//
//  Created by Marc Salinas on 1/5/18.
//  Copyright © 2018 CSULB Physics. All rights reserved.
//

#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Functions.h"
using namespace std;

// ################################################################################################
// ################################################################################################
// Print functions for testing
void printmatrixdouble (int rows, int cols, vector<vector<long double> > mat) {
    for (int i=0; i<rows; ++i) {
        for (int j=0; j<cols; ++j) {
            cout << mat[i][j] << '\t';
        }
        cout << endl;
    }
}

void printmatrixstr (int rows, int cols, vector<vector<string> > mat) {
    for (int i=0; i<rows; ++i) {
        for (int j=0; j<cols; ++j) {
            cout << mat[i][j] << '\t';
        }
        cout << endl;
    }
}

void printvectordouble (int rows, vector<long double> mat) {
    for (int i=0; i<rows; ++i) {
        cout << mat[i] << endl;
    }
}

void printvectorstr (int rows, vector<string> mat) {
    for (int i=0; i<rows; ++i) {
        cout << mat[i] << endl;
    }
}

// ################################################################################################
// ################################################################################################
// Function to count number of rows in txt file
int rowCount(string txtfile) {
    int count = 0; // Set initial count to 0
    string line; // Initialize variable to store line's string temporarily
    ifstream file(txtfile); // Read the txt file
    if (!file) {
        cout << "RowCount: Error opening file";
    }
    else {
        cout << "RowCount: File opened successfully \n";
    }
    
    // Use getline function from ifstream to count non empty lines
    while (getline(file, line)) {
        count++;
    }
    return count; // Return number of lines
}

// ################################################################################################
// ################################################################################################
// Returns the file type
string fileType(string filename) {
    
    ifstream file;
    string line;
    size_t pos;
    
    file.open(filename);
    
    if(!file){
        cout << "PolyFit: Unable to open file" << endl;
    }
    
    getline(file,line); // get line from file
    pos=line.find(","); // search
    if(pos!=string::npos) { // string::npos is returned if string is not found
        cout << "File name: " << filename << endl;
        file.close();
        return "CSV";
    } else {
        cout << "File name: " << filename << endl;
        file.close();
        return "TXT";
    }
}

// ################################################################################################
// ################################################################################################
// Convert string data to decimal data
int StrtoDouble(int numrows, vector<vector<string> >& strmatrix, vector<vector<long double> >& doublematrix) {
    for (int i = 0; i < numrows; ++i) {
        for (int j = 0; j < 2; ++j) {
            string num = strmatrix[i][j];
            istringstream os(num);
            long double decnum;
            os >> decnum;
            doublematrix[i][j] = decnum;
        }
    }
    return 0;
}

// ################################################################################################
// ################################################################################################
// Function to take file data and put it into a string matrix
int filetomatrixSTR(string txtfile, vector<vector<string> >& matrix) {
    int numdataRows = rowCount(txtfile);
    ifstream file;
    string line;

    file.open(txtfile);
    
    if(!file){
        cout << "MAX: Unable to open file" << endl;
    }
    
    if (fileType(txtfile) == "CSV") {
        ifstream file;
        string line;
        int i=0;
        int j=0;
        file.open(txtfile);
        while(getline(file,line)) {
            stringstream linestream(line);
            string value;
            while(getline(linestream,value,',')) {
                matrix[i][j] = value;
                j=j+1;
            }
            i=i+1;
            j=0;
        }
        file.close();
        
    } else {
        ifstream file;
        file.open(txtfile);
        for (int i=0; i < numdataRows; ++i) {
            for (int j=0; j < 2; ++j) {
                file >> matrix[i][j];
            }
        }
        file.close();
    }
    return 0;
}

// ################################################################################################
// ################################################################################################
// Function to find the smallest max x value of two files
long double MaxFind(string datatxt1, string datatxt2) {
    int numdataRows1 = rowCount(datatxt1);
    int numdataRows2 = rowCount(datatxt2);
    
    // Initialize string data vector 1
    vector<vector<string> > strdata1;
    strdata1.resize(numdataRows1);
    for (int i = 0; i < numdataRows1; ++i) {
        strdata1[i].resize(2);
    }
    
    // Initialize string data vector 2
    vector<vector<string> > strdata2;
    strdata2.resize(numdataRows2);
    for (int i = 0; i < numdataRows2; ++i) {
        strdata2[i].resize(2);
    }
    
    // Initialize double data vector 1
    vector<vector<long double> > data1;
    data1.resize(numdataRows1);
    for (int i = 0; i < numdataRows1; ++i) {
        data1[i].resize(2);
    }
    
    // Initialize double data vector 2
    vector<vector<long double> > data2;
    data2.resize(numdataRows2);
    for (int i = 0; i < numdataRows2; ++i) {
        data2[i].resize(2);
    }
    
    // Initialize x data vector 1
    vector<long double> dataX1;
    dataX1.resize(numdataRows1);
    
    // Initialize x data vector 2
    vector<long double> dataX2;
    dataX2.resize(numdataRows2);
    
    filetomatrixSTR(datatxt1, strdata1);
    filetomatrixSTR(datatxt2, strdata2);
    
    StrtoDouble(numdataRows1, strdata1, data1);
    StrtoDouble(numdataRows2, strdata2, data2);
    
    // Fill data vectors with x values
    for (int i=0; i<numdataRows1; ++i) {
        dataX1[i] = data1[i][0];
    }
    
    for (int i=0; i<numdataRows2; ++i) {
        dataX2[i] = data2[i][0];
    }
    
    // Get min of max of two data sets
    long double max1 = *max_element(dataX1.begin(), dataX1.end());
    long double max2 = *max_element(dataX2.begin(), dataX2.end());
    long double minofmax;
    if (max1>max2) {
        minofmax = max2;
    }
    else {
        minofmax = max1;
    }
    return minofmax;
}

// ################################################################################################
// ################################################################################################
// Function to find the largest min x value between two data sets
long double MinFind(string datatxt1, string datatxt2) {
    int numdataRows1 = rowCount(datatxt1);
    int numdataRows2 = rowCount(datatxt2);
    
    // Initialize string data vector 1
    vector<vector<string> > strdata1;
    strdata1.resize(numdataRows1);
    for (int i = 0; i < numdataRows1; ++i) {
        strdata1[i].resize(2);
    }
    
    // Initialize string data vector 2
    vector<vector<string> > strdata2;
    strdata2.resize(numdataRows2);
    for (int i = 0; i < numdataRows2; ++i) {
        strdata2[i].resize(2);
    }
    
    // Initialize double data vector 1
    vector<vector<long double> > data1;
    data1.resize(numdataRows1);
    for (int i = 0; i < numdataRows1; ++i) {
        data1[i].resize(2);
    }
    
    // Initialize double data vector 2
    vector<vector<long double> > data2;
    data2.resize(numdataRows2);
    for (int i = 0; i < numdataRows2; ++i) {
        data2[i].resize(2);
    }
    
    // Initialize x data vector 1
    vector<long double> dataX1;
    dataX1.resize(numdataRows1);
    
    // Initialize x data vector 2
    vector<long double> dataX2;
    dataX2.resize(numdataRows2);
    
    filetomatrixSTR(datatxt1, strdata1);
    filetomatrixSTR(datatxt2, strdata2);
    
    StrtoDouble(numdataRows1, strdata1, data1);
    StrtoDouble(numdataRows2, strdata2, data2);

    for (int i=0; i<numdataRows1; ++i) {
        dataX1[i] = data1[i][0];
    }
    
    for (int i=0; i<numdataRows2; ++i) {
        dataX2[i] = data2[i][0];
    }
    
    // Get the max of min of data sets
    long double min1 = *min_element(dataX1.begin(), dataX1.end());
    long double min2 = *min_element(dataX2.begin(), dataX2.end());
    long double maxofmin;
    if (min1<min2) {
        maxofmin = min2;
    }
    else {
        maxofmin = min1;
    }
    return maxofmin;
}

// ################################################################################################
// ################################################################################################
// Returns row number of closest value in data set to some intersection point
int findvalue(string txtfile, long double valuetofind, string type) {
    cout << "Looking for transition points in txt file" << endl;
    
    int numdatarows = rowCount(txtfile);
    
    // Initialize string data array
    vector<vector<string> > datamatrixstr;
    datamatrixstr.resize(numdatarows);
    for (int i = 0; i < numdatarows; ++i) {
        datamatrixstr[i].resize(2);
    }
    
    // Initialize double data array
    vector<vector<long double> > datamatrixdouble;
    datamatrixdouble.resize(numdatarows);
    for (int i = 0; i < numdatarows; ++i) {
        datamatrixdouble[i].resize(2);
    }
    
    filetomatrixSTR(txtfile, datamatrixstr);
    StrtoDouble(numdatarows, datamatrixstr, datamatrixdouble);

    long double error = abs(datamatrixdouble[0][0]-valuetofind);
    long double newerror;
    int rowID = 0;
    
    if (type == "X") {
        for (int i=0; i<numdatarows; ++i) {
            newerror = abs(datamatrixdouble[i][0]-valuetofind);
            if (newerror<error) {
                error = newerror;
                rowID = i;
            }
        }
    } else if (type == "Y") {
        for (int i=0; i<numdatarows; ++i) {
            newerror = abs(datamatrixdouble[i][1]-valuetofind);
            if (newerror<error) {
                error = newerror;
                rowID = i;
            }
        }
    }
    cout << endl;
    return rowID;
}

// ################################################################################################
// ################################################################################################
// Combine txt files to get the maxwell transition data
void combinetxt(string txtfileQ, string txtfileH, int rowIDQ, int rowIDH, string txtname) {
    cout << "Creating new combined txt file" << endl;
    int numdatarowsQ = rowCount(txtfileQ);
    int numdatarowsH = rowCount(txtfileH);
    
    // Initialize string data matrix
    vector<vector<string> > datastrmatrixQ;
    datastrmatrixQ.resize(numdatarowsQ);
    for (int i = 0; i < numdatarowsQ; ++i) {
        datastrmatrixQ[i].resize(2);
    }
    
    // Initialize double data matrix
    vector<vector<long double> > datadoublematrixQ;
    datadoublematrixQ.resize(numdatarowsQ);
    for (int i = 0; i < numdatarowsQ; ++i) {
        datadoublematrixQ[i].resize(2);
    }
    
    // Initialize string data array
    vector<vector<string> > datastrmatrixH;
    datastrmatrixH.resize(numdatarowsH);
    for (int i = 0; i < numdatarowsH; ++i) {
        datastrmatrixH[i].resize(2);
    }
    
    // Initialize double data array
    vector<vector<long double> > datadoublematrixH;
    datadoublematrixH.resize(numdatarowsH);
    for (int i = 0; i < numdatarowsH; ++i) {
        datadoublematrixH[i].resize(2);
    }
    
    filetomatrixSTR(txtfileQ, datastrmatrixQ);
    StrtoDouble(numdatarowsQ, datastrmatrixQ, datadoublematrixQ);
    filetomatrixSTR(txtfileH, datastrmatrixH);
    StrtoDouble(numdatarowsH, datastrmatrixH, datadoublematrixH);
    
    // For Hadron to quark
    int numQuarkRows = numdatarowsQ - (rowIDQ-1);
    int numHadRows = rowIDH;
    int numRows = numQuarkRows + numHadRows;
    
    // Hadron to Quark: Initialize new data array
    vector<vector<long double> > combineddata;
    combineddata.resize(numRows);
    for (int i = 0; i < numRows; ++i) {
        combineddata[i].resize(2);
    }
    
    // Hadron to Quark: Fill data matrix
    for (int i=0; i<numRows; ++i) {
        for (int j=0; j<2; ++j) {
            if (i<=numHadRows) {
                combineddata[i][j] = datadoublematrixH[i][j];
            } else {
                int k = i - numHadRows + rowIDQ-1;
                combineddata[i][j] = datadoublematrixQ[k][j];
            }
        }
    }
    
    // Create new combined txt file
    ofstream newfile;
    newfile.open(txtname);
    for (int i=0; i<numRows; ++i) {
        for (int j=0; j<2; ++j) {
            if (j==1) {
                newfile << combineddata[i][j] << endl;
            } else {
                newfile << combineddata[i][j] << " ";
            }
        }
    }
    newfile.close();
    cout << endl;
    cout << "Created Combined text file with transition data" << endl;
}