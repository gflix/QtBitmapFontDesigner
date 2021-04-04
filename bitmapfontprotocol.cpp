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

BitmapFont bitmapFontFromDomDocument(const QDomDocument& document)
{
    auto documentElement = document.documentElement();
    if (documentElement.tagName() != XML_TAG_BITMAP_FONT)
    {
        throw std::runtime_error("invalid XML, wong document element");
    }

    auto bitmapFontMetrics = bitmapFontMetricsFromXml(documentElement.firstChildElement(XML_TAG_METRICS));
    auto bitmapFontCharacters = bitmapFontCharactersFromXml(documentElement.firstChildElement(XML_TAG_CHARACTERS));

    return BitmapFont(
        bitmapFontMetrics,
        bitmapFontCharacters);
}
