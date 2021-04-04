#include "bitmapfontcharactermatrixprotocol.h"
#include "bitmapfontcharacterprotocol.h"
#include "xmltags.h"

void bitmapFontCharactersToXml(QDomDocument& document, QDomElement& base, const BitmapFontCharacters& characters, const BitmapFontMetrics& metrics)
{
    for (auto& character: characters)
    {
        QDomElement characterElement = document.createElement(XML_TAG_CHARACTER);
        bitmapFontCharacterToXml(document, characterElement, character, metrics);
        base.appendChild(characterElement);
    }
}

void bitmapFontCharacterToXml(QDomDocument& document, QDomElement& base, const BitmapFontCharacter& character, const BitmapFontMetrics& metrics)
{
    base.setAttribute(XML_ATTRIBUTE_CODEPOINT, character.character.unicode());
    base.setAttribute(XML_ATTRIBUTE_WIDTH, character.width);

    QDomElement matrixElement = document.createElement(XML_TAG_MATRIX);
    bitmapFontCharacterMatrixToXml(document, matrixElement, character.matrix, QSize(character.width, metrics.ascenders + metrics.descenders));
    base.appendChild(matrixElement);
}
