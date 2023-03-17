//
// Created by brunshweeck on 16/03/2023.
//

#include "KeyError.h"



KeyError::KeyError(const Object &key): ValueError("key not found: " + key.toString()) {}

KeyError::KeyError(): ValueError("No such key") {}

