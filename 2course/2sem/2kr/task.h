#include <iostream>

template <typename T>
class frac 
{
    T num, den;

    public:

    frac () {}

    frac (double a): num{a}, den{1} {}

    template <typename U> 
    frac (U a, U b): num {a}, den{b} 
    {
        if (b == 0)
            throw "devision by zero";
    }

    T get_num () const { return num; }
    T get_den () const { return den; }

    void set_num (const T &n) { num = n; }
    void set_den (const T &d)
    {
        if (d == 0)
            throw "devision by zero";

        den = d;
    }

    frac operator + (const frac &rhs) const
    {
        T res_d = den * rhs.den;
        T res_n = num * rhs.den + rhs.num * den;

        frac <T> res {res_n, res_d};

        return res;
    }

    frac operator - (const frac &rhs) const
    {
        T res_d = den * rhs.den;
        T res_n = num * rhs.den - rhs.num * den;

        frac <T> res {res_n, res_d};

        return res;
    }

    frac operator * (const frac &rhs) const
    {
        frac <T> res {num * rhs.num, den * rhs.den};

        return res;
    }

    frac operator / (const frac &rhs) const
    {
        if (rhs.num == 0)
            throw "devision by zero";

        T res_n = num * rhs.den;
        T res_d = den * rhs.num;

        if (res_d < 0)
        {
            res_n = res_n * (-1);
            res_d = res_d * (-1);
        }

        frac <T> res {num * rhs.den, den * rhs.num};

        return res;
    }

    auto operator <=> (const frac &rhs) const
    {
        return (num * rhs.den) <=> (den * rhs.num);
    }
};

template <typename T>
std::istream & operator >> (std::istream &in, frac <T> &f)
{
    in >> f.num >> f.den;

    if (f.den == 0)
        throw "division by zero";

    return in;
}

template <typename T>
std::ostream & operator << (std::ostream &out, const frac <T> &f)
{
    out << f.num << " / " << f.den;

    return out;
}

template <typename T>
class mfrac : frac <T>
{
    using frac <T>::num;
    using frac <T>::den;

    T m;

    public:

    mfrac () {}

    mfrac (double a): m{0}, frac <T> {a} {}

    template <typename U>
    mfrac (U num_, U den_): m{0}, frac <T> {num_, den_} {}

    template <typename U>
    mfrac (U m_, U num_, U den_): frac <T> {num_, den_}, m{m_} {}

    T get_m () const { return m; }
    void set_m (T m_) { m = m_; }

    mfrac operator + (const mfrac <T> &rhs) const
    {
        T res_d = den * rhs.den;
        T res_n = num * rhs.den + den * rhs.num;
        T res_m = res_n / res_d;

        res_n = res_n - m * res_d;

        mfrac <T> res {res_m, res_n, res_d};

        return res;
    }

    mfrac operator - (const mfrac <T> &rhs) const
    {
        T res_d = den * rhs.den;
        T res_n = num * rhs.den - den * rhs.num;
        T res_m = res_n / res_d;

        res_n = res_n - m * res_d;

        mfrac <T> res {res_m, res_n, res_d};

        return res;
    }

    mfrac operator * (const mfrac <T> &rhs) const
    {
        frac <T> r1 {m * rhs.num, rhs.den};
        frac <T> r2 {rhs.m * num, den};
        frac <T> r3 {m * rhs.num, den * rhs.den};

        frac <T> r4;
        r4 = r1 + r2 + r3;

        mfrac <T> res {m * rhs.m, r4.num, r4.den};

        return res;
    }

    mfrac operator / (const mfrac <T> &rhs) const
    {
        frac <T> r1 {m * den + num, den};
        frac <T> r2 {rhs.m * rhs.den + rhs.num, rhs.den};

        frac <T> r3;
        r3 = r1 / r2;

        T res_m = r3.num / r3.den;
        T res_n = r3.num - res_m * r3.den;
        T res_d = r3.den;

        mfrac <T> res{res_m, res_n, res_d};

        return res; 
    }

    auto operator <=> (const mfrac &rhs) const
    {
        return (frac <T> {m * den + num, den}) <=> (frac <T> {rhs.m * rhs.den + rhs.num, rhs.den});
    }
};

template <typename T>
std::istream & operator >> (std::istream & in, mfrac <T> &mf)
{
    in >> mf.m >> mf.num >> mf.den;

    if (mf.den == 0)
        throw "division by zero";

    return in;
}

template <typename T>
std::ostream & operator << (std::ostream & out, mfrac <T> &mf)
{
    out << mf.m << " " << mf.num << " / " << mf.den;

    return out;
}

template <typename T>
class complex
{
    T r;
    T c;

    public:

    complex () {}

    complex (T r_, T c_): r{r_}, c{c_} {}

    T get_r () const { return r; }
    T get_c () const { return c; }

    void set_r (T r_) { r = r_; }
    void set_c (T c_) { c = c_; }

    complex operator + (const complex <T> &rhs) const
    {
        complex <T> res {r + rhs.r, c + rhs.c};

        return res;
    }

    complex operator - (const complex <T> &rhs) const
    {
        complex <T> res {r - rhs.r, c - rhs.c};

        return res;
    }

    complex operator * (const complex <T> &rhs) const
    {
        complex <T> res {r * rhs.r - c * rhs.c, r * rhs.c + c * rhs.r};

        return res;
    }

    auto operator <=> (const complex &rhs) const
    {
        return (r * r + c * c) <=> (rhs.r * rhs.r + rhs.c * rhs.c);
    }
};

template <typename T>
std::istream & operator >> (std::istream &in, complex <T> &n)
{
    in >> n.r >> n.c;

    return in;
}

template <typename T>
std::ostream & operator << (std::ostream &out, const complex <T> &n)
{
    out << n.r << " " << n.c;

    return out;
}