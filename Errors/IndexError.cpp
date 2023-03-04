//
// Created by brunshweeck on 26/02/2023.
//

#include "IndexError.h"
#include "../String.h"

IndexError::IndexError(gint index) : index(index) {}

IndexError::IndexError(gint index, gint maxIndex) :
        index(index), maxIndex(maxIndex), maxIsSet(true) {}

IndexError::IndexError(gint index, gint minIndex, gint maxIndex) :
        index(index), minIndex(minIndex), maxIndex(maxIndex), maxIsSet(true), minIsSet(true) {}

String IndexError::message() const {
    if (!minIsSet && !maxIsSet)
        return String("Index out of range: ");
    if(minIsSet && maxIsSet)
        return "Index out if range :";
    return "Index out if range :";
}
