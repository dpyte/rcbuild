#ifndef RCASYNCINSTALL_H_
#define RCASYNCINSTALL_H_

#include "RcError.hxx"
#include "RcGenSources.hxx"
#include "RcValues.hxx"

namespace RcAsync {
    class RcInstaller {
        private:
            std::vector<RcValueTable_Ptr> rc_generated_values;

        public:
            RcInstaller() = delete;
            explicit RcInstaller(std::vector<RcValueTable_Ptr> &rc_install) noexcept;
            bool rc_async_installer();
    };
}

#endif // RCASYNCINSTALL_H_
