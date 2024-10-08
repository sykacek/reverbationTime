#include "inc/txt_file.h"

int main(void)
{
    /* load data from path */
    std::vector<std::string> files;
    txt::loadFromPath("output/data/", files);

    double startValue = 0, startTime = 0, time[5];

    for(long unsigned int i = 0; i < files.size(); i++){
        std::fstream read(files[i], std::ios_base::in);
        read >> startTime;
        read >> startValue;
        read.close();

        std::stringstream devide(files[i]);
        std::string newName, path = "output/stats/", printable;
        
        double avarge = 0;
        bool continuer = false;
        
        //append STATS suffix to filename
        for(int j = 0; j < 4; j++)
            getline(devide, newName, '/');
        int pos = newName.find(".dat");
        printable = newName.erase(pos);
        printable.append("STATS.txt");
        path.append(printable);

        /* write contents to the STATS.txt file */
        std::fstream write(path, std::ios_base::out);
        write << "***This is computation of revarbation time of file " << newName << ".wav ***\n\n";
        write << "\n******************************************************************************\n\n\n";
        int counter = 0;

        for(int j = 0; j < 6; j++){
            double temp = -j*10 + startValue - 10, revTime;
            time[j] = txt::returnTimeFromValue(files[i], temp);
            time[j] -= startTime;

            if(time[j] > 0){
                revTime = time[j] * 60/(j*10 +10);
                write << "Decreasement of " << j*10 + 10 << " dB was first measured in " << time[j] << " s\t";
                write << "time" << j*10 + 10 << " is " << revTime << " s\n";
                avarge += revTime;
                counter++;
            } else
                continuer = true;
        }

        /* if decreasement of 60 dB was not mesured, append maximum decreasement values */
        if(continuer == true){
            double tm, value, revTime;
            value = txt::biggestDecrease(files[i]);
            write << "\n\nBigest decrease was " << value;
            value *= -1;
            value += startValue;
            tm = txt::returnTimeFromValue(files[i], value);
            tm -= startTime;
            value -= startValue;
            value *= -1;
            revTime = tm*60/value;
            avarge += revTime;
            counter++;
            
            write << " dB in time " << tm << "\ttmax is " << revTime << " s\n";
        }
        /* write arithmeric mean from measured values */
        write << "\n\nArithmetic mean from measured values is " << avarge/counter << " s";
        write.close();
    }

    return 0;
}