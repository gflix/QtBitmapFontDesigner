#ifndef BITMAPFONTMETRICSPROTOCOL_H
#define BITMAPFONTMETRICSPROTOCOL_H

#include <QDomDocument>
#include <QDomElement>
#include "bitmapfontmetrics.h"

void bitmapFontMetricsToXml(QDomDocument& document, QDomElement& base, const BitmapFontMetrics& metrics);
BitmapFontMetrics bitmapFontMetricsFromXml(const QDomElement& base);

#endif // BITMAPFONTMETRICSPROTOCOL_H
