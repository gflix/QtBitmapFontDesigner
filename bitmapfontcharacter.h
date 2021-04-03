#ifndef BITMAPFONTCHARACTER_H
#define BITMAPFONTCHARACTER_H

#include <QChar>
#include <QMap>
#include "bitmapfontcharactermatrix.h"

struct BitmapFontCharacter
{
    BitmapFontCharacter(
        QChar character = '?',
        int width = 6,
        const BitmapFontCharacterMatrix& matrix = BitmapFontCharacterMatrix());

    QChar character;
    int width;
    BitmapFontCharacterMatrix matrix;
};

typedef QMap<QChar, BitmapFontCharacter> BitmapFontCharacters;

#endif // BITMAPFONTCHARACTER_H
