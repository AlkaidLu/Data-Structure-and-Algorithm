#ifndef SIMULATION_CLASS
#define SIMULATION_CLASS

#include <iostream>
#include <iomanip>
using namespace std;
#pragma hdrstop

#include "random.h"     // include random number generator

#define num_vip_window 0

// specifies the two kinds of events
enum EventType {arrival, departure};
enum isVip { notVip, Vip };

class Event                                         
{
    private:
        // members that identify both customer and teller, as
        // well as maintain information on time of the event,
        // the event type, the length of service required by
        // the customer, and the amount of time customer is
        // forced to wait for service
        int time;
        EventType etype;
        isVip ctype;
        int customerID;     // customers numbered 1, 2, 3,...
        int tellerID;       // tellers numbered 1, 2, 3,...
        int waittime;
        int servicetime;
        bool isCut;
    public:
        // constructors
        Event(void);
        Event(int t,EventType et,isVip ct,int cn,int tn,
              int wt,int st,bool ic);
        
        // methods to retrieve private data
        int GetTime(void) const;
        EventType GetEventType(void) const;
        isVip GetCustomerType(void) const;
        int       GetCustomerID(void) const;
        int GetTellerID(void) const;
        int GetWaitTime(void) const;
        int GetServiceTime(void) const;
        bool GetisCut();
        void Cut(bool iscut);
};

// default constructor - data filled by assignment later
Event::Event(void)
{}

// constructor that initializes all data members of the event
Event::Event(int t, EventType et, isVip ct, int cn, int tn,
             int wt,int st,bool ic=0): 
               time(t),etype(et),ctype(ct),customerID(cn),tellerID(tn),
               waittime(wt),servicetime(st),isCut(ic)
{}
    
// return the time the event occurs
int Event::GetTime(void) const
{
    return time;
}
    
// return the type of event (arrival, departure)
EventType Event::GetEventType(void) const
{
    return etype;
}

isVip Event::GetCustomerType(void) const {
    return ctype;
}

// return the customer number
int Event::GetCustomerID(void) const
{
    return customerID;
}
    
// return the teller number
int Event::GetTellerID(void) const
{
    return tellerID;
}
    
// return the time the customer waits for service
int Event::GetWaitTime(void) const
{
    return waittime;
}

// return the amount of teller time needed by customer
int Event::GetServiceTime(void) const
{
    return servicetime;
}
bool Event::GetisCut(){

    return isCut;
}
void Event::Cut(bool iscut){
    isCut=iscut;
}
// compare two Event objects using the time at 
// which the events occur. needed for the priority queue
int operator< (Event e1, Event e2)
{
    return e1.GetTime() < e2.GetTime();
}

typedef  Event  DataType;       // elements are Event objects

#include "apqueue.h"


// Structure for Teller Info    
struct TellerStats
{
    int finishService;      // when teller available
    int vipCustomerCount; // customers serviced
    int notvipCustomerCount;
    int vipCustomerWait;  //  customer waiting time
    int notvipCustomerWait;
    int totalService;       // total time servicing customers
};


class Simulation
{
    private:
        // data used to run the simulation
        int simulationLength;        // simulation length
        int numTellers;              // number of tellers
        int nextCustomer;            // next customer ID
        isVip isvip;
        int waitHigh;
        int arrivalLow, arrivalHigh; // next arrival range
        int serviceLow, serviceHigh; // service range
        TellerStats tstat[11];       // max 10 tellers
        /*
        PQueue pq_n;                   // priority queue for normal customers
        PQueue pq_v;                   //priority queue for vip customers
        */
        PQueue pq;
        RandomNumber rnd;            // use for arrival
                                     // and service times
                                        
        // private methods used by RunSimulation
        isVip NextCustomertype(void);
        int NextArrivalTime(void);
        int GetServiceTime(void);
        int NextAvailableTeller(isVip iv);
    public:
        // constructor
        Simulation(void);
                
        void RunSimulation(void);           // execute study
        void PrintSimulationResults(void);  // print stats
};

// constructor initializes simulation data and prompts client
// for simulation parameters
Simulation::Simulation(void)    
{
    int i;
    Event firstevent;
    
    // Initialize Teller Information Parameters
    for(i = 1; i <= 10; i++)
    {
        tstat[i].finishService = 0; 
        tstat[i].totalService = 0;
        tstat[i].vipCustomerWait = 0;
        tstat[i].vipCustomerCount = 0;
        tstat[i].notvipCustomerWait = 0;
        tstat[i].notvipCustomerCount = 0;
    }
    nextCustomer = 1;
    
    // reads client input for the study
    cout << "Enter the simulation time in minutes: ";
    cin >> simulationLength;
    cout << "Enter the number of bank tellers: ";
    cin >> numTellers;
    cout << "Enter the range of arrival times in minutes: ";
    cin >> arrivalLow >> arrivalHigh;
    cout << "Enter the range of service times in minutes: ";
    cin >> serviceLow >> serviceHigh;
    cout << "Enter the highest tolerated wait times of vip in minutes: ";
    cin >> waitHigh;
    
   bool flag = NextCustomertype();
    if (flag) {
    pq.PQInsert(Event(0, arrival, Vip, 1, 0, 0, 0));
    } 
    else {
    pq.PQInsert(Event(0, arrival, notVip, 1, 0, 0, 0));
    }
// generate first arrival event
// teller#/waittime/servicetime not used for arrival

}

