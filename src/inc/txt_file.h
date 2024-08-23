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

/* Library defines*/

/* Maximum number of cells in file */
#define CACHE_BUFFER_SIZE (100000)

/* Proccessing buffer size for approximating audio samples*/
#define PROCCESSING_BUFFER_SIZE (64)

/* More generic defines*/
#define DELTA (1)
#define FILE_DELTA (0.5)
#define PI (3.1415926)

/* defualt file locations*/
#define PATH_FILEAPROXIMATION           "fileAproximation.txt"
#define PATH_FILECOLUMNREMOVE           "fileColumnRemove.txt"
#define PATH_FILECUTFROMLINE            "fileCutFromLine.txt"
#define PATH_FILECUTTOLINE              "fileCutToLine.txt"
#define PATH_FILEFABS                   "fileFabs.txt"
#define PATH_FILELOGCOPY                "fileLogCopy.txt"
#define PATH_FILESHORTENORDERED         "fileShortenOrdered.txt"

/**
 * Library functions for text handling
 */

namespace txt_file
{
    /*static lib function, check if file has .txt extention*/
    static std::string nameProtect(std::string fileName);

    /*print additional info about opening and closing files*/
    static void message(std::string text, bool mode);

    /* determine size of array */
    static uint16_t arr_s(double * arr);

    /* returns number of tab-separated cells in the file*/
    uint32_t fileLenght(std::string fileName);
    
    /* return number of lines in the file*/
    uint32_t fileLineLenght(std::string fileName);
    
    /* returns number of tab-separated columns per line in the file*/
    uint32_t columnsInLine(std::string fileName);

    /* reads file into the array of doubles*/
    bool fileRead(std::string fileName, double readArray[]);

    /* reads file into  2 arrays of doubles, handy for reading 2 column files*/
    bool fileRead(std::string fileName, double readArray1[], double readArray2[]);

    /**
     * Reads cells from the file located in the pos-th column and stores them in readvector of doubles
     * pos is indexed from 0
     */
    bool fileRead(std::string fileName, std::vector<double> &readvector, uint16_t col_per_row = 2, uint16_t pos = 1);

    /* write data to the text file, every value on new line*/
    bool fileWrite(std::string fileName, double array1[]);

    /* write data to the text file in two columns*/
    bool fileWrite(std::string fileName, double array1[], double array2[]);

    /* write data to the text file, every value on new line*/
    bool fileWrite(std::string fileName, std::vector<double> & vect);

    /* write data to the text file in two columns*/
    bool fileWrite(std::string fileName, std::vector<double> & one, std::vector<double> & two);

    /* append data to the text file, every value on new line*/
    bool fileAppendLine(std::string fileName, double array1[]);

    /*append data to the next file, values are tab-separated*/
    bool fileAppendTab(std::string fileName, double array1[]);

    /*reduce number of lines of file n times*/
    bool fileAproximation(std::string fileRead, std::string fileWrite, int n = 10);
    
    /* expand contents of src n times to dest*/
    bool arrayExpand(double dest[], double src[], int n);

    /* vect[i] = 10*log(vect[i])*/
    bool logValue(std::vector<double> &vect);

    /* clear contents of text file*/
    bool fileClear(std::string fileName);

    /* copy contents of fileRead to fileWrite, formated by col_per_row */
    bool fileCopy(std::string fileRead, std::string fileWrite, uint32_t col_per_row = 2);

    /* copy contents of fileRead to fileWrite, second column has logarithmic values*/
    bool fileLogCopy(std::string fileNameRead, std::string fileNameWrite, uint16_t col_per_row = 2, uint16_t order1 = 0, uint16_t order2 = 1);
    
    /* returns index where is maximum value in column*/
    uint32_t maximumInCol(std::string fileName, uint32_t col_per_row = 2, uint32_t column = 1);

    /* returns index where is minimum value in column */
    uint32_t minimumInCol(std::string fileName, uint32_t col_per_row = 2, uint32_t column = 1);

    /* copy contents of fileRead to fileWrite, all values are positive*/
    bool fileFabs(std::string fileRead, std::string fileWrite, uint32_t col_per_row = 2);
    
    /* remove column in file, indexing from 0*/
    bool fileColumnRemove(std::string fileName, uint16_t col_per_row = 3, uint16_t eliminate = 1);
    
    /* rewrite file from index startPoint, value between lines differ by d*/
    bool fileShortenOrdered(std::string fileName, uint32_t startPoint, double d = 0);

    /* rewrite file to line index cut*/
    bool fileCutFromLine(std::string fileName, uint32_t cut, uint32_t col_per_row = 2);

    /* rewrite file from line index cut*/
    bool fileCutToLine(std::string fileName, uint32_t cut, uint32_t col_per_row = 2);
    
    /* average values from files, write them to the fileWrite, formated*/
    bool filesAverage(std::vector<std::string> & files, std::string fileWrite, uint32_t col_per_row = 2, uint32_t order1 = 0, uint32_t order2 = 1);
    
    /* returns value from first column on same line as value*/
    double returnTimeFromValue(std::string fileName, double value, uint16_t col_per_row = 2, uint16_t column = 1);
    
    /* load files from path to %vector
     * WARNING: if path is relative, it will be relative to the directory where the program is run!
    */
    bool loadFromPath(std::string path, std::vector<std::string> & files);
    
    /* returns index of line where is first discover different between values biger than diff*/
    uint32_t findLineFromDiff(std::string fileName, uint32_t startLine = 1, double diff = -30, uint16_t col_per_row = 2, uint16_t column = 1);
    
    /* returns biggest decrease of values in column*/
    double biggestDecrease(std::string fileName, uint32_t startLine = 1, uint16_t col_per_row = 2, uint16_t column = 1);
};

#endif
