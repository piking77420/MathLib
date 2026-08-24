#ifndef MATH_LIB_ALLOC_H
#define MATH_LIB_ALLOC_H

#include <cstdlib>
#include <memory>

#if defined(_MSC_VER)
#include <malloc.h>
#endif

#include <BenchmarkHeader.hpp>
#include <MathLibHeader.hpp>

namespace Alloc
{
    template<typename T>
    [[nodiscard]] T* alignMalloc(std::size_t count, std::size_t alignment)
    {
        const std::size_t size = sizeof(T) * count;
        static_assert(std::is_trivially_constructible_v<T>);
#if defined(_MSC_VER)
        return static_cast<T*>(_aligned_malloc(size, alignment));
#else
        // std::aligned_alloc requires size to be a multiple of alignment.
        return static_cast<T*>(std::aligned_alloc(alignment, MathLib::alignedSize(size, alignment)));
#endif
    }

    void freeAlignedMalloc(void* ptr);

    template<typename T, size_t OffsetPerElement>
    class Iterator
    {
    public:
        static constexpr size_t _OffsetPerElement = OffsetPerElement;
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using difference_type = std::ptrdiff_t;

        Iterator(std::uint8_t* ptr)
            : m_ptr(ptr)
        {
        }

        reference operator*() const noexcept
        {
            return *reinterpret_cast<T*>(m_ptr);
        }

        pointer operator->() const noexcept
        {
            return reinterpret_cast<T*>(m_ptr);
        }

        Iterator& operator++() noexcept
        {
            m_ptr += _OffsetPerElement;
            return *this;
        }

        bool operator==(const Iterator&) const = default;

    private:
        std::byte* m_ptr = nullptr;
    };

    template<typename T, std::size_t OffsetPerElement>
    class ConstIterator
    {
    public:
        static constexpr std::size_t _OffsetPerElement = OffsetPerElement;

        using value_type = T;
        using reference = const T&;
        using pointer = const T*;
        using difference_type = std::ptrdiff_t;

        explicit ConstIterator(const std::uint8_t* ptr) noexcept
            : m_ptr(ptr)
        {
        }

        reference operator*() const noexcept
        {
            return *reinterpret_cast<const T*>(m_ptr);
        }

        pointer operator->() const noexcept
        {
            return reinterpret_cast<const T*>(m_ptr);
        }

        ConstIterator& operator++() noexcept
        {
            m_ptr += _OffsetPerElement;
            return *this;
        }

        bool operator==(const ConstIterator&) const = default;

    private:
        const std::byte* m_ptr = nullptr;
    };

    template<typename T>
    class HardwareAlignedVector
    {
    public:
        using ElementType = T;

        static constexpr std::size_t Alignment = std::max(MathLib::HardwareDestructiveInterferenceSize, alignof(T));
        static constexpr std::size_t OffsetPerElement = MathLib::alignedSize(sizeof(T), Alignment);
        using iterator = Iterator<T, OffsetPerElement>;
        using const_iterator = ConstIterator<T, OffsetPerElement>;

        HardwareAlignedVector() = default;
        ~HardwareAlignedVector()
        {
            destroyAndDeallocate();
        }
        HardwareAlignedVector(const HardwareAlignedVector&) = delete;
        HardwareAlignedVector& operator=(const HardwareAlignedVector&) = delete;

        HardwareAlignedVector(HardwareAlignedVector&& other) noexcept
            : m_data(other.m_data)
            , m_size(other.m_size)
            , m_capacity(other.m_capacity)
        {
            other.m_data = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
        }

        HardwareAlignedVector& operator=(HardwareAlignedVector&& other) noexcept
        {
            if (this == &other)
                return *this;

            destroyAndDeallocate();

            m_data = other.m_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;

            other.m_data = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;

            return *this;
        }

        [[nodiscard]] iterator begin() noexcept
        {
            return iterator(m_data);
        }

        [[nodiscard]] iterator end() noexcept
        {
            return iterator(m_data == nullptr ? nullptr : m_data + m_size * OffsetPerElement);
        }

        [[nodiscard]] const_iterator begin() const noexcept
        {
            return const_iterator(m_data);
        }

