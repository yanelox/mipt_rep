#include "task1.h"

namespace math
{
    double acc = 0.01;
    
    int sum (int x1, int x2)
    {
        std::cout << "int sum\n";

        return x1 + x2;
    }

    double sum (double x1, double x2)
    {
        std::cout << "double sum\n";

        return x1 + x2;
    }

    //vector

    vector operator * (double n, vector &rhs)
    {
        vector res;

        for (int i = 0; i < 3; ++i)
            res.x[i] = n * rhs.x[i];

        return res;
    }

    std::istream & operator >> (std::istream &in, vector &vec)
    {
        in >> vec.x[0] >> vec.x[1] >> vec.x[2];

        return in;
    }

    std::ostream & operator << (std::ostream &out, const vector &vec)
    {
        out << vec.get_x() << " " << vec.get_y() << " " << vec.get_z();
        
        return out;
    }

    //matrix

    matrix matrix::operator + (const matrix &rhs) const
    {
        matrix res;

        for (int i = 0; i < 3; ++i)
            res.x[i] = x[i] + rhs.x[i];

        return res;
    }

    matrix matrix::operator - (const matrix &rhs) const
    {
        matrix res;

        for (int i = 0; i < 3; ++i)
            res.x[i] = x[i] - rhs.x[i];

        return res;
    }

    matrix matrix::T () const
    {
        matrix res;

        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                res.x[i].x[j] = x[j].x[i];

        return res;
    }

    matrix matrix::operator * (const matrix &rhs) const
    {
        matrix res, tmp;

        tmp = rhs.T();

        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                res.x[i].x[j] = x[i] ^ tmp.x[j];

        return res;
    }

    vector matrix::operator * (const vector &rhs) const
    {
        vector res;

        for (int i = 0; i < 3; ++i)
            res.x[i] = x[i] ^ rhs;

        return res;
    }

    matrix matrix::operator * (double rhs) const
    {
        matrix res;

        for (int i = 0; i < 3; ++i)
            res.x[i] = x[i] * rhs;

        return res;
    }

    std::istream & operator >> (std::istream  &in, matrix &m)
    {
        in >> m.x[0];
        in >> m.x[1];
        in >> m.x[2];

        return in;
    }

    std::ostream & operator << (std::ostream &out, const matrix &m)
    {
        out << m.x[0] << "\n" << m.x[1] << "\n" << m.x[2];
        
        return out;
    }
}