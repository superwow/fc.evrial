/*
 * Copyright (C) 2010-2012 OregonCore <http://www.oregoncore.com/>
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2012 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Common.h"
#include "Database/DatabaseEnv.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "World.h"
#include "Player.h"
#include "Opcodes.h"
#include "Chat.h"
#include "MapManager.h"
#include "ObjectAccessor.h"
#include "Language.h"
#include "AccountMgr.h"
#include "SystemConfig.h"
#include "revision.h"
#include "Util.h"

bool ChatHandler::HandleHelpCommand(const char* args)
{
    char* cmd = strtok((char*)args, " ");
    if (!cmd)
    {
        ShowHelpForCommand(getCommandTable(), "help");
        ShowHelpForCommand(getCommandTable(), "");
    }
    else
    {
        if (!ShowHelpForCommand(getCommandTable(), cmd))
            SendSysMessage(LANG_NO_HELP_CMD);
    }

    return true;
}

bool ChatHandler::HandleCommandsCommand(const char* args)
{
    ShowHelpForCommand(getCommandTable(), "");
    return true;
}

bool ChatHandler::HandleAccountCommand(const char* /*args*/)
{
    uint32 gmlevel = m_session->GetSecurity();
    PSendSysMessage(LANG_ACCOUNT_LEVEL, gmlevel);
    return true;
}

bool ChatHandler::HandleVipCommand(const char* /*args*/)
{
	Player *player = m_session->GetPlayer();
	uint32 player_id = player->GetGUIDLow();
	if (player->isVip())
	{
		PSendSysMessage("Your VIP status is Confirmed in session! All is OK!");
		//PSendSysMessage("Configs:");
	}
	else
	{
		PSendSysMessage("Your VIP status is NOT Confirmed in session! Talk to GM to VIP status");
		//PSendSysMessage("VIP status grands:");
	}
	/*if (sWorld.getConfig(CONFIG_VIP_PVE_SHOW))
	{
		PSendSysMessage("In PVE:");
		uint32 maxhonor = sWorld.getConfig(CONFIG_VIP_MAX_HONOR_POINTS);
		PSendSysMessage("Max Honor Points - %u",maxhonor);
		uint32 maxarena = sWorld.getConfig(CONFIG_VIP_MAX_ARENA_POINTS);
		PSendSysMessage("Max Arena Points - %u",maxarena);
		uint32 tradeskill = sWorld.getConfig(CONFIG_VIP_MAX_PRIMARY_TRADE_SKILL);
		PSendSysMessage("Count of Professions - %u",tradeskill);
		uint32 petition = sWorld.getConfig(CONFIG_VIP_MIN_PETITION_SIGNS);
		PSendSysMessage("Petition Sings for Guild - %u",petition);
		uint32 xpdist = sWorld.getConfig(CONFIG_VIP_GROUP_XP_DISTANCE);
		PSendSysMessage("Distance of giving XP in party - %u",xpdist);
		float money = sWorld.getConfig(VIP_RATE_DROP_MONEY);
		PSendSysMessage("Drop gold - %f X",money);
		float xpkill = sWorld.getConfig(VIP_RATE_XP_KILL);
		PSendSysMessage("XP for kills - %f X",xpkill);
		float xpquest = sWorld.getConfig(VIP_RATE_XP_QUEST);
		PSendSysMessage("XP for quests - %f X",xpquest);
		float rest = sWorld.getConfig(VIP_RATE_REST_OFFLINE_IN_TAVERN_OR_CITY);
		PSendSysMessage("Rate Rest - %f X",rest);
		float fall = sWorld.getConfig(VIP_RATE_DAMAGE_FALL);
		PSendSysMessage("Damage of fall - %f X",fall);
		float rep = sWorld.getConfig(VIP_RATE_REPUTATION_GAIN);
		PSendSysMessage("Reputation giving - %f X",rep);
		uint32 skills = sWorld.getConfig(CONFIG_VIP_SKILL_GAIN_WEAPON);
		PSendSysMessage("Skills levelup - %u",skills);
		uint32 slevel = sWorld.getConfig(CONFIG_VIP_DEATH_SICKNESS_LEVEL);
		PSendSysMessage("Death Sickness level - %u",slevel);
	}

	if (sWorld.getConfig(CONFIG_VIP_PVP_SHOW))
	{
		PSendSysMessage("In PVP");
		float honor = sWorld.getConfig(VIP_RATE_HONOR);
		PSendSysMessage("Honor - %f X",honor);
		uint32 bgwin = sWorld.getConfig(CONFIG_VIP_BG_MARKS_WIN);
		PSendSysMessage("More BG Marks if win - +%u",bgwin);
		uint32 bglose = sWorld.getConfig(CONFIG_VIP_BG_MARKS_LOSE);
		PSendSysMessage("More BG Marks if lose - +%u",bglose);
		float arena = sWorld.getConfig(VIP_RATE_ARENA_POINTS);
		PSendSysMessage("More Arena Points Dintributing - %f X",arena);
		uint32 desert = sWorld.getConfig(CONFIG_VIP_BATTLEGROUND_CAST_DESERTER);
		if (desert == 0)
			PSendSysMessage("No Desertire after leave BG");
	}*/
	return true;
}

