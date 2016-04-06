//=====================================  Funcion que actualiza los ajustes ===========================================
  void setTiempo(){
  switch (primerNumero) {
    case 1 :
      Serial.print ("Es esta la fecha? :"); Serial.print (instruct.substring(1, 2)); Serial.print ("/");
      Serial.print (instruct.substring(3, 4)); Serial.print ("/"); Serial.println (instruct.substring(5, 8));
      Serial.println("teclee si o no seguido de /");
      DD = instruct.substring(1, 2);
           MM = instruct.substring(3, 4);
                AAAA = instruct.substring(5, 8);

      break;
    case 2 :
      Serial.print ("Es esta la hora? :"); Serial.print (instruct.substring(1, 2)); Serial.print (":");
      Serial.print (instruct.substring(3, 4)); Serial.print (":"); Serial.println (instruct.substring(5, 6));
      Serial.println("teclee si o no seguido de /");
      HH = instruct.substring(1, 2);
           MIN = instruct.substring(3, 4);
                 SEG = instruct.substring(5, 8);
      break;
    case 3 :
      Serial.print ("Es esta la hora de la lalarma ? :"); Serial.print (instruct.substring(1, 2)); Serial.print (":");
      Serial.println (instruct.substring(3, 4));
      Serial.println("teclee si o no seguido de /");
       hh = instruct.substring(1, 2)
       mm = instruct.substring(3, 4)
            break;
default : /* Optional */
  Serial.println ("Error; ha incluido un numero distinto de 1 , 2 o 3");
  break;
}
}
