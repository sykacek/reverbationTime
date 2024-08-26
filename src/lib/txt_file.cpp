#include "../inc/txt_file.h"
/**
 * function implementation
 */

 std::string txt::nameProtect(std::string fileName)
{
    for(int i = 0; fileName[i]; i++){
        if(fileName[i] == '.')
            return fileName;
    }
    fileName += ".txt";

    return fileName;
}

 void txt::message(std::string text, bool mode)
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

 uint16_t txt::arr_s(float *arr)
{
    int ret = 0;
    while(*(arr + ret))
        ret++;
    return ret;
}

uint32_t txt::file_len(std::string fileName)
{
    fileName = txt::nameProtect(fileName);
    std::fstream read(fileName, std::ios_base::in);

    if(read.is_open()){
        //std::cout << "(length)";
        message(fileName, true);
        uint32_t i = 0;
        float temp;

        while(read){
            read >> temp;
            if(!read){
                read.close();
                message(fileName, false);
                return i;
            }
            i++;
        }
        read.close();
        message(fileName, false);
        return i;
    } else
        return (uint32_t) 0;
}

uint32_t txt::file_line_len(std::string fileName)
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

uint32_t txt::cols_per_row(std::string fileName)
{
    std::fstream read(fileName, std::ios_base::in);
    std::string line, temp{};
    uint32_t counter = 0;

    getline(read, line);
    read.close();

    std::stringstream sread(line);

    while(sread >> temp)
        counter++;

    return counter;
}

bool txt::fileRead(std::string fileName, float readArray[])
{
    if(readArray == NULL)
        return false;
    fileName = txt::nameProtect(fileName);
    uint32_t len;

    len = file_len(fileName);
    if(!len)
        return false;
    std::fstream read(fileName, std::ios_base::in);
    if(read.is_open()){
        message(fileName, true);
        float *p = &readArray[0];

        for(uint32_t i = 0; i < len; i++)
            read >> *(p+i);

        read.close();
        message(fileName, false);

        return true;
    }
    return false;
}

bool txt::fileRead(std::string fileName, float readArray1[], float readArray2[])
{
    if(readArray1 == NULL || readArray2 == NULL)
        return false;
    
    fileName = txt::nameProtect(fileName);

    float array[CACHE_BUFFER_SIZE] = {0};
    bool done = fileRead(fileName, array);
    if(!done)
        return false;

    uint32_t len;
    len = file_len(fileName);
    if(!len)
        return false;

    float *x = readArray1, *y = readArray2;
    for(uint32_t i = 0; i < len; i++){
        if(!(i%2))
            *(x+i/2) = array[i];
        else
            *(y+(i-1)/2) = array[i];
    }

    return true;
}

bool txt::fileRead(std::string fileName, std::vector<float> &readvector, uint16_t col_per_row, uint16_t pos)
{
    if(!col_per_row)
        return false;
    fileName = txt::nameProtect(fileName);
    std::fstream file(fileName, std::ios_base::in);

    if(file.is_open()){
        float temp;
        message(fileName, true);
        uint32_t len = file_len(fileName);

        for(uint32_t i = 0; i < len; i++){
            file >> temp;
            if(i % col_per_row == pos)
                readvector.push_back(temp);
        }

        file.close();
        message(fileName, false);

        return true;
    }
    return false;
}

bool txt::fileWrite(std::string fileName, float array1[])
{
    int length = arr_s(array1);
    if(!length)
        return false;
    
    fileName = txt::nameProtect(fileName);
    std::fstream file(fileName, std::ios_base::out);

    if(file.is_open()){
        message(fileName, true);
        file << std::setprecision(PREC);

        float *p = array1;
        for(int i = 0; i < length - 1; ++i){
            file << *(p + i) << "\n";
        }
        file << *(p + length - 1);

        file.close();
        message(fileName, false);

        return true;
    } else
        return false;
}

bool txt::fileWrite(std::string fileName, float array1[], float array2[])
{
    uint length = std::min(arr_s(array1), arr_s(array2));
    if(!length)
        return false;

    fileName = txt::nameProtect(fileName);
    std::fstream file(fileName, std::ios_base::out);

    if(file.is_open()){
        message(fileName, true);
        file << std::setprecision(PREC);
        
        float *p = array1;
        float *z = array2;

        for(uint i = 0; i < length - 1; i++){
            file << *(p +i) << "\t" << *(z+i) << "\n";
        }
        file << *(p + length - 1) << "\t" << *(z + length - 1);
        
        file.close();
        message(fileName, false);
        return true;
    } else
        return false;
}

bool txt::fileWrite(std::string fileName, std::vector<float> &vect)
{
    uint len = vect.size();
    if(!len)
        return false;
    
    std::fstream file(fileName, std::ios_base::out);
    if(file.is_open()){
        message(fileName, true);
        file << std::setprecision(PREC);

        for(uint i = 0; i < len - 1; i++)
            file << vect[i] << "\n";

        file << vect[len - 1];

        file.close();
        message(fileName, false);
        return true;
    } else {
        std::cout << "file " << fileName << " was unable to open\n";
        return false;
    }
}

