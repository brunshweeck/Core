#include <cassert>
#include "Charset.h"
#include "../String.h"
#include "../Character.h"
#include "../MemoryError.h"
#include "../CodingError.h"
#include "../CodingError.h"
#include "../CodingError.h"
#include "../StateError.h"
#include "../Enum.h"
#include "UTF8.h"

Charset::Charset(const String &name) {}

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

void Charset::set(const Object &obj) {}

static gint _initEnumNames() {
    Enum<Charset::CoderResult>::customAlias = [](Charset::CoderResult cr) -> String {
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
    Enum<Charset::State>::customAlias = [](Charset::State s) -> String {
        switch (s) {
            case Charset::State::RESET:
                return "RESET";
            case Charset::State::CODING:
                return "CODING";
            case Charset::State::FINISH:
                return "FINISH";
            case Charset::State::FLUSHED:
                return "FLUSHED";
        }
        return "";
    };
    Enum<Charset::ErrorAction>::customAlias = [](Charset::ErrorAction action) -> String {
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
            cr = flush(out);
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
                throw CodingError::malformed(errorLength);
            case CoderResult::UNMAPPABLE:
                throw CodingError::unmappable(errorLength);
        }
    }
    out.flip();
    return out;
}

Charset::CoderResult Charset::flush(Buffer const &) {
    if (state == State::FINISH)
        state = State::FLUSHED;
    return CoderResult::UNDERFLOW;
}

void Charset::reset() {
    state = State::RESET;
    errorLength = 0;
}

