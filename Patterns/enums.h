#ifndef ENUMS_H
#define ENUMS_H

#include "enum_macro.h"

#include "Logger.h"
#include "TestRunner.h"

#include <ratio>

void ENUM_MACRO_GET_NAMES_FUNCTION();

/////////////////////////// MATH ///////////////////////////

#define _LE "\u2264"
#define _LT "\u003C"
#define _GE "\u2265"
#define _GT "\u003E"
#define _EQ "\u003D"
#define _NE "\u2260"
#define _CIEQ "\u2248"
#define _CINE "\u2249"
/////////////////////////// RMO ///////////////////////////

#define PARAMS_DELIMETER    ", "            // ",\n" = not working due to test raw delimeter - cant copy to txt
#define ELEMENTS_DELIMETER  ";"
#define ROW_DELIMETER       "\r\n"

#define MAX_READ_CHANNELS_NUMBER        2

ENUM_MACRO4(AcceptanceType, AcceptanceType_Undefined, AcceptanceType_Workshop, AcceptanceType_OTK, AcceptanceType_VP,
            AcceptanceType_Undefined, AcceptanceType_Workshop, AcceptanceType_OTK, AcceptanceType_VP,
            Приемка, Цех, ОТК, ВП,
            0, 1, 2, 3);
ENUM_MACRO5(AuthUserRole, AuthUserRole_Undefined, Developer, Admin, Technologist, Operator,
            Undefined, Developer, Admin, Technologist, Operator,
            Не определено, Разработчик, Администратор, Технолог, Испытатель,
            0, 1, 2, 3, 4);
ENUM_MACRO5(ModelType, ModelType_Undefined, ModelType_Diode, ModelType_FET2, ModelType_FET5, ModelType_TestRV,
            Undefined, Diode, FET2, FET5, TestRV,
            Не определено, Диод, ПТ2, ПТ5, ТестУМ,
            0, 1, 2, 3, 4);
ENUM_MACRO3(RMOErrorCode, RMO_NO_ERROR, RMO_NO_TEST_FOUND, RMO_NO_OPERATION_FOUND,
            RMO_NO_ERROR, RMO_NO_TEST_FOUND, RMO_NO_OPERATION_FOUND,
            RMO_NO_ERROR, RMO_NO_TEST_FOUND, RMO_NO_OPERATION_FOUND,
            0, 1, 2);

ENUM_MACRO3(ATMLTestResult, ATMLTestResult_NotReady, ATMLTestResult_Done, ATMLTestResult_NotDone, "", "", "", "", "", "", 0, 1, 2); //no fun definition
ENUM_MACRO2(ControlType, ControlType_Undefined, ControlType_SignalsRequest, "", "", "", "", 0, 1); //no fun definition
ENUM_MACRO3(SetTestResultType, SetTestResultType_Undefined, SetTestResultType_LEDs, SetTestResultType_LEDs_PKV, "", "", "", "", "", "", 0, 1, 2); //no fun definition
ENUM_MACRO4(MeasureTypes, MeasurePulseAmplitude, MeasureDeltaPulseAmplitude, MeasureExtremum, MeasureDeltaByEdge,
            MeasurePulseAmplitude, MeasureDeltaPulseAmplitude, MeasureExtremum, MeasureDeltaByEdge,
            MeasurePulseAmplitude, MeasureDeltaPulseAmplitude, MeasureExtremum, MeasureDeltaByEdge, 0, 1, 2, 3);
ENUM_MACRO5(DACMode, DACModeUndefined, DACModeSimple, DACModeTriangle, DACModeDMA, DACModeRegulator, "", "", "", "", "", "", "", "", "", "", 0, 1, 2, 3, 4); //no fun definition

static QStringList AcceptanceTypes = {AcceptanceType_to_text(AcceptanceType_Undefined),
                                     AcceptanceType_to_text(AcceptanceType_Workshop),
                                     AcceptanceType_to_text(AcceptanceType_OTK),
                                     AcceptanceType_to_text(AcceptanceType_VP)};
static QStringList AuthUserRolesAll = {AuthUserRole_to_text(Operator),
                                           AuthUserRole_to_text(Technologist),
                                           AuthUserRole_to_text(Admin),
                                           AuthUserRole_to_text(Developer)};
static QStringList AuthUserRolesAdd = {AuthUserRole_to_text(Operator),
                                           AuthUserRole_to_text(Technologist)};

/////////////////////////// ATML ///////////////////////////
ENUM_MACRO4(OperationCommand, OC_CREATE = 0x43, OC_READ = 0x52, OC_UPDATE = 0x55, OC_DELETE = 0x44,
           OC_CREATE, OC_READ, OC_UPDATE, OC_DELETE,
           OC_CREATE, OC_READ, OC_UPDATE, OC_DELETE,
           0x43, 0x52, 0x55, 0x44);
ENUM_MACRO4(TestCommand, TC_CREATE = 0x43, TC_READ = 0x52, TC_UPDATE = 0x55, TC_DELETE = 0x44,
           TC_CREATE, TC_READ, TC_UPDATE, TC_DELETE,
           TC_CREATE, TC_READ, TC_UPDATE, TC_DELETE,
           0x43, 0x52, 0x55, 0x44);
ENUM_MACRO4(TestSequenceCommand, TSC_CHECK = 0x43, TSC_RUN = 0x52, TSC_SIZE = 0x53, TSC_DELETE = 0x44,
           TSC_CREATE, TSC_READ, TSC_UPDATE, TSC_DELETE,
           TSC_CREATE, TSC_READ, TSC_UPDATE, TSC_DELETE,
           0x43, 0x52, 0x55, 0x44);
ENUM_MACRO3(TestResultName, TestResult_Undefined, TestResult_Norma, TestResult_NotNorma,
           Undefined, Passed, Failed,
           Не определено, В норме, Не в норме,
           0, 1, 2);
ENUM_MACRO3(CompareResultName, CompareResult_Undefined, CompareResult_Norma, CompareResult_NotNorma,
           Undefined, Passed, Failed,
           Не определено, В норме, Не в норме,
           0, 1, 2);
ENUM_MACRO3(TestsResultName, TestsResult_Undefined, TestsResult_Passed, TestsResult_Failed,
           Undefined, Passed, Failed,
           Не определено, Годен, Брак,
           0, 1, 2);
ENUM_MACRO7(PinName, Pin_Undefined, Pin_A1, Pin_C, Pin_A2, Pin_G, Pin_D, Pin_S,
           Undefined, A1, C, A2, G, D, S,
           Undefined, A1, C, A2, G, D, S,
           0, 1, 2, 3, 4, 5, 6);
ENUM_MACRO3(XMLFileType, XMLFileType_Undefined, XMLFileType_TestDescription, XMLFileType_TestResults,
           Undefined, TestDescription, TestResults,
           Undefined, TestDescription, TestResults,
            0, 1, 2);
ENUM_MACRO20(OperationType, Operation_Undefined, Operation_Setup, Operation_Connect, Operation_Setup_Measure,
            Operation_Disconnect, Operation_Read, Operation_Calculate,
            Operation_Compare, Operation_Conditional, Operation_Exchange, Operation_Fetch, Operation_Reset,
            Operation_Decode_Message, Operation_Encode_Message,
            Operation_Message_In, Operation_Message_Out,
            Operation_Run_Frame, Operation_Read_Variable, Operation_Set_Variable,
            Operation_Wait_For,
           "Operation_Undefined", "Operation_Setup", "Operation_Connect", "Operation_Setup_Measure",
           "Operation_Disconnect", "Operation_Read", "Operation_Calculate",
           "Operation_Compare", "Operation_Conditional", "Operation_Exchange", "Operation_Fetch", "Operation_Reset",
           "Operation_Decode_Message", "Operation_Encode_Message",
           "Operation_Message_In", "Operation_Message_Out",
           "Operation_Run_Frame", "Operation_Read_Variable", "Operation_Set_Variable",
           "Operation_Wait_For",
           "Действие не определено", "Настройка", "Подключение", "Подключение измерения",
           "Отключение", "Измерение", "Вычисление",
           "Сравнение", "Условие", "Передача данных", "Прием данных", "Сброс",
           "Кодирование сообщения", "Дедирование сообщения",
           "Запрос", "Сообщение",
           "Цикл", "Считать", "Задать",
           "Ожидание",
           0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19); //no fun definition
ENUM_MACRO5(ATMLVariableType, ATMLVariable_Undefined, ATMLVariable_bool, ATMLVariable_int, ATMLVariable_double, ATMLVariable_string,
           "string", "boolean", "integer", "double", "string",
           "string", "boolean", "integer", "double", "string",
           0, 1, 2, 3, 4);
ENUM_MACRO5(ATMLSignalType, ATMLSignal_Undefined, ATMLSignal_DC_PULSED, ATMLSignal_RS232, ATMLSignal_TCP, ATMLSignal_UDP,
           "ATMLSignal_Undefined", "ATMLSignal_DC_PULSED", "ATMLSignal_RS232", "ATMLSignal_TCP", "ATMLSignal_UDP",
           "Сигнал не определен", "Импульс DC", "RS232", "TCP", "UDP",
           0, 1, 2, 3, 4);
ENUM_MACRO4(CalibrationCommand, CALIB_CREATE = 0x43, CALIB_READ = 0x52, CALIB_UPDATE = 0x55, CALIB_DELETE = 0x44, "", "", "", "", "", "", "", "", 0x43, 0x52, 0x55, 0x44); //no fun definition
ENUM_MACRO3(CalibratorCommand, CALIBRATOR_OFF = 0x50, CALIBRATOR_READ = 0x52, CALIBRATOR_UPDATE= 0x55, "", "", "", "", "", "", 0x50, 0x52, 0x55); //no fun definition
ENUM_MACRO2(RMOSettingsCommand, RMO_SETTINGS_READ = 0x52, RMO_SETTINGS_WRITE = 0x57, "", "", "", "", 0x52, 0x57); //no fun definition
ENUM_MACRO4(OscillogramType, OscillogramMeasure, HistMeasure, OscillogramTune, OscillogramRaw, "", "", "", "", "", "",  "", "", 0, 1, 2, 3); //no fun definition

