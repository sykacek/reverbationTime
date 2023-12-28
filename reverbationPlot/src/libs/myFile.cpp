#include "../headers/myFile.h"


std::string fileLib::nameProtect(std::string fileName)
{
    for(int i = 0; fileName[i] != 0; i++){
        if(fileName[i] == '.')
            return fileName;
        else
            ;
    }

    fileName += ".txt";

    return fileName;
}

void fileLib::message(std::string text, bool mode)
{
    if(mode == true)
        std::cout << "Soubor " << text << " byl otevřen\n";
    else 
        std::cout << "Soubor " << text << " byl zavřen\n";
    

}

uint32_t fileLib::fileLenght(std::string fileName)
{
    fileName = fileLib::nameProtect(fileName);

    std::fstream testName(fileName, std::ios_base::in);

    if(testName.is_open()){

        std::cout << "(fileLenght)";
        message(fileName, true);
        uint32_t i = 0;
        double temp;

        while(testName){

            testName >> temp;
            if(!testName){
                std::cout << "(fileLenght)velikost souboru " << fileName << " je " << i << " řádků\n";
                std::cout << "(fileLenght)";
                message(fileName, false);
                return i;
            }
            i++;
        }

        testName.close();

        std::cout << "(fileLenght)";
        message(fileName, false);
        
    } else{
        std::cout << "(FileLenght)Soubor " << fileName << " nebyl nalezen\n";
    }
    return (uint32_t) 0;
}

uint32_t fileLib::fileLineLenght(std::string fileName)
{
    std::fstream read(fileName, std::ios_base::in);

    if(read.is_open())
    {
        std::cout << "(fileLineLenght)";
        message(fileName, true);

        std::string temp{0};
        uint32_t len = 0;

        while(!read.eof())
        {
            getline(read, temp);
            len ++;
        }

        std::cout << "*(fileLineLenght)";
        message(fileName, false);

        read.close();

        std::cout << "len is " << len << "\n";

        return len;
    }
    else
    {
        std::cout << "unable to open file " << fileName << "\n";
        return 0;
    }
}

uint32_t fileLib::arrayLenght(double array[])
{
    double *p = array;

    for(uint32_t i = 0; i < maxSize; i++){
        if(*(p + i) == 0){
            return i;
        } else ;
    }

    return 0;
}

uint32_t fileLib::arrayLenght(std::vector<double> & vect)
{
    uint32_t len = vect.size();
    std::cout << "len is " << len << "\n";
    return len;
}

uint32_t fileLib::columnsInLine(std::string fileName)
{
    std::fstream read(fileName, std::ios_base::in);
    std::string line, temp{};
    uint32_t counter = 0;

    getline(read, line);
    read.close();

    std::stringstream strem(line);

    while(strem >> temp)
        counter++;

    return counter;
}
bool fileLib::fileRead(std::string fileName, double readArray[])
{
    fileName = fileLib::nameProtect(fileName);

    uint32_t amountOfValues;

    std::cout << "(FileRead)";
    amountOfValues = fileLenght(fileName);

    std::fstream testFile1(fileName, std::ios_base::in);
    if(testFile1.is_open()){
        std::cout << "(fileRead)";
        message(fileName, true);
        double *p = &readArray[0];

        for(uint32_t i = 0; i < amountOfValues; i++)
            testFile1 >> *(p+i);

        testFile1.close();

        std::cout << "(fileRead)";
        message(fileName, false);

        return true;

    } else{
        std::cout << "Soubor " << fileName << " se nepodařilo otevřít\n";
    }
    return false;
}

bool fileLib::fileRead(std::string fileName, double readArray1[], double readArray2[])
{
    fileName = fileLib::nameProtect(fileName);

    double array[maxLen] = {};

    bool done = fileRead(fileName, array);

    uint32_t amountOfValues;
    amountOfValues = fileLenght(fileName);

    double *x = readArray1, *y = readArray2;

    for(uint32_t i = 0; i < amountOfValues; i++){
        if(i%2 == 0)
            *(x+i/2) = array[i];
        else
            *(y+(i-1)/2) = array[i];

    }

    return done;
}

