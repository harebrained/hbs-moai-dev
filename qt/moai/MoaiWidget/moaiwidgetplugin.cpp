#include "moaiwidget.h"
#include "moaiwidgetplugin.h"

#include <QtCore/QtPlugin>

MoaiWidgetPlugin::MoaiWidgetPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void MoaiWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;
    
    // Add extension registrations, etc. here
    
    m_initialized = true;
}

bool MoaiWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *MoaiWidgetPlugin::createWidget(QWidget *parent)
{
    return new MoaiWidget(parent);
}

QString MoaiWidgetPlugin::name() const
{
    return QLatin1String("MoaiWidget");
}

QString MoaiWidgetPlugin::group() const
{
    return QLatin1String("");
}

QIcon MoaiWidgetPlugin::icon() const
{
    return QIcon();
}

QString MoaiWidgetPlugin::toolTip() const
{
    return QLatin1String("");
}

QString MoaiWidgetPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool MoaiWidgetPlugin::isContainer() const
{
    return false;
}

QString MoaiWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"MoaiWidget\" name=\"moaiWidget\">\n</widget>\n");
}

QString MoaiWidgetPlugin::includeFile() const
{
    return QLatin1String("moaiwidget.h");
}

Q_EXPORT_PLUGIN2(moaiwidgetplugin, MoaiWidgetPlugin)
