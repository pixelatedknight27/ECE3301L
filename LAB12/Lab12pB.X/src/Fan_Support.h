int get_RPM();
void Toggle_Fan();
void Turn_Off_Fan();
void Turn_On_Fan();
void Increase_Speed();
void Decrease_Speed();
void do_update_pwm(char);
void Set_DC_RGB(int);
void Set_RPM_RGB(int);
void Set_TempC_RGB(signed char);


#define FAN_EN          PORTDbits.RD6
#define FAN_PWM         PORTCbits.RC2
#define FANON_LED       PORTDbits.RD2
