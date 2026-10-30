#pragma once
#include <wut.h>
#include <nn/result.h>

/**
 * \defgroup nn_nim_cpp Title Package API
 * \ingroup nn_nim
 * Hands titles to the system downloader (see nn::nim).
 *
 * A title package task registered here is downloaded and installed by the
 * system itself, in the background, and is listed in the Download Management.
 * With the standby functions of the console enabled it also runs while the
 * console is switched off. This is the downloader the eShop handed its
 * purchases to.
 *
 * The layouts come from Cemu and from testing on a 5.5.5E console. Fields
 * named here were observed to behave as documented on that console, or are
 * marked as coming from Cemu; everything else is left as unknown bytes.
 * @{
 */

#ifdef __cplusplus

namespace nn
{

namespace nim
{

//! A title package task, see \link RegisterTitlePackageTask \endlink.
struct WUT_PACKED TitlePackageTaskConfig
{
   //! Title ID of the title to download.
   uint64_t titleId;
   //! Version of the title to download.
   //! Cemu calls this word region or language related, but the system builds
   //! the path of the TMD from it: 0 makes it request tmd.0, which fails with
   //! 105-0955 for a title that has no version 0.
   uint32_t titleVersion;
   //! Type of the title, a value of nn::Cafe::TitleType.
   //! The values are undocumented. Seen on a 5.5.5E console:
   //! - 0: application. Works for a game, and a demo installs as a demo
   //!   with it.
   //! - 1: update, carried by an update package the system registered on its
   //!   own. Cemu also marks 1 as an update.
   //! - 2: additional content. A demo registered with 2 was listed as
   //!   additional content and installed without an entry on the Wii U Menu.
   //!
   //! This is not the category byte of the title ID: 0x0C and 0x0E are
   //! accepted, but left the Download Management blank.
   uint8_t titleType;
   //! Device to install to. 1 installs to the internal memory. An update the
   //! system registered on its own, for a game stored on a USB drive,
   //! carried 2 here and in \link applicationBoxDevice2 \endlink.
   uint8_t applicationBoxDevice1;
   WUT_UNKNOWN_BYTES(1);
   //! Device to install to, set like \link applicationBoxDevice1 \endlink.
   uint8_t applicationBoxDevice2;
   WUT_UNKNOWN_BYTES(5);
   //! Unknown. Cemu sets it to 1, and so did every config tested on hardware.
   uint8_t unk_0x15;
   //! What happens once the download is complete.
   //! - 1: the title is installed right away, the way the eShop installs a purchase.
   //! - 2: background install policy. The install waits for the next start of
   //!   the title, which a title that is not installed yet cannot have.
   //!
   //! 0 has not been observed.
   uint8_t postDownloadAction;
   WUT_UNKNOWN_BYTES(1);
};
WUT_CHECK_OFFSET(TitlePackageTaskConfig, 0x00, titleId);
WUT_CHECK_OFFSET(TitlePackageTaskConfig, 0x08, titleVersion);
WUT_CHECK_OFFSET(TitlePackageTaskConfig, 0x0C, titleType);
WUT_CHECK_OFFSET(TitlePackageTaskConfig, 0x0D, applicationBoxDevice1);
WUT_CHECK_OFFSET(TitlePackageTaskConfig, 0x0F, applicationBoxDevice2);
WUT_CHECK_OFFSET(TitlePackageTaskConfig, 0x15, unk_0x15);
WUT_CHECK_OFFSET(TitlePackageTaskConfig, 0x16, postDownloadAction);
WUT_CHECK_SIZE(TitlePackageTaskConfig, 0x18);

//! State of a title package, see \link GetTitlePackageInfos \endlink.
struct WUT_PACKED TitlePackageInfo
{
   //! The config the package was registered with. For a package registered
   //! with \link RegisterTitlePackageTask \endlink these bytes equal the
   //! config that was passed in.
   TitlePackageTaskConfig config;
   // On a 5.5.5E console 0x18 to 0x3F held three pairs of equal values for
   // a finished download: two 64-bit byte counts matching the download size
   // at 0x18 and 0x20, two smaller 64-bit byte counts at 0x28 and 0x30, and
   // two 32-bit counts at 0x38 and 0x3C (7 and 7 for a DLC with 7
   // contents). Cemu reads 0x28 to 0x3F as download progress. Which value
   // of a pair is the total and which the progress is not established.
   WUT_UNKNOWN_BYTES(0x28);
   // Cemu writes a result-like value at 0x40. Not verified on hardware.
   WUT_UNKNOWN_BYTES(0x08);
   //! State of the package. According to Cemu, values 0 to 7 are allowed,
   //! 0 shows no progress bar and 3 shows one. A finished download waiting
   //! to be installed read 5 on a 5.5.5E console.
   uint8_t state;
   WUT_UNKNOWN_BYTES(0x07);
};
WUT_CHECK_OFFSET(TitlePackageInfo, 0x00, config);
WUT_CHECK_OFFSET(TitlePackageInfo, 0x48, state);
WUT_CHECK_SIZE(TitlePackageInfo, 0x50);

/**
 * Initializes nn_nim. Call it before any other function here.
 */
nn::Result
Initialize()
   asm("Initialize__Q2_2nn3nimFv");

/**
 * Finalizes nn_nim.
 */
nn::Result
Finalize()
   asm("Finalize__Q2_2nn3nimFv");

/**
 * Registers a title package task. The system downloads the title and, as
 * \link TitlePackageTaskConfig::postDownloadAction \endlink says, installs it.
 *
 * Before it takes the task the system fetches the icon of the title from
 * idbe-wup.cdn.nintendo.net, and a failure there refuses the task with
 * 105-1017. It installs with the ticket that is on the console, so a title
 * without one is downloaded and then fails to install with 105-3683.
 *
 * \param config
 * The task to register.
 *
 * \param contents
 * Indices of the contents to download, or \c nullptr to let the system pick
 * them. A list of every content of the TMD was refused as a usage error
 * (0xC0512E80) on a 5.5.5E console, while \c nullptr was accepted.
 *
 * \param numContents
 * Number of entries in \p contents.
 */
nn::Result
RegisterTitlePackageTask(const TitlePackageTaskConfig &config,
                         const uint16_t *contents,
                         uint32_t numContents)
   asm("RegisterTitlePackageTask__Q2_2nn3nimFRCQ3_2nn3nim22TitlePackageTaskConfigPCUsUi");

/**
 * Removes a title package, along with what it downloaded so far.
 *
 * \param packageId
 * ID of the package as \link ListTitlePackagesStatically \endlink returns it.
 * This is not the title ID: the title ID was refused with 105-0259
 * (TITLE_PACKAGE_NOT_FOUND) on a console that listed the package of that very
 * title as 0x1F.
 */
nn::Result
UnregisterTitlePackageTask(uint64_t packageId)
   asm("UnregisterTitlePackageTask__Q2_2nn3nimFUL");

/**
 * Gets the number of title packages the system holds, those of the eShop
 * included.
 */
uint32_t
GetNumTitlePackages()
   asm("GetNumTitlePackages__Q2_2nn3nimFv");

/**
 * Lists the title packages the system holds.
 *
 * \param outPackageIds
 * Receives the IDs of the packages. These are package IDs, not title IDs;
 * \link GetTitlePackageInfos \endlink turns them into title IDs.
 *
 * \param maxCount
 * Number of entries \p outPackageIds has room for.
 */
nn::Result
ListTitlePackagesStatically(uint64_t *outPackageIds,
                            uint32_t maxCount)
   asm("ListTitlePackagesStatically__Q2_2nn3nimFPULUi");

/**
 * Reads the state of title packages.
 *
 * \param outInfos
 * Receives one \link TitlePackageInfo \endlink per entry of \p packageIds.
 *
 * \param packageIds
 * IDs as \link ListTitlePackagesStatically \endlink returns them.
 *
 * \param count
 * Number of entries in \p packageIds.
 */
nn::Result
GetTitlePackageInfos(TitlePackageInfo *outInfos,
                     const uint64_t *packageIds,
                     uint32_t count)
   asm("GetTitlePackageInfos__Q2_2nn3nimFPQ3_2nn3nim16TitlePackageInfoPCULUi");

} // namespace nim

} // namespace nn

#endif

/** @} */
