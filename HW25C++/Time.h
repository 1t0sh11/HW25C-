#pragma once

#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>

using namespace std;

class Time
{
    int hour;
    int minutes;
    int seconds;
    bool format;
public:
    Time();
    Time(int hour, int minutes, int seconds = 0, bool format = true);
    Time(const Time& obj);
    Time& operator = (const Time& obj);
    ~Time();

    void setHour(int hour);
    int getHour() const;
    void setMinutes(int minutes);
    int getMinutes() const;
    void setSeconds(int seconds);
    int getSeconds() const;
    void setFormat(bool format);
    bool getFormat() const;

    bool valid() const;
    void tickTime();
    void untickTime();

    long long toSeconds() const;
    static Time fromSeconds(long long totalSec, bool format);

    Time& operator ++ ();
    Time  operator ++ (int);
    Time& operator -- ();
    Time  operator -- (int);

    bool operator == (const Time& obj) const&;
    bool operator != (const Time& obj) const&;
    bool operator > (const Time& obj) const&;
    bool operator < (const Time& obj) const&;
    bool operator >= (const Time& obj) const&;
    bool operator <= (const Time& obj) const&;

    Time& operator += (float s);
    Time& operator -= (float s);
    Time& operator += (int m);
    Time& operator -= (int m);
    Time& operator += (long h);
    Time& operator -= (long h);

    Time operator + (float s) const&;
    Time operator - (float s) const&;
    Time operator + (int m) const&;
    Time operator - (int m) const&;
    Time operator + (long h) const&;
    Time operator - (long h) const&;

    friend Time operator + (float seconds, const Time& a);
    friend Time operator - (float seconds, const Time& a);
    friend Time operator + (int minutes, const Time& a);
    friend Time operator - (int minutes, const Time& a);
    friend Time operator + (long hours, const Time& a);
    friend Time operator - (long hours, const Time& a);

    friend ostream& operator << (ostream& os, const Time& t);
    friend istream& operator >> (istream& is, Time& t);
};

class Bus {
private:
    Time startTime;
    Time endTime;
    int tripDuration;
    int restTime;

public:
    Bus(Time start, Time end, int duration, int rest);
    void generateBusSchedule() const;
};