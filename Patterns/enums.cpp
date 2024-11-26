#include "enums.h"

/////////////////////////// range ///////////////////////////
SignalName signal_from_calibration_signal(CalibrationSignalName calibration_signal_name) {
    SignalName signal_name = static_cast<SignalName>(calibration_signal_name);
    switch (calibration_signal_name) {
        case CalibrationSignal_I_for_tune:
        case CalibrationSignal_I_for_duration:
            signal_name = Signal_I_for;
        break;
        break;
        case CalibrationSignal_U_rev_tune:
        case CalibrationSignal_U_rev_duration:
            signal_name = Signal_U_rev;
        break;

        case CalibrationSignal_I_D_duration:
            signal_name = Signal_I_D;
        break;
        case CalibrationSignal_U_GS_duration:
            signal_name = Signal_U_GS;
        break;
        case CalibrationSignal_U_GSS_duration:
            signal_name = Signal_U_GSS;
        break;
        case CalibrationSignal_U_DS_duration:
            signal_name = Signal_U_DS;
        break;
        case CalibrationSignal_U_DS_L_duration:
            signal_name = Signal_U_DS_L;
        break;
        case CalibrationSignal_I_S_duration:
            signal_name = Signal_I_S;
        break;
        default:

        break;
    }
    return signal_name;
}

QString signal_range_to_text(const SignalName signal, const int range) {
    QString range_name = "Авто";
    switch (signal) {
        case Signal_U_for:
            range_name = Range_U_for_to_text(static_cast<Range_U_for>(range));
        break;
        case Signal_I_for:
            range_name = Range_I_for_to_text(static_cast<Range_I_for>(range));
        break;
        case Signal_U_rev:
            range_name = Range_U_rev_to_text(static_cast<Range_U_rev>(range));
        break;
        case Signal_I_rev:
            range_name = Range_I_rev_to_text(static_cast<Range_I_rev>(range));
        break;


        case Signal_I_D:
            range_name = ModeRange_I_D_to_text(static_cast<ModeRange_I_D>(range));
        break;
        case Signal_I_D_meas:
            range_name = MeasureRange_I_D_to_text(static_cast<MeasureRange_I_D>(range));
        break;
        case Signal_U_GS:
            range_name = ModeRange_U_GS_to_text(static_cast<ModeRange_U_GS>(range));
        break;
        case Signal_U_GS_meas:
            range_name = MeasureRange_U_GS_to_text(static_cast<MeasureRange_U_GS>(range));
        break;
        case Signal_U_GSS:
            range_name = ModeRange_U_GSS_to_text(static_cast<ModeRange_U_GSS>(range));
        break;
//        case Signal_U_GSS_R:
//            range_name = Range_U_GSS_R_to_text(static_cast<Range_U_GSS_R>(range));
//        break;
        case Signal_I_GSS:
            range_name = MeasureRange_I_GSS_to_text(static_cast<MeasureRange_I_GSS>(range));
        break;
//        case Signal_I_GSS_R:
//            range_name = Range_I_GSS_R_to_text(static_cast<Range_I_GSS_R>(range));
//        break;
        case Signal_I_DM_meas:
            range_name = MeasureRange_I_DM_to_text(static_cast<MeasureRange_I_DM>(range));
        break;
        case Signal_I_DL_meas:
            range_name = MeasureRange_I_DL_to_text(static_cast<MeasureRange_I_DL>(range));
        break;
        case Signal_U_DS:
            range_name = ModeRange_U_DS_to_text(static_cast<ModeRange_U_DS>(range));
        break;
        case Signal_U_DS_L:
            range_name = ModeRange_U_DS_L_to_text(static_cast<ModeRange_U_DS_L>(range));
            break;
        case Signal_U_DS_meas:
            range_name = MeasureRange_U_DS_to_text(static_cast<MeasureRange_U_DS>(range));
        break;
        case Signal_U_SD:
            range_name = MeasureRange_U_SD_to_text(static_cast<MeasureRange_U_SD>(range));
        break;
        case Signal_I_S:
            range_name = ModeRange_I_S_to_text(static_cast<ModeRange_I_S>(range));
        break;
        case Signal_I_DM:
            range_name = ModeRange_I_DM_to_text(static_cast<ModeRange_I_DM>(range));
        break;
//        case Signal_I_DL:
//            range_name = ModeRange_I_DL_to_text(static_cast<ModeRange_I_DL>(range));
//        break;
        case Signal_I_D_comp:
            range_name = ModeRange_I_D_comp_to_text(static_cast<ModeRange_I_D_comp>(range));
        break;
        default:

        break;
    }
    return range_name;
}