bool fileLib::fileRead(std::string fileName, std::vector<double> &readvector, uint16_t NumberInRow, uint16_t orderPlace)
{

    std::fstream file(fileName, std::ios_base::in);

    

    if(file.is_open())
    {
        double temp;
        std::cout << "(fileRead)";
        message(fileName, true);

        uint32_t len = fileLenght(fileName);

        for(int i = 0; i < len; i++)
        {
            file >> temp;
            if(i % NumberInRow == orderPlace)
            {   
                readvector.push_back(temp);
            }
            
        }
        

        std::cout << "*(fileRead)";
        message(fileName, false);
        return true;
    }
    else
    {
    std::cout << "file " << fileName << " was not opened\n";
    return false;
    }
}

bool fileLib::fileWrite(std::string fileName, double array1[])
{
    fileName = fileLib::nameProtect(fileName);

    std::fstream file(fileName, std::ios_base::out);

    if(file.is_open()){
        std::cout << "(fileWrite)";
        message(fileName, true);

        int lenght = fileLib::arrayLenght(array1);
        

        double *p = array1;

        for(int i = 0; i < lenght; i++){
            file << *(p +i) << "\n";
        }

        file.close();
        std::cout << "(fileWrite)";
        message(fileName, false);
        return true;
    } else
        return false;
}

bool fileLib::fileWrite(std::string fileName, double array1[], double array2[])
{
    
    fileName = fileLib::nameProtect(fileName);

    std::fstream file(fileName, std::ios_base::out);

    if(file.is_open()){
        std::cout << "(fileWrite)";
        message(fileName, true);

        int lenght = fileLib::arrayLenght(array1);
        

        double *p = array1;
        double *z = array2;

        for(int i = 0; i < lenght; i++){
            file << *(p +i) << "\t" << *(z+i) << "\n";
        }

        file.close();
        std::cout << "(fileWrite)";
        message(fileName, false);
        return true;
    } else
    {
        std::cout << "Soubor se nepodařilo otevřít\n";
        return false;
    }
}

bool fileLib::fileWrite(std::string fileName, std::vector<double> &vect)
{
    
    std::fstream file(fileName, std::ios_base::out);

    uint32_t len = arrayLenght(vect);

    if(file.is_open())
    {
        std::cout << "(fileWrite)";
        message(fileName, true);

        for(int i = 0; i < len; i++)
        {
            file << vect[i] << "\n";
        }

        std::cout << "*(fileWrite)";
        message(fileName, false);
        return true;
    }
    else
    {
        std::cout << "file " << fileName << " was unable to open\n";
        return false;
    }
    
}

bool fileLib::fileWrite(std::string fileName, std::vector<double> &one, std::vector<double> &two)
{
    uint32_t len = one.size();

    std::fstream file(fileName, std::ios_base::out);

    if(file.is_open())
    {
        std::cout << "(fileWrite)";
        message(fileName, true);
        for(int i = 0; i < len; i ++)
        {
            file << one[i] << "\t" << two[i] << "\n";
        }

        std::cout << "*(fileWrite)";
        message(fileName, false);

        return true;
    }
    else
    {
        std::cout << "file " << fileName << " was unable to open\n";
        return false;
    }

    
}

bool fileLib::fileAppendLine(std::string fileName, double array1[])
{
    fileName = fileLib::nameProtect(fileName);

    std::fstream file(fileName, std::ios_base::app);
    if(file.is_open())
    {
        std::cout << "(fileAppend)";
        message(fileName, true);

        int fileLen = fileLib::arrayLenght(array1);

        std::cout << "FileLen is " << fileLen << std::endl;

        double * p = array1;

        for(int i = 0; i < fileLen; i++){
            std::cout << i << "\n" << *(p + i);
            file << *(p + i) << "\n";
        }

        file.close();
        std::cout << "(fileAppend)";
        message(fileName, false);
        return true;
} else
    return false;
}

