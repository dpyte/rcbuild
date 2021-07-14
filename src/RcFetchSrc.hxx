#ifndef RCFETCHSRC_HXX_
#define RCFETCHSRC_HXX_

namespace RcFetchSrc {
    enum RcFetchType {
        GIT,
        CURL,
    };

    bool rc_fetch_source_git(const char *loc, const char *link, RcFetchType rc_type);
}

#endif // RCFETCHSRC_H_
