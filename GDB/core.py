
import gdb


class core_printer:
    def __init__(self, typename: str, this: gdb.Value) -> None:
        self.typename = typename
        self.this = this

    def to_string(self) -> str:
        return self.typename + '@%d' % self.this.address


class array_printer(core_printer):
    def __init__(self, typename: str, this: gdb.Value) -> None:
        super().__init__(typename, this)
        self.size = 0

    def children(self) -> list:
        return []

    def to_string(self) -> str:
        return 'size = %d' % self.size


class value_printer(core_printer):
    def to_string(self) -> str:
        return str(self.this['value'] if not self.typename.endswith('Byte') else int(self.this['value']))


class character_printer(core_printer):
    def to_string(self) -> str:
        cp = int(self.this['value'])
        try:
            return 'u"' + chr(cp) + '"'
        except UnicodeError:
            return 'u\'\\u%.4X\'' % cp


class string_printer(core_printer):
    def chr_to_str(self, cp: int):
        try:
            s = chr(cp)
            s2 = repr(s)
            if '\\x' in s2:
                i = s2.index('\\x')
                return self.chr_to_str2(int(s2[i+2] + s2[i+3], 16))
            elif '\\' in s2:
                i = s2.index('\\')
                return self.chr_to_str2(int(s2[i+2] + s2[i+3] + s2[i+4], 8))
            else:
                return s
        except UnicodeError:
            return '\\u%.4X' % cp

    def chr_to_str2(self, cp: int):
        return '\\u%.4X' % cp

    def to_string(self) -> str:
        data = self.this['value']
        size = self.this['len']
        if size <= 0 or data.address == 0:
            return 'u\"\"'
        s: list = [
            int((data[i << 1] & 0xFF) << 8 | data[1 + i << 1] & 0xFF)
            for i in range(size)
        ]
        s2: list = []
        i = 0
        while i < size:
            cp = s[i]
            if 0xD800 <= cp <= 0xDBFF:
                cp2 = s[i+1]
                if 0xDC00 <= cp2 <= 0xDFFF:
                    i = i + 2
                    s2.append(self.chr_to_str((cp << 10) + (cp2 - 0XDC00)))
                else:
                    i = i + 1
                    s2.append(self.chr_to_str2(cp))
            elif 0xDC00 <= cp <= 0xDFFF:
                i += 1
                s2.append(self.chr_to_str2(cp))
            else:
                i = i + 1
                s2.append(self.chr_to_str(cp))
        return 'u"' + ''.join(s2) + '"'


class array_list_printer(array_printer):
    def __init__(self, typename: str, this: gdb.Value) -> None:
        super().__init__(typename, this)
        size = self.this['len']
        capacity = self.this['capacity']
        if 0 < size <= capacity:
            self.size = size

    def children(self) -> list:
        s = []
        data = self.this['data']
        if 0 < self.size and data.address != 0:
            s = [data[i][0] for i in range(self.size)]
        return s


class buffer_printer(core_printer):
    def chr_to_str(self, cp):
        try:
            s = chr(cp)
            s2 = repr(s)
            if '\\x' in s2:
                i = s2.index('\\x')
                return self.chr_to_str2(int(s2[i+2] + s2[i+3], 16))
            elif '\\' in s2:
                i = s2.index('\\')
                return self.chr_to_str2(int(s2[i+2] + s2[i+3] + s2[i+4], 8))
            else:
                return s
        except UnicodeError:
            return '\\u%.4X' % cp

    def chr_to_str2(self, cp):
        return '\\u%.4X' % cp

    def to_string(self) -> str:
        data = self.this['value']
        size = self.this['len']
        r = [(('\'%s\'' % self.chr_to_str(data[i])) if self.typename !=
              'ByteBuffer' else int(data[i])) for i in range(size)]
        return '[%s]' % r

class unknown_printer(core_printer):
    def to_string(self) -> str:
        return self.typename.split('::')[-1]

