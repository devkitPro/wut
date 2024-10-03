#pragma once
#include <wut.h>
#include <nn/nfp/nfp_cpp.h>
#include <sysapp/args.h>

/**
 * \defgroup nn_nfp Amiibo Settings
 * \ingroup nn_nfp
 * Amiibo Settings applet related functionality (see nn::nfp)
 * @{
 */

#ifdef __cplusplus

namespace nn
{

namespace nfp
{

enum class AmiiboSettingsMode : uint32_t
{
   //! Open the Mii and Name register menu
   Register       = 0,
   //! Open the "Delete Game Data" menu
   DeleteGameData = 1,
   //! Open the "Restore" menu
   Restore        = 2,
};
WUT_CHECK_SIZE(AmiiboSettingsMode, 0x4);

struct AmiiboSettingsArgsIn
{
   //! The mode in which the amiibo settings should be opened
   AmiiboSettingsMode mode;
   TagInfo tag_info;
   //! Set to \c true if the tag is already registered
   bool is_registered;
   //! padding bytes, must be set to 0
   uint8_t padding[3];
   RegisterInfo register_info;
   CommonInfo common_info;
   //! reserved bytes, must be set to 0
   uint8_t reserved[0x20];
};
WUT_CHECK_OFFSET(AmiiboSettingsArgsIn, 0x0, mode);
WUT_CHECK_OFFSET(AmiiboSettingsArgsIn, 0x4, tag_info);
WUT_CHECK_OFFSET(AmiiboSettingsArgsIn, 0x58, is_registered);
WUT_CHECK_OFFSET(AmiiboSettingsArgsIn, 0x59, padding);
WUT_CHECK_OFFSET(AmiiboSettingsArgsIn, 0x5C, register_info);
WUT_CHECK_OFFSET(AmiiboSettingsArgsIn, 0x104, common_info);
WUT_CHECK_OFFSET(AmiiboSettingsArgsIn, 0x144, reserved);
WUT_CHECK_SIZE(AmiiboSettingsArgsIn, 0x164);

struct AmiiboSettingsArgs
{
   SYSStandardArgs standardArgs;
   AmiiboSettingsArgsIn argsIn;
};
WUT_CHECK_OFFSET(AmiiboSettingsArgs, 0x0, standardArgs);
WUT_CHECK_OFFSET(AmiiboSettingsArgs, 0x10, argsIn);
WUT_CHECK_SIZE(AmiiboSettingsArgs, 0x174);

struct AmiiboSettingsResult
{
   //! Result (0 on success)
   int32_t result;
   TagInfo tag_info;
   RegisterInfo register_info;
   CommonInfo common_info;
   //! reserved bytes
   uint8_t reserved[0x20];
};
WUT_CHECK_OFFSET(AmiiboSettingsResult, 0x0, result);
WUT_CHECK_OFFSET(AmiiboSettingsResult, 0x4, tag_info);
WUT_CHECK_OFFSET(AmiiboSettingsResult, 0x58, register_info);
WUT_CHECK_OFFSET(AmiiboSettingsResult, 0x100, common_info);
WUT_CHECK_OFFSET(AmiiboSettingsResult, 0x140, reserved);
WUT_CHECK_SIZE(AmiiboSettingsResult, 0x160);

/**
 * Initializes a \c AmiiboSettingsArgsIn struct.
 * 
 * \param args
 * The args which should be initialized.
 */
nn::Result
InitializeAmiiboSettingsArgsIn(AmiiboSettingsArgsIn *args)
   asm("InitializeAmiiboSettingsArgsIn__Q2_2nn3nfpFPQ3_2nn3nfp20AmiiboSettingsArgsIn");

/**
 * Switches to the amiibo settings applet.
 * 
 * \param args
 * The args passed to the amiibo settings.
 * 
 * \param standardArg
 * Optional standard args which will be serialized.
 * 
 * \param standardArgSize
 * The size of the standard args.
 */
nn::Result
SwitchToAmiiboSettings(const AmiiboSettingsArgsIn &args, const char *standardArg, uint32_t standardArgSize)
   asm("SwitchToAmiiboSettings__Q2_2nn3nfpFRCQ3_2nn3nfp20AmiiboSettingsArgsInPCcUi");

/**
 * Switches to the amiibo settings applet.
 * 
 * \param args
 * The args passed to the amiibo settings.
 */
nn::Result
SwitchToAmiiboSettings(const AmiiboSettingsArgsIn &args)
   asm("SwitchToAmiiboSettings__Q2_2nn3nfpFRCQ3_2nn3nfp20AmiiboSettingsArgsIn");

/**
 * Gets the amiibo settings result from a SYSArgs data block.
 * 
 * \param outResult
 * A pointer to which the result should be written to.
 * 
 * \param block
 * An argument data block read from \link SYSGetArguments \endlink with \link SYS_ARG_ID_RESULT \endlink.
 */
nn::Result
GetAmiiboSettingsResult(AmiiboSettingsResult *outResult, const SYSArgDataBlock &block)
   asm("GetAmiiboSettingsResult__Q2_2nn3nfpFPQ3_2nn3nfp20AmiiboSettingsResultRC15SysArgDataBlock");

/**
 * Used by Amiibo Settings internally to return to the caller.
 * 
 * \param result
 * The result which will be passed to the arguments.
 */
nn::Result
ReturnToCallerWithAmiiboSettingsResult(const AmiiboSettingsResult &result)
   asm("ReturnToCallerWithAmiiboSettingsResult__Q2_2nn3nfpFRCQ3_2nn3nfp20AmiiboSettingsResult");

/**
 * Used by Amiibo Settings internally to get the arguments of the caller.
 * 
 * \param outArgs
 * A pointer to which the arguments will be written to.
 */
nn::Result
GetAmiiboSettingsArgs(AmiiboSettingsArgs *outArgs)
   asm("GetAmiiboSettingsArgs__Q2_2nn3nfpFPQ3_2nn3nfp18AmiiboSettingsArgs");

} //namespace nfp

} //namespace nn

#endif

/** @} */
