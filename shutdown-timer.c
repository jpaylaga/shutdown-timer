#include<stdio.h>

#define HOUR 3600
#define MINUTE 60
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define IS_WINDOWS 1
#else
#define IS_WINDOWS 0
#endif

void scanf_int(char *q, int *n);
int shutdown(int h, int m, int s);
int calculate_seconds(int h, int m, int s);

int main() {
    int h = 0;
    int m = 0;
    int s = 0;

    printf("Simple Shutdown Timer for Windows.\n");
    printf("Written by: Joshua Paylaga\n\n");

    scanf_int("Hour(s): "   , &h);
    scanf_int("Minute(s): " , &m);
    scanf_int("Seconds(s): ", &s);

    if ( shutdown(h, m, s) == 1) {
        printf("\nYour computer will shutdown in %d:%d:%d.\n\n", h, m, s);
        system("pause");
    } else {
        printf("\nThis program is intended only for Windows Machine.\n\n");
    }

    return 0;
}

void scanf_int(char *q, int *n) {
    printf("%s", q);
    char buf[40];
    while (fgets(buf, sizeof buf, stdin) != NULL) {
        if (sscanf(buf, "%d", n) != 1) {
            printf("%s", q);
        } else {
            break;
        }
    }
}

int shutdown(int h, int m, int s) {
    int success = 0;
    if (IS_WINDOWS == 1) {
        int seconds = calculate_seconds(h, m, s);
        char command[250];
        sprintf(command, "shutdown /s /f /t %d", seconds);
        system(command);
        success = 1;
    }
    return success;
}

int calculate_seconds(int h, int m, int s) {
    int h_to_s = HOUR * h;
    int m_to_s = MINUTE * m;
    return (h_to_s + m_to_s + s);
}
