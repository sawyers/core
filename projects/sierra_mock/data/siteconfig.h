
/* siteconfig.h -- This is the include file where all site specific 
   non-hardware dependant compile info is set.  (Hardware dependent info is 
   in iiiconfig.h).  A master copy of this file resides in $INCL, and it is
   cutomized for the site and installed in $IIIDB/options/config by rawinst
   or iiiinst8.  It is the version in the config directory which is used at
   compile time by the "compile" program.  This file is itself included in
   iiidefault.h, and thus is accessed by all programs. */

/* 
 * VERSION="$Date: 2015-04-09 15:37:57 -0700 (Thu, 09 Apr 2015) $ @(#) siteconfig.h $Rev: 246122 $ @(#)";
 */

/*========================================================*/ 
/*
 >>>>>>>>>>>> READ THIS before edit this file.<<<<<<<<<<<<<<<<
 * To enable an option, remove the comments in front of each line.
 * This file is edited by rawinst. Follow the format exactly when 
 * adding new #define.
 * MAX_LANGUAGES will be added by rawinst. You needed to add this #define,
 * if edit by hand except when III_MULTILANG is define.
 */
/*lint -e602 */
/* 
/*
 * Language definitions.  If III_MULTILANG is defined, then 
 * all language definitions are turned on.  Otherwise, turn
 * on each language individually here.
 */
/* #define III_AUS                      /* AUS australian literals  - iiilang */
/* #define III_IRI                      /* IRI irish (gaelic) literals  - extlang */
/* #define III_POR                      /* POR portuguese literals - extlang */
/* #define III_JPN                      /* JPN japanese literals (extlang)&indexing*/
/* #define III_JPX                      /* JPX japanese literals - extlang */
/* #define III_POL                      /* POL polish literals - extlang */
/* #define III_GAG                      /* GAG galician literals - extlang */
/* #define III_EST                      /* EST estonian literals - extlang */
/* #define III_SPI                      /* SPI iberian spanish literals - extlang */
/* #define III_FRC                      /* FRC canadian french EXTERNAL literals - extlang */
/* #define III_FRF                      /* FRF french EXTERNAL literals - extlang */
/* #define III_TUR                      /* TUR turkish literals - extlang */
/* #define III_ITA                      /* ITA italian literals - extlang */
/* #define III_CHX                      /* CHX chinese literals  - extlang */
/* #define III_SWE                      /* SWE swedish literals  - extlang */
/* #define III_THX                      /* THX thai EXTERNAL literals  - extlang */
/* #define III_FIN                      /* FIN finnish literals  - extlang */
/* #define III_GER                      /* GER german literals  - extlang */
/* #define III_VAL                      /* VAL valenciano literals - extlang */
/* #define III_VIE                      /* VIE vietnamese literals - extlang */
/* #define III_CAT                      /* CAT catalan literals - extlang */
/* #define III_BAQ                      /* BAQ basque literals - extlang */
/* #define III_ENX                      /* ENX external english literals - extlang */
/* #define III_WEX                      /* WEX external welsh literals - extlang */
/* #define III_CHT                      /* CHT traditional chinese literals - extlang */
/* #define III_ARA                      /* ARA arabic literals - extlang */
/* #define III_KOR                      /* KOR korean literals - extlang */
/* #define III_RUS                      /* RUS russian literals - extlang */
/* #define III_HEB                      /* HEB hebrew literals - extlang */
/* #define III_DUT                      /* DUT dutch literals - extlang */
/* #define III_MAY                      /* MAY malay (bahasa) literals - extlang */
/* #define III_MAO          /* MAO maori (New Zealand) literals - extlang */
/* #define III_SCO          /* SCO scottish gaelic  literals - extlang */
/* #define III_SOT          /* SOT sotho (South Africa) literals - extlang */
/* #define III_ZUL          /* ZUL zulu (South Africa) literals - extlang */
/* #define III_AFR          /* AFR afrikaans(South Africa) literals - extlang */
/* #define III_HMN          /* HMN hmong literals - extlang */
/* #define III_GRE          /* GRE greek literals - extlang */
/* #define III_NOR          /* NOR norwegian literals - extlang */
/* #define III_GEO          /* GEO georgian literals - extlang */
/* #define III_ICE                      /* ICE icelandic literals - extlang */
/* #define III_MULTILANG        /* all of the above */

