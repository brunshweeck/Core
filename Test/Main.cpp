//
// Created by brunshweeck on 16/02/2023.
//

#include "../Collections/ArrayList.h"
#include "../Charset/UTF8.h"
#include "../Collections/LinkedList.h"
#include "../Collections/CharArray.h"

int& aaa(int b) {
    static int i;
    i = b;
    return i;
}

template<class T, CORE_SIZE S>
void ff(T(&&v)[S]) {
    for (const auto &item: v){}
}

int main() {
    ff<float>({1,2,3,4,5});
    LinkedList<Integer> ll{{1.0, 2, 4}};
    return 0;
}
