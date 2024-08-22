/**
 * 
 * Library for handling and proccessing text files
 * 
 * Author: Michal Sykacek 2024 
 */
#ifndef __MYFILE_H__
#define __MYFILE_H__

/*Includes*/
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <math.h>
#include <filesystem>
#include <sstream>
#include <cstring>

#define CACHE_BUFFER_SIZE (100000)
#define PROCCESSING_BUFFER_SIZE (64)
#define DELTA (1)
#define FILE_DELTA (0.5)
#define PI (3.1415926)

namespace txt_file
{
    static std::string nameProtect(std::string fileName);
    void message(std::string text, bool mode);
    uint32_t fileLenght(std::string fileName);
    uint32_t fileLineLenght(std::string fileName);
    uint32_t arrayLenght(double array[]);
    uint32_t arrayLenght(std::vector<double> & vect);
    uint32_t columnsInLine(std::string fileName);
    bool fileRead(std::string fileName, double readArray[]);
    bool fileRead(std::string fileName, double readArray1[], double readArray2[]);
    bool fileRead(std::string fileName, std::vector<double> & readvector, uint16_t NumberInRow = 2, uint16_t orderPlace = 1);
    //can read data from ALL sized files, Number of Rows says how many values there are in one row
    //orderPlace starts at zero, indexing same as with arrays --> third column has orderPlace 2
    //WARNING function is NOT using NAMEPROTECT, cou have to write name with fileformat

    bool fileWrite(std::string fileName, double array1[]);
    bool fileWrite(std::string fileName, double array1[], double array2[]);
    bool fileWrite(std::string fileName, std::vector<double> & vect);
    bool fileWrite(std::string fileName, std::vector<double> & one, std::vector<double> & two);
    bool fileAppendLine(std::string fileName, double array1[]);
    bool fileAppendTab(std::string fileName, double array1[]);
    bool fileAppendTab(std::string fileNames[], std::string outFile, int len);
    bool fileAproximation(std::string fileRead, std::string fileWrite, int aproximate = 10);
    bool fileExpand1(std::string fileRead, std::string fileWrite, int aproximate = 10);
    bool fileExpand2(std::string fileRead, std::string fileWrite, int aproximate = 10);
    bool arrayAproximation(double array1[], double array2[], int times);
    bool arrayAproximationTranspose(double array1[], double array2[], int times);
    bool logValue(std::vector<double> &vect);
    bool fileClear(std::string fileName);
    bool fileCopy(std::string fileRead, std::string fileWrite, uint32_t numOfCol = 2);
    bool fileLogCopy(std::string fileNameRead, std::string fileNameWrite, uint16_t numberInRow = 2, uint16_t order1 = 0, uint16_t order2 = 1);
    uint32_t maximumInCol(std::string fileName, uint32_t numOfCol = 2, uint32_t column = 1);
    uint32_t minimumInCol(std::string fileName, uint32_t numOfCol = 2, uint32_t column = 1);
    bool fileFabs(std::string fileRead, std::string fileWrite, uint32_t numOfCol = 2);
    bool fileColumnRemove(std::string fileName, uint16_t numOfCol = 3, uint16_t eliminate = 1);
    bool fileShortenOrdered(std::string fileName, uint32_t startPoint, double d = 0);
    bool fileCutFromLine(std::string fileName, uint32_t cut, uint32_t numOfCol = 2);
    bool fileCutToLine(std::string fileName, uint32_t line, uint32_t numOfCol = 2);
    bool filesAvarge(std::vector<std::string> & files, std::string fileWrite, uint32_t numOfCol = 2, uint32_t order1 = 0, uint32_t order2 = 1);
    double returnTimeFromValue(std::string fileName, double value, uint16_t numOfCol = 2, uint16_t column = 1);
    bool loadFromPath(std::string path, std::vector<std::string> & files);
    uint32_t findLineFromDiff(std::string fileName, uint32_t startLine = 1, double diff = -30, uint16_t numofCol = 2, uint16_t column = 1);
    double biggestDecrease(std::string fileName, uint32_t startLine = 1, uint16_t numOfCol = 2, uint16_t column = 1);
};

double zeroProtect(double valueProtected);

namespace etc
{
    void showArray(double array[]);
    void showArray(int array[]);
    void showArray(std::vector<double> & vect);
    void insertionSort(double array1[], double array2[]);
    int partition(double array[], double array1[], int start, int end);
    void quickSort(double array[], double array1[], int start, int end);
    bool arraySum(double array1[], double array2[]);
    int positionInArray(double array[], double wanted);
    int positionInArray(float array[], float wanted);
    int positionInArray(int array[], int wanted);
};

#endif
