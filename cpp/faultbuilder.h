#ifndef AWV_FAULTDBUILDER_HH
#define AWV_FAULTDBUILDER_HH

#include "modelbuilder.h"

namespace awv
{
    class FaultBuilder : public ModelBuilder
    {
        public:
            FaultBuilder();
            ~FaultBuilder();
            
            void buildit();
        private:
    };
}
#endif
