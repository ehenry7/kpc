// =============================================================================
// Main entry point to select between demo1 and demo2
// =============================================================================

#include <stdio.h>
#include <string.h>

// Forward declarations
int main(int argc, const char * argv[]);
int main2(int argc, const char * argv[]);

int main_entry(int argc, const char * argv[]) {
    // Use "demo2" as an argument to run the second demo
    if (argc > 1 && strcmp(argv[1], "demo2") == 0) {
        return main2(argc, argv);
    }
    return main(argc, argv);
}