include(FetchContent)

FetchContent_Declare(   googletest
    GIT_REPOSITORY      https://github.com/google/googletest
    GIT_TAG             release-1.10.0
)

set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(GTEST_LINKED_AS_SHARED_LIBRARY ON CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)