#include "vector_float.h"
#include <math.h>

void normalizeVectorFloat(t_vector2_float *vector)
{
  float x = vector->x;
  float y = vector->y;
  float length = sqrt(x * x + y * y);
  vector->x = x / length;
  vector->y = y / length;
}

void turnVectorByAngleFloat(t_vector2_float *vector, float angle)
{
  float x = vector->x;
  float y = vector->y;
  float cosAngle = cos(angle);
  float sinAngle = sin(angle);
  vector->x = x * cosAngle - y * sinAngle;
  vector->y = x * sinAngle + y * cosAngle;
}