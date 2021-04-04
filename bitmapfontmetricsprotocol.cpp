#include "bitmapfontmetricsprotocol.h"
#include "xmltags.h"

void bitmapFontMetricsToXml(QDomDocument&, QDomElement& base, const BitmapFontMetrics& metrics)
{
    base.setAttribute(XML_ATTRIBUTE_ASCENDERS, metrics.ascenders);
    base.setAttribute(XML_ATTRIBUTE_DESCENDERS, metrics.descenders);
}

BitmapFontMetrics bitmapFontMetricsFromXml(const QDomElement& base)
{
    return BitmapFontMetrics(
        base.attribute(XML_ATTRIBUTE_ASCENDERS).toInt(),
        base.attribute(XML_ATTRIBUTE_DESCENDERS).toInt());
}
