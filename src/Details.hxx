#ifndef RCBUILD_DETAILS_HXX
#define RCBUILD_DETAILS_HXX

#if defined(__cplusplus)
#define RCEXTERN extern "C"
#else
#define RCEXTERN extern
#endif

static constexpr auto RCBUILD_MAX = 32;

#define For(Iter, Iterable) for(typeof((Iterable).begin()) (Iter) = (Iterable).begin(); (Iter) != (Iterable).end(); (Iter)++)

#endif //RCBUILD_DETAILS_HXX
