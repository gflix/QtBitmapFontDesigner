#ifndef BITMAPFONTCHARACTER_H
#define BITMAPFONTCHARACTER_H

#include <QChar>
#include <QMap>

struct BitmapFontCharacter
{
    BitmapFontCharacter(QChar character = '?');

    QChar character;
};

typedef QMap<QChar, BitmapFontCharacter> BitmapFontCharacters;

#endif // BITMAPFONTCHARACTER_H