bool fileLib::fileAppendTab(std::string fileName, double array1[])
{
    fileName = fileLib::nameProtect(fileName);

    std::fstream file(fileName, std::ios_base::app);
    if(file.is_open())
    {
        std::cout << "(fileAppend)";
        message(fileName, true);

        int fileLen = fileLib::arrayLenght(array1);

        std::cout << "FileLen is " << fileLen << std::endl;

        double * p = array1;

        for(int i = 0; i < fileLen; i++){
            std::cout << i << "\n" << *(p + i);
            file << *(p + i) << "\t";
        }

        file << "\n";

        file.close();
        std::cout << "(fileAppend)";
        message(fileName, false);
        return true;
} else
    return false;
}

bool fileLib::fileAppendTab(std::string fileNames[], std::string outFile, int len)
{
    double array[maxLen];
    return true;
}

bool fileLib::fileAproximation(std::string fileRead, std::string fileWrite, int aproximate)
{
    if(fileWrite == "")
    {
        //std::cout << "empty string \n";
        fileWrite = "../src/temp/fileAproximation.txt";
    }
    std::fstream read(fileRead, std::ios_base::in);
    std::fstream write(fileWrite, std::ios_base::out);

    if(read.is_open() && write.is_open())
    {
        std::cout << "(fileAproximation)";
        message(fileRead, true);
        message(fileWrite, true);


        uint32_t len = fileLenght(fileRead);
        len /= aproximate;
        len /= 2;
        len -= 1;

        double read1, read2, sum1, sum2;

        for(uint32_t i = 0; i < len; i++)
        {
            sum1 = 0;
            sum2 = 0;
            for(int j = 0; j < aproximate; j++)
            {
                read >> read1;
                read >> read2;
                sum1 += read1;
                sum2 += read2;
            }
            sum1 /= aproximate;
            sum2 /= aproximate;
            write << sum1 << "\t" << sum2 << "\n";
        }


        std::cout << "(fileAproximation)";
        message(fileRead, false);
        message(fileWrite, false);

        read.close();
        write.close();

        if(fileWrite == "../src/temp/fileAproximation.txt")
        {
            std::cout << "working well\n";
            fileCopy("../src/temp/fileAproximation.txt", fileRead);
        }


        return true;
    }
    else
    {
        std::cout << "files were unable to open\n";
        return false;
    }
}



bool fileLib::fileExpand1(std::string fileRead, std::string fileWrite, int aproximate)
{
    fileRead = fileLib::nameProtect(fileRead);
    fileWrite = fileLib::nameProtect(fileWrite);

    std::cout << "FILEAPROXIMATION";
    uint32_t fileLen = fileLenght(fileRead);

    uint32_t ratio = aproximate/fileLen;

    //std::cout << "ratio is " << ratio << "\n";

    double readArray[maxLen] = {};

    std::cout << "FILEAPROXIMATION";
    bool done = fileLib::fileRead(fileRead, readArray);
    
    double writeArray[maxLen];


    for(int i = 0; i < fileLen; i++)
    {
        for(int j = 0; j < ratio; j++)
        {
            writeArray[i*ratio + j] = readArray[i];
            //std::cout << i*ratio + j << "\t" << writeArray[i*ratio + j] << "\n";
        }
    } 

    std::cout << "FILEAPROXIMATION";
    bool done1 = fileLib::fileWrite(fileWrite, writeArray);



    return done && done1;
}

bool fileLib::fileExpand2(std::string fileRead, std::string fileWrite, int aproximate)
{
    fileRead = fileLib::nameProtect(fileRead);
    fileWrite = fileLib::nameProtect(fileWrite);

    std::cout << "FILEAPROXIMATION";
    uint32_t fileLen = fileLib::fileLenght(fileRead)/2;

    uint32_t ratio = fileLen/aproximate;

    std::cout << "ratio is " << ratio << "\n";

    double readArray1[maxLen] = {}, readArray2[maxLen] = {}, writeArray1[maxLen] = {}, writeArray2[maxLen] = {};

    std::cout << "FILEAPROXIMATION";
    bool done = fileLib::fileRead(fileRead, readArray1, readArray2);
    

    for(int i = 0; i < fileLen; i ++)
    {
        for(int j = 0; j < ratio; j++)
        {
            writeArray1[i*ratio + j] = readArray1[i];
            writeArray2[i*ratio + j] = readArray2[i];

            std::cout << i*ratio + j << "\t" << writeArray1[i*ratio +j] << "\t" << writeArray2[i*ratio + j] << "\n";
        }
    }

    std::cout << "FILEAPROXIMATION";
    bool done1 = fileLib::fileWrite(fileWrite, writeArray1, writeArray2);



    return done && done1;
}

