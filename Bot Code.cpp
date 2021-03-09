#define echoPin 11
#define trigPin 10
#define IR1 A1
#define IR2 A2
#define IR3 A3
#define m1s1 5
#define m1s2 3
#define m2s1 9
#define m2s2 6

//ultrasonic function 

int ultrasonic()
{ 
	long dist, duration; 
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(5);
	digitalWrite(trigPin, LOW);
	duration = pulseIn(echoPin,HIGH)/2;
	dist = duration/29.15;    //distance is in centimetre return dist;
}

//infrared functions

int ir1()
{ 
	return(digitalRead(IR1));
}

int ir2()
{ 
	return(digitalRead(IR2));
}

int ir3()
{ 
	return(digitalRead(IR3));
}

// movement functions

void forward()                  //forward
{ 
	digitalWrite(m1s1,HIGH); 
	digitalWrite(m1s2,LOW); 
	digitalWrite(m2s1,HIGH); 
	digitalWrite(m2s2,LOW);
}

void backward()                  //backward
{ 
	digitalWrite(m1s2,HIGH); 
	digitalWrite(m2s1,LOW); 
	digitalWrite(m2s2,HIGH);
}

void left()                  //left
{ 
	digitalWrite(m1s1,HIGH);
	analogWrite(m1s2,100); 
	digitalWrite(m2s1,LOW); 
	digitalWrite(m2s2,LOW); 
	delay(600);
}

void right()                  //right
{ 
	digitalWrite(m1s1,LOW); 
	digitalWrite(m1s2,LOW); 
	digitalWrite(m2s1, HIGH); 
	analogWrite(m2s2,100); 
	delay(600);
}

void sharp_left()                  //sharp left
{ 
	digitalWrite(m1s1,HIGH); 
	digitalWrite(m1s2,LOW); 
	digitalWrite(m2s1,LOW); 
	digitalWrite(m2s2,LOW); 
	delay(600);
}

void sharp_right()                  //sharp right
{ 
	digitalWrite(m1s1,LOW); 
	digitalWrite(m1s2,LOW); 
	digitalWrite(m2s1,HIGH); 
	digitalWrite(m2s2,LOW); 
	delay(600);
}

void circular_rotate()                     //rotate right in one position and stop for the ultrasonic to detect---------
{ 
	digitalWrite(m1s1,LOW); 
	digitalWrite(m1s2,HIGH); 
	digitalWrite(m2s1,HIGH); 
	digitalWrite(m2s2,LOW); 
	delay(50); 

	digitalWrite(m1s2,LOW); 
	digitalWrite(m2s1,LOW); 
	digitalWrite(m2s2,LOW); 
	delay(50);
}

void rotate_left(){ 
	digitalWrite(m1s1,HIGH); 
	digitalWrite(m1s2,LOW); 
	digitalWrite(m2s1,LOW); 
	digitalWrite(m2s2,HIGH); 
	delay(400);
}

void rotate_right(){ 
	digitalWrite(m1s1,LOW); 
	digitalWrite(m1s2,HIGH); 
	digitalWrite(m2s1,HIGH); 
	digitalWrite(m2s2,LOW); 
	delay(400);
}



void back_se_sharp_left()                  //back se sharp left
{ 
	digitalWrite(m1s1,LOW); 
	digitalWrite(m1s2,HIGH); 
	digitalWrite(m2s1,LOW); 
	digitalWrite(m2s2,LOW); 
	delay(600);}

void back_se_sharp_right()                  //back se sharp right
{ 
	digitalWrite(m1s1,LOW); 
	digitalWrite(m1s2,LOW); 
	digitalWrite(m2s1,LOW); 
	digitalWrite(m2s2,HIGH); 
	delay(600);
}

//function to ensure we dont go out of ring void check(){
if(ir1()>200 && ir2()<200 && ir3()<200)          //200 is the threshold value for analog read ir
{ 
	rotate_right();   
	forward();   
	delay(400);
}
else if(ir1()<200 && ir2()>200 && ir3()<200)
{ 
	rotate_left();    
	forward();   
	delay(150);
}
else if(ir1()<200 && ir2()<200 && ir3()>200)
{ 
	forward();   
	delay(150);
} 
else if(ir1()>200 && ir2()>200 && ir3()<200)
{ 
	backward();
	delay(150); 
}
else if(ir1()>200 && ir2()<200 && ir3()>200)
{ 
	rotate_right();    
	forward();   
	delay(150); 
}
else if(ir1()<200 && ir2()>200 && ir3()>200)
{ 
	rotate_left();    
	forward();  
	delay(150); 
}
else if(ultrasonic()<75)
{ 	
	while(ultrasonic()<75)
		forward();
}

void setup() { 
	Serial.begin(9600); 
	pinMode(trigPin, OUTPUT); 
	pinMode(echoPin, INPUT); 
	pinMode(IR1, INPUT); 
	pinMode(IR2, INPUT); 
	pinMode(IR3, INPUT); 
	pinMode(m1s1, OUTPUT); 
	pinMode(m1s2, OUTPUT); 
	pinMode(m2s1, OUTPUT); 
	pinMode(m2s2, OUTPUT);
}

void loop()
{
	//for begining :3 different option to be used depending on analysis of opponet bot past matches
	
	//option 1 : just push----------------------------- 
	while( ultrasonic()<75 )
		forward();

	//option 2: savage dodge--------------------------
	
	static int j=1;             //we want it only in the begining------------- 
	if(j==1){ 	
		backward();
		delay(2000);
		if(ultrasonic()<(20))      //escape when he comes close escape----------- 
			back_se_sharp_left();
		just++;
	}
	
	//option 3: let loose and escape ------------------
	
	//static int j=1;                 we want it only in the begining 
	int i=0;
	if(j==1) 
	while( ultrasonic()<75)
	{ 
		analogWrite(m1s2,128);              // less power than opponent---------------- 
		digitalWrite(m1s1,0);               // so that he can push--------------- 
		analogWrite(m2s2,128);              // and escape at the edge------------ 
		digitalWrite(m2s1,0);
		if(ir3()==1)                        // escape just at the border--------------- 
			back_se_sharp_left();
		i++; 
	}
	j++;
	
	 




	//if opponent out of sight for begining :2 different option to be used depending on analysis of opponet bot past matches
	
	//option 1: nagin dance : move like snakes in ring
	 left(); while(1)
	{
		right();
		if( ir1()>200 || ir2()>200 || ir3()>200 || ultrasonic()<75 )   // if after right turn an ir on break
			break;

		right();
		if( ir1()>200 || ir2()>200 || ir3()>200 || ultrasonic()<75 )
			break;

		left();
		if( ir1()>200 || ir2()>200 || ir3()>200 || ultrasonic()<75 )
			break;

		left();
		if( ir1()>200 || ir2()>200 || ir3()>200 || ultrasonic()<75 )
			break;

	}
	

	//option 2: find space and move in circles
	static int j=1;                       //we want it only in the begining---------------------- 
	if(j==1)                              //move left and and forward to find space for circle
	{ 
		left(); 
		forward(); 
		delay(200); 
		j++;
	}
	while(1)
	{
		right();
		if( ir1()>200 || ir2()>200 || ir3()>200 || ultrasonic()<75 )
			break;
	} 
	check();              //check if we are near border of if opponent in radar------------------

}