Charset::CoderResult Charset::decode(ByteBuffer &in, CharBuffer &out, gbool endOfInput) {
    _;
    State newState = endOfInput ? State::FINISH : State::CODING;
    if (state != State::RESET && state != State::CODING && !(endOfInput && state == State::FINISH))
        throw StateError("Current = " + Enum<State>::toString(state) + ", New = " + Enum<State>::toString(newState));
    state = newState;
    for (;;) {
        CoderResult cr;
        cr = decodeLoop(in, out);
        if (cr == CoderResult::OVERFLOW)
            return cr;
        if (cr == CoderResult::UNDERFLOW) {
            if (endOfInput && in.hasRemaining()) {
                errorLength = in.remaining();
                cr = CoderResult::MALFORMED;
            }
            else
                return cr;
        }
        ErrorAction action = ErrorAction::REPORT;
        if (cr == CoderResult::MALFORMED) {
            action = malformedAction();
        } else if(cr == CoderResult::UNMAPPABLE)
            action = unmappableAction();
        else
            assert(false);
        if (action == ErrorAction::REPORT)
            return cr;
        if (action == ErrorAction::REPLACE) {
            gint length = decoderReplacement[2] ? 3 :
                          decoderReplacement[1] ? 2 : 1;
            if (out.remaining() < length)
                return CoderResult::OVERFLOW;
            for (int i = 0; i < length; ++i)
                out.put(decoderReplacement[i]);
        }
        if (action == ErrorAction::IGNORE || action == ErrorAction::REPLACE) {
            in.position(in.position() + errorLength);
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
    reset();
    for (;;) {
        CoderResult cr = in.hasRemaining() ? encode(in, out, true) : CoderResult::UNDERFLOW;
        if (cr == CoderResult::UNDERFLOW)
            cr = flush(out);
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
                throw CodingError::malformed(errorLength);
            case CoderResult::UNMAPPABLE:
                throw CodingError::malformed(errorLength);
            default:
                throw CodingError();
        }
    }
    out.flip();
    return out;
}

Charset::CoderResult Charset::encode(CharBuffer &in, ByteBuffer &out, bool endOfInput) {
    _;
    State newState = endOfInput ? State::FINISH : State::CODING;
    if (state != State::RESET && state != State::CODING && !(endOfInput && state == State::FINISH)) {
        throw StateError("Current = " + Enum<State>::toString(state) + ", New = " + Enum<State>::toString(newState));
    }
    state = newState;
    for (;;) {
        CoderResult cr;
        cr = encodeLoop(in, out);
        if (cr == CoderResult::OVERFLOW)
            return cr;
        if (cr == CoderResult::UNDERFLOW) {
            if (endOfInput && in.hasRemaining()) {
                errorLength = in.remaining();
                cr = CoderResult::MALFORMED;
            }
            else
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
            gint length = encoderReplacement[4] ? 5 :
                          encoderReplacement[3] ? 4 :
                          encoderReplacement[2] ? 3 :
                          encoderReplacement[1] ? 2 : 1;
            if (out.remaining() < length)
                return CoderResult::OVERFLOW;
            for (int i = 0; i < length; ++i)
                out.put(encoderReplacement[i]);
        }
        if (action == ErrorAction::IGNORE || action == ErrorAction::REPLACE) {
            in.position(in.position() + errorLength);
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

class PrivateCharset final : public Charset {
public:
    PrivateCharset(ErrorAction action, CoderResult result, Charset &charset) :
            Charset(charset.name()), action(action), result(result), charset(charset) {}

    String name() const override {
        return charset.name();
    }

    ErrorAction malformedAction() const override {
        if (result == Charset::CoderResult::MALFORMED)
            return action;
        return charset.malformedAction();
    }

    ErrorAction unmappableAction() const override {
        if (result == Charset::CoderResult::UNMAPPABLE)
            return action;
        return charset.malformedAction();
    }

    CoderResult decodeLoop(ByteBuffer &src, CharBuffer &dst) override {
        return charset.decodeLoop(src, dst);
    }

    CoderResult encodeLoop(CharBuffer &src, ByteBuffer &dst) override {
        return charset.encodeLoop(src, dst);
    }

    gfloat averageCharsPerByte() const override {
        return charset.averageCharsPerByte();
    }

    gfloat averageBytesPerChar() const override {
        return charset.averageBytesPerChar();
    }

    CharBuffer decode(ByteBuffer &in) override {
        return Charset::decode(in);
    }

    ByteBuffer encode(CharBuffer &in) override {
        return Charset::encode(in);
    }

    String toString() const override {
        return Charset::toString();
    }

    gint compareTo(const Charset &obj) const override {
        return charset.compareTo(obj);
    }

    gbool equals(const Object &obj) const override {
        return charset.equals(obj);
    }

    gbool contains(const Charset &cs) const override {
        return charset.contains(cs);
    }

    gbool canEncode(gchar c) const override {
        return Charset::canEncode(c);
    }

    Charset &onMalformed(ErrorAction errorAction) override {
        if (errorAction == malformedAction())
            return *this;
        if (errorAction == action && result == Charset::CoderResult::MALFORMED)
            return *this;
        return Charset::onMalformed(errorAction);
    }

    Charset &onUnmapped(ErrorAction errorAction) override {
        if (errorAction == unmappableAction())
            return *this;
        if (result == Charset::CoderResult::UNMAPPABLE && action == errorAction)
            return *this;
        return Charset::onUnmapped(errorAction);
    }

    Object &clone() const override {
        try {
            return *new PrivateCharset(action, result, charset);
        } catch (...) {
            throw MemoryError();
        }
    }

private:
    ErrorAction action;
    CoderResult result;
    Charset &charset;
};

Charset &Charset::onMalformed(ErrorAction action) {
    if (action == malformedAction())
        return *this;
    try {
        return *new PrivateCharset(action, CoderResult::MALFORMED, *this);
    } catch (...) {
        throw MemoryError();
    }
}

Charset &Charset::onUnmapped(ErrorAction action) {
    if (action == unmappableAction())
        return *this;
    try {
        return *new PrivateCharset(action, CoderResult::UNMAPPABLE, *this);
    } catch (...) {
        throw MemoryError();
    }
}

Charset &Charset::forName(const String &charset) {
    return UTF8::INSTANCE;
}