bool fileLib::arrayAproximation(double array1[], double array2[], int times)
{
    double * one = array1;
    double * two = array2;

    int len = fileLib::arrayLenght(array1);
    std::cout << "délka čtené řady je " << len << std::endl;

    for(int i = 0; i < len; i++)
    {
        for(int j = 0; j < times; j++)
        {
            *(two + i*times + j) = *(one + i);
        }
    }

    len = fileLib::arrayLenght(array2);
   std::cout << "délka vypsané řady je " << len << "\n";

    if(len > 0)
        return true;
    else 
        return false;

}

bool fileLib::arrayAproximationTranspose(double array1[], double array2[], int times)
{
    int transpose = times/2;

    //std::cout << "transpose is " << transpose << "\n";

    bool a = fileLib::arrayAproximation(array1, array2, times);

    int len = fileLib::arrayLenght(array2);

    //std::cout << "len is " << len << "\n";

    double first = array2[0];

    double * p = array2;

    for(int i = 0; i < len; i ++)
    {
        if(i >= len - transpose)
            *(p + i) = first;
        else
        {
            *(p + i) = *(p + i + transpose);
            //std::cout << *(p + i) << "\n";
        }
        
    }


    return a;
}

bool fileLib::logValue(std::vector<double> &vect)
{
    uint32_t len = vect.size();
    double temp1, temp2;


    for(int i = 0; i < len; i++)
    {
        temp1 = vect[i];
        temp2 = 10*log10(temp1);
        vect[i] = temp2;
    }

    if(len > 0)
        return true;
    else
        return false;
}

bool fileLib::fileClear(std::string fileName)
{
    std::fstream clean(fileName, std::ios_base::out);

    if(clean.is_open())
    {
        clean.close();
        return true;
    }
    else
        return false;
}

bool fileLib::fileCopy(std::string fileRead, std::string fileWrite, uint32_t numOfCol)
{
    std::fstream read(fileRead, std::ios_base::in);
    
    std::fstream write(fileWrite, std::ios_base::out);

    

    if(read.is_open() && write.is_open())
    {
        std::cout << "(fileCopy)";
        message(fileRead, true);
        message(fileWrite, true);

        std::string line;

        while(read)
        {
            getline(read, line);
            write << line << "\n";
            
        }


        std::cout << "*(fileCopy)";
        message(fileRead, false);
        message(fileWrite, false);

        read.close();
        write.close();

        return true;
    }
    else
    {
        std::cout << "(fileCopy)unable to open files\n";
        return false;
    }
}

bool fileLib::fileLogCopy(std::string fileNameRead, std::string fileNameWrite, uint16_t numberInRow, uint16_t order1, uint16_t order2)
{
    if(fileNameWrite == "")
        fileNameWrite = "../src/temp/fileLogCopy.txt";

    std::fstream fileRead(fileNameRead, std::ios_base::in);
    
    std::fstream fileWrite(fileNameWrite, std::ios_base::out);

    if(fileRead.is_open() && fileWrite.is_open())
    {
        std::cout << "(fileLogCopy)";
        message(fileNameRead, true);
        message(fileNameWrite, true);

        double temp1, temp2, temp3;
        uint32_t len = fileLenght(fileNameRead);
        std::cout << "len is " << len << "\n";

        for(uint32_t i = 0; i < len; i++)
        {
            fileRead >> temp1;
            if(i % numberInRow == order1)
            {
                fileWrite << temp1 << "\t";
            } 
            else if(i % numberInRow == order2)
            {
                temp2 = fabs(temp1);
                temp3 = 20*log10(temp2);
                fileWrite << temp3 << "\n";
            }

        }
        std::cout << "*(fileLogCopy)";
        message(fileNameRead, false);
        message(fileNameWrite, false);

        fileRead.close();
        fileWrite.close();

        if(fileNameWrite == "../src/temp/fileLogCopy.txt")
            fileCopy("../src/temp/fileLogCopy.txt", fileNameRead);

        return true;
    }
    else
    {
        std::cout << "(fileLogCopy)files were unable to open\n";
        return false;
    }

}

