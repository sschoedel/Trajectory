#include "Arduino.h"
#include "Trajectory.h"

Trajectory::Trajectory(const int max_trajectory_points)
{
  trajectoryComplete = true;
  this->MAX_SUBPOINTS = max_trajectory_points;
  points = new Vector3[this->MAX_SUBPOINTS];
}

void Trajectory::interpolate(float x1, float x2, float y1, float y2, float z1, float z2, int subPoints)
{
  // Initialize variables for navigating trajectory array
  trajectoryComplete = false;
  _currTrajectoryPoint = 0;
  _subPoints = subPoints;

  // Find step amount (delta) and direction to add step (+ or -) for x,y, and z
  float deltaX = abs(x1 - x2) / subPoints;
  float deltaY = abs(y1 - y2) / subPoints;
  float deltaZ = abs(z1 - z2) / subPoints;

  int xDir = (x2 - x1) / abs(x1 - x2);
  int yDir = (y2 - y1) / abs(y1 - y2);
  int zDir = (z2 - z1) / abs(z1 - z2);

  // Populate array with intermediate points (straight line)
  for (int i=0; i < subPoints; i++)
  {
    points[i].x = x1 + xDir * deltaX * i;
    points[i].y = y1 + yDir * deltaY * i;
    points[i].z = z1 + zDir * deltaZ * i;
  }

  // Include end point in trajectory
  points[subPoints].x = x2;
  points[subPoints].y = y2;
  points[subPoints].z = z2;
}

void Trajectory::step()
{
  if (_currTrajectoryPoint >= _subPoints)
  {
    trajectoryComplete = true;
  }
  else
  {
    _currTrajectoryPoint++;
  }
}

/*
    Returns current trajectory in a vector3 struct
    Returns 0, 0, 0 if the index supplied is out of bounds of the trajectory's array
    (foot position should never be 0, 0, 0 naturally)
*/
Vector3 Trajectory::getTrajectoryPoint(int index)
{
    if (index < MAX_SUBPOINTS)
    {
        trajectoryPoint = points[index];
    }
    else
    {
        trajectoryPoint.x = 0;
        trajectoryPoint.y = 0;
        trajectoryPoint.z = 0;
    }

    return trajectoryPoint;
}

/*
    Getter for current point
*/
Vector3 Trajectory::getCurrentTrajectoryPoint()
{
  return points[_currTrajectoryPoint];
}

void Trajectory::clearTrajectory()
{
    for (int i=0; i<MAX_SUBPOINTS; i++)
    {
        points[i].x = 0;
        points[i].y = 0;
        points[i].z = 0;
    }
}

void Trajectory::setTrajectoryPoint(int index, float x, float y, float z)
{
  points[index].x = x;
  points[index].y = y;
  points[index].z = z;
}

void Trajectory::setCurrentTrajectoryPoint(float x, float y, float z)
{
  points[_currTrajectoryPoint].x = x;
  points[_currTrajectoryPoint].y = y;
  points[_currTrajectoryPoint].z = z;
}

void Trajectory::printSubPoints()
{
   for (int i = 0; i < _subPoints; i++)
   {
     Serial.print("X Y Z - "); Serial.print(i); Serial.print(": ");
     Serial.print(points[i].x); Serial.print(", ");
     Serial.print(points[i].y); Serial.print(", ");
     Serial.println(points[i].z);
   }
}
