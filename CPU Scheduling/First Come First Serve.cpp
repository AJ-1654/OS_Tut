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
};

int n;///number of processes
process P[1000];

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
    freopen("inputFCFS.txt","r",stdin);
    cin>>n;
    for (int i=0;i<n;i++)
    {
        cin>>P[i].BurstTime>>P[i].ArrivalTime;P[i].PId=i+1;
    }
    sort(P,P+n);

    queue <process> Q;
    for (int i=0;i<n;i++)
    {
        Q.push(P[i]);
    }

    int T=0,ind=0;
    while(!Q.empty())
    {
        auto z=Q.front();Q.pop();
        T=max(T,z.ArrivalTime);
        z.__startTime=T;
        z.__finishTime=T+z.BurstTime;
        T=z.__finishTime;
        P[ind]=z;
        ind++;
    }
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
