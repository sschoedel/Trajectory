/*
    Trajectory planner given desired start and end points
*/
#ifndef Trajectory_h
#define Trajectory_h

#include "Arduino.h"

struct _Vector3
{
    float x;
    float y;
    float z;
};
typedef struct _Vector3 Vector3;

class Trajectory
{
    public:
        Trajectory(const int max_trajectory_points);
        void interpolate(float x1, float x2, float y1, float y2, float z1, float z2, int subPoints);
        Vector3 getTrajectoryPoint(int index);
        Vector3 getCurrentTrajectoryPoint();
        void setTrajectoryPoint(int index, float x, float y, float z);
        void setCurrentTrajectoryPoint(float x, float y, float z);
        void clearTrajectory();
        void printSubPoints();
        void step();
        bool trajectoryComplete;
    private:
        int MAX_SUBPOINTS;
        Vector3 * points;
        Vector3 trajectoryPoint;
        int _currTrajectoryPoint;
        int _subPoints;
};

#endif
