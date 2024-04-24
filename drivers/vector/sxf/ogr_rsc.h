//
// Created by leonid on 24.04.24.
//


#include <string>
#include <vector>
#include "cpl_port.h"

constexpr int DEFAULT_RGB = 0x00B536AD; // rgb(181, 54, 173);
/*
    RSC File record
*/
typedef struct {
    GUInt32 nOffset;      // RSC Section offset in bytes from the beginning of the RSC file
    GUInt32 nLength;      // RSC Section record length
    GUInt32 nRecordCount; // Count of records in the section
} RSCSection;

/*
    RSC File header
*/
typedef struct {
    GByte nEncoding[4];
    GUInt32 nFileState;
    GUInt32 nFileModState;
    GUInt32 nLang;              // 1 - en, 2 - ru
    GUInt32 nNextID;
    GByte date[8];
    GByte szMapType[32];
    GByte szClassifyName[32];
    GByte szClassifyCode[8];
    GUInt32 nScale;
    GUInt32 nScalesRange;       // 1 for scales 1:1 to 1:10000, for others - 0
    RSCSection Objects;            // OBJ
    RSCSection Semantic;        // SEM
    RSCSection ClassifySemantic;// CLS
    RSCSection DefaultsSemantic;// DEF
    RSCSection PossibleSemantic;// POS
    RSCSection Layers;            // SEG
    RSCSection Domains;            // LIM
    RSCSection Parameters;        // PAR
    RSCSection Print;            // PRN
    RSCSection Palettes;        // PAL
    RSCSection Fonts;            // TXT
    RSCSection Libs;            // IML
    RSCSection ImageParams;
    RSCSection Tables;            // TAB
    GByte nFlagKeysAsCodes;
    GByte nFlagPaletteMods;
    GByte Reserved[30];
    GUInt32 nFontEnc;
    GUInt32 nColorsInPalette;
} RSCHeader;

typedef struct {
    GUInt32 nLength;
    GByte szName[32];
    GByte szShortName[16];
    GByte nNo;
    GByte nDrawOrder; // 0 - 255. Less number will draw earlier
    GUInt16 nSemanticCount;
    GUInt32 reserve;
} RSCLayer;

typedef struct {
    GUInt32 nCode;
    GUInt16 nType;
    GByte bAllowMultiple;
    GByte bAllowAnythere;
    GByte szName[32];
    GByte szShortName[16];
    GByte szMeasurementValue[8];
    GUInt16 nFieldSize; // 0 - 255
    GByte nPrecision; // Number of digits after decimal point
    GByte bIsComplex;
    GUInt32 nClassifyOffset;
    GUInt32 nClassifyCount;
    GUInt32 nClassifyDefaultsOffset;
    GUInt32 nClassifyDefaultsCount;

} RSCSemantics;

enum RSCSemanticsType {
    RSC_SC_TEXT = 0,
    RSC_SC_REAL = 1,
    RSC_SC_FILE_NAME = 9,
    RSC_SC_BMP_NAME = 10,
    RSC_SC_OPE_NAME = 11,
    RSC_SC_LINK = 12,  // Map object identifier
    RSC_SC_PASSPORT_FILE = 13,
    RSC_SC_TXT_FILE = 14,
    RSC_SC_PCX_FILE = 15
};

enum RSCGraphicsType {
    RSC_GT_LINE = 128,
    RSC_GT_DASHED_LINE = 129,
    RSC_GT_DOTED_LINE = 148,
    RSC_GT_SQUARE = 135,
    RSC_GT_HATCH_SQUARE = 153,
    RSC_GT_POINT = 143,
    RSC_GT_POINTED_SQUARE = 144,
    RSC_GT_ROUND = 140,
    RSC_GT_FILL = 154,
    RSC_GT_VECTOR = 149,
    RSC_GT_VECTOR_SQUARE = 155,
    RSC_GT_DECORATED_LINE = 157,
    RSC_GT_TEXT = 142,
    RSC_GT_USER_FONT = 152,
    RSC_GT_TEMLATE = 150,
    RSC_GT_TTF_SYM = 151,
    RSC_GT_GRAPTH_GROUP = 147,
    RSC_GT_DASHED_LINE_2 = 158,
    RSC_GT_IMG = 165,
    RSC_GT_USER_OBJ = 250
};

