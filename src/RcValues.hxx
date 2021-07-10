
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

public:
    RcValues() = default;
    explicit RcValues(
                    std::string title_name,
                    std::string pname,
                    std::string fsources,
                    std::string loc);


    // !TODO: redo push to something more appropriate
    void push_sources(const std::string &source);
    void push_location(const std::string &loc);
    void push_project_name(const std::string &pname);
};


#endif //RCBUILD_RCVALUES_HXX
