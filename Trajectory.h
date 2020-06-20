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
        Trajectory();
        interpolate(float x1, float x2, float y1, float y2, float z1, float z2, int subPoints);
        getTrajectoryPoint(int index);
        clearTrajectory();

    private:
        int MAX_SUBPOINTS = 200;
        float xPoints[MAX_SUBPOINTS] = {};
        float yPoints[MAX_SUBPOINTS] = {};
        float zPoints[MAX_SUBPOINTS] = {};
        Vector3 trajectoryPoint;
};

#endif