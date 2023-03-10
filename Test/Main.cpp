//
// Created by brunshweeck on 16/02/2023.
//

#include "../Collections/ArrayList.h"

void func(int i) {
    i += 2;
}

int main(int, char const *[], char const *[]) {
    ArrayList<String> arrayList = ArrayList<String>(50);
    arrayList.add("50");
    arrayList.forEach([](String const& s) {});
}
