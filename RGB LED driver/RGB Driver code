///////////////////////////////////////////////////////////// APP DETAILS //////////////////////////////////////////////////////
// R,G,B,(128-133),x,x                     for ON/OFF
// R,G,B,0,x,x                             for simple colour change

// R,G,B,1,(21-35),x                       for low speed flash mode
// R,G,B,5,(20-29),(0-9)                   for high speed flash mode

// R,G,B,2,(21-35),x                       for giving time delay for loop mode
// R,G,B,6,(0-255),(0-255)                 for colour selection in loop mode

// R,G,B,3,(21-35),x                       for giving time delay for fade mode
// R,G,B,7,(0-127),x                       for colour selection in loop mode

// R,G,B,4,x,(0-255)                       for music mode
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <IRremote.h>
#include <EEPROM.h>
/////////////////////////////////////////////////////////////////////////
////////////////////////////// IR SECTION ///////////////////////////////
/////////////////////////////////////////////////////////////////////////

int flash,stro,fade,smooth;
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);

int green = 6;   //green
int red = 5;   //red 
int blue = 9;  //blue

//int led=13;

decode_results results;
int r3=0;// this variable makes sure that when system is powered on controller reads the state of IR only once
int a1=0;// to avoid other remote signals
/////////////////////////////////////////////////////////////////////////
////////////////////////// BLUETOOTH SECTION ////////////////////////////
/////////////////////////////////////////////////////////////////////////

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
  
//  pinMode(led, OUTPUT); 
  
  pinMode(red, OUTPUT); 
  pinMode(blue, OUTPUT); 
  pinMode(green, OUTPUT);
}

void dump(decode_results *results)
{
  int finaldata2[20];
  uint8_t s1,s4;
  unsigned long codeValue=results->value;
  
   if((codeValue==16236607)||(codeValue==16203967)||(codeValue==16187647)||(codeValue==16220287)||(codeValue==16195807)||(codeValue==16228447)||(codeValue==16212127)||(codeValue==16244767)||(codeValue==16191727)||(codeValue==16224367)||(codeValue==16208047)||(codeValue==16240687)||(codeValue==16199887)||(codeValue==16232527)||(codeValue==16216207)||(codeValue==16248847)||(codeValue==16189687)||(codeValue==16222327)||(codeValue==16206007)||(codeValue==16238647)||(codeValue==16197847)||(codeValue==16230487)||(codeValue==16214167)||(codeValue==16246807))
   {
    a1=1;
    /// while bluetooth is ON and a colour or mode is set by bluetooth, and remote is pressed 
    /// only if remote is basically in ON mode it goes into the loop and resets the bluetooth 
    /// data by making all the 6 packet values to 200 
    /// then the decoded ir remote value is evaluated and the respective colour is generated
    for(int u1=0;u1<6;u1++)
    {
        finaldata2[u1]=200;
        EEPROM.write((u1+25),finaldata2[u1]);
    }
    for(int u2=31;u2<53;u2++)
    {
      EEPROM.write(u2,0);
    }    
   }

   else
   {
     a1=0;
   }
   
  ////////////////// OFF /////////////////////
  if(codeValue==16203967)
  {
    s4=0;
    goto y1;
  }
  ////////////////// ON /////////////////////
  if(codeValue==16236607)
  {
    s4=0xff;
    goto y1;
  }
  
  while(0)
  {
    y1:EEPROM.write(4,s4);
  }
  //////////////////// red section /////////////////////
    if(codeValue==16195807)
    {
      s1=0x01;
      goto y2;
    }
    
    if(codeValue==16191727)
    {
      s1=0x05;
      goto y2;
    }
    if(codeValue==16199887)
    {
      s1=0x09;
      goto y2;
    }
    if(codeValue==16189687)
    {
      s1=0x0D;
      goto y2;
    }
    if(codeValue==16197847)
    {
      s1=0x11;
      goto y2;
    }  
    /////////////////// green section///////////////////////
    if(codeValue==16228447)
    {
      s1=0x02;
      goto y2;
    }
    if(codeValue==16224367)
    {
      s1=0x06;
      goto y2;
    }
    if(codeValue==16232527)
    {
      s1=0x0A;
      goto y2;
    }
    if(codeValue==16222327)
    {
      s1=0x0E;
      goto y2;
    }
    if(codeValue==16230487)
    {
      s1=0x12;
      goto y2;
    }  
    ///////////////////blue section///////////////////////
    if(codeValue==16212127)
    {
      s1=0x03;
      goto y2;
    }
    if(codeValue==16208047)
    {
      s1=0x07;
      goto y2;
    }
    if(codeValue==16216207)
    {
      s1=0x0B;
      goto y2;
    }
    if(codeValue==16206007)
    {
      s1=0x0F;
      goto y2;
    }
    if(codeValue==16214167)
    {
      s1=0x13;
      goto y2;
    }  
    ///////////////////pure white///////////////////////
    if(codeValue==16244767)
    {
      s1=0x04;
      goto y2;
    }
    //////////////////// Flash (red, green, blue, white, purple, orange) ////////////////////////
    if(codeValue==16240687)  
    {
      s1=0x08;
      goto y2;
    }
    //////////////////////////////// strobe (white fading) /////////////////////  
    if(codeValue==16248847)  
    {
      s1=0x0C;
      goto y2;
    }
    //////////////////////////////// fade (all colours fading) /////////////////////  
    if(codeValue==16238647)  
    {
      s1=0x10;
      goto y2;
    }
    //////////////////////////////// smooth (RGB flashing) /////////////////////  
    if(codeValue==16246807)  
    {
      s1=0x14;
      goto y2;
    }

    while(0)
    {
      y2:EEPROM.write(3,s1);
    }
  
  if(a1==1)
  {
    flash=0;
    stro=0;
    fade=0;
    smooth=0;
    remote();
  }
}

