#include "Arduino.h"
#include "Trajectory.h"

Trajectory::Trajectory()
{
    Serial.println("Trajectory planner created.");
}

void Trajectory::interpolate(float x1, float x2, float y1, float y2, float z1, float z2, int subPoints)
{
  // Find step amount (delta) and direction to add step (+ or -) for x,y, and z
  float deltaX = abs(x1 - x2) / subPoints;
  float deltaY = abs(y1 - y2) / subPoints;
  float deltaZ = abs(z1 - z2) / subPoints;

  int xDir = (x2 - x1) / abs(x1 - x2);
  int yDir = (y2 - y1) / abs(y1 - y2);
  int zDir = (z2 - z1) / abs(z1 - z2);

  for (int i=0; i < subPoints; i++)
  {
    xPoints[i] = x1 + xDir * deltaX * i;
    yPoints[i] = y1 + yDir * deltaY * i;
    zPoints[i] = z1 + zDir * deltaZ * i;
  }

  // Include end point in trajectory
  xPoints[subPoints] = x2;
  yPoints[subPoints] = y2;
  zPoints[subPoints] = z2;
}

/*
    Returns current trajectory in a vector3 data structure
    Returns 0, 0, 0 if the index supplied is out of bounds of the trajectory's array
    (foot position should never be 0, 0, 0 naturally)
*/
Vector3 Trajectory::getTrajectoryPoint(int index)
{
    if (index < MAX_SUBPOINTS)
    {
        trajectoryPoint.x = xPoints[index];
        trajectoryPoint.y = yPoints[index];
        trajectoryPoint.z = zPoints[index];
    }
    else
    {
        trajectoryPoint.x = 0;
        trajectoryPoint.y = 0;
        trajectoryPoint.z = 0;
    }
    
    return trajectoryPoint;
}

void Trajectory::clearTrajectory()
{
    for (int i=0; i<MAX_SUBPOINTS; i++)
    {
        xPoints[i] = 0;
        yPoints[i] = 0;
        zPoints[i] = 0;
    }
}