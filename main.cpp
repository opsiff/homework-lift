/*
start : 2018/02/10 10:29
ps : Good code can say any things.

*/
#include<iostream>
using namespace std;
int Global_time,n = 5;
struct passenger
{
    int request_time;
    int request_place_from;
    int request_place_to;
    int request_wait_time_long;
    int request_arrive_time;
};
struct queue
{
    int use=0;
    int leave = -1;
};
struct passenger passengerL[6];
struct queue passengerQ[6];
//Above delimit the global variable
void in(){
    for (int i = 1; i <= n;i++){
        cin >> passengerL[i].request_time >> passengerL[i].request_place_from >> passengerL[i].request_place_to;
    }
}
//get the in data
int check(){
    for (int i = 1; i <= n;i++){
        if(passengerQ[i].use==0){
            return 1;
        }
    }
    return 0;
}
//check the queue use
void pass(){
    for (int lift_position = 1; lift_position <= 10;lift_position++){
        if(check()==0){
            break;
        }
        int floor_wait = 0;
        //pass judge
        int t = 0, minjudge,min_i;
        if(lift_position==10)
        for (int i = 1; i <= n;i++){
            //from use and request_place_from same lift_postion
            if(passengerQ[i].use==1&&passengerQ[i].leave==-1){
                passengerL[i].request_arrive_time = Global_time;
                passengerQ[i].leave = 1;
                floor_wait = 1;
            }
        }
        //getout
        for (int i = 1; i <= n;i++){
            //from no use and request_place_from same lift_postion and choose the min  request
            if(passengerQ[i].use==0){
                if(passengerL[i].request_place_from==lift_position && passengerL[i].request_place_to==0){
                    if(t==0){
                        minjudge = passengerL[i].request_time;
                        min_i = i;
                    }
                    else{
                        if(passengerL[i].request_time<minjudge){
                            minjudge = passengerL[i].request_time;
                            min_i = i;
                        }
                    }
                }
            }
        }
        if(t==1){
            passengerQ[min_i].use = 1;
            floor_wait = 1;
        }
        //getin judge
        Global_time+=floor_wait;
    }
    if(check()!=0)
    for (int lift_position = 10; lift_position >= 1;lift_position--){
        if(check()==0){
            break;
        }
        int floor_wait = 0;
        //pass judge
        int t = 0, minjudge,min_i;
        if(lift_position==1)
        for (int i = 1; i <= n;i++){
            //from use and request_place_from same lift_postion
            if(passengerQ[i].use==1&&passengerQ[i].leave==-1){
                passengerL[i].request_arrive_time = Global_time;
                passengerQ[i].leave = 1;
                floor_wait = 1;
            }
        }
        //getout
        for (int i = 1; i <= n;i++){
            //from no use and request_place_from same lift_postion and choose the min  request
            if(passengerQ[i].use==0){
                if(passengerL[i].request_place_from==lift_position && passengerL[i].request_place_to==1){
                    if(t==0){
                        minjudge = passengerL[i].request_time;
                        min_i = i;
                    }
                    else{
                        if(passengerL[i].request_time<minjudge){
                            minjudge = passengerL[i].request_time;
                            min_i = i;
                        }
                    }
                }
            }
        }
        if(t==1){
            passengerQ[min_i].use = 1;
            floor_wait = 1;
        }
        //getin judge
        Global_time+=floor_wait;
    }
}
void run(){
    for (int lift_times = 1; lift_times <= n;lift_times++){
        pass();
    }
}
//run for answer
void out(){
    int temp=0;//count the number of wait time
    for (int i = 1; i <= n;i++){
        cout << passengerL[i].request_arrive_time << "时，停靠在";
        cout << passengerL[i].request_place_to << "楼"<<endl;
    }
    cout << temp << endl;
}
//output the out data
int main(){
    void in();
    void run();
    void out();
    return 0;
}