
#ifndef RCBUILD_RCVALUES_HXX
#define RCBUILD_RCVALUES_HXX

#include <string>

class RcValues {
private:
    /*
     * Values:
     *  project_name: Name of the project/ file corresponding to the source to be fetched
     *  fetch_src: source/ URL to the project
     *  fetch_type: GIT, WGET, CURL. Defaults to GIT
     *  location: emplace sources to the listed directory
     */
    std::string title;
    std::string project_name;
    std::string fetch_src;
    std::string fetch_type;
    std::string location;
    int git_depth;

public:
    RcValues() = default;
    explicit RcValues(std::string pname);

    // !TODO: redo push to something more appropriate
    void push_fetch_src(std::string fsrc);
    void push_fetch_type(std::string ftype);
    void push_location(std::string loc);
    void push_project_name(std::string pname);
    void push_sources(std::string source);
    void push_git_depth(int dp);
};


#endif //RCBUILD_RCVALUES_HXX
