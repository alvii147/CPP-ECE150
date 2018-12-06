#ifndef MYPRIVATEADDITIONS_H
#define MYPRIVATEADDITIONS_H

static float det(SafeMatrix& m);
static SafeMatrix reduce(SafeMatrix& m, int i, int j);
static bool identityTest(SafeMatrix& m);

#endif