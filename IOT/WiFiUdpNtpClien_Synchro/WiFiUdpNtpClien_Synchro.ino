/*

  Udp NTP Client

  Get the time from a Network Time Protocol (NTP) time server
  Demonstrates use of UDP sendPacket and ReceivePacket
  It adjusts UTC time to DST in Central Europe Time

*/


#include <TimeAlarms.h>
#include <Time.h>
#include <StopWatch.h>
#include <SPI.h>
#include <WiFi101.h>
#include <WiFiUdp.h>
AlarmId syncAviso;
StopWatch reloj(StopWatch::SECONDS);
int status = WL_IDLE_STATUS;
char ssid[] = "WLAN_A31A";  //  your network SSID (name)
char pass[] = "4c50627e8669011a99ea";       // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
unsigned int localPort = 2390;      // local port to listen for UDP packets
unsigned long currentMillis;
unsigned long previousMillis;
unsigned long previousMillis1;
unsigned long previousMillis2;
unsigned long previousMillis3;


unsigned long intervalo = 1000;

IPAddress timeServer(129, 6, 15, 28); // time.nist.gov NTP server

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message

byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
WiFiUDP Udp;
// ............. send an NTP request to the time server at the given address ...........
unsigned long sendNTPpacket(IPAddress& address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}

//............. print info on the network you're attached to.................
void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
//............. print info on the network you're attached to.................
void Synchro() {
  Serial.println("Soy una puta Alarma ");
  reloj.start();
  sendNTPpacket(timeServer); // send an NTP packet to a time server
  // wait to see if a reply is available
  while (reloj.elapsed() <= 3) // this prevents the time from being constantly shown.
  {
    ;
  }
  reloj.reset();
  if ( Udp.parsePacket() ) {
    Serial.println("packet received");
    // We've received a packet, read the data from it
    Udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

    //the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, esxtract the two words:

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    Serial.print("Seconds since Jan 1 1900 = " );
    Serial.println(secsSince1900);

    // now convert NTP time into everyday time:
    Serial.print("Unix time = ");
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;
    // subtract seventy years:
    unsigned long epoch = secsSince1900 - seventyYears;
    // print Unix time:
    Serial.println(epoch);
    setTime(epoch);
    int anno = year();
    Serial.printf("The UTC Date is %d-%d-%d\n ", day(), month(), year());
    // print the hour, minute and second:
    Serial.print("The UTC time is ");       // UTC is the time at Greenwich Meridian (GMT)
    Serial.print(hour()); // print the hour (86400 equals secs per day)
    Serial.print(':');
    Serial.print(minute()); // print the minute (3600 equals secs per minute)
    Serial.print(':');
    Serial.println(second()); // print the second
    unsigned long europeanEpoch = epoch + adjustDstEurope(anno);
    setTime(europeanEpoch);
  }
}
//............ function that gives the adjusting seconds towards UTC for the European TZ ...................

int adjustDstEurope(int anyo)
{
  // last sunday of march
  int beginDSTDate =  (31 - (5 * year() / 4 + 4) % 7);
  Serial.println(beginDSTDate);
  int beginDSTMonth = 3;
  //last sunday of october
  int endDSTDate = (31 - (5 * year() / 4 + 1) % 7);
  Serial.println(endDSTDate);
  int endDSTMonth = 10;
  // DST is valid as:
  if (((month() > beginDSTMonth) && (month() < endDSTMonth))
      || ((month() == beginDSTMonth) && (day() >= beginDSTDate))
      || ((month() == endDSTMonth) && (day() <= endDSTDate)))
    return 7200;  // DST europe = utc +2 hour
  else return 3600; // nonDST europe = utc +1 hour
}
// ............. send an NTP request to the time server at the given address ...........

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    reloj.start();
    // wait 10 seconds for connection:
    while (reloj.elapsed() <= 10) // this prevents the time from being constantly shown.
    {
      ;
    } reloj.reset();
  }

  Serial.println("Connected to wifi");
  printWifiStatus();
  reloj.start();
  Serial.println("\nStarting connection to server...");
  Udp.begin(localPort);
 while (reloj.elapsed() <= 5) // this prevents the time from being constantly shown.
  { ;
  }
  setTime(0, 0, 0, 1, 1, 1971);
  Serial.printf(" Hora %d H:%d M:%d S\n", hour(), minute(), second());
  syncAviso = Alarm.alarmRepeat(hour(), minute(), second() + 5, Synchro);
  Serial.printf(" Hora de Alarma %d H:%d M:%d S\n", hour(), minute(), (second() + 5));
  reloj.reset();
}

void loop() {
  currentMillis = millis();
  if (currentMillis - previousMillis >= intervalo) // this prevents the time from being constantly shown.
  { previousMillis = currentMillis;
    Serial.printf ("Fecha: %d-%d-%d. Hora: %d:%d:%d\n", day(), month(), year(), hour(), minute(), second());
  }
  /*if (hour()==0&&minute()==0&&second()==20){
    Synchro();
    }*/
  Alarm.delay(0);
}

















