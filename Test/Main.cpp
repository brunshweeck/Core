//
// Created by brunshweeck on 16/02/2023.
//

#include "../Collections/Collection.h"
#include "../Function/Consumer.h"
#include "../Enum.h"
#include "../Function/Predicate.h"

void func(int i) {
    i += 2;
}

int main(int, char const *[], char const *[]) {
    ValueError error = ValueError(u"啦送日俄的怕");
    auto a = error.message();
    throw error;
}
