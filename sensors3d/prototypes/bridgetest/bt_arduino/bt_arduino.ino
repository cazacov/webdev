#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

YunServer server;

void setup() {
  Bridge.begin();
  server.listenOnLocalhost();
  server.begin();
}

void loop() {
  YunClient client = server.accept();
  if (client) {
    process(client);
    client.stop();
  }
  delay(20);
}

void process(YunClient client) {
  String command = client.readString();
  command.trim();
  if (command == "s") {
    client.print(F("sensors,"));
    client.println("001122-334455");
   }
}