isVip Simulation::NextCustomertype(void)
{
    int isvip=rnd.Random(100);
    if(isvip>75)//生成vip的概率是25%
        return Vip;
    else
        return notVip;
}
// determine random time of next arrival 
int Simulation::NextArrivalTime(void)
{
    return arrivalLow+rnd.Random(arrivalHigh-arrivalLow+1);
}

// determine random time for customer service
int Simulation::GetServiceTime(void)
{
    return serviceLow+rnd.Random(serviceHigh-serviceLow+1);
}

// return first available teller
int Simulation::NextAvailableTeller(isVip iv)
{
    // initially assume all tellers finish at closing time
    int minfinish = 10*simulationLength;
    
    // assign random teller to customer who arrives
    // before closing but obtains service after closing
    int minfinishindex = rnd.Random(numTellers) + 1;
   if(iv){
        // find teller who is free first for Vip
        for (int i = 1; i <= numTellers; i++)
        {
            if (tstat[i].finishService < minfinish)
            {
                minfinish = tstat[i].finishService;
                minfinishindex = i;
            }
        }
    }
    else{
        // find teller who is free first for notVip
        for (int i = 1+num_vip_window; i <= numTellers; i++)
        {
            if (tstat[i].finishService < minfinish)
            {
                minfinish = tstat[i].finishService;
                minfinishindex = i;
            }
        }
    }
    return minfinishindex;
}


// implements the simulation
void Simulation::RunSimulation(void)
{
    Event e, newevent;
    int nexttime;
    int tellerID;
    int servicetime;
    int waittime;
        
    // run till priority queue is empty
    
    /*while (!pq_n.PQEmpty()|!pq_v.PQEmpty())*/
    while (!pq.PQEmpty())
    {
        // get next event (time measures the priority)
        e = pq.PQDelete();

        // handle an arrival event
        if (e.GetEventType() == arrival)
        {
            //get the type of customer(Vip/notVip)
            isVip isvip = NextCustomertype();//1 for Vip, 0 for notVip
            // compute time for next arrival.
            nexttime = e.GetTime() + NextArrivalTime();
            
            if (nexttime > simulationLength);
                // process events but don't generate any more
            else
            {
                // generate arrival for next customer. put in queue
                nextCustomer++;
                newevent = Event(nexttime, arrival, isvip, nextCustomer, 0, 0, 0);
                pq.PQInsert(newevent);

            }
            
            cout << "Time: " << setw(2) << e.GetTime()
                 << "  " << "arrival   of "<<(e.GetCustomerType()?"   Vip":"notVip")<<" customer "
                 << e.GetCustomerID() ;
            
            // generate departure event for current customer
            
            // time the customer takes
            servicetime = GetServiceTime();
            // teller who services customer
            tellerID = NextAvailableTeller(e.GetCustomerType());
            cout << "       Teller " << tellerID<<endl;
            // if teller free, update sign to current time
            if (tstat[tellerID].finishService == 0)
                tstat[tellerID].finishService = e.GetTime();
            // compute time customer waits by subtracting the
            // current time from time on the teller's sign
            waittime = tstat[tellerID].finishService -
                        e.GetTime();
            // update teller statistics
            
            tstat[tellerID].totalService += servicetime;
            tstat[tellerID].finishService += servicetime;

            // create a departure object and put in the queue
            newevent = Event(tstat[tellerID].finishService,
                        departure, e.GetCustomerType(),e.GetCustomerID(),tellerID,
                        waittime,servicetime);
            pq.PQInsert(newevent);

            
            
        }
        // handle a departure event
        else
        {
            cout << "Time: " << setw(2) << e.GetTime()
                 << "  " << "departure of "<<(e.GetCustomerType()?"   Vip":"notVip")<<" customer "
                 << e.GetCustomerID();
            cout << "       Teller " << e.GetTellerID()
                 << "  Wait " << e.GetWaitTime()
                 << "  Service " << e.GetServiceTime()
                 << endl;
            
            tellerID = e.GetTellerID();
            // if nobody waiting for teller, mark teller free
            if (e.GetTime() == tstat[tellerID].finishService)
                tstat[tellerID].finishService = 0;
            
            if(e.GetCustomerType()){
            tstat[tellerID].vipCustomerWait += e.GetWaitTime();
            tstat[tellerID].vipCustomerCount++;
            }
            else{
            tstat[tellerID].notvipCustomerWait += e.GetWaitTime();
            tstat[tellerID].notvipCustomerCount++;
            }
            //执行完当前的departure,就开始对队伍里的vip的等待时间进行计算
            
            //**add**//
            PQueue tmp;
            bool flag=0;
            int cut_servicetime;
            int ini_tellerID;
            int to_tellerID;
            int high_vip_wait=0;
            //探测有没有vip不耐烦了
            while(!pq.PQEmpty()){
                Event t = pq.PQDelete();
                //如果t的类型是vip的departure，且此时等待时间比最大等待时间长,服务一个vip
                if(t.GetEventType()==departure&&t.GetCustomerType()==Vip
                &&e.GetTime()<t.GetTime()-t.GetServiceTime()
                &&e.GetTime()-(t.GetTime()-t.GetServiceTime()-t.GetWaitTime())>waitHigh
                &&flag==0&&t.GetisCut()==0){
                    if(high_vip_wait<e.GetTime()-(t.GetTime()-t.GetServiceTime()-t.GetWaitTime())){
                        high_vip_wait=e.GetTime()-(t.GetTime()-t.GetServiceTime()-t.GetWaitTime());
                        cut_servicetime=t.GetServiceTime();
                        ini_tellerID=t.GetTellerID();
                        to_tellerID=e.GetTellerID();
                    }

                    t=Event(e.GetTime()+cut_servicetime,
                        departure, t.GetCustomerType(),t.GetCustomerID(),tellerID,
                        e.GetTime()-(t.GetTime()-t.GetServiceTime()-t.GetWaitTime()),
                        t.GetServiceTime(),1);
                    flag=1;
                    cout<<"VIP customer "<<t.GetCustomerID()<<" will be served by teller "<<tellerID<<" immediately.\n";
                }
                tmp.PQInsert(t);
            }
            while (!tmp.PQEmpty())              
                {                                  
                    Event t = tmp.PQDelete();
                    pq.PQInsert(t);
                }
            if(flag==1){
                while(!pq.PQEmpty()){
                    Event t = pq.PQDelete();
                    //插队窗口其他离开事件预计等待时间增加
                    if(t.GetTime() - t.GetServiceTime() >= e.GetTime()&&t.GetEventType()==departure
                    &&t.GetTellerID()==to_tellerID&&t.GetisCut()==0){
                        t=Event(t.GetTime()+cut_servicetime,
                            departure, t.GetCustomerType(),t.GetCustomerID(),t.GetTellerID(),
                            t.GetWaitTime()+cut_servicetime,t.GetServiceTime(),0);
                    }
                    //原窗口其他离开事件预计等待时间减小
                    else if(t.GetTime() - t.GetServiceTime() >= e.GetTime()&&t.GetEventType()==departure
                    &&t.GetTellerID()==ini_tellerID&&t.GetisCut()==0){
                        t=Event(t.GetTime()-cut_servicetime,
                            departure, t.GetCustomerType(),t.GetCustomerID(),t.GetTellerID(),
                            t.GetWaitTime()-cut_servicetime,t.GetServiceTime(),0);
                    }
                    tmp.PQInsert(t);
                }
                while (!tmp.PQEmpty())              
                {                                  
                    Event t = tmp.PQDelete();
                    pq.PQInsert(t);
                }
            }
            
            
            //**add**//
        } 
    }
    
    // adjust simulation to account for overtime by tellers
    simulationLength = (e.GetTime() <= simulationLength)
                        ? simulationLength : e.GetTime();
}