bool ChatHandler::HandleStartCommand(const char* /*args*/)
{
    Player *chr = m_session->GetPlayer();

    if (chr->isInFlight())
    {
        SendSysMessage(LANG_YOU_IN_FLIGHT);
        SetSentErrorMessage(true);
        return false;
    }

    if (chr->isInCombat())
    {
        SendSysMessage(LANG_YOU_IN_COMBAT);
        SetSentErrorMessage(true);
        return false;
    }

    // cast spell Stuck
    chr->CastSpell(chr,7355,false);
    return true;
}

bool ChatHandler::HandleSpectatorStopCommand(const char* args)
{
	Player *plr = m_session->GetPlayer();

	if (plr->isSpectator())
	{
		plr->TeleportTo(plr->GetBattleGroundEntryPoint());
		plr->SetSpectator(false);
	}
	return true;
}

bool ChatHandler::HandleServerInfoCommand(const char* /*args*/)
{
    uint32 activeClientsNum = sWorld.GetActiveSessionCount();
    uint32 queuedClientsNum = sWorld.GetQueuedSessionCount();
    uint32 maxActiveClientsNum = sWorld.GetMaxActiveSessionCount();
    uint32 maxQueuedClientsNum = sWorld.GetMaxQueuedSessionCount();
    std::string str = secsToTimeString(sWorld.GetUptime());
    uint32 updateTime = sWorld.GetUpdateTime();

    PSendSysMessage(_FULLVERSION);
    //if (m_session)
    //    full = _FULLVERSION(REVISION_DATE,REVISION_TIME,"|cffffffff|Hurl:" REVISION_ID "|h" REVISION_ID "|h|r");
    //else
    //    full = _FULLVERSION(REVISION_DATE,REVISION_TIME,REVISION_ID);

    //SendSysMessage(full);
    //PSendSysMessage(LANG_USING_WORLD_DB,sWorld.GetDBVersion());
    PSendSysMessage(LANG_CONNECTED_USERS, activeClientsNum, maxActiveClientsNum, queuedClientsNum, maxQueuedClientsNum);
    PSendSysMessage(LANG_UPTIME, str.c_str());
    PSendSysMessage("Update time diff: %u.", updateTime);

    return true;
}

bool ChatHandler::HandleDismountCommand(const char* /*args*/)
{
    //If player is not mounted, so go out :)
    if (!m_session->GetPlayer()->IsMounted())
    {
        SendSysMessage(LANG_CHAR_NON_MOUNTED);
        SetSentErrorMessage(true);
        return false;
    }

    if (m_session->GetPlayer()->isInFlight())
    {
        SendSysMessage(LANG_YOU_IN_FLIGHT);
        SetSentErrorMessage(true);
        return false;
    }

    m_session->GetPlayer()->Unmount();
    m_session->GetPlayer()->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
    return true;
}