uint32_t fileLib::maximumInCol(std::string fileName, uint32_t numOfCol, uint32_t column)
{
    std::fstream read(fileName, std::ios_base::in);

    uint32_t counter = 0, line = 1;
    double temp, maximum = -1e10, maxLine = 1;

    while(read)
    {
        read >> temp;
        
        if(counter % numOfCol == column)
        {
            if(temp > maximum)
            {
                maximum = temp;
                maxLine = line;
            }
            line ++;
        }
        counter ++;
    }

    read.close();

    return maxLine;
}

uint32_t fileLib::minimumInCol(std::string fileName, uint32_t numOfCol, uint32_t column)
{
    std::fstream read(fileName, std::ios_base::in);

    uint32_t counter = 0, line = 1;
    double temp, minimum = 1e10, maxLine = 1;

    while(read)
    {
        read >> temp;
        
        //std::cout << "gfht\n";
        
        if(counter % numOfCol == column)
        {
            
            if(minimum > temp && read)
            {
                maxLine = line;
                minimum = temp;
            }
            line ++;
        }
        counter ++;
    }

    read.close();

    return maxLine;
}

bool fileLib::fileFabs(std::string fileRead, std::string fileWrite, uint32_t numOfCol)
{
    if(fileWrite == "")
        fileWrite = "../src/temp/fileFabs.txt";

    std::fstream read(fileRead, std::ios_base::in);
    std::fstream write(fileWrite, std::ios_base::out);

    if(read.is_open() && write.is_open())
    {
        std::cout << "(fileFabs)";
        message(fileRead, true);
        message(fileWrite, true);

        double temp;
        uint32_t counter = 0;
        while(read)
        {
            read >> temp;
            if(!read)
                break;
            temp = fabs(temp);
            write << temp;
            if(counter++ % numOfCol == 0)
                write << "\t";
            else
                write << "\n";
        }


        std::cout << "*(fileFabs)";
        message(fileRead, false);
        message(fileWrite, false);

        read.close();
        write.close();

        if(fileWrite == "../src/temp/fileFabs.txt")
            fileCopy("../src/temp/fileFabs.txt", fileRead);

        return true;
    }
    else
    {
        std::cout << "unable to open files\n";
        return false;
    }

}

bool fileLib::fileColumnRemove(std::string fileName, uint16_t numOfCol, uint16_t eliminate)
{
    std::fstream read(fileName, std::ios_base::in);
    std::fstream write("../src/temp/fileColumnRemove.txt", std::ios_base::out);

    if(read.is_open() && write.is_open())
    {
        std::cout << "(fileColumnRemove)";
        message(fileName, true);

        double temp;
        uint32_t counter = 0, pos = numOfCol - 1;

        if(eliminate == pos)
            pos--;

        //std::cout << eliminate << "\t" << pos << "\n";

        while(read)
        {
            read >> temp;
            if(!read)
                break;
            if(counter % numOfCol == eliminate)
                ;//std::cout << "fasddf\n";
            else 
                write << temp << "\t";
            if(counter % numOfCol == pos)
                write << "\n";
            //std::cout << counter << "\n";
            counter++;

        }

        read.close();
        write.close();
        std::cout << "*(fileColumnRemove)";
        message(fileName, false);

        fileCopy("../src/temp/fileColumnRemove.txt", fileName);

        return true;
    }
    else
    {
        std::cout << "unable to open file " << fileName << "\n";
        return false;
    }
}

