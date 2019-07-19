#include "drawtimeline.h"
#include "drawtimelineplugin.h"

#include <QtPlugin>

DrawTimelinePlugin::DrawTimelinePlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void DrawTimelinePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool DrawTimelinePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *DrawTimelinePlugin::createWidget(QWidget *parent)
{
    return new DrawTimeline(parent);
}

QString DrawTimelinePlugin::name() const
{
    return QLatin1String("DrawTimeline");
}

QString DrawTimelinePlugin::group() const
{
    return QLatin1String("Customise");
}

QIcon DrawTimelinePlugin::icon() const
{
    return QIcon();
}

QString DrawTimelinePlugin::toolTip() const
{
    return QLatin1String("只显示的时间轴插件");
}

QString DrawTimelinePlugin::whatsThis() const
{
    return QLatin1String("一些描述");
}

bool DrawTimelinePlugin::isContainer() const
{
    return false;
}

QString DrawTimelinePlugin::domXml() const
{
    return QLatin1String("<widget class=\"DrawTimeline\" name=\"drawTimeline\">\n</widget>\n");
}

QString DrawTimelinePlugin::includeFile() const
{
    return QLatin1String("drawtimeline.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(drawtimelineplugin, DrawTimelinePlugin)
#endif // QT_VERSION < 0x050000
