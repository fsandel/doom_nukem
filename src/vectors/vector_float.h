#ifndef VECTORS_VECTOR_FLOAT_H
#define VECTORS_VECTOR_FLOAT_H

typedef struct s_vector2_float
{
  float x;
  float y;
} t_vector2_float;

void normalizeVectorFloat(t_vector2_float *vector);
void turnVectorByAngleFloat(t_vector2_float *vector, float angle);

#endif //VECTORS_VECTOR_FLOAT_H