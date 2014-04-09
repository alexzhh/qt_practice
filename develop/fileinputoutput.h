#ifndef FILEINPUTOUTPUT_H
#define FILEINPUTOUTPUT_H

#include <QFileDialog>
#include <QString>

class FileInputOutput
{
public:
    FileInputOutput();
    virtual QString OpenFile(QString filter = "All File (*.*)");
    virtual QString SaveFile(QString filter = "All File (*.*)");
    ~FileInputOutput();
};

#endif // FILEINPUTOUTPUT_H
