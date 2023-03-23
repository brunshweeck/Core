#include <cassert>
#include "Charset.h"
#include "../Character.h"
#include "../MemoryError.h"
#include "../Enum.h"

gint Charset::CODING_ERROR_LENGTH = 0;

gint Charset::compareTo(const Charset &obj) const {
    return name().compareToIgnoreCase(obj.name());
}

gbool Charset::equals(const Object &obj) const {
    if (this == &obj)
        return true;
    if (!dynamic_cast<Charset const *>(&obj))
        return false;
    Charset const &cs = (Charset const &) obj;
    return name().equalsIgnoreCase(cs.name());
}

static gint _initEnumNames() {
    Enum<Charset::CoderResult>::alias = [](Charset::CoderResult cr) -> String {
        switch (cr) {
            case Charset::CoderResult::UNDERFLOW:
                return u"UNDERFLOW";
            case Charset::CoderResult::OVERFLOW:
                return u"OVERFLOW";
            case Charset::CoderResult::MALFORMED:
                return u"MALFORMED";
            case Charset::CoderResult::UNMAPPABLE:
                return u"UNMAPPABLE";
        }
        return "";
    };

    Enum<Charset::ErrorAction>::alias = [](Charset::ErrorAction action) -> String {
        switch (action) {
            case Charset::ErrorAction::IGNORE:
                return "IGNORE";
            case Charset::ErrorAction::REPORT:
                return "REPORT";
            case Charset::ErrorAction::REPLACE:
                return "REPLACE";
        }
        return "";
    };

    return 0;
}

static gint _ = _initEnumNames();

CharBuffer Charset::decode(ByteBuffer &in) {
    gint n = (gint) ((gfloat) in.remaining() * averageCharsPerByte());
    CharBuffer out = CharBuffer(n);
    if (n == 0 || in.remaining() == 0)
        return out;
    for (;;) {
        CoderResult cr = in.hasRemaining() ? decode(in, out, true) : CoderResult::UNDERFLOW;
        if (cr == CoderResult::UNDERFLOW)
            break;
        if (cr == CoderResult::OVERFLOW) {
            n = 2 * n + 1;
            CharBuffer o = CharBuffer(n);
            out.flip();
            o.put(out);
            delete[] (gchar *) out.base();
            out = o;
            continue;
        }
        switch (cr) {
            case CoderResult::UNDERFLOW:
                throw CodingError::underflow();
            case CoderResult::OVERFLOW:
                throw CodingError::overflow();
            case CoderResult::MALFORMED:
                throw CodingError::malformed(CODING_ERROR_LENGTH);
            case CoderResult::UNMAPPABLE:
                throw CodingError::unmappable(CODING_ERROR_LENGTH);
        }
    }
    out.flip();
    return out;
}

Charset::CoderResult Charset::decode(ByteBuffer &in, CharBuffer &out, gbool endOfInput) {
    _ = 5;
    for (;;) {
        CoderResult cr;
        cr = decodeLoop(in, out);
        if (cr == CoderResult::OVERFLOW)
            return cr;
        if (cr == CoderResult::UNDERFLOW) {
            if (endOfInput && in.hasRemaining()) {
                CODING_ERROR_LENGTH = in.remaining();
                cr = CoderResult::MALFORMED;
            } else
                return cr;
        }
        ErrorAction action = ErrorAction::REPORT;
        if (cr == CoderResult::MALFORMED) {
            action = malformedAction();
        } else if (cr == CoderResult::UNMAPPABLE)
            action = unmappableAction();
        else
            assert(false);
        if (action == ErrorAction::REPORT)
            return cr;
        if (action == ErrorAction::REPLACE) {
            gint length = REPLACEMENT_CHARS[2] ? 3 :
                          REPLACEMENT_CHARS[1] ? 2 : 1;
            if (out.remaining() < length)
                return CoderResult::OVERFLOW;
            for (int i = 0; i < length; ++i)
                out.put(REPLACEMENT_CHARS[i]);
        }
        if (action == ErrorAction::IGNORE || action == ErrorAction::REPLACE) {
            in.position(in.position() + CODING_ERROR_LENGTH);
            continue;
        }
        assert(false);
    }
    return CoderResult::UNMAPPABLE;
}

