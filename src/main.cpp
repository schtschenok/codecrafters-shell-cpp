#include <cstring>
#include <cstdio>

#define INPUT_BUFFER_SIZE 1024

int main() {
    setvbuf(stdout, nullptr, _IONBF, 0);
    setvbuf(stderr, nullptr, _IONBF, 0);

    printf("$ ");

    char input_buffer[INPUT_BUFFER_SIZE];
    fgets(input_buffer, INPUT_BUFFER_SIZE, stdin);

    input_buffer[strcspn(input_buffer, "\r\n")] = 0;

    printf("%s: command not found", input_buffer);
}
