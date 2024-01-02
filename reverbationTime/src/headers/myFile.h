#ifndef __MYFILE_H__
#define __MYFILE_H__

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <math.h>
#include <filesystem>
#include <sstream>
#include <cstring>

//Maximum lenght of array

const int maxLen = 10000;
const int maxSize = 100000;
const uint8_t dim = 3;
const int bufferSize = 64;
const uint16_t structMax = 20;



const double lambda = 1;
const double delta = 1;
const double fileDelta = 0.5;
#define PI 3.1415926

namespace fileLib
{

std::string nameProtect(std::string fileName);
//function to add .txt to filename if not done yet



void message(std::string text, bool mode);
//function for displaying which function is accessing data



uint32_t fileLenght(std::string fileName);
//number of elements in file separated by \t or \n

uint32_t fileLineLenght(std::string fileName);
//number of lines in file



uint32_t arrayLenght(double array[]);
//size of arary

uint32_t arrayLenght(std::vector<double> & vect);




uint32_t columnsInLine(std::string fileName);
//return how many columns are in one line




bool fileRead(std::string fileName, double readArray[]);
//reads data from FileName to readArray

bool fileRead(std::string fileName, double readArray1[], double readArray2[]);
//reads data from fileName to readArray1 and readArray2, useful for reading from tables with
//two columns

bool fileRead(std::string fileName, std::vector<double> & readvector, uint16_t NumberInRow = 2, uint16_t orderPlace = 1);
//can read data from ALL sized files, Number of Rows says how many values there are in one row
//orderPlace starts at zero, indexing same as with arrays --> third column has orderPlace 2
//WARNING function is NOT using NAMEPROTECT, cou have to write name with fileformat


bool fileWrite(std::string fileName, double array1[]);
//writes array1 into fileName

bool fileWrite(std::string fileName, double array1[], double array2[]);
//writes arra1 and array2 into fileName, useful for tables

bool fileWrite(std::string fileName, std::vector<double> & vect);
//writes elements of vector to fileName     vect \n
//WARNING function is NOT using NAMEPROTECT, cou have to write name with fileformat

bool fileWrite(std::string fileName, std::vector<double> & one, std::vector<double> & two);
//writes elements of vector one \t two \n to fileName
//WARNING function is NOT using NAMEPROTECT, cou have to write name with fileformat



bool fileAppendLine(std::string fileName, double array1[]);
//appends array on new line

bool fileAppendTab(std::string fileName, double array1[]);
//appends array on line 

bool fileAppendTab(std::string fileNames[], std::string outFile, int len);
//reads data from fileNames are writes them in outFile with Tab Append




bool fileAproximation(std::string fileRead, std::string fileWrite, int aproximate = 10);
//when fileRead > fileWrite writes arithmetical avarge into fileWrite, useful for shrinking data
//it is uses for files with 2 columns of data using 1:2
//this function was meant for big files, not best for aproximating smaller files 




bool fileExpand1(std::string fileRead, std::string fileWrite, int aproximate = 10);
// parametrs - fileRead = source file of information, fileWrite = file where is going to be written information
//aproximate is final size of fileWtrite

//expands size of data to aproximate

bool fileExpand2(std::string fileRead, std::string fileWrite, int aproximate = 10);
//overwrites data from readFile to WriteFile but expands some values to final count of aproximate
//uses every piece of data for aproximate times




bool arrayAproximation(double array1[], double array2[], int times);
//rewrites values of array1 to array2, each value is used times times

bool arrayAproximationTranspose(double array1[], double array2[], int times);
//aproximates values of array1 to array2 using it times times, all expanded values are expanded
//around original value



bool logValue(std::vector<double> &vect);
//subsitutes all elements with thier acoustic logaritgmic value 10*log(vect[i])



bool fileClear(std::string fileName);
//clears all data from fileName




bool fileCopy(std::string fileRead, std::string fileWrite, uint32_t numOfCol = 2);
//copies values from fileRead to fileWrite, numOfCol is for right arrangement of files


bool fileLogCopy(std::string fileNameRead, std::string fileNameWrite, uint16_t numberInRow = 2, uint16_t order1 = 0, uint16_t order2 = 1);
//numberInRow says how many columns are in read file, order1 is values which are going to be copied
//order2 is column where values are giong to be 10log(x)



uint32_t maximumInCol(std::string fileName, uint32_t numOfCol = 2, uint32_t column = 1);
//return number of row where is maximum value in column, indexing starts at 0
//numOfCol is for how many columns are there in file

uint32_t minimumInCol(std::string fileName, uint32_t numOfCol = 2, uint32_t column = 1);
//returns number of row where is minimum value in column, indexing starts from 0
//numOfCol says how many columns file has



bool fileFabs(std::string fileRead, std::string fileWrite, uint32_t numOfCol = 2);
//rewrites fileRead to fileWrite with only positive values 
//using fabs() function

bool fileColumnRemove(std::string fileName, uint16_t numOfCol = 3, uint16_t eliminate = 1);
//eliminates column number eliminate from file


bool fileShortenOrdered(std::string fileName, uint32_t startPoint, double delta = 0);
//rewrites values of fileName from line numbered startPoint with numbering of first column starting with
//old numbering from 0



bool fileCutFromLine(std::string fileName, uint32_t cut, uint32_t numOfCol = 2);
//rewrites fileName to cut line

bool fileCutToLine(std::string fileName, uint32_t line, uint32_t numOfCol = 2);
//rewrites file from line


bool filesAvarge(std::vector<std::string> & files, std::string fileWrite, uint32_t numOfCol = 2, uint32_t order1 = 0, uint32_t order2 = 1);
//writes avarge of files to fileWrite
//files have same arrangement with numOfCol (number of columns), order1 is for first column, order2 for second column

double returnTimeFromValue(std::string fileName, double value, uint16_t numOfCol = 2, uint16_t column = 1);
//return value in first column on line where is value in column 


bool loadFromPath(std::string path, std::vector<std::string> & files);
//fills vector with list of file names in path folder
//WARNING clears whole files vector!!

uint32_t findLineFromDiff(std::string fileName, uint32_t startLine = 1, double diff = -30, uint16_t numofCol = 2, uint16_t column = 1);
//returns number of line where is first time detectect difference between startLine 
//and this searched line bigger (or smaller than diff)

double biggestDecrease(std::string fileName, uint32_t startLine = 1, uint16_t numOfCol = 2, uint16_t column = 1);
//returns biggest difference in values in column starting from startLine

};