// summarize the simulation results
void Simulation::PrintSimulationResults(void)
{
    int cumvipCustomers = 0, cumvipWait = 0, cumnotvipCustomers = 0, cumnotvipWait = 0, i;
    int avgvipCustWait=0, avgnotvipCustWait=0, tellerWorkPercent;
    float tellerWork;

    for (i = 1; i <= numTellers; i++)
    {
        cumvipCustomers += tstat[i].vipCustomerCount;
        cumvipWait += tstat[i].vipCustomerWait;
        cumnotvipCustomers += tstat[i].notvipCustomerCount;
        cumnotvipWait += tstat[i].notvipCustomerWait;
    }

    cout << endl;
    cout << "******** Simulation Summary ********" << endl;
    cout << "Simulation of " << simulationLength
         << " minutes" <<" with "<<num_vip_window<<" vip windows" << endl;
    cout << "   No. of vip Customers:  " << cumvipCustomers << endl;
    cout << "   No. of notvip Customers:  " << cumnotvipCustomers << endl;
    cout << "   Average vip Customer Wait: ";
    if(cumvipCustomers!=0){
        avgvipCustWait = int(float(cumvipWait)/cumvipCustomers + 0.5);
    }
    cout << avgvipCustWait << " minutes" << endl;
    cout << "   Average notvip Customer Wait: ";
    
    if(cumnotvipCustomers!=0){
        avgnotvipCustWait = int(float(cumnotvipWait)/cumnotvipCustomers + 0.5);
    }
    cout << avgnotvipCustWait << " minutes" << endl;
    for(i=1;i <= numTellers;i++)
    {
        cout << "    Teller #" << i << "  % Working: ";
        // display percent rounded to nearest integer value
        tellerWork = float(tstat[i].totalService)/simulationLength;
        tellerWorkPercent =int( tellerWork * 100.0 + 0.5);
        cout << tellerWorkPercent << endl;
    }
}

#endif  // SIMULATION_CLASS