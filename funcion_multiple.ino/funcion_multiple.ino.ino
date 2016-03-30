//Este sketch ejempliica el uso de una función que devuelve argumentos múltiples 
double array[5];
//En el setup activamos Serial y llenamos el array
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  int i;
  for (i = 0; i < 5; i = i + 1) {
    array[i] = i + 1;
    Serial.println(array[i]);
  }
  Serial.print("tamanyo double:"); Serial.println(sizeof(array)/sizeof(double));
}

//La funcion Averages devuelve dos medias: la geométrica y la aritmética
void loop() {
  // put your main code here, to run repeatedly:
   double mediarit;
   double mediageo;
   Averages(5, array,&mediarit, &mediageo);// Function call con las direcciones - &var -donde se almacenarán los valores de las medias
  Serial.print("media aritmetica ");Serial.println(mediarit);//imprimo las variables
  Serial.print("media geometrica ");Serial.println(mediageo);
  //imprimo las direcciones
  Serial.printf("&media aritmetica :%u\n", &mediarit);//imprimo las variables
  Serial.printf("&media geometrica :%u\n",&mediageo);
  delay (5000);
    
  //.printf("Por pointersDobles 1: AVG %u",*p);
  //Serial.printf("\t; 2: AVGGEOM %d \n",*(p+1));
  delay (5000);
}

//Una sola función retorna dos argumentos: pointer al primero de ellos
void Averages(int size,double arr[],double *avg, double *avggeo){
double suma=0;
double prod=1;
for (int i=0;i<size;++i){
        suma =suma+arr[i];
        prod = prod*arr[i];
       Serial.print("producto: ");Serial.println( prod);

 }
 double AVG=suma/size;
Serial.printf("media aritmetica :\t");Serial.println( AVG);
 double expo=1./size;
 double AVGGEO=pow(prod,expo);
Serial.print("pow :\t");Serial.println(AVGGEO);
Serial.printf("media geometrica :\t");Serial.println( AVGGEO);
 *avg=AVG;
 *avggeo=AVGGEO;
 }


