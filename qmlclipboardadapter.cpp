#include "qmlclipboardadapter.h"

QmlClipboardAdapter::QmlClipboardAdapter(QObject *parent) : QObject(parent)
{
    clipboard = QGuiApplication::clipboard();
}

void QmlClipboardAdapter::setText(QString text){
    clipboard->setText(text);
}