void remote()
{
  uint8_t s2,s3;
  s2=EEPROM.read(3);
  s3=EEPROM.read(4);

  ///////////////// OFF section /////////////////////
  if(s3==0)
  {
    analogWrite(red, 0);
    analogWrite(green, 0);
    analogWrite(blue, 0);
  }
  if(s3==0xff)
  {
    ////////////////////////////////////// red section ///////////////////////////////////
          if(s2==0x01)
          {
            analogWrite(red, 255);
            analogWrite(green, 0);
            analogWrite(blue, 0);
          }
          if(s2==0x05)
          {
            analogWrite(red, 255);
            analogWrite(green, 60);
            analogWrite(blue, 0);
          }
          if(s2==0x09)
          {
            analogWrite(red, 255);
            analogWrite(green, 107);
            analogWrite(blue, 0);
          }
          if(s2==0x0D)
          {
            analogWrite(red, 255);
            analogWrite(green, 160);
            analogWrite(blue, 0);
          }
          if(s2==0x11)
          {
            analogWrite(red, 255);
            analogWrite(green, 255);
            analogWrite(blue, 0);
          }  
          /////////////////// green section///////////////////////
          if(s2==0x02)
          {
            analogWrite(red, 0);
            analogWrite(green, 255);
            analogWrite(blue, 0);
          }
          if(s2==0x06)
          {
            analogWrite(red, 0);
            analogWrite(green, 255);
            analogWrite(blue, 160);
          }
          if(s2==0x0A)
          {
            analogWrite(red, 0);
            analogWrite(green, 255);
            analogWrite(blue, 225);
          }
          if(s2==0x0E)
          {
            analogWrite(red, 0);
            analogWrite(green, 195);
            analogWrite(blue, 245);
          }
          if(s2==0x12)
          {
            analogWrite(red, 0);
            analogWrite(green, 175);
            analogWrite(blue, 255);
          }  
          ///////////////////blue section///////////////////////
          if(s2==0x03)
          {
            analogWrite(red, 0);
            analogWrite(green, 0);
            analogWrite(blue, 255);
          }
          if(s2==0x07)
          {
            analogWrite(red, 50);
            analogWrite(green, 0);
            analogWrite(blue, 255);
          }
          if(s2==0x0B)
          {
            analogWrite(red, 110);
            analogWrite(green, 0);
            analogWrite(blue, 255);
          }
          if(s2==0x0F)
          {
            analogWrite(red, 170);
            analogWrite(green, 0);
            analogWrite(blue, 255);
          }
          if(s2==0x13)
          {
            analogWrite(red, 230);
            analogWrite(green, 0);
            analogWrite(blue, 255);
          }  
          ///////////////////pure white///////////////////////
          if(s2==0x04)
          {
            analogWrite(red, 255);
            analogWrite(green, 255);
            analogWrite(blue, 255);
          }
           //////////////////// Flash (red, green, blue, white, purple, orange) ////////////////////////
          if(s2==0x08)  
          {
            flash=1;
          }
           //////////////////////////////// strobe (white fading) /////////////////////  
          if(s2==0x0C)  
          {
            stro=1;
          } 
           if(s2==0x10)  
          {
            fade=1;
          }
           if(s2==0x14)  
          {
            smooth=1;
          } 
          if(s2==0xff)
          {
            flash=0;
            stro=0;
            fade=0;
            smooth=0;
          }
       }
}

