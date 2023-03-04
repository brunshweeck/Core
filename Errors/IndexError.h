//
// Created by brunshweeck on 26/02/2023.
//

#ifndef CORE_INDEXERROR_H
#define CORE_INDEXERROR_H


#include "Error.h"

class IndexError: public Error {
public:
    CORE_EXPLICIT IndexError(gint index);

    IndexError(gint index, gint maxIndex);

    IndexError(gint index, gint minIndex, gint maxIndex);

    String message() const override;

private:
    gint index, minIndex, maxIndex;
    gbool minIsSet = false;
    gbool maxIsSet = false;
};


#endif //CORE_INDEXERROR_H
