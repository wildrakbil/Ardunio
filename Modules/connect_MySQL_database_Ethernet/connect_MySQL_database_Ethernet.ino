#include <Ethernet.h>
#include <MySQL_Connection.h>
#include <Dns.h>

byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress server_addr(127, 0, 0, 1); // IP of the MySQL *server* here
IPAddress server_ip;

char hostname[] = "db4free.net";
char user[] = "wildrakbil";              // MySQL user login username
char password[] = "wpq3518xh";        // MySQL user login password


//char hostname[] = "localhost";
//char user[] = "root";              // MySQL user login username
//char password[] = "password";        // MySQL user login password


char default_db = "dbhome";
int serverPort = 3306;

EthernetClient client;
MySQL_Connection conn((Client *)&client);


DNSClient dns_client;   // DNS instance

void setup() {
  Serial.begin(115200);
  while (!Serial); // wait for serial port to connect
  Ethernet.begin(mac_addr);
  dns_client.begin(Ethernet.dnsServerIP());
  dns_client.getHostByName(hostname, server_ip);
  Serial.print("Connecting...:");
  Serial.println(server_ip);
  if (conn.connect(server_ip, 3306, user, password)) {
    delay(10000);
  }
  else {
    Serial.println("Connection failed.");
  }
}

void loop() {

}
