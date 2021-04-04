#ifndef BITMAPFONTPROTOCOL_H
#define BITMAPFONTPROTOCOL_H

#include <QDomDocument>
#include "bitmapfont.h"

QDomDocument bitmapFontToDomDocument(const BitmapFont& bitmapFont);
BitmapFont bitmapFontFromDomDocument(const QDomDocument& document);

#endif // BITMAPFONTPROTOCOL_H
