
/*
// /////////////////////////////////////////////////////////////////////// COPYRIGHT NOTICE
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with Pip-Project.  If not, see <http://www.gnu.org/licenses/>.
// /////////////////////////////////////////////////////////////////////// COPYRIGHT NOTICE
// /////////////////////////////////////////////////////////////////////// VERSION CONTROL
// PAGE CREATED BY: Phillip Kraguljac
// PAGE CREATED DATE: 2019-07-20
// DATE       || NAME           || MODIFICATION
// 2019-10-24   || Phillip Kraguljac    || Created.
// /////////////////////////////////////////////////////////////////////// VERSION CONTROL
*/

int counter = 0;
volatile int Main_Measurement = 0;
volatile bool Step_Recorded = false;
bool Rotating_Forward = true;
int Encoder_A_Terminal = 2; 
int Encoder_B_Terminal = 3;


volatile byte Encoder_A_Value = 0;
volatile byte Encoder_B_Value = 0;
volatile byte Encoder_A_Value_Memory = 0;
volatile byte Encoder_B_Value_Memory = 0;


void setup() {

Serial.begin (9600);
pinMode(Encoder_A_Terminal, INPUT);                                                  // Declare IO's.
pinMode(Encoder_B_Terminal, INPUT);                                                  // Declare IO's.
//pinMode(Encoder_2A_Terminal, INPUT_PULLUP);                                                  // Declare IO's.
//pinMode(Encoder_2B_Terminal, INPUT);                                                  // Declare IO's.

//attachInterrupt(digitalPinToInterrupt(Encoder_A_Terminal), Input_Change_Detected, CHANGE); //Interrupt trigger mode: RISING
attachInterrupt(digitalPinToInterrupt(Encoder_B_Terminal), Input_Change_Detected, CHANGE); //Interrupt trigger mode: RISING
}

void loop() {
  
counter++;
Serial.print(String(counter)+" - ");
Serial.print("A:"+String(Encoder_A_Value_Memory)+" - ");
Serial.print("B:"+String(Encoder_B_Value_Memory)+" - ");
Serial.print("D:"+String(Rotating_Forward)+" - ");
Serial.print("S:"+String(Step_Recorded)+" - ");
Serial.println("M:"+String(Main_Measurement));

//delay(100);

}









void Input_Change_Detected(){
Encoder_A_Value = digitalRead(Encoder_A_Terminal);
Encoder_B_Value = digitalRead(Encoder_B_Terminal);
Determine_Direction();
Encoder_A_Value_Memory = Encoder_A_Value;
Encoder_B_Value_Memory = Encoder_B_Value;




}


void Determine_Direction(){
if(Step_Recorded==false){
if(Encoder_A_Value_Memory==0&&Encoder_B_Value_Memory==0){  
if(Encoder_A_Value==1){Rotating_Forward=true; Main_Measurement++; Step_Recorded=true;}
if(Encoder_B_Value==1){Rotating_Forward=false; Main_Measurement--; Step_Recorded=true;}
}
}
if(Encoder_A_Value_Memory==0&&Encoder_B_Value_Memory==0){
Step_Recorded = false;
}  
}
