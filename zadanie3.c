#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct Item {
    char name[256];
    bool dir;

    char owner[256];
    int npaBa;

    struct Item *parent;
    struct Item *children;
    struct Item *bro;
} Item;

Item* Construct(char* name, bool dir, Item* parent) {
    Item* sosud = malloc(sizeof(Item));
    if (!sosud) return NULL;

    strncpy(sosud->name, name, 255);
    sosud->dir = dir;

    strncpy(sosud->owner, "user", 255);
    sosud->npaBa = 7;

    sosud->parent = parent;
    sosud->children = NULL;
    sosud->bro = NULL;

    return sosud;
}


bool CommandScanner(char input[], char **commands, void (**func)(char *), int comm_num);

void ContentShow(char *arguments);
void TransitionTo(char *arguments);
void Remove(char *arguments);
void CreateFile(char *arguments);
void CreateDirectory(char *arguments);
void ShowFileContent(char *arguments);
void RunFile(char *arguments);
void WriteFile(char *arguments);
void ChangeMode(char *arguments);
void ChangeOwn(char *arguments);

void SystemResponse(bool error);
void Splitter(char *input, char **first, char **rest);


int main() {
    char input[516];

    char *commands[] = {"ls", "cd", "rm", "touch", "mkdir", "vypis", "spusti", "zapis", "chmod", "chown"};
    // TODO: подумать над передачей актуальной папки
    void (*func[])(char *) = {ContentShow, TransitionTo, Remove, CreateFile, CreateDirectory, ShowFileContent, RunFile, WriteFile, ChangeMode, ChangeOwn};
    int comm_num = sizeof(commands)/sizeof(commands[0]);

    // TODO: разобратся как лучше начать (создать рут) и как его видеть всем
    Item* base = Construct("", true, NULL);
    Item* root = base;

    bool present = true;
    while (present) {
        printf("# ");
        if (fgets(input, 516, stdin) != NULL) {
            input[strcspn(input, "\n")] = '\0';

            if (strlen(input) == 0) continue;

            present = CommandScanner(input, commands, func, comm_num);
        }
        else {
            present = false;
        }
    }

    free(base);
    return 0;
}


bool CommandScanner(char input[], char **commands, void (**func)(char *), const int comm_num) {
    char *command = NULL;
    char *rest = NULL;

    Splitter(input, &command, &rest);

    if (strcmp(command, "quit") == 0) return false;

    for (int i = 0; i < comm_num; i++) {
        if (command != NULL && strcmp(command, commands[i]) == 0) {
            func[i](rest);

            return true;
        }
    }

    SystemResponse(true);
    return true;
}


void ContentShow(char *arguments) {
    if (arguments == NULL) return;

    printf("%s\n", arguments);
}

void TransitionTo(char *arguments) {
    if (arguments == NULL) {
        SystemResponse(true);
        return;
    }

    printf("%s\n", arguments);
}

void Remove(char *arguments) {
    if (arguments == NULL) {
        SystemResponse(true);
        return;
    }

    printf("%s\n", arguments);
}

void CreateFile(char *arguments) {
    if (arguments == NULL) {
        SystemResponse(true);
        return;
    }

    // TODO: выделить память четко под имя и в добавить в чилдрен актуальной папки
    // char *name = ...;
    // strcpy();

    printf("%s\n", arguments);
}

void CreateDirectory(char *arguments) {
    if (arguments == NULL) {
        SystemResponse(true);
        return;
    }

    // TODO: тоже что и файл но дир тру

    printf("%s\n", arguments);
}

void ShowFileContent(char *arguments) {
    if (arguments == NULL) {
        SystemResponse(true);
        return;
    }

    printf("%s\n", arguments);
}

void RunFile(char *arguments) {
    if (arguments == NULL) {
        SystemResponse(true);
        return;
    }

    printf("%s\n", arguments);
}

void WriteFile(char *arguments) {
    if (arguments == NULL) {
        SystemResponse(true);
        return;
    }

    printf("%s\n", arguments);
}

void ChangeMode(char *arguments) {
    if (arguments == NULL) {
        SystemResponse(true);
        return;
    }

    printf("%s\n", arguments);
}

void ChangeOwn(char *arguments) {
    if (arguments == NULL) {
        SystemResponse(true);
        return;
    }

    printf("%s\n", arguments);
}


void SystemResponse(bool error) {
    if (error) {
        printf("chyba\n");
    }
    else {
        printf("ok\n");
    }
}

void Splitter(char *input, char **first, char **rest) {
    *first = strtok(input, " ");
    *rest = strtok(NULL, "");
}