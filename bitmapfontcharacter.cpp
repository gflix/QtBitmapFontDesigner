#include "bitmapfontcharacter.h"

BitmapFontCharacter::BitmapFontCharacter(
    QChar character,
    int width,
    const BitmapFontCharacterMatrix& matrix):
    character(character),
    width(width),
    matrix(matrix)
{
}
