#ifndef POINT_H
#define POINT_H


class Point
{
    public:
        Point();
        Point(double x , double y , double z);
        virtual ~Point();
        Point(Point* other);

        double GetX() { return X; }
        void SetX(double val) { X = val; }
        double GetY() { return Y; }
        void SetY(double val) { Y = val; }
        double GetZ() { return Z; }
        void SetZ(double val) { Z = val; }

    protected:
    private:
        double X;
        double Y;
        double Z;
};

#endif // POINT_H
