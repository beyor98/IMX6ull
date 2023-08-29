#ifndef _LED_OPR_H
#define _LED_OPR_H

struct led_operations{
	int (*init) (int which);/*初始化led，which指定*/
	int (*ctl) (int which, char status);/*which进行指定，status显示状态*/
};

struct led_operations *get_board_led_opr(void);

#endif