#ifndef SWITCHES_H
#define SWITCHES_H

#include <vector>

#define SWITCHES_MAX_SIZE 32 //from "config_stm32.h"

#include "Logger.h"
#include "TestRunner.h"

#include "enums.h"
#include "mixins.h"
#include "templates.h"

class Switches : public CopyMoveBase, public not_equal<Switches> {
public:
    Switches();
    virtual ~Switches() {};

    uint32_t get_switches() const;
    void update_switches_v() const;

    friend QDebug operator<<(QDebug os, const Switches& r);
    friend std::ostream& operator<<(std::ostream &os, const Switches &r);
    friend bool operator==(const Switches &lhs, const Switches &rhs);
public:
    unsigned int S0 = 0; //:1
    unsigned int S1 = 0;
    unsigned int S2 = 0;
    unsigned int S3 = 0;

    unsigned int S4 = 0;
    unsigned int S5 = 0;
    unsigned int S6 = 0;
    unsigned int S7 = 0;

    unsigned int S8 = 0;
    unsigned int S9 = 0;
    unsigned int S10 = 0;
    unsigned int S11 = 0;

    unsigned int S12 = 0;
    unsigned int S13 = 0;
    unsigned int S14 = 0;
    unsigned int S15 = 0;

    unsigned int S16 = 0;
    unsigned int S17 = 0;
    unsigned int S18 = 0;
    unsigned int S19 = 0;

    unsigned int S20 = 0;
    unsigned int S21 = 0;
    unsigned int S22 = 0;
    unsigned int S23 = 0;

    unsigned int S24 = 0;
    unsigned int S25 = 0;
    unsigned int S26 = 0;
    unsigned int S27 = 0;

    unsigned int S28 = 0;
    unsigned int S29 = 0;
    unsigned int S30 = 0;
    unsigned int S31 = 0;

    int _switches_size = SWITCHES_MAX_SIZE;

    std::vector<std::string> switches_names_v;
    mutable std::vector<unsigned int> switches_v;
};

class U_for_switches : public Switches {
public:
    U_for_switches();

    static uint32_t U_for_switches_default_u;
};

class I_for_switches : public Switches {
public:
    I_for_switches();

    static uint32_t I_for_switches_default_u;
};

class U_rev_switches : public Switches {
public:
    U_rev_switches();

    static uint32_t U_rev_switches_default_u;
};

class I_rev_switches : public Switches {
public:
    I_rev_switches();

    static uint32_t I_rev_switches_default_u;
};

namespace fet2_ns {
    class I_D_switches : public Switches {
    public:
        I_D_switches();

        static uint32_t I_D_switches_default_u;
    };

    class I_D_meas_switches : public Switches {
    public:
        I_D_meas_switches();

        static uint32_t I_D_meas_switches_default_u;
    };

    class U_GS_switches : public Switches {
    public:
        U_GS_switches();

        static uint32_t U_GS_switches_default_u;
    };

    class U_GS_meas_switches : public Switches {
    public:
        U_GS_meas_switches();

        static uint32_t U_GS_meas_switches_default_u;
    };

    class U_GSS_switches : public Switches {
    public:
        U_GSS_switches();

        static uint32_t U_GSS_switches_default_u;
    };

//    class U_GSS_R_switches : public Switches {
//    public:
//        U_GSS_R_switches();

//        static uint32_t U_GSS_R_switches_default_u;
//    };

    class I_GSS_switches : public Switches {
    public:
        I_GSS_switches();

        static uint32_t I_GSS_switches_default_u;
    };

//    class I_GSS_R_switches : public Switches {
//    public:
//        I_GSS_R_switches();

//        static uint32_t I_GSS_R_switches_default_u;
//    };

    class I_DM_switches : public Switches {
    public:
        I_DM_switches();

        static uint32_t I_DM_switches_default_u;
    };

    class I_DL_switches : public Switches {
    public:
        I_DL_switches();

        static uint32_t I_DL_switches_default_u;
    };

    class U_DS_switches : public Switches {
    public:
        U_DS_switches();

        static uint32_t U_DS_switches_default_u;
    };

    class U_DS_L_switches : public Switches {
    public:
        U_DS_L_switches();

        static uint32_t U_DS_L_switches_default_u;
    };

    class U_DS_meas_switches : public Switches {
    public:
        U_DS_meas_switches();

        static uint32_t U_DS_meas_switches_default_u;
    };

    class U_SD_switches : public Switches {
    public:
        U_SD_switches();

        static uint32_t U_SD_switches_default_u;
    };

    class I_S_switches : public Switches {
    public:
        I_S_switches();

        static uint32_t I_S_switches_default_u;
    };

    class I_D_comp_switches : public Switches {
    public:
        I_D_comp_switches();

        static uint32_t I_D_comp_switches_default_u;
    };
}

