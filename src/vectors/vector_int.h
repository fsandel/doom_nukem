#ifndef VECTORS_VECTOR_INT_H
#define VECTORS_VECTOR_INT_H

typedef struct s_vector2_int
{
  int x;
  int y;
} t_vector2_int;

void turnVectorByAngleInt(t_vector2_int *vector, float angle);
void normalizeVectorInt(t_vector2_int *vector);

#endif // VECTORS_VECTOR_INT_H