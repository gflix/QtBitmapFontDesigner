#ifndef BITMAPFONTCHARACTERMATRIXPROTOCOL_H
#define BITMAPFONTCHARACTERMATRIXPROTOCOL_H

#include <QDomDocument>
#include <QDomElement>
#include <QSize>
#include "bitmapfontcharactermatrix.h"

void bitmapFontCharacterMatrixToXml(QDomDocument& document, QDomElement& base, const BitmapFontCharacterMatrix& matrix, const QSize& size);

#endif // BITMAPFONTCHARACTERMATRIXPROTOCOL_H
