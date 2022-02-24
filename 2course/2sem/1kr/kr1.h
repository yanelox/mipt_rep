// 1 вариант
#include <iostream>

namespace my_time
{
    double acc = 0.01;

    class time_
    {
        public:
        
        int hours = 0, minute = 0;
        double sec = 0.0;

        time_ () = default;
        time_ (const time_ & rhs) = default;
        time_ (double Sec): sec{Sec} {}
        time_ (int h, int m, double s): hours {h}, minute {m}, sec {s} {}

        int get_h () const { return hours; }
        int get_m () const { return minute; }
        double get_s () const { return sec; }

        void set_h (int h) { hours = h; }
        void set_m (int m) { minute = m; }
        void set_s (double s) { sec = s; }

        void fix ()
        {
            time_ res{};

            res.sec = sec;

            res.minute += sec / 60;

            res.sec -= res.minute * 60;

            if (res.sec < 0)
            {
                res.sec += 60;
                res.minute -= 1;
            }

            res.minute += minute;

            res.hours += res.minute / 60;

            res.minute -= res.hours * 60;

            if (res.minute < 0)
            {
                res.minute += 60;
                res.hours -= 1;
            }

            res.hours += hours;

            hours = res.hours;
            minute = res.minute;
            sec = res.sec;
        }

        time_ operator + (const time_ &rhs) const
        {
            time_ res;

            res.hours = hours + rhs.hours;
            res.minute = minute + rhs.minute;
            res.sec = sec + rhs.sec;

            res.fix();

            return res;
        }

        time_ operator - (const time_ &rhs) const
        {
            time_ res;

            res.hours = hours - rhs.hours;
            res.minute = minute - rhs.minute;
            res.sec = sec - rhs.sec;

            res.fix();

            return res;
        }

        time_ operator ++ () 
        {
            time_ res {*this};

            sec += 1;

            res.fix();

            return res;
        }

        time_ operator -- ()
        {
            time_ res(*this);

            sec -=1;

            res.fix();

            return res;
        }

        time_ operator += (const time_ &rhs)
        {
            *this = *this + rhs;

            return *this;
        }

        time_ operator -= (const time_ rhs)
        {
            *this = *this - rhs;

            return *this;
        }

        auto operator <=> (const time_ &rhs) const
        {
            if (hours != rhs.hours)
                return (double) hours <=> (double) rhs.hours;

            else if (minute != rhs.minute)
                return (double) minute <=> (double) rhs.minute;

            return sec <=> rhs.sec;   
        }

        operator bool () const
        {
            double a = hours * 3600 + minute * 60 + sec;

            return (a < acc && a > -acc) ? false : true;
        }

        time_ operator - () const
        {
            time_ res{};

            res.hours = -hours;
            res.minute = -minute;
            res.sec = -sec;

            res.fix();

            return res;
        }
    };

    time_ operator * (const time_ &rhs, double n)
    {
        time_ res{rhs};

        res.hours *= n;
        res.minute *= n;
        res.sec *= n;

        res.fix();

        return res;
    }

    time_ operator * (double n, const time_ &rhs)
    {
        return rhs * n;
    }

    time_ operator / (const time_ &rhs, double n)
    {
        return rhs * (1 / n);
    }

    time_ operator / (double n, const time_ &rhs)
    {
        return rhs / n;
    }

    std::istream & operator >> (std::istream &in, time_ &t)
    {
        in >> t.hours >> t.minute >> t.sec;

        t.fix();

        return in;
    }

    std::ostream & operator << (std::ostream & out, const time_ &t)
    {
        out << t.hours << " " << t.minute << " " << t.sec;

        return out;
    }
}