ENUM_MACRO3(FilterType, FilterMAO, FilterAA, FilterMedian,
            FilterMAO, FilterAA, FilterMedian,
            Фильтр бегущее среднее, Фильтр бегущее среднее с адаптивным коэф., Медианный фильтр, 0, 1, 2);

static QStringList TestResultNames = {TestResultName_to_text(TestResult_Undefined),
            TestResultName_to_text(TestResult_Norma),
            TestResultName_to_text(TestResult_NotNorma)};
static QStringList TestsResultNames = {TestsResultName_to_text(TestsResult_Undefined),
             TestsResultName_to_text(TestsResult_Passed),
             TestsResultName_to_text(TestsResult_Failed)};
static QStringList FilterTypesNames_sl = {FilterType_to_text(FilterMAO),
                                        FilterType_to_text(FilterAA),
                                        FilterType_to_text(FilterMedian)};
/////////////////////////// MVC ////////////////////////////
static QStringList TestResultColumnRus = {"Номер\nтеста", "Результат", "Группа\nгодности", "Норма",
                                         "Амплитуда\n(изм.)", "Длительность\n(изм.)",
                                          "Запущено", "Завершено", "Длительность\nвыполнения"}; //"Выполнено", "Режим\n(изм.)",

#define END_TIME_COLUMN 10

static QStringList TestsResultColumnRus = {"Партия", "Номер\nв партии", "Наименование\nприбора", "Результат",
                                           "Группа\nгодности", "Группа\nбрака", "Комментарий", "Тип приемки", "Температура",
                                           "Запущено", "Завершено", "Длительность\nвыполнения"};

static QStringList StatisticColumn = {"Тест", "Кол-во\nбрака", "Номера\nбракованных\nприборов"};

static QStringList TestResultColumnRus_html = {"Но-<br>мер<br>тес-<br>та", "Результат", "Группа<br>год-<br>ности", "Норма",
                                         "Амплитуда<br>(изм.)", "Длитель-<br>ность<br>(изм.)",
                                               "Запущено", "Завершено", "Длитель-<br>ность<br>выпол-<br>нения"}; //"Выполнено", "Режим\n(изм.)",

static QStringList TestsResultColumnRus_html = {"Партия", "Номер<br>в партии", "Наимено-<br>вание<br>прибора", "Результат",
                                                "Группа<br>год-<br>ности", "Группа<br>брака", "Ком-<br>ментарий", "Тип<br>приемки", "Темпе-<br>ратура",
                                                "Запущено", "Завершено", "Длитель-<br>ность<br>выпол-<br>нения"};

static QStringList StatisticColumn_html = {"Тест", "Кол-во<br>брака", "Номера<br>бракованных<br>приборов"};

static QStringList TestResultColumnRus_class_html = {" class=\"shrink\" ", " class=\"shrink\" ", " class=\"shrink\" ", " class=\"expand\" ",
                                                     " class=\"expand\" ", " class=\"shrink\" ",
                                                     " class=\"small_expand\" ", " class=\"small_expand\" ", " class=\"shrink\" "};

static QStringList TestsResultColumnRus_class_html = {" class=\"shrink\" ", " class=\"shrink\" ", " class=\"small_expand\" ", " class=\"shrink\" ",
                                                      " class=\"shrink\" ", " class=\"shrink\" ", " class=\"shrink\" ", " class=\"shrink\" ", " class=\"shrink\" ",
                                                      " class=\"small_expand\" ", " class=\"small_expand\" ", " class=\"shrink\" "};

/////////////////////////// signal ///////////////////////////

ENUM_MACRO15(TestType, Test_Undefined, Test_Contacting, Test_I_rev, Test_U_for,
           Test_Contacting_U_SD, Test_I_D,
           Test_U_GS, Test_I_GSS, Test_I_GSS_R, Test_R_DS,
           Test_I_DM, Test_S, Test_I_DL,
           Test_U_DS, Test_U_SD,
            Undefined, Test_Contacting, Test_I_rev, Test_U_for,
            Test_Contacting_U_SD, Test_I_D,
            Test_U_GS, Test_I_GSS, Test_I_GSS_R, Test_R_DS,
            Test_I_DM, Test_S, Test_I_DL,
            Test_U_DS, Test_U_SD,
            Не определено, Контактирование, Обратный ток, Прямое напряжение,
            Контактирование Uис, Начальный ток стока Iс нач, Пороговое напряжение Uзи пор,
            Ток утечки затвора Iз изм, Ток утечки затвора -Iз изм, Сопротивление Rси отк,
            Импульсный ток стока Iс(и) max, Крутизна характеристики S, Импульсный ток стока Iс инд,
            Пробивное напряжение диода Uси, Пост. пр. напряжение диода Uис,
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14);

ENUM_MACRO22(SignalName, Signal_Undefined = 0,
               Signal_I_for = 1,
               Signal_U_for = 2,
               Signal_I_rev = 3,
               Signal_U_rev = 4,
               Signal_I_D = 101,
               Signal_I_D_meas = 102,
               Signal_U_GS = 103,
               Signal_U_GS_meas = 104,
               Signal_U_GSS = 105,
               //Signal_U_GSS_R = 106,
               Signal_I_GSS = 107,
               //Signal_I_GSS_R = 108,
               Signal_I_DM_meas = 109,
               Signal_I_DL_meas = 110,
               Signal_R_DS = 111,
               Signal_S = 112,
               Signal_U_DS = 113,
               Signal_U_DS_L = 114,
               Signal_U_DS_meas = 115,
               Signal_U_SD = 116,
               Signal_I_S = 117,
               Signal_I_DM = 118,
               //Signal_I_DL = 119,
               Signal_I_D_comp = 120,
               Undefined, I_for, U_for, I_rev, U_rev,
               I_D, I_D_meas, U_GS, U_GS_meas, U_GSS, I_GSS, //U_GSS_R, I_GSS, I_GSS_R,
               I_DM_meas, I_DL_meas, R_DS, S, U_DS, U_DS_L, U_DS_meas, U_SD, I_S, I_DM, I_DL_comp,
               Не определено, Iпр,  Uпр, Iобр, Uобр,
               Iс, Iс изм, Uзи, Uзи изм, Uзи ут, Iз изм, //|-Uзи ут|, Iз изм, |-Iз изм|,
               Iс max, Iс инд, Rси, S, Uси, Uси инд, Uси изм, Uис, Iи, Iс max огр, Iс комп,
               0, 1, 2, 3, 4, 101, 102, 103, 104, 105, 107, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 120);

//SignalName order for QT calibration must match CalibrationSignalName
ENUM_MACRO35(CalibrationSignalName,
             CalibrationSignal_Undefined = 0,
               CalibrationSignal_I_for = 1, //Signal_I_for
               CalibrationSignal_U_for_D1 = 2, //Signal_U_for
               CalibrationSignal_U_for_D2 = 8,
               CalibrationSignal_I_rev_D1 = 3, //Signal_I_rev
               CalibrationSignal_I_rev_D2 = 9,
               CalibrationSignal_U_rev = 4, //Signal_U_rev
               CalibrationSignal_PFM = 5,
               CalibrationSignal_I_for_tune = 6,
               CalibrationSignal_U_rev_tune = 7,
               CalibrationSignal_I_for_duration = 10,
               CalibrationSignal_U_rev_duration = 11,

               CalibrationSignal_I_D = 101,
               CalibrationSignal_I_D_meas = 102,
               CalibrationSignal_U_GS = 103,
               CalibrationSignal_U_GS_meas = 104,
               CalibrationSignal_U_GSS = 105,
               //CalibrationSignal_U_GSS_R = 106,
               CalibrationSignal_I_GSS_meas = 107,
               //CalibrationSignal_I_GSS_R = 108,
               CalibrationSignal_I_DM_meas = 109,
               CalibrationSignal_I_DL_meas = 110,
               CalibrationSignal_R_DS = 111,
               CalibrationSignal_S = 112,
               CalibrationSignal_U_DS = 113,
               CalibrationSignal_U_DS_L = 114,
               CalibrationSignal_U_DS_meas = 115,
               CalibrationSignal_U_SD_meas = 116,
               CalibrationSignal_I_S = 117,
               CalibrationSignal_I_DM = 118,
               //CalibrationSignal_I_DL = 119,
               CalibrationSignal_I_D_comp = 120,

             CalibrationSignal_I_D_duration = 121,
             CalibrationSignal_U_GS_duration = 123,
             CalibrationSignal_U_GSS_duration = 125,
             CalibrationSignal_U_DS_duration = 133,
             CalibrationSignal_U_DS_L_duration = 134,
             CalibrationSignal_I_S_duration = 137,

           Undefined,
           Ifor_DAC,
           Ufor_diode_1_ADC,
           Ufor_diode_2_ADC,
           Irev_diode_1_ADC,
           Irev_diode_2_ADC,
           Urev_DAC,
           PFM,
           Ifor_ADC,
           Urev_ADC,
           Ifor_duration,
           Urev_duration,

           I_D_DAC,
           I_D_ADC,
           U_GS_DAC,
           U_GS_ADC,
           U_GSS_DAC,
           //U_GSS_R_DAC,
           I_GSS_ADC,
           //I_GSS_R_ADC,
           I_D_MAX_ADC,
           I_D_L_ADC,
           R_DS,
           S,
           U_DS_DAC,
           U_DS_L_DAC,
           U_DS_ADC,
           U_SD_ADC,
           I_S_DAC,
             I_D_MAX_DAC,
             //I_D_L_DAC,
             I_D_comp_DAC,

             I_D_duration,
             U_GS_duration,
             U_GSS_duration,
             U_DS_duration,
             U_DS_L_duration,
             I_S_duration,

           Не определено,
           Iпр (DAC),
           Uпр - диод 1 (ADC),
           Uпр - диод 2 (ADC),
           Iобр - диод 1 (ADC),
           Iобр - диод 2 (ADC),
           Uобр (DAC),
           PFM,
           Iпр (ADC),
           Uобр (ADC),
           Iпр (длительность),
           Uобр (длительность),

           Iс (DAC),
           Iс (ADC),
           Uзи (DAC),
           Uзи (ADC),
           Uзи ут (DAC),
           //-Uзи ут (DAC),
           Iзи ут (ADC),
           //-Iзи ут (ADC),
           Iс max (ADC),
           Iс инд (ADC),
           Rси,
           S,
           Uси (DAC),
           Uси инд (DAC),
           Uси (ADC),
           Uис (ADC),
           Iи (DAC),
           Iс max (DAC),
           //Iс инд (DAC),
           Iс комп (DAC),

             Iс (длительность),
             Uзи (длительность),
             Uзи ут (длительность),
             Uси (длительность),
             Uси инд (длительность),
             Iи (длительность),
           0, 1, 2, 8, 3, 9, 4, 5, 6, 7, 10, 11, 101, 102, 103, 104, 105, 107, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 120, 121, 123, 125, 133, 134, 137
);