bool fileLib::fileShortenOrdered(std::string fileName, uint32_t startPoint, double delta)
{
    if(startPoint == 1)
        return true;

    if(startPoint == fileLineLenght(fileName) - 2)
    {
        std::cout << "startPoint is bigger than lenght of file\n";
        return false;
    }
    std::cout << "fileName is " << fileName << "\n";
    std::fstream read1(fileName, std::ios_base::in);
   
    std::fstream write1("../src/temp/fileShortenOrdered.txt", std::ios_base::out);

    if(read1.is_open() && write1.is_open())
    {
        std::cout << "(fileShortenOrdered)";
        message(fileName, true);

        double temp;

        read1 >> temp;

        if(delta == 0)
            delta = temp;

        std::cout << delta << "\n";


        for(uint32_t i = 1; i < 2*startPoint - 2; i++)
        {
            read1 >> temp;
            //std::cout << i << "\t" << temp << "\n";
        }
        
        int counter = 0;
        int i = 1;

        

        while(read1)
        {
            read1 >> temp;
            if(!read1)
                break;
            //std::cout << "counter is " << counter << "\t";
            
            if(counter % 2 == 1)
            {
                //std::cout << temp << "\n";
                write1 << temp << "\n";
            }
            else
            {
                write1 << delta*i++ << "\t";
                //std::cout << delta*i << "\n";
            }

            counter++;
        }


        read1.close();
        write1.close();

        std::cout << "*(fileShortenOrdered)";
        message(fileName, false);

        fileCopy("../src/temp/fileShortenOrdered.txt", fileName);

        return true;
    }
    else
    {
        std::cout << "unable to open file " << fileName << "\n";
        return false;
    }
}

bool fileLib::fileCutFromLine(std::string fileName, uint32_t cut, uint32_t numOfCol)
{
    std::fstream read(fileName, std::ios_base::in);
    std::fstream write("../src/temp/fileCutFromLine.txt", std::ios_base::out);


    if(read.is_open() && write.is_open())
    {
        std::cout << "(fileCutFromLine)";
        message(fileName, true);

        uint32_t len = fileLineLenght(fileName);

        if(len < cut)
        {
            std::cout << "cut line is bigger than size of file\n"
            << "maximum len is " << len/numOfCol << " !\n";
            return false;
        }
        else
        {
            std::string ligne;
            uint32_t count = 0;
            while(count < cut)
            {
                getline(read, ligne);
                write << ligne << "\n";
                count ++;
            }
        }

        read.close();
        write.close();

        std::cout << "*(fileCutFromLine)";
        message(fileName, false);

        fileCopy("../src/temp/fileCutFromLine.txt", fileName);

        return true;
    }
    else
    {
        std::cout << "unable to file " << fileName << "\n";
        return false;
    }
}

bool fileLib::fileCutToLine(std::string fileName, uint32_t line, uint32_t numOfCol)
{
    std::fstream read(fileName, std::ios_base::in);

    std::fstream write("../src/temp/fileCutToLine.dat", std::ios_base::out);


    if(read.is_open() && write.is_open())
    {
        std::cout << "(fileCutToLine)";
        message(fileName, true);

        std::string ligne;

        for(int i = 0; i < line; i++)
            getline(read, ligne);

        while(read)
        {
            getline(read, ligne);
            write << ligne << "\n";
        }
        read.close();
        write.close();

        std::cout << "*(fileCutToLine)";
        message(fileName, false);

        fileCopy("../src/temp/fileCutToLine.dat", fileName, numOfCol);

        return true;
    }
    else
    {
        std::cout << "unable to open files\n";
        return false;
    }
}

bool fileLib::filesAvarge(std::vector<std::string> &files, std::string fileWrite, uint32_t numOfCol, uint32_t order1, uint32_t order2)
{
    std::cout << "numOfCol is: " << numOfCol << "\n";
    uint16_t len = files.size(), counter = 0;
    std::cout << len << "\n";

    std::fstream write(fileWrite, std::ios_base::out);

    double dataRead[numOfCol*bufferSize], temp;

    std::memset(dataRead, 0, sizeof(dataRead));

    bool end = false;

    int k = numOfCol * bufferSize;

    while(!end)
    {
        
        for(uint16_t i = 0; i < len; i++)
        {
            std::fstream read(files[i], std::ios_base::in);

            for(int j = 0; j < counter*bufferSize*numOfCol; j++)
                read >> temp;
     
            for(int j = 0; j < numOfCol*bufferSize; j++)
            {
                read >> temp;
                if(!read)
                {
                    k = j;
                    break;
                }
                dataRead[j] += temp;
            }

            end = read.eof();
            read.close();

        }
        counter++;

        for(int i = 0; i < k; i++)
        {
            write << dataRead[i]/len;
            dataRead[i] = 0;
            
            if(i % numOfCol == (numOfCol - 1))
                write << "\n";
            else 
                write << "\t";
        }
    }

    write.close();

    len = fileLenght(fileWrite);

    if(len > 0)
        return true;
    else
        return false;
}

