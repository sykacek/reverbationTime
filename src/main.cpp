#include "headers/myFile.h"



int main()
{

    std::vector<std::string> files;

    fileLib::loadFromPath("../src/audioDat/", files);

    int fils = files.size();

    if(files.size() > 0)
    {
        uint32_t numOfCol, tempLen{0}, minLen = fileLib::fileLineLenght(files[0]),
        tempMax;

        std::string result, temp;

        for(int i = 0; i < fils; i++)
        {
            fileLib::fileCutToLine(files[i], 3);
            numOfCol = fileLib::columnsInLine(files[i]);
            

            for(int j = 0; j < numOfCol - 2; j++)
            {
                fileLib::fileColumnRemove(files[i], numOfCol - j, numOfCol - j - 1);
            }

            fileLib::fileFabs(files[i], "");
            fileLib::fileAproximation(files[i], "", 600);

            tempMax = fileLib::maximumInCol(files[i]);
            fileLib::fileShortenOrdered(files[i], tempMax);

            tempLen = fileLib::fileLineLenght(files[i]);
            if(tempLen < minLen)
                minLen = tempLen;

            std::stringstream devide(files[i]);

            result.clear();


            for(int i = 0; i < 2; i++)
            {
                getline(devide, temp, '/');
                result.append(temp);
                result.append("/");
            }

            
            getline(devide, temp, '/');
            result.append(temp);
            result.append("Copy/");
            getline(devide, temp, '/');
            result.append(temp);

            fileLib::fileCopy(files[i], result);
            
        }

        
        
        //std::cout << "minLen is " << minLen << "\n";

        for(int i = 0; i < files.size(); i ++)
        {
            fileLib::fileCutFromLine(files[i], minLen, 2);
        }

        fileLib::filesAvarge(files, "../out/data/average.dat");
        fileLib::fileLogCopy("../out/data/average.dat", "");


        fileLib::loadFromPath("../src/audioDatCopy/", files);
        for(int i = 0; i < files.size(); i++)
        {
            //fileLib::fileAproximation(files[i], "", 100);
            uint32_t max;

            max = fileLib::maximumInCol(files[i]);

            if(max == 0)
            {
                std::cout << "error here\n";
                return 0;
            }

            fileLib::fileShortenOrdered(files[i], max);
            fileLib::fileLogCopy(files[i], "");
        
        }
    }
    else
        std::cout << "unable to openFile\n";


    return 0;

}

