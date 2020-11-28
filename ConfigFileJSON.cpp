#include "ConfigFileJSON.h"

ConfigFileJSON::ConfigFileJSON(const char _filename[]): doc(1024)
{
  strcpy(filename, _filename);
  if (SPIFFS.begin())
  {
    if (SPIFFS.exists(filename))
    {
      File file = SPIFFS.open(filename, "r");
      if (file)
      {
        deserializeJson(doc, file);
        file.close();
      }
      else
        Serial.printf("[ERROR] File open failed.\n");
    }
    else
        Serial.printf("[ERROR] File open failed.\n");
    SPIFFS.end();
  }
  else
    Serial.printf("SPIFFS initialization failed.\n");
}

bool ConfigFileJSON::write_file()
{
  if (SPIFFS.begin())
  {
    File file = SPIFFS.open(filename, "w");
    if (file)
    {
      serializeJson(doc, file);
      file.close();
    }
    else
    {
      Serial.printf("[ERROR] File open failed.\n");
      return false;
    }
    SPIFFS.end();
  }
  else
  {
    Serial.printf("SPIFFS initialization failed.\n");
    return false;
  }
  return true;
}

bool ConfigFileJSON::tget(const char* key, bool* target)
{
  Serial.printf("bool\n");
  if (!doc.containsKey(key))
    return false;
  if (!doc[key].is<bool>())
    return false;
  *target = doc[key];
  return true;
}

bool ConfigFileJSON::tget(const char* key, int* target)
{
  Serial.printf("int\n");
  if (!doc.containsKey(key))
    return false;
  if (!doc[key].is<int>())
    return false;
  *target = doc[key];
  return true;
}

bool ConfigFileJSON::tget(const char* key, float* target)
{
  Serial.printf("float\n");
  if (!doc.containsKey(key))
    return false;
  if (!doc[key].is<float>())
    return false;
  *target = doc[key];
  return true;
}

bool ConfigFileJSON::tget(const char* key, char* target)
{
  Serial.printf("string\n");
  if (!doc.containsKey(key))
    return false;
  if (!doc[key].is<char*>())
    return false;
  strcpy(target, doc[key]);
  return true;
}

bool ConfigFileJSON::clear()
{
  doc.clear();
  return write_file();
}

bool ConfigFileJSON::remove(const char key[])
{
  if (!doc.containsKey(key))
    return false;
  doc.remove(key);
  return write_file();
}

void ConfigFileJSON::dump()
{
  serializeJson(doc, Serial);
  Serial.printf("\n");
}
