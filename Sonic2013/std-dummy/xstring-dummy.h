#pragma once
#include <xstring>

namespace std::dummy
{
    template<typename CharType, typename CharTraits = std::char_traits<CharType>, typename AllocatorType = std::allocator<CharType>>
    class basic_string
    {
    public:
        static constexpr size_t _BUF_SIZE = 16 / sizeof(CharType);
        static constexpr size_t _BUF_CAP = _BUF_SIZE - sizeof(CharType);

        using value_type = CharType;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using traits_type = CharTraits;
        using allocator_type = AllocatorType;

        union _Bxty
        {
            CharType _Buf[_BUF_SIZE];
            pointer _Ptr;
        } _Bx;

        size_t _Mysize = 0; // Length
        size_t _Myres = _BUF_CAP; // Capacity

        // Actually placed at the beginning
        // Placed here to recreate old LWAPI _Mypad behaviour
        allocator_type _Alloc{};

        void reset()
        {
            _Mysize = 0;
            if (_Myres >= _BUF_SIZE)
            {
                _Alloc.deallocate(_Bx._Ptr, _Myres);
            }

            _Bx._Buf[0] = (value_type)0;
            _Myres = _BUF_CAP;
        }

        void set(const_pointer v)
        {
            set(v, traits_type::length(v));
        }

        void set(const_pointer v, size_t l)
        {
            _Mysize = l;
            if (!_Mysize)
            {
                reset();
                return;
            }

            if (_Mysize < _BUF_SIZE)
            {
                traits_type::copy(_Bx._Buf, v, _Mysize);
                
                _Bx._Buf[_Mysize] = (value_type)0;
                _Myres = _BUF_CAP;
                
                return;
            }

            if (_Myres < _Mysize)
            {
                if (_Myres >= _BUF_SIZE)
                {
                    _Alloc.deallocate(_Bx._Ptr, _Myres);
                }

                _Bx._Ptr = _Alloc.allocate(_Mysize + 1);
            }

            traits_type::copy(_Bx._Ptr, v, _Mysize);
            _Bx._Ptr[_Mysize] = (value_type)0;
        }

        bool is_small() const
        {
            return _Myres < _BUF_SIZE;
        }

        size_t size() const
        {
            return _Mysize;
        }

        const_pointer data() const
        {
            if (_Myres >= _BUF_SIZE)
            {
                return _Bx._Ptr;
            }

            return _Bx._Buf;
        }

        pointer data()
        {
            if (_Myres >= _BUF_SIZE)
            {
                return _Bx._Ptr;
            }

            return _Bx._Buf;
        }

        pointer c_str()
        {
            return data();
        }

        const_pointer c_str() const
        {
            return data();
        }

        basic_string()
        {
            reset();
        }

        basic_string(basic_string&& other)
        {
            _Alloc = other._Alloc;
            _Mysize = other._Mysize;
            _Myres = other._Myres;

            memcpy(&_Bx, &other._Bx, sizeof(_Bx));
            memset(&other._Bx, 0, sizeof(_Bx));

            other._Mysize = 0;
            other._Myres = _BUF_CAP;
        }

        basic_string(const basic_string& other)
        {
            set(other.data(), other.size());
        }

        basic_string(const_pointer other)
        {
            set(other);
        }

        basic_string& operator=(const basic_string& other)
        {
            set(other.data(), other.size());
            return *this;
        }

        basic_string& operator=(const_pointer other)
        {
            set(other);
            return *this;
        }

        ~basic_string()
        {
            reset();
        }
    };

    using string = basic_string<char, std::char_traits<char>, std::allocator<char>>;
}