#include "materialstore.h"

#include <iostream>
#include <ios>
#include <fstream>

awv::MaterialStore* awv::MaterialStore::instance_ = 0;

awv::MaterialStore*
awv::MaterialStore::
instance()
{
    if ( !instance_ ) {
        instance_ = new MaterialStore();
    }
    return instance_;
}

awv::MaterialStore::
MaterialStore()
{
    std::cout << "awv::MaterialStore-ctor" << std::endl;
    awave_dir_ = "/home/fredpatrick/wrk/awv/dat";
    is_open_ = false;
}

awv::MaterialStore::
~MaterialStore()
{
}

void
awv::MaterialStore::
open(const std::string& model_name)
{
    std::cout << "awv::MaterialStore::open, model_name = " << model_name << std::endl;
    model_name_ = model_name;
    filnam_     = awave_dir_ + "/" + model_name_ + "_materials.dat";
    std::ifstream ifs(filnam_,std::ios_base::in);
    if ( !ifs ) {
        std::cout << "awv::MaterialStore::open, filename = " << 
                                   filnam_ << " failed to open" << std::endl;
        return;
    }
    materials_.clear();
    if ( ifs.is_open() ) {
        int    index;
        std::pair<float, float> prop;
        ifs >> index >> prop.first >> prop.second;
        materials_.insert( make_pair(index, prop) );
        while ( !ifs.eof() ) {
            ifs >> index >> prop.first >> prop.second;
            materials_.insert(make_pair(index, prop) );
            std::cout << "awv""MaterialStore::open - " << index << " " <<
                                         prop.first << " " << prop.second << std::endl;
        }
        ifs.close();
        is_open_ = true;
        std::cout << "awv::MaterialStore::open - loaded materials from " << 
                         filnam_ << std::endl;
    }
}

std::map<int, int> 
awv::MaterialStore::
indexes()
{
    if ( !is_open_ ) return std::map<int,int>{std::make_pair(0,0) };
    std::map<int, int> row_map;
    int irow = 0;
    for ( auto p = materials_.begin(); p != materials_.end(); p++) {
        irow += 1; 
        int  index = p->first;
        row_map.insert(std::make_pair(index, irow) );
        std::cout << "awv::MaterialStore::indexes() - index = " << 
                                           index << ", irowe = " << irow << std::endl;
    }
    return row_map;
}

void
awv::MaterialStore::
save()
{
    if ( !is_open_ ) return;
    std::ofstream ofs(filnam_, std::ios_base::out);
    for ( auto p = materials_.begin(); p != materials_.end(); ++p) {
        int index = p->first;
        std::pair<float, float> props = p->second;
        ofs << index << " " << props.first << " " << props.second << std::endl;
        std::cout << "awv::MaterialStore::close - " << 
                           index << " " << props.first << " " << props.second << std::endl;
    }
    ofs.close();
}

void
awv::MaterialStore::
close()
{
    is_open_ = false;
}

void
awv::MaterialStore::
print()
{
    if ( !is_open_ ) return;
    for ( auto p = materials_.begin(); p != materials_.end(); ++p) {
        int index = p->first;
        std::pair<float, float> prop  = p->second;
        std::cout << "awv::MaterialStore::print - " << 
                           index << " " << prop.first << " " << prop.second << std::endl;
    }
}

bool
awv::MaterialStore::
index_exists( int index)
{
    if ( !is_open_ ) return false;
//  std::cout << "awv::MaterialStore::index_exists, index = " << index << std::endl;
    auto p = materials_.find(index);
    if ( p != materials_.end() ) return true;
    return false;
}

std::pair<float, float> 
awv::MaterialStore::
properties(int index)
{
    if ( !is_open_ ) return std::make_pair(0.0, 0.0);
    auto p = materials_.find(index);
    if ( p != materials_.end() ) {
        return p->second;
    } else {
        std::cout << "awv::MaterialStore::properties, bad index = " << index << std::endl;
        return std::make_pair(0.0, 0.0);
    }
}

void
awv::MaterialStore::
properties(int index, std::pair<float, float> props)
{
    if ( !is_open_ ) return;
    materials_.insert( std::make_pair(index, props) );
    std::cout << "awv::MaterialStore::properties - " << 
                 index << " " << props.first << " " << props.second << std::endl;
    std::cout << "awv::MatriealStore::properties - size = " << materials_.size() << std::endl;
}

void
awv::MaterialStore::
erase_properties(int index)
{
    if ( !is_open_ ) return;
    int n = materials_.erase(index);
    std::cout << "awv::MaterialStore::erase_properties - " << n << 
                      " properiteis with index = " << index << " erased" << std::endl;
}

