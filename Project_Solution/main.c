#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "mapping.h"
#include "truck.h"

int main(void) {
    // Print header
    header();

    // Creating a pkg struct
    struct PackageInf pkg;

    // Invoking input
    input(&pkg);

    // Print footer
    footer();

    return 0;
}
