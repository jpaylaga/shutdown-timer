/**
 * Simple Shutdown Timer for Windows.
 * Written by: Joshua Paylaga
 *
 * Emails: joshuapaylaga@gmail.com | joshua@greyboxsolutions.co
 * Website: http://greyboxsolutions.co/
 * Skype: jpaylaga
 *
 * Thank you :)
 */

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

    if ((h >= 0) && (m >= 0 && m < 60) && (s >= 0 && s < 60)) {
        if ( shutdown(h, m, s) == 1) {
            printf("\nYour computer will shutdown in %d:%d:%d.\n\n", h, m, s);
            system("pause");
        } else {
            printf("\nThis program is intended only for Windows Machine.\n\n");
        }
    } else {
        printf("\nInvalid time provided.\n\n");
    }

    return 0;
}

/**
 * Accepts input from user and prevent run-time breakage
 * due to NULL input or wrong data type input.
 */
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

/**
 * Shuts down your computer within the time given.
 * It utilizes the windows command shutdown /s /f /t {seconds}
 * to initialize shutdown. This will not work if compiled to
 * other operating systems.
 */
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

/**
 * Converts h:m:s time to seconds.
 */
int calculate_seconds(int h, int m, int s) {
    int h_to_s = HOUR * h;
    int m_to_s = MINUTE * m;
    return (h_to_s + m_to_s + s);
}
