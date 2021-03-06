#include "common/const.h"
#include "common/vector3.h"

Vector3 operator+(const Vector3& A, const Vector3& B)
{
    return Vector3(A.x + B.x, A.y + B.y, A.z + B.z);
}

Vector3 operator-(const Vector3& A, const Vector3& B)
{
    return Vector3(A.x - B.x, A.y - B.y, A.z - B.z);
}

Vector3 operator*(const Vector3& A, const Vector3& B)
{
    return Vector3(A.y * B.z - A.z * B.y, A.z * B.x - A.x * B.z, A.x * B.y - A.y * B.x);
}

std::ostream& operator<<(std::ostream& out, const Vector3& v)
{
    return out << '(' << v.x << ' ' << v.y << ' ' << v.z << ')';
}

Vector3 Vector3::operator-() const
{
    return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator*(double k) const
{
    return Vector3(x * k, y * k, z * k);
}

Vector3 Vector3::operator/(double k) const
{
    return Vector3(x / k, y / k, z / k);
}

double Vector3::dot(const Vector3& B) const
{
    return x * B.x + y * B.y + z * B.z;
}

double Vector3::mod() const
{
    return sqrt(x * x + y * y + z * z);
}

double Vector3::mod2() const
{
    return x * x + y * y + z * z;
}

Vector3 Vector3::unitize() const
{
    double m = mod();
    return *(this) / (m < Const::EPS ? 1 : m);
}

Vector3 Vector3::reflect(const Vector3& n) const
{
    return *this - n * (2 * this->dot(n));
}

Vector3 Vector3::refract(const Vector3& n, double rindex) const
{
    double ni = 1 / rindex; // 折射率的倒数，nT/ni
    double cosi = this->dot(n), cosT2 = 1 - ni * ni * (1 - cosi * cosi);
    if (cosT2 < Const::EPS)
        return Vector3();
    else
        return (*this) * ni - n * (sqrt(cosT2) + cosi * ni);
}
