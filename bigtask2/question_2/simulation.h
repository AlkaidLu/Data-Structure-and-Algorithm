#include<fstream>
#include<iostream>
#include <cstring>
using namespace std;
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
    Drug(int ID = -1, double cost = 0, double price = 0,
     int inilife=0, int life = 0, State state = warehouse);
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
        printf("ID can't find error");
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
    void Sortsell(Drug* sorted_drug, int date);
    Drug *Sortonshelf(Drug* sorted_drug, int date);
    void Strategy(char* filename, char* delfile);
    void DeleteDrug(char *filename,  Drug* drug);
    void Sortdrug(Drug *somedrug, int len);         //优先按保质期排序，相等时再按价格排序
    void RunSimulation(char *filename, char *delname, char *outfile);  
    void PrintSimulationResults(char * filename); 
};

//对于顾客，购买的药品排序
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
//给出利润
double Simulation::GetProfit(){
    return profit;
}
//制定销售策略，对药品排序
void Simulation::Sortsell(Drug* sorted_drug, int date) {
    for(int i=0; i<50; i++)
    {
        for(int j=i+1; j<50; j++)
        {
            if(sorted_drug[i].getlife(date) > sorted_drug[j].getlife(date))
            {
                std::swap(sorted_drug[i], sorted_drug[j]);
            }
            else if(sorted_drug[i].getlife(date) == sorted_drug[j].getlife(date) 
                && sorted_drug[i].getprice() > sorted_drug[j].getprice())
            {
                std::swap(sorted_drug[i], sorted_drug[j]);
            }
            if (sorted_drug[i].getlife(date) >= 10 && sorted_drug[j].getlife(date) >= 10
            &&sorted_drug[i].getprice() > sorted_drug[j].getprice())
                {
                    std::swap(sorted_drug[i], sorted_drug[j]);
                }
        }
    }
}
Drug* Simulation::Sortonshelf(Drug* sorted_drug, int date) {
    for(int i=0; i<50; i++)
    {
        for(int j=i+1; j<50; j++)
        {
                if(sorted_drug[i].getlife(date) > sorted_drug[j].getlife(date))
                    {
                        std::swap(sorted_drug[i], sorted_drug[j]);
                    }
        }
    }
    return sorted_drug;
}
//写delete的文件,delete前应该按过期时间为第一关键字，价格为第二关键字排好序了
void Simulation::DeleteDrug(char *filename, Drug* drug) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    int j = 0;
    int sum = 0;
    for (int d = 1; d < 11; d++) {
        while (j < 50 && drug[j].getlife(0) == d) {
            sum++;
            j++;
        }

        if (sum > 3 * d) {
            int del = sum - 3 * d;
            int i = 0; 
            while (j < 50&&i<del) {
                int id = drug[j].getID();
                drug[j].changestate(thrown);
                fprintf(fp, "0\t%d\n", id); // 第零天丢掉
                j++;
                i++;
            }
            sum-=del;
        }
    }

    fclose(fp);
}

//制定上架策略，并写入Strategy文件
void Simulation::Strategy(char* strfile, char* delfile) {
    double profitlist[7] = {-1.5, -1, -0.5, 0, 2 ,4 ,6};
    FILE* fp;
    fp = fopen(strfile, "wb");
    Drug* sorted_drug = new Drug[50];
    // 初始化药品数组，并设置初始价格方便排序
    for (int i = 0; i < 50; i++) {
        sorted_drug[i] = ph->findDrug(i);
        sorted_drug[i].setprice(sorted_drug[i].getcost()+6);
    }
    int overten=0;
    while(sorted_drug[overten].getlife(0)<10){
        overten++;
    }
    Sortsell(sorted_drug, 0);
    DeleteDrug(delfile, sorted_drug);//生成丢掉的药品文件
   for (int date = 1; date <= 10; date++) // 十天的上架策略
    {
        // 调用排序策略获取排序后的药品数组
        Sortsell(sorted_drug, 0);
        double top = 0; // 用于存储三种药品中最高标价(每天)
        // 从 sorted_drugs 里选头三种药品,利润设为最高
        int cnt=0;
        int minlife=1000;
        //卖出顺序排序
        for (int i = 0; i < 50 && cnt < 3; i++) {
            if (sorted_drug[i].getstate() != thrown&&sorted_drug[i].getstate() != sold) {
                int id = sorted_drug[i].getID();
                int index = 6;
                fprintf(fp, "%d,%d\t", id, index);
                if(sorted_drug[i].getlife(0)<minlife)
                    minlife=sorted_drug[i].getlife(0);
                sorted_drug[i].changestate(sold);
                sorted_drug[i].setprice(sorted_drug[i].getcost() + profitlist[index]);
                
                if (sorted_drug[i].getprice() > top)
                    top = sorted_drug[i].getprice();
                cnt++;
            }
        }
        // 在保证头三种药品卖掉的情况下
        // 即剩下的七种药品成本加上 6 价格仍然大于头三种里的最高价
        // 尽量选取保质期小的药品上架（可以节省保管费）
        Drug * onshelf=NULL;
        //上架的其他药品排序,只按时间先后排
        onshelf=Sortonshelf(sorted_drug, date);
        //上架
        for (int i = 0; i < 50 && cnt < 10; i++) {
            if (onshelf[i].getstate() != thrown &&onshelf[i].getstate() != sold&&
                //onshelf[i].getcost()+6 > top)
                (onshelf[i].getcost()+6>top||onshelf[i].getlife(0)<=minlife))
                 {
                //SortStrategy(sorted_drug,date);
                int id = onshelf[i].getID();
                int index = 6;
                fprintf(fp, "%d,%d\t", id, index);
                onshelf[i].setprice(onshelf[i].getcost() + profitlist[index]);
                cnt++;
            }
        }
        //没放满的情况
        while(cnt<10){
            fprintf(fp, "-1,6\t");
            cnt++;
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    delete[] sorted_drug;
}

//模拟初始化
Simulation::Simulation(char *filename){
    day = 0;
    profit = 5;
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
    
    DeleteExpiredmedicine(delname);//第0天丢弃的药品
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
        printf("Day%d:",day);
        printf( "%f\n", profit);
        
        delete [] onshelfdrug;
       
    }
    FILE *f = fopen(outfile, "a");
    fprintf(f, "Fianl:\n");
    fprintf(f, "%f\n", profit);
    fprintf(f, "\n");
    fclose(f);
    printf( "Fianl:\n");
    printf("%f\n", profit);
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