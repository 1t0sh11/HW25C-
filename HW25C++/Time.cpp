#include "Time.h"

Time::Time() {
    time_t now = time(0);
    tm ltm;
#if defined(_MSC_VER)
    localtime_s(&ltm, &now);
#else
    localtime_r(&now, &ltm);
#endif
    hour = ltm.tm_hour;
    minutes = ltm.tm_min;
    seconds = ltm.tm_sec;
    format = true;
}

Time::Time(int h, int m, int s, bool f) {
    hour = h;
    minutes = m;
    seconds = s;
    format = f;
}

Time::Time(const Time& obj) {
    hour = obj.hour;
    minutes = obj.minutes;
    seconds = obj.seconds;
    format = obj.format;
}

Time& Time::operator = (const Time& obj) {
    if (this != &obj) {
        hour = obj.hour;
        minutes = obj.minutes;
        seconds = obj.seconds;
        format = obj.format;
    }
    return *this;
}

Time::~Time() {}

void Time::setHour(int h) { hour = h; }
int Time::getHour() const { return hour; }
void Time::setMinutes(int m) { minutes = m; }
int Time::getMinutes() const { return minutes; }
void Time::setSeconds(int s) { seconds = s; }
int Time::getSeconds() const { return seconds; }
void Time::setFormat(bool f) { format = f; }
bool Time::getFormat() const { return format; }

bool Time::valid() const {
    return (hour >= 0 && hour < 24) && (minutes >= 0 && minutes < 60) && (seconds >= 0 && seconds < 60);
}

long long Time::toSeconds() const {
    return (long long)hour * 3600 + minutes * 60 + seconds;
}

Time Time::fromSeconds(long long totalSec, bool fmt) {
    totalSec = (totalSec % 86400 + 86400) % 86400;
    int h = totalSec / 3600;
    int m = (totalSec % 3600) / 60;
    int s = totalSec % 60;
    return Time(h, m, s, fmt);
}

void Time::tickTime() {
    long long total = toSeconds() + 1;
    Time t = fromSeconds(total, format);
    hour = t.hour; minutes = t.minutes; seconds = t.seconds;
}

void Time::untickTime() {
    long long total = toSeconds() - 1;
    Time t = fromSeconds(total, format);
    hour = t.hour; minutes = t.minutes; seconds = t.seconds;
}

Time& Time::operator ++ () {
    *this += 1;
    return *this;
}

Time Time::operator ++ (int) {
    Time temp(*this);
    *this += 1;
    return temp;
}

Time& Time::operator -- () {
    *this -= 1;
    return *this;
}

Time Time::operator -- (int) {
    Time temp(*this);
    *this -= 1;
    return temp;
}

bool Time::operator == (const Time& obj) const& { return toSeconds() == obj.toSeconds(); }
bool Time::operator != (const Time& obj) const& { return toSeconds() != obj.toSeconds(); }
bool Time::operator > (const Time& obj) const& { return toSeconds() > obj.toSeconds(); }
bool Time::operator < (const Time& obj) const& { return toSeconds() < obj.toSeconds(); }
bool Time::operator >= (const Time& obj) const& { return toSeconds() >= obj.toSeconds(); }
bool Time::operator <= (const Time& obj) const& { return toSeconds() <= obj.toSeconds(); }

Time& Time::operator += (float s) {
    long long total = toSeconds() + (long long)(s + (s >= 0 ? 0.5f : -0.5f));
    Time t = fromSeconds(total, format);
    hour = t.hour; minutes = t.minutes; seconds = t.seconds;
    return *this;
}
Time& Time::operator -= (float s) { return (*this += (-s)); }

Time& Time::operator += (int m) {
    long long total = toSeconds() + (long long)m * 60;
    Time t = fromSeconds(total, format);
    hour = t.hour; minutes = t.minutes; seconds = t.seconds;
    return *this;
}
Time& Time::operator -= (int m) { return (*this += (-m)); }

Time& Time::operator += (long h) {
    long long total = toSeconds() + h * 3600;
    Time t = fromSeconds(total, format);
    hour = t.hour; minutes = t.minutes; seconds = t.seconds;
    return *this;
}
Time& Time::operator -= (long h) { return (*this += (-h)); }

Time Time::operator + (float s) const& { Time res(*this); res += s; return res; }
Time Time::operator - (float s) const& { Time res(*this); res -= s; return res; }
Time Time::operator + (int m) const& { Time res(*this); res += m; return res; }
Time Time::operator - (int m) const& { Time res(*this); res -= m; return res; }
Time Time::operator + (long h) const& { Time res(*this); res += h; return res; }
Time Time::operator - (long h) const& { Time res(*this); res -= h; return res; }

Time operator + (float seconds, const Time& a) { return a + seconds; }
Time operator - (float seconds, const Time& a) { return Time::fromSeconds(seconds - a.toSeconds(), a.format); }

Time operator + (int minutes, const Time& a) { return a + minutes; }
Time operator - (int minutes, const Time& a) {
    long long sec = (long long)minutes * 60 - a.toSeconds();
    return Time::fromSeconds(sec, a.format);
}

Time operator + (long hours, const Time& a) { return a + hours; }
Time operator - (long hours, const Time& a) {
    long long sec = hours * 3600 - a.toSeconds();
    return Time::fromSeconds(sec, a.format);
}

ostream& operator << (ostream& os, const Time& t) {
    if (t.format) {
        os << setfill('0') << setw(2) << t.hour << ":"
            << setw(2) << t.minutes << ":"
            << setw(2) << t.seconds << " (24h)";
    }
    else {
        int h12 = t.hour % 12;
        if (h12 == 0) h12 = 12;
        string period = (t.hour >= 12) ? "PM" : "AM";
        os << setfill('0') << setw(2) << h12 << ":"
            << setw(2) << t.minutes << ":"
            << setw(2) << t.seconds << " " << period;
    }
    return os;
}

istream& operator >> (istream& is, Time& t) {
    char colon1, colon2;
    is >> t.hour >> colon1 >> t.minutes >> colon2 >> t.seconds;
    return is;
}

Bus::Bus(Time start, Time end, int duration, int rest) {
    startTime = start;
    endTime = end;
    tripDuration = duration;
    restTime = rest;
}

void Bus::generateBusSchedule() const {
    cout << "\n==================================================\n";
    cout << "           SUBURBAN BUS ROUTE SCHEDULE            \n";
    cout << "==================================================\n";
    cout << "Working hours: " << startTime << " - " << endTime << endl;
    cout << "Trip duration: " << tripDuration << " min | Rest time: " << restTime << " min\n";
    cout << "--------------------------------------------------\n";
    cout << setw(15) << "Terminal A" << " | " << setw(15) << "Terminal B" << endl;
    cout << "--------------------------------------------------\n";

    Time departureA = startTime;

    while (true) {
        Time arrivalB = departureA + tripDuration;

        if (departureA > endTime) {
            break;
        }

        cout << setw(15) << departureA << " | " << setw(15) << arrivalB << endl;

        Time departureB = arrivalB + restTime;
        Time arrivalA = departureB + tripDuration;

        if (departureB > endTime) {
            break;
        }

        cout << setw(15) << departureB << " (from B) | " << setw(15) << arrivalA << " (back to A)\n";

        departureA = arrivalA + restTime;
    }
    cout << "==================================================\n\n";
}