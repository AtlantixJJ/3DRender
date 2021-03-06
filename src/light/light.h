#ifndef LIGHT_H
#define LIGHT_H

#include "collision.h"
#include "common/color.h"

class Scene;
class PointLight;

class Light
{
public:
    Light(const Color& c)
        : m_color(c) {}
    virtual ~Light() {}

    Color getColor() const { return m_color; }

    // 发光点
    virtual Vector3 getSource() const = 0;

    // 与视线相交
    virtual Collision collide(const Vector3& start, const Vector3& dir) const = 0;

    // 计算阴影比例，值越小阴影越深
    virtual double getShadowRatio(const Scene* scene, const Vector3& p) const = 0;

protected:
    Color m_color;
};

#endif // LIGHT_H
