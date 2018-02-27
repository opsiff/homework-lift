#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
class control_table{
  private:
    int state;//1.���أ�2.�п�

  public:
    int aim[11];
    control_table(){
        state = 1;
        for (int i = 0; i <= 10;i++){
            aim[i] = 0;
        }
    };
    int ask_for_state();
    int update_state(int floor);
    int downdate_state(int floor);
    ~control_table(){};
};
class elevator{
  //friend int check_get();

public:
  elevator(){
    elevator_place = 1;
  };
  void get(int people);
  void out(int people);
  void MoveUp();
  void MoveDowm();
  int state();
  ~elevator(){};

private:
  int people_num;
  int elevator_place;
}; 
void elevator::MoveDowm(){
    elevator_place--;
}
void elevator::MoveUp(){
    elevator_place++;
}
void elevator::get(int people){
    people_num+=people;
}
void elevator::out(int people){
    people_num-=people;
}
int elevator::state(){
    return elevator_place;
}
int control_table::ask_for_state(){
    return state;
}
int control_table::update_state(int floor){
    if(floor==-1){
        state = 1;
        return 0;
    }
    else{
        state = 2;
        aim[floor] = 1;
        return 1;
    }
}
int control_table::downdate_state(int floor){
    aim[floor] = 0;
    bool k = 0;
    for (int i = 0; i <= 10;i++){
        if(aim[i]==1)
            k = 1;
    }
    if(k==0)
        state = 1;
    return 1;
}
int abs(int k){
    return (k > 0) ? k : (-k);
}
//ʱ����㿪ʼ���������
int Global_time=0,n = 5;
control_table control1;
elevator elevator1;
struct passenger{
    int req_time,req_place_fr,req_place_to;
    int /*req_wait_time_long,*/req_arrive_time=100;
    int use,leave;
};
struct passenger passengerL[6];
void check_data(){
    for (int i = 1; i <= 5;i++){
        if(passengerL[i].req_time<0||passengerL[i].req_place_fr<0||passengerL[i].req_place_to<0){
            cout << "���벻�Ϸ�" << endl;
            exit(0);
        }
    }
}
void in(){
    for (int i = 0; i < 6;i++){
        passengerL[i].use = 0;passengerL[i].leave = 0;
    }
    for (int i = 1; i <= 5;i++){
        cin >> passengerL[i].req_time;
        cin >> passengerL[i].req_place_fr;
        cin >> passengerL[i].req_place_to;
        if(passengerL[i].req_place_to==0)
            passengerL[i].req_place_to = 10;
    }
        check_data();
}
//��������Ƿ����
int check_queue_use(){
    for (int i = 1; i <= 5;i++){
        if(passengerL[i].leave==0){
            return i;
        }
    }
    return 0;
}
//Ѱ����Ѵ��������
int find_passenger(){
    //ȥ�ҵ�ǰ��һ������
    if(check_queue_use()!=0){
        int passengermin = 100000;
        int passengerminn = -1;
        for (int i = 1; i <= 5;i++){
            if(passengerL[i].req_time<passengermin&&passengerL[i].use==0){
                passengermin=passengerL[i].req_time;
                passengerminn = i;
            }
        }
        return passengerminn;
    }
    else{
        return -1;
    }
} 
//Ѱ��Ŀ�ĵ�ͣ��
int find_aim_place(int floor){
    int temp=100,tmp;
    for (int i = 1; i <= 10;i++){
        if(control1.aim[i]==1){
            if(abs(floor-i)<temp){
                tmp = i;
                temp = abs(floor - i);
            }
        }
    }
    return tmp;
}
int check_get(){
    int passengerT;
    passengerT = find_passenger();
    //�������ʱ���Ŀǰ�磬����û����Ӧ�����Ҹպ������
    if(passengerT>0)
    if(passengerL[passengerT].req_time<=Global_time){
        if(passengerL[passengerT].use==0){
            if(passengerL[passengerT].req_place_fr==elevator1.state()){
                //cout << passengerT << endl;
                return 1;
            }
        }
    }
    return 0;
}
int put_out(){
    bool state = 0;//�Ƿ������µ���
    for (int i = 1; i <= n;i++){
        //�����˶�Ӧ¥���ʱ��Ѱ���������˵��ݿ����µĳ˿�
        if(passengerL[i].req_place_to==elevator1.state()){
            if(passengerL[i].use==1&&passengerL[i].leave==0){
               // cout << "out " << i << endl;
                passengerL[i].leave = 1;
                passengerL[i].req_arrive_time = Global_time;
                elevator1.out(1);
                control1.downdate_state(elevator1.state());
                state = 1;
            }
        }
    }
    if(state==1){
        return 1;
    }
    else{
        return 0;
    }
}
//���ĵ��Ȳ���
void run(){
    int person,/*person_number=1,*/floor_stop=0;
    //�ҵ�һ����
    person = find_passenger();
    //passengerL[person].use = 1;
    if(person!=-1){
        //����ʱ��δ��������
        if(Global_time<passengerL[find_passenger()].req_time){
            bool k = 0;
            for (int i = 1; i <= n;i++){
                if(passengerL[i].use==1&&passengerL[i].leave==0){
                    k = 1;
                }
            }
            if(k==0){
                Global_time = passengerL[find_passenger()].req_time;
            }
        }
        else{
            control1.update_state(passengerL[person].req_place_fr);
        }
    }
    
    //�ƶ���;+��;�ӿ�/�¿�
        //    cout << "fget " << find_passenger() << " "<<find_aim_place(elevator1.state())<<endl;
    while(elevator1.state()!=find_aim_place(elevator1.state())){
        //��;����
        floor_stop = put_out();
        while(check_get()){//�ƶ�����;����
            floor_stop = 1;//ͣ��ʱ��
            int temp_passenger = find_passenger();//��ֹ�ظ�����
        //    cout << "get " << temp_passenger << endl;
            passengerL[temp_passenger].use = 1;//�Ѿ���Ӧ
            control1.update_state(passengerL[temp_passenger].req_place_to);//����Ŀ��¥�㰴ť
            elevator1.get(1);//���ݼ���
        }
       // cout << "find " << find_aim_place(elevator1.state()) << "\n";
        control1.downdate_state(elevator1.state()); //�����¥����
        if(elevator1.state()<find_aim_place(elevator1.state())){
            elevator1.MoveUp();
            //cout << "Up" << elevator1.state() <<floor_stop<<Global_time<< endl;
            Global_time=Global_time+floor_stop+1;
            floor_stop = 0;
        }
        else{
            elevator1.MoveDowm();
        //    cout << "Down" << elevator1.state() << endl;
            Global_time=Global_time+floor_stop+1;
            floor_stop = 0;
        }
    }
    //����
    floor_stop = put_out();
    while(check_get()){//����
        floor_stop = 1;//ͣ��ʱ��
        int temp_passenger = find_passenger();//��ֹ�ظ�����
      //  cout << "get " << temp_passenger << endl;
        passengerL[temp_passenger].use = 1;//�Ѿ���Ӧ
        control1.update_state(passengerL[temp_passenger].req_place_to);//����Ŀ��¥�㰴ť
        elevator1.get(1);//���ݼ���
    }
    Global_time = Global_time + floor_stop;
    control1.downdate_state(elevator1.state()); //�����¥����
    //cout << Global_time << "\n";
}
void out(){
    int temp=0;
    for (int i = 1; i <= 5;i++){
        temp = temp + (passengerL[i].req_arrive_time - passengerL[i].req_time);
       // cout << passengerL[i].req_arrive_time<< " " << passengerL[i].req_time<<" "<<passengerL[i].req_place_to<<"\n";
        cout << passengerL[i].req_arrive_time<< "ʱ��ͣ����" << passengerL[i].req_place_to<<"¥\n";
    }
    cout << temp << "\n";
}
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    in();
        //int ff = 0;
    //��������˵�����û�����㣬���ݾͼ�������
    while(check_queue_use()!=0){
       // cout << "run " << ++ff << endl;
        run();
    }
    out();
    //while(1);
    return 0;
}

