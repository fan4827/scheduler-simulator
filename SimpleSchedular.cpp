#include <iostream>
#include <vector>
#include<algorithm>
#include <queue>
using namespace std;

struct Process {
    int pid;
    int arrival;
    int burst;
    int remaining;
    int finish_time;
};

void FCFS(vector<Process>& p){
	int n=p.size(),time=p[0].arrival;
	for(int i=0;i<n;i++){
		time=max(p[i].arrival,time);
		p[i].finish_time=time+p[i].burst;
		time=p[i].finish_time;
	}
}

void SRJF(vector<Process>& p){
	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
	int time=0,finished=0,n=p.size(),i=0;
	
	while(finished < n){
		//new arrival
	    while(i<n && p[i].arrival <= time){
	        pq.push({p[i].remaining , i});
	        i++;
	    }
		//idle
	    if(pq.empty()){
	        time++;
	        continue;
	    }
	
	    auto cur = pq.top(); pq.pop();
	    int idx = cur.second;
	
	    p[idx].remaining--;
	    time++;
	
	    if(p[idx].remaining == 0){
	        p[idx].finish_time = time;
	        finished++;
	    }
	    else{
	        pq.push({p[idx].remaining , idx});
	    }
	}
}

void RR(vector<Process>& p,int quantum){
	queue<pair<int,int>>rrq;
	int time=0,finished=0,n=p.size(),i=0;
	while(finished < n){
		//new arrival
	    while(i<n && p[i].arrival <= time){
	        rrq.push({p[i].remaining , i});
	        i++;
	    }
		//idle
	    if(rrq.empty()){
	        time=p[i].arrival;
	        continue;
	    }
	    
	    auto cur = rrq.front(); rrq.pop();
	    int idx = cur.second,slice=min(quantum,p[idx].remaining);

	    p[idx].remaining-=slice;
	    time+=slice;
	    //slice new arrival
	    while(i<n && p[i].arrival <= time){
	        rrq.push({p[i].remaining , i});
	        i++;
	    }
	    //remain push_back
	    if(p[idx].remaining == 0){
	        p[idx].finish_time = time;
	        finished++;
	    }
	    else{
	        rrq.push({p[idx].remaining , idx});
	    }
	}
}

bool Compare(Process &a,Process &b){
	return a.arrival<b.arrival;
}

void PrintProcess(Process a){
	cout<<a.pid<<" "<<a.arrival<<" "<<a.burst<<" "<<a.remaining<<" "<<a.finish_time<<"\n";
}

void PrintWaiting_time(Process a){
	cout<<"Pid:"<<a.pid<<" Waiting time="<<a.finish_time-a.arrival-a.burst<<"\n";
}

int main(){
	int pid,arrival,burst;
	int waiting_time,turnaround_time;
	vector<Process>todo_queue;
	
	cout<<"PID Arrival Burst\n";
	while(cin>>pid>>arrival>>burst){
		todo_queue.push_back( {pid,arrival,burst,burst,arrival} );
	}
	sort(todo_queue.begin(),todo_queue.end(),Compare);
	
	RR(todo_queue,3);
	
	int n=todo_queue.size();
	for(int i=0;i<n;i++){
		PrintWaiting_time(todo_queue[i]);
	}
	
	return 0;
}

