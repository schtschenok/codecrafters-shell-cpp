#include <cerrno>
#include <cstdio>
#include <cwchar>
#include <clocale>
// #include <csignal>

#define INPUT_BUFFER_SIZE 1024
#define OUTPUT_BUFFER_SIZE 2048

static bool keep_running = true;

void read(wchar_t *input) {
    // TODO: write my own getline(), with blackjack and heap allocations done only when it's actually needed.
    // Could be a good idea to terminate early after the first space since at this point we already know if there's such command.
    fgetws(input, INPUT_BUFFER_SIZE, stdin);

    const size_t input_buffer_end = wcscspn(input, L"\r\n");
    input[input_buffer_end] = 0;
}

void eval(const wchar_t *input, const size_t output_size, wchar_t *output) {
    swprintf(output, output_size, L"%ls: command not found\n", input);
}

void print(const wchar_t *input) {
    wprintf(input);
}

// void sigint_handler(int sig) {
//     keep_running = false;
// }

int main() {
    // Unicode output doesn't seem to work without it. TODO: needs more research!
    setlocale(LC_CTYPE, "");

    setvbuf(stdout, nullptr, _IONBF, 0);
    setvbuf(stderr, nullptr, _IONBF, 0);

    // TODO: Figure out signals
    // Returns 0, why?
    // struct sigaction act{};
    // act.sa_handler = sigint_handler;
    // wprintf(L"%i\n", sigaction(SIGINT, &act, nullptr));

    // Also returns 0, why?
    // wprintf(L"%i\n", signal(SIGINT, sigint_handler) == SIG_ERR);

    // ReSharper disable CppTooWideScope
    wchar_t input_buffer[INPUT_BUFFER_SIZE];
    wchar_t output_buffer[OUTPUT_BUFFER_SIZE];
    // ReSharper restore CppTooWideScope

    // ReSharper disable once CppDFALoopConditionNotUpdated
    // ReSharper disable once CppDFAEndlessLoop
    // ReSharper disable once CppDFAConstantConditions
    while (keep_running) {
        wprintf(L"$ ");
        read(input_buffer);
        eval(input_buffer, OUTPUT_BUFFER_SIZE, output_buffer);
        print(output_buffer);
    }

    return 0;
}
