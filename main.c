#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VARIABLES 100
#define MAX_LABELS 50
#define MAX_STACK_SIZE 100

// Variable type
typedef enum { INT, STRING } VarType;

// Variable structure
typedef struct {
    char name[32];
    union {
        int intValue;
        char stringValue[256];
    };
    VarType type;
} Variable;

// Label structure
typedef struct {
    char name[32];
    int line_number;
} Label;

// Stack structure
int stack[MAX_STACK_SIZE];
int stack_top = -1;

// Global variables and labels
Variable variables[MAX_VARIABLES];
int variable_count = 0;

Label labels[MAX_LABELS];
int label_count = 0;

// Condition flags for CMP command
int equal_flag = 0;
int less_flag = 0;
int greater_flag = 0;

// Function to set or update a variable
void set_variable(const char *name, int value, const char *str_value, int is_string) {
    for (int i = 0; i < variable_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            if (is_string) {
                strcpy(variables[i].stringValue, str_value);
                variables[i].type = STRING;
            } else {
                variables[i].intValue = value;
                variables[i].type = INT;
            }
            return;
        }
    }
    // New variable
    strcpy(variables[variable_count].name, name);
    if (is_string) {
        strcpy(variables[variable_count].stringValue, str_value);
        variables[variable_count].type = STRING;
    } else {
        variables[variable_count].intValue = value;
        variables[variable_count].type = INT;
    }
    variable_count++;
}

// Function to get a variable's value
int get_variable(const char *name, int *found, char *str_value) {
    for (int i = 0; i < variable_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            *found = 1;
            if (variables[i].type == STRING) {
                strcpy(str_value, variables[i].stringValue);
            }
            return variables[i].intValue;
        }
    }
    *found = 0;
    return 0;
}

// Function to compare two variables
void compare(int x, int y) {
    equal_flag = (x == y);
    less_flag = (x < y);
    greater_flag = (x > y);
}

// Function to process a single line of code
int process_line(const char *line, int *program_counter, int total_lines, char **lines) {
    char command[32], arg1[32], arg2[32], str_value[256];
    int arg_value, result;

    if (sscanf(line, "%31s", command) != 1) return 0;

    if (strcmp(command, "MOV") == 0) {
        // MOV variable value
        if (sscanf(line, "MOV %31s %d", arg1, &arg_value) == 2) {
            set_variable(arg1, arg_value, NULL, 0);  // Integer assignment
        } else if (sscanf(line, "MOV %31s \"%255[^\"]\"", arg1, str_value) == 2) {
            set_variable(arg1, 0, str_value, 1);  // String assignment
        }

    } else if (strcmp(command, "ADD") == 0) {
        // ADD variable value
        sscanf(line, "ADD %31s %d", arg1, &arg_value);
        int found = 0;
        result = get_variable(arg1, &found, str_value);
        if (found && variables[found].type == INT) {
            set_variable(arg1, result + arg_value, NULL, 0);
        } else {
            printf("Error: Undefined variable '%s' or incorrect type\n", arg1);
        }

    } else if (strcmp(command, "SUB") == 0) {
        // SUB variable value
        sscanf(line, "SUB %31s %d", arg1, &arg_value);
        int found = 0;
        result = get_variable(arg1, &found, str_value);
        if (found && variables[found].type == INT) {
            set_variable(arg1, result - arg_value, NULL, 0);
        } else {
            printf("Error: Undefined variable '%s' or incorrect type\n", arg1);
        }

    } else if (strcmp(command, "MUL") == 0) {
        // MUL variable value
        sscanf(line, "MUL %31s %d", arg1, &arg_value);
        int found = 0;
        result = get_variable(arg1, &found, str_value);
        if (found && variables[found].type == INT) {
            set_variable(arg1, result * arg_value, NULL, 0);
        } else {
            printf("Error: Undefined variable '%s' or incorrect type\n", arg1);
        }

    } else if (strcmp(command, "DIV") == 0) {
        // DIV variable value
        sscanf(line, "DIV %31s %d", arg1, &arg_value);
        int found = 0;
        result = get_variable(arg1, &found, str_value);
        if (found && variables[found].type == INT && arg_value != 0) {
            set_variable(arg1, result / arg_value, NULL, 0);
        } else if (arg_value == 0) {
            printf("Error: Division by zero\n");
        } else {
            printf("Error: Undefined variable '%s' or incorrect type\n", arg1);
        }

    } else if (strcmp(command, "PRINT") == 0) {
        // PRINT variable
        sscanf(line, "PRINT %31s", arg1);
        int found = 0;
        char output_str[256];
        result = get_variable(arg1, &found, output_str);
        if (found) {
            if (variables[found].type == STRING) {
                printf("%s\n", output_str);  // Print the string
            } else {
                printf("%d\n", result);  // Print the integer
            }
        } else {
            printf("Error: Undefined variable '%s'\n", arg1);
        }

    } else if (strcmp(command, "LABEL") == 0) {
        // LABEL name
        sscanf(line, "LABEL %31s", arg1);
        strcpy(labels[label_count].name, arg1);
        labels[label_count].line_number = *program_counter;
        label_count++;

    } else if (strcmp(command, "JMP") == 0) {
        // JMP label
        sscanf(line, "JMP %31s", arg1);
        for (int i = 0; i < label_count; i++) {
            if (strcmp(labels[i].name, arg1) == 0) {
                *program_counter = labels[i].line_number;
                return 1;
            }
        }
        printf("Error: Undefined label '%s'\n", arg1);

    } else {
        printf("Error: Unknown command '%s'\n", command);
    }
    return 0;
}

// Main function
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <source_file>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char *lines[100];
    int total_lines = 0;

    // Read all lines
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        lines[total_lines] = strdup(buffer);
        total_lines++;
    }
    fclose(file);

    // Execute lines
    for (int i = 0; i < total_lines; i++) {
        int program_counter = i;
        process_line(lines[i], &program_counter, total_lines, lines);
        if (program_counter != i) {
            i = program_counter - 1;  // Adjust for loop increment
        }
    }

    // Free lines
    for (int i = 0; i < total_lines; i++) {
        free(lines[i]);
    }

    return 0;
}
