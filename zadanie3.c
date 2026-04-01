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

Item* Construct(char* name, bool dir, Item *parent) {
    Item *sosud = malloc(sizeof(Item));
    if (!sosud) return NULL;

    strncpy(sosud->name, name, 255);
    sosud->name[255] = '\0';
    sosud->dir = dir;

    strncpy(sosud->owner, "user", 255);
    sosud->npaBa = 7;

    sosud->parent = parent;
    sosud->children = NULL;
    sosud->bro = NULL;

    return sosud;
}


bool CommandScanner(char input[], char **commands, void (**func)(char *, Item **), int comm_num, Item **root);

void ContentShow(char *arguments, Item **root);
void TransitionTo(char *arguments, Item **root);
void Remove(char *arguments, Item **root);
void CreateFile(char *arguments, Item **root);
void CreateDirectory(char *arguments, Item **root);
void ShowFileContent(char *arguments, Item **root);
void RunFile(char *arguments, Item **root);
void WriteFile(char *arguments, Item **root);
void ChangeMode(char *arguments, Item **root);
void ChangeOwn(char *arguments, Item **root);

void SystemResponse(bool error);
void Splitter(char *input, char **first, char **rest);
void Stripping(Item *base);


int main() {
    char input[516];

    char *commands[] = {"ls", "cd", "rm", "touch", "mkdir", "vypis", "spusti", "zapis", "chmod", "chown"};
    void (*func[])(char *, Item **) = {ContentShow, TransitionTo, Remove, CreateFile, CreateDirectory, ShowFileContent, RunFile, WriteFile, ChangeMode, ChangeOwn};
    int comm_num = sizeof(commands)/sizeof(commands[0]);

    Item *base = Construct("", true, NULL);
    Item *root = base;

    bool present = true;
    while (present) {
        printf("# ");
        if (fgets(input, 516, stdin) != NULL) {
            input[strcspn(input, "\n")] = '\0';

            if (strlen(input) == 0) continue;

            present = CommandScanner(input, commands, func, comm_num, &root);
        }
        else {
            present = false;
        }
    }

    Stripping(base);
    return 0;
}


bool CommandScanner(char input[], char **commands, void (**func)(char *, Item **), const int comm_num, Item **root) {
    char *command = NULL;
    char *rest = NULL;

    Splitter(input, &command, &rest);

    if (strcmp(command, "quit") == 0) return false;

    for (int i = 0; i < comm_num; i++) {
        if (command != NULL && strcmp(command, commands[i]) == 0) {
            func[i](rest, root);

            return true;
        }
    }

    SystemResponse(true);
    return true;
}


void ContentShow(char *arguments, Item **root) {
    if (arguments == NULL) return;

    printf("%s\n", arguments);
}

void TransitionTo(char *arguments, Item **root) {
    if (arguments == NULL) {
        SystemResponse(true);
        return;
    }

    printf("%s\n", arguments);
}

void Remove(char *arguments, Item **root) {
    if (arguments == NULL) {
        SystemResponse(true);
        return;
    }

    printf("%s\n", arguments);
}

void CreateFile(char *arguments, Item **root) {
    if (arguments == NULL) {
        SystemResponse(true);
        return;
    }

    // TODO: выделить память четко под имя и в добавить в чилдрен актуальной папки
    // char *name = ...;
    // strcpy();

    printf("%s\n", arguments);
}

void CreateDirectory(char *arguments, Item **root) {
    if (arguments == NULL) {
        SystemResponse(true);
        return;
    }

    // TODO: тоже что и файл но дир тру

    printf("%s\n", arguments);
}

void ShowFileContent(char *arguments, Item **root) {
    if (arguments == NULL) {
        SystemResponse(true);
        return;
    }

    printf("%s\n", arguments);
}

void RunFile(char *arguments, Item **root) {
    if (arguments == NULL) {
        SystemResponse(true);
        return;
    }

    printf("%s\n", arguments);
}

void WriteFile(char *arguments, Item **root) {
    if (arguments == NULL) {
        SystemResponse(true);
        return;
    }

    printf("%s\n", arguments);
}

void ChangeMode(char *arguments, Item **root) {
    if (arguments == NULL) {
        SystemResponse(true);
        return;
    }

    printf("%s\n", arguments);
}

void ChangeOwn(char *arguments, Item **root) {
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

void Stripping(Item *base) {
    if (base == NULL) return;

    Stripping(base->children);
    Stripping(base->bro);

    free(base);
}