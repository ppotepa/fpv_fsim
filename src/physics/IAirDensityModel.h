#ifndef IAIRDENSITYMODEL_H
#define IAIRDENSITYMODEL_H

class IAirDensityModel {
public:
    virtual ~IAirDensityModel() = default;
    virtual float getDensity(float altitude) const = 0;
};

#endif
