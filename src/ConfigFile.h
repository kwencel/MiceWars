#ifndef MICEWARS_CONFIGFILE_H
#define MICEWARS_CONFIGFILE_H

#include <stdio.h>

struct stack_node {
    stack_node * next;
    char* name;
    char* value;
};

class ConfigFile {
private:
    static ConfigFile* m_pInstance;
    stack_node config_stack;

// Writes setting name and value to the stack_node (name - setting name, value - seting value).
    void push(char* name, char* value);

// Reads and deletes setting name and value from the stack_node
    stack_node* pop();

// Reads the configuration settings from the stack_node and applies them to the game.
// Writes error on the stderr if encountered an error in parsing the config file.
    void processConfig();

    ConfigFile() { printf("ConfigFile instance created!\n"); };

public:

// Writes the default config file if it wasn't found in the game directory. Returns -1 on fail.
    int writeDefaultConfig(FILE *fp);

// Reads the configuration file and uses 'push' function to put in onto
// temporary stack_node for later processing.
    void loadConfig(const char* );

    static ConfigFile* Instance();
};


#endif //MICEWARS_CONFIGFILE_H
