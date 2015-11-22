#ifndef MICEWARS_CONFIGFILE_H
#define MICEWARS_CONFIGFILE_H

#include <stdio.h>

struct StackNode {
    StackNode * next;
    char* name;
    char* value;
};

class ConfigFile {
private:
    static ConfigFile* m_pInstance;

// Writes setting name and value to the StackNode (name - setting name, value - seting value).
    void push(char* name, char* value);

// Reads and deletes setting name and value from the StackNode
    StackNode * pop();

// Reads the configuration settings from the StackNode and applies them to the game.
// Writes error on the stderr if encountered an error in parsing the config file.
    void processConfig();

// Writes the default config file if it wasn't found in the game directory. Returns -1 on fail.
    int writeDefaultConfig(FILE *fp);

    ConfigFile() { printf("ConfigFile instance created!\n"); };

public:

// Reads the configuration file and uses 'push' function to put in onto
// temporary StackNode for later processing.
    void loadConfig(const char* filepath);

    static ConfigFile* Instance();
};


#endif //MICEWARS_CONFIGFILE_H
