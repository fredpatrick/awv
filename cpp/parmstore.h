#ifndef AWV_PARMSTORE_HH
#define AWV_PARMSTORE_HH

#include <string>
#include <vector>
#include <set>

namespace awv
{

    class ParmStore
    {
        public:
            static ParmStore* instance();
            ~ParmStore();

            std::vector<std::string> names();
            bool                     name_exists(const std::string& model_name);
            void                     open(const std::string& model_name);

            void         model_type(const std::string& model_type);
            void         model_dir (const std::string& model_dir );

            std::string  model_name();
            std::string  model_type();
            std::string  model_dir ();
            void         nt(int nta);
            int          nt();
            void         nx(int ntx);
            int          nx();
            void         nz(int ntz);
            int          nz();
            void         dt(float dta);
            float        dt();
            void         dh(float dha);
            float        dh();

            void         save();
            void         load(std::ifstream& ifs);
            void         print();

        protected:
            ParmStore();

        private:
            static ParmStore* instance_;

            bool                  is_open_;
            std::set<std::string> model_names_;
            std::string           model_name_;
            std::string           awave_dir_;
            std::string           filnam_;
            std::string           model_type_;
            std::string           model_dir_;
            int                   nt_;
            int                   nx_;
            int                   nz_;
            float                 dt_;
            float                 dh_;
    };
}
#endif
