#ifndef AWV_LAYEREDBUILDER_HH
#define AWV_LAYEREDBUILDER_HH

#include "modelbuilder.h"

namespace awv
{
    class LayeredBuilder : public ModelBuilder
    {
        public:
            LayeredBuilder();
            ~LayeredBuilder();
            
            void buildit();
        private:
    };
}
#endif
