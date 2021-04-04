#include "bitmapfontcharacterprotocol.h"
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

    QDomElement charactersElement = domDocument.createElement(XML_TAG_CHARACTERS);
    bitmapFontCharactersToXml(domDocument, charactersElement, bitmapFont.characters, bitmapFont.metrics);
    element.appendChild(charactersElement);

    domDocument.appendChild(element);

    return domDocument;
}
