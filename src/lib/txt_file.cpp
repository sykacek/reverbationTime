#include "../inc/txt_file.h"
/**
 * function implementation
 */

 std::string txt_file::nameProtect(std::string fileName)
{
    for(int i = 0; fileName[i]; i++){
        if(fileName[i] == '.')
            return fileName;
    }
    fileName += ".txt";

    return fileName;
}

 void txt_file::message(std::string text, bool mode)
{
    /**
     * Uncomment for additional debbuging info 
     */
    /*if(mode == true)
        std::cout << "File " << text << " was opened\n";
    else 
        std::cout << "File " << text << " was closed\n";
    */
}

 uint16_t txt_file::arr_s(double *arr)
{
    int ret = 0;
    while(*(arr + ret++))
        ret++;
    return ret;
}
uint32_t txt_file::fileLenght(std::string fileName)
{
    fileName = txt_file::nameProtect(fileName);
    std::fstream testName(fileName, std::ios_base::in);

    if(testName.is_open()){
        //std::cout << "(fileLenght)";
        message(fileName, true);
        uint32_t i = 0;
        double temp;

        while(testName){
            testName >> temp;
            if(!testName){
                message(fileName, false);
                return i;
            }
            i++;
        }
        testName.close();
        message(fileName, false);
    } else{
    }
    return (uint32_t) 0;
}

uint32_t txt_file::fileLineLenght(std::string fileName)
{
    std::fstream read(fileName, std::ios_base::in);
    if(read.is_open()){
        message(fileName, true);
        std::string temp{0};
        uint32_t len = 0;

        while(!read.eof()){
            getline(read, temp);
            len ++;
        }
        message(fileName, false);
        read.close();

        return len;
    } else {
        std::cout << "unable to open file " << fileName << "\n";
        return 0;
    }
}

uint32_t txt_file::columnsInLine(std::string fileName)
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
bool txt_file::fileRead(std::string fileName, double readArray[])
{
    fileName = txt_file::nameProtect(fileName);
    uint32_t amountOfValues;

    amountOfValues = fileLenght(fileName);
    std::fstream testFile1(fileName, std::ios_base::in);
    if(testFile1.is_open()){
        message(fileName, true);
        double *p = &readArray[0];

        for(uint32_t i = 0; i < amountOfValues; i++)
            testFile1 >> *(p+i);

        testFile1.close();
        message(fileName, false);

        return true;
    }
    return false;
}

