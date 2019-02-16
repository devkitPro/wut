#pragma once
#include <wut.h>

/**
 * \defgroup nn_result Result
 * \ingroup nn
 * Result structure used by nn libraries (C++: see nn::Result)
 * @{
 */

typedef struct NNResult NNResult;

/**
 * Result structure for nn libraries
 * <!--
 *    TODO: the actual bitfield stuff?
 * -->
 */
struct NNResult
{
   //! Aggregate value of result bitfield
   int32_t value;
};

/**
 * Determine if a NNResult represents a successful state.
 *
 * \param result
 * The NNResult to check.
 *
 * \return
 * \c 1 if the NNResult represents a success, or \c 0 otherwise.
 *
 * \sa
 * - \link NNResult_IsFailure \endlink
 */
static inline int NNResult_IsSuccess(NNResult result)
{
   return result.value >= 0;
}

/**
 * Determine if a NNResult represents a failure.
 *
 * \param result
 * The NNResult to check.
 *
 * \return
 * \c 1 if the NNResult represents a failure, or \c 0 otherwise.
 *
 * \sa
 * - \link NNResult_IsSuccess \endlink
 */
static inline int NNResult_IsFailure(NNResult result)
{
   return result.value < 0;
}

#ifdef __cplusplus

namespace nn
{

/**
 * Result value type used by nn libraries.
 */
class Result
{
public:
   enum Level
   {
      LEVEL_SUCCESS                       = 0,
      LEVEL_FATAL                         = -1,
      LEVEL_USAGE                         = -2,
      LEVEL_STATUS                        = -3,
      LEVEL_END                           = -7,
   };

   enum LegacyLevel
   {
      LEVEL_INFO                          = 1,
      LEVEL_RESET                         = -4,
      LEVEL_REINIT                        = -5,
      LEVEL_PERMANENT                     = -6,
      LEVEL_TEMPORARY                     = -7,
   };

   enum Module
   {
      RESULT_MODULE_COMMON                = 0,
      RESULT_MODULE_NN_IPC                = 1,
      RESULT_MODULE_NN_BOSS               = 2,
      RESULT_MODULE_NN_ACP                = 3,
      RESULT_MODULE_NN_IOS                = 4,
      RESULT_MODULE_NN_NIM                = 5,
      RESULT_MODULE_NN_PDM                = 6,
      RESULT_MODULE_NN_ACT                = 7,
      RESULT_MODULE_NN_NGC                = 8,
      RESULT_MODULE_NN_ECA                = 9,
      RESULT_MODULE_NN_NUP                = 10,
      RESULT_MODULE_NN_NDM                = 11,
      RESULT_MODULE_NN_FP                 = 12,
      RESULT_MODULE_NN_AC                 = 13,
      RESULT_MODULE_NN_CONNTEST           = 14,
      RESULT_MODULE_NN_DRMAPP             = 15,
      RESULT_MODULE_NN_TELNET             = 16,
      RESULT_MODULE_NN_OLV                = 17,
      RESULT_MODULE_NN_VCTL               = 18,
      RESULT_MODULE_NN_NEIA               = 19,
      RESULT_MODULE_NN_SPM                = 20,
      RESULT_MODULE_NN_TEST               = 125,
   };

