#include <iostream>

#define SENTINEL -9999
#define BLANK -9999

typedef struct {
    int year, month, day;
    int hour, minute, second;
} DateTime;


bool isLeapYear(int year) {
    return (year%4 == 0 && year%100 != 0) || (year%400 == 0);
}

int yearsJunLeapSec[] = {1972, 1981, 1982, 1983, 1985, 1992, 1993, 1994, 1997, 2012, 2015, SENTINEL};
int yearsDecLeapSec[] = {1972, 1973, 1974, 1975, 1976, 1977, 1978, 1979, 1987, 1989, 1990, 1995, 1998, 2005, 2008, 2016, SENTINEL};

int daysOfMonthNonLeap[13]={BLANK, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int daysOfMonthLeap[13]={BLANK, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool isLeapSec (int year, int leapSecArr[]) {
    for(int i = 0, y = leapSecArr[0]; y != SENTINEL; y = leapSecArr[++i]) {
        if(year == y) {
            return true;
        }
    }
    return false;
}

int secondsToYearEnd(const DateTime &dt) {
    int year = dt.year;
    int *daysOfMonth = isLeapYear(year) ? daysOfMonthLeap : daysOfMonthNonLeap;
    int leapSec = 0;
    if(dt.month <= 6 && isLeapSec(dt.year, yearsJunLeapSec)) {
        leapSec += 1;
    }
    if(isLeapSec(dt.year, yearsDecLeapSec)) {
        leapSec += 1;
    }

    int daysToYearEnd = daysOfMonth[dt.month] - dt.day;

    for(int m = dt.month + 1; m <= 12; ++m) {
        daysToYearEnd += daysOfMonth[m];
    }
    int secsToYearEnd = daysToYearEnd * 24 * 60 * 60 + leapSec;
    int hoursToDayEnd = 24 - dt.hour - 1;
    int minutesToHourEnd = 60 - dt.minute - 1;
    int secondsToMinuteEnd = 60 - dt.second;
    secsToYearEnd += hoursToDayEnd * 60 * 60;
    secsToYearEnd += minutesToHourEnd * 60;
    secsToYearEnd += secondsToMinuteEnd;

    return secsToYearEnd;
}

int yearLengthInSeconds(int year) {
    DateTime yearStart;
    yearStart.year = year;
    yearStart.month = 1;
    yearStart.day = 1;
    yearStart.hour = 0;
    yearStart.minute = 0;      
    yearStart.second = 0;
    return secondsToYearEnd(yearStart);
} 

int secondsBetween(const DateTime &dt1, const DateTime &dt2) {
    int sec1 = secondsToYearEnd(dt1);
    int sec2 = secondsToYearEnd(dt2);
    if(dt1.year == dt2.year) {
        return sec1 - sec2;
    }
    int secBetween = 0;
    int year = dt1.year + 1;
    while(year < dt2.year) {
        secBetween += yearLengthInSeconds(year);
        year += 1;
    }
    return sec1 + secBetween + (yearLengthInSeconds(dt2.year) - sec2);
}


int main() {
    char _connector_dump;

    DateTime date1;
    DateTime date2;
    
    std::cin >> date1.year >> _connector_dump
        >> date1.month >> _connector_dump
        >> date1.day
        >> date1.hour >> _connector_dump
        >> date1.minute >> _connector_dump
        >> date1.second;

    std::cin >> date2.year >> _connector_dump
        >> date2.month >> _connector_dump
        >> date2.day
        >> date2.hour >> _connector_dump
        >> date2.minute >> _connector_dump
        >> date2.second;
    
    std::cout << secondsBetween(date1, date2) << std::endl;
}


// void printDateTime(const DateTime &d) {
//     std::cout << d.year << "-" << d.month << "-" << d.day 
//         << " " << d.hour << ":" << d.minute << ":" << d.second << std::endl;
// }