
String input = "";
char c;
String instruct = "";
void setup(){
  Serial.begin(9600);
  }

void loop()
   {
     
     instruct=getEntry();
     if (instruct.length()>1){
       Serial.print("Eureka ");Serial.println(instruct); 
      } 
}
 
 
 String getEntry(){String salida="";
  // Read any serial input
     while (Serial.available() > 0)
     {Serial.print("input1 ");Serial.println(input); c=(char) Serial.read();
        input =input+c; // Read in one char at a time
         delay(5); // Delay for 5 ms so the next char has time to be received
        Serial.print("inputilloagregado ");Serial.println(input); 
        Serial.print("longitud ");Serial.println(input.length()); 
        Serial.print("último character ");Serial.println(input[input.length()-1]); 
  if (input[input.length()-1]=='/'){
  salida=input.substring(0,input.length()-1);
  Serial.print("inputanésimo ");Serial.println(salida);
  input=""; }            
 }return salida;  
  }


