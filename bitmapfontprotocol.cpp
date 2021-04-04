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

QDomDocument bitmapFontToQtResourceDocument(const BitmapFont& bitmapFont, const QString& resourcePath)
{
    QDomDocument domDocument;

    QDomElement element = domDocument.createElement(XML_TAG_RCC);

    QDomElement qResourceElement = domDocument.createElement(XML_TAG_QRESOURCE);
    qResourceElement.setAttribute(XML_ATTRIBUTE_PREFIX, "/");

    for (auto& character: bitmapFont.characters)
    {
        QDomElement fileElement = domDocument.createElement(XML_TAG_FILE);
        fileElement.appendChild(domDocument.createTextNode(QString("%1/character-%2.png").arg(resourcePath).arg(character.character.unicode())));
        qResourceElement.appendChild(fileElement);
    }

    QDomElement fileElement = domDocument.createElement(XML_TAG_FILE);
    fileElement.appendChild(domDocument.createTextNode(QString("%1/manifest.xml").arg(resourcePath)));
    qResourceElement.appendChild(fileElement);

    element.appendChild(qResourceElement);

    domDocument.appendChild(element);

    return domDocument;
}

QDomDocument bitmapFontToManifestDocument(const BitmapFont& bitmapFont)
{
    QDomDocument domDocument;

    QDomElement element = domDocument.createElement(XML_TAG_BITMAP_FONT);
    element.setAttribute(XML_ATTRIBUTE_MAX_ASCENDER, bitmapFont.metrics.ascenders);
    element.setAttribute(XML_ATTRIBUTE_MAX_DESCENDER, bitmapFont.metrics.descenders);

    for (auto& character: bitmapFont.characters)
    {
        QDomElement characterElement = domDocument.createElement(XML_TAG_CHARACTER);
        characterElement.setAttribute(XML_ATTRIBUTE_RESOURCE, QString("character-%1.png").arg(character.character.unicode()));
        characterElement.setAttribute(XML_ATTRIBUTE_UNICODE, character.character.unicode());
        element.appendChild(characterElement);
    }

    domDocument.appendChild(element);

    return domDocument;
}
