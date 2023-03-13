//
// Created by brunshweeck on 16/02/2023.
//

#include "../Collections/ArrayList.h"
#include "../Charset/GB18030.h"
#include "../CodingError.h"
#include "../Charset/UTF8.h"

void func(int i) {
    i += 2;
}
#include <cstdio>
#include <unistd.h>

int main(int, char const *[], char const *[]) {
    throw Error();
    FILE* f = fopen("C:/Users/brunshweeck/CLionProjects/Core/Test/text.txt", "r");
    fgetc(f);
    gbyte * ptr = (gbyte *)f->_ptr - 1;
    fseek(f, 0, SEEK_END);
    gint size = ftell(f);
    String string = String(ptr, ftell(f), UTF8::INSTANCE);
    return string.length();
}