/* programs/modules/functions include flag */ 
/* #define III_IRDCB        /* Site is INN-Reach DCB box */
/* #define III_OHIO_CENTRAL     /* OHIO Link central machine */
/* #define III_OHIO_CAMPUS      /* OHIO Link slave machine */
/* #define ILL_SYSTEM           /* Inter-Library Loan */
/* #define KWEXPAND             /* Expanded Keywords */
#define TARGET_EXPAND   /* Expand Search Target */
/* #define TOCHUU                       /* TOCHUU indexing */
#define MYSQLBUILD       /* MySQL server loaded */
/* #define NO_LIBNCFTP      /* do not compile ncftp with libraries */
/* #define INVMAX           /* Expanded Invoice Max */
/* #define HANGUL                       /* HANGUL (Korean) keyword indexing */
/* #define FBAL_EXPAND      /* Expand fbal/oldfbal fundname field to 160 bytes */
/* #define SKYRV                        /* Sky River machine */
#define SSCE_BUILD                      /* SSCE Spell Check Build */
/*lint -restore */

#ifdef III_MULTILANG
#       define III_AUS                  /* AUS australian literals */
#       define III_IRI                  /* IRI irish (gaelic) literals */
#       define III_POR                  /* POR portuguese literals */
#       define III_JPX                  /* JPX japanese literals */
#       define III_POL                  /* POL polish literals */
#       define III_GAG                  /* GAG galician literals */
#       define III_EST                  /* EST estonian literals */
#       define III_SPI                  /* SPI iberian spanish literals */
#       define III_FRC                  /* FRC canadian french EXTERNAL literals */
#       define III_FRF                  /* FRF french EXTERNAL literals */
#       define III_TUR                  /* TUR turkish literals */
#       define III_ITA                  /* ITA italian literals */
#       define III_CHX                  /* CHX chinese EXTERNAL literals */
#       define III_SWE                  /* SWE swedish literals  - extlang */
#       define III_THX                  /* THX thai EXTERNAL literals  - extlang */
#       define III_FIN                  /* FIN finnish literals  - extlang */
#       define III_GER                  /* GER german literals  - extlang */
#       define III_VAL                  /* VAL valenciano literals - extlang */
#       define III_VIE                  /* VIE vietnamese literals - extlang */
#       define III_CAT                  /* CAT catalan literals - extlang */
#       define III_BAQ                  /* BAQ basque literals - extlang */
#       define III_ENX                  /* ENX external english literals - extlang */
#       define III_WEX                  /* WEX external welsh literals - extlang */
#       define III_CHT                  /* CHT traditional chinese literals - extlang */
#       define III_ARA                  /* ARA arabic literals - extlang */
#       define III_KOR                  /* KOR korean literals - extlang */
#       define III_RUS                  /* RUS korean literals - extlang */
#       define III_HEB                  /* HEB korean literals - extlang */
#       define III_DUT                  /* DUT dutch literals - extlang */
#       define III_MAY                  /* MAY malay (bahasa) literals - extlang */
#       define III_MAO          /* MAO maori (New Zealand)  literals - extlang */
#       define III_SCO          /* SCO scottish gaelic  literals - extlang */
#       define III_SOT          /* SOT sotho (South Africa) literals - extlang */
#       define III_ZUL          /* ZUL zulu (South Africa) literals - extlang */
#       define III_AFR          /* AFR afrikaans(South Africa) literals - extlang */
#       define III_HMN          /* HMN hmong literals - extlang */
#       define III_GRE          /* GRE greek literals - extlang */
#       define III_NOR          /* NOR norwegian literals - extlang */
#       define III_GEO          /* GEO georgian literals - extlang */
#       define III_ICE                  /* ICE icelandic literals - extlang */
#       ifdef MAX_LANGUAGES
#               undef MAX_LANGUAGES
#       endif
#       define MAX_LANGUAGES 40 /* all of above plus one more for English */
#endif /* III_MULTILANG */

#define STORE_UNICODE  /* Store UNICODE instead of III braced form */
#define UNICODE_EXPAND /* Expanded field sizes for unicode sites */

/* #define SYMPOSIA_SYSTEM      /* This is a Symposia system */
/* #define HAS_HANDLE           /* The CNRI Handle Client Library is available */
#define MAX_LANGUAGES 1