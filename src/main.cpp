#include "inc/txt_file.h"
#include <errno.h>

/**
 * program arguments:
 * 1 - apx_coeff - coefficient to be used to aproximate data files
 */
int main(int argc, char **argv)
{
    /* read program arguments */
    int apx_coef = atoi(argv[1]);
    if(apx_coef < 2){
        printf("Error: Inavlid argument apx_coef\n");
        return -EINVAL;
    }

    /* load files from path */
    std::vector<std::string> files;
    txt::loadFromPath("src/audio_dat/", files);
    int fils = files.size();

    if(files.size() > 0){
        uint32_t numOfCol = 0;
        uint32_t tempLen = 0; 
        uint32_t minLen = txt::fileLineLenght(files[0]);
        uint32_t tempMax = 0;
        std::string result, temp;

        /* cut all data from peak, prepare files to be averaged */
        for(int i = 0; i < fils; i++){
            txt::fileCutToLine(files[i], 3);
            numOfCol = txt::columnsInLine(files[i]);

            for(uint j = 0; j < numOfCol - 2; j++)
                txt::fileColumnRemove(files[i], numOfCol - j, numOfCol - j - 1);

            txt::fileFabs(files[i], "");
            txt::fileAproximation(files[i], "", apx_coef);

            tempMax = txt::maximumInCol(files[i]);
            txt::fileShortenOrdered(files[i], tempMax);

            tempLen = txt::fileLineLenght(files[i]);

            if(tempLen < minLen)
                minLen = tempLen;
            std::stringstream devide(files[i]);
            result.clear();

            for(int i = 0; i < 1; i++){
                getline(devide, temp, '/');
                result.append(temp);
                result.append("/");
            }
            
            getline(devide, temp, '/');
            result.append(temp);
            result.append("cp/");
            getline(devide, temp, '/');
            result.append(temp);

            txt::fileCopy(files[i], result);
        }

        /* cut all fata files to same lenght, neccessary to be averaged */
        for(long unsigned int i = 0; i < files.size(); i ++){
            txt::fileCutFromLine(files[i], minLen, 2);
        }

        /* average files and set decreasement values logarithmic */
        txt::filesAverage(files, "output/data/average.dat");
        txt::fileLogCopy("output/data/average.dat", "");

        txt::loadFromPath("src/audio_datcp/", files);
        for(long unsigned int i = 0; i < files.size(); i++){
            uint32_t max;
            max = txt::maximumInCol(files[i]);

            txt::fileShortenOrdered(files[i], max);
            txt::fileLogCopy(files[i], "");
        }

        return 0;
    } else {
        std::cout << "Error: failed to open files\n";
        return -ENFILE;
    }
}