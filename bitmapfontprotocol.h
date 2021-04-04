#ifndef BITMAPFONTPROTOCOL_H
#define BITMAPFONTPROTOCOL_H

#include <QDomDocument>
#include "bitmapfont.h"

QDomDocument bitmapFontToDomDocument(const BitmapFont& bitmapFont);
BitmapFont bitmapFontFromDomDocument(const QDomDocument& document);

QDomDocument bitmapFontToQtResourceDocument(const BitmapFont& bitmapFont, const QString& resourcePath);

QDomDocument bitmapFontToManifestDocument(const BitmapFont& bitmapFont);

#endif // BITMAPFONTPROTOCOL_H
