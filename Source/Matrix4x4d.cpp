#include <Matrix4x4d.hpp>
#include <Matrix3x3d.hpp>
#include <Vector4d.hpp>

namespace MathLib
{
    double Matrix4x4<double>::determinant() const noexcept
    {
        // [a, b, c, d]
        // [e, f, g, h]
        // [i, j, k, l]
        // [m, n, o, p]

        // compute determinant from 1 coloms
        // aeim
        const Vector4d factor = Vector4d(m_data[0].getX(), -m_data[1].getX(), m_data[2].getX(), -m_data[3].getX());
        // clang-format off
        const double fgh_jkl_nopDeterminant = Matrix3x3d(static_cast<Vector3d>(m_data[1].yzwx()),                // fgh
                                                         static_cast<Vector3d>(m_data[2].yzwx()),                // jkl
                                                         static_cast<Vector3d>(m_data[3].yzwx())).determinant(); // nop

        const double bcd_jkl_nopDeterminant = Matrix3x3d(static_cast<Vector3d>(m_data[0].yzwx()),                // bcd
                                                         static_cast<Vector3d>(m_data[2].yzwx()),                // jkl
                                                         static_cast<Vector3d>(m_data[3].yzwx())).determinant(); // nop

        const double bcd_fgh_nopDeterminant = Matrix3x3d(static_cast<Vector3d>(m_data[0].yzwx()),                // bcd
                                                         static_cast<Vector3d>(m_data[1].yzwx()),                // fgh
                                                         static_cast<Vector3d>(m_data[3].yzwx())).determinant(); // nop

        const double bcd_fgh_jklDeterminant = Matrix3x3d(static_cast<Vector3d>(m_data[0].yzwx()),                // bcd
                                                          static_cast<Vector3d>(m_data[1].yzwx()),                // fgh
                                                          static_cast<Vector3d>(m_data[2].yzwx())).determinant(); // jkl
        // clang-format on

        return Vector4d::dot(factor, Vector4d(fgh_jkl_nopDeterminant, bcd_jkl_nopDeterminant, bcd_fgh_nopDeterminant,
                                              bcd_fgh_jklDeterminant));
    }

