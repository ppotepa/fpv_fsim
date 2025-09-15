#ifndef EXPONENTIALAIRDENSITYMODEL_H
#define EXPONENTIALAIRDENSITYMODEL_H

#include "IAirDensityModel.h"

class ExponentialAirDensityModel : public IAirDensityModel
{
public:
    ExponentialAirDensityModel(float seaLevelDensity, float scaleHeight);
    float getDensity(float altitude) const override;

private:
    float seaLevelDensity_;
    float scaleHeight_;
};

#endif
