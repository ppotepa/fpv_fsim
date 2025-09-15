#ifndef IWINDMODEL_H
#define IWINDMODEL_H

class IWindModel
{
public:
    virtual ~IWindModel() = default;
    virtual void getWind(float x, float y, float z, float &wx, float &wy, float &wz) const = 0;
};

#endif