    Matrix4x4<double>& Matrix4x4<double>::inverse() noexcept
    {
        // [a, b, c, d]
        // [e, f, g, h]
        // [i, j, k, l]
        // [m, n, o, p]

        // clang-format off
        // coloms1
        // m11
        const double fgh_jkl_nop_Determinant = Matrix3x3d(static_cast<Vector3d>(m_data[1].yzwx()),                // fgh
                                                          static_cast<Vector3d>(m_data[2].yzwx()),                // jkl
                                                          static_cast<Vector3d>(m_data[3].yzwx())).determinant(); // nop
        // m21
        const double bcd_jkl_nopDeterminant = Matrix3x3d(static_cast<Vector3d>(m_data[0].yzwx()),                // bcd
                                                         static_cast<Vector3d>(m_data[2].yzwx()),                // jkl
                                                         static_cast<Vector3d>(m_data[3].yzwx())).determinant(); // nop
        // m31
        const double bcd_fgh_nopDeterminant = Matrix3x3d(static_cast<Vector3d>(m_data[0].yzwx()),                // bcd
                                                         static_cast<Vector3d>(m_data[1].yzwx()),                // fgh
                                                         static_cast<Vector3d>(m_data[3].yzwx())).determinant(); // nop
        // m41
        const double bcd_fgh_jklDeterminant = Matrix3x3d(static_cast<Vector3d>(m_data[0].yzwx()),                // bcd
                                                          static_cast<Vector3d>(m_data[1].yzwx()),                // fgh
                                                          static_cast<Vector3d>(m_data[2].yzwx())).determinant(); // jkl
        // clang-format on

        const double determianant = [&]()
        {
            // compute determinant from 1 coloms
            // aeim
            const Vector4d factor = Vector4d(m_data[0].getX(), -m_data[1].getX(), m_data[2].getX(), -m_data[3].getX());
            return Vector4d::dot(factor, Vector4d(fgh_jkl_nop_Determinant, bcd_jkl_nopDeterminant,
                                                  bcd_fgh_nopDeterminant, bcd_fgh_jklDeterminant));
        }();

        if (fuzzyZero(determianant)) // is invertable
            return *this;

        // clang-format off
        // coloms2
        // m12
        const double egh_ikl_nopDeterminant = Matrix3x3d(static_cast<Vector3d>(m_data[1].xzwy()),                // egh
                                                         static_cast<Vector3d>(m_data[2].xzwy()),                // ikl
                                                         static_cast<Vector3d>(m_data[3].xzwy())).determinant(); // mop
        // m22
        const double acd_ijl_nopDeterminant = Matrix3x3d(static_cast<Vector3d>(m_data[0].xzwy()),                // acd
                                                         static_cast<Vector3d>(m_data[2].xzwy()),                // ikl
                                                         static_cast<Vector3d>(m_data[3].xzwy())).determinant(); // nop
        // m32
        const double acd_egh_mopDeterminant = Matrix3x3d(static_cast<Vector3d>(m_data[0].xzwy()),                // acd
                                                         static_cast<Vector3d>(m_data[1].xzwy()),                // egh
                                                         static_cast<Vector3d>(m_data[3].xzwy())).determinant(); // nop
        // m42
        const double acd_eghi_jklDeterminant = Matrix3x3d(static_cast<Vector3d>(m_data[0].xzwy()),               // acd
                                                          static_cast<Vector3d>(m_data[1].xzwy()),               // egh
                                                          static_cast<Vector3d>(m_data[2].xzwy())).determinant();// ikl
        // clang-format on

        // clang-format off
        // coloms3
        // m13
        const double efh_ijl_mnpDeterminant = Matrix3x3d(static_cast<Vector3d>(m_data[1].xywz()),                // efh
                                                         static_cast<Vector3d>(m_data[2].xywz()),                // ijl
                                                         static_cast<Vector3d>(m_data[3].xywz())).determinant(); // mnp
        // m23
        const double abd_ijl_mnpDeterminant = Matrix3x3d(static_cast<Vector3d>(m_data[0].xywz()),                // abd
                                                         static_cast<Vector3d>(m_data[2].xywz()),                // ijl
                                                         static_cast<Vector3d>(m_data[3].xywz())).determinant(); // mnp
        // m33
        const double abd_efh_mnpDeterminant = Matrix3x3d(static_cast<Vector3d>(m_data[0].xywz()),                // abd
                                                         static_cast<Vector3d>(m_data[1].xywz()),                // efh
                                                         static_cast<Vector3d>(m_data[3].xywz())).determinant(); // mnp
        // m43
        const double abd_efh_ijlDeterminant = Matrix3x3d(static_cast<Vector3d>(m_data[0].xywz()),                // abd
                                                         static_cast<Vector3d>(m_data[1].xywz()),                // efh
                                                         static_cast<Vector3d>(m_data[2].xywz())).determinant(); // ijl
        // clang-format on

        // clang-format off
        // coloms4
        // m14
        const double efg_ijk_mnoDeterminant = Matrix3x3d(static_cast<Vector3d>(m_data[1].xyz()),                 // efg
                                                         static_cast<Vector3d>(m_data[2].xyz()),                 // ijk
                                                         static_cast<Vector3d>(m_data[3].xyz())).determinant();  // mno
        // m24
        const double abc_ijk_mnoDeterminant = Matrix3x3d(static_cast<Vector3d>(m_data[0].xyz()),                 // abc
                                                         static_cast<Vector3d>(m_data[2].xyz()),                 // ijk
                                                         static_cast<Vector3d>(m_data[3].xyz())).determinant();  // mno
        // m34
        const double abc_efg_mnoDeterminant = Matrix3x3d(static_cast<Vector3d>(m_data[0].xyz()),                 // abc
                                                         static_cast<Vector3d>(m_data[1].xyz()),                 // efg
                                                         static_cast<Vector3d>(m_data[3].xyz())).determinant();  // mno
        // m44
        const double abc_efg_ijkDeterminant = Matrix3x3d(static_cast<Vector3d>(m_data[0].xyz()),                 // abc
                                                         static_cast<Vector3d>(m_data[1].xyz()),                 // efh
                                                         static_cast<Vector3d>(m_data[2].xyz())).determinant();  // ijl
        // clang-format on

        const double invDertminant = 1.0 / determianant;
        // construct the transposed cofactor (adjugate)
        // clang-format off
        *this = Matrix4x4( fgh_jkl_nop_Determinant, -bcd_jkl_nopDeterminant,  bcd_fgh_nopDeterminant, -bcd_fgh_jklDeterminant,
                          -egh_ikl_nopDeterminant,   acd_ijl_nopDeterminant, -acd_egh_mopDeterminant,  acd_eghi_jklDeterminant,
                           efh_ijl_mnpDeterminant,  -abd_ijl_mnpDeterminant,  abd_efh_mnpDeterminant, -abd_efh_ijlDeterminant,
                          -efg_ijk_mnoDeterminant,   abc_ijk_mnoDeterminant, -abc_efg_mnoDeterminant,  abc_efg_ijkDeterminant) * invDertminant;
        // clang-format on
        return *this;
    }

} // namespace MathLib
