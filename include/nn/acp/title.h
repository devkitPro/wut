#pragma once
#include <wut.h>
#include <nn/acp/result.h>
#include <nn/acp/device.h>

/**
 * \defgroup nn_acp_title Title
 * \ingroup nn_acp
 *
 * Information and control of installed title metadata
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef uint64_t ACPTitleId;
typedef struct ACPMetaXml ACPMetaXml;

struct WUT_PACKED ACPMetaXml {
    uint64_t title_id;
    uint64_t boss_id;
    uint64_t os_version;
    uint64_t app_size;
    uint64_t common_save_size;
    uint64_t account_save_size;
    uint64_t common_boss_size;
    uint64_t account_boss_size;
    uint64_t join_game_mode_mask;
    uint32_t version;
    char product_code[32];
    char content_platform[32];
    char company_code[8];
    char mastering_date[32];
    uint32_t logo_type;
    uint32_t app_launch_type;
    uint32_t invisible_flag;
    uint32_t no_managed_flag;
    uint32_t no_event_log;
    uint32_t no_icon_database;
    uint32_t launching_flag;
    uint32_t install_flag;
    uint32_t closing_msg;
    uint32_t title_version;
    uint32_t group_id;
    uint32_t save_no_rollback;
    uint32_t bg_daemon_enable;
    uint32_t join_game_id;
    uint32_t olv_accesskey;
    uint32_t wood_tin;
    uint32_t e_manual;
    uint32_t e_manual_version;
    uint32_t region;
    uint32_t pc_cero;
    uint32_t pc_esrb;
    uint32_t pc_bbfc;
    uint32_t pc_usk;
    uint32_t pc_pegi_gen;
    uint32_t pc_pegi_fin;
    uint32_t pc_pegi_prt;
    uint32_t pc_pegi_bbfc;
    uint32_t pc_cob;
    uint32_t pc_grb;
    uint32_t pc_cgsrr;
    uint32_t pc_oflc;
    uint32_t pc_reserved0;
    uint32_t pc_reserved1;
    uint32_t pc_reserved2;
    uint32_t pc_reserved3;
    uint32_t ext_dev_nunchaku;
    uint32_t ext_dev_classic;
    uint32_t ext_dev_urcc;
    uint32_t ext_dev_board;
    uint32_t ext_dev_usb_keyboard;
    uint32_t ext_dev_etc;
    char ext_dev_etc_name[512];
    uint32_t eula_version;
    uint32_t drc_use;
    uint32_t network_use;
    uint32_t online_account_use;
    uint32_t direct_boot;
    uint32_t reserved_flag0;
    uint32_t reserved_flag1;
    uint32_t reserved_flag2;
    uint32_t reserved_flag3;
    uint32_t reserved_flag4;
    uint32_t reserved_flag5;
    uint32_t reserved_flag6;
    uint32_t reserved_flag7;
    char longname_ja[512];
    char longname_en[512];
    char longname_fr[512];
    char longname_de[512];
    char longname_it[512];
    char longname_es[512];
    char longname_zhs[512];
    char longname_ko[512];
    char longname_nl[512];
    char longname_pt[512];
    char longname_ru[512];
    char longname_zht[512];
    char shortname_ja[256];
    char shortname_en[256];
    char shortname_fr[256];
    char shortname_de[256];
    char shortname_it[256];
    char shortname_es[256];
    char shortname_zhs[256];
    char shortname_ko[256];
    char shortname_nl[256];
    char shortname_pt[256];
    char shortname_ru[256];
    char shortname_zht[256];
    char publisher_ja[256];
    char publisher_en[256];
    char publisher_fr[256];
    char publisher_de[256];
    char publisher_it[256];
    char publisher_es[256];
    char publisher_zhs[256];
    char publisher_ko[256];
    char publisher_nl[256];
    char publisher_pt[256];
    char publisher_ru[256];
    char publisher_zht[256];
    uint32_t add_on_unique_id[32];
    WUT_UNKNOWN_BYTES(52);
};
WUT_CHECK_OFFSET(ACPMetaXml, 0x00, title_id);
WUT_CHECK_OFFSET(ACPMetaXml, 0x08, boss_id);
WUT_CHECK_OFFSET(ACPMetaXml, 0x10, os_version);
WUT_CHECK_OFFSET(ACPMetaXml, 0x18, app_size);
WUT_CHECK_OFFSET(ACPMetaXml, 0x20, common_save_size);
WUT_CHECK_OFFSET(ACPMetaXml, 0x28, account_save_size);
WUT_CHECK_OFFSET(ACPMetaXml, 0x30, common_boss_size);
WUT_CHECK_OFFSET(ACPMetaXml, 0x38, account_boss_size);
WUT_CHECK_OFFSET(ACPMetaXml, 0x40, join_game_mode_mask);
WUT_CHECK_OFFSET(ACPMetaXml, 0x48, version);
WUT_CHECK_OFFSET(ACPMetaXml, 0x4C, product_code);
WUT_CHECK_OFFSET(ACPMetaXml, 0x6C, content_platform);
WUT_CHECK_OFFSET(ACPMetaXml, 0x8C, company_code);
WUT_CHECK_OFFSET(ACPMetaXml, 0x94, mastering_date);
WUT_CHECK_OFFSET(ACPMetaXml, 0xB4, logo_type);
WUT_CHECK_OFFSET(ACPMetaXml, 0xB8, app_launch_type);
WUT_CHECK_OFFSET(ACPMetaXml, 0xBC, invisible_flag);
WUT_CHECK_OFFSET(ACPMetaXml, 0xC0, no_managed_flag);
WUT_CHECK_OFFSET(ACPMetaXml, 0xC4, no_event_log);
WUT_CHECK_OFFSET(ACPMetaXml, 0xC8, no_icon_database);
WUT_CHECK_OFFSET(ACPMetaXml, 0xCC, launching_flag);
WUT_CHECK_OFFSET(ACPMetaXml, 0xD0, install_flag);
WUT_CHECK_OFFSET(ACPMetaXml, 0xD4, closing_msg);
WUT_CHECK_OFFSET(ACPMetaXml, 0xD8, title_version);
WUT_CHECK_OFFSET(ACPMetaXml, 0xDC, group_id);
WUT_CHECK_OFFSET(ACPMetaXml, 0xE0, save_no_rollback);
WUT_CHECK_OFFSET(ACPMetaXml, 0xE4, bg_daemon_enable);
WUT_CHECK_OFFSET(ACPMetaXml, 0xE8, join_game_id);
WUT_CHECK_OFFSET(ACPMetaXml, 0xEC, olv_accesskey);
WUT_CHECK_OFFSET(ACPMetaXml, 0xF0, wood_tin);
WUT_CHECK_OFFSET(ACPMetaXml, 0xF4, e_manual);
WUT_CHECK_OFFSET(ACPMetaXml, 0xF8, e_manual_version);
WUT_CHECK_OFFSET(ACPMetaXml, 0xFC, region);
WUT_CHECK_OFFSET(ACPMetaXml, 0x100, pc_cero);
WUT_CHECK_OFFSET(ACPMetaXml, 0x104, pc_esrb);
WUT_CHECK_OFFSET(ACPMetaXml, 0x108, pc_bbfc);
WUT_CHECK_OFFSET(ACPMetaXml, 0x10C, pc_usk);
WUT_CHECK_OFFSET(ACPMetaXml, 0x110, pc_pegi_gen);
WUT_CHECK_OFFSET(ACPMetaXml, 0x114, pc_pegi_fin);
WUT_CHECK_OFFSET(ACPMetaXml, 0x118, pc_pegi_prt);
WUT_CHECK_OFFSET(ACPMetaXml, 0x11C, pc_pegi_bbfc);
WUT_CHECK_OFFSET(ACPMetaXml, 0x120, pc_cob);
WUT_CHECK_OFFSET(ACPMetaXml, 0x124, pc_grb);
WUT_CHECK_OFFSET(ACPMetaXml, 0x128, pc_cgsrr);
WUT_CHECK_OFFSET(ACPMetaXml, 0x12C, pc_oflc);
WUT_CHECK_OFFSET(ACPMetaXml, 0x130, pc_reserved0);
WUT_CHECK_OFFSET(ACPMetaXml, 0x134, pc_reserved1);
WUT_CHECK_OFFSET(ACPMetaXml, 0x138, pc_reserved2);
WUT_CHECK_OFFSET(ACPMetaXml, 0x13C, pc_reserved3);
WUT_CHECK_OFFSET(ACPMetaXml, 0x140, ext_dev_nunchaku);
WUT_CHECK_OFFSET(ACPMetaXml, 0x144, ext_dev_classic);
WUT_CHECK_OFFSET(ACPMetaXml, 0x148, ext_dev_urcc);
WUT_CHECK_OFFSET(ACPMetaXml, 0x14C, ext_dev_board);
WUT_CHECK_OFFSET(ACPMetaXml, 0x150, ext_dev_usb_keyboard);
WUT_CHECK_OFFSET(ACPMetaXml, 0x154, ext_dev_etc);
WUT_CHECK_OFFSET(ACPMetaXml, 0x158, ext_dev_etc_name);
WUT_CHECK_OFFSET(ACPMetaXml, 0x358, eula_version);
WUT_CHECK_OFFSET(ACPMetaXml, 0x35C, drc_use);
WUT_CHECK_OFFSET(ACPMetaXml, 0x360, network_use);
WUT_CHECK_OFFSET(ACPMetaXml, 0x364, online_account_use);
WUT_CHECK_OFFSET(ACPMetaXml, 0x368, direct_boot);
WUT_CHECK_OFFSET(ACPMetaXml, 0x36C, reserved_flag0);
WUT_CHECK_OFFSET(ACPMetaXml, 0x370, reserved_flag1);
WUT_CHECK_OFFSET(ACPMetaXml, 0x374, reserved_flag2);
WUT_CHECK_OFFSET(ACPMetaXml, 0x378, reserved_flag3);
WUT_CHECK_OFFSET(ACPMetaXml, 0x37C, reserved_flag4);
WUT_CHECK_OFFSET(ACPMetaXml, 0x380, reserved_flag5);
WUT_CHECK_OFFSET(ACPMetaXml, 0x384, reserved_flag6);
WUT_CHECK_OFFSET(ACPMetaXml, 0x388, reserved_flag7);
WUT_CHECK_OFFSET(ACPMetaXml, 0x38C, longname_ja);
WUT_CHECK_OFFSET(ACPMetaXml, 0x58C, longname_en);
WUT_CHECK_OFFSET(ACPMetaXml, 0x78C, longname_fr);
WUT_CHECK_OFFSET(ACPMetaXml, 0x98C, longname_de);
WUT_CHECK_OFFSET(ACPMetaXml, 0xB8C, longname_it);
WUT_CHECK_OFFSET(ACPMetaXml, 0xD8C, longname_es);
WUT_CHECK_OFFSET(ACPMetaXml, 0xF8C, longname_zhs);
WUT_CHECK_OFFSET(ACPMetaXml, 0x118C, longname_ko);
WUT_CHECK_OFFSET(ACPMetaXml, 0x138C, longname_nl);
WUT_CHECK_OFFSET(ACPMetaXml, 0x158C, longname_pt);
WUT_CHECK_OFFSET(ACPMetaXml, 0x178C, longname_ru);
WUT_CHECK_OFFSET(ACPMetaXml, 0x198C, longname_zht);
WUT_CHECK_OFFSET(ACPMetaXml, 0x1B8C, shortname_ja);
WUT_CHECK_OFFSET(ACPMetaXml, 0x1C8C, shortname_en);
WUT_CHECK_OFFSET(ACPMetaXml, 0x1D8C, shortname_fr);
WUT_CHECK_OFFSET(ACPMetaXml, 0x1E8C, shortname_de);
WUT_CHECK_OFFSET(ACPMetaXml, 0x1F8C, shortname_it);
WUT_CHECK_OFFSET(ACPMetaXml, 0x208C, shortname_es);
WUT_CHECK_OFFSET(ACPMetaXml, 0x218C, shortname_zhs);
WUT_CHECK_OFFSET(ACPMetaXml, 0x228C, shortname_ko);
WUT_CHECK_OFFSET(ACPMetaXml, 0x238C, shortname_nl);
WUT_CHECK_OFFSET(ACPMetaXml, 0x248C, shortname_pt);
WUT_CHECK_OFFSET(ACPMetaXml, 0x258C, shortname_ru);
WUT_CHECK_OFFSET(ACPMetaXml, 0x268C, shortname_zht);
WUT_CHECK_OFFSET(ACPMetaXml, 0x278C, publisher_ja);
WUT_CHECK_OFFSET(ACPMetaXml, 0x288C, publisher_en);
WUT_CHECK_OFFSET(ACPMetaXml, 0x298C, publisher_fr);
WUT_CHECK_OFFSET(ACPMetaXml, 0x2A8C, publisher_de);
WUT_CHECK_OFFSET(ACPMetaXml, 0x2B8C, publisher_it);
WUT_CHECK_OFFSET(ACPMetaXml, 0x2C8C, publisher_es);
WUT_CHECK_OFFSET(ACPMetaXml, 0x2D8C, publisher_zhs);
WUT_CHECK_OFFSET(ACPMetaXml, 0x2E8C, publisher_ko);
WUT_CHECK_OFFSET(ACPMetaXml, 0x2F8C, publisher_nl);
WUT_CHECK_OFFSET(ACPMetaXml, 0x308C, publisher_pt);
WUT_CHECK_OFFSET(ACPMetaXml, 0x318C, publisher_ru);
WUT_CHECK_OFFSET(ACPMetaXml, 0x328C, publisher_zht);
WUT_CHECK_OFFSET(ACPMetaXml, 0x338C, add_on_unique_id);
WUT_CHECK_SIZE(ACPMetaXml,0x3440);

ACPResult
ACPGetTitleIdOfMainApplication(ACPTitleId* titleId);

ACPResult
ACPGetTitleMetaXml(ACPTitleId titleId,
                   ACPMetaXml* metaXml);

ACPResult
ACPGetTitleMetaDirByDevice(ACPTitleId titleId,
                           char* directory,
                           size_t directoryLen,
                           ACPDeviceType deviceType);

#ifdef __cplusplus
}
#endif

/** @} */
