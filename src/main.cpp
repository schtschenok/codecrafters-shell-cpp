#include <clocale>
#include <corecrt_memcpy_s.h>
#include <corecrt_wstring.h>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cwchar>

#define INPUT_BUFFER_SIZE 1024
#define OUTPUT_BUFFER_SIZE 2048

static bool keep_running = true;

void print(const wchar_t* input) {
    wprintf(input);
    wprintf(L"\n");
}

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
    wchar_t* command[1024];
    bool string_not_finished = true;
    size_t i = 0;
    size_t input_size = wcslen(input);
    wchar_t temp_buffer[INPUT_BUFFER_SIZE];
    size_t current_word = 0;
    size_t word_count = 0;

    for (int i = 0; i <= input_size; i++) {
        if (input[i] == L' ' || input[i] == L'\0') {
            temp_buffer[i] = L'\0';

            wchar_t* substring = (wchar_t*)(&(temp_buffer[i]) - current_word);
            command[word_count] = substring;
            // print(substring);

            word_count++;
            current_word = 0;
        } else {
            temp_buffer[i] = input[i];
            current_word++;
        }
    }

    if (word_count == 0) {
        swprintf(output, output_size, L": command not found\n");
    }

    if (wcsncmp(command[0], L"exit", 4) == 0) {
        if (word_count > 1) {
            size_t second_argument_length = wcslen(command[1]);
            int exit_code = wcstol(command[1], &command[1] + second_argument_length, 32);
            exit(exit_code);
        }
        exit(0);
    }

    if (wcsncmp(command[0], L"echo", 4) == 0) {
        if (word_count > 1) {
            wcsncpy_s(output, wcslen((wchar_t*)(input + 5)) + 1, (wchar_t*)(input + 5), wcslen((wchar_t*)(input + 5)));
            return;
        }
        output[0] = L'\0';
        return;
    }

    swprintf(output, output_size, L"%ls: command not found", input);
}

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
