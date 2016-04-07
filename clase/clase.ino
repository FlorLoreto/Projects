#include <TimeAlarms.h>
#include <Time.h>
class Alarma {
  //Atributos https://processing.org/tutorials/objects/

private: int alarmHora;
 //Metodos
  //getters

public: int getAlarmHora(){return alarmHora; } 

  //setters
   
  public: void setAlarmHora (int aH){
    alarmHora=aH;} 
   
   //constructor
    public: Alarma(int aH){
       alarmHora=aH;
       }
     
      public: Alarma(){
      
      alarmHora=0;
            }   
    void suena(){
        pinMode(13, OUTPUT);
        digitalWrite(13, HIGH);
        delay(2000);
        digitalWrite(13, LOW);
        delay(2250);
        }
    };
    Alarma Alarma1(0);
    

void setup(){
  while(!Serial);
  setTime (12,0,0,day(),month(),year());
  Serial.begin(9600);
   }
void loop(){Alarm.alarmRepeat(12,0,1, Morning);
 // Alarma1.suena();
 int t=second();
 Serial.printf("hora %d:%d:%d\n",hour(),minute(),t);
  }
 void Morning(){
 // Alarma1.suena();
  Serial.println("paso por aqui");
  Serial.println("paso por aqui");
  Serial.println("paso por aqui");
  Serial.println("paso por aqui");
  Serial.println("paso por aqui");
  /*pinMode(13, OUTPUT);
        digitalWrite(13, HIGH);
        delay(2000);
        digitalWrite(13, LOW);
        delay(2250);*/
        }

