#include "bitmapfontprotocol.h"
#include "bitmapfontmetricsprotocol.h"
#include "xmltags.h"

QDomDocument bitmapFontToDomDocument(const BitmapFont& bitmapFont)
{
    QDomDocument domDocument;

    QDomElement element = domDocument.createElement(XML_TAG_BITMAP_FONT);

    QDomElement metricsElement = domDocument.createElement(XML_TAG_METRICS);
    bitmapFontMetricsToXml(domDocument, metricsElement, bitmapFont.metrics);
    element.appendChild(metricsElement);

    domDocument.appendChild(element);

    return domDocument;
}
