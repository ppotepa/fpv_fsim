#ifndef PERLINWINDMODEL_H
#define PERLINWINDMODEL_H

#include "IWindModel.h"

class PerlinWindModel : public IWindModel
{
public:
    PerlinWindModel(float strength, float frequency, float amplitude, int seed);
    void getWind(float x, float y, float z, float &wx, float &wy, float &wz) const override;

private:
    float strength_;
    float frequency_;
    float amplitude_;
    int seed_;
};

#endif
