/*
 *  Copyright (c) 2014 Dmitry Kazakov <dimula73@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef __K_UNDO2_MAGIC_STRING_H
#define __K_UNDO2_MAGIC_STRING_H

#include <QString>
#include <klocale.h>

#include "kundo2_export.h"
#include <boost/operators.hpp>


/**
 * \class KUndo2MagicString is a special wrapper for a string that is
 * going to passed to a KUndo2Command and be later shown in the undo
 * history and undo action in menu. The strings like that must have
 * (qtundo-format) context to let translators know that they are
 * allowed to use magic split in them.
 *
 * Magic split is used in some languages to split the message in the
 * undo history docker (which is either verb or noun in nominative)
 * and the message in undo/redo actions (which is usually a noun in
 * accusative). When the translator needs it he, splits two
 * translations with '\n' symbol and the magig string will recognize
 * it.
 *
 * NOTE: KUndo2MagicString will never support concatenation operators,
 *       because in many languages you cannot combine words without
 *       knowing the proper case.
 */
class KUNDO2_EXPORT KUndo2MagicString : boost::equality_comparable<KUndo2MagicString>
{
public:
    /**
     * Construct an empty string. Note that you cannot create a
     * non-empy string without special functions, all the calls to which
     * are processed by xgettext.
     */
    explicit KUndo2MagicString();

    /**
     * Fetch the main translated string. That is the one that goes to
     * undo history and resembles the action name in verb/nominative
     */
    QString toString() const;

    /**
     * Fetch the secondary string which will go to the undo/redo
     * action.  This is usually a noun in accusative. If the
     * translator didn't provide a secondary string, toString() and
     * toSecondaryString() return the same values.
     */
    QString toSecondaryString() const;

    /**
     * \return true if the contained string is empty
     */
    bool isEmpty() const;

    // the != counterpart is provided by boost
    bool operator==(const KUndo2MagicString &rhs) const;

private:
    friend QDebug operator<<(QDebug dbg, const KUndo2MagicString &v);

private:
    /**
     * Construction of a magic string is allowed only with the means
     * of speacial macros which resemble their kde-wide counterparts
     */
    explicit KUndo2MagicString(const QString &text);


    friend KUndo2MagicString kundo2_noi18n (const QString &text);
    template <typename A1>
        friend KUndo2MagicString kundo2_noi18n (const char *text, const A1 &a1);
    template <typename A1, typename A2>
        friend KUndo2MagicString kundo2_noi18n (const char *text, const A1 &a1, const A2 &a2);
    template <typename A1, typename A2, typename A3>
        friend KUndo2MagicString kundo2_noi18n (const char *text, const A1 &a1, const A2 &a2, const A3 &a3);
    template <typename A1, typename A2, typename A3, typename A4>
        friend KUndo2MagicString kundo2_noi18n (const char *text, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4);


    friend KUndo2MagicString kundo2_i18n (const char *text);
    template <typename A1>
        friend KUndo2MagicString kundo2_i18n (const char *text, const A1 &a1);
    template <typename A1, typename A2>
        friend KUndo2MagicString kundo2_i18n (const char *text, const A1 &a1, const A2 &a2);
    template <typename A1, typename A2, typename A3>
        friend KUndo2MagicString kundo2_i18n (const char *text, const A1 &a1, const A2 &a2, const A3 &a3);
    template <typename A1, typename A2, typename A3, typename A4>
        friend KUndo2MagicString kundo2_i18n (const char *text, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4);


    friend KUndo2MagicString kundo2_i18nc (const char *ctxt, const char *text);
    template <typename A1>
        friend KUndo2MagicString kundo2_i18nc (const char *ctxt, const char *text, const A1 &a1);
    template <typename A1, typename A2>
        friend KUndo2MagicString kundo2_i18nc (const char *ctxt, const char *text, const A1 &a1, const A2 &a2);
    template <typename A1, typename A2, typename A3>
        friend KUndo2MagicString kundo2_i18nc (const char *ctxt, const char *text, const A1 &a1, const A2 &a2, const A3 &a3);


