#include "vector_int.h"
#include <math.h>

void normalizeVectorInt(t_vector2_int *vector)
{
  float x = vector->x;
  float y = vector->y;
  float length = sqrt(x * x + y * y);
  vector->x = x / length;
  vector->y = y / length;
}

void turnVectorByAngleInt(t_vector2_int *vector, float angle)
{
  float x = vector->x;
  float y = vector->y;
  float cosAngle = cos(angle);
  float sinAngle = sin(angle);
  vector->x = x * cosAngle - y * sinAngle;
  vector->y = x * sinAngle + y * cosAngle;
}