namespace fet5_ns {
    class I_D_switches : public Switches {
    public:
        I_D_switches();

        static uint32_t I_D_switches_default_u;
    };

    class I_D_meas_switches : public Switches {
    public:
        I_D_meas_switches();

        static uint32_t I_D_meas_switches_default_u;
    };

    class U_GS_switches : public Switches {
    public:
        U_GS_switches();

        static uint32_t U_GS_switches_default_u;
    };

    class U_GS_meas_switches : public Switches {
    public:
        U_GS_meas_switches();

        static uint32_t U_GS_meas_switches_default_u;
    };

    class U_GSS_switches : public Switches {
    public:
        U_GSS_switches();

        static uint32_t U_GSS_switches_default_u;
    };

//    class U_GSS_R_switches : public Switches {
//    public:
//        U_GSS_R_switches();

//        static uint32_t U_GSS_R_switches_default_u;
//    };

    class I_GSS_switches : public Switches {
    public:
        I_GSS_switches();

        static uint32_t I_GSS_switches_default_u;
    };

//    class I_GSS_R_switches : public Switches {
//    public:
//        I_GSS_R_switches();

//        static uint32_t I_GSS_R_switches_default_u;
//    };

    class I_DM_switches : public Switches {
    public:
        I_DM_switches();

        static uint32_t I_DM_switches_default_u;
    };

    class I_DL_switches : public Switches {
    public:
        I_DL_switches();

        static uint32_t I_DL_switches_default_u;
    };

    class U_DS_switches : public Switches {
    public:
        U_DS_switches();

        static uint32_t U_DS_switches_default_u;
    };

    class U_DS_L_switches : public Switches {
    public:
        U_DS_L_switches();

        static uint32_t U_DS_L_switches_default_u;
    };


    class U_DS_meas_switches : public Switches {
    public:
        U_DS_meas_switches();

        static uint32_t U_DS_meas_switches_default_u;
    };

    class U_SD_switches : public Switches {
    public:
        U_SD_switches();

        static uint32_t U_SD_switches_default_u;
    };

    class I_S_switches : public Switches {
    public:
        I_S_switches();

        static uint32_t I_S_switches_default_u;
    };

    class I_D_comp_switches : public Switches {
    public:
        I_D_comp_switches();

        static uint32_t I_D_comp_switches_default_u;
    };
}

static U_for_switches U_for_switches_default;
static I_for_switches I_for_switches_default;
static U_rev_switches U_rev_switches_default;
static I_rev_switches I_rev_switches_default;

namespace fet2_ns {
    static fet2_ns::I_D_switches I_D_switches_default;
    static fet2_ns::I_D_meas_switches I_D_meas_switches_default;
    static fet2_ns::U_GS_switches U_GS_switches_default;
    static fet2_ns::U_GS_meas_switches U_GS_meas_switches_default;
    static fet2_ns::U_GSS_switches U_GSS_switches_default;
    //static U_GSS_R_switches U_GSS_R_switches_default;
    static fet2_ns::I_GSS_switches I_GSS_switches_default;
    //static I_GSS_R_switches I_GSS_R_switches_default;
    static fet2_ns::I_DM_switches I_DM_switches_default;
    static fet2_ns::I_DL_switches I_DL_switches_default;
    static fet2_ns::U_DS_switches U_DS_switches_default;
    static fet2_ns::U_DS_L_switches U_DS_L_switches_default;
    static fet2_ns::U_DS_meas_switches U_DS_meas_switches_default;
    static fet2_ns::U_SD_switches U_SD_switches_default;
    static fet2_ns::I_S_switches I_S_switches_default;
    static fet2_ns::I_D_comp_switches I_D_comp_switches_default;
}

namespace fet5_ns {
    static fet5_ns::I_D_switches I_D_switches_default;
    static fet5_ns::I_D_meas_switches I_D_meas_switches_default;
    static fet5_ns::U_GS_switches U_GS_switches_default;
    static fet5_ns::U_GS_meas_switches U_GS_meas_switches_default;
    static fet5_ns::U_GSS_switches U_GSS_switches_default;
    //static U_GSS_R_switches U_GSS_R_switches_default;
    static fet5_ns::I_GSS_switches I_GSS_switches_default;
    //static I_GSS_R_switches I_GSS_R_switches_default;
    static fet5_ns::I_DM_switches I_DM_switches_default;
    static fet5_ns::I_DL_switches I_DL_switches_default;
    static fet5_ns::U_DS_switches U_DS_switches_default;
    static fet5_ns::U_DS_L_switches U_DS_L_switches_default;
    static fet5_ns::U_DS_meas_switches U_DS_meas_switches_default;
    static fet5_ns::U_SD_switches U_SD_switches_default;
    static fet5_ns::I_S_switches I_S_switches_default;
    static fet5_ns::I_D_comp_switches I_D_comp_switches_default;
}

#endif // SWITCHES_H