bool txt::fileWrite(std::string fileName, std::vector<float> &one, std::vector<float> &two)
{
    uint len = std::min(one.size(), two.size());
    if(!len)
        return false;
    
    std::fstream file(fileName, std::ios_base::out);

    if(file.is_open()){
        message(fileName, true);
        file << std::setprecision(PREC);

        for(uint16_t i = 0; i < len - 1; i ++)
            file << one[i] << "\t" << two[i] << "\n";

        file << one[len - 1] << "\t" << two[len - 1];
        message(fileName, false);

        return true;
    } else {
        std::cout << "file " << fileName << " was unable to open\n";
        return false;
    }
}

bool txt::fileAppendLine(std::string fileName, float array1[])
{
    int len = arr_s(array1);
    if(!len)
        return false;
    
    fileName = txt::nameProtect(fileName);
    std::fstream file(fileName, std::ios_base::app);

    if(file.is_open()){
        message(fileName, true);
        file << std::setprecision(PREC);

        float * p = array1;
        for(int i = 0; i < len - 1; i++){
            file << *(p++) << "\n";
        }
        file << *(p);

        file.close();
        message(fileName, false);

        return true;
    } else
        return false;
}

bool txt::fileAppendTab(std::string fileName, float array1[])
{
    fileName = txt::nameProtect(fileName);
    std::fstream file(fileName, std::ios_base::app);
    
    if(file.is_open()){
        message(fileName, true);
        int len = arr_s(array1);
        file << std::setprecision(PREC);


        float * p = array1;
        for(int i = 0; i < len - 1; i++){
            file << *(p++) << "\t";
        }
        file << *p;
        file.close();
        message(fileName, false);

        return true;
    } else
        return false;
}