double fileLib::returnTimeFromValue(std::string fileName, double value, uint16_t numOfCol, uint16_t column)
{
    std::fstream read(fileName, std::ios_base::in);


    if(read.is_open())
    {
        std::cout << "(returnTimeFromValue)";
        message(fileName, true);

        double time, temp;
        uint32_t counter = 0;

        while(read)
        {
            read >> temp;
            if(counter % numOfCol == 0)
                time = temp;

            if(counter++ % numOfCol == column && (temp - fileDelta < value && time + fileDelta > value))
                break;

        }
        std::cout << "*(returnTimeFromValue)";
        message(fileName, false);
        read.close();
        return time;
    }
    else
    {
        std::cout << "unable to open file " << fileName << "\n";
        return 0;
    }
    return 0.0;
}

bool fileLib::loadFromPath(std::string path, std::vector<std::string> &files)
{
    files.clear();

    for(const auto & entry : std::filesystem::directory_iterator(path))
        files.push_back(entry.path());

    if(files.size() > 0)
        return true;
    else
    {
        std::cout << "folder is empty\n";
        return false;
    }
}

uint32_t fileLib::findLineFromDiff(std::string fileName, uint32_t startLine, double diff, uint16_t numofCol, uint16_t column)
{
    std::fstream read(fileName, std::ios_base::in);

    if(read.is_open())
    {
        std::cout << "(findLineFromDiff)";
        message(fileName, true);

        std::string line;
        double temp, max;
        uint32_t counter = 0;

        for(uint32_t i = 1; i < startLine; i++)
            getline(read, line);

        for(int i = 0; i < column; i++)
            read >> temp;

        read >> max;
        diff += max;

        for(int i = max + 1; i < numofCol; i++)
            read >> temp;

        while(read)
        {
            read >> temp;
            if(counter++ % numofCol == column && temp < diff)
                break;
        }
        std::cout << "*(findLineFromDiff)";
        message(fileName, false);
        read.close();
        return counter/numofCol;
    }
    else
    {
        std::cout << "unable to open file " << fileName << "\n";
        return 0;
    }
}

double fileLib::biggestDecrease(std::string fileName, uint32_t startLine, uint16_t numOfCol, uint16_t column)
{
    std::fstream read(fileName, std::ios_base::in);

    if(read.is_open())
    {
        std::cout << "(biggestDecrease)";
        message(fileName, true);

        double temp, maximum, start;
        uint32_t counter = 0;
        std::string line;


        //ingnores lines before startLine
        for(int i = 1; i < startLine; i++)
            getline(read, line);

        //ingnores cells before column
        for(int i = 0; i < column; i++)
            read >> temp;

        read >> start;

        //reads rest in startLine
        for(int i = column; i < numOfCol - 1; i++)
            read >> temp;

        maximum = start;

        while(read)
        {
            read >> temp;

            if(counter++ % numOfCol == column && temp < maximum)
                maximum = temp;
        }




        read.close();
        std::cout << "*(biggestDecrease)";
        message(fileName, false);
        return (start - maximum);
    }
    else
    {
        std::cout << "unable to open file " << fileName << "\n";
        return 0;
    }
    
}
double zeroProtect(double valueProtected)
{
    if(valueProtected == 0)
    {
        std::cout << "value " << valueProtected << " was protected from zero\n";
        return 1E-6;
    }
    else
        return valueProtected;
}


