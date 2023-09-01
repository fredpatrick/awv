#include "parmstore.h"

#include <iostream>
#include <ios>
#include <fstream>
#include <filesystem>

awv::ParmStore* awv::ParmStore::instance_ = 0;

awv::ParmStore*
awv::ParmStore::
instance()
{
    if ( !instance_ ) {
        instance_ = new ParmStore();
    }
    return instance_;
}

awv::ParmStore::
ParmStore()
{
    std::cout << "awv::ParmStore::ctor" << std::endl;
    model_names_.clear();
    awave_dir_  = "/home/fredpatrick/wrk/awv/dat";
    const std::filesystem::path namesdir{awave_dir_};
    for ( auto const& dir_entry : std::filesystem::directory_iterator{(namesdir)})
    {
        std::string filename = dir_entry.path();
        std::cout << "awv::ParmStore::ctor filname = " << filename << std::endl;
        auto pos = filename.find("_parameters.dat");
        std::cout << "pos = " << pos << std::endl;
        if ( pos != std::string::npos) {
            int ls = awave_dir_.length() + 1;
            std::cout << "ls =  " << ls << std::endl;
            int n  = pos - ls;
            std::cout << "n   = " << n << std::endl;
            std::string s = filename.substr(ls , n);
            std::cout << "awv::ParmStore::ctor model_name = " << s << std::endl;
            model_names_.insert(s);
        }
    }
    is_open_ = false;
}

awv::ParmStore::
~ParmStore()
{
}

std::vector<std::string> 
awv::ParmStore::
names()
{
    std::vector<std::string> nms;
    for ( auto p = model_names_.begin(); p != model_names_.end(); ++p ) {
        nms.push_back(*p);
    }
    return nms;
}

bool
awv::ParmStore::
name_exists(const std::string& model_name)
{
    auto p = model_names_.find(model_name);
    if ( p != model_names_.end() ) return false;
    return true;
}


void
awv::ParmStore::
open( const std::string& model_name)
{
    std::cout << "awv::ParmStore::open, model_name = " << model_name << std::endl;
    model_name_ = model_name;
    filnam_     = awave_dir_ + "/" + model_name_ + "_parameters.dat";
    std::ifstream ifs(filnam_, std::ios_base::in);
    if ( !ifs.is_open() ) {
        std::cout << "awv:ParmStore::open, couldnt open " << filnam_ << std::endl;
        model_name_ = model_name;
        model_type_ = "";
        model_dir_  = "";
        nt_         = 0;
        dt_         = 0.0;
        nx_         = 0;
        dh_         = 0.0;
        nz_         = 0;
        save();
    } else {
        load(ifs);
    }
    is_open_ = true;
}

std::string
awv::ParmStore::
model_name()
{
    if ( !is_open_ ) return " ";
    return model_name_;
}

void
awv::ParmStore::
model_type(const std::string& model_type)
{
    if ( !is_open_ ) return;
    model_type_ = model_type;
}

std::string
awv::ParmStore::
model_type()
{
    if ( !is_open_ ) return " ";
    return model_type_;
}

void
awv::ParmStore::
model_dir(const std::string& model_dir)
{
    if ( !is_open_ ) return;
    model_dir_ = model_dir;
}

std::string
awv::ParmStore::
model_dir()
{
    if ( !is_open_ ) return "";
    return model_dir_;
}

void
awv::ParmStore::
nt(int nta)
{
    std::cout << "awv::ModselParmStore::nt, nt = " << nta << std::endl;
    if ( !is_open_ ) return;
    nt_ = nta;
}

int
awv::ParmStore::
nt()
{
    if ( !is_open_ ) return 0;
    return nt_;
}

void
awv::ParmStore::
nx(int nxa)
{
    if ( !is_open_ ) return;
    nx_ = nxa;
}

int
awv::ParmStore::
nx()
{
    if ( !is_open_ ) return 0;
    return nx_;
}

void
awv::ParmStore::
nz(int nza)
{
    if ( !is_open_ ) return;
    nz_ = nza;
}

int
awv::ParmStore::
nz()
{
    if ( !is_open_ ) return 0;
    return nz_;
}

void
awv::ParmStore::
dt(float dta)
{
    if ( !is_open_ ) return;
    dt_ = dta;
}

float
awv::ParmStore::
dt()
{
    if ( !is_open_ ) return 0.0;
    return dt_;
}

void
awv::ParmStore::
dh(float dha)
{
    if ( !is_open_ ) return;
    dh_ = dha;
}

float
awv::ParmStore::
dh()
{
    if ( !is_open_ ) return 0.0;
    return dh_;
}

void
awv::ParmStore::
save()
{
    std::cout << "awv::ParmStore::save, filnam_ = " << filnam_ << std::endl;
    std::ofstream ofl(filnam_);
    ofl << "model_name " << model_name_ << std::endl;
    ofl << "model_type " << model_type_ << std::endl;
    ofl << "model_dir  " << model_dir_  << std::endl;
    ofl << "nt "  << nt_ << std::endl;
    ofl << "nx "  << nx_ << std::endl;
    ofl << "nz "  << nz_ << std::endl;
    ofl << "dt "  << dt_ << std::endl;
    ofl << "dh "  << dh_ << std::endl;
    ofl.close();
}
    
void
awv::ParmStore::
load(std::ifstream& ifs)
{
    std::cout << "awv::ParmStore::load, filnam_ = " << filnam_ << std::endl;
    std::string tag;
    ifs >> tag >> model_name_;
    ifs >> tag >> model_type_;
    ifs >> tag >> model_dir_;
    ifs >> tag >> nt_;;
    ifs >> tag >> nx_;;
    ifs >> tag >> nz_;;
    ifs >> tag >> dt_;;
    ifs >> tag >> dh_;;
    ifs.close();
}
    
void
awv::ParmStore::
print()
{
}