bool txt::fileAproximation(std::string fileRead, std::string fileWrite, uint n)
{
    if(fileWrite == "")
        fileWrite = PATH_FILEAPROXIMATION;

    uint32_t len = file_line_len(fileRead);
    if(!len)
        return false;

    const uint cols = cols_per_row(fileRead);
    if(!cols)
        return false;

    if(!n)
        return false;

    std::fstream read(fileRead, std::ios_base::in);
    std::fstream write(fileWrite, std::ios_base::out);

    if(read.is_open() && write.is_open()){
        message(fileRead, true);
        message(fileWrite, true);
        write << std::setprecision(PREC);

        len /= n;

        /* dynamically allocate memory for all columns */
        std::vector<float> read_vect, sum_vect;
        for(uint i = 0; i < cols; ++i){
            read_vect.push_back(0);
            sum_vect.push_back(0);
        }

        for(uint i = 0; i < len; ++i){
            /* set values 0 each start of loop */
            for(uint k = 0; k < cols; ++k)
                sum_vect[k] = 0;

            /* read values to vector */
            for(uint j = 0; j < n; j++){
                for(uint k = 0; k < cols; ++k){
                    read >> read_vect[k];
                    sum_vect[k] += read_vect[k];
                }
            }

            /* get arithmetic mean */
            for(uint k = 0; k < cols; ++k){
                sum_vect[k] /= n;
            }

            /* write values */
            for(uint k = 0; k < cols - 1; ++k)
                write << sum_vect[k] << "\t";
            if(i != len - 1)
                write << sum_vect[cols - 1] << "\n";
            else
                write << sum_vect[cols - 1];
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

bool txt::logValue(std::vector<float> &vect)
{
    uint16_t len = vect.size();
    float temp1, temp2;

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

bool txt::fileClear(std::string fileName)
{
    std::fstream clean(fileName, std::ios_base::out);
    if(clean.is_open()){
        clean.close();
        return true;
    }
    else
        return false;
}

bool txt::fileCopy(std::string fileRead, std::string fileWrite, uint32_t col_per_row)
{
    std::fstream read(fileRead, std::ios_base::in);
    std::fstream write(fileWrite, std::ios_base::out);

    if(read.is_open() && write.is_open()){
        message(fileRead, true);
        message(fileWrite, true);
        write << std::setprecision(PREC);


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

bool txt::fileLogCopy(std::string fileNameRead, std::string fileNameWrite, uint16_t col_per_row, uint16_t order1, uint16_t order2)
{
    if(fileNameWrite == "")
        fileNameWrite = PATH_FILELOGCOPY;

    std::fstream fileRead(fileNameRead, std::ios_base::in);
    std::fstream fileWrite(fileNameWrite, std::ios_base::out);

    if(fileRead.is_open() && fileWrite.is_open()){
        message(fileNameRead, true);
        message(fileNameWrite, true);
        fileRead << std::setprecision(PREC);

        float temp1, temp2, temp3;
        uint32_t len = file_len(fileNameRead);

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

uint32_t txt::maximumInCol(std::string fileName, uint32_t col_per_row, uint32_t column)
{
    std::fstream read(fileName, std::ios_base::in);
    uint32_t counter = 0, line = 1;
    float temp, maximum = -1e10, maxLine = 1;

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

uint32_t txt::minimumInCol(std::string fileName, uint32_t col_per_row, uint32_t column)
{
    std::fstream read(fileName, std::ios_base::in);

    uint32_t counter = 0, line = 1;
    float temp, minimum = 1e10, maxLine = 1;
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

bool txt::fileFabs(std::string fileRead, std::string fileWrite, uint32_t col_per_row)
{
    if(fileWrite == "")
        fileWrite = PATH_FILEFABS;

    std::fstream read(fileRead, std::ios_base::in);
    std::fstream write(fileWrite, std::ios_base::out);
    if(read.is_open() && write.is_open()) {
        message(fileRead, true);
        message(fileWrite, true);
        write << std::setprecision(PREC);

        float temp;
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

bool txt::fileColumnRemove(std::string fileName, uint16_t col_per_row, uint16_t eliminate)
{
    std::fstream read(fileName, std::ios_base::in);
    std::fstream write(PATH_FILECOLUMNREMOVE, std::ios_base::out);

    if(read.is_open() && write.is_open()) {
        message(fileName, true);
        write << std::setprecision(PREC);
        float temp;
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

bool txt::fileShortenOrdered(std::string fileName, uint32_t startPoint, float d)
{
    if(startPoint == 1)
        return true;

    if(startPoint == file_line_len(fileName) - 2)
        return false;

    std::fstream read(fileName, std::ios_base::in);
    std::fstream write(PATH_FILESHORTENORDER, std::ios_base::out);

    if(read.is_open() && write.is_open()){
        message(fileName, true);
        write << std::setprecision(PREC);
        float temp;
        read >> temp;

        if(d == 0)
            d = temp;

        for(uint32_t i = 1; i < 2*startPoint - 2; i++)
            read >> temp;
        int counter = 0;
        int i = 1;

        while(read){
            read >> temp;
            
            if(!read)
                break;
            if(counter % 2 == 1)
                write << temp << "\n";
            else
                write << DELTA*i++ << "\t";
            counter++;
        }
        read.close();
        write.close();
        message(fileName, false);
        fileCopy(PATH_FILESHORTENORDER, fileName);

        return true;
    } else {
        std::cout << "unable to open file " << fileName << "\n";
        return false;
    }
}

bool txt::fileCutFromLine(std::string fileName, uint32_t cut, uint32_t col_per_row)
{
    std::fstream read(fileName, std::ios_base::in);
    std::fstream write(PATH_FILECUTFROMLINE, std::ios_base::out);

    if(read.is_open() && write.is_open()){
        message(fileName, true);
        write << std::setprecision(PREC);
        uint32_t len = file_line_len(fileName);

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

bool txt::fileCutToLine(std::string fileName, uint32_t line, uint32_t col_per_row)
{
    std::fstream read(fileName, std::ios_base::in);
    std::fstream write(PATH_FILECUTTOLINE, std::ios_base::out);

    if(read.is_open() && write.is_open()){
        message(fileName, true);
        write << std::setprecision(PREC);
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

bool txt::filesAverage(std::vector<std::string> &files, std::string fileWrite, uint32_t col_per_row, uint32_t order1, uint32_t order2)
{
    if(!col_per_row)
        return false;

    if(std::max(order1, order2) >= col_per_row)
        return false;

    uint16_t len = files.size(), counter = 0;
    if(!len)
        return false;

    std::fstream write(fileWrite, std::ios_base::out);
    write << std::setprecision(PREC);

    float dataRead[col_per_row*PROCCESSING_BUFFER_SIZE], temp;

    std::memset(dataRead, 0, arr_s(dataRead) * sizeof(float));
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
    len = file_len(fileWrite);

    if(len > 0)
        return true;
    else
        return false;
}

float txt::returnTimeFromValue(std::string fileName, float value, uint16_t col_per_row, uint16_t column)
{
    if(!col_per_row)
        return (float)0;
    
    if(column >= col_per_row)
        return 0;
    
    std::fstream read(fileName, std::ios_base::in);
    if(read.is_open()){
        message(fileName, true);
        float time, temp;
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
        return (float)0;
    }
}

bool txt::loadFromPath(std::string path, std::vector<std::string> &files)
{
    files.clear();
    for(const auto & entry : std::filesystem::directory_iterator(path))
        files.push_back(entry.path());

    if(files.size() > 0)
        return true;
    else
        return false;
}

uint32_t txt::findLineFromDiff(std::string fileName, uint32_t startLine, float diff, uint16_t col_per_row, uint16_t column)
{
    if(!col_per_row)
        return 0;
    std::fstream read(fileName, std::ios_base::in);
    if(read.is_open()){
        message(fileName, true);

        std::string line;
        float temp, max;
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

float txt::biggestDecrease(std::string fileName, uint32_t startLine, uint16_t col_per_row, uint16_t column)
{
    if(!col_per_row)
        return 0;

    if(column >= col_per_row)
        return 0;
    
    std::fstream read(fileName, std::ios_base::in);
    if(read.is_open()){
        message(fileName, true);
        float temp, maximum, start;
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