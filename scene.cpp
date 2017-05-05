#include "collision.h"
#include "common/const.h"
#include "light/light.h"
#include "light/pointlight.h"
#include "object/object.h"
#include "object/plane.h"
#include "object/sphere.h"
#include "scene.h"

#include <algorithm>

Scene::Scene()
    : m_camera(new Camera()), m_ambient_color(Color(0.2, 0.2, 0.2))
{
    m_lights.push_back(new PointLight(Color(0.8, 0.8, 0.8), Vector3(-0.5, 0, 0.9)));

    Material* groundMaterial = new Material(Color(0.4, 0.4, 0.4), 0.8, 0, 0, 0);
    Material* wallMaterial = new Material(Color(1, 1, 1), 0.9, 0.1, 0, 0);
    Material* ballMaterial = new Material(Color(1.0, 0.2, 0.2), 0.4, 0.99, 0.6, 0);
    Material* mirrorMaterial = new Material(Color(0.9, 0.9, 0.9), 0.1, 0.9, 0.9, 0);

    Object* ground = new Plane(wallMaterial, Vector3(0, 0, 1), 1);
    Object* ceiling = new Plane(wallMaterial, Vector3(0, 0, -1), 1);
    Object* wall1 = new Plane(mirrorMaterial, Vector3(0, -1, 0.1), 1);
    Object* wall2 = new Plane(wallMaterial, Vector3(-1, 0, 0), 1);
    Object* wall3 = new Plane(wallMaterial, Vector3(1, 0, 0), 1);
    Object* wall4 = new Plane(wallMaterial, Vector3(0, 1, 0), 1);
    Object* ball1 = new Sphere(ballMaterial, Vector3(0.6, 0.7, -0.8), 0.2);
    Object* ball2 = new Sphere(mirrorMaterial, Vector3(-0.5, 0.5, -0.7), 0.3);

    m_objects.push_back(ground);
    m_objects.push_back(ceiling);
    m_objects.push_back(wall1);
    m_objects.push_back(wall2);
    m_objects.push_back(wall3);
    m_objects.push_back(wall4);
    m_objects.push_back(ball1);
    m_objects.push_back(ball2);

    // 反射光比例小的物体优先，其次折射光
    sort(m_objects.begin(), m_objects.end(), [](const Object* A, const Object* B) {
        return A->getMaterial()->compare(B->getMaterial());
    });
}

Scene::~Scene()
{
    if (m_camera) delete m_camera;
    for (auto i : m_lights) delete i;
    for (auto i : m_objects) delete i;
    m_lights.clear();
    m_objects.clear();
}

Collision Scene::findNearestCollision(const Vector3& start, const Vector3& dir) const
{
    Collision ret;
    for (auto l : m_lights)
    {
        Collision coll = l->collide(start, dir);
        if (coll.isHit() && coll.dist + Const::EPS < ret.dist) ret = coll;
    }
    for (auto o : m_objects)
    {
        Collision coll = o->collide(start, dir);
        if (coll.isHit() && coll.dist + Const::EPS < ret.dist) ret = coll;
    }
    return ret;
}
