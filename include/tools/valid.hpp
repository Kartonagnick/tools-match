
// [2021y-02m-05d] Idrisov Denis R.
#pragma once
#ifndef dTOOLS_VALID_USED_
#define dTOOLS_VALID_USED_ 100
#include <tools/features.hpp>
//==============================================================================
//==============================================================================
namespace tools
{
    #define dATTRIBUTES \
        dNODISCARD dCONSTEXPR_CPP11

    #define dTEMPLATE \
        template<class t> dATTRIBUTES

    namespace stringed_v1
    {
        dTEMPLATE bool valid(t*& p)                dNOEXCEPT { return p != 0; }
        dTEMPLATE bool valid(t* const& p)          dNOEXCEPT { return p != 0; }
        dTEMPLATE bool valid(t* volatile& p)       dNOEXCEPT { return p != 0; }
        dTEMPLATE bool valid(t* volatile const& p) dNOEXCEPT { return p != 0; }

        dTEMPLATE bool valid(t&) dNOEXCEPT 
            { return true; }

        #ifdef dHAS_CPP11

        dATTRIBUTES bool valid(nullptr_t&) dNOEXCEPT 
            { return false; }

        dATTRIBUTES bool valid(const nullptr_t&) dNOEXCEPT 
            { return false; }

        #endif // !dHAS_CPP11

    } // namespace stringed_v1

    #ifdef dHAS_CPP11
        dTEMPLATE bool valid(t&& p) dNOEXCEPT 
            { return ::tools::stringed_v1::valid(p); }
    #else
        dTEMPLATE bool valid(const t& p) dNOEXCEPT 
        { 
            return ::tools::stringed_v1::valid(p);
        }
    #endif // !dHAS_CPP11

    #undef dATTRIBUTES
    #undef dTEMPLATE

} // namespace tools 
//==============================================================================
//==============================================================================
#endif // !dTOOLS_VALID_USED_

