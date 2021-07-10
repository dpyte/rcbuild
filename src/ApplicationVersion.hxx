#ifndef APPLICATIONVERSION_HXX
#define APPLICATIONVERSION_HXX

#ifndef __USAID_VERSION_MAJOR
#define __USAID_VERSION_MAJOR "0"

#ifndef __USAID_VERSION_MINOR
#define __USAID_VERSION_MINOR "0"

// version modes:
// 	odd: development
// 	even: release
#ifndef __USAID_VERSION_MODE
#define __USAID_VERSION_MODE "1"

#ifndef __GET_USAID_VERSION
#define __GET_USAID_VERSION() __USAID_VERSION_MAJOR "." __USAID_VERSION_MINOR "." __USAID_VERSION_MODE

#define get_usaid_version __GET_USAID_VERSION()

#endif // __GET_USAID_VERSION
#endif // __GET_USAID_VERSION_MODE
#endif // __GET_USAID_VERSION_MINOR
#endif // __GET_USAID_VERSION_MAJOR

#endif // APPLICATIONVERSION_HXX
