#include <stdlib.h>
#include <string.h>
#include "ConfigFile.h"
#include "global_vars.h"
#include "Engine.h"
#include "Timer.h"

ConfigFile* ConfigFile::m_pInstance = nullptr;

ConfigFile* ConfigFile::Instance() {
    if (m_pInstance == nullptr) {
        m_pInstance = new ConfigFile;
    } // Only allow one instance at time
    return m_pInstance;
}

struct stack_node * root = 0;

void ConfigFile::push(char* name, char* value) {
    stack_node * node;
    node = new stack_node;
    node->next = root;
    node->name = name;
    node->value = value;
    root = node;
}

stack_node* ConfigFile::pop() {
    struct stack_node *val;
    val = root;
    if (root)
        root = root->next;
    return val;
}

int ConfigFile::writeDefaultConfig(FILE* fp) {
    printf("[INFO] Creating a default config file...");
    if ((fp = fopen(CONFIG_FILE_PATH, "w"))) {
        fprintf(fp, "[Gameplay]\n");
        fprintf(fp, "FPS=60\n");
        fprintf(fp, "[Resolution]\n");
        fprintf(fp, "Width=%d\n",DEFAULT_WIN_WIDTH);
        fprintf(fp, "Height=%d\n",DEFAULT_WIN_HEIGHT);
        fclose(fp);
        printf(" OK.\n");
        return 0;
    }
    else {
        fprintf(stderr, "\r[ERROR] An error occured during writing the default configuration file.\n");
        return -1;
    }
}

void ConfigFile::loadConfig(const char* filepath) {
    char* sett_name = nullptr;
    char* sett_value = nullptr;
    char buffer[50];
    char curr_char;
    size_t pos = 0;
    bool is_found_eq_sign = 0;
    FILE* fp;

    if ((fp = fopen(filepath, "r"))) {
        while ((curr_char = (char) fgetc(fp)) != EOF) {
            switch (curr_char) {
                case '=': {
                    sett_name = strndup(buffer, pos);
                    pos = 0;
                    is_found_eq_sign = 1;
                    break;
                }
                case '\n': {
                    if (is_found_eq_sign == 1) {
                        sett_value = strndup(buffer, pos);
                        push(sett_name, sett_value);
                    } else if (strndup(buffer, pos)[0] != '[') {
                        fprintf(stderr, "[ERROR] Error parsing the config file: No '=' found in the current line.\n");
                    }
                    pos = 0;
                    is_found_eq_sign = 0;
                    break;
                }
                default: {
                    buffer[pos] = curr_char;
                    pos++;
                }
            }
        }
        fclose(fp);
        processConfig();
    }
    else {
        writeDefaultConfig(fp);
    }
}

void ConfigFile::processConfig() {
    struct stack_node *sett;
    printf("[INFO] Loading configuration...\n");
    for (sett = pop(); sett != NULL; sett = pop()) {
        printf("[CONFIG] %s = %s\n", sett->name, sett->value);
        if ((strcmp(sett->name, "FPS") == 0)) {
            Timer::Instance()->setFPS(atoi(sett->value));
        }
        else if ((strcmp(sett->name, "Width") == 0)) {
            Engine::Instance()->setWindowWidth(atoi(sett->value));
        }
        else if ((strcmp(sett->name, "Height") == 0)) {
            Engine::Instance()->setWindowHeight(atoi(sett->value));
        }
//        free(sett->name);
//        free(sett->value);
//        free(sett);
    }
    printf("[INFO] Configuration loaded.\n");
}
