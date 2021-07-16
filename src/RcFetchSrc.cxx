#include "RcFetchSrc.hxx"
#include "RcError.hxx"

#if defined(__NT__) || defined(_WIN64)
#include "lib/libgit2/include/git2.h"
#else
#include <git2.h>
#endif

// !TODO: replace this method with something that is more verbose.
//     -> Like a progress bar (?)
static void rc_fetch_from_git(const char *rc_clone_loc, const char *rc_git_link) {
    git_repository *repo = nullptr;
    const auto err = git_clone(&repo, rc_git_link, rc_clone_loc, nullptr);
}

bool RcFetchSrc::rc_fetch_source_git(const char *loc, const char *link, RcFetchType rc_type) {
    switch (rc_type) {
        case RcFetchType::GIT:
            rc_fetch_from_git(loc, link);
            break;
        case RcFetchType::CURL:
            break;
    }

    return false;
}
