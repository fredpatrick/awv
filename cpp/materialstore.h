#ifndef AWV_MATERIALSTORE_HH
#define AWV_MATERIALSTORE_HH

#include <string>
#include <map>
#include <utility>

namespace awv
{
    class MaterialStore
    {
        public:
            static MaterialStore* instance();
            ~MaterialStore();

            std::map<int, int>      indexes();
            std::pair<float,float>  properties(int index);
            void                    properties(int index, std::pair<float, float> props);
            void                    erase_properties(int index);
            bool                    index_exists(int index);

            void                    open(const std::string& model_name);
            void                    close();
            void                    save();
            void                    print();

        protected:
            MaterialStore();

        private:
            static MaterialStore* instance_;

            std::string                            awave_dir_;
            std::map<int, std::pair<float, float>> materials_;


            std::string                            model_name_;
            std::string                            filnam_;
            bool                                   is_open_;
    };
}
#endif

