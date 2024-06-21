/*
 * displayer.h
 *
 *  Created on: Nov 3, 2023
 *      Author: Ahmedmohamed
 */

#ifndef DISPLAYER_H_
#define DISPLAYER_H_
#define MC1_READY 0x10

/*extern uint8 fpass[5], spass[5], thpass[5], reset_pass[5],i, counters,key;*/
void dis_pass1(void);
void reenter_pass(void);
void screen_door(void);
void dislay_error(void);
void display_firstpass(void);
void display_2ndpass(void);
void compare_tw0_passwords(void);





#endif /* DISPLAYER_H_ */