void etc::showArray(double array[])
{
    std::cout << "\nlenght of array is " << fileLib::arrayLenght(array) << "\n\n";
    
    double * p = array;
    int i = 0;

    while(*(p + i) > 1e-250 && *(p +i) < 1e250)
    {
        std::cout << *(p + i) << "\n";
        i++;
    }
}

void etc::showArray(int array[])
{
    std::cout << "začátek měřené arraye\n\n";
   
    int * p = array;
    int i = 0;

    while(*(p +i) != 0)
    {
        std::cout << *(p +i) << "\n";
        i++;
    }
}

void etc::showArray(std::vector<double> &vect)
{
    uint32_t len = vect.size();
    std::cout << "len is " << len << "\n";

    for(int i = 0; i < len; i++)
        std::cout << vect[i] << "\n";
}

void etc::insertionSort(double array1[], double array2[])
{
    int len = fileLib::arrayLenght(array1), i, j;
    double key1, key2;

    for(int i = 1; i < len; i++)
    {
        key1 = array1[i];
        key2 = array2[i];
        j = i - 1;

        while(j >= 0 && array1[j] > key1)
        {
            array1[j + 1] = array1[j];
            array2[j + 1] = array2[j];
            j -= 1;
        }
        array1[j + 1] = key1;
        array2[j + 1] = key2;
    }

}

inline int etc::partition(double array[], double array1[], int start, int end)
{
    double pivot = array[start];

    int count = 0;
    for(int i = start + 1; i <= end; i++)
    {
        if(array[i] <= pivot)
            count++;
    }

    int pivotIndex = start +count;
    std::swap(array[pivotIndex], array[start]);
    std::swap(array1[pivotIndex], array1[start]);

    int i = start, j = end;

    while(i < pivotIndex && j > pivotIndex)
    {
        while(array[i] <= pivot)
            i++;
        while(array[j] > pivot)
            j--;

        if(i < pivotIndex && j > pivotIndex)
        {
            std::swap(array[i++], array[j--]);
            std::swap(array1[i++], array1[j--]);
        }
    }

    return pivotIndex;
}

inline void etc::quickSort(double array[], double array1[], int start, int end)
{
    if(start >= end)
        return;

    if(fileLib::arrayLenght(array) != fileLib::arrayLenght(array1))
        return;

    int p = partition(array, array1, start, end);

    quickSort(array, array1, start, p-1);
    quickSort(array, array1, p + 1, end);
}


bool etc::arraySum(double array1[], double array2[])
{
    int len = fileLib::arrayLenght(array1);
    //std::cout << "len is " << len << "\n";
    insertionSort(array1, array2);
   

    int diff;
    int point = 0;
    int counter = 0;

    while(point < len )
    {
        diff = 1;
        std::cout << "we are on " << point << "\n";
        array1[counter] = array1[point];
        array2[counter] = array2[point];
        while(array1[point] == array1[point + diff])
        {
           
            array2[counter] += array2[point + diff];
           
            std::cout << "we are on " << point << " + " << diff << "\n";
          
            array1[point + diff] = 0;
            array2[point + diff] = 0;
            diff++;
        }

        counter++;
        point += diff;

    }

    while(counter < len)
    {
        array1[counter] = 0;
        array2[counter] = 0;
        counter++;
    }


    if(len > 0)
        return true;
    else
        return false;
}

int etc::positionInArray(double array[], double wanted)
{
    double * p = &array[0];

    for(int i = 0; i < maxLen; i++)
    {
        if(*(p + i) == wanted)
            return i;
    }

    std::cout << "nothing was found\n";
    return 0;
}

int etc::positionInArray(float array[], float wanted)
{
    float * p = &array[0];

    for(int i = 0; i < maxLen; i++)
    {
        if(*(p + i) == wanted)
            return i;
    }

    std::cout << "nothing was found\n";
    return 0;
}


int etc::positionInArray(int array[], int wanted)
{
    int * p = &array[0];

    for(int i = 0; i < maxLen; i++)
    {
        if(*(p + i) == wanted)
            return i;
    }

    std::cout << "nothing was found\n";
    return 0;
}
