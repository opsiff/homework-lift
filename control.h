#ifndef CONTROL_FLAG 
#define CONTROL_FLAG // Type declaration here... 
//电梯的控制面板，上面有电梯的状态，aim是楼层有没有被按
class control_table{
  private:
    int state;//1.空载，2.有客

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
#endif //CONTROL_FLAG