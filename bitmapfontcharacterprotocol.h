#ifndef BITMAPFONTCHARACTERPROTOCOL_H
#define BITMAPFONTCHARACTERPROTOCOL_H

#include <QDomDocument>
#include <QDomElement>
#include "bitmapfontcharacter.h"
#include "bitmapfontmetrics.h"

void bitmapFontCharactersToXml(QDomDocument& document, QDomElement& base, const BitmapFontCharacters& characters, const BitmapFontMetrics& metrics);
void bitmapFontCharacterToXml(QDomDocument& document, QDomElement& base, const BitmapFontCharacter& character, const BitmapFontMetrics& metrics);

BitmapFontCharacters bitmapFontCharactersFromXml(const QDomElement& base);
BitmapFontCharacter bitmapFontCharacterFromXml(const QDomElement& base);

#endif // BITMAPFONTCHARACTERPROTOCOL_H
