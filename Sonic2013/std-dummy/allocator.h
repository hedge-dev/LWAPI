#pragma once

namespace std::dummy
{
    // CLASS TEMPLATE allocator
    template <class _Ty>
    class allocator {
    public:
        static_assert(!is_const_v<_Ty>, "The C++ Standard forbids containers of const elements "
            "because allocator<const T> is ill-formed.");

        using _From_primary = allocator;

        using value_type = _Ty;

        _CXX17_DEPRECATE_OLD_ALLOCATOR_MEMBERS typedef _Ty* pointer;
        _CXX17_DEPRECATE_OLD_ALLOCATOR_MEMBERS typedef const _Ty* const_pointer;

        _CXX17_DEPRECATE_OLD_ALLOCATOR_MEMBERS typedef _Ty& reference;
        _CXX17_DEPRECATE_OLD_ALLOCATOR_MEMBERS typedef const _Ty& const_reference;

        using size_type = size_t;
        using difference_type = ptrdiff_t;

        using propagate_on_container_move_assignment = true_type;
        using is_always_equal _CXX17_DEPRECATE_OLD_ALLOCATOR_MEMBERS = true_type;

        template <class _Other>
        struct _CXX17_DEPRECATE_OLD_ALLOCATOR_MEMBERS rebind {
            using other = allocator<_Other>;
        };

        _CXX17_DEPRECATE_OLD_ALLOCATOR_MEMBERS _NODISCARD _Ty* address(_Ty& _Val) const noexcept {
            return _STD addressof(_Val);
        }

        _CXX17_DEPRECATE_OLD_ALLOCATOR_MEMBERS _NODISCARD const _Ty* address(const _Ty& _Val) const noexcept {
            return _STD addressof(_Val);
        }

        constexpr allocator() noexcept {}

        constexpr allocator(const allocator&) noexcept = default;
        template <class _Other>
        constexpr allocator(const allocator<_Other>&) noexcept {}

        void deallocate(_Ty* const _Ptr, const size_t _Count) {
            // no overflow check on the following multiply; we assume _Allocate did that check
            __HH_FREE(_Ptr);
        }

        _NODISCARD __declspec(allocator) _Ty* allocate(_CRT_GUARDOVERFLOW const size_t _Count) {
            return static_cast<_Ty*>(__HH_ALLOCALIGN(sizeof(_Ty) * _Count, alignof(_Ty)));
        }

        _CXX17_DEPRECATE_OLD_ALLOCATOR_MEMBERS _NODISCARD __declspec(allocator) _Ty* allocate(
            _CRT_GUARDOVERFLOW const size_t _Count, const void*) {
            return allocate(_Count);
        }

        template <class _Objty, class... _Types>
        _CXX17_DEPRECATE_OLD_ALLOCATOR_MEMBERS void construct(_Objty* const _Ptr, _Types&&... _Args) {
            ::new (const_cast<void*>(static_cast<const volatile void*>(_Ptr))) _Objty(_STD forward<_Types>(_Args)...);
        }

        template <class _Uty>
        _CXX17_DEPRECATE_OLD_ALLOCATOR_MEMBERS void destroy(_Uty* const _Ptr) {
            _Ptr->~_Uty();
        }

        _CXX17_DEPRECATE_OLD_ALLOCATOR_MEMBERS _NODISCARD size_t max_size() const noexcept {
            return static_cast<size_t>(-1) / sizeof(_Ty);
        }
    };
}