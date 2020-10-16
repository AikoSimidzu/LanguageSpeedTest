namespace LanguageSpeedTestCSharp
{
    using System;
    using System.Diagnostics;
    using System.IO;
    using System.Threading;
    using System.Threading.Tasks;

    class Program
    {
        static bool GlobalT = false;
        static int Tet = 0, sec = 10, coreCount = 4;
        static long Tte = 0;

        static void Main(string[] args)
        {
            File.AppendAllText("ResultsCSharp.txt", "Starting: " + DateTime.Now + "\n");
            Task.Run(() => CpuWhileThread());

            double TempC = 0;

            for (int i = 0; (i - 1) != sec; i++)
            {
                Process p = Process.GetCurrentProcess();
                PerformanceCounter _perfCounter;
                Tet = p.Id;
                Tte = p.WorkingSet64 / 1024;

                _perfCounter = new PerformanceCounter("Process", "% Processor Time", p.ProcessName);
                TempC += _perfCounter.RawValue / coreCount / 100000;
                Thread.Sleep(1000);
                if ((i + 1) >= sec)
                {
                    File.AppendAllText("ResultsCSharp.txt", "CPU usage: " + (TempC / sec).ToString() + "%\n");
                    break;
                }
            }            

            Console.ReadKey();
        }                

        static void CpuWhileThread()
        {
            Task.Run (() => Timer(10));
            int i = 0;
            while (true)
            {
                ++i;
                Console.WriteLine(i);
                if (GlobalT != false)
                { 
                    File.AppendAllText("ResultsCSharp.txt", "Score result: " + i + "\n");
                    File.AppendAllText("ResultsCSharp.txt", "Ending: " + DateTime.Now + "\n");
                    break;
                }
            }            
            Console.WriteLine("Finish!");
        }

        static void Timer(int sec)
        {
            for (int i = 0; (i - 1) != sec; i++)
            {
                Thread.Sleep(1000);                
                Console.WriteLine("Прошло: {0}", i);
            }
            GlobalT = true;
        }
    }
}
