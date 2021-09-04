/* Robot line following program
 the robot will follow the black electrical tape around the course. 
 after hitting the other perpendicular black line, it will perform a u-turn.
 it will go back to the initial starting position and stop on the black line.
 * inputs: RA3 & RA4 
 * outputs: RB6, RB7, RB8, RB9
/* -----------------------------------------------------------------
 * Bryan Huang
 * June 21st, 2021
------------------------------------------------------------------- */
/* ------------------------------------------------------------------
Include Files
------------------------------------------------------------------- */
#include "p24F32KA302.h"
#include "configBits.h"
#include "delay.h"
/* ----------------------------------------------------------------
Symbolic Constants used by main()
---------------------------------------------------------------- */
/* ----------------------------------------------------------------`
Local Function Prototypes
---------------------------------------------------------------- */
void fwd(void); // moves the robot forwards when both sensors are high
void left(void); // moves the robot left when left sensor is low and right sensor is high
void right(void); // moves the robot right when right sensor is low and left sensor is high
void turnaround(void); // turns the robot around when both sensors are low
void stop(void); // stops the robot when both sensors are low for a second time
/* ---------------------------------------------------------------- */
int counter = 0; // checks how many times the circuit has hit a black line

// main part of code
int main()
 {
    // initialize the timer for delay
    initTimer();
    // teach all PORTB to be outputs
    TRISB = 0x00;
    // initialize all PORTB
    LATB = 0;
    // set PORTA to all digital inputs
    TRISA = 0xFF;
    // initialize all PORTA
    ANSA = 0;
    
    // continues looping this part of code infinitely
    while (1)
    {
        // move car forward
        if (PORTAbits.RA3 == 1 && PORTAbits.RA4 == 1) 
        {
            fwd(); // fwd method
        } // fi
        // move car left
        else if (PORTAbits.RA3 == 1 && PORTAbits.RA4 == 0) // left
        {
            left(); // left method
        } // fi esle 
        // move car right
        else if (PORTAbits.RA3 == 0 && PORTAbits.RA4 == 1) // right
        {
            right(); // right method
        } // fi esle
        // turn the car around
        if (PORTAbits.RA3 == 0 && PORTAbits.RA4 == 0 && counter == 0) // stop or turnaround
        {
            turnaround(); // turnaround method
        } // fi
        // stop the car 
        if (PORTAbits.RA3 == 0 && PORTAbits.RA4 == 0 && counter == 1)
        {
            stop(); // stop method
        } //fi
    } // elihw
} // niam

/* -----------------------------------------------------------
List of functions: all the mini codes that jump from the
main program loop to execute a set of codes and then jump back to the main
program when it's finished.
----------------------------------------------------------- */
void fwd(void)
{
    // continue looping the forward movement if both sensors are on
    while (PORTAbits.RA3 == 1 && PORTAbits.RA4 == 1)
    {
        LATBbits.LATB6 = 0; 
        LATBbits.LATB7 = 1; // right wheel forward
        LATBbits.LATB8 = 0; 
        LATBbits.LATB9 = 1; // left wheel forward
    } // elihw
} // end of fwd method
void left(void)
{
    // continues turning left if the left sensor is off
    while (PORTAbits.RA3 == 1 && PORTAbits.RA4 == 0)
    {
        LATBbits.LATB6 = 0;
        LATBbits.LATB7 = 1; // right wheel forward
        LATBbits.LATB8 = 1; // left wheel reverse
        LATBbits.LATB9 = 0;
    } // elihw
} // end of left method
void right(void)
{
    // continues turning right while the right sensor is off
    while (PORTAbits.RA3 == 0 && PORTAbits.RA4 == 1)
    {
        LATBbits.LATB6 = 1; // right wheel backwards
        LATBbits.LATB7 = 0;
        LATBbits.LATB8 = 0;
        LATBbits.LATB9 = 1; // left wheel forward
    } // elihw
} // end of right method
void turnaround(void)
{
    LATBbits.LATB6 = 0;
    LATBbits.LATB7 = 1; // right wheel forward
    LATBbits.LATB8 = 1; // left wheel reverse
    LATBbits.LATB9 = 0;
    // makes the robot u-turn for 800 milliseconds
    delay(800); 
    // continues turning the robot if it has not reached the track yet
    while (PORTAbits.RA3 == 1 && PORTAbits.RA4 == 1)
    { 
        LATBbits.LATB6 = 0;
        LATBbits.LATB7 = 1; // right wheel forward
        LATBbits.LATB8 = 1; // left wheel reverse
        LATBbits.LATB9 = 0;
        // turns the robot left for 20 milliseconds
        delay(20);
        LATBbits.LATB6 = 0; 
        LATBbits.LATB7 = 0; 
        LATBbits.LATB8 = 0; 
        LATBbits.LATB9 = 0; 
        // no movement for 20 milliseconds
        delay(20);
    } // elihw
    // increment the counter by one
    counter++; 
} // end of turnaround method
void stop(void)
 {
    // continues to keep all motors low while both sensors are off
    while (PORTAbits.RA3 == 0 && PORTAbits.RA4 == 0)
    {
        LATBbits.LATB6 = 0;
        LATBbits.LATB7 = 0;
        LATBbits.LATB8 = 0;
        LATBbits.LATB9 = 0;
    } // elihw
} // end of stop method