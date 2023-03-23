//
// Created by brunshweeck on 16/02/2023.
//

#include "../Enum.h"
#include "../Collections/ArrayList.h"
#include "../Collections/CharArray.h"
#include "../Collections/LinkedList.h"
#include "../Collections/TreeMap.h"

using namespace std;
int main() {
    ArrayList<Integer> a = {};
    a.add(20);
    a.add(0, 10);
    a.add(30);
    LinkedList<Integer> l = {};
    l.add(0, 10);
    l.add(20);
    l.add(30);
    TreeMap<Integer, String> m = {};
    m.add(0, "20");
    m.add(0, "10");
    m.add(m.size(), "30");
    //
    return 0;
}
