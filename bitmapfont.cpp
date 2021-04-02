#include "bitmapfont.h"

BitmapFont::BitmapFont(
    const BitmapFontMetrics& metrics,
    const BitmapFontCharacters& characters):
    metrics(metrics),
    characters(characters)
{
}
