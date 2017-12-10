
#include<reg52.h>	//Header file of generic 80C51

/*
R1, Y1, G1 are red,Yellow and green lights for north
side traffic regulate by first three bits of port 2 of 8051
*/
sbit R1=P2^0;
sbit Y1=P2^1;
sbit G1=P2^2;				

/*
R2, Y2, G2 are red,Yellow and green lights for east
side traffic regulate by three bits(4,5&6) of port 2 of 8051
*/
sbit R2=P2^4;
sbit Y2=P2^5;
sbit G2=P2^6;

/*
R3, Y3, G3 are red,Yellow and green lights for south
side traffic regulate by first three bits of port 3 of 8051
*/
sbit R3=P3^0;
sbit Y3=P3^1;
sbit G3=P3^2;

/*
R4, Y4, G4 are red,Yellow and green lights for west
side traffic regulate by three bits(4,5&6) of port 3 of 8051
*/
sbit R4=P3^4;
sbit Y4=P3^5;
sbit G4=P3^6;


void Delay_msec(unsigned int);   //Delay Function declaration using onboard timer

void main()			// Start of program			  
{
	int looper;			//Variable to regulate the State of program
   	TMOD=0x10;			//Setting mode: timer,software based, 16 bit register
	looper=0;			//Initialization of variable 
	P2=0x12;			//Initialization of port 2[Set Y1,R2]
	P3=0x11;			//Initialization of port 3[Set R3,R4]
	Delay_msec(1000);	//calling delay function
    while(1)                // infinite loop
    {
	switch(looper)		//Switch case
	{
	/*
	Transition of traffic lights b/w North and East  
	*/
	case 0 :
	Y1=0;		  
	G1=1;		  		//Go signal for North traffic
	Delay_msec(5000);	//Timer of 5 seconds
	G1=0;
	Y1=1;
	R2=0;
	Y2=1;				//Ready signal for East traffic
	Delay_msec(1000);	//Timer of 1 second
	Y1=0;
	R1=1;				//Stop signal for North traffic
	break;
	
	/*
	Transition of traffic lights b/w East and South  
	*/
	case 1 :
	Y2=0;
	G2=1;				//Go signal for East traffic
	Delay_msec(5000);	//Timer of 5 seconds
	G2=0;
	Y2=1;
	R3=0;
	Y3=1;				//Ready signal for South traffic
	Delay_msec(1000);	//Timer of 1 second
	Y2=0;
	R2=1;				//Stop signal for East traffic
	break;

	/*
	Transition of traffic lights b/w South and West  
	*/	
	case 2 :
	Y3=0;
	G3=1;				 //Go signal for South traffic
	Delay_msec(5000);	 //Timer of 5 seconds
	G3=0;
	Y3=1;
	R4=0;
	Y4=1;				  //Ready signal for West traffic
	Delay_msec(1000);	 //Timer of 1 second
	Y3=0;
	R3=1;
	break;				 //Stop signal for South traffic
	
	/*
	Transition of traffic lights b/w West and North   
	*/
	case 3 :
	Y4=0;
	G4=1;				  //Go signal for West traffic
	Delay_msec(5000);	  //Timer of 5 seconds
	G4=0;
	Y4=1;
	R1=0;
	Y1=1;				  //Ready signal for North traffic
	Delay_msec(1000);	  //Timer of 1 second
	Y4=0;
	R4=1;				  //Stop signal for West traffic
	break;
	default :
	break;
	}
	looper=looper+1;	  //Increment in case
	looper=looper%4;	  // To bound variable b/w 0 to 4
    }
}

void Delay_msec(unsigned int num_msec)	//Delay function with input in milliseconds
{
	int i;
   	TH1=0x00;					 
   	TL1=0x00;					 //Clear the timer 1 register
	TR1=0x40;					 //Start timer
/*
Timer register is 16 bit
Clock speed =occilator speed/12
Occilator Speed is 11.5 MHz
Timer register overflow in 71 milliseconds
*/
	for(i=0; i<num_msec/71;i++){ //Set delay
	TF1=0;						 //Clear overflow flag
	while(TF1==0){				 //while overflow flag is clear
	} 
	}
}
