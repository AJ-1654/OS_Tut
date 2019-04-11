#include <bits/stdc++.h>
using namespace std;

struct process
{
    int PId,BurstTime,ArrivalTime,WaitTime,TurnAroundTime,ResponseTime;
    int __startTime,__finishTime;
    static map <int,int> RemainingTime;
    bool operator < (process other)
    {
        return ArrivalTime<other.ArrivalTime;
    }
};
map<int,int> process::RemainingTime=map<int,int>();
int n;///number of processes
int quantum=3;
process P[1000],Out[1000];

void update(int n,process P[])
{
    double BT=0,WT=0,TAT=0;
    for (int i=0;i<n;i++)
    {
        P[i].TurnAroundTime=P[i].__finishTime-P[i].ArrivalTime;
        P[i].WaitTime=P[i].TurnAroundTime-P[i].BurstTime;
        P[i].ResponseTime=P[i].__startTime-P[i].ArrivalTime;
        BT+=P[i].BurstTime;WT+=P[i].WaitTime;
        TAT+=P[i].TurnAroundTime;
    }
    cout<<"Avg Burst Time : "<<BT/n<<"\n"<<"Avg Wait Time :  "<<WT/n<<"\n"<<"Avg TA Time :  "<<TAT/n<<"\n";;
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
    freopen("inputRR.txt","r",stdin);
    ///freopen("inputRRnoAT.txt","r",stdin);
    cin>>n;
    for (int i=0;i<n;i++)
    {
        cin>>P[i].BurstTime>>P[i].ArrivalTime;P[i].PId=i+1;
        process::RemainingTime[i+1]=P[i].BurstTime;
    }
    sort(P,P+n);

    int Curtime=P[0].ArrivalTime,ind=0,curr=0,processesadded=0;
    vector <process> V;

    while(ind!=n)
    {
        while(processesadded<n&&P[processesadded].ArrivalTime<=Curtime)
            V.push_back(P[processesadded]),processesadded++;

        curr%=V.size();
        auto &z=V[curr];
        if (process::RemainingTime[z.PId]==0)
        {
            curr=(curr+1);continue;
        }
        if (process::RemainingTime[z.PId]==z.BurstTime)z.__startTime=Curtime;
        if (process::RemainingTime[z.PId]<=quantum)
        {
            Curtime+=process::RemainingTime[z.PId];
            z.__finishTime=Curtime;
            process::RemainingTime[z.PId]=0;
            Out[ind++]=z;
        }
        else
        {
            Curtime+=quantum;
            process::RemainingTime[z.PId]-=quantum;
        }
        curr=(curr+1);
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
