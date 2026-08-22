#include <Matrix3x3d.hpp>
#include <Matrix2x2d.hpp>
#include <Vector2d.hpp>
#include <Vector3d.hpp>

namespace MathLib
{
    Matrix3x3<double>& Matrix3x3<double>::inverse() noexcept
    {
        // TODO compare those 2 implmenation
        // the version below look like the best
#if 0
        const Vector3d cofactor0 = Vector3d::cross(m_data[1], m_data[2]);

        const double determinant = Vector3d::dot(m_data[0], cofactor0);

        if (fuzzyZero(determinant))
            return *this;

        const double invDeterminant = (1.0 / determinant);
        const Vector3d cofactor1 = Vector3d::cross(m_data[2], m_data[0]);
        const Vector3d cofactor2 = Vector3d::cross(m_data[0], m_data[1]);

        *this = Matrix3x3d(cofactor0, cofactor1, cofactor2).transpose() * (1.0 / determinant);

        return *this;
#else

        // [a, b, c]
        // [d, e, f]
        // [g, h, i]
        // compute determoinant from colms 1
        // clang-format off
        // TODO look if computing the determinant by calling determinant is not quicker

        const Vector2d m12m13 = m_data[0].yz();
        const Vector2d m22m23 = m_data[1].yz();
        const Vector2d m32m33 = m_data[2].yz();


        const double efhi = Matrix2x2d(m22m23, 
                                       m32m33).determinant(); // m11

        const double bchi = Matrix2x2d(m12m13, 
                                       m32m33).determinant();  // m21

        const double bcef = Matrix2x2d(m12m13,
                                       m22m23).determinant(); // m31

        const double determinant = [&]()
        {
            const Vector3d adg = Vector3d(getM11(), -getM21(), getM31());
            const Vector3d determinantVec = Vector3d(efhi, bchi, bcef);
            return Vector3d::dot(adg, determinantVec);
        }();

        if (fuzzyZero(determinant))
            return *this;

        // clang-format on

        // compute the left element for cofactor
        const Vector2d m21m23 = m_data[1].xz();
        const Vector2d m31m33 = m_data[2].xz();

        const Vector2d m21m22 = m_data[1].xy();
        const Vector2d m31m32 = m_data[2].xy();

        const Vector2d m11m13 = m_data[0].xz();
        const Vector2d m11m12 = m_data[0].xy();

        const double dfgi = Matrix2x2d(m21m23, m31m33).determinant(); // m12

        const double degh = Matrix2x2d(m21m22, m31m32).determinant(); // m13

        const double acgi = Matrix2x2d(m11m13, m31m33).determinant(); // m22

        const double abgh = Matrix2x2d(m11m12, m31m32).determinant(); // m23

        const double acdf = Matrix2x2d(m11m13, m21m23).determinant(); // m32

        const double abde = Matrix2x2d(m11m12, m21m22).determinant(); // m33

        // construct the transposed cofactor (adjugate)
        // clang-format off
        const Matrix3x3d transposedCofactor(
                efhi, -bchi,  bcef,
                -dfgi, acgi, -acdf,
                degh, -abgh,  abde
        );
        // clang-format on
        *this = transposedCofactor * (1.0 / determinant);
        return *this;
#endif
    }

} // MathLib