//SignalName order for QT calibration must match PreparationSignalName
ENUM_MACRO10(PreparationSignalName,
                PreparationSignal_Undefined = 0,
                PreparationSignal_I_for = 1,
                PreparationSignal_U_rev = 4,
                PreparationSignal_I_D = 101,
                PreparationSignal_U_GS = 103,
                PreparationSignal_U_GSS = 105,
                PreparationSignal_U_GSS_R = 106,
                PreparationSignal_U_DS = 113,
                PreparationSignal_U_DS_L = 114,
                PreparationSignal_I_S = 117,
               Undefined,
               Ifor_DAC,
               Urev_DAC,
               Id_DAC,
               Ugs_DAC,
               Ugss_DAC,
               -Ugss_r_DAC,
               Uds_DAC,
               Uds_L_DAC,
               Is_DAC,

               Не определено,
               Iпр (DAC),
               Uобр (DAC),
               Iс (DAC),
               Uзи (DAC),
               Uзи ут (DAC),
               -Uзи ут (DAC),
               Uси (DAC),
               Uси инд (DAC),
               Iи (DAC),
               0, 1, 4, 101, 103, 105, 106, 113, 114, 117);

static QStringList TestTypesDiode = {TestType_to_text(Test_Contacting),
                               TestType_to_text(Test_I_rev),
                               TestType_to_text(Test_U_for)};

static QStringList TestTypesDiode_re = {TestType_to_text(Test_Contacting),
                               TestType_to_text(Test_I_rev),
                               TestType_to_text(Test_U_for)};

static QStringList SignalNameDiode_sl = {SignalName_to_text(Signal_Undefined),
                                    SignalName_to_text(Signal_I_for),
                                    SignalName_to_text(Signal_U_for),
                                    SignalName_to_text(Signal_I_rev),
                                    SignalName_to_text(Signal_U_rev)};

static QStringList SignalNameDiode_sl_re = {SignalName_to_text(Signal_I_for),
                                    SignalName_to_text(Signal_U_for),
                                    SignalName_to_text(Signal_I_rev),
                                    SignalName_to_text(Signal_U_rev)};

static QStringList TestTypesFet = {//test_type_to_text(Test_Contacting_U_GS),
                                //test_type_to_text(Test_Contacting_U_SD),
                                TestType_to_text(Test_Contacting_U_SD),
                                TestType_to_text(Test_I_D),
                                TestType_to_text(Test_U_GS),
                                TestType_to_text(Test_I_GSS),
                                TestType_to_text(Test_I_GSS_R),
                                TestType_to_text(Test_R_DS),
                                TestType_to_text(Test_I_DM),
                                TestType_to_text(Test_S),
                                TestType_to_text(Test_I_DL),
                                TestType_to_text(Test_U_DS),
                                TestType_to_text(Test_U_SD)};

static QStringList TestTypesFet_re = {//test_type_to_text(Test_Contacting_U_GS),
                                //test_type_to_text(Test_Contacting_U_DS),
                                TestType_to_text(Test_Contacting_U_SD),
                                TestType_to_text(Test_I_D),
                                TestType_to_text(Test_U_GS),
                                TestType_to_text(Test_I_GSS),
                                TestType_to_text(Test_I_GSS_R),
                                TestType_to_text(Test_R_DS),
                                QString(TestType_to_text(Test_I_DM)).replace("(", "\\W").replace(")", "\\W"),
                                TestType_to_text(Test_S),
                                TestType_to_text(Test_I_DL),
                                TestType_to_text(Test_U_DS),
                                TestType_to_text(Test_U_SD)};

static QStringList SignalNameFet_sl = {SignalName_to_text(Signal_Undefined),
                                    SignalName_to_text(Signal_I_D),
                                    SignalName_to_text(Signal_I_D_meas),
                                    SignalName_to_text(Signal_U_GS),
                                    SignalName_to_text(Signal_U_GS_meas),
                                    SignalName_to_text(Signal_I_GSS),
                                    //SignalName_to_text(Signal_I_GSS_R),
                                    SignalName_to_text(Signal_I_DM_meas),
                                    SignalName_to_text(Signal_I_DL_meas),
                                    SignalName_to_text(Signal_R_DS),
                                    SignalName_to_text(Signal_S),
                                    SignalName_to_text(Signal_U_DS),
                                    SignalName_to_text(Signal_U_DS_L),
                                    SignalName_to_text(Signal_U_DS_meas),
                                    SignalName_to_text(Signal_U_SD),
                                    SignalName_to_text(Signal_I_S),
                                    SignalName_to_text(Signal_I_DM),
                                    //SignalName_to_text(Signal_I_DL),
                                    SignalName_to_text(Signal_I_D_comp)
                                      };

//Signal_I_D and Signal_U_GS must be after another for re + delete undefined
//Signal_U_GSS_R and Signal_U_GSS must be before Signal_U_GS_meas and Signal_U_GS
//Signal_U_GSS_R and Signal_I_GSS_R msut be before non _R
//Signal_I_DM and Signal_I_DL must be before meas signals
static QStringList SignalNameFet_sl_re = {
                                    //QString(SignalName_to_text(Signal_U_GSS_R)).replace("|", "[|]"),
                                    SignalName_to_text(Signal_U_GSS),
                                    SignalName_to_text(Signal_U_GS_meas),
                                    SignalName_to_text(Signal_U_GS),
                                    //QString(SignalName_to_text(Signal_I_GSS_R)).replace("|", "[|]"),
                                    SignalName_to_text(Signal_I_GSS),
                                    SignalName_to_text(Signal_I_DM),
                                    //SignalName_to_text(Signal_I_DL),
                                    SignalName_to_text(Signal_I_D_comp),
                                    SignalName_to_text(Signal_I_DM_meas),
                                    SignalName_to_text(Signal_I_DL_meas),
                                    SignalName_to_text(Signal_I_D_meas),
                                    SignalName_to_text(Signal_I_D),
                                    SignalName_to_text(Signal_R_DS),
                                    SignalName_to_text(Signal_S),
                                    SignalName_to_text(Signal_U_DS_L),
                                    SignalName_to_text(Signal_U_DS_meas),
                                    SignalName_to_text(Signal_U_DS),
                                    SignalName_to_text(Signal_U_SD),
                                    SignalName_to_text(Signal_I_S)};

static QStringList TestTypes = TestTypesFet + TestTypesDiode; //TestTypesDiode must be after Fet due to Contacting name
static QStringList TestTypes_re = TestTypesFet_re + TestTypesDiode_re; //TestTypesDiode must be after Fet due to Contacting name
static QStringList SignalName_sl = SignalNameDiode_sl + SignalNameFet_sl;
static QStringList SignalName_sl_re = SignalNameDiode_sl_re + SignalNameFet_sl_re;

namespace diode_ns {
    static QStringList CalibrationSignalName_sl = {CalibrationSignalName_to_text(CalibrationSignal_Undefined),
                                    CalibrationSignalName_to_text(CalibrationSignal_I_for),
                                    CalibrationSignalName_to_text(CalibrationSignal_U_for_D1),
                                    CalibrationSignalName_to_text(CalibrationSignal_U_for_D2),
                                    CalibrationSignalName_to_text(CalibrationSignal_I_rev_D1),
                                    CalibrationSignalName_to_text(CalibrationSignal_I_rev_D2),
                                    CalibrationSignalName_to_text(CalibrationSignal_U_rev),
                                    CalibrationSignalName_to_text(CalibrationSignal_PFM),
                                    CalibrationSignalName_to_text(CalibrationSignal_I_for_tune),
                                    CalibrationSignalName_to_text(CalibrationSignal_U_rev_tune),
                                    CalibrationSignalName_to_text(CalibrationSignal_I_for_duration),
                                    CalibrationSignalName_to_text(CalibrationSignal_U_rev_duration)};

    static QStringList CalibratorDACSignalName_sl = {CalibrationSignalName_to_text(CalibrationSignal_Undefined),
                                    CalibrationSignalName_to_text(CalibrationSignal_I_for),
                                    CalibrationSignalName_to_text(CalibrationSignal_U_rev)};

    static QStringList CalibratorADCSignalName_sl = {CalibrationSignalName_to_text(CalibrationSignal_Undefined),
                                    CalibrationSignalName_to_text(CalibrationSignal_U_for_D1),
                                    CalibrationSignalName_to_text(CalibrationSignal_I_rev_D1)};

