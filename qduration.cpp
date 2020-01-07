#include "qduration.h"

#define YEAR_SECONDS 31536000 //contain 365 days
#define MONTH_SECONDS 2592000 //contain 30 days
#define DAY_SECONDS 86400
#define HOUR_SECONDS 3600
#define MINUTE_SECONDS 60

QDuration::QDuration()
{
    days_ = 0;
    months_ = 0;
    years_ = 0;
    time_ = QTime::fromString("00:00:00:000", "hh:mm:ss:zzz");
}

QDuration::QDuration(QTime time, int days, int months, int years)
{
    days_ = 0;
    months_ = 0;
    years_ = 0;
    time_ = time;
    this->addYears(years);
    this->addMonths(months);
    this->addDays(days);
}

QString QDuration::toString()
{
    QString duration;
    duration = QString::number(this->years_) + "-" + QString::number(this->months_) + "-" + QString::number(this->days_) + " " +
            this->time_.toString("hh:mm:ss:zzz");
    return duration;
}

QDuration QDuration::fromString(QString timeDurationString, QString dateDurationString)
{
    /*Time Duration format is hh:mm:ss and Date Duration format is yy-mm-dd*/
    QStringList datePices = dateDurationString.split( "-" );
    QDuration duration;
    duration.addYears(datePices[0].toInt());
    duration.addMonths(datePices[1].toInt());
    duration.addDays(datePices[2].toInt());
    duration.time_ = QTime::fromString(timeDurationString, "hh:mm:ss:zzz");
    return duration;
}

QDuration QDuration::fromString(QString durationString)
{
    /*Duration format is yy-mm-dd hh:mm:ss*/
    QDuration duration;
    if(!durationString.isNull())
    {
        QStringList durationPices = durationString.split(" ");
        QStringList datePices = durationPices[0].split( "-" );
        duration.addYears(datePices[0].toInt());
        duration.addMonths(datePices[1].toInt());
        duration.addDays(datePices[2].toInt());
        duration.time_ = QTime::fromString(durationPices[1], "hh:mm:ss:zzz");
    }
    return duration;

}

QDuration QDuration::toDuration(QDuration duration)
{
    QTime falseTime;
    falseTime = QTime::fromString("00:00:00:000", "hh:mm:ss:zzz");
    QDuration falseValue(falseTime, 30, 12, 67);
    QDuration result;

    if(this->seconds() <= duration.seconds())
    {
        result.years_ = duration.years_ - this->years_;
        result.months_ = duration.months_ - this->months_;
        result.days_ = duration.days_ - this->days_;
        if(this->time_.secsTo(duration.time_) >= 0)
        {
            result.addSeconds(this->time_.secsTo(duration.time_));
        }
        else
        {
            int sec = 0;
            QDuration temp;
            sec = result.seconds();
            sec -= abs(this->time_.secsTo(duration.time_));
            temp.addSeconds(sec);
            result = temp;
        }
        return result;
    }
    else
    {
        return falseValue;
    }

}

int QDuration::seconds()
{
    int sec = 0;
    sec += this->years_ * YEAR_SECONDS;
    sec += this->months_ * MONTH_SECONDS;
    sec += this->days_ * DAY_SECONDS;
    sec += this->timeSeconds();
    return sec;
}

int QDuration::mSeconds()
{
    int msec = 0;
    msec += this->years_ * YEAR_SECONDS;
    msec += this->months_ * MONTH_SECONDS;
    msec += this->days_ * DAY_SECONDS;
    msec = msec * 1000;
    msec += this->timeMseconds();
    return msec;
}

int QDuration::timeSeconds()
{
    int sec = 0;
    sec += this->time_.hour() * HOUR_SECONDS;
    sec += this->time_.minute() * MINUTE_SECONDS;
    sec += this->time_.second();
    return sec;
}

int QDuration::timeSeconds(QTime time)
{
    int sec = 0;
    sec += time.hour() * HOUR_SECONDS;
    sec += time.minute() * MINUTE_SECONDS;
    sec += time.second();
    return sec;
}

int QDuration::timeMseconds()
{
    int msec = 0;
    msec += this->time_.hour() * HOUR_SECONDS;
    msec += this->time_.minute() * MINUTE_SECONDS;
    msec += this->time_.second();
    msec = msec * 1000;
    msec += this->time_.msec();
    return msec;
}

int QDuration::timeMseconds(QTime time)
{
    int msec = 0;
    msec += time.hour() * HOUR_SECONDS;
    msec += time.minute() * MINUTE_SECONDS;
    msec += time.second();
    msec = msec * 1000;
    msec += time.msec();
    return msec;
}

void QDuration::addYears(int years)
{
    this->years_ += years;
    if(this->years_ > 67)
    {
        this->years_ = this->years_ - 67;
    }
}

void QDuration::addMonths(int months)
{
    this->months_ += months;
    if(this->months_ >= 12)
    {
        this->addYears((this->months_ / 12));
        this->months_ = this->months_ % 12;
    }
}

void QDuration::addDays(int days)
{
    this->days_ += days;
    if(this->days_ >= 30)
    {
        this->addMonths((this->days_ / 30));
        this->days_ = this->days_ % 30;
    }
}

void QDuration::addHours(int hours)
{
    QTime temp = this->time_;
    if(hours < 24 && hours > 0)
    {
        this->time_ = this->time_.addSecs(hours * HOUR_SECONDS);
        if(timeSeconds(temp) >= this->timeSeconds())
        {
            this->addDays(1);
        }
    }
    else if(hours > 0)
    {
        this->addDays(hours / 24);
        this->addHours(hours % 24);
    }

}

void QDuration::addMinutes(int minutes)
{
    QTime temp = this->time_;
    if(minutes < 60 && minutes > 0)
    {
        this->time_ = this->time_.addSecs(minutes * MINUTE_SECONDS);
        if(timeSeconds(temp) >= this->timeSeconds())
        {
            this->addDays(1);
        }
    }
    else if(minutes > 0)
    {
        this->addHours(minutes / 60);
        this->addMinutes(minutes % 60);
    }

}

void QDuration::addSeconds(int seconds)
{
    QTime temp = this->time_;
    if(seconds < 60 && seconds > 0)
    {
        this->time_ = this->time_.addSecs(seconds);
        if(timeSeconds(temp) >= this->timeSeconds())
        {
            this->addDays(1);
        }
    }
    else if(seconds > 0)
    {
        this->addMinutes(seconds / 60);
        this->addSeconds(seconds % 60);
    }
}

void QDuration::addMiliseconds(int miliseconds)
{
    QTime temp = this->time_;
    if(miliseconds < 1000 && miliseconds > 0)
    {
        this->time_ = this->time_.addMSecs(miliseconds);
        if(timeMseconds(temp) >= this->timeMseconds())
        {
            this->addDays(1);
        }
    }
    else if(miliseconds > 0)
    {
        this->addSeconds(miliseconds / 1000);
        this->addMiliseconds(miliseconds % 1000);
    }
}

void QDuration::clearDuration()
{
    days_ = 0;
    months_ = 0;
    years_ = 0;
    time_ = QTime::fromString("00:00:00:000", "hh:mm:ss:zzz");
}

bool QDuration::isValid()
{
    if(this->time_.isValid() && this->years_ <= 67 && this->years_ >=0 && this->months_ < 12 &&
            this->months_ >= 0 && this->days_ < 30 && this->days_ >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

QTime QDuration::getTime()
{
    return time_;
}