bool ChatHandler::HandleSaveCommand(const char* /*args*/)
{
    Player *player=m_session->GetPlayer();

    // save GM account without delay and output message (testing, etc)
    if (m_session->GetSecurity())
    {
        player->SaveToDB();
        SendSysMessage(LANG_PLAYER_SAVED);
        return true;
    }

    // save or plan save after 20 sec (logout delay) if current next save time more this value and _not_ output any messages to prevent cheat planning
    uint32 save_interval = sWorld.getConfig(CONFIG_INTERVAL_SAVE);
    if (save_interval == 0 || save_interval > 20*IN_MILLISECONDS && player->GetSaveTimer() <= save_interval - 20*IN_MILLISECONDS)
        player->SaveToDB();

    return true;
}

bool ChatHandler::HandleGMListIngameCommand(const char* /*args*/)
{
    bool first = true;

    ObjectAccessor::Guard guard(*HashMapHolder<Player>::GetLock());
    HashMapHolder<Player>::MapType &m = ObjectAccessor::Instance().GetPlayers();
    for (HashMapHolder<Player>::MapType::iterator itr = m.begin(); itr != m.end(); ++itr)
    {
        if (itr->second->GetSession()->GetSecurity() &&
            (itr->second->isGameMaster() || sWorld.getConfig(CONFIG_GM_IN_GM_LIST)) &&
            (!m_session || itr->second->IsVisibleGloballyFor(m_session->GetPlayer())))
        {
            if (first)
            {
                SendSysMessage(LANG_GMS_ON_SRV);
                first = false;
            }

            SendSysMessage(itr->second->GetName());
        }
    }

    if (first)
        SendSysMessage(LANG_GMS_NOT_LOGGED);

    return true;
}

bool ChatHandler::HandleAccountPasswordCommand(const char* args)
{
    if (!*args)
        return false;

    char *old_pass = strtok ((char*)args, " ");
    char *new_pass = strtok (NULL, " ");
    char *new_pass_c  = strtok (NULL, " ");

    if (!old_pass || !new_pass || !new_pass_c)
        return false;

    std::string password_old = old_pass;
    std::string password_new = new_pass;
    std::string password_new_c = new_pass_c;

    if (strcmp(new_pass, new_pass_c) != 0)
    {
        SendSysMessage (LANG_NEW_PASSWORDS_NOT_MATCH);
        SetSentErrorMessage (true);
        return false;
    }

    if (!sAccountMgr->CheckPassword (m_session->GetAccountId(), password_old))
    {
        SendSysMessage (LANG_COMMAND_WRONGOLDPASSWORD);
        SetSentErrorMessage (true);
        return false;
    }

    AccountOpResult result = sAccountMgr->ChangePassword(m_session->GetAccountId(), password_new);

    switch(result)
    {
        case AOR_OK:
            SendSysMessage(LANG_COMMAND_PASSWORD);
            break;
        case AOR_PASS_TOO_LONG:
            SendSysMessage(LANG_PASSWORD_TOO_LONG);
            SetSentErrorMessage(true);
            return false;
        case AOR_NAME_NOT_EXIST:                            // not possible case, don't want get account name for output
        default:
            SendSysMessage(LANG_COMMAND_NOTCHANGEPASSWORD);
            SetSentErrorMessage(true);
            return false;
    }

    return true;
}

bool ChatHandler::HandleAccountLockCommand(const char* args)
{
    if (!*args)
    {
        SendSysMessage(LANG_USE_BOL);
        return true;
    }

    std::string argstr = (char*)args;
    if (argstr == "on")
    {
        LoginDatabase.PExecute("UPDATE account SET locked = '1' WHERE id = '%d'",m_session->GetAccountId());
        PSendSysMessage(LANG_COMMAND_ACCLOCKLOCKED);
        return true;
    }

    if (argstr == "off")
    {
        LoginDatabase.PExecute("UPDATE account SET locked = '0' WHERE id = '%d'",m_session->GetAccountId());
        PSendSysMessage(LANG_COMMAND_ACCLOCKUNLOCKED);
        return true;
    }

    SendSysMessage(LANG_USE_BOL);
    return true;
}

// Display the 'Message of the day' for the realm
bool ChatHandler::HandleServerMotdCommand(const char* /*args*/)
{
    PSendSysMessage(LANG_MOTD_CURRENT, sWorld.GetMotd());
    return true;
}

