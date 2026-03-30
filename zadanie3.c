#include <stdio.h>
#include <stdbool.h>

void SystemResponse(bool error);


int main() {
    SystemResponse(true);

    return 0;
}


void SystemResponse(const bool error) {
    if (error) {
        printf("chyba\n");
    }
    else {
        printf("ok\n");
    }
}