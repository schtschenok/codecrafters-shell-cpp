#include <clocale>
#include <cstdio>
#include <cstdlib>
#include <cwchar>

#define INPUT_BUFFER_SIZE 1024
#define OUTPUT_BUFFER_SIZE 2048

static bool keep_running = true;

void read(wchar_t* input) {
    // TODO: write my own getline(), with blackjack and heap allocations done only
    // when it's actually needed. Could be a good idea to terminate early after
    // the first space since at this point we already know if there's such
    // command.
    fgetws(input, INPUT_BUFFER_SIZE, stdin);

    const size_t input_buffer_end = wcscspn(input, L"\r\n");
    input[input_buffer_end] = 0;
}

void eval(const wchar_t* input, const size_t output_size, wchar_t* output) {
    if (wcsncmp(input, L"exit", 4) == 0) {
        exit(0); // TODO: Pass an exit code properly
    }

    swprintf(output, output_size, L"%ls: command not found\n", input);
}

void print(const wchar_t* input) { wprintf(input); }

int main() {
    // Unicode output doesn't seem to work without it. TODO: needs more research!
    setlocale(LC_CTYPE, "");

    setvbuf(stdout, nullptr, _IONBF, 0); // What does it do? I don't remember.
    setvbuf(stderr, nullptr, _IONBF, 0);

    wchar_t input_buffer[INPUT_BUFFER_SIZE];
    wchar_t output_buffer[OUTPUT_BUFFER_SIZE];

    while (keep_running) {
        wprintf(L"$ ");
        read(input_buffer);
        eval(input_buffer, OUTPUT_BUFFER_SIZE, output_buffer);
        print(output_buffer);
    }

    return 0;
}