double zeroProtect(double valueProtected);

#endif

#ifndef __ETC_H__
#define __ETC_H__


namespace etc
{
    //shows array which is ending by 0, 0 is terminating process
    void showArray(double array[]);
    void showArray(int array[]);
    void showArray(std::vector<double> & vect);


    //sortig algorithm, sortes both arrays but control array is array1, 
    // == it sorts pairs of data by elements of array1
    void insertionSort(double array1[], double array2[]);


    //function used for quick sort algorithm
    int partition(double array[], double array1[], int start, int end);

    //quicksort algorithm for sorting arrays, control array is array1 and arrray2 is resorted with respect for array1
    //so cartesian product of all pairs is same as before sorting 
    void quickSort(double array[], double array1[], int start, int end);


    //function used for sorting and summing arrays
    //if there are more values y for one specific x
    //algorithm will add all the y of some x to y0
    //x = {1, 1, 5, 1, 8, 1, 8}
    //y = {1, 1, 1, 1, 1, 1, 1};
    //
    // ==> 
    //
    //x = {1, 5, 8}
    //y = {4, 1, 2}

    bool arraySum(double array1[], double array2[]);

    int positionInArray(double array[], double wanted);
    int positionInArray(float array[], float wanted);
    int positionInArray(int array[], int wanted);


};



#endif
