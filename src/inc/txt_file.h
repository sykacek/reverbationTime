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
#define CACHE_BUFFER_SIZE (524288) //buffer of floats will be 2 MB

/* Proccessing buffer size for approximating audio samples*/
#define PROCCESSING_BUFFER_SIZE (64)

/* More generic defines */
#define DELTA (1)
#define FILE_DELTA (0.5)
#define PI (3.1415926)
/* define output data precision */
#define PREC 4
/* defualt file locations */
#define PATH_FILEAPROXIMATION               "src/temp/fileAproximation.txt"
#define PATH_FILECOLUMNREMOVE               "src/temp/fileColumnRemove.txt"
#define PATH_FILECUTFROMLINE                "src/temp/fileCutFromLine.txt"
#define PATH_FILECUTTOLINE                  "src/temp/fileCutToLine.txt"
#define PATH_FILEFABS                       "src/temp/fileFabstxt"
#define PATH_FILELOGCOPY                    "src/temp/fileLogCopy.txt"
#define PATH_FILESHORTENORDER               "src/temp/fileShortenOrdered.txt"
/**
 * Library functions for text handling
 */



namespace txt
{
    /* lib function, check if file has some .*** extention*/
     std::string nameProtect(std::string fileName);

    /*print additional info about opening and closing files*/
     void message(std::string text, bool mode);

    /* determine size of array */
     uint16_t arraySize(float * arr);

    /* returns number of tab-separated cells in the file*/
    uint32_t fileLen(std::string fileName);
    
    /* return number of '\n' separated lines in the file*/
    uint32_t fileLineLen(std::string fileName);
    
    /* returns number of tab-separated columns per line in the file*/
    uint32_t colsPerRow(std::string fileName);

    /* reads file into the array of floats*/
    bool fileRead(std::string fileName, float readArray[]);

    /* reads file into  2 arrays of floats, handy for reading 2 column files*/
    bool fileRead(std::string fileName, float readArray1[], float readArray2[]);

    /**
     * Reads cells from the file located in the pos-th column and stores them in readvector of floats
     * pos is indexed from 0
     */
    bool fileRead(std::string fileName, std::vector<float> &readvector, uint16_t col_per_row = 2, uint16_t pos = 1);

    /* write data to the text file in one column*/
    bool fileWrite(std::string fileName, float array1[]);

    /* write data to the text file in two columns*/
    bool fileWrite(std::string fileName, float array1[], float array2[]);

    /* write data to the text file, every value on new line*/
    bool fileWrite(std::string fileName, std::vector<float> & vect);

    /* write data to the text file in two columns*/
    bool fileWrite(std::string fileName, std::vector<float> & one, std::vector<float> & two);

    /* append data to the text file, every value on new line*/
    bool fileAppendLine(std::string fileName, float array1[]);

    /*append data to the next file, values are tab-separated*/
    bool fileAppendTab(std::string fileName, float array1[]);

    /*reduce number of lines of file n times*/
    bool fileAproximation(std::string fileRead, std::string fileWrite, uint n = 10);
    
    /* vect[i] = 20*log(vect[i])*/
    bool logValue(std::vector<float> &vect);

    /* clear contents of text file*/
    bool fileClear(std::string fileName);

    /* copy contents of fileRead to fileWrite, formated by col_per_row */
    bool fileCopy(std::string fileRead, std::string fileWrite, uint32_t col_per_row = 2);

    /* copy contents of fileRead to fileWrite, second column has logarithmic values*/
    bool fileLogCopy(std::string fileNameRead, std::string fileNameWrite);
    
    /* returns index where is maximum value in column*/
    uint32_t maximumInCol(std::string fileName, uint32_t col_per_row = 2, uint32_t column = 1);

    /* returns index where is minimum value in column */
    uint32_t minimumInCol(std::string fileName, uint32_t col_per_row = 2, uint32_t column = 1);

    /* copy contents of fileRead to fileWrite, all values are positive*/
    bool fileFabs(std::string fileRead, std::string fileWrite, uint32_t col_per_row = 2);
    
    /* remove column in file, indexing from 0*/
    bool fileColumnRemove(std::string fileName, uint16_t col_per_row = 3, uint16_t eliminate = 1);
    
    /* rewrite file from index startPoint, value between lines differ by d*/
    bool fileShortenOrdered(std::string fileName, uint32_t startPoint, float d = 0);

    /* rewrite file to line index cut*/
    bool fileCutFromLine(std::string fileName, uint32_t cut, uint32_t col_per_row = 2);

    /* rewrite file from line index cut*/
    bool fileCutToLine(std::string fileName, uint32_t cut, uint32_t col_per_row = 2);
    
    /* average values from files, write them to the fileWrite, formated*/
    bool filesAverage(std::vector<std::string> & files, std::string fileWrite, uint32_t col_per_row = 2, uint32_t order1 = 0, uint32_t order2 = 1);
    
    /* returns value from first column on same line as value*/
    float returnTimeFromValue(std::string fileName, float value, uint16_t col_per_row = 2, uint16_t column = 1);
    
    /* load files from path to %vector
     * WARNING: if path is relative, it will be relative to the directory where the program is run!
    */
    bool loadFromPath(std::string path, std::vector<std::string> & files);
    
    /* returns index of line where is first discover different between values biger than diff*/
    uint32_t findLineFromDiff(std::string fileName, uint32_t startLine = 1, float diff = -30, uint16_t col_per_row = 2, uint16_t column = 1);
    
    /* returns biggest decrease of values in column*/
    float biggestDecrease(std::string fileName, uint32_t startLine = 1, uint16_t col_per_row = 2, uint16_t column = 1);
};

#endif