    template <typename A1>
        friend KUndo2MagicString kundo2_i18np (const char *sing, const char *plur, const A1 &a1);
    template <typename A1, typename A2>
        friend KUndo2MagicString kundo2_i18np (const char *sing, const char *plur, const A1 &a1, const A2 &a2);
    template <typename A1, typename A2, typename A3>
        friend KUndo2MagicString kundo2_i18np (const char *sing, const char *plur, const A1 &a1, const A2 &a2, const A3 &a3);


    template <typename A1>
        friend KUndo2MagicString kundo2_i18ncp (const char *ctxt, const char *sing, const char *plur, const A1 &a1);
    template <typename A1, typename A2>
        friend KUndo2MagicString kundo2_i18ncp (const char *ctxt, const char *sing, const char *plur, const A1 &a1, const A2 &a2);
    template <typename A1, typename A2, typename A3>
        friend KUndo2MagicString kundo2_i18ncp (const char *ctxt, const char *sing, const char *plur, const A1 &a1, const A2 &a2, const A3 &a3);

private:
    QString m_text;
};

KUNDO2_EXPORT QDebug operator<<(QDebug dbg, const KUndo2MagicString &v);


/**
 * This is a special wrapper to a string which tells explicitly
 * that we don't need a translation for a given string. It is used
 * either in testing or internal commands, which don't go to the
 * stack directly.
 */
inline KUndo2MagicString kundo2_noi18n (const QString &text) {
    return KUndo2MagicString(text);
}

template <typename A1>
inline KUndo2MagicString kundo2_noi18n (const char *text, const A1 &a1) {
    return KUndo2MagicString(QString(text).arg(a1));
}

template <typename A1, typename A2>
    inline KUndo2MagicString kundo2_noi18n (const char *text, const A1 &a1, const A2 &a2) {
    return KUndo2MagicString(QString(text).arg(a1).arg(a2));
}

template <typename A1, typename A2, typename A3>
    inline KUndo2MagicString kundo2_noi18n (const char *text, const A1 &a1, const A2 &a2, const A3 &a3) {
    return KUndo2MagicString(QString(text).arg(a1).arg(a2).arg(a3));
}

template <typename A1, typename A2, typename A3, typename A4>
    inline KUndo2MagicString kundo2_noi18n (const char *text, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4) {
    return KUndo2MagicString(QString(text).arg(a1).arg(a2).arg(a3).arg(a4));
}

/**
 * Same as ki18n, but is supposed to work with strings going to
 * undo stack
 */

inline KUndo2MagicString kundo2_i18n (const char *text) {
    return KUndo2MagicString(i18nc("(qtundo-format)", text));
}

template <typename A1>
inline KUndo2MagicString kundo2_i18n (const char *text, const A1 &a1) {
    return KUndo2MagicString(i18nc("(qtundo-format)", text, a1));
}

template <typename A1, typename A2>
inline KUndo2MagicString kundo2_i18n (const char *text, const A1 &a1, const A2 &a2) {
    return KUndo2MagicString(i18nc("(qtundo-format)", text, a1, a2));
}

template <typename A1, typename A2, typename A3>
inline KUndo2MagicString kundo2_i18n (const char *text, const A1 &a1, const A2 &a2, const A3 &a3) {
    return KUndo2MagicString(i18nc("(qtundo-format)", text, a1, a2, a3));
}

template <typename A1, typename A2, typename A3, typename A4>
    inline KUndo2MagicString kundo2_i18n (const char *text, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4) {
    return KUndo2MagicString(i18nc("(qtundo-format)", text, a1, a2, a3, a4));
}

inline QString prependContext(const char *ctxt) {
    return QString("(qtundo-format) %1").arg(ctxt);
}

