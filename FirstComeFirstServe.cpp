//Author: Vaidehi Desai
//Github: vaidehi-cell

// C++ implementation of program to implement 'First Come First Serve Algorithm'(Non- preemptive) for process scheduling
// For the input of Context Switching Time, Arrival Time and Burst Time of Processes in order of Process Id.,
// The program prints Completion time, Turn Around Time, Waiting Time corresponding to every process in order,
// the Average Waiting time and the Efficiency of schedule.
#include <bits/stdc++.h>
using namespace std;

//Class: process to store process information
class process
{
public:
    double at;
    double bt;
    double p_id;
};

int main()
{
    //at = Arrival Time, bt = Burst Time, wt = Waiting Time, del = Context Switching Time, Inefficiency =  Time no process is being executed
    double bt, at, ct = 0, wt = 0, del = 0, inefficiency = 0;
    //i = Process ID
    int i = 1;

    //Comparator for priority queue of processes.
    auto cmp = [](process a, process b)
    {
        //In case two process arrive at different times, give higher priority to first arrived process
        if (a.at > b.at)
            return true;
        else if (a.at < b.at)
            return false;
        //if two processes arrive at same time, give higher priority to lower process id.
        else if (a.p_id < b.p_id)
            return false;
        else
            return true;
    };

    //Priority Queue to keep Processes in required order of execution
    priority_queue<process, vector<process>, decltype(cmp)> at_bt(cmp);

    //Inputs
    cout << "Enter the Context Switching Time: " << endl;
    cin >> del;
    cout << "Enter -1 when all inputs entered.\n";
    while (true)
    {
        cout << "Process no. " << i << ":" << endl;
        cout << "Enter Arrival time and Burst Time: ";
        cin >> at;
        if (at < 0)
        {
            break;
        }
        cin >> bt;
        if(bt < 0)
        {
            break;
        }
        process p;
        p.at = at;
        p.bt = bt;
        p.p_id = i;
        at_bt.push(p);
        i++;
    }
    //Initially no process is running till first arrival so, initialize inefficiency with the first arrival time 
    inefficiency = at_bt.top().at;
    //Vector to store Completion Time and process id of processes in order of execution
    vector<pair<double, int>> ct_list;
    //Vectors to store Wating Time Time and Turn Around Time of processes in order of execution respectively
    vector<double> wt_list, tat_list;

    //Calculating the completion time, Waiting Time and Turn Around Time
    while (!at_bt.empty())
    {
        ct += del;
        process tp = at_bt.top(); 
        inefficiency += del;
        wt += ct - tp.at;
        wt_list.push_back(ct - tp.at);
        ct += tp.bt;
        tat_list.push_back(ct - tp.at);
        ct_list.push_back({ct, tp.p_id});
        at_bt.pop();
        if (!at_bt.empty())
        {
            if (at_bt.top().at > ct)
            {
                inefficiency += at_bt.top().at - ct;
                ct = at_bt.top().at;
            }
        }
    }

    //Output
    for (int i = 0; i < ct_list.size(); i++)
    {
        cout << "Process " << ct_list[i].second << ": " << "\n\tCT  = " << ct_list[i].first << "\n\tTAT = " << tat_list[i];
        cout << "\n\tWT  = " << wt_list[i] << endl;
    }
    cout << "Average Waiting Time = " << wt/(double)(wt_list.size()) << endl;
    cout << "Efficiency = " << 1 - inefficiency/(double)ct << endl;
    return 0;
}
