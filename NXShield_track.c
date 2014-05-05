//arduino
#include <Wire.h>
#include <NXShield.h>
#include <LightSensorArray.h>
#include "Timer.h"
NXShield    nxshield;
LightSensorArray lsa (0x14);
 uint8_t *cal;         //declare "cal" pointer
void setup()
{
	  char str[256];
	  Serial.begin(115200); 
	  delay(500); 
	  nxshield.init( SH_SoftwareI2C );
	  nxshield.waitForButtonPress(BTN_GO);
	  lsa.init( &nxshield, SH_BBS1 );
	  nxshield.bank_a.motorReset();
	  nxshield.bank_b.motorReset();
}

void loop()
{
	  byte rr,ll,ff;
	  char aa[80];
	  char str[256];        //declare character string length     
	  int  i;               //declare integer "i"
	  byte midVal;
	  byte TotalVal;
	  boolean tempStr[8];  
	  byte SpeedVal,Max,Min;
	  int temp;
	  rr=0;ll=0;ff=0;
	  cal = lsa.getCalibrated();
	  temp=0;
	  Max = 0;  
	  Min = 255; 
	  for (i=0; i< 8; i++){
		  if(cal[i]>Max) Max = cal[i]; 
		  if(cal[i]<Min) Min = cal[i]; 
		  sprintf (str, "Value: %d = %d", i, cal[i]); 
		  Serial.println(str);
	  }
	  midVal = (Max + Min)/2;
	  midVal =  midVal - midVal/4; 
	  TotalVal=0;
	  for (i=0; i<= 3; i++){
		 if (cal[i]>midVal) {
			 tempStr[i] =0;                  
		 }
		 else {
			 tempStr[i] =1;  
			 TotalVal=TotalVal+ pow(2, i);       
		 }
		 Serial.print(tempStr[i]);
			 if (tempStr[i] == 1){
			rr=rr+tempStr[i];
		}else{
		 
		}
	  }
	  Serial.println('\0'); 
		   Serial.print(rr); 
	  Serial.println('\0'); 
		for (i=4; i<=7; i++){
		 if (cal[i]>midVal) {
			 tempStr[i] =0;                  
		 }
		 else {
			 tempStr[i] =1;  
			 TotalVal=TotalVal+ pow(2, i);       
		 }
		 Serial.print(tempStr[i]);
		 if (tempStr[i] == 1){
				 ll=ll+tempStr[i];
		}else{

		}
		
		 }
		 Serial.println('\0'); 
			  Serial.print(ll);
		  if (ll>rr){  
		ff=ll-rr;
	}else{
	  ff=rr-ll;
	}
    Serial.println('\0'); 
          Serial.print(ff);   
                     SpeedVal=100; 
        if ((ll==2 && rr==3) || (rr==2 && ll==3) ){
                nxshield.bank_b.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward,SpeedVal+20);
                nxshield.bank_b.motorRunUnlimited(SH_Motor_2, SH_Direction_Forward,SpeedVal+20); 
            }else if (ll==4 && rr==1){
                nxshield.bank_b.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward,SpeedVal-40);
                nxshield.bank_b.motorRunUnlimited(SH_Motor_2, SH_Direction_Forward,SpeedVal-80); 
            }else if (rr==4 && ll==1){
                nxshield.bank_b.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward,SpeedVal-80);
                nxshield.bank_b.motorRunUnlimited(SH_Motor_2, SH_Direction_Forward,SpeedVal-40);          
            }else if(rr==0 && ll==4){
               nxshield.bank_b.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward,SpeedVal-50);
                nxshield.bank_b.motorRunUnlimited(SH_Motor_2, SH_Direction_Forward,SpeedVal-100);          
            }else if(ll==0 && rr==4){
             nxshield.bank_b.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward,SpeedVal-100);
                nxshield.bank_b.motorRunUnlimited(SH_Motor_2, SH_Direction_Forward,SpeedVal-50);          
            }
}
