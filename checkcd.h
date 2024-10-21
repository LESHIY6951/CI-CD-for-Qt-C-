#ifndef CHECKCD_H
#define CHECKCD_H

#include <QSqlDatabase>


class CheckCD
{
public:
    CheckCD();
    QSqlDatabase db;
    QString CD();
};

#endif // CHECKCD_H
