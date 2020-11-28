#include "ConfigFileJSON.h"

ConfigFileJSON cf("whatever.json");

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  Serial.printf("test\n");
  cf.set("inum", 18, "mypara", "gernot", "fnum", 3.456);
  cf.set("test", 17);
  bool ok;
  int x;
  float f;
  char s[64];
  cf.get("inum", &x, "mypara", s, "fnum", &f);
  // ok = cf.get("inum", x);
  Serial.printf("inum = %d\n", x);
  Serial.printf("fnum = %f\n", f);
  Serial.printf("mypara = %s\n", s);
  cf.dump();

  delay(1000);
}