    static QStringList PreparationSignalName_sl = {PreparationSignalName_to_text(PreparationSignal_Undefined),
                                    PreparationSignalName_to_text(PreparationSignal_I_for),
                                    PreparationSignalName_to_text(PreparationSignal_U_rev)};
}

namespace fet2_ns {
    static QStringList CalibrationSignalName_sl = {CalibrationSignalName_to_text(CalibrationSignal_Undefined),
                                              CalibrationSignalName_to_text(CalibrationSignal_I_D),
                                              CalibrationSignalName_to_text(CalibrationSignal_I_D_meas),
                                              CalibrationSignalName_to_text(CalibrationSignal_U_GS),
                                              CalibrationSignalName_to_text(CalibrationSignal_U_GS_meas),
                                              CalibrationSignalName_to_text(CalibrationSignal_U_GSS),
                                              //CalibrationSignalName_to_text(CalibrationSignal_U_GSS_R),
                                              CalibrationSignalName_to_text(CalibrationSignal_I_GSS_meas),
                                              //CalibrationSignalName_to_text(CalibrationSignal_I_GSS_R),
                                              CalibrationSignalName_to_text(CalibrationSignal_I_DM_meas),
                                              CalibrationSignalName_to_text(CalibrationSignal_I_DL_meas),
                                              //calibration_signal_name_to_text(CalibrationSignal_R_DS),
                                              //calibration_signal_name_to_text(CalibrationSignal_S),
                                              CalibrationSignalName_to_text(CalibrationSignal_U_DS),
                                              CalibrationSignalName_to_text(CalibrationSignal_U_DS_L),
                                              CalibrationSignalName_to_text(CalibrationSignal_U_DS_meas),
                                               CalibrationSignalName_to_text(CalibrationSignal_U_SD_meas),
                                               CalibrationSignalName_to_text(CalibrationSignal_I_S),
                                               CalibrationSignalName_to_text(CalibrationSignal_I_DM),
                                               CalibrationSignalName_to_text(CalibrationSignal_I_D_comp),
                                               CalibrationSignalName_to_text(CalibrationSignal_I_D_duration),
                                               CalibrationSignalName_to_text(CalibrationSignal_U_GS_duration),
                                               CalibrationSignalName_to_text(CalibrationSignal_U_GSS_duration),
                                               CalibrationSignalName_to_text(CalibrationSignal_U_DS_duration),
                                               CalibrationSignalName_to_text(CalibrationSignal_U_DS_L_duration),
                                               CalibrationSignalName_to_text(CalibrationSignal_I_S_duration)};

    static QStringList CalibratorDACSignalName_sl = {CalibrationSignalName_to_text(CalibrationSignal_Undefined),
                                                    CalibrationSignalName_to_text(CalibrationSignal_U_DS),
                                                    CalibrationSignalName_to_text(CalibrationSignal_U_DS_L),
                                               CalibrationSignalName_to_text(CalibrationSignal_I_D),
                                               CalibrationSignalName_to_text(CalibrationSignal_U_GS),

                                               CalibrationSignalName_to_text(CalibrationSignal_U_GSS),
                                               //CalibrationSignalName_to_text(CalibrationSignal_U_GSS_R),

                                               CalibrationSignalName_to_text(CalibrationSignal_I_S),
                                               CalibrationSignalName_to_text(CalibrationSignal_I_DM),
                                               CalibrationSignalName_to_text(CalibrationSignal_I_D_comp)};

    static QStringList CalibratorADCSignalName_sl = {CalibrationSignalName_to_text(CalibrationSignal_Undefined),
                                                 CalibrationSignalName_to_text(CalibrationSignal_I_D_meas),
                                                 CalibrationSignalName_to_text(CalibrationSignal_U_DS_meas),

                                                 CalibrationSignalName_to_text(CalibrationSignal_I_GSS_meas),
                                                 //CalibrationSignalName_to_text(CalibrationSignal_I_GSS_R),

                                                 CalibrationSignalName_to_text(CalibrationSignal_I_DM_meas),
                                                 CalibrationSignalName_to_text(CalibrationSignal_I_DL_meas),
                                                 CalibrationSignalName_to_text(CalibrationSignal_U_SD_meas)};

    static QStringList PreparationSignalName_sl = {PreparationSignalName_to_text(PreparationSignal_Undefined),
                                                  PreparationSignalName_to_text(PreparationSignal_I_D),
                                                  PreparationSignalName_to_text(PreparationSignal_U_GS),
                                                  PreparationSignalName_to_text(PreparationSignal_U_GSS),
                                                  //PreparationSignalName_to_text(PreparationSignal_U_GSS_R),
                                                  PreparationSignalName_to_text(PreparationSignal_U_DS),
                                                  PreparationSignalName_to_text(PreparationSignal_U_DS_L),
                                                  PreparationSignalName_to_text(PreparationSignal_I_S)};
}

namespace fet5_ns {
    static QStringList CalibrationSignalName_sl = {CalibrationSignalName_to_text(CalibrationSignal_Undefined),
                                              CalibrationSignalName_to_text(CalibrationSignal_I_D),
                                              CalibrationSignalName_to_text(CalibrationSignal_I_D_meas),
                                              CalibrationSignalName_to_text(CalibrationSignal_U_GS),
                                              CalibrationSignalName_to_text(CalibrationSignal_U_GS_meas),
                                              CalibrationSignalName_to_text(CalibrationSignal_U_GSS),
                                              //CalibrationSignalName_to_text(CalibrationSignal_U_GSS_R),
                                              CalibrationSignalName_to_text(CalibrationSignal_I_GSS_meas),
                                              //CalibrationSignalName_to_text(CalibrationSignal_I_GSS_R),
                                              CalibrationSignalName_to_text(CalibrationSignal_I_DM_meas),
                                              CalibrationSignalName_to_text(CalibrationSignal_I_DL_meas),
                                              //calibration_signal_name_to_text(CalibrationSignal_R_DS),
                                              //calibration_signal_name_to_text(CalibrationSignal_S),
                                              CalibrationSignalName_to_text(CalibrationSignal_U_DS),
                                              ///CalibrationSignalName_to_text(CalibrationSignal_U_DS_L),
                                              CalibrationSignalName_to_text(CalibrationSignal_U_DS_meas),
                                              CalibrationSignalName_to_text(CalibrationSignal_U_SD_meas),
                                              CalibrationSignalName_to_text(CalibrationSignal_I_S),
                                              CalibrationSignalName_to_text(CalibrationSignal_I_DM),
                                              //CalibrationSignalName_to_text(CalibrationSignal_I_DL),
                                              CalibrationSignalName_to_text(CalibrationSignal_I_D_comp),
                                               CalibrationSignalName_to_text(CalibrationSignal_I_D_duration),
                                               CalibrationSignalName_to_text(CalibrationSignal_U_GS_duration),
                                               CalibrationSignalName_to_text(CalibrationSignal_U_GSS_duration),
                                               CalibrationSignalName_to_text(CalibrationSignal_U_DS_duration),
                                               //CalibrationSignalName_to_text(CalibrationSignal_U_DS_L_duration),
                                               CalibrationSignalName_to_text(CalibrationSignal_I_S_duration)};

    static QStringList CalibratorDACSignalName_sl = {CalibrationSignalName_to_text(CalibrationSignal_Undefined),
                                                    CalibrationSignalName_to_text(CalibrationSignal_U_DS),
                                                    ////CalibrationSignalName_to_text(CalibrationSignal_U_DS_L),
                                               CalibrationSignalName_to_text(CalibrationSignal_I_D),
                                               CalibrationSignalName_to_text(CalibrationSignal_U_GS),

                                               CalibrationSignalName_to_text(CalibrationSignal_U_GSS),
                                               //CalibrationSignalName_to_text(CalibrationSignal_U_GSS_R),

                                               CalibrationSignalName_to_text(CalibrationSignal_I_S),
                                               CalibrationSignalName_to_text(CalibrationSignal_I_DM),
                                               //CalibrationSignalName_to_text(CalibrationSignal_I_DL),
                                               CalibrationSignalName_to_text(CalibrationSignal_I_D_comp)};

    static QStringList CalibratorADCSignalName_sl = {CalibrationSignalName_to_text(CalibrationSignal_Undefined),
                                                 CalibrationSignalName_to_text(CalibrationSignal_I_D_meas),
                                                 CalibrationSignalName_to_text(CalibrationSignal_U_DS_meas),

                                                 CalibrationSignalName_to_text(CalibrationSignal_I_GSS_meas),
                                                 //CalibrationSignalName_to_text(CalibrationSignal_I_GSS_R),

                                                 CalibrationSignalName_to_text(CalibrationSignal_I_DM_meas),
                                                 CalibrationSignalName_to_text(CalibrationSignal_I_DL_meas),
                                                 CalibrationSignalName_to_text(CalibrationSignal_U_SD_meas)};

    static QStringList PreparationSignalName_sl = {PreparationSignalName_to_text(PreparationSignal_Undefined),
                                                  PreparationSignalName_to_text(PreparationSignal_I_D),
                                                  PreparationSignalName_to_text(PreparationSignal_U_GS),
                                                  PreparationSignalName_to_text(PreparationSignal_U_GSS),
                                                  //PreparationSignalName_to_text(PreparationSignal_U_GSS_R),
                                                  PreparationSignalName_to_text(PreparationSignal_U_DS),
                                                  ////PreparationSignalName_to_text(PreparationSignal_U_DS_L),
                                                  PreparationSignalName_to_text(PreparationSignal_I_S)};
}

/////////////////////////// range ///////////////////////////