        [[nodiscard]] const_iterator end() const noexcept
        {
            return const_iterator(m_data == nullptr ? nullptr : m_data + m_size * OffsetPerElement);
        }

        [[nodiscard]] const_iterator cbegin() const noexcept
        {
            return begin();
        }

        [[nodiscard]] const_iterator cend() const noexcept
        {
            return end();
        }

        [[nodiscard]] T& operator[](std::size_t index) noexcept
        {
            return *elementPtr(index);
        }

        [[nodiscard]] const T& operator[](std::size_t index) const noexcept
        {
            return *elementPtr(index);
        }

        [[nodiscard]] T& front() noexcept
        {
            return (*this)[0];
        }

        [[nodiscard]] const T& front() const noexcept
        {
            return (*this)[0];
        }

        [[nodiscard]] T& back() noexcept
        {
            return (*this)[m_size - 1];
        }

        [[nodiscard]] const T& back() const noexcept
        {
            return (*this)[m_size - 1];
        }

        [[nodiscard]] std::size_t size() const noexcept
        {
            return m_size;
        }

        [[nodiscard]] std::size_t capacity() const noexcept
        {
            return m_capacity;
        }

        [[nodiscard]] bool empty() const noexcept
        {
            return m_size == 0;
        }

        void reserve(std::size_t newCapacity)
        {
            if (newCapacity <= m_capacity)
                return;

            // realloc
            std::byte* newData = allocate(newCapacity);
            std::size_t constructedCount = 0;
            for (; constructedCount < m_size; ++constructedCount)
            {
                std::construct_at(reinterpret_cast<T*>(newData + constructedCount * OffsetPerElement),
                                  std::move_if_noexcept(*elementPtr(constructedCount)));
            }

            destroyElements();
            deallocate(m_data);

            m_data = newData;
            m_capacity = newCapacity;
        }

        void push_back(const T& element)
        {
            ensureCapacity();

            std::construct_at(elementPtr(m_size), element);

            ++m_size;
        }

        void push_back(T&& element)
        {
            ensureCapacity();

            std::construct_at(elementPtr(m_size), std::move(element));

            ++m_size;
        }

        template<typename... Args>
        T& emplace_back(Args&&... args)
        {
            ensureCapacity();

            T* ptr = elementPtr(m_size);

            std::construct_at(ptr, std::forward<Args>(args)...);

            m_size++;

            return *ptr;
        }

        void pop_back() noexcept
        {
            m_size--;
            std::destroy_at(elementPtr(m_size));
        }

        void clear() noexcept
        {
            destroyElements();
            m_size = 0;
        }

    private:
        [[nodiscard]] static std::byte* allocate(std::size_t capacity)
        {
            if (capacity == 0)
                return nullptr;

            return static_cast<std::byte*>(::operator new(capacity * OffsetPerElement, std::align_val_t{Alignment}));
        }

        static void deallocate(std::byte* ptr) noexcept
        {
            if (ptr == nullptr)
                return;

            ::operator delete(ptr, std::align_val_t{Alignment});
        }

        [[nodiscard]] T* elementPtr(std::size_t index) noexcept
        {
            return reinterpret_cast<T*>(m_data + index * OffsetPerElement);
        }

        [[nodiscard]] const T* elementPtr(std::size_t index) const noexcept
        {
            return reinterpret_cast<const T*>(m_data + index * OffsetPerElement);
        }

        void ensureCapacity()
        {
            if (m_size == m_capacity)
            {
                reserve(m_capacity == 0 ? 1 : m_capacity * 2);
            }
        }

        void destroyElements() noexcept
        {
            for (std::size_t i = 0; i < m_size; ++i)
            {
                std::destroy_at(elementPtr(i));
            }
        }

        void destroyAndDeallocate() noexcept
        {
            destroyElements();
            deallocate(m_data);

            m_data = nullptr;
            m_size = 0;
            m_capacity = 0;
        }

        std::byte* m_data = nullptr;

        std::size_t m_size = 0;
        std::size_t m_capacity = 0;
    };

} // namespace Alloc

#endif // MATH_LIB_ALLOC_H
