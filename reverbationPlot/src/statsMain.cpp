#include "headers/myFile.h"
#include "headers/stats.h"



int main()
{
    std::vector<std::string> files;
    fileLib::loadFromPath("../out/data/", files);

    double startValue{0}, startTime{0}, time[5];

    for(int i = 0; i < files.size(); i++)
    {
        std::fstream read(files[i], std::ios_base::in);
        read >> startTime;
        read >> startValue;
        read.close();

        std::stringstream devide(files[i]);
        std::string newName, path = "../out/stats/", printable;
        int pos = 0, counter = 0;
        double avarge = 0;
        bool continuer = false;
        
        for(int j = 0; j < 4; j++)
            getline(devide, newName, '/');
        pos = newName.find(".dat");
        printable = newName.erase(pos);
        printable.append("STATS.txt");


        path.append(printable);
        std::cout << "path is " << path << "\n";

        std::fstream write(path, std::ios_base::out);
        write << "***This is computation of revarbation time of file " << newName << ".wav ***\n\n";

        write << "\n***************************************************************************\n\n";

        for(int j = 0; j < 6; j++)
        {
            //std::cout << i << "\t" << j << "\n";
            double temp = -j*10 + startValue - 10, revTime;
            //std::cout << temp;
            time[j] = fileLib::returnTimeFromValue(files[i], temp);
            time[j] -= startTime;
            if(time[j] > 0)
            {
                revTime = time[j] * 60/(j*10 +10);
                write << "\nDecreasement of " << j*10 + 10 << " dB was first recognized in " << time[j] << " s\t";
                write << "time" << j*10 + 10 << " is " << revTime;
                avarge += revTime;
                counter++;
            }
            else
                continuer = true;
            
        }

        if(continuer == true)
        {
            double tm, value, revTime;
            value = fileLib::biggestDecrease(files[i]);
            write << "\n\nBigest decrease was " << value;
            value *= -1;
            value += startValue;
            tm = fileLib::returnTimeFromValue(files[i], value);
            tm -= startTime;
            value -= startValue;
            value *= -1;
            revTime = tm*60/value;
            avarge += revTime;
            counter++;
            
            write << " dB in time " << tm << "\ttmax is " << revTime << "\n";
        }
        
        write << "\n\nAvarged t60 is " << avarge/counter << " s";

        write.close();
    }

    return 0;
}