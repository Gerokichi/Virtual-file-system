#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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
char* Fade(char *head);
Item* LastBro(Item *root);
Item* BloodHound(Item *child, char *name);
void ThreeYearsInDagestan(int npaBa, char *sosud);
bool Allowed(Item *item, int npaBa);


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

    if (command == NULL) return true;

    if (strcmp(command, "quit") == 0) return false;

    for (int i = 0; i < comm_num; i++) {
        if (command != NULL && strcmp(command, commands[i]) == 0) {
            func[i](Fade(rest), root);
            return true;
        }
    }

    SystemResponse(true);
    return true;
}


void ContentShow(char *arguments, Item **root) {
    if (!Allowed(*root, 4)) {
        SystemResponse(true);
        return;
    }

    char sosud_npaB[4];

    if (arguments == NULL) {
        Item *temp = (*root)->children;
        while (temp != NULL) {
            ThreeYearsInDagestan(temp->npaBa, sosud_npaB);
            printf("%s %s %s\n", temp->name, temp->owner, sosud_npaB);
            temp = temp->bro;
        }
        return;
    }

    char *name = NULL;
    char *rest = NULL;
    Splitter(arguments, &name, &rest);

    if (rest != NULL) {
        SystemResponse(true);
        return;
    }

    Item *target = BloodHound((*root)->children, name);
    if (target != NULL) {
        ThreeYearsInDagestan(target->npaBa, sosud_npaB);
        printf("%s %s %s\n", target->name, target->owner, sosud_npaB);
    }
    else SystemResponse(true);
}

void TransitionTo(char *arguments, Item **root) {
    if (arguments == NULL) {
        SystemResponse(true);
        return;
    }

    char *name = NULL;
    char *rest = NULL;
    Splitter(arguments, &name, &rest);

    if (rest != NULL) {
        SystemResponse(true);
        return;
    }

    if (strcmp(name, "..") == 0) {
        if ((*root)->parent != NULL) {
            *root = (*root)->parent;
        }
        return;
    }

    Item *target = BloodHound((*root)->children, name);
    if (target != NULL && target->dir && Allowed(target, 1)) {
        *root = target;
    }
    else SystemResponse(true);
}

void Remove(char *arguments, Item **root) {
    if (arguments == NULL) {
        SystemResponse(true);
        return;
    }

    char *name = NULL;
    char *rest = NULL;
    Splitter(arguments, &name, &rest);

    if (rest != NULL) {
        SystemResponse(true);
        return;
    }

    Item *end = NULL;
    Item *current = (*root)->children;

    while (current != NULL && strcmp(current->name, name) != 0) {
        end = current;
        current = current->bro;
    }

    if (current == NULL) {
        SystemResponse(true);
        return;
    }

    if (Allowed(current, 2)) {
        if (end != NULL) {
            end->bro = current->bro;
        }
        else {
            (*root)->children = current->bro;
        }

        current->bro = NULL;
        Stripping(current);
    }
    else {
        SystemResponse(true);
    }
}

void CreateFile(char *arguments, Item **root) {
    if (arguments == NULL || !Allowed(*root, 2)) {
        SystemResponse(true);
        return;
    }

    char *name = NULL;
    char *rest = NULL;
    Splitter(arguments, &name, &rest);

    if (rest != NULL || BloodHound((*root)->children, name) != NULL) {
        SystemResponse(true);
        return;
    }

    Item *new = Construct(name, false, *root);
    if ((*root)->children == NULL) {
        (*root)->children = new;
    }
    else {
        LastBro((*root)->children)->bro = new;
    }
}

void CreateDirectory(char *arguments, Item **root) {
    if (arguments == NULL || !Allowed(*root, 2)) {
        SystemResponse(true);
        return;
    }

    char *name = NULL;
    char *rest = NULL;
    Splitter(arguments, &name, &rest);

    if (rest != NULL || BloodHound((*root)->children, name) != NULL) {
        SystemResponse(true);
        return;
    }

    Item *new = Construct(name, true, *root);
    if ((*root)->children == NULL) {
        (*root)->children = new;
    }
    else {
        LastBro((*root)->children)->bro = new;
    }
}

void ShowFileContent(char *arguments, Item **root) {
    if (arguments == NULL) {
        SystemResponse(true);
        return;
    }

    char *name = NULL;
    char *rest = NULL;
    Splitter(arguments, &name, &rest);

    if (rest != NULL) {
        SystemResponse(true);
        return;
    }

    Item *target = BloodHound((*root)->children, name);
    if (target != NULL && Allowed(target, 4)) {
        SystemResponse(false);
    } else SystemResponse(true);
}

void RunFile(char *arguments, Item **root) {
    if (arguments == NULL) {
        SystemResponse(true);
        return;
    }

    char *name = NULL;
    char *rest = NULL;
    Splitter(arguments, &name, &rest);

    if (rest != NULL) {
        SystemResponse(true);
        return;
    }

    Item *target = BloodHound((*root)->children, name);
    if (target == NULL || !Allowed(target, 1)) SystemResponse(true);
}

void WriteFile(char *arguments, Item **root) {
    if (arguments == NULL) {
        SystemResponse(true);
        return;
    }

    char *name = NULL;
    char *rest = NULL;
    Splitter(arguments, &name, &rest);

    if (rest != NULL) {
        SystemResponse(true);
        return;
    }

    Item *target = BloodHound((*root)->children, name);
    if (target == NULL || !Allowed(target, 2)) SystemResponse(true);
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

char* Fade(char *head) {
    if (head == NULL) return NULL;

    while (isspace((unsigned char)*head)) head++;
    if (*head == '\0') return NULL;

    char *end = head + strlen(head) - 1;
    while (end > head && isspace((unsigned char)*end)) end--;
    end[1] = '\0';

    return head;
}

Item* LastBro(Item *root) {
    if (root == NULL) return NULL;

    Item *last = root;
    while (last->bro != NULL) {
        last = last->bro;
    }

    return last;
}

Item* BloodHound(Item *child, char *name) {
    if (child == NULL) return NULL;

    Item *target = child;
    while (strcmp(target->name, name) != 0) {
        if (target->bro == NULL) return NULL;

        target = target->bro;
    }

    return target;
}

void ThreeYearsInDagestan(const int npaBa, char *sosud) {
    sosud[0] = npaBa & 4 ? 'r' : '-';
    sosud[1] = npaBa & 2 ? 'w' : '-';
    sosud[2] = npaBa & 1 ? 'x' : '-';
    sosud[3] = '\0';
}

bool Allowed(Item *item, int npaBa) {
    if (item == NULL) return false;

    return (item->npaBa & npaBa) != 0;
}