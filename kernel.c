#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum {
    BLACK,
    RED,
    GREEN,
    BLUE,
    // Add more colors as needed
} VGA_Color;

void setTerminalFontColor(VGA_Color color) {
    const char* ANSI_COLOR_CODES[] = {
        "\x1B[0;30m", // BLACK
        "\x1B[0;31m", // RED
        "\x1B[0;32m", // GREEN
        "\x1B[0;34m", // BLUE
        // Add more ANSI color codes as needed
    };

    if (color >= 0 && color < sizeof(ANSI_COLOR_CODES) / sizeof(ANSI_COLOR_CODES[0])) {
        printf("%s", ANSI_COLOR_CODES[color]);
    } else {
        printf("Error: Invalid color code\n");
    }
}

void handleCommand(const char *command) {
    char color[20];

    if (strcmp(command, "exit") == 0) {
        printf("Exiting...\n");
        exit(0);
    } else if (sscanf(command, "color -%19[A-Za-z]", color) == 1) {
        VGA_Color vgaColor;
        if (strcasecmp(color, "BLACK") == 0) {
            vgaColor = BLACK;
        } else if (strcasecmp(color, "RED") == 0) {
            vgaColor = RED;
        } else if (strcasecmp(color, "GREEN") == 0) {
            vgaColor = GREEN;
        } else if (strcasecmp(color, "BLUE") == 0) {
            vgaColor = BLUE;
        } else {
            printf("Error: Invalid color parameter\n");
            return;
        }

        setTerminalFontColor(vgaColor);
        printf("Setting terminal font color to %s\n", color);
        // Reset color to default after printing the message
        printf("\x1B[0m");
    } else if (strcmp(command, "help") == 0) {
        printf("Known commands: exit, color, help\n");
    } else {
        printf("Error: Unknown command\n");
    }
}

int main() {
    char command[50];
    while (1) {
        printf("~> ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0';  // Remove the trailing newline

        handleCommand(command);
    }

    return 0;
}
