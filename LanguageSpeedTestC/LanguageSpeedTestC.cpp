#include <iostream>
#include <fstream>
#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <time.h>
#include <tchar.h>
#include <thread>

using namespace std;

int GetCpuUsage();
double cpuU = 0;
void CpuWhileThread(int Tsize);

int _tmain()
{
    int irl = 0, Nirl = 0, yourTime = 10, min = 0, sec = 0;

    thread* th;
    th = new thread[CpuWhileThread(yourTime), 1];
    th-> joinable();

    LARGE_INTEGER perfFreq, perfCounter;
    QueryPerformanceFrequency(&perfFreq);
    LONGLONG prevValue = 0;
    while (true)
    {
        struct tm tim;
        time_t tt = time(NULL);
        localtime_s(&tim, &tt);

        QueryPerformanceCounter(&perfCounter);
        LONGLONG currentValue = perfCounter.QuadPart / perfFreq.QuadPart;

        if (Nirl == 0)
        {
            //Время начала работы
            cout << "Starting: " << tim.tm_min << "." << tim.tm_sec << endl;
            min = tim.tm_min;
            sec = tim.tm_sec;

            prevValue = currentValue + yourTime - 1;
            Nirl += 1;
        }

        ++irl;

        cout << irl << endl;

        if (currentValue > prevValue)
        {            
            //Время окончания работы
            cout << "Ending: " << tim.tm_min << "." << tim.tm_sec << "\nPC CPU usage: " << cpuU << "\nLog saved!" << endl;

            std::ofstream out("ResultsC.txt", ios::app);
            if (out.is_open())
            {
                string Ending = tim.tm_min + "." + tim.tm_sec;
                out << "Starting: " << min << "." << sec << "\nEnding: " << tim.tm_min << "." << tim.tm_sec << "\nPC CPU usage: " << cpuU << "\nScore result: " << irl << endl;
            }
            out.close();

            break;
        }
    }
    return 0;
}

int main()
{
    _tmain();
    
    system("pause");
}

int GetCpuUsage()
{
    static ULARGE_INTEGER TimeIdle, TimeKernel, TimeUser;
    FILETIME Idle, Kernel, User;
    ULARGE_INTEGER uIdle, uKernel, uUser;
    GetSystemTimes(&Idle, &Kernel, &User);
    memcpy(&uIdle, &Idle, sizeof(FILETIME));
    memcpy(&uKernel, &Kernel, sizeof(FILETIME));
    memcpy(&uUser, &User, sizeof(FILETIME));
    long long t;
    t = (((((uKernel.QuadPart - TimeKernel.QuadPart) + (uUser.QuadPart - TimeUser.QuadPart)) -
        (uIdle.QuadPart - TimeIdle.QuadPart)) * (100)) / ((uKernel.QuadPart -
            TimeKernel.QuadPart) + (uUser.QuadPart - TimeUser.QuadPart)));
    TimeIdle.QuadPart = uIdle.QuadPart;
    TimeUser.QuadPart = uUser.QuadPart;
    TimeKernel.QuadPart = uKernel.QuadPart;
    return(static_cast<int>(t));
}

void CpuWhileThread(int Tsize)
{
    double Msize = 0;
    int i = 0;

    do
    {
        Sleep(1000);
        Msize += GetCpuUsage();
        i++;
    } while (i == Tsize);

    cpuU = Msize / Tsize;
}