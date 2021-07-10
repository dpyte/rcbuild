#include <utility>

#include "RcValues.hxx"

RcValues::RcValues(std::string title_name, std::string pname, std::string fsources, std::string loc) :
    title(std::move(title_name)), project_name(std::move(pname)), fetch_src(std::move(fsources)),
    location(std::move(loc)) { }

void RcValues::push_location(const std::string &loc) {
    location = loc;
}

void  RcValues::push_project_name(const std::string &pname) {
    project_name = pname;
}

void RcValues::push_sources(const std::string &sources) {
    fetch_src = sources;
}