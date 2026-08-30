#ifndef MATH_LIB_MATRIX4X4D_H
#define MATH_LIB_MATRIX4X4D_H

#include <cstring>
#include <Vector3.hpp>
#include <Vector4d.hpp>
#include <AVX.hpp>

namespace MathLib
{
    template<typename T>
    class Matrix4x4;

    // Matrix elements are stored in row-major order
    // Mathematical operations use a column-vector convention
    template<>
    class alignas(VECTOR4D_ALIGNEMENT) Matrix4x4<double>
    {
    public:
        using _VectorType = Vector4d;

        explicit Matrix4x4() = default;

        ~Matrix4x4() = default;
        // clang-format off
        MATH_LIB_FORCE_INLINE explicit Matrix4x4(double getM11, double getM12, double getM13, double getM14,
                                                 double getM21, double getM22, double getM23, double getM24,
                                                 double getM31, double getM32, double getM33, double getM34,
                                                 double getM41, double getM42, double getM43, double getM44)
            : m_data{Vector4d(getM11, getM12, getM13, getM14), 
                     Vector4d(getM21, getM22, getM23, getM24),
                     Vector4d(getM31, getM32, getM33, getM34),
                     Vector4d(getM41, getM42, getM43, getM44)}
        {

        }
        // clang-format on
        // clang-format off
        MATH_LIB_FORCE_INLINE explicit Matrix4x4(const Vector4d& row1, 
                                                 const Vector4d& row2, 
                                                 const Vector4d& row3,
                                                 const Vector4d& row4)
            : m_data{row1, row2, row3, row4}
        {
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE const double* data() const noexcept
        {
            return m_data[0].data();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double* data() noexcept
        {
            return m_data[0].data();
        }

        [[nodiscard]] static Matrix4x4 zero() noexcept
        {
            // clang-format off
            return Matrix4x4(0.0, 0.0, 0.0, 0.0,
                             0.0, 0.0, 0.0, 0.0,
                             0.0, 0.0, 0.0, 0.0,
                             0.0, 0.0, 0.0, 0.0);
            // clang-format on
        }

        [[nodiscard]] static Matrix4x4 identity() noexcept
        {
            // clang-format off
            return Matrix4x4(1.0, 0.0, 0.0, 0.0,
                             0.0, 1.0, 0.0, 0.0,
                             0.0, 0.0, 1.0, 0.0,
                             0.0, 0.0, 0.0, 1.0);
            // clang-format on
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM11() const noexcept
        {
            return m_data[0].getX();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM12() const noexcept
        {
            return m_data[0].getY();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM13() const noexcept
        {
            return m_data[0].getZ();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM14() const noexcept
        {
            return m_data[0].getW();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM21() const noexcept
        {
            return m_data[1].getX();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM22() const noexcept
        {
            return m_data[1].getY();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM23() const noexcept
        {
            return m_data[1].getZ();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM24() const noexcept
        {
            return m_data[1].getW();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM31() const noexcept
        {
            return m_data[2].getX();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM32() const noexcept
        {
            return m_data[2].getY();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM33() const noexcept
        {
            return m_data[2].getZ();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM34() const noexcept
        {
            return m_data[2].getW();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM41() const noexcept
        {
            return m_data[3].getX();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM42() const noexcept
        {
            return m_data[3].getY();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM43() const noexcept
        {
            return m_data[3].getZ();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM44() const noexcept
        {
            return m_data[3].getW();
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM11(double getM11) noexcept
        {
            m_data[0].setX(getM11);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM12(double getM12) noexcept
        {
            m_data[0].setY(getM12);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM13(double getM13) noexcept
        {
            m_data[0].setZ(getM13);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM14(double getM14) noexcept
        {
            m_data[0].setW(getM14);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM21(double getM21) noexcept
        {
            m_data[1].setX(getM21);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM22(double getM22) noexcept
        {
            m_data[1].setY(getM22);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM23(double getM23) noexcept
        {
            m_data[1].setZ(getM23);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM24(double getM24) noexcept
        {
            m_data[1].setW(getM24);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM31(double getM31) noexcept
        {
            m_data[2].setX(getM31);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM32(double getM32) noexcept
        {
            m_data[2].setY(getM32);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM33(double getM33) noexcept
        {
            m_data[2].setZ(getM33);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM34(double getM34) noexcept
        {
            m_data[2].setW(getM34);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM41(double getM41) noexcept
        {
            m_data[3].setX(getM41);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM42(double getM42) noexcept
        {
            m_data[3].setY(getM42);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM43(double getM43) noexcept
        {
            m_data[3].setZ(getM43);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM44(double getM44) noexcept
        {
            m_data[3].setW(getM44);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& transpose() noexcept
        {
            double* ptr = reinterpret_cast<double*>(&m_data[0]);

            static constexpr std::size_t m12offset = 1;
            static constexpr std::size_t m13offset = 2;
            static constexpr std::size_t m14offset = 3;

            static constexpr std::size_t m21offset = 4;
            static constexpr std::size_t m23offset = 6;
            static constexpr std::size_t m24offset = 7;

            static constexpr std::size_t m31offset = 8;
            static constexpr std::size_t m32offset = 9;
            static constexpr std::size_t m34offset = 11;

            static constexpr std::size_t m41offset = 12;
            static constexpr std::size_t m42offset = 13;
            static constexpr std::size_t m43offset = 14;

            std::swap(ptr[m12offset], ptr[m21offset]);

            std::swap(ptr[m13offset], ptr[m31offset]);
            std::swap(ptr[m14offset], ptr[m41offset]);

            std::swap(ptr[m23offset], ptr[m32offset]);
            std::swap(ptr[m24offset], ptr[m42offset]);

            std::swap(ptr[m34offset], ptr[m43offset]);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4 getTranspose() const noexcept
        {
            Matrix4x4 m = (*this);
            return m.transpose();
        }

        MATH_LIB_FORCE_INLINE double determinant() const noexcept
        {
            return Vector4d::dot(m_data[0], Vector4d::cross(m_data[1], m_data[2], m_data[3]));
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& inverse() noexcept
        {
            // clang-format off
            const double row1x = m_data[0].getX(); const double row1y = m_data[0].getY(); const double row1z = m_data[0].getZ(); const double row1w = m_data[0].getW();
            const double row2x = m_data[1].getX(); const double row2y = m_data[1].getY(); const double row2z = m_data[1].getZ(); const double row2w = m_data[1].getW();
            const double row3x = m_data[2].getX(); const double row3y = m_data[2].getY(); const double row3z = m_data[2].getZ(); const double row3w = m_data[2].getW();
            const double row4x = m_data[3].getX(); const double row4y = m_data[3].getY(); const double row4z = m_data[3].getZ(); const double row4w = m_data[3].getW();

            double inv[16];
            inv[0]   =  row2y * row3z * row4w - row2y * row3w * row4z - row3y * row2z * row4w + row3y * row2w * row4z + row4y * row2z * row3w - row4y * row2w * row3z;
            inv[1]   = -row1y * row3z * row4w + row1y * row3w * row4z + row3y * row1z * row4w - row3y * row1w * row4z - row4y * row1z * row3w + row4y * row1w * row3z;
            inv[2]   =  row1y * row2z * row4w - row1y * row2w * row4z - row2y * row1z * row4w + row2y * row1w * row4z + row4y * row1z * row2w - row4y * row1w * row2z;
            inv[3]   = -row1y * row2z * row3w + row1y * row2w * row3z + row2y * row1z * row3w - row2y * row1w * row3z - row3y * row1z * row2w + row3y * row1w * row2z;
            inv[4]   = -row2x * row3z * row4w + row2x * row3w * row4z + row3x * row2z * row4w - row3x * row2w * row4z - row4x * row2z * row3w + row4x * row2w * row3z;
            inv[5]   =  row1x * row3z * row4w - row1x * row3w * row4z - row3x * row1z * row4w + row3x * row1w * row4z + row4x * row1z * row3w - row4x * row1w * row3z;
            inv[6]   = -row1x * row2z * row4w + row1x * row2w * row4z + row2x * row1z * row4w - row2x * row1w * row4z - row4x * row1z * row2w + row4x * row1w * row2z;
            inv[7]   =  row1x * row2z * row3w - row1x * row2w * row3z - row2x * row1z * row3w + row2x * row1w * row3z + row3x * row1z * row2w - row3x * row1w * row2z;
            inv[8]   =  row2x * row3y * row4w - row2x * row3w * row4y - row3x * row2y * row4w + row3x * row2w * row4y + row4x * row2y * row3w - row4x * row2w * row3y;
            inv[9]   = -row1x * row3y * row4w + row1x * row3w * row4y + row3x * row1y * row4w - row3x * row1w * row4y - row4x * row1y * row3w + row4x * row1w * row3y;
            inv[10]  =  row1x * row2y * row4w - row1x * row2w * row4y - row2x * row1y * row4w + row2x * row1w * row4y + row4x * row1y * row2w - row4x * row1w * row2y;
            inv[11]  = -row1x * row2y * row3w + row1x * row2w * row3y + row2x * row1y * row3w - row2x * row1w * row3y - row3x * row1y * row2w + row3x * row1w * row2y;
            inv[12]  = -row2x * row3y * row4z + row2x * row3z * row4y + row3x * row2y * row4z - row3x * row2z * row4y - row4x * row2y * row3z + row4x * row2z * row3y;
            inv[13]  =  row1x * row3y * row4z - row1x * row3z * row4y - row3x * row1y * row4z + row3x * row1z * row4y + row4x * row1y * row3z - row4x * row1z * row3y;
            inv[14]  = -row1x * row2y * row4z + row1x * row2z * row4y + row2x * row1y * row4z - row2x * row1z * row4y - row4x * row1y * row2z + row4x * row1z * row2y;
            inv[15]  =  row1x * row2y * row3z - row1x * row2z * row3y - row2x * row1y * row3z + row2x * row1z * row3y + row3x * row1y * row2z - row3x * row1z * row2y;

            // clang-format on
            const double determinant = row1x * inv[0] + row1y * inv[4] + row1z * inv[8] + row1w * inv[12];
            if (fuzzyZero(determinant) || !std::isfinite(determinant))
            {
                return *this;
            }

            const double invDeterminant = 1.0 / determinant;
            for (auto& d : inv)
                d = d * invDeterminant;

            static_assert(sizeof(m_data) == sizeof(inv));
            std::memcpy(m_data.data(), inv, sizeof(m_data));

            return *this;
        }

        Matrix4x4 getInverse() const noexcept
        {
            Matrix4x4 m = *this;
            return m.inverse();
        }

        Matrix4x4& operator+=(const double value) noexcept
        {
#if defined(MATH_LIB_INTRINSIC)
            double* ptr = data();
            const auto valueAsVector4DRegister = Simd::makeVector4D(value);
            Simd::storeAligned(Simd::add(Simd::makeVector4DAligned(ptr), valueAsVector4DRegister), ptr);

            Simd::storeAligned(Simd::add(Simd::makeVector4DAligned(ptr + 4), valueAsVector4DRegister), ptr + 4);

            Simd::storeAligned(Simd::add(Simd::makeVector4DAligned(ptr + 8), valueAsVector4DRegister), ptr + 8);

            Simd::storeAligned(Simd::add(Simd::makeVector4DAligned(ptr + 12), valueAsVector4DRegister), ptr + 12);
#else
            m_data[0] += value;
            m_data[1] += value;
            m_data[2] += value;
            m_data[3] += value;
#endif
            return *this;
        }

        [[nodiscard]] Matrix4x4 operator+(double scalar) const
        {
            Matrix4x4 result = *this;
            result += scalar;
            return result;
        }

        Matrix4x4& operator-=(const double value) noexcept
        {
#if defined(MATH_LIB_INTRINSIC)

            double* ptr = data();
            const auto valueAsVector4DRegister = Simd::makeVector4D(value);
            Simd::storeAligned(Simd::sub(Simd::makeVector4DAligned(ptr), valueAsVector4DRegister), ptr);

            Simd::storeAligned(Simd::sub(Simd::makeVector4DAligned(ptr + 4), valueAsVector4DRegister), ptr + 4);

            Simd::storeAligned(Simd::sub(Simd::makeVector4DAligned(ptr + 8), valueAsVector4DRegister), ptr + 8);

            Simd::storeAligned(Simd::sub(Simd::makeVector4DAligned(ptr + 12), valueAsVector4DRegister), ptr + 12);
#else
            m_data[0] -= value;
            m_data[1] -= value;
            m_data[2] -= value;
            m_data[3] -= value;
#endif
            return *this;
        }

        [[nodiscard]] Matrix4x4 operator-(double scalar) const
        {
            Matrix4x4 result = *this;
            result -= scalar;
            return result;
        }

        Matrix4x4& operator*=(const double value) noexcept
        {
#if defined(MATH_LIB_INTRINSIC)

            double* ptr = data();
            const auto valueAsVector4DRegister = Simd::makeVector4D(value);
            Simd::storeAligned(Simd::mul(Simd::makeVector4DAligned(ptr), valueAsVector4DRegister), ptr);

            Simd::storeAligned(Simd::mul(Simd::makeVector4DAligned(ptr + 4), valueAsVector4DRegister), ptr + 4);

            Simd::storeAligned(Simd::mul(Simd::makeVector4DAligned(ptr + 8), valueAsVector4DRegister), ptr + 8);

            Simd::storeAligned(Simd::mul(Simd::makeVector4DAligned(ptr + 12), valueAsVector4DRegister), ptr + 12);
#else
            m_data[0] *= value;
            m_data[1] *= value;
            m_data[2] *= value;
            m_data[3] *= value;
#endif
            return *this;
        }

        [[nodiscard]] Matrix4x4 operator*(double scalar) const
        {
            Matrix4x4 result = *this;
            result *= scalar;
            return result;
        }

        Matrix4x4& operator/=(const double value) noexcept
        {
#if defined(MATH_LIB_INTRINSIC)

            double* ptr = data();
            const auto valueAsVector4DRegister = Simd::makeVector4D(value);
            Simd::storeAligned(Simd::div(Simd::makeVector4DAligned(ptr), valueAsVector4DRegister), ptr);

            Simd::storeAligned(Simd::div(Simd::makeVector4DAligned(ptr + 4), valueAsVector4DRegister), ptr + 4);

            Simd::storeAligned(Simd::div(Simd::makeVector4DAligned(ptr + 8), valueAsVector4DRegister), ptr + 8);

            Simd::storeAligned(Simd::div(Simd::makeVector4DAligned(ptr + 12), valueAsVector4DRegister), ptr + 12);
#else
            m_data[0] /= value;
            m_data[1] /= value;
            m_data[2] /= value;
            m_data[3] /= value;
#endif
            return *this;
        }

        [[nodiscard]] Matrix4x4 operator/(double scalar) const
        {
            Matrix4x4 result = *this;
            result /= scalar;
            return result;
        }

        Matrix4x4& operator+=(const Matrix4x4& rhs) noexcept
        {
#if defined(MATH_LIB_INTRINSIC)

            double* ptr = data();
            const double* otherPtr = rhs.data();
            Simd::storeAligned(Simd::add(Simd::makeVector4DAligned(ptr), Simd::makeVector4DAligned(otherPtr)), ptr);

            Simd::storeAligned(Simd::add(Simd::makeVector4DAligned(ptr + 4), Simd::makeVector4DAligned(otherPtr + 4)),
                               ptr + 4);

            Simd::storeAligned(Simd::add(Simd::makeVector4DAligned(ptr + 8), Simd::makeVector4DAligned(otherPtr + 8)),
                               ptr + 8);

            Simd::storeAligned(Simd::add(Simd::makeVector4DAligned(ptr + 12), Simd::makeVector4DAligned(otherPtr + 12)),
                               ptr + 12);
#else
            m_data[0] += rhs.m_data[0];
            m_data[1] += rhs.m_data[1];
            m_data[2] += rhs.m_data[2];
            m_data[3] += rhs.m_data[3];
#endif

            return *this;
        }

        [[nodiscard]] Matrix4x4 operator+(const Matrix4x4& rhs) const
        {
            Matrix4x4 result = *this;
            result += rhs;
            return result;
        }

        Matrix4x4& operator-=(const Matrix4x4& rhs) noexcept
        {
#if defined(MATH_LIB_INTRINSIC)

            double* ptr = data();
            const double* otherPtr = rhs.data();
            Simd::storeAligned(Simd::sub(Simd::makeVector4DAligned(ptr), Simd::makeVector4DAligned(otherPtr)), ptr);

            Simd::storeAligned(Simd::sub(Simd::makeVector4DAligned(ptr + 4), Simd::makeVector4DAligned(otherPtr + 4)),
                               ptr + 4);

            Simd::storeAligned(Simd::sub(Simd::makeVector4DAligned(ptr + 8), Simd::makeVector4DAligned(otherPtr + 8)),
                               ptr + 8);

            Simd::storeAligned(Simd::sub(Simd::makeVector4DAligned(ptr + 12), Simd::makeVector4DAligned(otherPtr + 12)),
                               ptr + 12);
#else
            m_data[0] -= rhs.m_data[0];
            m_data[1] -= rhs.m_data[1];
            m_data[2] -= rhs.m_data[2];
            m_data[3] -= rhs.m_data[3];
#endif
            return *this;
        }

        [[nodiscard]] Matrix4x4 operator-(const Matrix4x4& rhs) const
        {
            Matrix4x4 result = *this;
            result -= rhs;
            return result;
        }

        [[nodiscard]] Vector4d operator*(const Vector4d& rhs) const noexcept
        {
#if defined(MATH_LIB_INTRINSIC)
            // clang-format off
            const double row1x = m_data[0].getX(); const double row1y = m_data[0].getY(); const double row1z = m_data[0].getZ(); const double row1w = m_data[0].getW();
            const double row2x = m_data[1].getX(); const double row2y = m_data[1].getY(); const double row2z = m_data[1].getZ(); const double row2w = m_data[1].getW();
            const double row3x = m_data[2].getX(); const double row3y = m_data[2].getY(); const double row3z = m_data[2].getZ(); const double row3w = m_data[2].getW();
            const double row4x = m_data[3].getX(); const double row4y = m_data[3].getY(); const double row4z = m_data[3].getZ(); const double row4w = m_data[3].getW();
            // clang-format on

            const Simd::VectorRegister4Double col0 = Simd::makeVector4D(row1x, row2x, row3x, row4x);
            const Simd::VectorRegister4Double col1 = Simd::makeVector4D(row1y, row2y, row3y, row4y);
            const Simd::VectorRegister4Double col2 = Simd::makeVector4D(row1z, row2z, row3z, row4z);
            const Simd::VectorRegister4Double col3 = Simd::makeVector4D(row1w, row2w, row3w, row4w);

            const Simd::VectorRegister4Double x = Simd::makeVector4D(rhs.getX());
            const Simd::VectorRegister4Double y = Simd::makeVector4D(rhs.getY());
            const Simd::VectorRegister4Double z = Simd::makeVector4D(rhs.getZ());
            const Simd::VectorRegister4Double w = Simd::makeVector4D(rhs.getW());

            Simd::VectorRegister4Double result = Simd::mul(col0, x);
            result = Simd::fma(col1, y, result);
            result = Simd::fma(col2, z, result);
            result = Simd::fma(col3, w, result);

            return Vector4d(result);
#else
            return Vector4d(Vector4d::dot(m_data[0], rhs), Vector4d::dot(m_data[1], rhs), Vector4d::dot(m_data[2], rhs),
                            Vector4d::dot(m_data[3], rhs));
#endif // defined(MATH_LIB_INTRINSIC)
        }

        [[nodiscard]] Vector4d operator*(const Vector3<double>& rhs) const noexcept
        {
            return operator*(Vector4d(rhs.getX(), rhs.getY(), rhs.getZ(), 1.0));
        }

        Matrix4x4& operator*=(Matrix4x4 rhs) noexcept
        {
            // because the matrix is row layout and we want to only do an dot product
            // we transopse the other matrix to make the base row * coloms multiplication
            // an row * row multiplication
            rhs.transpose();

            const double m11 = Vector4d::dot(m_data[0], rhs.m_data[0]);
            const double m12 = Vector4d::dot(m_data[0], rhs.m_data[1]);
            const double m13 = Vector4d::dot(m_data[0], rhs.m_data[2]);
            const double m14 = Vector4d::dot(m_data[0], rhs.m_data[3]);
            const Vector4d row1 = Vector4d(m11, m12, m13, m14);

            const double m21 = Vector4d::dot(m_data[1], rhs.m_data[0]);
            const double m22 = Vector4d::dot(m_data[1], rhs.m_data[1]);
            const double m23 = Vector4d::dot(m_data[1], rhs.m_data[2]);
            const double m24 = Vector4d::dot(m_data[1], rhs.m_data[3]);
            const Vector4d row2 = Vector4d(m21, m22, m23, m24);

            const double m31 = Vector4d::dot(m_data[2], rhs.m_data[0]);
            const double m32 = Vector4d::dot(m_data[2], rhs.m_data[1]);
            const double m33 = Vector4d::dot(m_data[2], rhs.m_data[2]);
            const double m34 = Vector4d::dot(m_data[2], rhs.m_data[3]);
            const Vector4d row3 = Vector4d(m31, m32, m33, m34);

            const double m41 = Vector4d::dot(m_data[3], rhs.m_data[0]);
            const double m42 = Vector4d::dot(m_data[3], rhs.m_data[1]);
            const double m43 = Vector4d::dot(m_data[3], rhs.m_data[2]);
            const double m44 = Vector4d::dot(m_data[3], rhs.m_data[3]);
            const Vector4d row4 = Vector4d(m41, m42, m43, m44);

            // clang-format off
            *this = Matrix4x4(row1,
                              row2,
                              row3,
                              row4);
            // clang-format on
            return *this;
        }

        [[nodiscard]] Matrix4x4 operator*(const Matrix4x4& rhs) const noexcept
        {
            Matrix4x4 m = *this;
            m *= rhs;
            return m;
        }

        bool operator==(const Matrix4x4& rhs) const noexcept
        {
            return m_data[0] == rhs.m_data[0] && m_data[1] == rhs.m_data[1] && m_data[2] == rhs.m_data[2] &&
                   m_data[3] == rhs.m_data[3];
        }

        bool operator!=(const Matrix4x4& rhs) const noexcept
        {
            return !this->operator==(rhs);
        }

    private:
        std::array<Vector4d, 4> m_data;
    };

    using Matrix4x4d = Matrix4x4<double>;
} // namespace MathLib

#endif // MATH_LIB_MATRIX4X4D_H
