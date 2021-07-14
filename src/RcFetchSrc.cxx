#include "RcFetchSrc.hxx"

#include <git2.h>

static void rc_fetch_from_git(const char *rc_clone_loc, const char *rc_git_link) {
    // git_repository *repo = nullptr;
    // const auto err = git_clone(&repo, rc_git_link, rc_clone_loc, nullptr);
}

bool RcFetchSrc::rc_fetch_source_git(const char *loc, const char *link, RcFetchType rc_type) {
    switch (rc_type) {
        case RcFetchType::GIT:
            break;
        case RcFetchType::CURL:
            break;
    }

    return false;
}
