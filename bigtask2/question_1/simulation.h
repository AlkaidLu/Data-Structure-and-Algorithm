#include<fstream>
#include<iostream>
#include <cstring>
enum State {warehouse,onshelf,thrown,sold};

class Drug{

private:
    int ID;
    double cost;
    double price;
    int inilife;
    int life;
    State state;

public:
    Drug(int ID = -1, double cost = 0, double price = 0, int inilife=0, int life = 0, State state = warehouse);
    int getID();
    double getcost();
    int getlife(int day);
    double getprice();
    void setprice(double price);
    void changelife(int day);//药品保质期随时间缩短
    State getstate();
    void changestate(int s);
};

Drug::Drug(int id, double c, double p, int inilife, int life, State state)
    : ID(id), cost(c), price(p), inilife(inilife), life(life), state(state) {}
int Drug::getID(){
    return ID;
}
double Drug::getcost(){
    return cost;
}
double Drug::getprice(){
    return price;
}
void Drug::setprice(double p){
    price=p;
}
int Drug::getlife(int day){
    changelife(day);
    return life;
}
void Drug::changelife(int day){
    life=inilife-day;
}
State Drug::getstate(){
    return state;
}
void Drug::changestate(int s){
    switch (s)
    {
    case 0:
        state=warehouse;
        break;
    case 1:
        state=onshelf;
        break;
    case 2:
        state=thrown;
        break;
    case 3:
        state=sold;
        break;
    default:
        break;
    }
}

class Pharmacy{
private:
    Drug drugs[50];
public:
    Pharmacy(Drug * readdrug);                                 //初始化
    Drug & findDrug(int id);                       //查看药品    
};
Pharmacy::Pharmacy(Drug *readdrug) {
    for (int i = 0; i < 50; i++) {
        drugs[i] = readdrug[i];
    }
}

Drug& Pharmacy::findDrug(int id){
    if (id >= 0 && id < 50) {
        return drugs[id];
    }
    else{
        printf("error");
        Drug drug;
        return drug;
    }
}


class Simulation{
    private:
        int day;
        double profit;
        Pharmacy * ph;
    public:
    Simulation(char *filename);
    void GetManageCost(void);
    void DeleteExpiredmedicine(char *filename);
    double GetProfit();
    void Sortdrug(Drug *somedrug, int len);         //优先按保质期排序，相等时再按价格排序
    void RunSimulation(char *filename, char *delname, char *outfile);  
    void PrintSimulationResults(char * filename); 
};

//药品排序
void Simulation::Sortdrug(Drug *somedrug, int len){
    for(int i=0; i<len; i++)
    {
        for(int j=i+1; j<len; j++)
        {
            if(somedrug[i].getprice() > somedrug[j].getprice())
            {
                Drug tmp = somedrug[i];
                somedrug[i] = somedrug[j];
                somedrug[j] = tmp;
            }
            else if(somedrug[i].getlife(day) < somedrug[j].getlife(day) && somedrug[i].getprice() == somedrug[j].getprice())
            {
                Drug tmp = somedrug[i];
                somedrug[i] = somedrug[j];
                somedrug[j] = tmp;
            }
        }
    }
}      
//给外部调用留下接口，给出利润
double Simulation::GetProfit(){
    return profit;
}
//模拟初始化
Simulation::Simulation(char *filename){
    day = 0;
    profit = 0;
    FILE *fp = fopen(filename, "r");
    Drug *readdrug=new Drug[50];
    //int ID = -1, double cost = 0, double price = 0, int inilife=0, int life = 0, State state = warehouse
    for(int i=0; i<50; i++)
    {
        int l;
        double c;
        fscanf(fp, "%lf\t%d\n", &c, &l);
        Drug singledrug(i,c,0,l);
        readdrug[i]=singledrug;
    }
    fclose(fp);
    ph = new Pharmacy(readdrug);
    delete []readdrug;
    
}
//把利润减去某一天的管理费
void Simulation::GetManageCost(void){
    for(int i=0;i<50;i++){
        if(ph->findDrug(i).getstate()==warehouse){
            if(ph->findDrug(i).getlife(day)<5){
                profit-=1;
            }
            else{
                profit-=0.5;
            }
        }
    }
}
//删去过期药品
void Simulation::DeleteExpiredmedicine(char *filename){
    FILE *fp = NULL;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error file read in delete.\n");
        return;
    }
    int d;
    int id;
    while(fscanf(fp, "%d\t%d\n", &d, &id)!=EOF)
    {
    if(day == d)
        {
            ph->findDrug(id).changestate(thrown);
            profit-=ph->findDrug(id).getcost();

        }
    }
    fclose(fp);
}
//根据策略上架药品，开始跑模拟
void Simulation::RunSimulation(char *onshelfname, char *delname, char *outfile){
    FILE *fp = fopen(onshelfname, "rb");
    if (fp == NULL) {
        printf("Error file read.\n");
        return;
    }
    DeleteExpiredmedicine(delname);//看看有没有第0天丢弃的药品
    double profitlist[7] = {-1.5, -1, -0.5, 0, 2 ,4 ,6};
    for(day=1;day<=10;day++){
        Drug *onshelfdrug=new Drug[10];
        int num=0;
        //药品上架，计算货架上的价格
        for(int j=0; j<10; j++)
        {
            int id;
            int index;
            fscanf(fp, "%d,%d\t", &id, &index);
            if(id!=-1){
                double c= profitlist[index];
                ph->findDrug(id).changestate(onshelf);
                ph->findDrug(id).setprice(ph->findDrug(id).getcost()+c);
                //printf("%d\t%lf\n",id,ph->findDrug(id).getprice());
                onshelfdrug[num]=ph->findDrug(id);
                num++;
            }
        }
        //对一天的药按价格和保质期排序
        Sortdrug(onshelfdrug,num);
        //卖出，获得利润
        for(int i=0;i<3;i++){
            ph->findDrug(onshelfdrug[i].getID()).changestate(sold);
            profit+=onshelfdrug[i].getprice()-onshelfdrug[i].getcost();
            
        }    
        //减去管理费
        GetManageCost();
        //商品下架
        for(int j=3; j<num; j++)
        {
            ph->findDrug(onshelfdrug[j].getID()).changestate(warehouse);
        }
        PrintSimulationResults(outfile);
        //printf("Day%d:",day);
        //printf( "%f\n", profit);
        //减掉丢掉的药品的进价
        DeleteExpiredmedicine(delname);
        delete [] onshelfdrug;
       
    }
    FILE *f = fopen(outfile, "a");
    fprintf(f, "Fianl:\n");
    fprintf(f, "%f\n", profit);
    fprintf(f, "\n");
    fclose(f);

    fclose(fp);
}


void Simulation::PrintSimulationResults(char *filename) {
    FILE *fp;
    if(day==1){
        fp = fopen(filename, "wb");
    }
    else{
        fp = fopen(filename, "a");
    }
    fprintf(fp, "Day%d:\n", day);
    fprintf(fp, "%f\n", profit);
    fclose(fp);
}
/*
 switch(onshelfdrug[i].getstate()) {
        case warehouse:
            std::cout << "Warehouse";
            break;
        case onshelf:
            std::cout << "On Shelf";
            break;
        case thrown:
            std::cout << "Thrown";
            break;
        case sold:
            std::cout << "Sold";
            break;
        case exhausted:
            std::cout << "Exhausted";
            break;
        default:
            std::cout << "Unknown State";
    }
    */