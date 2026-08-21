#include <Matrix3x3d.hpp>
#include <Vector2.hpp>
#include <Matrix2x2d.hpp>

namespace MathLib
{
    double Matrix3x3<double>::determinant() const noexcept
    {
        // [a, b, c]
        // [d, e, f]
        // [g, h, i]

#if defined(SIMD_SSE2)

#else
        // clang-format off
        const double efhi = Matrix2x2d(getM22(), getM23(), 
                                        getM32(), getM33()).determinant();

        const double bchi = Matrix2x2d(getM12(), getM13(), 
                                        getM32(), getM33()).determinant();

        const double bcef = Matrix2x2d(getM12(), getM13(), 
                                        getM22(), getM23()).determinant();
        // clang-format on
        const Vector3d adg = Vector3d(getM11(), -getM21(), getM31());
        const Vector3d determinantVec = Vector3d(efhi, bchi, bcef);

        return Vector3d::dot(adg, determinantVec);
#endif // defined(SIMD_SSE2) || defined(SIMD_SSE42)
    }

    Matrix3x3<double>& Matrix3x3<double>::inverse() noexcept
    {
        // [a, b, c]
        // [d, e, f]
        // [g, h, i]

        // compute determoinant from colms 1
        // clang-format off
        const double efhi = Matrix2x2d(getM22(), getM23(), 
                                       getM32(), getM33()).determinant(); // m11

        const double bchi = Matrix2x2d(getM12(), getM13(), 
                                       getM32(), getM33()).determinant();  // m21

        const double bcef = Matrix2x2d(getM12(), getM13(),
                                       getM22(), getM23()).determinant(); // m31

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

        const double dfgi = Matrix2x2d(getM21(), getM23(), getM31(), getM33()).determinant(); // m12

        const double degh = Matrix2x2d(getM21(), getM22(), getM31(), getM32()).determinant(); // m13

        const double acgi = Matrix2x2d(getM11(), getM13(), getM31(), getM33()).determinant(); // m22

        const double abgh = Matrix2x2d(getM11(), getM12(), getM31(), getM32()).determinant(); // m23

        const double acdf = Matrix2x2d(getM11(), getM13(), getM21(), getM23()).determinant(); // m32

        const double abde = Matrix2x2d(getM11(), getM12(), getM21(), getM22()).determinant(); // m33

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
    }

} // MathLib
