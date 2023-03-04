#include "Charset.h"
#include "../String.h"
#include "../Character.h"

Charset::Charset(const String &name) {}

gint Charset::compareTo(const Charset &obj) const {
    return name().compareToIgnoreCase(obj.name());
}

gbool Charset::equals(const Object &obj) const {
    if (this == &obj)
        return true;
    if (!dynamic_cast<Charset const *>(&obj))
        return false;
    return compareTo((Charset const &) obj) == 0;
}


void Charset::set(const Object &obj) {}

CharBuffer Charset::decode(ByteBuffer &in) {
    gint n = (gint) ((gfloat)in.remaining() * averageCharsPerByte());
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
            delete [] (gchar *) out.base();
            out = o;
            continue;
        }
        break;
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
}

Charset::CoderResult Charset::decode(ByteBuffer &in, CharBuffer &out, gbool endOfInput) {
    State newState = endOfInput ? State::FINISH : State::CODING;
    if (state != State::RESET && state != State::CODING && !(endOfInput && state == State::FINISH)) {}
    state = newState;
    for (;;) {
        CoderResult cr;
        cr = decodeLoop(in, out);
        if (cr == CoderResult::OVERFLOW)
            return cr;
        if (cr == CoderResult::UNDERFLOW) {
            if (endOfInput && in.hasRemaining())
                cr = CoderResult::MALFORMED;
            else
                return cr;
        }
        ErrorAction action;
        if (cr == CoderResult::MALFORMED) {
            action = malformedAction();
        } else
            action = unmappableAction();
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
        break;
    }
    return CoderResult::UNMAPPABLE;
}

ByteBuffer Charset::encode(CharBuffer &in) {
    gint n = (gint) ((gfloat)in.remaining() * averageBytesPerChar());
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
    }
    out.flip();
    return out;
}

Charset::CoderResult Charset::encode(CharBuffer &in, ByteBuffer &out, bool endOfInput) {
    State newState = endOfInput ? State::FINISH : State::CODING;
    if (state != State::RESET && state != State::CODING && !(endOfInput && state == State::FINISH)) {}
    state = newState;
    for (;;) {
        CoderResult cr;
        cr = encodeLoop(in, out);
        if (cr == CoderResult::OVERFLOW)
            return cr;
        if (cr == CoderResult::UNDERFLOW) {
            if (endOfInput && in.hasRemaining())
                cr = CoderResult::MALFORMED;
            else
                return cr;
        }
        ErrorAction action;
        if (cr == CoderResult::MALFORMED) {
            action = malformedAction();
        } else
            action = unmappableAction();
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
        break;
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