/**
 * Same as ki18nc, but is supposed to work with strings going to
 * undo stack
 */
inline KUndo2MagicString kundo2_i18nc (const char *ctxt, const char *text) {
    return KUndo2MagicString(i18nc(prependContext(ctxt).toLatin1().data(), text));
}

template <typename A1>
inline KUndo2MagicString kundo2_i18nc (const char *ctxt, const char *text, const A1 &a1) {
    return KUndo2MagicString(i18nc(prependContext(ctxt).toLatin1().data(), text, a1));
}

template <typename A1, typename A2>
inline KUndo2MagicString kundo2_i18nc (const char *ctxt, const char *text, const A1 &a1, const A2 &a2) {
    return KUndo2MagicString(i18nc(prependContext(ctxt).toLatin1().data(), text, a1, a2));
}

template <typename A1, typename A2, typename A3>
inline KUndo2MagicString kundo2_i18nc (const char *ctxt, const char *text, const A1 &a1, const A2 &a2, const A3 &a3) {
    return KUndo2MagicString(i18nc(prependContext(ctxt).toLatin1().data(), text, a1, a2, a3));
}

template <typename A1, typename A2, typename A3, typename A4>
    inline KUndo2MagicString kundo2_i18nc (const char *ctxt, const char *text, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4) {
    return KUndo2MagicString(i18nc(prependContext(ctxt).toLatin1().data(), text, a1, a2, a3, a4));
}

/**
 * Same as ki18np, but is supposed to work with strings going to
 * undo stack
 */

template <typename A1>
inline KUndo2MagicString kundo2_i18np (const char *sing, const char *plur, const A1 &a1)
{
    return KUndo2MagicString(i18ncp("(qtundo-format)", sing, plur, a1));
}

template <typename A1, typename A2>
inline KUndo2MagicString kundo2_i18np (const char *sing, const char *plur, const A1 &a1, const A2 &a2)
{
    return i18ncp("(qtundo-format)", sing, plur, a1, a2);
}

template <typename A1, typename A2, typename A3>
inline KUndo2MagicString kundo2_i18np (const char *sing, const char *plur, const A1 &a1, const A2 &a2, const A3 &a3)
{
    return i18ncp("(qtundo-format)", sing, plur, a1, a2, a3);
}

template <typename A1, typename A2, typename A3, typename A4>
    inline KUndo2MagicString kundo2_i18np (const char *sing, const char *plur, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4)
{
    return i18ncp("(qtundo-format)", sing, plur, a1, a2, a3, a4);
}


/**
 * Same as ki18ncp, but is supposed to work with strings going to
 * undo stack
 */
template <typename A1>
inline KUndo2MagicString kundo2_i18ncp (const char *ctxt, const char *sing, const char *plur, const A1 &a1)
{
    return KUndo2MagicString(i18ncp(prependContext(ctxt).toLatin1().data(), sing, plur, a1));
}

template <typename A1, typename A2>
inline KUndo2MagicString kundo2_i18ncp (const char *ctxt, const char *sing, const char *plur, const A1 &a1, const A2 &a2)
{
    return i18ncp(prependContext(ctxt).toLatin1().data(), sing, plur, a1, a2);
}

template <typename A1, typename A2, typename A3>
    inline KUndo2MagicString kundo2_i18ncp (const char *ctxt, const char *sing, const char *plur, const A1 &a1, const A2 &a2, const A3 &a3)
{
    return i18ncp(prependContext(ctxt).toLatin1().data(), sing, plur, a1, a2, a3);
}

template <typename A1, typename A2, typename A3, typename A4>
    inline KUndo2MagicString kundo2_i18ncp (const char *ctxt, const char *sing, const char *plur, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4)
{
    return i18ncp(prependContext(ctxt).toLatin1().data(), sing, plur, a1, a2, a3, a4);
}

#endif /* __K_UNDO2_MAGIC_STRING_H */
