#ifndef AWV_MODELBUILDER_HH
#define AWV_MODELBUILDER_HH

namespace awv
{
    class ModelBuilder
    {
        public:
            ModelBuilder();
            ~ModelBuilder();

            virtual void buildit() = 0;
        private:
    };
}
#endif