ByteBuffer Charset::encode(CharBuffer &in) {
    gint n = (gint) ((gfloat) in.remaining() * averageBytesPerChar());
    ByteBuffer out = ByteBuffer(n);
    if (n == 0 && in.remaining() == 0)
        return out;
    CODING_ERROR_LENGTH = 0;
    for (;;) {
        CoderResult cr = in.hasRemaining() ? encode(in, out, true) : CoderResult::UNDERFLOW;
        if (cr == CoderResult::UNDERFLOW)
            break;
        if (cr == CoderResult::OVERFLOW) {
            n = 2 * n + 1;
            ByteBuffer o = ByteBuffer(n);
            out.flip();
            o.put(out);
            out = o;
            continue;
        }
        switch (cr) {
            case CoderResult::UNDERFLOW:
                throw CodingError::underflow();
            case CoderResult::OVERFLOW:
                throw CodingError::overflow();
            case CoderResult::MALFORMED:
                throw CodingError::malformed(CODING_ERROR_LENGTH);
            case CoderResult::UNMAPPABLE:
                throw CodingError::malformed(CODING_ERROR_LENGTH);
            default:
                throw CodingError();
        }
    }
    out.flip();
    return out;
}

Charset::CoderResult Charset::encode(CharBuffer &in, ByteBuffer &out, bool endOfInput) {
    _ = 8;
    for (;;) {
        CoderResult cr;
        cr = encodeLoop(in, out);
        if (cr == CoderResult::OVERFLOW)
            return cr;
        if (cr == CoderResult::UNDERFLOW) {
            if (endOfInput && in.hasRemaining()) {
                CODING_ERROR_LENGTH = in.remaining();
                cr = CoderResult::MALFORMED;
            } else
                return cr;
        }
        ErrorAction action = ErrorAction::REPORT;
        if (cr == CoderResult::MALFORMED) {
            action = malformedAction();
        } else if (cr == CoderResult::UNMAPPABLE)
            action = unmappableAction();
        else
            assert(false);
        if (action == ErrorAction::REPORT)
            return cr;
        if (action == ErrorAction::REPLACE) {
            gint length = REPLACEMENT_BYTES[4] ? 5 :
                          REPLACEMENT_BYTES[3] ? 4 :
                          REPLACEMENT_BYTES[2] ? 3 :
                          REPLACEMENT_BYTES[1] ? 2 : 1;
            if (out.remaining() < length)
                return CoderResult::OVERFLOW;
            for (int i = 0; i < length; ++i)
                out.put(REPLACEMENT_BYTES[i]);
        }
        if (action == ErrorAction::IGNORE || action == ErrorAction::REPLACE) {
            in.position(in.position() + CODING_ERROR_LENGTH);
            continue;
        }
        assert(false);
    }
    return CoderResult::UNMAPPABLE;
}

Charset::ErrorAction Charset::malformedAction() const {
    return ErrorAction::REPORT;
}

Charset::ErrorAction Charset::unmappableAction() const {
    return ErrorAction::REPORT;
}

gbool Charset::canEncode(gchar c) const {
    return !Character::isSurrogate(c);
}

String Charset::toString() const {
    return name();
}

class CustomizableCharset : public Charset {
public:
    CORE_FAST static gint MALFORMED_REPORT_MASK = 0;
    CORE_FAST static gint MALFORMED_REPLACE_MASK = 1;
    CORE_FAST static gint MALFORMED_IGNORE_MASK = 2;
    CORE_FAST static gint UNMAPPED_REPORT_MASK = 3;
    CORE_FAST static gint UNMAPPED_REPLACE_MASK = 4;
    CORE_FAST static gint UNMAPPED_IGNORE_MASK = 5;
    gint mask = 0;
    Charset *cs = nullptr;

    CustomizableCharset(ErrorAction a, CoderResult cr, Charset const &charset) {
        cs = Class<CustomizableCharset>::hasInstance(charset) ?
             ((CustomizableCharset const &) charset).cs : &(Charset &) charset;
        if (!Class<Charset>::hasInstance(*this->cs))
            throw MemoryError("It not cloneable charset object");
        if (cr == Charset::CoderResult::MALFORMED)
            switch (a) {
                case ErrorAction::IGNORE:
                    mask = 1 << MALFORMED_IGNORE_MASK;
                    break;
                case ErrorAction::REPORT:
                    mask = 1 << MALFORMED_REPORT_MASK;
                    break;
                case ErrorAction::REPLACE:
                    mask = 1 << MALFORMED_REPLACE_MASK;
                    break;
            }
        else
            switch (a) {
                case ErrorAction::IGNORE:
                    mask = 1 << UNMAPPED_IGNORE_MASK;
                    break;
                case ErrorAction::REPORT:
                    mask = 1 << UNMAPPED_REPORT_MASK;
                    break;
                case ErrorAction::REPLACE:
                    mask = 1 << UNMAPPED_REPLACE_MASK;
                    break;
            }

    }

