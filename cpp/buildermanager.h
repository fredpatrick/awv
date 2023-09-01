#ifndef AWV_BUILDERMANAGER_HH
#define AWV_BUILDERMANAGER_HH

#include <string>
#include <vector>

namespace awv
{
    class BuilderManager
    {
        public:
            static BuilderManager* instance();
            ~BuilderManager();

            std::vector<std::string> types();
            void                     create_builder(const std::string& type);
        protected:
            BuilderManager();
        private:
            static BuilderManager*   instance_;
            std::vector<std::string> types_{ "layered", "fault"};
    };
}
#endif