QString any_range_to_text(const int signal, const int range) {
    Q_UNUSED(range)
    std::string res = "Авто";
    switch (signal) {
        case 1: //I_for
        case 6: //I_for_tune
        case 10: //I_for_duration
            res = Range_I_for_to_text(static_cast<Range_I_for>(range));
        break;
        case 2: //U_for_D1
        case 8: //U_for_D2
            res = Range_U_for_to_text(static_cast<Range_U_for>(range));
        break;
        case 3: //I_rev_D1
        case 9: //I_rev_D2
            res = Range_I_rev_to_text(static_cast<Range_I_rev>(range));
        break;
        case 4: //U_rev
        case 7: //U_rev_tune
        case 11: //U_rev_duration
            res = Range_U_rev_to_text(static_cast<Range_U_rev>(range));
        break;
        case 5: //PFM
            res = Range_PFM_to_text(static_cast<Range_PFM>(range));
        break;


        case 101: //Signal_I_D
            res = ModeRange_I_D_to_text(static_cast<ModeRange_I_D>(range));
        break;
        case 102: //Signal_I_D_meas
            res = MeasureRange_I_D_to_text(static_cast<MeasureRange_I_D>(range));
        break;
        case 103: //Signal_U_GS
            res = ModeRange_U_GS_to_text(static_cast<ModeRange_U_GS>(range));
        break;
        case 104: //Signal_U_GS_meas
            res = MeasureRange_U_GS_to_text(static_cast<MeasureRange_U_GS>(range));
        break;
        case 105: //Signal_U_GSS
            res = ModeRange_U_GSS_to_text(static_cast<ModeRange_U_GSS>(range));
        break;
//        case 106: //Signal_U_GSS_R
//            res = Range_U_GSS_R_to_text(static_cast<Range_U_GSS_R>(range));
//        break;
        case 107: //Signal_I_GSS
            res = MeasureRange_I_GSS_to_text(static_cast<MeasureRange_I_GSS>(range));
        break;
//        case 108: //Signal_I_GSS_R
//            res = Range_I_GSS_R_to_text(static_cast<Range_I_GSS_R>(range));
//        break;
        case 109: //Signal_I_DM
            res = MeasureRange_I_DM_to_text(static_cast<MeasureRange_I_DM>(range));
        break;
        case 110: //Signal_I_DL
            res = MeasureRange_I_DL_to_text(static_cast<MeasureRange_I_DL>(range));
        break;
            //111 - Signal_R_DS
            //112 - Signal_S
        case 113: //Signal_U_DS
            res = ModeRange_U_DS_to_text(static_cast<ModeRange_U_DS>(range));
        break;
        case 114: //Signal_U_DS_L
            res = ModeRange_U_DS_L_to_text(static_cast<ModeRange_U_DS_L>(range));
            break;
        case 115: //Signal_U_DS_meas
            res = MeasureRange_U_DS_to_text(static_cast<MeasureRange_U_DS>(range));
        break;
        case 116: //Signal_U_SD
            res = MeasureRange_U_SD_to_text(static_cast<MeasureRange_U_SD>(range));
        break;
        case 117: //I_S
            res = ModeRange_I_S_to_text(static_cast<ModeRange_I_S>(range));
        break;
        case 118: //I_DM
            res = ModeRange_I_DM_to_text(static_cast<ModeRange_I_DM>(range));
        break;
//        case 119: //I_DL
//            res = ModeRange_I_DL_to_text(static_cast<ModeRange_I_DL>(range));
//        break;
        case 120: //I_D_comp
            res = ModeRange_I_D_comp_to_text(static_cast<ModeRange_I_D_comp>(range));
        break;
        default:

        break;
    }

    return res.c_str();
}