bool txt_file::fileRead(std::string fileName, double readArray1[], double readArray2[])
{
    fileName = txt_file::nameProtect(fileName);

    double array[CACHE_BUFFER_SIZE] = {};
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

bool txt_file::fileRead(std::string fileName, std::vector<double> &readvector, uint16_t col_per_row, uint16_t pos)
{
    fileName = txt_file::nameProtect(fileName);
    std::fstream file(fileName, std::ios_base::in);

    if(file.is_open()){
        double temp;
        message(fileName, true);
        uint32_t len = fileLenght(fileName);

        for(uint32_t i = 0; i < len; i++){
            file >> temp;
            if(i % col_per_row == pos)
                readvector.push_back(temp);
        }
        message(fileName, false);

        return true;
    }
    return false;
}

bool txt_file::fileWrite(std::string fileName, double array1[])
{
    fileName = txt_file::nameProtect(fileName);
    std::fstream file(fileName, std::ios_base::out);

    if(file.is_open()){
        message(fileName, true);
        int lenght = arr_s(array1);
        
        double *p = array1;
        for(int i = 0; i < lenght; i++){
            file << *(p +i) << "\n";
        }
        file.close();
        message(fileName, false);

        return true;
    } else
        return false;
}

bool txt_file::fileWrite(std::string fileName, double array1[], double array2[])
{
    fileName = txt_file::nameProtect(fileName);
    std::fstream file(fileName, std::ios_base::out);

    if(file.is_open()){
        message(fileName, true);
        int lenght = arr_s(array1);

        double *p = array1;
        double *z = array2;

        for(int i = 0; i < lenght; i++){
            file << *(p +i) << "\t" << *(z+i) << "\n";
        }
        file.close();
        message(fileName, false);
        return true;
    } else
        return false;
}

bool txt_file::fileWrite(std::string fileName, std::vector<double> &vect)
{
    std::fstream file(fileName, std::ios_base::out);
    uint len = vect.size();
    if(file.is_open()){
        message(fileName, true);
        for(uint i = 0; i < len; i++)
            file << vect[i] << "\n";

        message(fileName, false);
        return true;
    } else {
        std::cout << "file " << fileName << " was unable to open\n";
        return false;
    }
}

bool txt_file::fileWrite(std::string fileName, std::vector<double> &one, std::vector<double> &two)
{
    uint16_t len = one.size();
    std::fstream file(fileName, std::ios_base::out);

    if(file.is_open()){
        message(fileName, true);
        for(uint16_t i = 0; i < len; i ++)
            file << one[i] << "\t" << two[i] << "\n";
        message(fileName, false);

        return true;
    } else {
        std::cout << "file " << fileName << " was unable to open\n";
        return false;
    }
}

bool txt_file::fileAppendLine(std::string fileName, double array1[])
{
    fileName = txt_file::nameProtect(fileName);
    std::fstream file(fileName, std::ios_base::app);

    if(file.is_open()){
        message(fileName, true);
        int fileLen = arr_s(array1);

        double * p = array1;
        for(int i = 0; i < fileLen; i++){
            file << *(p + i) << "\n";
        }
        file.close();
        message(fileName, false);

        return true;
    } else
        return false;
}

bool txt_file::fileAppendTab(std::string fileName, double array1[])
{
    fileName = txt_file::nameProtect(fileName);
    std::fstream file(fileName, std::ios_base::app);
    
    if(file.is_open()){
        message(fileName, true);
        int fileLen = arr_s(array1);

        double * p = array1;
        for(int i = 0; i < fileLen; i++){
            file << *(p + i) << "\t";
        }
        file << "\n";
        file.close();
        message(fileName, false);

        return true;
    } else
        return false;
}

bool txt_file::fileAproximation(std::string fileRead, std::string fileWrite, int n)
{
    if(fileWrite == "")
        fileWrite = PATH_FILEAPROXIMATION;

    std::fstream read(fileRead, std::ios_base::in);
    std::fstream write(fileWrite, std::ios_base::out);

    if(read.is_open() && write.is_open()){
        message(fileRead, true);
        message(fileWrite, true);

        uint32_t len = fileLenght(fileRead);
        len /= n;
        len /= 2;
        len -= 1;

        double read1, read2, sum1, sum2;
        for(uint32_t i = 0; i < len; i++){
            sum1 = 0;
            sum2 = 0;
            for(int j = 0; j < n; j++){
                read >> read1;
                read >> read2;
                sum1 += read1;
                sum2 += read2;
            }

            sum1 /= n;
            sum2 /= n;
            write << sum1 << "\t" << sum2 << "\n";
        }
        message(fileRead, false);
        message(fileWrite, false);

        read.close();
        write.close();
        if(fileWrite == PATH_FILEAPROXIMATION)
            fileCopy(PATH_FILEAPROXIMATION, fileRead);

        return true;
    } else {
        std::cout << "Error: failed to open file " << fileRead << "\n";
        return false;
    }
}

bool txt_file::arrayExpand(double dest[], double src[], int n)
{
    int len = arr_s(src);

    for(int i = 0; i < len; i++){
        for(int j = 0; j < n; j++)
            *(dest + i*n + j) = *(src + i);
    }
    len = arr_s(dest);

    if(len > 0)
        return true;
    else 
        return false;
}

bool txt_file::logValue(std::vector<double> &vect)
{
    uint16_t len = vect.size();
    double temp1, temp2;

    for(uint16_t i = 0; i < len; i++){
        temp1 = vect[i];
        temp2 = 10*log10(temp1);
        vect[i] = temp2;
    }

    if(len > 0)
        return true;
    else
        return false;
}

bool txt_file::fileClear(std::string fileName)
{
    std::fstream clean(fileName, std::ios_base::out);
    if(clean.is_open()){
        clean.close();
        return true;
    }
    else
        return false;
}

bool txt_file::fileCopy(std::string fileRead, std::string fileWrite, uint32_t col_per_row)
{
    std::fstream read(fileRead, std::ios_base::in);
    std::fstream write(fileWrite, std::ios_base::out);

    if(read.is_open() && write.is_open()){
        message(fileRead, true);
        message(fileWrite, true);

        std::string cut;
        while(read){
            getline(read, cut);
            write << cut << "\n";
        }
        message(fileRead, false);
        message(fileWrite, false);

        read.close();
        write.close();

        return true;
    } else {
        std::cout << "(fileCopy) failed to open file " << fileRead << "\n";
        return false;
    }
}

bool txt_file::fileLogCopy(std::string fileNameRead, std::string fileNameWrite, uint16_t col_per_row, uint16_t order1, uint16_t order2)
{
    if(fileNameWrite == "")
        fileNameWrite = PATH_FILELOGCOPY;

    std::fstream fileRead(fileNameRead, std::ios_base::in);
    std::fstream fileWrite(fileNameWrite, std::ios_base::out);

    if(fileRead.is_open() && fileWrite.is_open()){
        message(fileNameRead, true);
        message(fileNameWrite, true);

        double temp1, temp2, temp3;
        uint32_t len = fileLenght(fileNameRead);

        for(uint32_t i = 0; i < len; i++){
            fileRead >> temp1;
            if(i % col_per_row == order1)
                fileWrite << temp1 << "\t";
            else if(i % col_per_row == order2){
                temp2 = fabs(temp1);
                temp3 = 20*log10(temp2);
                fileWrite << temp3 << "\n";
            }
        }
        message(fileNameRead, false);
        message(fileNameWrite, false);

        fileRead.close();
        fileWrite.close();

        if(fileNameWrite == PATH_FILELOGCOPY)
            fileCopy(PATH_FILELOGCOPY, fileNameRead);

        return true;
    } else {
        std::cout << "(fileLogCopy) failed to open files\n";
        return false;
    }
}

uint32_t txt_file::maximumInCol(std::string fileName, uint32_t col_per_row, uint32_t column)
{
    std::fstream read(fileName, std::ios_base::in);
    uint32_t counter = 0, line = 1;
    double temp, maximum = -1e10, maxLine = 1;

    while(read){
        read >> temp;
        if(counter % col_per_row == column){
            if(temp > maximum){
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

uint32_t txt_file::minimumInCol(std::string fileName, uint32_t col_per_row, uint32_t column)
{
    std::fstream read(fileName, std::ios_base::in);

    uint32_t counter = 0, line = 1;
    double temp, minimum = 1e10, maxLine = 1;
    while(read){
        read >> temp;
        if(counter % col_per_row == column) {
            if(minimum > temp && read) {
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

bool txt_file::fileFabs(std::string fileRead, std::string fileWrite, uint32_t col_per_row)
{
    if(fileWrite == "")
        fileWrite = PATH_FILEFABS;

    std::fstream read(fileRead, std::ios_base::in);
    std::fstream write(fileWrite, std::ios_base::out);
    if(read.is_open() && write.is_open()) {
        message(fileRead, true);
        message(fileWrite, true);

        double temp;
        uint32_t counter = 0;
        while(read) {
            read >> temp;
            if(!read)
                break;
            temp = fabs(temp);
            write << temp;
            
            if(counter++ % col_per_row == 0)
                write << "\t";
            else
                write << "\n";
        }
        message(fileRead, false);
        message(fileWrite, false);

        read.close();
        write.close();

        if(fileWrite == PATH_FILEFABS)
            fileCopy(PATH_FILEFABS, fileRead);

        return true;
    } else {
        std::cout << "unable to open files\n";
        return false;
    }
}

bool txt_file::fileColumnRemove(std::string fileName, uint16_t col_per_row, uint16_t eliminate)
{
    std::fstream read(fileName, std::ios_base::in);
    std::fstream write(PATH_FILECOLUMNREMOVE, std::ios_base::out);

    if(read.is_open() && write.is_open()) {
        message(fileName, true);
        double temp;
        uint32_t counter = 0, pos = col_per_row - 1;

        if(eliminate == pos)
            pos--;

        while(read) {
            read >> temp;
            if(!read)
                break;
            if(counter % col_per_row != eliminate)
                write << temp << "\t";
            if(counter % col_per_row == pos)
                write << "\n";

            counter++;
        }
        read.close();
        write.close();
        message(fileName, false);
        fileCopy(PATH_FILECOLUMNREMOVE, fileName);

        return true;
    } else {
        std::cout << "unable to open file " << fileName << "\n";
        return false;
    }
}

bool txt_file::fileShortenOrdered(std::string fileName, uint32_t startPoint, double d)
{
    if(startPoint == 1)
        return true;

    if(startPoint == fileLineLenght(fileName) - 2)
        return false;

    std::fstream read1(fileName, std::ios_base::in);
    std::fstream write1(PATH_FILESHORTENORDER, std::ios_base::out);

    if(read1.is_open() && write1.is_open()){
        message(fileName, true);
        double temp;
        read1 >> temp;

        if(d == 0)
            d = temp;

        for(uint32_t i = 1; i < 2*startPoint - 2; i++)
            read1 >> temp;
        int counter = 0;
        int i = 1;

        while(read1){
            read1 >> temp;
            
            if(!read1)
                break;
            if(counter % 2 == 1)
                write1 << temp << "\n";
            else
                write1 << DELTA*i++ << "\t";
            counter++;
        }
        read1.close();
        write1.close();
        message(fileName, false);
        fileCopy(PATH_FILESHORTENORDER, fileName);

        return true;
    } else {
        std::cout << "unable to open file " << fileName << "\n";
        return false;
    }
}

bool txt_file::fileCutFromLine(std::string fileName, uint32_t cut, uint32_t col_per_row)
{
    std::fstream read(fileName, std::ios_base::in);
    std::fstream write(PATH_FILECUTFROMLINE, std::ios_base::out);

    if(read.is_open() && write.is_open()){
        message(fileName, true);
        uint32_t len = fileLineLenght(fileName);

        if(len < cut)
            return false;
        
        std::string ligne;
        uint32_t count = 0;
        while(count < cut){
            getline(read, ligne);
            write << ligne << "\n";
            count ++;
        }
        read.close();
        write.close();
        message(fileName, false);
        fileCopy(PATH_FILECUTFROMLINE, fileName);

        return true;
    } else {
        std::cout << "unable to file " << fileName << "\n";
        return false;
    }
}

bool txt_file::fileCutToLine(std::string fileName, uint32_t line, uint32_t col_per_row)
{
    std::fstream read(fileName, std::ios_base::in);
    std::fstream write(PATH_FILECUTTOLINE, std::ios_base::out);

    if(read.is_open() && write.is_open()){
        message(fileName, true);
        std::string ligne;

        for(uint32_t i = 0; i < line; i++)
            getline(read, ligne);

        while(read){
            getline(read, ligne);
            write << ligne << "\n";
        }
        read.close();
        write.close();
        message(fileName, false);
        fileCopy(PATH_FILECUTTOLINE, fileName, col_per_row);

        return true;
    } else {
        std::cout << "unable to open files\n";
        return false;
    }
}

bool txt_file::filesAverage(std::vector<std::string> &files, std::string fileWrite, uint32_t col_per_row, uint32_t order1, uint32_t order2)
{
    uint16_t len = files.size(), counter = 0;
    std::fstream write(fileWrite, std::ios_base::out);
    double dataRead[col_per_row*PROCCESSING_BUFFER_SIZE], temp;

    std::memset(dataRead, 0, arr_s(dataRead));
    bool end = false;
    int k = col_per_row * PROCCESSING_BUFFER_SIZE;
    
    while(!end) {
        for(uint16_t i = 0; i < len; i++){
            std::fstream read(files[i], std::ios_base::in);

            for(uint32_t j = 0; j < counter*PROCCESSING_BUFFER_SIZE*col_per_row; j++)
                read >> temp;
     
            for(uint32_t j = 0; j < col_per_row*PROCCESSING_BUFFER_SIZE; j++){
                read >> temp;
                if(!read){
                    k = j;
                    break;
                }
                dataRead[j] += temp;
            }
            end = read.eof();
            read.close();
        }
        counter++;
        for(int i = 0; i < k; i++){
            write << dataRead[i]/len;
            dataRead[i] = 0;
            
            if(i % col_per_row == (col_per_row - 1))
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

double txt_file::returnTimeFromValue(std::string fileName, double value, uint16_t col_per_row, uint16_t column)
{
    std::fstream read(fileName, std::ios_base::in);
    if(read.is_open()){
        message(fileName, true);
        double time, temp;
        uint32_t counter = 0;

        while(read){
            read >> temp;
            if(counter % col_per_row == 0)
                time = temp;

            if(counter++ % col_per_row == column && (temp - FILE_DELTA < value && time + FILE_DELTA > value))
                break;
        }
        message(fileName, false);
        read.close();

        return time;
    } else {
        std::cout << "unable to open file " << fileName << "\n";
        return (double)0;
    }
}

bool txt_file::loadFromPath(std::string path, std::vector<std::string> &files)
{
    files.clear();
    for(const auto & entry : std::filesystem::directory_iterator(path))
        files.push_back(entry.path());

    if(files.size() > 0)
        return true;
    else
        return false;
}

uint32_t txt_file::findLineFromDiff(std::string fileName, uint32_t startLine, double diff, uint16_t col_per_row, uint16_t column)
{
    std::fstream read(fileName, std::ios_base::in);
    if(read.is_open()){
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

        for(int i = max + 1; i < col_per_row; i++)
            read >> temp;

        while(read){
            read >> temp;
            if(counter++ % col_per_row == column && temp < diff)
                break;
        }
        message(fileName, false);
        read.close();

        return counter/col_per_row;
    } else {
        std::cout << "unable to open file " << fileName << "\n";
        return 0;
    }
}

double txt_file::biggestDecrease(std::string fileName, uint32_t startLine, uint16_t col_per_row, uint16_t column)
{
    std::fstream read(fileName, std::ios_base::in);
    if(read.is_open()){
        message(fileName, true);
        double temp, maximum, start;
        uint32_t counter = 0;
        std::string line;

        for(uint32_t i = 1; i < startLine; i++)
            getline(read, line);

        for(uint16_t i = 0; i < column; i++)
            read >> temp;
        read >> start;

        for(int i = column; i < col_per_row - 1; i++)
            read >> temp;
        maximum = start;
        
        while(read){
            read >> temp;
            if(counter++ % col_per_row == column && temp < maximum)
                maximum = temp;
        }
        read.close();
        message(fileName, false);

        return (start - maximum);
    } else {
        std::cout << "unable to open file " << fileName << "\n";
        return 0;
    }
}