#include "inc/txt_file.h"
#include <errno.h>

int main(void)
{
    //read file names
    std::vector<std::string> files;
    txt_file::loadFromPath("src/audio_dat/", files);
    int fils = files.size();

    if(files.size() > 0){
        uint32_t numOfCol, tempLen{0}, minLen = txt_file::fileLineLenght(files[0]),
        tempMax;
        std::string result, temp;

        for(int i = 0; i < fils; i++){
            txt_file::fileCutToLine(files[i], 3);
            numOfCol = txt_file::columnsInLine(files[i]);

            for(int j = 0; j < numOfCol - 2; j++)
                txt_file::fileColumnRemove(files[i], numOfCol - j, numOfCol - j - 1);

            txt_file::fileFabs(files[i], "");
            txt_file::fileAproximation(files[i], "", 600);

            tempMax = txt_file::maximumInCol(files[i]);
            txt_file::fileShortenOrdered(files[i], tempMax);

            tempLen = txt_file::fileLineLenght(files[i]);

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

            txt_file::fileCopy(files[i], result);
        }

        for(int i = 0; i < files.size(); i ++){
            txt_file::fileCutFromLine(files[i], minLen, 2);
        }
        txt_file::filesAvarge(files, "output/data/average.dat");
        txt_file::fileLogCopy("output/data/average.dat", "");

        txt_file::loadFromPath("src/audio_datcp/", files);
        for(int i = 0; i < files.size(); i++){
            //txt_file::fileAproximation(files[i], "", 100);
            uint32_t max;

            max = txt_file::maximumInCol(files[i]);

            if(max == 0){
                std::cout << "error here\n";
                return 0;
            }

            txt_file::fileShortenOrdered(files[i], max);
            txt_file::fileLogCopy(files[i], "");
        }
    } else {
        std::cout << "unable to open File\n";
        return -ENFILE;
    }

    return 0;
}