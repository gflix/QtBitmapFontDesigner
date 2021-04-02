#ifndef BITMAPFONT_H
#define BITMAPFONT_H

#include "bitmapfontcharacter.h"
#include "bitmapfontmetrics.h"

struct BitmapFont
{
    explicit BitmapFont(
        const BitmapFontMetrics& metrics = BitmapFontMetrics(),
        const BitmapFontCharacters& characters = BitmapFontCharacters());

    BitmapFontMetrics metrics;
    BitmapFontCharacters characters;
};

#endif // BITMAPFONT_H
