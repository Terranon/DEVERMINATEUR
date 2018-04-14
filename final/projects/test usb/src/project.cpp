/*****************************************************************************\
 * Authors: Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour,
 *          William Chartrand
 * Name:        project.cpp
 * Description: Project to communicate with the robodiag program
 * 
 * Pinout :                                                     
 *                                                                     
 * PORTA  1 3 5 7    PORTB  1 3 5 7    PORTC  0 1 2 3 4 5 6 7    PORTD  1 3 5 7 
 *        0 2 4 6           0 2 4 6                                     0 2 4 6 
 *                                                                      

 * Version: 1.0
\******************************************************************************/

#include <USBCommunicator.h>

/******************************************************************************\
 * Main
\******************************************************************************/
int main() {
	USBCommunicator usb;
	usb.communicate();
}