    String name() const override {
        return cs->name();
    }

    ErrorAction malformedAction() const override {
        return
                (mask >> MALFORMED_REPORT_MASK) & 1 ? ErrorAction::REPORT :
                (mask >> MALFORMED_REPLACE_MASK) & 1 ? ErrorAction::REPLACE : ErrorAction::IGNORE;
    }

    ErrorAction unmappableAction() const override {
        return
                (mask >> UNMAPPED_REPORT_MASK) & 1 ? ErrorAction::REPORT :
                (mask >> UNMAPPED_REPLACE_MASK) & 1 ? ErrorAction::REPLACE : ErrorAction::IGNORE;
    }

    CoderResult decodeLoop(ByteBuffer &src, CharBuffer &dst) override {
        return cs->decodeLoop(src, dst);
    }

    CoderResult encodeLoop(CharBuffer &src, ByteBuffer &dst) override {
        return cs->encodeLoop(src, dst);
    }

    gfloat averageCharsPerByte() const override {
        return cs->averageCharsPerByte();
    }

    gfloat averageBytesPerChar() const override {
        return cs->averageBytesPerChar();
    }

    String toString() const override {
        return cs->toString();
    }

    gint compareTo(const Charset &obj) const override {
        return cs->compareTo(obj);
    }

    gbool equals(const Object &obj) const override {
        return cs->equals(obj);
    }

    gbool contains(const Charset &charset) const override {
        return cs->contains(charset);
    }

    gbool canEncode(gchar c) const override {
        return cs->canEncode(c);
    }

    Charset &onMalformed(ErrorAction action) override {
        if (action == malformedAction())
            return *this;
        switch (unmappableAction()) {
            case ErrorAction::IGNORE:
                mask = 1 << UNMAPPED_IGNORE_MASK;
                break;
            case ErrorAction::REPORT:
                mask = 1 << UNMAPPED_REPORT_MASK;
                break;
            case ErrorAction::REPLACE:
                mask = 1 << UNMAPPED_REPLACE_MASK;
                break;
        }
        switch (action) {
            case ErrorAction::IGNORE:
                mask |= 1 << MALFORMED_IGNORE_MASK;
                break;
            case ErrorAction::REPORT:
                mask |= 1 << MALFORMED_REPORT_MASK;
                break;
            case ErrorAction::REPLACE:
                mask |= 1 << MALFORMED_REPLACE_MASK;
                break;
        }
        return *this;
    }

    Charset &onUnmapped(ErrorAction action) override {
        if (action == unmappableAction())
            return *this;
        switch (malformedAction()) {
            case ErrorAction::IGNORE:
                mask = 1 << MALFORMED_IGNORE_MASK;
                break;
            case ErrorAction::REPORT:
                mask = 1 << MALFORMED_REPORT_MASK;
                break;
            case ErrorAction::REPLACE:
                mask = 1 << MALFORMED_REPLACE_MASK;
                break;
        }
        switch (action) {
            case ErrorAction::IGNORE:
                mask |= 1 << UNMAPPED_IGNORE_MASK;
                break;
            case ErrorAction::REPORT:
                mask |= 1 << UNMAPPED_REPORT_MASK;
                break;
            case ErrorAction::REPLACE:
                mask |= 1 << UNMAPPED_REPLACE_MASK;
                break;
        }
        return *this;
    }

    Object &clone() const override {
        try { return *new CustomizableCharset(*this); } catch (...) { throw MemoryError(); }
    }
};

Charset &Charset::onMalformed(ErrorAction action) {
    if (action == malformedAction())
        return *this;
    try { return *new CustomizableCharset(action, CoderResult::MALFORMED, *this); }
    catch (...) { throw MemoryError(); }
}

Charset &Charset::onUnmapped(ErrorAction action) {
    if (action == unmappableAction())
        return *this;
    try { return *new CustomizableCharset(action, CoderResult::UNMAPPABLE, *this); }
    catch (...) { throw MemoryError(); }
}
