#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

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
void Separator(char *input, char **first, char **rest);


int main() {
    char input[516];

    char *commands[] = {"ls", "cd", "rm", "touch", "mkdir", "vypis", "spusti", "zapis", "chmod", "chown"};
    void (*func[])(char *) = {ContentShow, TransitionTo, Remove, CreateFile, CreateDirectory, ShowFileContent, RunFile, WriteFile, ChangeMode, ChangeOwn};
    int comm_num = sizeof(commands)/sizeof(commands[0]);

    bool present = true;
    while (present) {
        printf("# ");
        fgets(input, 516, stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 0) continue;

        present = CommandScanner(input, commands, func, comm_num);
    }

    return 0;
}


bool CommandScanner(char input[], char **commands, void (**func)(char *), const int comm_num) {
    char *command = NULL;
    char *rest = NULL;

    Separator(input, &command, &rest);

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
    if (arguments == NULL) return;

    printf("%s\n", arguments);
}

void Remove(char *arguments) {
    if (arguments == NULL) return;

    printf("%s\n", arguments);
}

void CreateFile(char *arguments) {
    if (arguments == NULL) return;

    printf("%s\n", arguments);
}

void CreateDirectory(char *arguments) {
    if (arguments == NULL) return;

    printf("%s\n", arguments);
}

void ShowFileContent(char *arguments) {
    if (arguments == NULL) return;

    printf("%s\n", arguments);
}

void RunFile(char *arguments) {
    if (arguments == NULL) return;

    printf("%s\n", arguments);
}

void WriteFile(char *arguments) {
    if (arguments == NULL) return;

    printf("%s\n", arguments);
}

void ChangeMode(char *arguments) {
    if (arguments == NULL) return;

    printf("%s\n", arguments);
}

void ChangeOwn(char *arguments) {
    if (arguments == NULL) return;

    printf("%s\n", arguments);
}


void SystemResponse(const bool error) {
    if (error) {
        printf("chyba\n");
    }
    else {
        printf("ok\n");
    }
}

void Separator(char *input, char **first, char **rest) {
    *first = strtok(input, " ");
    *rest = strtok(NULL, "");
}