ENUM_MACRO3(Range_U_for, U_for_Auto, U_for_600mV, U_for_3300mV,
            Auto, Ufor_600_mV, Ufor_3.3_V,
            Авто, Uпр 600 мВ, Uпр 3.3 В,
            0, 1, 2);

ENUM_MACRO4(Range_I_for, I_for_Auto, I_for_500mA, I_for_5A, I_for_50A,
            Auto, Ifor_500_mA, Ifor_5_A, Ifor_50_A,
            Авто, Iпр 500 мА, Iпр 5 А, Iпр 50 А,
            0, 1, 2, 3);

ENUM_MACRO3(Range_U_rev, U_rev_Auto, U_rev_100V, U_rev_700V,
            Auto, Urev_100_V, Urev_700_V,
            Авто, Uобр 100 В, Uобр 700 В,
            0, 1, 2);

ENUM_MACRO11(Range_I_rev, I_rev_Auto, I_rev_5uA_low, I_rev_5uA_high, I_rev_50uA_low, I_rev_50uA_high, I_rev_500uA_low, I_rev_500uA_high,
            I_rev_5mA_low, I_rev_5mA_high, I_rev_50mA_low, I_rev_50mA_high,
            Auto, Irev_5_uA_low, Irev_5_uA_high, Irev_50_uA_low, Irev_50_uA_high, Irev_500_uA_low, Irev_500_uA_high, Irev_5_mA_low, Irev_5_mA_high, Irev_50_mA_low, Irev_50_mA_high,
            Авто, Iобр 2 мкА, Iобр 5 мкА, Iобр 20 мкА, Iобр 50 мкА, Iобр 200 мкА, Iобр 500 мкА, Iобр 2 мА, Iобр 5 мА, Iобр 20 мА, Iобр 50 мА,
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

ENUM_MACRO2(Range_PFM, PFM_Undefined, PFM_,
            Undefined, PFM,
            Не определено, PFM,
            0, 1);

ENUM_MACRO11(ModeRange_I_D, I_D_Auto, I_D__7uA, I_D__40uA, I_D__200uA, I_D__1mA, I_D__10mA,
            I_D_100uA, I_D_1mA, I_D_10mA, //I_D_300uA
            I_D__30A, I_D_40A,
            Auto, Id__7_uA, Id__40_uA, Id__200_uA, Id__1_mA, Id__10_mA,
            I_D_100uA, I_D_1mA, Id_10_mA, //I_D_300uA
            Id__30_A, Id_40_A,
            Авто, Iс от -1мкА до -7мкА, Iс от -7мкА до -40мкА, Iс от -40мкА до -200мкА, Iс от -200мкА до -1мА, Iс -10мА,
            Iс от 10мкА до 100мкА, Iс от 100мкА до 1мА, Iс 10мА, // Iс от 100мкА до 300мкА
            Iс от -8А до -30А, Iс от 8А до 40А,
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

ENUM_MACRO9(MeasureRange_I_D, _I_D_Auto, _I_D__7uA, _I_D__40uA, _I_D__200uA, _I_D__1mA, _I_D__30A,
            _I_D_100uA, _I_D_1mA, _I_D_40A,
            Auto, Id__7_uA, Id__40_uA, Id__200_uA, Id__1_mA, Id__30_A,
            Id_100_uA, I_D_1mA, I_D_40A,
            Авто, Iс изм от -1мкА до -7мкА, Iс изм от -7мкА до -40мкА, Iс изм от -40мкА до -200мкА, Iс изм от -200мкА до -1мА, Iс изм от -8А до -30А,
            Iс изм от 10мкА до 100мкА, Iс изм от 100мкА до 1мА, Iс изм от 8А до 40А,
            0, 1, 2, 3, 4, 5, 6, 7, 8);

ENUM_MACRO3(ModeRange_U_GS, U_GS_Auto, U_GS_25V, U_GS__30V,
            Auto, Ugs_25_V, Ugs__30_V,
            Авто, Uзи от 1В до 25В, Uзи от -1В до -25В,
            0, 1, 2);

ENUM_MACRO3(MeasureRange_U_GS, _U_GS_Auto, _U_GS_7V, _U_GS__10V,
            Auto, Ugs_7_V, Ugs__10_V,
            Авто, Uзи изм от 1В до 7В, Uзи изм от -1В до -10В,
            0, 1, 2);

ENUM_MACRO5(ModeRange_U_GSS, U_GSS_Auto, U_GSS__25V, U_GSS_25V, U_GSS__30V, U_GSS_30V,
            Auto, Ugss__25_V, Ugss_25_V, Ugss__30_V, Ugss_30_V,
            Авто, Uзи ут от -15В до -25В, Uзи ут от 15В до 25В, Uзи ут от -1В до -30В, Uзи ут от 1В до 30В,
            0, 1, 2, 3, 4);

ENUM_MACRO3(MeasureRange_I_GSS, _I_GSS_Auto, _I_GSS__300nA, _I_GSS_300nA,
            Auto, Igss__300_nA, Igss_300_nA,
            Авто, Iз изм от -30нА до -300нА, Iз изм от 30нА до 300нА,
            0, 1, 2);

ENUM_MACRO3(MeasureRange_I_DM, _I_DM_Auto, _I_DM__150A, _I_DM_200A,
            Auto, Idm__150_A, Idm_200_A,
            Авто, Iс max от -45А до -150А, Iс max от 50А до 200А,
            0, 1, 2);

ENUM_MACRO3(MeasureRange_I_DL, _I_DL_Auto, _I_DL__30A, _I_DL_40A,
            Auto, Idl__30_A, Idl_40_A,
            Авто, Iс инд от -15А до -25А, Iс инд от 8А до 40А,
            0, 1, 2);

ENUM_MACRO5(ModeRange_U_DS, U_DS_Auto, U_DS__50V, U_DS_60V, U_DS_110V, U_DS__250V,
            Auto, Uds__50_V, Uds_60_V, Uds_110_V, Uds__250_V,
            Авто, Uси от -15В до -50В, Uси от 15В до 60В, Uси от 45В до 110В, Uси от -80В до -250В,
            0, 1, 2, 3, 4);

ENUM_MACRO3(ModeRange_U_DS_L, U_DS_L_Auto, U_DS_L__30V, U_DS_L_60V,
            Auto, Uds_L__30_V, Uds_L_60_V,
            Авто, Uси инд от -15В до -30В, Uси инд от 15В до 60В,
            0, 1, 2);

ENUM_MACRO7(MeasureRange_U_DS, _U_DS_Auto, _U_DS__600mV, _U_DS_300mV, _U_DS_2V, _U_DS__6V, _U_DS_110V, _U_DS__250V,
            Auto, Uds__600_mV, Uds_300_mV, Uds_2_V, Uds__6_V, Uds_110_V, Uds__250_V,
            Авто, Uси изм -600мВ, Uси изм от 50мВ до 300мВ, Uси изм от 300мВ до 2В, Uси изм -1В до -6В, Uси изм от 45В до 110В, Uси изм от -80В до -250В,
            0, 1, 2, 3, 4, 5, 6);

ENUM_MACRO4(MeasureRange_U_SD, _U_SD_Auto, _U_SD__600mV, _U_SD__3V, _U_SD_3V,
            Auto, Usd__600_mV, Usd__3_V, Usd_3_V,
            Авто, Uис от -500мВ до -600мВ, Uис от -500мВ до -3В, Uис от 1В до 3В,
            0, 1, 2, 3);

ENUM_MACRO5(ModeRange_I_S, I_S_Auto, I_S__100mA, I_S_100mA, I_S__25A, I_S_50A,
            Auto, Is__100_mA, Is_100_mA, Is__25_A, Is_50_A,
            Авто, Iи от -50мА до -100мА, Iи от 50мА до 100мА, Iи от -15 А до -25А, Iи от 10А до 50А,
            0, 1, 2, 3, 4);

ENUM_MACRO3(ModeRange_I_DM, I_DM_Auto, I_DM__150A, I_DM_200A,
            Auto, Idm__150_A, Idm_200_A,
            Авто, Iс max от -45А до -150А, Iс max от 50А до 200А,
            0, 1, 2);

//ENUM_MACRO2(ModeRange_I_DL, I_DL_Auto, I_DL__30A,
//            Auto, Idl__30_A,
//            Авто, Iс инд -30А,
//            0, 1);

ENUM_MACRO3(ModeRange_I_D_comp, I_D_comp_Auto, I_D_comp__30A, I_D_comp_40A,
            Auto, Idcomp__30_A, Idcomp_40_A,
            Авто, Iс комп от -8А до -30А, Iс комп от 8А до 40А,
            0, 1, 2);

SignalName signal_from_calibration_signal(CalibrationSignalName calibration_signal_name);

QString signal_range_to_text(const SignalName signal, const int range);

QString any_range_to_text(const int signal, const int range);
QString any_range_to_text_EN(const int signal, const int range);
int any_range_from_text(QString qtext);

static QStringList MeasureRange_U_for = {Range_U_for_to_text(U_for_Auto),
                                        Range_U_for_to_text(U_for_600mV),
                                        Range_U_for_to_text(U_for_3300mV)};

static QStringList ModeRange_I_for = {Range_I_for_to_text(I_for_Auto),
                                      Range_I_for_to_text(I_for_500mA),
                                      Range_I_for_to_text(I_for_5A),
                                      Range_I_for_to_text(I_for_50A)};

static QStringList ModeRange_U_rev = {Range_U_rev_to_text(U_rev_Auto),
                                      Range_U_rev_to_text(U_rev_100V),
                                      Range_U_rev_to_text(U_rev_700V)};

static QStringList MeasureRange_I_rev = {Range_I_rev_to_text(I_rev_Auto),
                                        Range_I_rev_to_text(I_rev_5uA_low),
                                        Range_I_rev_to_text(I_rev_5uA_high),
                                        Range_I_rev_to_text(I_rev_50uA_low),
                                        Range_I_rev_to_text(I_rev_50uA_high),
                                        Range_I_rev_to_text(I_rev_500uA_low),
                                        Range_I_rev_to_text(I_rev_500uA_high),
                                        Range_I_rev_to_text(I_rev_5mA_low),
                                        Range_I_rev_to_text(I_rev_5mA_high),
                                        Range_I_rev_to_text(I_rev_50mA_low),
                                        Range_I_rev_to_text(I_rev_50mA_high)};

static QStringList Range_PFM_sl = {Range_PFM_to_text(PFM_Undefined),
                                  Range_PFM_to_text(PFM_)};

namespace fet2_ns {
    static QStringList ModeRange_I_D_sl = {ModeRange_I_D_to_text(I_D_Auto),
                                           ModeRange_I_D_to_text(I_D_100uA),
                                           ModeRange_I_D_to_text(I_D_1mA),
                                           ModeRange_I_D_to_text(I_D_10mA),
                                           ModeRange_I_D_to_text(I_D_40A)};

    static QStringList ModeRange_I_D_HV_sl = {ModeRange_I_D_to_text(I_D_Auto),
                                           ModeRange_I_D_to_text(I_D_100uA),
                                           ModeRange_I_D_to_text(I_D_1mA),
                                           ModeRange_I_D_to_text(I_D_10mA)};

    static QStringList ModeRange_I_D_HV_U_GS_sl = {ModeRange_I_D_to_text(I_D_Auto),
                                           ModeRange_I_D_to_text(I_D_1mA)};

    static QStringList ModeRange_I_D_HV_U_DS_sl = {ModeRange_I_D_to_text(I_D_Auto),
                                           ModeRange_I_D_to_text(I_D_10mA)};

    static QStringList ModeRange_I_D_HC_sl = {ModeRange_I_D_to_text(I_D_Auto),
                                           ModeRange_I_D_to_text(I_D_40A)};

    static QStringList MeasureRange_I_D_sl = {MeasureRange_I_D_to_text(_I_D_Auto),
                                              MeasureRange_I_D_to_text(_I_D_100uA),
                                              MeasureRange_I_D_to_text(_I_D_1mA),
                                              MeasureRange_I_D_to_text(_I_D_40A)};

    static QStringList MeasureRange_I_D_HV_sl = {MeasureRange_I_D_to_text(_I_D_Auto),
                                              MeasureRange_I_D_to_text(_I_D_100uA),
                                              MeasureRange_I_D_to_text(_I_D_1mA)};

    static QStringList MeasureRange_I_D_HC_sl = {MeasureRange_I_D_to_text(_I_D_Auto),
                                              MeasureRange_I_D_to_text(_I_D_40A)};

    static QStringList ModeRange_U_GS_sl = {ModeRange_U_GS_to_text(U_GS_Auto),
                                            ModeRange_U_GS_to_text(U_GS_25V)};

    static QStringList MeasureRange_U_GS_sl = {MeasureRange_U_GS_to_text(_U_GS_Auto),
                                              MeasureRange_U_GS_to_text(_U_GS_7V)};

    static QStringList ModeRange_U_GSS_sl = {ModeRange_U_GSS_to_text(U_GSS_Auto),
                                         ModeRange_U_GSS_to_text(U_GSS__25V),
                                        ModeRange_U_GSS_to_text(U_GSS_25V)};

    static QStringList ModeRange_U_GSS_P_sl = {ModeRange_U_GSS_to_text(U_GSS_Auto),
                                            ModeRange_U_GSS_to_text(U_GSS_30V)};

    static QStringList ModeRange_U_GSS_R_sl = {ModeRange_U_GSS_to_text(U_GSS_Auto),
                                            ModeRange_U_GSS_to_text(U_GSS__30V)};

    static QStringList MeasureRange_I_GSS_sl = {MeasureRange_I_GSS_to_text(_I_GSS_Auto),
                                         MeasureRange_I_GSS_to_text(_I_GSS__300nA),
                                        MeasureRange_I_GSS_to_text(_I_GSS_300nA)};

    static QStringList MeasureRange_I_GSS_P_sl = {MeasureRange_I_GSS_to_text(_I_GSS_Auto),
                                         MeasureRange_I_GSS_to_text(_I_GSS_300nA)};

    static QStringList MeasureRange_I_GSS_R_sl = {MeasureRange_I_GSS_to_text(_I_GSS_Auto),
                                         MeasureRange_I_GSS_to_text(_I_GSS__300nA)};

    static QStringList MeasureRange_I_DM_sl = {MeasureRange_I_DM_to_text(_I_DM_Auto),
                                                MeasureRange_I_DM_to_text(_I_DM_200A)};

    static QStringList MeasureRange_I_DL_sl = {MeasureRange_I_DL_to_text(_I_DL_Auto),
                                                MeasureRange_I_DL_to_text(_I_DL_40A)};

    static QStringList ModeRange_U_DS_sl = {ModeRange_U_DS_to_text(U_DS_Auto),
                                            ModeRange_U_DS_to_text(U_DS_60V),
                                           ModeRange_U_DS_to_text(U_DS_110V)};

    static QStringList ModeRange_U_DS_HV_sl = {ModeRange_U_DS_to_text(U_DS_Auto),
                                           ModeRange_U_DS_to_text(U_DS_110V)};

    static QStringList ModeRange_U_DS_HC_sl = {ModeRange_U_DS_to_text(U_DS_Auto),
                                               ModeRange_U_DS_to_text(U_DS_60V)};

    static QStringList ModeRange_U_DS_L_sl = {ModeRange_U_DS_L_to_text(U_DS_L_Auto),
                                            ModeRange_U_DS_L_to_text(U_DS_L_60V)};

    static QStringList MeasureRange_U_DS_sl = {MeasureRange_U_DS_to_text(_U_DS_Auto),
                                               MeasureRange_U_DS_to_text(_U_DS_300mV),
                                               MeasureRange_U_DS_to_text(_U_DS_2V),
                                               MeasureRange_U_DS_to_text(_U_DS_110V)};

    static QStringList MeasureRange_U_DS_R_DS_sl = {MeasureRange_U_DS_to_text(_U_DS_Auto),
                                               MeasureRange_U_DS_to_text(_U_DS_300mV),
                                               MeasureRange_U_DS_to_text(_U_DS_2V)};

    static QStringList MeasureRange_U_DS_U_DS_sl = {MeasureRange_U_DS_to_text(_U_DS_Auto),
                                               MeasureRange_U_DS_to_text(_U_DS_110V)};

    static QStringList MeasureRange_U_SD_sl = {MeasureRange_U_SD_to_text(_U_SD_Auto),
                                               MeasureRange_U_SD_to_text(_U_SD_3V)};

    static QStringList ModeRange_I_S_sl = {ModeRange_I_S_to_text(I_S_Auto),
                                           ModeRange_I_S_to_text(I_S_100mA),
                                           ModeRange_I_S_to_text(I_S_50A)};

    static QStringList ModeRange_I_DM_sl = {ModeRange_I_DM_to_text(I_DM_Auto),
                                            ModeRange_I_DM_to_text(I_DM_200A)};

    static QStringList ModeRange_I_D_comp_sl = {ModeRange_I_D_comp_to_text(I_D_comp_Auto),
                                            ModeRange_I_D_comp_to_text(I_D_comp_40A)};
}

namespace fet5_ns {
    static QStringList ModeRange_I_D_sl = {ModeRange_I_D_to_text(I_D_Auto),
                                        ModeRange_I_D_to_text(I_D__7uA),
                                        ModeRange_I_D_to_text(I_D__40uA),
                                        ModeRange_I_D_to_text(I_D__200uA),
                                        ModeRange_I_D_to_text(I_D__1mA),
                                        ModeRange_I_D_to_text(I_D__10mA),
                                        ModeRange_I_D_to_text(I_D__30A)};

    static QStringList ModeRange_I_D_HV_sl = {ModeRange_I_D_to_text(I_D_Auto),
                                           ModeRange_I_D_to_text(I_D__7uA),
                                           ModeRange_I_D_to_text(I_D__40uA),
                                           ModeRange_I_D_to_text(I_D__200uA),
                                          ModeRange_I_D_to_text(I_D__1mA),
                                          ModeRange_I_D_to_text(I_D__10mA)};

    static QStringList ModeRange_I_D_HV_U_GS_sl = {ModeRange_I_D_to_text(I_D_Auto),
                                                   ModeRange_I_D_to_text(I_D__1mA)};

    static QStringList ModeRange_I_D_HV_U_DS_sl = {ModeRange_I_D_to_text(I_D_Auto),
                                                   ModeRange_I_D_to_text(I_D__10mA)};

    static QStringList ModeRange_I_D_HC_sl = {ModeRange_I_D_to_text(I_D_Auto),
                                          ModeRange_I_D_to_text(I_D__30A)};

    static QStringList MeasureRange_I_D_sl = {MeasureRange_I_D_to_text(_I_D_Auto),
                                              MeasureRange_I_D_to_text(_I_D__7uA),
                                              MeasureRange_I_D_to_text(_I_D__40uA),
                                              MeasureRange_I_D_to_text(_I_D__200uA),
                                              MeasureRange_I_D_to_text(_I_D__1mA),
                                              MeasureRange_I_D_to_text(_I_D__30A)};

    static QStringList MeasureRange_I_D_HV_sl = {MeasureRange_I_D_to_text(_I_D_Auto),
                                              MeasureRange_I_D_to_text(_I_D__7uA),
                                              MeasureRange_I_D_to_text(_I_D__40uA),
                                              MeasureRange_I_D_to_text(_I_D__200uA),
                                              MeasureRange_I_D_to_text(_I_D__1mA)};

    static QStringList MeasureRange_I_D_HC_sl = {MeasureRange_I_D_to_text(_I_D_Auto),
                                              MeasureRange_I_D_to_text(_I_D__30A)};

    static QStringList ModeRange_U_GS_sl = {ModeRange_U_GS_to_text(U_GS_Auto),
                                            ModeRange_U_GS_to_text(U_GS__30V)};

    static QStringList MeasureRange_U_GS_sl = {MeasureRange_U_GS_to_text(_U_GS_Auto),
                                              MeasureRange_U_GS_to_text(_U_GS__10V)};

    static QStringList ModeRange_U_GSS_sl = {ModeRange_U_GSS_to_text(U_GSS_Auto),
                                            ModeRange_U_GSS_to_text(U_GSS__30V),
                                            ModeRange_U_GSS_to_text(U_GSS_30V)};

    static QStringList ModeRange_U_GSS_P_sl = {ModeRange_U_GSS_to_text(U_GSS_Auto),
                                            ModeRange_U_GSS_to_text(U_GSS_30V)};

    static QStringList ModeRange_U_GSS_R_sl = {ModeRange_U_GSS_to_text(U_GSS_Auto),
                                            ModeRange_U_GSS_to_text(U_GSS__30V)};

    static QStringList MeasureRange_I_GSS_sl = {MeasureRange_I_GSS_to_text(_I_GSS_Auto),
                                         MeasureRange_I_GSS_to_text(_I_GSS__300nA),
                                        MeasureRange_I_GSS_to_text(_I_GSS_300nA)};

    static QStringList MeasureRange_I_GSS_P_sl = {MeasureRange_I_GSS_to_text(_I_GSS_Auto),
                                         MeasureRange_I_GSS_to_text(_I_GSS_300nA)};

    static QStringList MeasureRange_I_GSS_R_sl = {MeasureRange_I_GSS_to_text(_I_GSS_Auto),
                                         MeasureRange_I_GSS_to_text(_I_GSS__300nA)};

    static QStringList MeasureRange_I_DM_sl = {MeasureRange_I_DM_to_text(_I_DM_Auto),
                                       MeasureRange_I_DM_to_text(_I_DM__150A)};

    static QStringList MeasureRange_I_DL_sl = {MeasureRange_I_DL_to_text(_I_DL_Auto),
                                       MeasureRange_I_DL_to_text(_I_DL__30A)};

    static QStringList ModeRange_U_DS_sl = {ModeRange_U_DS_to_text(U_DS_Auto),
                                               ModeRange_U_DS_to_text(U_DS__50V),
                                               ModeRange_U_DS_to_text(U_DS__250V)};

    static QStringList ModeRange_U_DS_HV_sl = {ModeRange_U_DS_to_text(U_DS_Auto),
                                           ModeRange_U_DS_to_text(U_DS__250V)};

    static QStringList ModeRange_U_DS_HC_sl = {ModeRange_U_DS_to_text(U_DS_Auto),
                                            ModeRange_U_DS_to_text(U_DS__50V)};

    static QStringList ModeRange_U_DS_L_sl = {ModeRange_U_DS_L_to_text(U_DS_L_Auto),
                                            ModeRange_U_DS_L_to_text(U_DS_L__30V)};

    static QStringList MeasureRange_U_DS_sl = {MeasureRange_U_DS_to_text(_U_DS_Auto),
                                               ////MeasureRange_U_DS_to_text(_U_DS__600mV),
                                               MeasureRange_U_DS_to_text(_U_DS__6V),
                                               MeasureRange_U_DS_to_text(_U_DS__250V)};

    static QStringList MeasureRange_U_DS_U_DS_sl = {MeasureRange_U_DS_to_text(_U_DS_Auto),
                                               MeasureRange_U_DS_to_text(_U_DS__250V)};

    static QStringList MeasureRange_U_DS_R_DS_sl = {MeasureRange_U_DS_to_text(_U_DS_Auto),
                                               MeasureRange_U_DS_to_text(_U_DS__6V)};

    static QStringList MeasureRange_U_SD_sl = {MeasureRange_U_SD_to_text(_U_SD_Auto),
                                        ////MeasureRange_U_SD_to_text(_U_SD__600mV),
                                        MeasureRange_U_SD_to_text(_U_SD__3V)};

    static QStringList ModeRange_I_S_sl = {ModeRange_I_S_to_text(I_S_Auto),
                                           ModeRange_I_S_to_text(I_S__100mA),
                                           ModeRange_I_S_to_text(I_S__25A)};

    static QStringList ModeRange_I_DM_sl = {ModeRange_I_DM_to_text(I_DM_Auto),
                                            ModeRange_I_DM_to_text(I_DM__150A)};

//    static QStringList ModeRange_I_DL_sl = {ModeRange_I_DL_to_text(I_DL_Auto),
//                                            ModeRange_I_DL_to_text(I_DL__30A)};

    static QStringList ModeRange_I_D_comp_sl = {ModeRange_I_D_comp_to_text(I_D_comp_Auto),
                                            ModeRange_I_D_comp_to_text(I_D_comp__30A)};
}

namespace diode_ns {
    static QVector<QStringList> CalibrationRanges_sl_v = {{},
                                                         ModeRange_I_for,
                                                         MeasureRange_U_for,
                                                         MeasureRange_U_for,
                                                         MeasureRange_I_rev,
                                                         MeasureRange_I_rev,
                                                         ModeRange_U_rev,
                                                         Range_PFM_sl,
                                                         ModeRange_I_for,
                                                         ModeRange_U_rev,
                                                         ModeRange_I_for,
                                                         ModeRange_U_rev};

    static QVector<int> CalibrationSync_v = {0,
                                             0,
                                             0,
                                             0,
                                             0,
                                             0,
                                             0,
                                             1, //CalibrationSignal_PFM
                                             1, //CalibrationSignal_I_for_tune
                                             1, //CalibrationSignal_U_rev_tune
                                             0,
                                             0};


    static QVector<QStringList> CalibratorDACRanges_sl_v = {{},
                                                         ModeRange_I_for,
                                                         ModeRange_U_rev};

    static QVector<QStringList> CalibratorADCRanges_sl_v = {{},
                                                         MeasureRange_U_for,
                                                         MeasureRange_I_rev};

    static QVector<QStringList> PreparationRanges_sl_v = {{},
                                                         ModeRange_I_for,
                                                         ModeRange_U_rev};
}

namespace fet2_ns {
    static QVector<QStringList> CalibrationRanges_sl_v = {{},
                                                         ModeRange_I_D_sl,
                                                         MeasureRange_I_D_sl,
                                                         ModeRange_U_GS_sl,
                                                         MeasureRange_U_GS_sl,
                                                         ModeRange_U_GSS_sl,
                                                         //Range_U_GSS_R_sl,
                                                         MeasureRange_I_GSS_sl,
                                                         //Range_I_GSS_R_sl,
                                                         MeasureRange_I_DM_sl,
                                                         MeasureRange_I_DL_sl,
                                                         //R
                                                         //S
                                                         ModeRange_U_DS_sl,                                                          
                                                         ModeRange_U_DS_L_sl,
                                                         MeasureRange_U_DS_sl,
                                                         MeasureRange_U_SD_sl,
                                                         ModeRange_I_S_sl,
                                                         ModeRange_I_DM_sl,
                                                         ModeRange_I_D_comp_sl,
                                                          ModeRange_I_D_sl,
                                                          ModeRange_U_GS_sl,
                                                          ModeRange_U_GSS_sl,
                                                          ModeRange_U_DS_sl,
                                                          ModeRange_U_DS_L_sl,
                                                          ModeRange_I_S_sl};

    static QVector<int> CalibrationSync_v = {0,
                                             0,
                                             0,
                                             0,
                                             0,
                                             0,
                                             0,
                                             //0,
                                             0,
                                             //0,
                                             0,
                                             0,
                                             //R
                                             //S
                                             0,
                                             0,
                                             0,
                                             0,
                                             0,
                                             0,
                                             0,
                                             0,
                                             0,
                                             0,
                                             0,
                                             0,
                                             0};

    static QVector<QStringList> CalibratorDACRanges_sl_v = {{},
                                                            ModeRange_U_DS_sl,
                                                            ModeRange_U_DS_L_sl,
                                                            ModeRange_I_D_sl,
                                                            ModeRange_U_GS_sl,
                                                            ModeRange_U_GSS_sl,
                                                            //Range_U_GSS_R_sl,
                                                            ModeRange_I_S_sl,
                                                            ModeRange_I_DM_sl,
                                                            ModeRange_I_D_comp_sl};

    static QVector<QStringList> CalibratorADCRanges_sl_v = {{},
                                                            MeasureRange_I_D_sl, // + Range_I_DM_sl.pop_back() + Range_I_DL_sl
                                                            MeasureRange_U_DS_sl, // + MeasureRange_U_GS_sl
                                                            MeasureRange_I_GSS_sl,
                                                            //Range_I_GSS_R_sl,
                                                            MeasureRange_I_DM_sl,
                                                            MeasureRange_I_DL_sl,
                                                            MeasureRange_U_SD_sl};

    static QVector<QStringList> PreparationRanges_sl_v = {{},
                                                             ModeRange_I_D_sl,
                                                             ModeRange_U_GS_sl,
                                                             ModeRange_U_GSS_sl,
                                                             //Range_U_GSS_R_sl,
                                                             ModeRange_U_DS_sl,
                                                             ModeRange_U_DS_L_sl,
                                                             ModeRange_I_S_sl};
}

namespace fet5_ns {
    static QVector<QStringList> CalibrationRanges_sl_v = {{},
                                                         ModeRange_I_D_sl,
                                                         MeasureRange_I_D_sl,
                                                         ModeRange_U_GS_sl,
                                                         MeasureRange_U_GS_sl,
                                                         ModeRange_U_GSS_sl,
                                                         //Range_U_GSS_R_sl,
                                                         MeasureRange_I_GSS_sl,
                                                         //Range_I_GSS_R_sl,
                                                         MeasureRange_I_DM_sl,
                                                         MeasureRange_I_DL_sl,
                                                         //R
                                                         //S
                                                         ModeRange_U_DS_sl,
                                                         ////ModeRange_U_DS_L_sl,
                                                         MeasureRange_U_DS_sl,
                                                         MeasureRange_U_SD_sl,
                                                         ModeRange_I_S_sl,
                                                         ModeRange_I_DM_sl,
                                                         //ModeRange_I_DL_sl,
                                                         ModeRange_I_D_comp_sl,
                                                          ModeRange_I_D_sl,
                                                          ModeRange_U_GS_sl,
                                                          ModeRange_U_GSS_sl,
                                                          ModeRange_U_DS_sl,
                                                          ////ModeRange_U_DS_L_sl,
                                                          ModeRange_I_S_sl
                                                         };

    static QVector<int> CalibrationSync_v = {0,
                                             0,
                                             0,
                                             0,
                                             0,
                                             0,
                                             0,
                                             //0,
                                             0,
                                             //0,
                                             0,
                                             0,
                                             //R
                                             //S
                                             0,
                                             ////0, //U_DS_L
                                             0,
                                             0,
                                             0,
                                             0,
                                             //0, //I_DL
                                             0,
                                             0,
                                             0,
                                             0,
                                             ////0, //U_DS_L
                                             0};

    static QVector<QStringList> CalibratorDACRanges_sl_v = {{},
                                                            ModeRange_U_DS_sl,
                                                            ////ModeRange_U_DS_L_sl,
                                                            ModeRange_I_D_sl,
                                                            ModeRange_U_GS_sl,
                                                            ModeRange_U_GSS_sl,
                                                            //Range_U_GSS_R_sl,
                                                            ModeRange_I_S_sl,
                                                            ModeRange_I_DM_sl,
                                                            //ModeRange_I_DL_sl,
                                                            ModeRange_I_D_comp_sl};

    static QVector<QStringList> CalibratorADCRanges_sl_v = {{},
                                                            MeasureRange_I_D_sl, // + Range_I_DM_sl.pop_back() + Range_I_DL_sl
                                                            MeasureRange_U_DS_sl, // + MeasureRange_U_GS_sl
                                                            MeasureRange_I_GSS_sl,
                                                            //Range_I_GSS_R_sl,
                                                            MeasureRange_I_DM_sl,
                                                            MeasureRange_I_DL_sl,
                                                            MeasureRange_U_SD_sl};

    static QVector<QStringList> PreparationRanges_sl_v = {{},
                                                             ModeRange_I_D_sl,
                                                             ModeRange_U_GS_sl,
                                                             ModeRange_U_GSS_sl,
                                                             //Range_U_GSS_R_sl,
                                                             ModeRange_U_DS_sl,
                                                             ////ModeRange_U_DS_L_sl,
                                                             ModeRange_I_S_sl};
}

/////////////////////////// dimensions ///////////////////////////

//typedef std::ratio<1, 1000000000> n_ratio;
//typedef std::ratio<1, 1000000> u_ratio;
//typedef std::ratio<1, 1000> m_ratio;
//typedef std::ratio<1000, 1> k_ratio;
//typedef std::ratio<1000000, 1> M_ratio;
//typedef std::ratio<1000000000, 1> G_ratio;

//static std::map<std::string, long double> dimension_m = {
//    {"n", 0.000000001},
//    {"u", 0.000001},
//    {"m", 0.001},
//    {"k", 1000},
//    {"M", 1000000},
//    {"G", 1000000000},
//    {"н", 0.000000001},
//    {"мк", 0.000001},
//    {"м", 0.001},
//    {"к", 1000},
//    {"М", 1000000},
//    {"Г", 1000000000}
//};

static std::pair<double, double> n_pair = {1, 1000000000};
static std::pair<double, double> u_pair = {1, 1000000};
static std::pair<double, double> m_pair = {1, 1000};
static std::pair<double, double> k_pair = {1000, 1};
static std::pair<double, double> M_pair = {1000000, 1};
static std::pair<double, double> G_pair = {1000000000, 1};

static std::map<std::string, std::pair<double, double>> dimension_m = {
    {"n", n_pair},
    {"u", u_pair},
    {"m", m_pair},
    {"k", k_pair},
    {"M", M_pair},
    {"G", G_pair},
    {"н", n_pair},
    {"мк", u_pair},
    {"м", m_pair},
    {"к", k_pair},
    {"М", M_pair},
    {"Г", G_pair}
};

static std::vector<std::string> dimension_v = {"n", "u", "m", "k", "M", "G", "н", "мк", "м", "к", "М", "Г"};
static std::vector<int> dimension_erase_v = {1, 1, 1, 1, 1, 1, 2, 4, 2, 2, 2, 2};

static std::vector<std::string> dimension_up = {"к", "М", "Г"};
static std::vector<std::string> dimension_down = {"м", "мк", "н"};

static std::map<std::string, QStringList> dimension_metric_prefix_m = {
    {"А", {"А", "мА", "мкА", "нА"}},
    {"В", {"В", "мВ"}},
    {"Ом", {"Ом", "мОм"}},
    {"См", {"См", "мСм"}}
    };

static std::map<std::string, std::string> signal_dimension_m = {
    {"I", "А"},
    {"U", "В",},
    {"R", "Ом"},
    {"S", "См"}
    };

/////////////////////////// MATH ///////////////////////////

static std::map<std::string, std::function<bool(bool, bool)>> comparisions_bool_m = {
    {"L", std::less<bool>()},
    {"LT", std::less<bool>()},
    {"G", std::greater<bool>()},
    {"GT", std::greater<bool>()},
    {"E", std::equal_to<bool>()},
    {"EQ", std::equal_to<bool>()},
    {"NE", std::not_equal_to<bool>()},
    {"LE", std::less_equal<bool>()},
    {"GE", std::greater_equal<bool>()},

    {"<", std::less<bool>()},
    {">", std::greater<bool>()},
    {"==", std::equal_to<bool>()},
    {"!=", std::not_equal_to<bool>()},
    {"<=", std::less_equal<bool>()},
    {">=", std::greater_equal<bool>()},

    {_LT, std::less<bool>()},
    {_GT, std::greater<bool>()},
    {_LE, std::less_equal<bool>()},
    {_GE, std::greater_equal<bool>()},
    {_EQ, std::equal_to<bool>()},
    {_NE, std::not_equal_to<bool>()},
    {_CIEQ, std::equal_to<bool>()},
    {_CIEQ, std::not_equal_to<bool>()}
};

#define value_epsilon 0.000000001
static std::function<bool(double, double)> equal_to_double = [](double x, double y) { return std::abs(x - y) < value_epsilon; };
static std::function<bool(double, double)> not_equal_to_double = [](double x, double y) { return !(std::abs(x - y) < value_epsilon); };

static std::map<std::string, std::function<bool(double, double)>> comparisions_double_m = {
    {"L", std::less<double>()},
    {"LT", std::less<double>()},
    {"G", std::greater<double>()},
    {"GT", std::greater<double>()},
    //{"E", std::equal_to<double>()},
    {"E", equal_to_double},
    //{"NE", std::not_equal_to<double>()},
    {"NE", not_equal_to_double},
    {"LE", std::less_equal<double>()},
    {"GE", std::greater_equal<double>()},

    {"<", std::less<double>()},
    {">", std::greater<double>()},
    //{"==", std::equal_to<double>()},
    {"==", equal_to_double},
    //{"!=", std::not_equal_to<double>()},
    {"!=", not_equal_to_double},
    {"<=", std::less_equal<double>()},
    {">=", std::greater_equal<double>()},

    {_LT, std::less<double>()},
    {_GT, std::greater<double>()},
    {_LE, std::less_equal<double>()},
    {_GE, std::greater_equal<double>()},
    //{_EQ, std::equal_to<double>()},
    {_EQ, equal_to_double},
    //{_NE, std::not_equal_to<double>()},
    {_NE, not_equal_to_double},
    {_CIEQ, std::equal_to<double>()},
    {_CIEQ, std::not_equal_to<double>()}
};

static std::map<std::string, std::function<bool(std::string, std::string)>> comparisions_string_m = {
    {"L", std::less<std::string>()},
    {"LT", std::less<std::string>()},
    {"G", std::greater<std::string>()},
    {"GT", std::greater<std::string>()},
    {"E", std::equal_to<std::string>()},
    {"EQ", std::equal_to<std::string>()},
    {"NE", std::not_equal_to<std::string>()},
    {"CIEQ", std::equal_to<std::string>()},
    {"CINE", std::not_equal_to<std::string>()},
    {"LE", std::less_equal<std::string>()},
    {"GE", std::greater_equal<std::string>()},

    {"<", std::less<std::string>()},
    {">", std::greater<std::string>()},
    {"==", std::equal_to<std::string>()},
    {"!=", std::not_equal_to<std::string>()},
    {"<=", std::less_equal<std::string>()},
    {">=", std::greater_equal<std::string>()},

    {_LT, std::less<std::string>()},
    {_GT, std::greater<std::string>()},
    {_LE, std::less_equal<std::string>()},
    {_GE, std::greater_equal<std::string>()},
    {_EQ, std::equal_to<std::string>()},
    {_NE, std::not_equal_to<std::string>()},
    {_CIEQ, std::equal_to<std::string>()},
    {_CINE, std::not_equal_to<std::string>()},
};

static std::map<char, std::function<double(double, double)>> math_expressions_double_m = {
    {'+', std::plus<double>()},
    {'-', std::minus<double>()},
    {'/', std::divides<double>()},
    {'*', std::multiplies<double>()}
};

#endif // ENUMS_H
