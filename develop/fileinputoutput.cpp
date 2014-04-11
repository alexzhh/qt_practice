#include "fileinputoutput.h"

FileInputOutput::FileInputOutput()
{
}

FileInputOutput::~FileInputOutput()
{
}


QString FileInputOutput::OpenFile(QString filter)
{
  return QFileDialog::getOpenFileName(
            NULL,
            QString::fromStdString("Open File"),
            QDir::currentPath(),
            filter);
}


QString FileInputOutput::SaveFile(QString filter)
{
  return QFileDialog::getSaveFileName(
            NULL,
            QString::fromStdString("Save File"),
            QDir::currentPath(),
            filter);
}
