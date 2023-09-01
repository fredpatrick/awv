#include "buildermanager.h"
#include "layeredbuilder.h"
#include "faultbuilder.h"

#include <iostream>

awv::BuilderManager* awv::BuilderManager::instance_ = 0;

awv::BuilderManager*
awv::BuilderManager::
instance()
{
    if ( !instance_ ) {
        instance_ = new BuilderManager();
    }
    return instance_;
}

awv::BuilderManager::
BuilderManager() 
{
}

awv::BuilderManager::
~BuilderManager()
{
}

std::vector<std::string> 
awv::BuilderManager::
types()
{
    return types_;
}

void
awv::BuilderManager::
create_builder(const std::string& type)
{
    if ( type == "layered" ) {
        ModelBuilder* mb = new LayeredBuilder;
    } else if ( type == "fault" ) {
        ModelBuilder* mb = new FaultBuilder;
    }
}