   enum LegacyModule
   {
      MODULE_COMMON                       = 0,
      MODULE_NN_KERNEL                    = 1,
      MODULE_NN_UTIL                      = 2,
      MODULE_NN_FILE_SERVER               = 3,
      MODULE_NN_LOADER_SERVER             = 4,
      MODULE_NN_TCB                       = 5,
      MODULE_NN_OS                        = 6,
      MODULE_NN_DBG                       = 7,
      MODULE_NN_DMNT                      = 8,
      MODULE_NN_PDN                       = 9,
      MODULE_NN_GX                        = 0xA,
      MODULE_NN_I2C                       = 0xB,
      MODULE_NN_GPIO                      = 0xC,
      MODULE_NN_DD                        = 0xD,
      MODULE_NN_CODEC                     = 0xE,
      MODULE_NN_SPI                       = 0xF,
      MODULE_NN_PXI                       = 0x10,
      MODULE_NN_FS                        = 0x11,
      MODULE_NN_DI                        = 0x12,
      MODULE_NN_HID                       = 0x13,
      MODULE_NN_CAMERA                    = 0x14,
      MODULE_NN_PI                        = 0x15,
      MODULE_NN_PM                        = 0x16,
      MODULE_NN_PMLOW                     = 0x17,
      MODULE_NN_FSI                       = 0x18,
      MODULE_NN_SRV                       = 0x19,
      MODULE_NN_NDM                       = 0x1A,
      MODULE_NN_NWM                       = 0x1B,
      MODULE_NN_SOCKET                    = 0x1C,
      MODULE_NN_LDR                       = 0x1D,
      MODULE_NN_ACC                       = 0x1E,
      MODULE_NN_ROMFS                     = 0x1F,
      MODULE_NN_AM                        = 0x20,
      MODULE_NN_HIO                       = 0x21,
      MODULE_NN_UPDATER                   = 0x22,
      MODULE_NN_MIC                       = 0x23,
      MODULE_NN_FND                       = 0x24,
      MODULE_NN_MP                        = 0x25,
      MODULE_NN_MPWL                      = 0x26,
      MODULE_NN_AC                        = 0x27,
      MODULE_NN_HTTP                      = 0x28,
      MODULE_NN_DSP                       = 0x29,
      MODULE_NN_SND                       = 0x2A,
      MODULE_NN_DLP                       = 0x2B,
      MODULE_NN_HIOLOW                    = 0x2C,
      MODULE_NN_CSND                      = 0x2D,
      MODULE_NN_SSL                       = 0x2E,
      MODULE_NN_AMLOW                     = 0x2F,
      MODULE_NN_NEX                       = 0x30,
      MODULE_NN_FRIENDS                   = 0x31,
      MODULE_NN_RDT                       = 0x32,
      MODULE_NN_APPLET                    = 0x33,
      MODULE_NN_NIM                       = 0x34,
      MODULE_NN_PTM                       = 0x35,
      MODULE_NN_MIDI                      = 0x36,
      MODULE_NN_MC                        = 0x37,
      MODULE_NN_SWC                       = 0x38,
      MODULE_NN_FATFS                     = 0x39,
      MODULE_NN_NGC                       = 0x3A,
      MODULE_NN_CARD                      = 0x3B,
      MODULE_NN_CARDNOR                   = 0x3C,
      MODULE_NN_SDMC                      = 0x3D,
      MODULE_NN_BOSS                      = 0x3E,
      MODULE_NN_DBM                       = 0x3F,
      MODULE_NN_CFG                       = 0x40,
      MODULE_NN_PS                        = 0x41,
      MODULE_NN_CEC                       = 0x42,
      MODULE_NN_IR                        = 0x43,
      MODULE_NN_UDS                       = 0x44,
      MODULE_NN_PL                        = 0x45,
      MODULE_NN_CUP                       = 0x46,
      MODULE_NN_GYROSCOPE                 = 0x47,
      MODULE_NN_MCU                       = 0x48,
      MODULE_NN_NS                        = 0x49,
      MODULE_NN_NEWS                      = 0x4A,
      MODULE_NN_RO                        = 0x4B,
      MODULE_NN_GD                        = 0x4C,
      MODULE_NN_CARDSPI                   = 0x4D,
      MODULE_NN_EC                        = 0x4E,
      MODULE_NN_WEBBRS                    = 0x4F,
      MODULE_NN_TEST                      = 0x50,
      MODULE_NN_ENC                       = 0x51,
      MODULE_NN_PIA                       = 0x52,
      MODULE_APPLICATION                  = 0x1FE,
   };

   enum LegacySummary
   {
      SUMMARY_SUCCESS                     = 0,
      SUMMARY_NOTHING_HAPPENED            = 1,
      SUMMARY_WOULD_BLOCK                 = 2,
      SUMMARY_OUT_OF_RESOURCE             = 3,
      SUMMARY_NOT_FOUND                   = 4,
      SUMMARY_INVALID_STATE               = 5,
      SUMMARY_NOT_SUPPORTED               = 6,
      SUMMARY_INVALID_ARGUMENT            = 7,
      SUMMARY_WRONG_ARGUMENT              = 8,
      SUMMARY_CANCELLED                   = 9,
      SUMMARY_STATUS_CHANGED              = 10,
      SUMMARY_INTERNAL                    = 11,
   };

   enum LegacySignature
   {
      SIGNATURE_IS_LEGACY                 = 3,
   };

public:
   Result(Level level, Module module, unsigned description) :
      mDescription(description),
      mModule(module),
      mLevel(level)
   {
   }

   Result(const NNResult &result) :
      mValue(result.value)
   {
   }

   /**
    * Determine if the Result instance represents a failure.
    *
    * \return
    * \c trie if the Result represents a failure, or \c false otherwise.
    *
    * \sa
    * - \link IsSuccess \endlink
    */
   bool IsFailure() const
   {
      return !IsSuccess();
   }

   /**
    * Determine if the Result instance represents a successful state.
    *
    * \return
    * \c true if the Result represents a success, or \c false otherwise.
    *
    * \sa
    * - \link IsFailure \endlink
    */
   bool IsSuccess() const
   {
      return mLevel >= 0;
   }

   bool IsLegacy() const
   {
      return mLegacy.signature == SIGNATURE_IS_LEGACY;
   }

   unsigned GetDescription() const
   {
      if (IsLegacy()) {
         return mLegacy.description;
      }

      return mDescription;
   }

   int GetLevel() const
   {
      if (IsLegacy()) {
         return mLegacy.level;
      }

      return mLevel;
   }

   unsigned GetModule() const
   {
      if (IsLegacy()) {
         return mLegacy.module;
      }

      return mModule;
   }

   unsigned GetSummary() const
   {
      if (IsLegacy()) {
         return mLegacy.summary;
      }

      return 0;
   }

   operator bool() const
   {
      return IsSuccess();
   }

   operator NNResult() const
   {
      NNResult result;
      result.value = mValue;
      return result;
   }

   bool operator==(const Result &other) const
   {
      return mValue == other.mValue;
   }

   bool operator!=(const Result &other) const
   {
      return mValue != other.mValue;
   }

private:
   union {
      struct {
         uint32_t description : 10;
         uint32_t summary : 4;
         int32_t level : 4;
         uint32_t : 2;
         uint32_t module : 7;
         uint32_t signature : 2;
      } mLegacy;

      struct {
         uint32_t mDescription : 20;
         uint32_t mModule : 9;
         int32_t mLevel : 3;
      };

      int32_t mValue;
   };
};

} // namespace nn

#endif // ifdef __cplusplus

/** @} */
