#include <FS.h>
#include <ArduinoJson.h>
#include "StreamUtils.h"


class ConfigFileJSON
{
  private:
    // File name storage:
    char filename[32];
    // JSON storage for data
    DynamicJsonDocument doc;

    // Template functions to assemble JSON object from variable number of input parameters:
    template<typename Tparameter, typename Tvalue>
    void assembleJSON(Tparameter parameter, Tvalue value)
    {
      doc[parameter]=value;
    }
    template<typename Tparameter, typename Tvalue, typename... Args>
    void assembleJSON(Tparameter parameter, Tvalue value, Args... args)
    {
      doc[parameter]=value;
      assembleJSON(args...);
    }

    // Template functions to dissemble JSON object from variable number of input parameters:
    template<typename Tparameter, typename Tvalue>
    void dissembleJSON(Tparameter parameter, Tvalue* value)
    {
      tget(parameter, value);
    }
    template<typename Tparameter, typename Tvalue, typename... Args>
    void dissembleJSON(Tparameter parameter, Tvalue* value, Args... args)
    {
      tget(parameter, value);
      dissembleJSON(args...);
    }

    // Routine to write JSON data to SPIFFS file system:
    bool write_file();
    // Routines to get data from JSON fields:
    bool tget(const char* key, bool* target);
    bool tget(const char* key, int* target);
    bool tget(const char* key, float* target);
    bool tget(const char* key, char* target);

  public:
    // Constructor; reads JSON data from SPIFFS file system to initialize:
    ConfigFileJSON(const char _filename[]);

    // Template functions to write a variable number of input parameters as JSON object:
    template<typename... Args>
    bool set(Args... args)
    {
        assembleJSON(args...);
        return write_file();
    }

    // Template functions to read a variable number of input parameters from JSON object:
    template<typename... Args>
    void get(Args... args)
    {
        dissembleJSON(args...);
    }

    // Utility routines:
    bool clear();
    bool remove(const char key[]);
    void dump();
};