QString any_range_to_text_EN(const int signal, const int range) {
    Q_UNUSED(range)
    std::string res = "Auto";
    switch (signal) {
        case 1: //I_for
        case 6: //I_for_tune
        case 10: //I_for_duration
            res = Range_I_for_to_text_EN(static_cast<Range_I_for>(range));
        break;
        case 2: //U_for_D1
        case 8: //U_for_D2
            res = Range_U_for_to_text_EN(static_cast<Range_U_for>(range));
        break;
        case 3: //I_rev_D1
        case 9: //I_rev_D2
            res = Range_I_rev_to_text_EN(static_cast<Range_I_rev>(range));
        break;
        case 4: //U_rev
        case 7: //U_rev_tune
        case 11: //U_rev_duration
            res = Range_U_rev_to_text_EN(static_cast<Range_U_rev>(range));
        break;
        case 5: //PFM
            res = Range_PFM_to_text(static_cast<Range_PFM>(range));
        break;


        case 101: //Signal_I_D
            res = ModeRange_I_D_to_text_EN(static_cast<ModeRange_I_D>(range));
        break;
        case 102: //Signal_I_D_meas
            res = MeasureRange_I_D_to_text_EN(static_cast<MeasureRange_I_D>(range));
        break;
        case 103: //Signal_U_GS
            res = ModeRange_U_GS_to_text_EN(static_cast<ModeRange_U_GS>(range));
        break;
        case 104: //Signal_U_GS_meas
            res = MeasureRange_U_GS_to_text_EN(static_cast<MeasureRange_U_GS>(range));
        break;
        case 105: //Signal_U_GSS
            res = ModeRange_U_GSS_to_text_EN(static_cast<ModeRange_U_GSS>(range));
        break;
//        case 106: //Signal_U_GSS_R
//            res = Range_U_GSS_R_to_text_EN(static_cast<Range_U_GSS_R>(range));
//        break;
        case 107: //Signal_I_GSS
            res = MeasureRange_I_GSS_to_text_EN(static_cast<MeasureRange_I_GSS>(range));
        break;
//        case 108: //Signal_I_GSS_R
//            res = Range_I_GSS_R_to_text_EN(static_cast<Range_I_GSS_R>(range));
//        break;
        case 109: //Signal_I_DM
            res = MeasureRange_I_DM_to_text_EN(static_cast<MeasureRange_I_DM>(range));
        break;
        case 110: //Signal_I_DL
            res = MeasureRange_I_DL_to_text_EN(static_cast<MeasureRange_I_DL>(range));
        break;
            //111 - Signal_R_DS
            //112 - Signal_S
        case 113: //Signal_U_DS
            res = ModeRange_U_DS_to_text_EN(static_cast<ModeRange_U_DS>(range));
        break;
        case 114: //Signal_U_DS_L
            res = ModeRange_U_DS_L_to_text_EN(static_cast<ModeRange_U_DS_L>(range));
            break;
        case 115: //Signal_U_DS_meas
            res = MeasureRange_U_DS_to_text_EN(static_cast<MeasureRange_U_DS>(range));
        break;
        case 116: //Signal_U_SD
            res = MeasureRange_U_SD_to_text_EN(static_cast<MeasureRange_U_SD>(range));
        break;
        case 117: //I_S
            res = ModeRange_I_S_to_text_EN(static_cast<ModeRange_I_S>(range));
        break;
        case 118: //I_DM
            res = ModeRange_I_DM_to_text_EN(static_cast<ModeRange_I_DM>(range));
        break;
//        case 119: //I_DL
//            res = ModeRange_I_DM_to_text_EN(static_cast<ModeRange_I_DL>(range));
//        break;
        case 120: //I_D_comp
            res = ModeRange_I_D_comp_to_text_EN(static_cast<ModeRange_I_D_comp>(range));
        break;
        default:

        break;
    }

    return res.c_str();
}

int any_range_from_text(const QString qtext) {
    std::string text = qtext.toStdString();
    int range = 0;

    if (text == "Авто") {
        return range;
    }

    {
        //DIODE
        range = Range_U_for_from_text(text.c_str());
        if (range != 0) {
            return range;
        }
        range = Range_I_for_from_text(text.c_str());
        if (range != 0) {
            return range;
        }
        range = Range_U_rev_from_text(text.c_str());
        if (range != 0) {
            return range;
        }
        range = Range_I_rev_from_text(text.c_str());
        if (range != 0) {
            return range;
        }
        range = Range_PFM_from_text(text.c_str());
        if (range != 0) {
            return range;
        }
    }

    {
        //FET
        range = ModeRange_I_D_from_text(text.c_str());
        if (range != 0) {
            return range;
        }

        range = MeasureRange_I_D_from_text(text.c_str());
        if (range != 0) {
            return range;
        }

        range = ModeRange_U_GS_from_text(text.c_str());
        if (range != 0) {
            return range;
        }

        range = MeasureRange_U_GS_from_text(text.c_str());
        if (range != 0) {
            return range;
        }

//        range = Range_U_GSS_R_from_text(text.c_str());
//        if (range != 0) {
//            return range;
//        }

        range = ModeRange_U_GSS_from_text(text.c_str());
        if (range != 0) {
            return range;
        }

//        range = Range_I_GSS_R_from_text(text.c_str());
//        if (range != 0) {
//            return range;
//        }

        range = MeasureRange_I_GSS_from_text(text.c_str());
        if (range != 0) {
            return range;
        }

        range = MeasureRange_I_DM_from_text(text.c_str());
        if (range != 0) {
            return range;
        }

        range = MeasureRange_I_DL_from_text(text.c_str());
        if (range != 0) {
            return range;
        }

        range = ModeRange_U_DS_from_text(text.c_str());
        if (range != 0) {
            return range;
        }

        range = ModeRange_U_DS_L_from_text(text.c_str());
        if (range != 0) {
            return range;
        }

        range = MeasureRange_U_DS_from_text(text.c_str());
        if (range != 0) {
            return range;
        }

        range = MeasureRange_U_SD_from_text(text.c_str());
        if (range != 0) {
            return range;
        }

        range = ModeRange_I_S_from_text(text.c_str());
        if (range != 0) {
            return range;
        }

        range = ModeRange_I_DM_from_text(text.c_str());
        if (range != 0) {
            return range;
        }

//        range = ModeRange_I_DL_from_text(text.c_str());
//        if (range != 0) {
//            return range;
//        }

        range = ModeRange_I_D_comp_from_text(text.c_str());
        if (range != 0) {
            return range;
        }
    }

    //_EN includes in non _EN function
    return range;
}

