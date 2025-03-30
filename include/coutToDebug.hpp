#pragma once

// Only define and use these classes on Windows
#ifdef _WIN32

#include <iostream>
#include <Windows.h> // Include Windows header only when compiling for Windows

class debugStreambuf : public std::streambuf {
public:
    virtual int_type overflow(int_type c = EOF) {
        if (c != EOF) {
            // TCHAR buf[] = { (TCHAR)c, '\0' }; // Use TCHAR for potential Unicode compatibility
            char buf[] = { static_cast<char>(c), '\0' }; // More direct for typical ASCII/UTF8 console output
            OutputDebugStringA(buf); // Use the ANSI version explicitly if not using TCHAR
        }
        return c;
    }
};

class Cout2VisualStudioDebugOutput {

    debugStreambuf dbgstream;
    std::streambuf* default_stream;

public:
    Cout2VisualStudioDebugOutput() {
        // Redirect cout only if running on Windows
        default_stream = std::cout.rdbuf(&dbgstream);
    }

    ~Cout2VisualStudioDebugOutput() {
        // Restore cout only if it was redirected
        std::cout.rdbuf(default_stream);
    }

    // Prevent copying and moving
    Cout2VisualStudioDebugOutput(const Cout2VisualStudioDebugOutput&) = delete;
    Cout2VisualStudioDebugOutput& operator=(const Cout2VisualStudioDebugOutput&) = delete;
    Cout2VisualStudioDebugOutput(Cout2VisualStudioDebugOutput&&) = delete;
    Cout2VisualStudioDebugOutput& operator=(Cout2VisualStudioDebugOutput&&) = delete;
};

#endif // _WIN32
