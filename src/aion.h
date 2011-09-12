#ifndef AION_H_INCLUDED
#define AION_H_INCLUDED

#include "chatlog.h"

#define AION_NAME_DEFAULT   "You"
#define AION_CHAT_SZ        CHATLOG_CHAT_SZ
#define AION_NAME_SZ        CHATLOG_NAME_SZ

#define AION_SYSOVR_FILE    "system.ovr"
#define AION_SYSOVR_CHATLOG "g_chatlog"

extern bool aion_init(void);
extern bool aion_player_is_self(char *charname);

extern bool aion_group_join(char *charname);
extern bool aion_group_leave(char *charname);
extern void aion_group_disband(void);
extern void aion_group_loot(char *charname, uint32_t itemid);

extern void aion_apvalue_reset(void);
extern bool aion_group_apvalue_update(char *charname, uint32_t apval);
extern bool aion_group_apvalue_set(char *charname, uint32_t apval);
extern uint32_t aion_group_get_apvalue_lowest(void);

extern bool aion_group_invfull_set(char *charname, bool isfull);
extern bool aion_group_invfull_get(char *charname);

extern bool aion_player_chat_cache(char *charname, char *chat);
extern bool aion_player_chat_get(char *charname, int msgnum, char *dst, size_t dst_sz);
extern void aion_player_name_set(char *charname);

/* The group iterator */
struct aion_group_iter
{
    char                *agi_name;
    uint32_t            agi_apvalue;
    bool                agi_invfull;

    struct aion_player  *__agi_curplayer;
};

extern void aion_group_first(struct aion_group_iter *iter);
extern void aion_group_next(struct aion_group_iter *iter);
extern bool aion_group_end(struct aion_group_iter *iter);

#define LANG_ELYOS      1
#define LANG_ASMODIAN   2
#define LANG_KRALL      3
#define LANG_MAU        4
#define LANG_BALAUR     5

extern void aion_translate(char *txt, uint32_t language);
extern void aion_rtranslate(char *txt, uint32_t language);

extern bool aion_group_get_stats(char *stats, size_t stats_sz);
extern bool aion_group_get_aplootrights(char *stats, size_t stats_sz);

extern char* aion_default_install_path(void);
extern bool aion_chatlog_is_enabled(bool *isenabled);
extern bool aion_chatlog_enable(void);

#endif /* AION_H_INCLUDED */