typedef struct {
    GUInt32 nLength;
    GUInt32 nClassifyCode;
    GUInt32 nInternalCode;
    GUInt32 nIdCode;
    GByte szShortName[32];
    GByte szName[32];
    GByte nGeometryType; // Same as enum SXFGeometryType
    GByte nLayerId;
    GByte nScalable;
    GByte nLowViewLevel;
    GByte nHeighViewLevel;
    GByte nExtLocalization;
    GByte nDigitizeDirection;
    GByte nUseSemantics;
    GUInt16 nExtNo;
    GByte nLabelsCount;
    GByte nSqueeze;
    GByte nMaxZoom;
    GByte nMinZoom;
    GByte nUseBorders;
    GByte reseve;
    GUInt32 nLinkedText;
    GUInt32 nSemCode;
    GByte szPref[7];
    GByte nZeroes;
} RSCObject;

typedef struct {
    GUInt32 nLength;
    GUInt32 nObjectCode;
    GByte nLocalization;
    GByte reserve[3];
    GUInt16 nMandatorySemCount;
    GUInt16 nPossibleSemCount;
} RSCObjectSemantics;

typedef struct {
    GUInt32 nLength;
    GUInt32 nObjectCode;
    GByte nLocalization;
    GByte reserve[7];
    GUInt32 nSC1;
    GUInt16 nSC1LimCount;
    GUInt16 nSC1LimDefIndex;
    GUInt32 nSC2;
    GUInt16 nSC2LimCount;
    GUInt16 nSC2LimDefIndex;
} RSCLimitsRecord;

typedef struct {
    GUInt32 nColorsTablesOffset;
    GUInt32 nColorsTablesLength;
    GUInt32 nRecordCount;
    GByte reserve[60];
} RSCTables;

constexpr GByte CMYK[] = {
        0, 0, 0, 255,
        170, 170, 0, 85,
        170, 0, 170, 85,
        85, 0, 0, 170,
        0, 170, 170, 85,
        0, 85, 170, 0,
        0, 85, 170, 85,
        0, 0, 0, 85,
        0, 0, 0, 170,
        255, 85, 0, 0,
        170, 0, 170, 0,
        170, 170, 0, 0,
        0, 255, 170, 0,
        0, 170, 0, 0,
        0, 0, 170, 0,
        0, 0, 0, 0
};

constexpr GByte CROSS[] = {
        130, 0, 0, 0,
        68, 0, 0, 0,
        40, 0, 0, 0,
        16, 0, 0, 0,
        40, 0, 0, 0,
        68, 0, 0, 0,
        130, 0, 0, 0
};

typedef struct {
    GByte anPal[1024];
    GByte pszName[32];
} RSCPalette;

typedef struct {
    GByte pszName[32];
    GByte pszCode[32];
    GUInt32 nCode;
    GByte nTestSym;
    GByte nCodePage;
    GByte reserve[2];
} RSCFont;

typedef struct {
    GUInt32 nLength;
    GUInt16 nCode;
    GUInt16 nType;
} RSCParameter;

typedef struct
{
    int nCode;
    int nType;
    std::string osName;
    int nFieldSize;
    int nPrecision;
    bool bAllowAnythere;
    bool bAllowMultiple;
} RSCSem;

typedef struct {
    int nCode;
    int nLoc;
    std::string osName;
    int nLayer;
    std::vector<RSCSem> aoSem;
} RSCObj;

typedef struct {
    std::string osName;
    int nDrawingOrder;
} RSCSeg;

typedef struct
{
    GUInt32 nId;
    GUInt32 nCode;
    double dMin;
    double dDef;
    double dMax;
} RSCSemDefault;