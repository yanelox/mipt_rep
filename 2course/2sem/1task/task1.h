#include <iostream>
#include <cmath>

namespace math
{
    extern double acc;

    class vector
    {
        public:

        double x[3];

        vector () 
        {
            x[0] = x[1] = x[2] = 0;
        }
        
        vector (double a)
        {
            x[0] = x[1] = x[2] = a;
        }

        vector (double X, double Y, double Z)
        {
            x[0] = X;
            x[1] = Y;
            x[2] = Z;
        }

        ~vector ()
        {
            // std::cout << "Vector was deleted\n";
        }

        double get_x () const
        {
            return x[0];
        }

        double get_y () const
        {
            return x[1];
        }

        double get_z () const
        {
            return x[2];
        }

        void set_x (double X)
        {
            x[0] = X;
        }

        void set_y (double Y)
        {
            x[1] = Y;
        }

        void set_z (double Z)
        {
            x[2] = Z;
        }

        vector operator + (const vector &a) const
        {
            vector C{x[0] + a.x[0], x[1] + a.x[1], x[2] + a.x[2]};

            return C;
        }

        vector operator - (const vector &a) const
        {
            vector C{x[0] - a.x[0], x[1] - a.x[1], x[2] - a.x[2]};

            return C;
        }

        vector operator * (const vector &a) const
        {
            vector c{};

            c.x[0] = x[1] * a.x[2] - a.x[1] * x[2];
            c.x[1] = a.x[0] * x[2] - a.x[2] * x[0];
            c.x[2] = x[0] * a.x[1] - a.x[0] * x[1];

            return c;
        }

        vector operator * (double rhs) const
        {
            vector res;

            for (int i = 0; i < 3; ++i)
                res.x[i] = x[i] * rhs;

            return res;
        }

        vector operator ++ ()
        {
            vector res{*this};

            for (int i = 0; i < 3; ++i)
                x[i] += 1;

            return res;
        }

        vector operator -- ()
        {
            vector res{*this};

            for (int i = 0; i < 3; ++i)
                x[i] -= 1;

            return res;
        }

        vector & operator += (const vector &rhs)
        {
            for (int i = 0; i < 3; ++i)
                x[i] += rhs.x[i];

            return *this;
        }

        vector operator -= (const vector &rhs)
        {
            for (int i = 0; i < 3; ++i)
                x[i] -= rhs.x[i];

            return *this;
        }

        vector operator *= (double n)
        {
            for (int i = 0; i < 3; ++i)
                x[i] *= n;

            return *this;
        }

        auto operator <=> (const vector &rhs) const
        {
            double a = mod();
            double b = rhs.mod();

            return a <=> b;
        }

        double operator ^ (const vector &a) const
        {
            double res = x[0] * a.x[0] + x[1] * a.x[1] + x[2] * a.x[2];

            return res;
        }

        double mod () const
        {
            return std::sqrt (x[0] * x[0] + x[1] * x[1] + x[2] * x[2]);
        }

        operator bool () const
        {
            double a = mod();

            return (a < acc && a > -acc) ? false : true;
        }
    };

    std::ostream & operator << (std::ostream &out, const vector &vec);
    std::istream & operator >> (std::istream  &in, vector &vec);

    class matrix
    {
        public:

        vector x[3];

        matrix operator + (const matrix &) const; 
        matrix operator - (const matrix &) const;
        matrix operator * (const matrix &) const;
        vector operator * (const vector &) const;
        matrix operator * (double)   const;

        matrix T () const;
    };

    std::ostream & operator << (std::ostream &out, const matrix &m);
    std::istream & operator >> (std::istream  &in, matrix &m);

    int sum (int, int);
    double sum (double, double);
}