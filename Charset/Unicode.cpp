//
// Created by brunshweeck on 25/02/2023.
//

#include "Unicode.h"
#include "../String.h"
#include "UTF8.h"
#include "UTF16.h"
#include "UTF32.h"

Unicode::Unicode(const String &name) : Charset(name) {}

gbool Unicode::contains(const Charset &cs) const {
    return dynamic_cast<UTF8 const *>(&cs) != nullptr
           || dynamic_cast<UTF16 const *>(&cs) != nullptr
           || dynamic_cast<UTF32 const *>(&cs) != nullptr
           || cs.name().equals("GBK") != 0
           || cs.name().equals("GB18030")
           || cs.name().equals("ISO-8859-2")
           || cs.name().equals("ISO-8859-3")
           || cs.name().equals("ISO-8859-4")
           || cs.name().equals("ISO-8859-5")
           || cs.name().equals("ISO-8859-6")
           || cs.name().equals("ISO-8859-7")
           || cs.name().equals("ISO-8859-8")
           || cs.name().equals("ISO-8859-9")
           || cs.name().equals("ISO-8859-13")
           || cs.name().equals("JIS_X0201")
           || cs.name().equals("x-JIS0208")
           || cs.name().equals("JIS_X0212-1990")
           || cs.name().equals("GB2312")
           || cs.name().equals("EUC-KR")
           || cs.name().equals("x-EUC-TW")
           || cs.name().equals("EUC-JP")
           || cs.name().equals("x-euc-jp-linux")
           || cs.name().equals("KOI8-R")
           || cs.name().equals("TIS-620")
           || cs.name().equals("x-ISCII91")
           || cs.name().equals("Windows-1251")
           || cs.name().equals("Windows-1253")
           || cs.name().equals("Windows-1254")
           || cs.name().equals("Windows-1255")
           || cs.name().equals("Windows-1256")
           || cs.name().equals("Windows-1257")
           || cs.name().equals("Windows-1258")
           || cs.name().equals("Windows-932")
           || cs.name().equals("Windows-936")
           || cs.name().equals("Windows-949")
           || cs.name().equals("Windows-950")
           || cs.name().equals("Windows-31j")
           || cs.name().equals("Big5")
           || cs.name().equals("Big5-HKSCS")
           || cs.name().equals("MS950-HKSCS")
           || cs.name().equals("ISO-2022-JP")
           || cs.name().equals("ISO-2022-KR")
           || cs.name().equals("ISO-2022-CN-CNS")
           || cs.name().equals("ISO-2022-CN-GB")
           || cs.name().equals("Johab")
           || cs.name().equals("Shift-JIS");
}
