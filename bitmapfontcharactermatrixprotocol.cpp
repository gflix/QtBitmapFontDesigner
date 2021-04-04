#include "bitmapfontcharactermatrixprotocol.h"
#include "xmltags.h"

void checkMatrixSize(const BitmapFontCharacterMatrix& matrix, const QSize& size)
{
    if (matrix.count() != size.width())
    {
        throw std::out_of_range(QString("expect width of %1, got %2 instead").arg(size.width()).arg(matrix.count()).toStdString());
    }
    for (auto& column: matrix)
    {
        if (column.count() != size.height())
        {
            throw std::out_of_range(QString("expect height of %1, got %2 instead").arg(size.height()).arg(column.count()).toStdString());
        }
    }
}

void bitmapFontCharacterMatrixToXml(QDomDocument& document, QDomElement& base, const BitmapFontCharacterMatrix& matrix, const QSize& size)
{
    checkMatrixSize(matrix, size);

    for (int y = 0; y < size.height(); ++y)
    {
        QDomElement rowElement = document.createElement(XML_TAG_ROW);
        QString text;
        for (int x = 0; x < size.width(); ++x)
        {
            text += matrix[x][y] ? 'X' : '.';
        }
        rowElement.appendChild(document.createTextNode(text));
        base.appendChild(rowElement);
    }
}
