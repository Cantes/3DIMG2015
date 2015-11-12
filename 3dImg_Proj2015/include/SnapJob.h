#ifndef SNAPJOB_H
#define SNAPJOB_H


class SnapJob
{
    public:
        SnapJob();
        virtual ~SnapJob();
        double position[3];
        double direction[3];
        double up[3];
        int n;
    protected:
};

#endif // SNAPJOB_H
