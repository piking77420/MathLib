#ifndef MATH_LIB_MATRIX4X4_H
#define MATH_LIB_MATRIX4X4_H

#include <cstring>
#include <Vector3.hpp>
#include <Vector4.hpp>
#include <AVX.hpp>

namespace MathLib
{
    // Matrix elements are stored in row-major order
    // Mathematical operations use a column-vector convention
    template<typename T>
    class alignas(std::is_same_v<T, float> ? VECTOR4F_ALIGNEMENT : VECTOR4D_ALIGNEMENT) Matrix4x4
    {
    public:
        using _VectorType = Vector4<T>;
#if defined(MATH_LIB_INTRINSIC)
        using _VectorInstrinsic = Vector4<T>::_VectorInstrinsic;
#endif

        explicit Matrix4x4() = default;

        ~Matrix4x4() = default;
        // clang-format off
        MATH_LIB_FORCE_INLINE explicit Matrix4x4(T getM11, T getM12, T getM13, T getM14,
                                                 T getM21, T getM22, T getM23, T getM24,
                                                 T getM31, T getM32, T getM33, T getM34,
                                                 T getM41, T getM42, T getM43, T getM44)
            : m_data{Vector4<T>(getM11, getM12, getM13, getM14), 
                     Vector4<T>(getM21, getM22, getM23, getM24),
                     Vector4<T>(getM31, getM32, getM33, getM34),
                     Vector4<T>(getM41, getM42, getM43, getM44)}
        {

        }
        // clang-format on
        // clang-format off
        MATH_LIB_FORCE_INLINE explicit Matrix4x4(const Vector4<T>& row1, 
                                                 const Vector4<T>& row2, 
                                                 const Vector4<T>& row3,
                                                 const Vector4<T>& row4)
            : m_data{row1, row2, row3, row4}
        {
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE const T* data() const noexcept
        {
            return m_data[0].data();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T* data() noexcept
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

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getM11() const noexcept
        {
            return m_data[0].getX();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getM12() const noexcept
        {
            return m_data[0].getY();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getM13() const noexcept
        {
            return m_data[0].getZ();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getM14() const noexcept
        {
            return m_data[0].getW();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getM21() const noexcept
        {
            return m_data[1].getX();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getM22() const noexcept
        {
            return m_data[1].getY();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getM23() const noexcept
        {
            return m_data[1].getZ();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getM24() const noexcept
        {
            return m_data[1].getW();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getM31() const noexcept
        {
            return m_data[2].getX();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getM32() const noexcept
        {
            return m_data[2].getY();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getM33() const noexcept
        {
            return m_data[2].getZ();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getM34() const noexcept
        {
            return m_data[2].getW();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getM41() const noexcept
        {
            return m_data[3].getX();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getM42() const noexcept
        {
            return m_data[3].getY();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getM43() const noexcept
        {
            return m_data[3].getZ();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getM44() const noexcept
        {
            return m_data[3].getW();
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM11(T getM11) noexcept
        {
            m_data[0].setX(getM11);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM12(T getM12) noexcept
        {
            m_data[0].setY(getM12);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM13(T getM13) noexcept
        {
            m_data[0].setZ(getM13);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM14(T getM14) noexcept
        {
            m_data[0].setW(getM14);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM21(T getM21) noexcept
        {
            m_data[1].setX(getM21);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM22(T getM22) noexcept
        {
            m_data[1].setY(getM22);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM23(T getM23) noexcept
        {
            m_data[1].setZ(getM23);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM24(T getM24) noexcept
        {
            m_data[1].setW(getM24);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM31(T getM31) noexcept
        {
            m_data[2].setX(getM31);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM32(T getM32) noexcept
        {
            m_data[2].setY(getM32);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM33(T getM33) noexcept
        {
            m_data[2].setZ(getM33);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM34(T getM34) noexcept
        {
            m_data[2].setW(getM34);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM41(T getM41) noexcept
        {
            m_data[3].setX(getM41);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM42(T getM42) noexcept
        {
            m_data[3].setY(getM42);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM43(T getM43) noexcept
        {
            m_data[3].setZ(getM43);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM44(T getM44) noexcept
        {
            m_data[3].setW(getM44);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& transpose() noexcept
        {
            T* ptr = reinterpret_cast<T*>(&m_data[0]);

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

        MATH_LIB_FORCE_INLINE T determinant() const noexcept
        {
            return Vector4<T>::dot(m_data[0], Vector4<T>::cross(m_data[1], m_data[2], m_data[3]));
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& inverse() noexcept
        {
            // clang-format off
            const T row1x = m_data[0].getX(); const T row1y = m_data[0].getY(); const T row1z = m_data[0].getZ(); const T row1w = m_data[0].getW();
            const T row2x = m_data[1].getX(); const T row2y = m_data[1].getY(); const T row2z = m_data[1].getZ(); const T row2w = m_data[1].getW();
            const T row3x = m_data[2].getX(); const T row3y = m_data[2].getY(); const T row3z = m_data[2].getZ(); const T row3w = m_data[2].getW();
            const T row4x = m_data[3].getX(); const T row4y = m_data[3].getY(); const T row4z = m_data[3].getZ(); const T row4w = m_data[3].getW();

            T inv[16];
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
            const T determinant = row1x * inv[0] + row1y * inv[4] + row1z * inv[8] + row1w * inv[12];
            if (fuzzyZero(determinant) || !std::isfinite(determinant))
            {
                return *this;
            }

            const T invDeterminant = 1.0 / determinant;
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

        Matrix4x4& operator+=(const T value) noexcept
        {
#if defined(MATH_LIB_INTRINSIC)
            T* ptr = data();
            const _VectorInstrinsic valueAsVector4DRegister = Simd::makeVector4(value);
            Simd::storeAligned(Simd::add(Simd::makeVector4Aligned(ptr), valueAsVector4DRegister), ptr);

            Simd::storeAligned(Simd::add(Simd::makeVector4Aligned(ptr + 4), valueAsVector4DRegister), ptr + 4);

            Simd::storeAligned(Simd::add(Simd::makeVector4Aligned(ptr + 8), valueAsVector4DRegister), ptr + 8);

            Simd::storeAligned(Simd::add(Simd::makeVector4Aligned(ptr + 12), valueAsVector4DRegister), ptr + 12);
#else
            m_data[0] += value;
            m_data[1] += value;
            m_data[2] += value;
            m_data[3] += value;
#endif
            return *this;
        }

        [[nodiscard]] Matrix4x4 operator+(T scalar) const
        {
            Matrix4x4 result = *this;
            result += scalar;
            return result;
        }

        Matrix4x4& operator-=(const T value) noexcept
        {
#if defined(MATH_LIB_INTRINSIC)

            T* ptr = data();
            const auto valueAsVector4DRegister = Simd::makeVector4(value);
            Simd::storeAligned(Simd::sub(Simd::makeVector4Aligned(ptr), valueAsVector4DRegister), ptr);

            Simd::storeAligned(Simd::sub(Simd::makeVector4Aligned(ptr + 4), valueAsVector4DRegister), ptr + 4);

            Simd::storeAligned(Simd::sub(Simd::makeVector4Aligned(ptr + 8), valueAsVector4DRegister), ptr + 8);

            Simd::storeAligned(Simd::sub(Simd::makeVector4Aligned(ptr + 12), valueAsVector4DRegister), ptr + 12);
#else
            m_data[0] -= value;
            m_data[1] -= value;
            m_data[2] -= value;
            m_data[3] -= value;
#endif
            return *this;
        }

        [[nodiscard]] Matrix4x4 operator-(T scalar) const
        {
            Matrix4x4 result = *this;
            result -= scalar;
            return result;
        }

        Matrix4x4& operator*=(const T value) noexcept
        {
#if defined(MATH_LIB_INTRINSIC)

            T* ptr = data();
            const auto valueAsVector4DRegister = Simd::makeVector4(value);
            Simd::storeAligned(Simd::mul(Simd::makeVector4Aligned(ptr), valueAsVector4DRegister), ptr);

            Simd::storeAligned(Simd::mul(Simd::makeVector4Aligned(ptr + 4), valueAsVector4DRegister), ptr + 4);

            Simd::storeAligned(Simd::mul(Simd::makeVector4Aligned(ptr + 8), valueAsVector4DRegister), ptr + 8);

            Simd::storeAligned(Simd::mul(Simd::makeVector4Aligned(ptr + 12), valueAsVector4DRegister), ptr + 12);
#else
            m_data[0] *= value;
            m_data[1] *= value;
            m_data[2] *= value;
            m_data[3] *= value;
#endif
            return *this;
        }

        [[nodiscard]] Matrix4x4 operator*(T scalar) const
        {
            Matrix4x4 result = *this;
            result *= scalar;
            return result;
        }

        Matrix4x4& operator/=(const T value) noexcept
        {
#if defined(MATH_LIB_INTRINSIC)

            T* ptr = data();
            const auto valueAsVector4DRegister = Simd::makeVector4(value);
            Simd::storeAligned(Simd::div(Simd::makeVector4Aligned(ptr), valueAsVector4DRegister), ptr);

            Simd::storeAligned(Simd::div(Simd::makeVector4Aligned(ptr + 4), valueAsVector4DRegister), ptr + 4);

            Simd::storeAligned(Simd::div(Simd::makeVector4Aligned(ptr + 8), valueAsVector4DRegister), ptr + 8);

            Simd::storeAligned(Simd::div(Simd::makeVector4Aligned(ptr + 12), valueAsVector4DRegister), ptr + 12);
#else
            m_data[0] /= value;
            m_data[1] /= value;
            m_data[2] /= value;
            m_data[3] /= value;
#endif
            return *this;
        }

        [[nodiscard]] Matrix4x4 operator/(T scalar) const
        {
            Matrix4x4 result = *this;
            result /= scalar;
            return result;
        }

        Matrix4x4& operator+=(const Matrix4x4& rhs) noexcept
        {
#if defined(MATH_LIB_INTRINSIC)

            T* ptr = data();
            const T* otherPtr = rhs.data();
            Simd::storeAligned(Simd::add(Simd::makeVector4Aligned(ptr), Simd::makeVector4Aligned(otherPtr)), ptr);

            Simd::storeAligned(Simd::add(Simd::makeVector4Aligned(ptr + 4), Simd::makeVector4Aligned(otherPtr + 4)),
                               ptr + 4);

            Simd::storeAligned(Simd::add(Simd::makeVector4Aligned(ptr + 8), Simd::makeVector4Aligned(otherPtr + 8)),
                               ptr + 8);

            Simd::storeAligned(Simd::add(Simd::makeVector4Aligned(ptr + 12), Simd::makeVector4Aligned(otherPtr + 12)),
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

            T* ptr = data();
            const T* otherPtr = rhs.data();
            Simd::storeAligned(Simd::sub(Simd::makeVector4Aligned(ptr), Simd::makeVector4Aligned(otherPtr)), ptr);

            Simd::storeAligned(Simd::sub(Simd::makeVector4Aligned(ptr + 4), Simd::makeVector4Aligned(otherPtr + 4)),
                               ptr + 4);

            Simd::storeAligned(Simd::sub(Simd::makeVector4Aligned(ptr + 8), Simd::makeVector4Aligned(otherPtr + 8)),
                               ptr + 8);

            Simd::storeAligned(Simd::sub(Simd::makeVector4Aligned(ptr + 12), Simd::makeVector4Aligned(otherPtr + 12)),
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

        [[nodiscard]] Vector4<T> operator*(const Vector4<T>& rhs) const noexcept
        {
#if defined(MATH_LIB_INTRINSIC)
            // clang-format off
            const T row1x = m_data[0].getX(); const T row1y = m_data[0].getY(); const T row1z = m_data[0].getZ(); const T row1w = m_data[0].getW();
            const T row2x = m_data[1].getX(); const T row2y = m_data[1].getY(); const T row2z = m_data[1].getZ(); const T row2w = m_data[1].getW();
            const T row3x = m_data[2].getX(); const T row3y = m_data[2].getY(); const T row3z = m_data[2].getZ(); const T row3w = m_data[2].getW();
            const T row4x = m_data[3].getX(); const T row4y = m_data[3].getY(); const T row4z = m_data[3].getZ(); const T row4w = m_data[3].getW();
            // clang-format on

            const _VectorInstrinsic col0 = Simd::makeVector4(row1x, row2x, row3x, row4x);
            const _VectorInstrinsic col1 = Simd::makeVector4(row1y, row2y, row3y, row4y);
            const _VectorInstrinsic col2 = Simd::makeVector4(row1z, row2z, row3z, row4z);
            const _VectorInstrinsic col3 = Simd::makeVector4(row1w, row2w, row3w, row4w);

            const _VectorInstrinsic x = Simd::makeVector4(rhs.getX());
            const _VectorInstrinsic y = Simd::makeVector4(rhs.getY());
            const _VectorInstrinsic z = Simd::makeVector4(rhs.getZ());
            const _VectorInstrinsic w = Simd::makeVector4(rhs.getW());

            _VectorInstrinsic result = Simd::mul(col0, x);
            result = Simd::fma(col1, y, result);
            result = Simd::fma(col2, z, result);
            result = Simd::fma(col3, w, result);

            return Vector4<T>(result);
#else
            return Vector4<T>(Vector4<T>::dot(m_data[0], rhs), Vector4<T>::dot(m_data[1], rhs),
                              Vector4<T>::dot(m_data[2], rhs), Vector4<T>::dot(m_data[3], rhs));
#endif // defined(MATH_LIB_INTRINSIC)
        }

        [[nodiscard]] Vector4<T> operator*(const Vector3<T>& rhs) const noexcept
        {
            return operator*(Vector4<T>(rhs.getX(), rhs.getY(), rhs.getZ(), 1.0));
        }

        Matrix4x4& operator*=(Matrix4x4 rhs) noexcept
        {
            // because the matrix is row layout and we want to only do an dot product
            // we transopse the other matrix to make the base row * coloms multiplication
            // an row * row multiplication
            rhs.transpose();

            const T m11 = Vector4<T>::dot(m_data[0], rhs.m_data[0]);
            const T m12 = Vector4<T>::dot(m_data[0], rhs.m_data[1]);
            const T m13 = Vector4<T>::dot(m_data[0], rhs.m_data[2]);
            const T m14 = Vector4<T>::dot(m_data[0], rhs.m_data[3]);
            const Vector4<T> row1 = Vector4<T>(m11, m12, m13, m14);

            const T m21 = Vector4<T>::dot(m_data[1], rhs.m_data[0]);
            const T m22 = Vector4<T>::dot(m_data[1], rhs.m_data[1]);
            const T m23 = Vector4<T>::dot(m_data[1], rhs.m_data[2]);
            const T m24 = Vector4<T>::dot(m_data[1], rhs.m_data[3]);
            const Vector4<T> row2 = Vector4<T>(m21, m22, m23, m24);

            const T m31 = Vector4<T>::dot(m_data[2], rhs.m_data[0]);
            const T m32 = Vector4<T>::dot(m_data[2], rhs.m_data[1]);
            const T m33 = Vector4<T>::dot(m_data[2], rhs.m_data[2]);
            const T m34 = Vector4<T>::dot(m_data[2], rhs.m_data[3]);
            const Vector4<T> row3 = Vector4<T>(m31, m32, m33, m34);

            const T m41 = Vector4<T>::dot(m_data[3], rhs.m_data[0]);
            const T m42 = Vector4<T>::dot(m_data[3], rhs.m_data[1]);
            const T m43 = Vector4<T>::dot(m_data[3], rhs.m_data[2]);
            const T m44 = Vector4<T>::dot(m_data[3], rhs.m_data[3]);
            const Vector4<T> row4 = Vector4<T>(m41, m42, m43, m44);

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
        std::array<Vector4<T>, 4> m_data;
    };

    using Matrix4x4d = Matrix4x4<double>;
    using Matrix4x4f = Matrix4x4<float>;
} // namespace MathLib

#endif // MATH_LIB_MATRIX4X4_H
