
from math import isnan, isinf

class ObjectPrinter:
    def __init__(self, typename: str, this):
        self._type = typename
        self._this = this
    
    def to_string(self):
        return self._type + '{...}'

class StringPrinter(ObjectPrinter):
    def to_string(self):
        this = self._this
        size = this['len']
        data = this['value']
        if size <= 0 or data.address == 0:
            return 'u""'
        try:
            if hasattr(data, 'lazy_string'):
                return data.lazy_string('utf-16BE', size << 1)
            else:
                return data.string('utf-16BE', 'String Printing Failed', size << 1)
        except:
            out = '"'
            limit = size << 1
            while limit > 0:
                b1 = data[limit-1]
                b2 = data[limit]
                limit -= 2
                c = ((b1 & 0xFF) << 8) | (b2 & 0xFF)
                try:
                    out = chr(c) + out
                except:
                    out = '?' + out
            return 'u"' + out

class CharArrayPrinter(ObjectPrinter):
    def to_string(self):
        this = self._this
        size = this['len']
        data = this['value']
        if size <= 0 or data.address == 0:
            return '[]'
        out = ']'
        limit = size << 1
        while limit > 0:
            b1 = data[limit-1]
            b2 = data[limit]
            limit -= 2
            c = ((b1 & 0xFF) << 8) | (b2 & 0xFF)
            try:
                s = ''
                if 32 <= c <= 126:
                    s = '\'' + chr(c) + '\''
                elif c > 127:
                    s = 'u\'' + chr(c) + '\''
                else:
                    s = repr(chr(c)).replace('"', '\'')
                if len(out) == 1:
                    out = s + out
                else:
                    out = s + ', ' + out

            except:
                if len(out) == 1:
                    out = '\'?\'' + out
                else:
                    out = '\'?\', ' + out
        return '[' + out
            
class BufferPrinter(ObjectPrinter):
    def to_string(self):
        this = self._this
        data = this['_buffer']
        pos = this['_position']
        limit = this['_limit']
        size = limit - pos
        if limit <= 0 or data.address == 0:
            return '""'
        if hasattr(data, 'lazy_string'):
            return data.lazy_string(length=size)
        else:
            return data.string(length=size)

class NumeralPrinter(ObjectPrinter):
    def to_string(self):
        this = self._this
        value = this['value']
        if self._type == 'Float' or self._type == 'Double':
            if isnan(value):
                return "NaN"
            elif isinf(value):
                if value > 0:
                    return "Infinity"
                else:
                    return "-Infinity"
        elif self._type == 'Boolean':
            if value == 0:
                return 'false'
            else:
                return 'true'
        elif self._type == 'Byte':
            return str(int(value))
        return str(value)

class ObjectNodePrinter(ObjectPrinter):
    def __init__(self, typename: str, this):
        super().__init__(typename, this)
        self._data = []
    
    def to_string(self):
        return 'size: ' + str(len(self._data))
    
    def children(self):
        class itr:
            def __init__(self, data:list) -> None:
                self._data = data
                self._size = len(data)
                self._cursor = 0
            
            def __next__(self):
                if self._cursor == self._size:
                    raise StopIteration
                cursor = self._cursor
                self._cursor += 1
                return self._data[cursor]

        return itr(self._data)

class ArrayListPrinter(ObjectNodePrinter):
    def __init__(self, typename: str, this):
        super().__init__(typename, this)
        data = self._this['data']
        size = self._this['len']
        capacity = self._this['capacity']
        if size > 0 and data.address != 0 and size < capacity:
            cursor = 0
            while cursor < size:
                try:
                    element = data[cursor]
                    self._data.append(('[%d]' % cursor, element[0]))
                    cursor += 1
                except:
                    break

class LinkedListPrinter(ObjectNodePrinter):
    def __init__(self, typename: str, this):
        super().__init__(typename, this)
        begin = self._this['first']
        end = self._this['last']
        size = self._this['len']
        if size > 0 and begin.address != 0 and end.address != 0:
            cursor = 0
            while cursor < size and begin.address != 0:
                try:
                    element = begin['item']
                    self._data.append(('[%d]' % cursor, element[0]))
                    cursor += 1
                    begin = begin['next']
                except:
                    break
                
class TreeMapPrinter(ObjectNodePrinter):
    def __init__(self, typename: str, this):
        super().__init__(typename, this)
        begin = self._this['root']
        size = self._this['len']
        if size > 0 and begin.address != 0:
            cursor = 0
            begin = self.__first(begin)
            while cursor < size and begin.address != 0:
                try:
                    element = begin
                    self._data.append(('%s =' % element['_key'], element['_value'][0]))
                    cursor += 1
                    begin = self.__next(begin)
                except:
                    break

    def __first(self, node):
        if node.address != 0:
            while node['left'].address != 0:
                node = node['left']
        return node

    def __next(self, node):
        if node['right'].address != 0:
            node = node['right']
            return self.__first(node)
        node1 = node
        node = node['parent']
        while node.address != 0:
            if node1.address != node['parent'].address:
                break
            node1 = node
            node = node['parent']
        return node
        
class ErrorPrinter(ObjectNodePrinter):
    def __init__(self, typename: str, this):
        super().__init__(typename, this)
        self._data = [('[Message]', self._this['_message'])]

def custom_dictionary():
    print("GDB Load Custom Printer [Core]")
    global core_printer 
    core_printer = Printer("Core")
    _1 = [
        'Collection',
        'List',
        'Set',
    ]
    _2 = [
        'Object',
        'Iterable',
        'Number',
        'Void',
        'Break',
        'Functional',
        'Function',
        'Consumer',
        'Predicate',
        'BiFunctional',
        'BiFunction',
        'BiConsumer',
        'BiPredicate',
        'Iterable',
        'Iterable2',
        'Iterator',
        'Iterator2'
    ]
    _3 = [
        'Boolean',
        'Byte',
        'Short',
        'Character',
        'Integer',
        'Enum',
        'Long',
        'Float',
        'Double',
    ]
    _4 = [
        'ByteBuffer',
        'CharBuffer',
        'IntBuffer'
    ]
    _5 = [
        'CharArray',
        'IntArray',
        'FloatArray',
        'DoubleArray',
    ]
    _6 = [
        'Error',
        'CastError',
        'CodingError',
        'IndexError',
        'IOError',
        'KeyError',
        'MemoryError',
        'StateError',
        'ValueError',
    ]
    for _type in _1:
        core_printer.add_version('', _type, ObjectNodePrinter)
    for _type in _2:
        core_printer.add_version('', _type, ObjectPrinter)
    for _type in _3:
        core_printer.add_version('', _type, NumeralPrinter)
    for _type in _4:
        core_printer.add_version('', _type, BufferPrinter)
    for _type in _5:
        core_printer.add_version('', _type, CharArrayPrinter)
    for _type in _6:
        core_printer.add_version('', _type, ErrorPrinter)

    core_printer.add_version('', 'ArrayList', ArrayListPrinter)
    core_printer.add_version('', 'LinkedList', LinkedListPrinter)
    core_printer.add_version('', 'TreeMap', TreeMapPrinter)

custom_dictionary()
