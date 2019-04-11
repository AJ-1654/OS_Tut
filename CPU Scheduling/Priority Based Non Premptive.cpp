#include <bits/stdc++.h>
using namespace std;

struct process
{
    int PId,BurstTime,ArrivalTime,WaitTime,TurnAroundTime,ResponseTime,Priority;
    int __startTime,__finishTime;
    bool operator < (process other)
    {
        return ArrivalTime<other.ArrivalTime;
    }
     struct comparator///sort by burst time
    {
        bool operator () (process A,process B)
        {
            if (A.Priority==B.Priority&&A.ArrivalTime==B.ArrivalTime)return A.PId>B.PId;
            if (A.Priority==B.Priority)return A.ArrivalTime>B.ArrivalTime;
            return A.Priority<B.Priority;///by default max priority que is formed
        }
    };
};

int n;///number of processes
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
    cout<<"Avg Burst Time : "<<BT/n<<"\n"<<"Avg Wait Time :  "<<WT/n<<"\n"<<"Avg TA Time :  "<<TAT/n<<"\n";
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
    freopen("inputPriorityNP.txt","r",stdin);
    ///freopen("inputSJFnoAT.txt","r",stdin);
    cin>>n;

    for (int i=0;i<n;i++)
    {
        cin>>P[i].Priority>>P[i].BurstTime>>P[i].ArrivalTime;P[i].PId=i+1;
    }
    sort(P,P+n);///sort by arrival time
    priority_queue <process,vector <process>,process::comparator> PQ;
    int Curtime=P[0].ArrivalTime,processespushed=0,ind=0;
    int CurP=P[0].Priority;
    while(processespushed!=n)
    {
        Curtime=max(Curtime,P[processespushed].ArrivalTime);
        while(processespushed<n&&P[processespushed].ArrivalTime<=Curtime)PQ.push(P[processespushed]),processespushed++;

        while((!PQ.empty())&&(processespushed==n||(processespushed<n&&Curtime<P[processespushed].ArrivalTime)))
        {
            auto z=PQ.top();PQ.pop();
            z.__startTime=Curtime;
            Curtime+=z.BurstTime;
            z.__finishTime=Curtime;
            Out[ind++]=z;
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

