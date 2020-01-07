#ifndef QDURATION_H
#define QDURATION_H
#include <QTime>

class QDuration
{
public:
    QDuration();
    QDuration(QTime time, int days = 0, int months = 0, int years = 0);
    QString toString();
    QDuration fromString(QString timeDurationString, QString dateDurationString);
    QDuration fromString(QString durationString);
    void addMiliseconds(int miliseconds);
    void addSeconds(int seconds);
    void addMinutes(int minutes);
    void addHours(int hours);
    void addDays(int days);
    void addMonths(int months);
    void addYears(int years);
    void clearDuration();
    QDuration toDuration(QDuration duration);
    int seconds();
    int mSeconds();
    int timeSeconds();
    int timeSeconds(QTime time);
    int timeMseconds();
    int timeMseconds(QTime time);
    bool isValid();
    QTime getTime();

private:
    int days_;
    int months_;
    int years_;
    QTime time_;
};

#endif // QDURATION_H
