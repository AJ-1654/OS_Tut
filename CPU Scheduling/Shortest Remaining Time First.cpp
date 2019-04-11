#include <bits/stdc++.h>
using namespace std;

struct process
{
    int PId,BurstTime,ArrivalTime,WaitTime,TurnAroundTime,ResponseTime;
    int __startTime,__finishTime;
    bool operator < (process other)
    {
        return ArrivalTime<other.ArrivalTime;
    }

    struct comparator///sort by remaining time
    {
        static map<int,int> RemainingTime; ///maps process id to remaining time
        bool operator () (process A,process B)
        {
            return RemainingTime[A.PId]>RemainingTime[B.PId];///by default max priority que is formed
        }
    };
};
map <int,int> process::comparator::RemainingTime=map<int,int> ();///initialize static variables

int n;///number of processes
process P[1000],Out[1000];

void update(int n,process P[])
{
    double BT=0,WT=0;
    for (int i=0;i<n;i++)
    {
        P[i].TurnAroundTime=P[i].__finishTime-P[i].ArrivalTime;
        P[i].WaitTime=P[i].TurnAroundTime-P[i].BurstTime;
        P[i].ResponseTime=P[i].__startTime-P[i].ArrivalTime;
        BT+=P[i].BurstTime;WT+=P[i].WaitTime;
    }
    cout<<"Avg Burst Time : "<<BT/n<<"\n"<<"Avg Wait Time :  "<<WT/n<<"\n";
}
double utilization(int n,process P[])
{
    int worktime=0,__MT=0;
    for (int i=0;i<n;i++)worktime+=P[i].BurstTime,__MT=max(__MT,P[i].__finishTime);
    return ((double)worktime*100.0/__MT);
}
double throughput(int n,process P[])
{
    int totalBT=0;
    for (int i=0;i<n;i++)totalBT+=P[i].BurstTime;
    return (double)n/totalBT;
}
int main()
{
    freopen("inputSRTF.txt","r",stdin);
    cin>>n;
    for (int i=0;i<n;i++)
    {
        cin>>P[i].BurstTime>>P[i].ArrivalTime;P[i].PId=i+1;
        process::comparator::RemainingTime[i+1]=P[i].BurstTime;
    }
    sort(P,P+n);///sort by arrival time
    priority_queue <process,vector <process>,process::comparator> PQ;
    int Curtime=P[0].ArrivalTime,processespushed=0,ind=0;

    while(processespushed!=n)
    {
        Curtime=max(Curtime,P[processespushed].ArrivalTime);
        while(processespushed<n&&P[processespushed].ArrivalTime==Curtime)PQ.push(P[processespushed]),processespushed++;

        while((!PQ.empty()))
        {
            auto z=PQ.top();PQ.pop();
            if (process::comparator::RemainingTime[z.PId]==z.BurstTime)z.__startTime=Curtime;
            if (processespushed<n)
            {
                if (P[processespushed].ArrivalTime<Curtime+process::comparator::RemainingTime[z.PId])
                {
                    process::comparator::RemainingTime[z.PId]-=(P[processespushed].ArrivalTime-Curtime);
                    Curtime=P[processespushed].ArrivalTime;
                    PQ.push(z);
                    break;
                }
                else
                {
                    Curtime+=process::comparator::RemainingTime[z.PId];
                    z.__finishTime=Curtime;
                    Out[ind++]=z;
                    process::comparator::RemainingTime[z.PId]=0;

                }
            }
            else
            {
                Curtime+=process::comparator::RemainingTime[z.PId];
                z.__finishTime=Curtime;
                Out[ind++]=z;
                process::comparator::RemainingTime[z.PId]=0;
            }
        }

    }
    for (int i=0;i<n;i++)P[i]=Out[i];


    update(n,P);
    cout<<"Utilization : "<<utilization(n,P)<<"\n";
    cout<<"Throughput : "<<throughput(n,P)<<"\n";
    cout<<"ID      AT  StTime    FinTime  BT       WT     TAT      RT\n";

    for (int i=0;i<n;i++)
    {
        cout<<P[i].PId<<"\t"<<P[i].ArrivalTime<<"\t"<<P[i].__startTime<<"\t"<<P[i].__finishTime<<"\t"
            <<P[i].BurstTime<<"\t"<<P[i].WaitTime<<"\t"<<P[i].TurnAroundTime<<"\t"<<P[i].ResponseTime
        <<"\n";
    }
}
