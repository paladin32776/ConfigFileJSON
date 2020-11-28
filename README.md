# ConfigFileJSON
Storing config data to a file on SPIFFS. Data is stored in JSON format. However, the JSON layer is hidden behind easy to use get and set methods.

# Example:
## Initialization:
    ConfigFileJSON config('config.json');
    
At object instantiation, if the file already exists, the file content is read and buffered.

## Add/change data:

    config.set("mykey", "myvalue");

or

    config.set("mykey", "myvalue", "mykey1", 2.15);

values of type bool, int, float, and char[] are supported in this version.

# Constructor:
    ConfigFileJSON(const char _filename[])
_filename ... Filename to be used for data storage on SPIFFS.

# Methods:
## set
    bool set(Args... args)

Store a variable number of key/value pairs Keys and values must come in pairs. Supported value types are bool, int, float, and char[].
Returns true if operation has been successful.

## get
    void get(Args... args)
Retrieve values for a variable number of keys. Keys and return variable pointers must be passed as pairs.
Example:
```
int x;
char s[64];
get("name", s, "number", x);
```
## clear 
    bool clear()
Clears buffer and file.
## remove
    bool remove(const char key[])
Removes a specific key from buffer and file.
## dump
    void dump()
Outputs buffer in JSON format over Serial. For debugging.
