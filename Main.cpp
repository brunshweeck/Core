//
// Created by brunshweeck on 16/02/2023.
//

#include "Class.h"
#include "Float.h"
#include "Double.h"
#include "Boolean.h"
#include "Enum.h"
#include "Integer.h"
#include "Short.h"
#include "Byte.h"
#include "Character.h"
#include "Long.h"
#include "String.h"
#include "Charset/MS1250.h"

enum A {
    AA = 128
};
enum class B {
    BB = 512
};

int main(int, char const *[], char const *[]) {
//    auto a = Float(Float::MAX);
//    auto b = Float(Float::MIN);
//    auto c = Double(Double::MAX);
//    auto d = Double(Double::MIN);
//    Boolean e = Boolean::TRUE;
//    Boolean f = Boolean::FALSE;
//    auto g = Byte(Byte::MAX);
//    auto h = Byte(Byte::MIN);
//    auto i = Short(Short::MAX);
//    auto j = Short(Short::MIN);
//    auto k = Integer(Integer::MAX);
//    auto l = Integer(Integer::MIN);
//    auto m = Long(Long::MAX);
//    auto n = Long(Long::MIN);
//    auto o = Character(Character::MAX);
//    auto p = Character(Character::MIN);
    String string = "aáàâãä";
    auto d = string.toUpperCase();
    auto e = string.toLowerCase();
    auto f = string.toTitleCase();
    return 0;
}
