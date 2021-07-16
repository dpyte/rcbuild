#include <utility>
#include "RcValues.hxx"

RcValues::RcValues(std::string pname) : project_name(std::move(pname)) {}

void RcValues::push_location(std::string loc) {
    location = std::move(loc);
}

void  RcValues::push_project_name(std::string pname) {
    project_name = std::move(pname);
}

void RcValues::push_sources(std::string sources) {
    fetch_src = std::move(sources);
}

void RcValues::push_fetch_src(std::string fsrc) {
    fetch_src = std::move(fsrc);
}

void RcValues::push_fetch_type(std::string ftype) {
    fetch_type = std::move(ftype);
}

void RcValues::push_git_depth(int dp) {
    git_depth = dp;
}

std::string RcValues::rcv_title() const {
    return title;
}

std::string RcValues::rcv_project_name() const {
    return project_name;
}

std::string RcValues::rcv_fetch_src() const {
    return fetch_src;
}

std::string RcValues::rcv_fetch_type() const {
    return fetch_type;
}

std::string RcValues::rcv_location() const {
    return location;
}

int RcValues::rcv_git_depth() const {
    return git_depth;
}