void loop()
{
int f1[7],L1[15];  // to read the state of colour selected in loop & faded mode
int binaryNumber[8]={0},binaryNumber1[8]={0},binaryNumber2[8]={0};
int c0=0,c1=0,c2=0,c3=0,c4=0,c5=0,c6=0,c7=0,c8=0,c9=0,c10=0,c11=0,c12=0,c13=0,c14=0;
int d0=0,d1=0,d2=0,d3=0,d4=0,d5=0,d6=0;
int codem,i=0,j=0,k=0,l=0,m=0,p=0,q=0,r=0,g1,g2,g3,g4,fadevalue1,fadevalue2;
int fl0,fl1,q0,q1,q2,q3,q4,q5,q6,fadevalue3;
int a=0,b=0,c=0,d=0,e=0,f=0,g=0,x1=0,y=0,w=0;
char incomingByte;
int finaldata[20],finaldata1[20],m1=0,m2=0,m3=0;

while(1)
{
  /////////////// to read IR state when system is turned on only ONCE
  if(r3==0)
  {
    remote();
    r3=1;      // to make sure controller does not enter this loop once again
  }
x4:
  if(flash==1)
  {
            g1++;
            
            if((g1>0)&&(g1<5001))
            {
            analogWrite(red, 255);
            analogWrite(green, 0);
            analogWrite(blue, 0);
            }
            
            if((g1>5000)&&(g1<10001))
            {
            analogWrite(red, 0);
            analogWrite(green, 255);
            analogWrite(blue, 0);
            }
            
            if((g1>10000)&&(g1<15001))
            {
            analogWrite(red, 0);
            analogWrite(green, 0);
            analogWrite(blue, 255);
            }
            
            if((g1>15000)&&(g1<20001))
            {
            analogWrite(red, 255);
            analogWrite(green, 255);
            analogWrite(blue, 255);
            }
            
            if((g1>20000)&&(g1<25001))
            {
            analogWrite(red, 230);
            analogWrite(green, 0);
            analogWrite(blue, 255);
            }
            
            if((g1>25000)&&(g1<30001))
            {
            analogWrite(red, 255);
            analogWrite(green, 255);
            analogWrite(blue, 0);
            }
            
            if(g1>30000)
            {
              g1=0;
            }
            
  }
  
  if(stro==1)
  {
    g2++;
    
    if((g2>0)&&(g2<8001))
    {
      fadevalue1=map(g2,1,8000,0,255);
      analogWrite(red, fadevalue1);
      analogWrite(green, fadevalue1);
      analogWrite(blue, fadevalue1);
    }            
    
    if((g2>8000)&&(g2<16001))
    {
      fadevalue1=map(g2,8001,16000,0,255);
      analogWrite(red, (255-fadevalue1));
      analogWrite(green, (255-fadevalue1));
      analogWrite(blue, (255-fadevalue1));
    }
    
    if(g2>16000)
    {
      g2=0;  
    }
  }
  
  if(fade==1)
  {
    g3++;
    
    if((g3>0)&&(g3<10001))
    {
      fadevalue2=map(g3,1,10000,0,255);
      analogWrite(red, (255-fadevalue2));
      analogWrite(green, fadevalue2);
      analogWrite(blue, 0);
    }
    
    if((g3>10000)&&(g3<20001))
    {
      fadevalue2=map(g3,10001,20000,0,255);
      analogWrite(red, 0);
      analogWrite(green, (255-fadevalue2));
      analogWrite(blue, fadevalue2);
    }
    
    if((g3>20000)&&(g3<30001))
    {
      fadevalue2=map(g3,20001,30000,0,255);
      analogWrite(red, fadevalue2);
      analogWrite(green, 0);
      analogWrite(blue, (255-fadevalue2));
    }
    
    if(g3>30000)
    {
      g3=0;
    }
  }
  
  if(smooth==1)
  {
            g4++;
            
            if((g4>0)&&(g4<3001))
            {
            analogWrite(red, 255);
            analogWrite(green, 0);
            analogWrite(blue, 0);
            }
            
            if((g4>3000)&&(g4<6001))
            {
            analogWrite(red, 0);
            analogWrite(green, 255);
            analogWrite(blue, 0);
            }
            
            if((g4>6000)&&(g4<9001))
            {
            analogWrite(red, 0);
            analogWrite(green, 0);
            analogWrite(blue, 255);
            }
            
            if(g4>9000)
            {
              g4=0;
            }
   }
y3:  
  while(Serial.available() > 0) 
  {
    l2:
    incomingByte = Serial.read();

    if(incomingByte=='\r')
    {
      i=0;
      if(finaldata1[3]!=4)
      {
//        Serial.println("");
        for(int z=0;z<6;z++) 
        {
//          Serial.print(finaldata1[z]);
//          Serial.print(',');
          EEPROM.write((z+25),finaldata1[z]);
        }
        EEPROM.write(3,0xff);
        flash=0;
        stro=0;
        fade=0;
        smooth=0;
        goto l1;
      }
      if(finaldata1[3]==4)
      {
        goto b2;
      }
   }
     
    codem= incomingByte;
    if(codem<0)
    {
      codem=codem+256;
    }
    
    if((codem!=13) && (codem!=10))
    {
      finaldata1[i++]=codem;
    }
  }
  
    while(0)
    {
      b2:
      EEPROM.write(28,4);

      for(int z9=0;z9<6;z9++) 
      {
        finaldata[z9]=finaldata1[z9];
      }
      flash=0;
      stro=0;
      fade=0;
      smooth=0;
      
      //Serial.println("");
      //Serial.print(m1);
      //Serial.print("     ");
      //Serial.print(finaldata[5]);
      
      if(m1==finaldata[5])
      {
        m2++;
      }
      else
      {
        m2=0;
      }
      
      if(m2>5)
      {
          analogWrite(red, 0);
          analogWrite(green, 0);
          analogWrite(blue, 0);
          m1=finaldata[5];
          m2=6;
          //digitalWrite(led,HIGH);
          goto y3;
      }
      
      //digitalWrite(led,LOW);
      m1=finaldata[5];
      //Serial.println(finaldata[5]);
        //////////////////////////////////// MUSIC ////////////////////////////////////////

        if((finaldata[0]==255)&&(finaldata[1]==0)&&(finaldata[2]==0)&&(m2<6))
        {
          analogWrite(red, finaldata[5]);
          analogWrite(green, 0);
          analogWrite(blue, 0);
          goto y3;
        }
        
        if((finaldata[0]==0)&&(finaldata[1]==255)&&(finaldata[2]==0)&&(m2<6))
        {
          analogWrite(red, 0);
          analogWrite(green, finaldata[5]);
          analogWrite(blue, 0);
          goto y3;
        }
        
        if((finaldata[0]==0)&&(finaldata[1]==0)&&(finaldata[2]==255)&&(m2<6))
        {
          analogWrite(red, 0);
          analogWrite(green, 0);
          analogWrite(blue, finaldata[5]);
          goto y3;
        }
        
        int x2=finaldata[4];
        x2=map(x2,21,35,10,255);    // setting sensitivity of music 
        x2=255-x2;
        
        //if(m2<11)
        if((finaldata[5]>x2)&&(m2<6))
        {
            if((finaldata[0]==255)&&(finaldata[1]==255)&&(finaldata[2]==255))
            {
              r++;
              if((r>0)&&(r<26))
              {
                analogWrite(red,255);
                analogWrite(green,0);
                analogWrite(blue,0);
              }
              
              if((r>25)&&(r<51))
              {
                analogWrite(red,0);
                analogWrite(green,255);
                analogWrite(blue,0);
              }
              
              if((r>50)&&(r<76))
              {
                analogWrite(red,0);
                analogWrite(green,0);
                analogWrite(blue,255);
              }
              
              if((r>75)&&(r<101))
              {
                analogWrite(red,255);
                analogWrite(green,255);
                analogWrite(blue,0);
              }
              
              if((r>100)&&(r<126))
              {
                analogWrite(red,255);
                analogWrite(green,0);
                analogWrite(blue,255);
              }
              
              if((r>125)&&(r<151))
              {
                analogWrite(red,255);
                analogWrite(green,255);
                analogWrite(blue,255);
              }
              
              if((r>150)&&(r<176))
              {
                analogWrite(red,255);
                analogWrite(green,30);
                analogWrite(blue,0);
              }
              
              if((r>175)&&(r<201))
              {
                analogWrite(red,255);
                analogWrite(green,0);
                analogWrite(blue,180);
              }
              
              if((r>200)&&(r<226))
              {
                analogWrite(red,230);
                analogWrite(green,0);
                analogWrite(blue,255);
              }
              
              if(r>225)
              {
                r=0;
              }
            }
            else
            {
              analogWrite(red, finaldata[0]);
              analogWrite(green, finaldata[1]);
              analogWrite(blue, finaldata[2]);
            }
          }
        else
        {
          analogWrite(red, 0);
          analogWrite(green, 0);
          analogWrite(blue, 0);
        }
      goto y3;
    }
  
l1:   
    for(int u3=0;u3<6;u3++)
    {
      finaldata[u3]=EEPROM.read(u3+25);
    }
    
    if(!((finaldata[3]==128)||(finaldata[3]==129)||(finaldata[3]==130)||(finaldata[3]==131)||(finaldata[3]==132)||(finaldata[3]==133)))
    {
      if(finaldata[3]==0)
      {
        analogWrite(red,finaldata[0]);
        analogWrite(green,finaldata[1]);
        analogWrite(blue,finaldata[2]);
      }

      if(finaldata[3]==200)
      {
      }
      /////////////////////////////////////////// FLASH ///////////////////////////////////////
      if(finaldata[3]==5)  
      {
        x1=finaldata[4];
        y=finaldata[5];
        if(x1>19)
        {
          x1=x1-20;
        }
        x1=x1*10;
        y=y*10;
      }
      
      if(finaldata[3]==5)
      {
        analogWrite(red,finaldata[0]);
        analogWrite(green,finaldata[1]);
        analogWrite(blue,finaldata[2]);
        delay(x1);
        
        analogWrite(red,0);
        analogWrite(green,0);
        analogWrite(blue,0);
        delay(y);
      }
      
      if(finaldata[3]==1)
      {
        if(finaldata[4]==21)
        {
          g=2000;
        }
        if(finaldata[4]==22)
        {
          g=4000;
        }
        if(finaldata[4]==23)
        {
          g=6000;
        }
        if(finaldata[4]==24)
        {
          g=8000;
        }
        if(finaldata[4]==25)
        {
          g=10000;
        }
        if(finaldata[4]==26)
        {
          g=12000;
        }
        if(finaldata[4]==27)
        {
          g=14000;
        }
        if(finaldata[4]==28)
        {
          g=16000;
        }
        if(finaldata[4]==29)
        {
          g=18000;
        }
        if(finaldata[4]==30)
        {
          g=20000;
        }
        if(finaldata[4]==31)
        {
          g=22000;
        }
        if(finaldata[4]==32)
        {
          g=24000;
        }
        if(finaldata[4]==33)
        {
          g=26000;
        }
        if(finaldata[4]==34)
        {
          g=28000;
        }
        if(finaldata[4]==35)
        {
          g=30000;
        }
        
        for(q0=0;q0<g;q0++)
        {
          if(Serial.available() > 0)
          goto l2;
          if (irrecv.decode(&results))
          {
            dump(&results);
            irrecv.resume(); // Receive the next value
            if(a1==1)
            {
              goto x4;
            }
          }
          analogWrite(red,finaldata[0]);
          analogWrite(green,finaldata[1]);
          analogWrite(blue,finaldata[2]);
          delayMicroseconds(10);
        }
        
        for(q0=0;q0<g;q0++)
        {
          if(Serial.available() > 0)
          goto l2;
          if (irrecv.decode(&results))
          {
            dump(&results);
            irrecv.resume(); // Receive the next value
            if(a1==1)
            {
              goto x4;
            }
          }
          analogWrite(red,0);
          analogWrite(green,0);
          analogWrite(blue,0);
          delayMicroseconds(10);
        }
      }
      ///////////////////////////////////////////////// LOOP //////////////////////////////////////////////
      if(finaldata[3]==6)
      {
        x1=finaldata[4];
        y=finaldata[5];
        
        if((x1>19)&&(x1<256))
        {
          x1=x1-20;
        }
        else
        {
          x1=x1+236;
        }
      }
      
      if(finaldata[3]==6)  
      {
        while(x1!=0)
	{
          binaryNumber[j++]= (x1)%2;			
          x1 = x1/2;
	}
		
	if(binaryNumber[0]==1)
	{
          c0=1;
        }
	else
	{
          c0=0;
        }
		
	if(binaryNumber[1]==1)
	{
          c1=1;
	}
	else
	{
          c1=0;
	}

	if(binaryNumber[2]==1)
	{
          c2=1;
	}
	else
	{
          c2=0;
	}
		
	if(binaryNumber[3]==1)
	{
          c3=1;
	}
	else
	{
          c3=0;
	}
		
	if(binaryNumber[4]==1)
	{
          c4=1;
	}
	else
	{
          c4=0;
	}
		
	if(binaryNumber[5]==1)
	{
          c5=1;
	}
	else
	{
          c5=0;
	}
		
	if(binaryNumber[6]==1)
	{
          c6=1;
	}
	else
	{
          c6=0;
	}
		
	if(binaryNumber[7]==1)
	{
          c7=1;
	}
	else
	{
          c7=0;
	}
	
        ///////////////////// writing colour state into EEPROM ///////////////////////
        EEPROM.write(38,c0);
        EEPROM.write(39,c1);
        EEPROM.write(40,c2);
        EEPROM.write(41,c3);
        EEPROM.write(42,c4);
        EEPROM.write(43,c5);
        EEPROM.write(44,c6);
        EEPROM.write(45,c7);
        	
	for(k=0;k<8;k++)
	{
	  binaryNumber[k]=0;
	}
        j=0;
        /////////////////////////////////////////////////////////////////////////////////////////
        
        while(y!=0)
	{
          binaryNumber1[l++]= y%2;			
          y = y/2;
	}
		
	if(binaryNumber1[0]==1)
	{
          c8=1;
	}
	else
	{
          c8=0;
	}
		
	if(binaryNumber1[1]==1)
	{
          c9=1;
	}
	else
	{
          c9=0;
	}

	if(binaryNumber1[2]==1)
	{
          c10=1;
	}
	else
	{
          c10=0;
	}
		
	if(binaryNumber1[3]==1)
	{
          c11=1;
	}
	else
	{
          c11=0;
	}
		
	if(binaryNumber1[4]==1)
	{
          c12=1;
	}
	else
	{
          c12=0;
	}
		
	if(binaryNumber1[5]==1)
	{
          c13=1;
	}
	else
	{
          c13=0;
	}
		
	if(binaryNumber1[6]==1)
	{
          c14=1;
	}
	else
	{
          c14=0;
	}
	
        ///////////////////// writing colour state into EEPROM ///////////////////////
        EEPROM.write(46,c8);
        EEPROM.write(47,c9);
        EEPROM.write(48,c10);
        EEPROM.write(49,c11);
        EEPROM.write(50,c12);
        EEPROM.write(51,c13);
        EEPROM.write(52,c14);
        	
	for(m=0;m<8;m++)
	{
	  binaryNumber1[m]=0;
	}
        l=0;
      }
      
      if(finaldata[3]==2)  
      {
        if(finaldata[4]==21)
        {
          g=2000;
        }
        if(finaldata[4]==22)
        {
          g=4000;
        }
        if(finaldata[4]==23)
        {
          g=6000;
        }
        if(finaldata[4]==24)
        {
          g=8000;
        }
        if(finaldata[4]==25)
        {
          g=10000;
        }
        if(finaldata[4]==26)
        {
          g=12000;
        }
        if(finaldata[4]==27)
        {
          g=14000;
        }
        if(finaldata[4]==28)
        {
          g=16000;
        }
        if(finaldata[4]==29)
        {
          g=18000;
        }
        if(finaldata[4]==30)
        {
          g=20000;
        }
        if(finaldata[4]==31)
        {
          g=22000;
        }
        if(finaldata[4]==32)
        {
          g=24000;
        }
        if(finaldata[4]==33)
        {
          g=26000;
        }
        if(finaldata[4]==34)
        {
          g=28000;
        }
        if(finaldata[4]==35)
        {
          g=30000;
        }
        
        for(int z2=0;z2<15;z2++)
        {
          L1[z2]=EEPROM.read(z2+38);
        }
        
        if(L1[0])
        {
          for(q0=0;q0<g;q0++)
          {
            if(Serial.available() > 0)
            goto l2;
            if (irrecv.decode(&results))
            {
              dump(&results);
              irrecv.resume(); // Receive the next value
              if(a1==1)
              {
                goto x4;
              }
            }
            analogWrite(red,255);
            analogWrite(green,0);
            analogWrite(blue,0);
            delayMicroseconds(10);
          } 
        }
        
        if(L1[1])
        {
          for(q0=0;q0<g;q0++)
          {
            if(Serial.available() > 0)
            goto l2;
            if (irrecv.decode(&results))
            {
              dump(&results);
              irrecv.resume(); // Receive the next value
              if(a1==1)
              {
                goto x4;
              }
            }
            analogWrite(red,0);
            analogWrite(green,255);
            analogWrite(blue,0);
            delayMicroseconds(10);
          } 
        }
        
        if(L1[2])
        {
          for(q0=0;q0<g;q0++)
          {
            if(Serial.available() > 0)
            goto l2;
            if (irrecv.decode(&results))
            {
              dump(&results);
              irrecv.resume(); // Receive the next value
              if(a1==1)
              {
                goto x4;
              }
            }
            analogWrite(red,0);
            analogWrite(green,0);
            analogWrite(blue,255);
            delayMicroseconds(10);
          } 
        }
        
        if(L1[3])
        {
          for(q0=0;q0<g;q0++)
          {
            if(Serial.available() > 0)
            goto l2;
            if (irrecv.decode(&results))
            {
              dump(&results);
              irrecv.resume(); // Receive the next value
              if(a1==1)
              {
                goto x4;
              }
            }
            analogWrite(red,255);
            analogWrite(green,255);
            analogWrite(blue,0);
            delayMicroseconds(10);
          } 
        }
        
        if(L1[4])
        {
          for(q0=0;q0<g;q0++)
          {
            if(Serial.available() > 0)
            goto l2;
            if (irrecv.decode(&results))
            {
              dump(&results);
              irrecv.resume(); // Receive the next value
              if(a1==1)
              {
                goto x4;
              }
            }
            analogWrite(red,255);
            analogWrite(green,0);
            analogWrite(blue,255);
            delayMicroseconds(10);
          } 
        }
        
        if(L1[5])
        {
          for(q0=0;q0<g;q0++)
          {
            if(Serial.available() > 0)
            goto l2;
            if (irrecv.decode(&results))
            {
              dump(&results);
              irrecv.resume(); // Receive the next value
              if(a1==1)
              {
                goto x4;
              }
            }
            analogWrite(red,0);
            analogWrite(green,255);
            analogWrite(blue,255);
            delayMicroseconds(10);
          } 
        }
        
        if(L1[6])
        {
          for(q0=0;q0<g;q0++)
          {
            if(Serial.available() > 0)
            goto l2;
            if (irrecv.decode(&results))
            {
              dump(&results);
              irrecv.resume(); // Receive the next value
              if(a1==1)
              {
                goto x4;
              }
            }
            analogWrite(red,255);
            analogWrite(green,255);
            analogWrite(blue,255);
            delayMicroseconds(10);
          } 
        }
        
        if(L1[7])
        {
          for(q0=0;q0<g;q0++)
          {
            if(Serial.available() > 0)
            goto l2;
            if (irrecv.decode(&results))
            {
              dump(&results);
              irrecv.resume(); // Receive the next value
              if(a1==1)
              {
                goto x4;
              }
            }
            analogWrite(red,50);
            analogWrite(green,0);
            analogWrite(blue,255);
            delayMicroseconds(10);
          } 
        }
        
        if(L1[8])
        {
          for(q0=0;q0<g;q0++)
          {
            if(Serial.available() > 0)
            goto l2;
            if (irrecv.decode(&results))
            {
              dump(&results);
              irrecv.resume(); // Receive the next value
              if(a1==1)
              {
                goto x4;
              }
            }
            analogWrite(red,0);
            analogWrite(green,255);
            analogWrite(blue,160);
            delayMicroseconds(10);
          } 
        }
        
        if(L1[9])
        {
          for(q0=0;q0<g;q0++)
          {
            if(Serial.available() > 0)
            goto l2;
            if (irrecv.decode(&results))
            {
              dump(&results);
              irrecv.resume(); // Receive the next value
              if(a1==1)
              {
                goto x4;
              }
            }
            analogWrite(red,255);
            analogWrite(green,30);
            analogWrite(blue,0);
            delayMicroseconds(10);
          } 
        }
        
        if(L1[10])
        {
          for(q0=0;q0<g;q0++)
          {
            if(Serial.available() > 0)
            goto l2;
            if (irrecv.decode(&results))
            {
              dump(&results);
              irrecv.resume(); // Receive the next value
              if(a1==1)
              {
                goto x4;
              }
            }
            analogWrite(red,255);
            analogWrite(green,107);
            analogWrite(blue,0);
            delayMicroseconds(10);
          } 
        }
        
        if(L1[11])
        {
          for(q0=0;q0<g;q0++)
          {
            if(Serial.available() > 0)
            goto l2;
            if (irrecv.decode(&results))
            {
              dump(&results);
              irrecv.resume(); // Receive the next value
              if(a1==1)
              {
                goto x4;
              }
            }
            analogWrite(red,155);
            analogWrite(green,0);
            analogWrite(blue,0);
            delayMicroseconds(10);
          } 
        }
        
        if(L1[12])
        {
          for(q0=0;q0<g;q0++)
          {
            if(Serial.available() > 0)
            goto l2;
            if (irrecv.decode(&results))
            {
              dump(&results);
              irrecv.resume(); // Receive the next value
              if(a1==1)
              {
                goto x4;
              }
            }
            analogWrite(red,255);
            analogWrite(green,0);
            analogWrite(blue,180);
            delayMicroseconds(10);
          } 
        }
        
        if(L1[13])
        {
          for(q0=0;q0<g;q0++)
          {
            if(Serial.available() > 0)
            goto l2;
            if (irrecv.decode(&results))
            {
              dump(&results);
              irrecv.resume(); // Receive the next value
              if(a1==1)
              {
                goto x4;
              }
            }
            analogWrite(red,170);
            analogWrite(green,0);
            analogWrite(blue,255);
            delayMicroseconds(10);
          } 
        }
        
        if(L1[14])
        {
          for(q0=0;q0<g;q0++)
          {
            if(Serial.available() > 0)
            goto l2;
            if (irrecv.decode(&results))
            {
              dump(&results);
              irrecv.resume(); // Receive the next value
              if(a1==1)
              {
                goto x4;
              }
            }
            analogWrite(red,230);
            analogWrite(green,0);
            analogWrite(blue,255);
            delayMicroseconds(10);
          } 
        }
      }
      ////////////////////////////////////////////  FADE  ///////////////////////////////////////////
      if(finaldata[3]==7)
      {
        x1=finaldata[4];
        x1=x1-20;
      }
      
      if(finaldata[3]==7)  
      {
        while(x1!=0)
	{
          binaryNumber2[q++]= x1%2;			
          x1 = x1/2;
	}
		
	if(binaryNumber2[0]==1)
	{
          d0=1;
        }
	else
	{
          d0=0;
	}
		
	if(binaryNumber2[1]==1)
	{
          d1=1;
	}
	else
	{
          d1=0;
	}

	if(binaryNumber2[2]==1)
	{
          d2=1;
	}
	else
	{
          d2=0;
	}
		
	if(binaryNumber2[3]==1)
	{
          d3=1;
	}
	else
	{
          d3=0;
	}
		
	if(binaryNumber2[4]==1)
	{
          d4=1;
	}
	else
	{
          d4=0;
	}
		
	if(binaryNumber2[5]==1)
	{
          d5=1;
	}
	else
	{
          d5=0;
	}
		
	if(binaryNumber2[6]==1)
	{
          d6=1;
	}
	else
	{
          d6=0;
	}
        
        ///////////////////// writing colour state into EEPROM ///////////////////////
        EEPROM.write(31,d0);
        EEPROM.write(32,d1);
        EEPROM.write(33,d2);
        EEPROM.write(34,d3);
        EEPROM.write(35,d4);
        EEPROM.write(36,d5);
        EEPROM.write(37,d6);
      }	
      
      for(p=0;p<8;p++)
      {
        binaryNumber2[p]=0;
      }
      q=0;
        
      if(finaldata[3]==3)
      {
        if(finaldata[4]==21)
        {
          g=2000;
        }
        if(finaldata[4]==22)
        {
          g=4000;
        }
        if(finaldata[4]==23)
        {
          g=6000;
        }
        if(finaldata[4]==24)
        {
          g=8000;
        }
        if(finaldata[4]==25)
        {
          g=10000;
        }
        if(finaldata[4]==26)
        {
          g=12000;
        }
        if(finaldata[4]==27)
        {
          g=14000;
        }
        if(finaldata[4]==28)
        {
          g=16000;
        }
        if(finaldata[4]==29)
        {
          g=18000;
        }
        if(finaldata[4]==30)
        {
          g=20000;
        }
        if(finaldata[4]==31)
        {
          g=22000;
        }
        if(finaldata[4]==32)
        {
          g=24000;
        }
        if(finaldata[4]==33)
        {
          g=26000;
        }
        if(finaldata[4]==34)
        {
          g=28000;
        }
        if(finaldata[4]==35)
        {
          g=30000;
        }
        
        for(int z1=0;z1<7;z1++)
        {
          f1[z1]=EEPROM.read(z1+31);
        }
        
        if(f1[0])
        {
          for(q0=0;q0<g;q0++)
          {
            fadevalue3=map(q0,1,g,0,255);
            if(Serial.available() > 0)
            goto l2;
            if (irrecv.decode(&results))
            {
              dump(&results);
              irrecv.resume(); // Receive the next value
              if(a1==1)
              {
                goto x4;
              }
            }
            analogWrite(red, fadevalue3);
            analogWrite(green, 0);
            analogWrite(blue, 0);
            delayMicroseconds(20);
          }
          
          for(q0=0;q0<g;q0++)
          {
            fadevalue3=map(q0,1,g,0,255);
            if(Serial.available() > 0)
            goto l2;
            if (irrecv.decode(&results))
            {
              dump(&results);
              irrecv.resume(); // Receive the next value
              if(a1==1)
              {
                goto x4;
              }
            }
            analogWrite(red, (255-fadevalue3));
            analogWrite(green, 0);
            analogWrite(blue, 0);
            delayMicroseconds(20);
          }
        }
        
        if(f1[1])
        {
          for(q0=0;q0<g;q0++)
          {
            fadevalue3=map(q0,1,g,0,255);
            if(Serial.available() > 0)
            goto l2;
            if (irrecv.decode(&results))
            {
              dump(&results);
              irrecv.resume(); // Receive the next value
              if(a1==1)
              {
                goto x4;
              }
            }
            analogWrite(red, 0);
            analogWrite(green, fadevalue3);
            analogWrite(blue, 0);
            delayMicroseconds(20);
          }
          
          for(q0=0;q0<g;q0++)
          {
            fadevalue3=map(q0,1,g,0,255);
            if(Serial.available() > 0)
            goto l2;
            if (irrecv.decode(&results))
            {
              dump(&results);
              irrecv.resume(); // Receive the next value
              if(a1==1)
              {
                goto x4;
              }
            }
            analogWrite(red, 0);
            analogWrite(green, (255-fadevalue3));
            analogWrite(blue, 0);
            delayMicroseconds(20);
          }
        }
        
        if(f1[2])
        {
          for(q0=0;q0<g;q0++)
          {
            fadevalue3=map(q0,1,g,0,255);
            if(Serial.available() > 0)
            goto l2;
            if (irrecv.decode(&results))
            {
              dump(&results);
              irrecv.resume(); // Receive the next value
              if(a1==1)
              {
                goto x4;
              }
            }
            analogWrite(red, 0);
            analogWrite(green, 0);
            analogWrite(blue, fadevalue3);
            delayMicroseconds(20);
          }
          
          for(q0=0;q0<g;q0++)
          {
            fadevalue3=map(q0,1,g,0,255);
            if(Serial.available() > 0)
            goto l2;
            if (irrecv.decode(&results))
            {
              dump(&results);
              irrecv.resume(); // Receive the next value
              if(a1==1)
              {
                goto x4;
              }
            }
            analogWrite(red, 0);
            analogWrite(green, 0);
            analogWrite(blue, (255-fadevalue3));
            delayMicroseconds(20);
          }
        }
        
        if(f1[3])
        {
          for(q0=0;q0<g;q0++)
          {
            fadevalue3=map(q0,1,g,0,255);
            if(Serial.available() > 0)
            goto l2;
            if (irrecv.decode(&results))
            {
              dump(&results);
              irrecv.resume(); // Receive the next value
              if(a1==1)
              {
                goto x4;
              }
            }
            analogWrite(red, fadevalue3);
            analogWrite(green, fadevalue3);
            analogWrite(blue, 0);
            delayMicroseconds(20);
          }
          
          for(q0=0;q0<g;q0++)
          {
            fadevalue3=map(q0,1,g,0,255);
            if(Serial.available() > 0)
            goto l2;
            if (irrecv.decode(&results))
            {
              dump(&results);
              irrecv.resume(); // Receive the next value
              if(a1==1)
              {
                goto x4;
              }
            }
            analogWrite(red, (255-fadevalue3));
            analogWrite(green, (255-fadevalue3));
            analogWrite(blue, 0);
            delayMicroseconds(20);
          }
        }
        
        if(f1[4])
        {
          for(q0=0;q0<g;q0++)
          {
            fadevalue3=map(q0,1,g,0,255);
            if(Serial.available() > 0)
            goto l2;
            if (irrecv.decode(&results))
            {
              dump(&results);
              irrecv.resume(); // Receive the next value
              if(a1==1)
              {
                goto x4;
              }
            }
            analogWrite(red, fadevalue3);
            analogWrite(green, 0);
            analogWrite(blue, fadevalue3);
            delayMicroseconds(20);
          }
          
          for(q0=0;q0<g;q0++)
          {
            fadevalue3=map(q0,1,g,0,255);
            if(Serial.available() > 0)
            goto l2;
            if (irrecv.decode(&results))
            {
              dump(&results);
              irrecv.resume(); // Receive the next value
              if(a1==1)
              {
                goto x4;
              }
            }
            analogWrite(red, (255-fadevalue3));
            analogWrite(green, 0);
            analogWrite(blue, (255-fadevalue3));
            delayMicroseconds(20);
          }
        }
        
        if(f1[5])
        {
          for(q0=0;q0<g;q0++)
          {
            fadevalue3=map(q0,1,g,0,255);
            if(Serial.available() > 0)
            goto l2;
            if (irrecv.decode(&results))
            {
              dump(&results);
              irrecv.resume(); // Receive the next value
              if(a1==1)
              {
                goto x4;
              }
            }
            analogWrite(red, 0);
            analogWrite(green, fadevalue3);
            analogWrite(blue, fadevalue3);
            delayMicroseconds(20);
          }
          
          for(q0=0;q0<g;q0++)
          {
            fadevalue3=map(q0,1,g,0,255);
            if(Serial.available() > 0)
            goto l2;
            if (irrecv.decode(&results))
            {
              dump(&results);
              irrecv.resume(); // Receive the next value
              if(a1==1)
              {
                goto x4;
              }
            }
            analogWrite(red, 0);
            analogWrite(green, (255-fadevalue3));
            analogWrite(blue, (255-fadevalue3));
            delayMicroseconds(20);
          }
        }
        
        if(f1[6])
        {
          for(q0=0;q0<g;q0++)
          {
            fadevalue3=map(q0,1,g,0,255);
            if(Serial.available() > 0)
            goto l2;
            if (irrecv.decode(&results))
            {
              dump(&results);
              irrecv.resume(); // Receive the next value
              if(a1==1)
              {
                goto x4;
              }
            }
            analogWrite(red, fadevalue3);
            analogWrite(green, fadevalue3);
            analogWrite(blue, fadevalue3);
            delayMicroseconds(20);
          }
          
          for(q0=0;q0<g;q0++)
          {
            fadevalue3=map(q0,1,g,0,255);
            if(Serial.available() > 0)
            goto l2;
            if (irrecv.decode(&results))
            {
              dump(&results);
              irrecv.resume(); // Receive the next value
              if(a1==1)
              {
                goto x4;
              }
            }
            analogWrite(red, (255-fadevalue3));
            analogWrite(green, (255-fadevalue3));
            analogWrite(blue, (255-fadevalue3));
            delayMicroseconds(20);
          }
        }
      }
    }
    else    // if bluetooth is off then switch off the colours
    {
      analogWrite(red, 0);
      analogWrite(green, 0);
      analogWrite(blue, 0);
    }
    
  if (irrecv.decode(&results))
  {
    dump(&results);
    irrecv.resume();
  }
}
}
