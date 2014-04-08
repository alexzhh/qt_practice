#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <QWidget>
#include <dcmtk/dcmdata/dcdatset.h>

class savefile : public QWidget
{
    Q_OBJECT
public:
    explicit savefile(QWidget *parent = 0);
    bool saveFile(QString fileName,QString  );
signals:

public slots:

};

#endif // SAVEFILE_H
