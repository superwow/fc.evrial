#include "ScriptPCH.h"
#include "World.h"

bool GossipHello_npc_transmogrification(Player *pPlayer, Creature *pCreature)
{
	// ������ ����
	pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual T1", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
	pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual T2", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
	pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual T3", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 30);
	pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual T4", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 40);
	pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual T5", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 50);
	pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual T6", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 60);
	pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual A1", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 70);
	pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual A2", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 80);
	pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual A3", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 90);
	pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual A4", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 100);

	// ���������� ����
	pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
	return true;
}
void UpdateGear(Player *pPlayer )
{
	// ���������� ���������� ����� ������
	pPlayer->SendUpdateToPlayer(pPlayer);

	// �������� ��� ������
	WorldPacket data(SMSG_FORCE_DISPLAY_UPDATE, 8);
	data << pPlayer->GetGUID();
	pPlayer->SendMessageToSet(&data,true);

	// ���������� ������ (��� �����)
	pPlayer->CastSpell(pPlayer, 24222, true);
}
bool GossipSelect_npc_transmogrification(Player *pPlayer, Creature *pCreature, uint32 sender, uint32 action )
{
	// �� ��������� � �������
    if (pPlayer->isInCombat())
    {
		pPlayer->CLOSE_GOSSIP_MENU();
		pCreature->MonsterWhisper("You are in combat!", pPlayer->GetGUID());
		return false;
    }

	// �������� ������� �����
	if (pPlayer->GetMoney() < sWorld.getConfig(CONFIG_TRANS_GOLD))
	{
		pPlayer->CLOSE_GOSSIP_MENU();
		pCreature->MonsterWhisper("You have not enough gold!", pPlayer->GetGUID());
		return false;
	}

	// �������� ������� ������
	if (pPlayer->GetHonorPoints() < sWorld.getConfig(CONFIG_TRANS_HONOR))
	{
		pPlayer->CLOSE_GOSSIP_MENU();
		pCreature->MonsterWhisper("You have not enough honor!", pPlayer->GetGUID());
		return false;
	}

	// �������� ������� ���
	if (pPlayer->GetArenaPoints() < sWorld.getConfig(CONFIG_TRANS_AP))
	{
		pPlayer->CLOSE_GOSSIP_MENU();
		pCreature->MonsterWhisper("You have not enough arena points!", pPlayer->GetGUID());
		return false;
	}

	// �������� ������� ��������
	if (pPlayer->GetMaxPersonalArenaRatingRequirement() < sWorld.getConfig(CONFIG_TRANS_RATING))
	{
		pPlayer->CLOSE_GOSSIP_MENU();
		pCreature->MonsterWhisper("You have not enough arena rating!", pPlayer->GetGUID());
		return false;
	}

	// �������� ������� ������
	if (pPlayer->HasItemCount(sWorld.getConfig(CONFIG_TRANS_ITEM), sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true))
	{
		pPlayer->CLOSE_GOSSIP_MENU();
		pCreature->MonsterWhisper("You have not enough items!", pPlayer->GetGUID());
		return false;
	}

	// ��������� ������� ������� ������
	if (!pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0 ,EQUIPMENT_SLOT_HEAD) || 
		!pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0 ,EQUIPMENT_SLOT_SHOULDERS) || 
		!pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0 ,EQUIPMENT_SLOT_CHEST) || 
		!pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0 ,EQUIPMENT_SLOT_WRISTS) || 
		!pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0 ,EQUIPMENT_SLOT_HANDS) || 
		!pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0 ,EQUIPMENT_SLOT_WAIST) || 
		!pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0 ,EQUIPMENT_SLOT_LEGS) || 
		!pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0 ,EQUIPMENT_SLOT_FEET))
	{
		pPlayer->CLOSE_GOSSIP_MENU();
		pCreature->MonsterWhisper("You does not have full equipment!", pPlayer->GetGUID());
		return false;
	}

	// ���� ������
		// ���� 346
		// ����� 378
		// ���� 410
		// ���� 474
		// ����� 490
		// ���� 426
		// ����� 442
		// ����� 458

	//��� �������:
		// ��� 11
		// ��� 8
		// ����� 5
		// ��� 7
		// ��� 1
		// ���� 3
		// ��� 2
		// ��� 4
		// ��� 9

	// ����������� ���������� -> ���������� �����
	Item *oldItem1 = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0 ,EQUIPMENT_SLOT_HEAD);
	Item *oldItem2 = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0 ,EQUIPMENT_SLOT_SHOULDERS);
	Item *oldItem3= pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0 ,EQUIPMENT_SLOT_CHEST);
	Item *oldItem4 = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0 ,EQUIPMENT_SLOT_WRISTS);
	Item *oldItem5 = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0 ,EQUIPMENT_SLOT_HANDS);
	Item *oldItem6 = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0 ,EQUIPMENT_SLOT_WAIST);
	Item *oldItem7 = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0 ,EQUIPMENT_SLOT_LEGS);
	Item *oldItem8 = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0 ,EQUIPMENT_SLOT_FEET);

	switch (action)
	{
		// ������� �����������������
		case GOSSIP_ACTION_INFO_DEF + 10: // T1
		{
			// �������
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warrior", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Paladin", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Hunter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13); // ����
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Rogue", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Priest", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 15); // �����
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Shaman", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 16); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Mage", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 17); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warlock", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 18); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Druid", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 19); // ���

			// ���������� ����
			pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 20: // T2
		{
			// �������
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warrior", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 21); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Paladin", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 22); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Hunter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 23); // ����
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Rogue", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 24); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Priest", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 25); // �����
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Shaman", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 26); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Mage", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 27); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warlock", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 28); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Druid", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 29); // ���

			// ���������� ����
			pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 30: // T3
		{
			// �������
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warrior", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Paladin", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 32); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Hunter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33); // ����
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Rogue", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 34); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Priest", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 35); // �����
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Shaman", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 36); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Mage", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 37); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warlock", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 38); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Druid", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 39); // ���

			// ���������� ����
			pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 40: // �4
		{
			// �������
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warrior", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 41); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Paladin", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 42); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Hunter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 43); // ����
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Rogue", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 44); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Priest", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 45); // �����
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Shaman", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 46); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Mage", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 47); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warlock", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 48); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Druid", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 49); // ���

			// ���������� ����
			pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 50: // �5
		{
			// �������
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warrior", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 51); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Paladin", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 52); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Hunter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 53); // ����
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Rogue", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 54); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Priest", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 55); // �����
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Shaman", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 56); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Mage", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 57); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warlock", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 58); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Druid", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 59); // ���

			// ���������� ����
			pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 60: // T6
		{
			// �������
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warrior", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 61); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Paladin", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 62); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Hunter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 63); // ����
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Rogue", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 64); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Priest", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 65); // �����
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Shaman", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 66); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Mage", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 67); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warlock", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 68); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Druid", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 69); // ���

			// ���������� ����
			pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 70: // A1
		{
			// �������
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warrior", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 71); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Paladin", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 72); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Hunter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 73); // ����
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Rogue", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 74); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Priest", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 75); // �����
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Shaman", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 76); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Mage", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 77); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warlock", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 78); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Druid", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 79); // ���

			// ���������� ����
			pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 80: // �2
		{
			// �������
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warrior", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 81); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Paladin", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 82); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Hunter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 83); // ����
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Rogue", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 84); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Priest", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 85); // �����
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Shaman", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 86); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Mage", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 87); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warlock", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 88); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Druid", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 89); // ���

			// ���������� ����
			pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 90: // �3
		{
			// �������
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warrior", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 91); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Paladin", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 92); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Hunter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 93); // ����
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Rogue", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 94); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Priest", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 95); // �����
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Shaman", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 96); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Mage", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 97); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warlock", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 98); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Druid", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 99); // ���

			// ���������� ����
			pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 100: // �4
		{
			// �������
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warrior", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 101); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Paladin", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 102); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Hunter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 103); // ����
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Rogue", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 104); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Priest", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 105); // �����
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Shaman", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 106); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Mage", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 107); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warlock", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 108); // ���
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Druid", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 109); // ���

			// ���������� ����
			pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 11: // ��� �1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16866); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16868); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16865); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16861); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16863); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16864); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16867); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16862); // �����

			oldItem1->SetFakeEntry(16866);
			oldItem2->SetFakeEntry(16868);
			oldItem3->SetFakeEntry(16865);
			oldItem4->SetFakeEntry(16861);
			oldItem5->SetFakeEntry(16863);
			oldItem6->SetFakeEntry(16864);
			oldItem7->SetFakeEntry(16867);
			oldItem8->SetFakeEntry(16862);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 12: // ��� �1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16854); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16856); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16853); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16857); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16860); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16858); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16855); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16859); // �����

			oldItem1->SetFakeEntry(16854);
			oldItem2->SetFakeEntry(16856);
			oldItem3->SetFakeEntry(16853);
			oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(16860);
			oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(16855);
			oldItem8->SetFakeEntry(16859);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 13: // ���� �1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16846); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16848); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16845); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16850); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16852); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16851); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16847); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16849); // �����

			oldItem1->SetFakeEntry(16846);
			oldItem2->SetFakeEntry(16848);
			oldItem3->SetFakeEntry(16845);
			oldItem4->SetFakeEntry(16850);
			oldItem5->SetFakeEntry(16852);
			oldItem6->SetFakeEntry(16851);
			oldItem7->SetFakeEntry(16847);
			oldItem8->SetFakeEntry(16849);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 14: // ��� �1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16821); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16823); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16820); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16825); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16826); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16827); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16822); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16824); // �����

			oldItem1->SetFakeEntry(16821);
			oldItem2->SetFakeEntry(16823);
			oldItem3->SetFakeEntry(16820);
			oldItem4->SetFakeEntry(16825);
			oldItem5->SetFakeEntry(16826);
			oldItem6->SetFakeEntry(16827);
			oldItem7->SetFakeEntry(16822);
			oldItem8->SetFakeEntry(16824);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 15: // ����� �1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16813); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16816); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16815); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16819); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16812); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16817); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16814); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16811); // �����

			oldItem1->SetFakeEntry(16813);
			oldItem2->SetFakeEntry(16816);
			oldItem3->SetFakeEntry(16815);
			oldItem4->SetFakeEntry(16819);
			oldItem5->SetFakeEntry(16812);
			oldItem6->SetFakeEntry(16817);
			oldItem7->SetFakeEntry(16814);
			oldItem8->SetFakeEntry(16811);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 16: // ��� �1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16842); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16844); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16841); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16840); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16839); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16838); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16843); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16837); // �����

			oldItem1->SetFakeEntry(16842);
			oldItem2->SetFakeEntry(16844);
			oldItem3->SetFakeEntry(16841);
			oldItem4->SetFakeEntry(16840);
			oldItem5->SetFakeEntry(16839);
			oldItem6->SetFakeEntry(16838);
			oldItem7->SetFakeEntry(16843);
			oldItem8->SetFakeEntry(16837);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 17: // ��� �1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16795); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16797); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16798); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16799); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16801); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16802); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16796); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16800); // �����

			oldItem1->SetFakeEntry(16795);
			oldItem2->SetFakeEntry(16797);
			oldItem3->SetFakeEntry(16798);
			oldItem4->SetFakeEntry(16799);
			oldItem5->SetFakeEntry(16801);
			oldItem6->SetFakeEntry(16802);
			oldItem7->SetFakeEntry(16796);
			oldItem8->SetFakeEntry(16800);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 18: // ��� �1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16808); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16807); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16809); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16804); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16805); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16806); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16810); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16803); // �����

			oldItem1->SetFakeEntry(16808);
			oldItem2->SetFakeEntry(16807);
			oldItem3->SetFakeEntry(16809);
			oldItem4->SetFakeEntry(16804);
			oldItem5->SetFakeEntry(16805);
			oldItem6->SetFakeEntry(16806);
			oldItem7->SetFakeEntry(16810);
			oldItem8->SetFakeEntry(16803);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 19: // ��� �1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16834); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16836); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16833); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16830); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16831); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16828); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16835); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16829); // �����

			oldItem1->SetFakeEntry(16834);
			oldItem2->SetFakeEntry(16836);
			oldItem3->SetFakeEntry(16833);
			oldItem4->SetFakeEntry(16830);
			oldItem5->SetFakeEntry(16831);
			oldItem6->SetFakeEntry(16828);
			oldItem7->SetFakeEntry(16835);
			oldItem8->SetFakeEntry(16829);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 21: // ��� �2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16963); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16961); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16966); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16959); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16964); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16960); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16962); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16965); // �����

			oldItem1->SetFakeEntry(16963);
			oldItem2->SetFakeEntry(16961);
			oldItem3->SetFakeEntry(16966);
			oldItem4->SetFakeEntry(16959);
			oldItem5->SetFakeEntry(16964);
			oldItem6->SetFakeEntry(16960);
			oldItem7->SetFakeEntry(16962);
			oldItem8->SetFakeEntry(16965);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 22: // ��� �2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16955); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16953); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16958); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16951); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16956); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16952); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16954); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16957); // �����

			oldItem1->SetFakeEntry(16955);
			oldItem2->SetFakeEntry(16953);
			oldItem3->SetFakeEntry(16958);
			oldItem4->SetFakeEntry(16951);
			oldItem5->SetFakeEntry(16956);
			oldItem6->SetFakeEntry(16952);
			oldItem7->SetFakeEntry(16954);
			oldItem8->SetFakeEntry(16957);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 23: // ���� �2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16939); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16937); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16942); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16935); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16940); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16936); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16938); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16941); // �����

			oldItem1->SetFakeEntry(16939);
			oldItem2->SetFakeEntry(16937);
			oldItem3->SetFakeEntry(16942);
			oldItem4->SetFakeEntry(16935);
			oldItem5->SetFakeEntry(16940);
			oldItem6->SetFakeEntry(16936);
			oldItem7->SetFakeEntry(16938);
			oldItem8->SetFakeEntry(16941);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 24: // ��� �2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16908); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16832); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16905); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16911); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16907); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16910); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16909); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16906); // �����

			oldItem1->SetFakeEntry(16908);
			oldItem2->SetFakeEntry(16832);
			oldItem3->SetFakeEntry(16905);
			oldItem4->SetFakeEntry(16911);
			oldItem5->SetFakeEntry(16907);
			oldItem6->SetFakeEntry(16910);
			oldItem7->SetFakeEntry(16909);
			oldItem8->SetFakeEntry(16906);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 25: // ����� �2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16921); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16924); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16923); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16926); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16920); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16925); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16922); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16919); // �����

			oldItem1->SetFakeEntry(16921);
			oldItem2->SetFakeEntry(16924);
			oldItem3->SetFakeEntry(16923);
			oldItem4->SetFakeEntry(16926);
			oldItem5->SetFakeEntry(16920);
			oldItem6->SetFakeEntry(16925);
			oldItem7->SetFakeEntry(16922);
			oldItem8->SetFakeEntry(16919);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 26: // ��� �2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16947); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16945); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16950); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16943); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16948); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16944); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16946); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16949); // �����

			oldItem1->SetFakeEntry(16947);
			oldItem2->SetFakeEntry(16945);
			oldItem3->SetFakeEntry(16950);
			oldItem4->SetFakeEntry(16943);
			oldItem5->SetFakeEntry(16948);
			oldItem6->SetFakeEntry(16944);
			oldItem7->SetFakeEntry(16946);
			oldItem8->SetFakeEntry(16949);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 27: // ��� �2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16914); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16917); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16916); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16918); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16913); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16818); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16915); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16912); // �����

			oldItem1->SetFakeEntry(16914);
			oldItem2->SetFakeEntry(16917);
			oldItem3->SetFakeEntry(16916);
			oldItem4->SetFakeEntry(16918);
			oldItem5->SetFakeEntry(16913);
			oldItem6->SetFakeEntry(16818);
			oldItem7->SetFakeEntry(16915);
			oldItem8->SetFakeEntry(16912);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 28: // ��� �2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16929); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16932); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16931); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16934); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16928); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16933); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16930); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16927); // �����

			oldItem1->SetFakeEntry(16929);
			oldItem2->SetFakeEntry(16932);
			oldItem3->SetFakeEntry(16931);
			oldItem4->SetFakeEntry(16934);
			oldItem5->SetFakeEntry(16928);
			oldItem6->SetFakeEntry(16933);
			oldItem7->SetFakeEntry(16930);
			oldItem8->SetFakeEntry(16927);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 29: // ��� �2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16900); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16902); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16897); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16904); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16899); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16903); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16901); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16898); // �����

			oldItem1->SetFakeEntry(16900);
			oldItem2->SetFakeEntry(16902);
			oldItem3->SetFakeEntry(16897);
			oldItem4->SetFakeEntry(16904);
			oldItem5->SetFakeEntry(16899);
			oldItem6->SetFakeEntry(16903);
			oldItem7->SetFakeEntry(16901);
			oldItem8->SetFakeEntry(16898);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 31: // ��� �3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 22418); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 22419); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 22416); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 22421); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 22417); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // �����

			oldItem1->SetFakeEntry(22418);
			oldItem2->SetFakeEntry(22419);
			oldItem3->SetFakeEntry(22416);
			oldItem4->SetFakeEntry(22423);
			oldItem5->SetFakeEntry(22421);
			oldItem6->SetFakeEntry(22422);
			oldItem7->SetFakeEntry(22417);
			oldItem8->SetFakeEntry(22420);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 32: // ��� �3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 22428); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 22429); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 22425); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22424); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 22426); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22431); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 22427); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22430); // �����

			oldItem1->SetFakeEntry(22428);
			oldItem2->SetFakeEntry(22429);
			oldItem3->SetFakeEntry(22425);
			oldItem4->SetFakeEntry(22424);
			oldItem5->SetFakeEntry(22426);
			oldItem6->SetFakeEntry(22431);
			oldItem7->SetFakeEntry(22427);
			oldItem8->SetFakeEntry(22430);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 33: // ���� �3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 22438); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 22439); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 22436); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22443); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 22441); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22442); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 22437); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22440); // �����

			oldItem1->SetFakeEntry(22438);
			oldItem2->SetFakeEntry(22439);
			oldItem3->SetFakeEntry(22436);
			oldItem4->SetFakeEntry(22443);
			oldItem5->SetFakeEntry(22441);
			oldItem6->SetFakeEntry(22442);
			oldItem7->SetFakeEntry(22437);
			oldItem8->SetFakeEntry(22440);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 34: // ��� �3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 22478); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 22479); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 22476); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22483); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 22481); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22482); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 22477); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22480); // �����

			oldItem1->SetFakeEntry(22478);
			oldItem2->SetFakeEntry(22479);
			oldItem3->SetFakeEntry(22476);
			oldItem4->SetFakeEntry(22483);
			oldItem5->SetFakeEntry(22481);
			oldItem6->SetFakeEntry(22482);
			oldItem7->SetFakeEntry(22477);
			oldItem8->SetFakeEntry(22480);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 35: // ����� �3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 22514); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 22515); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 22512); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22517); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 22519); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22518); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 22513); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22516); // �����

			oldItem1->SetFakeEntry(22514);
			oldItem2->SetFakeEntry(22515);
			oldItem3->SetFakeEntry(22512);
			oldItem4->SetFakeEntry(22517);
			oldItem5->SetFakeEntry(22519);
			oldItem6->SetFakeEntry(22518);
			oldItem7->SetFakeEntry(22513);
			oldItem8->SetFakeEntry(22516);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 36: // ��� �3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 22466); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 22467); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 22464); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22471); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 22469); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22470); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 22465); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22468); // �����

			oldItem1->SetFakeEntry(22466);
			oldItem2->SetFakeEntry(22467);
			oldItem3->SetFakeEntry(22464);
			oldItem4->SetFakeEntry(22471);
			oldItem5->SetFakeEntry(22469);
			oldItem6->SetFakeEntry(22470);
			oldItem7->SetFakeEntry(22465);
			oldItem8->SetFakeEntry(22468);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 37: // ��� �3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 22498); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 22499); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 22496); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22503); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 22501); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22502); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 22497); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22500); // �����

			oldItem1->SetFakeEntry(22498);
			oldItem2->SetFakeEntry(22499);
			oldItem3->SetFakeEntry(22496);
			oldItem4->SetFakeEntry(22503);
			oldItem5->SetFakeEntry(22501);
			oldItem6->SetFakeEntry(22502);
			oldItem7->SetFakeEntry(22497);
			oldItem8->SetFakeEntry(22500);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 38: // ��� �3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 22506); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 22507); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 22504); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22511); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 22509); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22510); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 22505); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22508); // �����

			oldItem1->SetFakeEntry(22506);
			oldItem2->SetFakeEntry(22507);
			oldItem3->SetFakeEntry(22504);
			oldItem4->SetFakeEntry(22511);
			oldItem5->SetFakeEntry(22509);
			oldItem6->SetFakeEntry(22510);
			oldItem7->SetFakeEntry(22505);
			oldItem8->SetFakeEntry(22508);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 39: // ��� �3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 22490); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 22491); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 22488); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22495); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 22493); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22494); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 22489); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22492); // �����

			oldItem1->SetFakeEntry(22490);
			oldItem2->SetFakeEntry(22491);
			oldItem3->SetFakeEntry(22488);
			oldItem4->SetFakeEntry(22495);
			oldItem5->SetFakeEntry(22493);
			oldItem6->SetFakeEntry(22494);
			oldItem7->SetFakeEntry(22489);
			oldItem8->SetFakeEntry(22492);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 41: // ��� �4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 29011); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 29016); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 29012); // ����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 29017); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 29015); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // �����

			oldItem1->SetFakeEntry(29011);
			oldItem2->SetFakeEntry(29016);
			oldItem3->SetFakeEntry(29012);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(29017);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(29015);
			//oldItem8->SetFakeEntry(16859);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 42: // ��� �4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 29068); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 29070); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 29066); // ����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 29067); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 29069); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // �����

			oldItem1->SetFakeEntry(29068);
			oldItem2->SetFakeEntry(29070);
			oldItem3->SetFakeEntry(29066);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(29067);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(29069);
			//oldItem8->SetFakeEntry(16859);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 43: // ���� �4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 29081); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 29084); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 29082); // ����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 29085); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 29083); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // �����

			oldItem1->SetFakeEntry(29081);
			oldItem2->SetFakeEntry(29084);
			oldItem3->SetFakeEntry(29082);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(29085);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(29083);
			//oldItem8->SetFakeEntry(16859);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 44: // ��� �4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 29044); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 29047); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 29045); // ����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 29048); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 29046); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // �����

			oldItem1->SetFakeEntry(29044);
			oldItem2->SetFakeEntry(29047);
			oldItem3->SetFakeEntry(29045);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(29048);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(29046);
			//oldItem8->SetFakeEntry(16859);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 45: // ����� �4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 29049); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 29054); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 29050); // ����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 29055); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 29053); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // �����

			oldItem1->SetFakeEntry(29049);
			oldItem2->SetFakeEntry(29054);
			oldItem3->SetFakeEntry(29050);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(29055);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(29053);
			//oldItem8->SetFakeEntry(16859);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 46: // ��� �4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 29040); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 29043); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 29038); // ����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 29039); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 29042); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // �����

			oldItem1->SetFakeEntry(29040);
			oldItem2->SetFakeEntry(29043);
			oldItem3->SetFakeEntry(29038);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(29039);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(29042);
			//oldItem8->SetFakeEntry(16859);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 47: // ��� �4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 29076); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 29079); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 29077); // ����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 29080); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 29078); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // �����

			oldItem1->SetFakeEntry(29076);
			oldItem2->SetFakeEntry(29079);
			oldItem3->SetFakeEntry(29077);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(29080);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(29078);
			//oldItem8->SetFakeEntry(16859);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 48: // ��� �4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 28963); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 28967); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 28964); // ����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 28968); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 28966); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // �����

			oldItem1->SetFakeEntry(28963);
			oldItem2->SetFakeEntry(28967);
			oldItem3->SetFakeEntry(28964);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(28968);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(28966);
			//oldItem8->SetFakeEntry(16859);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 49: // ��� �4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 29098); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 29100); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 29096); // ����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 29097); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 29099); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // �����

			oldItem1->SetFakeEntry(29098);
			oldItem2->SetFakeEntry(29100);
			oldItem3->SetFakeEntry(29096);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(29097);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(29099);
			//oldItem8->SetFakeEntry(16859);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 51: // ��� �5
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 30120); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 30122); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 30118); // ����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 ,  30119); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 30121); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // �����

			oldItem1->SetFakeEntry(30120);
			oldItem2->SetFakeEntry(30122);
			oldItem3->SetFakeEntry(30118);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(30119);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(30121);
			//oldItem8->SetFakeEntry(16859);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 52: // ��� �5
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 30136); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 30138); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 30134); // ����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 30135); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 30137); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // �����

			oldItem1->SetFakeEntry(30136);
			oldItem2->SetFakeEntry(30138);
			oldItem3->SetFakeEntry(30134);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(30135);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(30137);
			//oldItem8->SetFakeEntry(16859);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 53: // ���� �5
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 30141); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 30143); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 30139); // ����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 30140); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 30142); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // �����

			oldItem1->SetFakeEntry(30141);
			oldItem2->SetFakeEntry(30143);
			oldItem3->SetFakeEntry(30139);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(30140);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(30142);
			//oldItem8->SetFakeEntry(16859);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 54: // ��� �5
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 30146); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 30149); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 30144); // ����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 30145); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 30148); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // �����

			oldItem1->SetFakeEntry(30146);
			oldItem2->SetFakeEntry(30149);
			oldItem3->SetFakeEntry(30144);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(30145);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(30148);
			//oldItem8->SetFakeEntry(16859);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 55: // ����� �5
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 30161); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 30163); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 30159); // ����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 30160); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 30162); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // �����

			oldItem1->SetFakeEntry(30161);
			oldItem2->SetFakeEntry(30163);
			oldItem3->SetFakeEntry(30159);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(30160);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(30162);
			//oldItem8->SetFakeEntry(16859);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 56: // ��� �5
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 30171); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 30173); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 30169); // ����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 30170); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 30172); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // �����

			oldItem1->SetFakeEntry(30171);
			oldItem2->SetFakeEntry(30173);
			oldItem3->SetFakeEntry(30169);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(30170);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(30172);
			//oldItem8->SetFakeEntry(16859);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 57: // ��� �5
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 30206); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 30210); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 30196); // ����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 30205); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 30207); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // �����

			oldItem1->SetFakeEntry(30206);
			oldItem2->SetFakeEntry(30210);
			oldItem3->SetFakeEntry(30196);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(30205);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(30207);
			//oldItem8->SetFakeEntry(16859);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 58: // ��� �5
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 30212); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 30215); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 30214); // ����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 30211); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 30213); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // �����

			oldItem1->SetFakeEntry(30212);
			oldItem2->SetFakeEntry(30215);
			oldItem3->SetFakeEntry(30214);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(30211);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(30213);
			//oldItem8->SetFakeEntry(16859);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 59: // ��� �5
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 30233); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 30235); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 30231); // ����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 30232); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 30234); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // �����

			oldItem1->SetFakeEntry(30233);
			oldItem2->SetFakeEntry(30235);
			oldItem3->SetFakeEntry(30231);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(30232);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(30234);
			//oldItem8->SetFakeEntry(16859);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 61: // ��� �6
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 30972); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 30979); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 30975); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 34441); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 30969); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 34546); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 30977); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 34569); // �����

			oldItem1->SetFakeEntry(30972);
			oldItem2->SetFakeEntry(30979);
			oldItem3->SetFakeEntry(30975);
			oldItem4->SetFakeEntry(34441);
			oldItem5->SetFakeEntry(30969);
			oldItem6->SetFakeEntry(34546);
			oldItem7->SetFakeEntry(30977);
			oldItem8->SetFakeEntry(34569);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 62: // ��� �6
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 30988); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 30996); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 30992); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 34432); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 30992); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 34487); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 30994); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 34559); // �����

			oldItem1->SetFakeEntry(30988);
			oldItem2->SetFakeEntry(30996);
			oldItem3->SetFakeEntry(30992);
			oldItem4->SetFakeEntry(34432);
			oldItem5->SetFakeEntry(30992);
			oldItem6->SetFakeEntry(34487);
			oldItem7->SetFakeEntry(30994);
			oldItem8->SetFakeEntry(34559);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 63: // ���� �6
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 31003); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 31006); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 31004); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 34443); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 31001); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 34549); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 31005); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 34570); // �����

			oldItem1->SetFakeEntry(31003);
			oldItem2->SetFakeEntry(31006);
			oldItem3->SetFakeEntry(31004);
			oldItem4->SetFakeEntry(34443);
			oldItem5->SetFakeEntry(31001);
			oldItem6->SetFakeEntry(34549);
			oldItem7->SetFakeEntry(31005);
			oldItem8->SetFakeEntry(34570);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 64: // ��� �6
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 31027); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 31030); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 31028); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 34448); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 31026); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 34558); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 31029); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 34575); // �����

			oldItem1->SetFakeEntry(31027);
			oldItem2->SetFakeEntry(31030);
			oldItem3->SetFakeEntry(31028);
			oldItem4->SetFakeEntry(34448);
			oldItem5->SetFakeEntry(31026);
			oldItem6->SetFakeEntry(34558);
			oldItem7->SetFakeEntry(31029);
			oldItem8->SetFakeEntry(34575);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 65: // ����� �6
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 31063); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 31069); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 31066); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 34435); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 31060); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 34527); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 31068); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 34562); // �����

			oldItem1->SetFakeEntry(31063);
			oldItem2->SetFakeEntry(31069);
			oldItem3->SetFakeEntry(31066);
			oldItem4->SetFakeEntry(34435);
			oldItem5->SetFakeEntry(31060);
			oldItem6->SetFakeEntry(34527);
			oldItem7->SetFakeEntry(31068);
			oldItem8->SetFakeEntry(34562);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 66: // ��� �6
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 31014); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 31023); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 31017); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 34437); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 31008); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 34542); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 31020); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 34566); // �����

			oldItem1->SetFakeEntry(31014);
			oldItem2->SetFakeEntry(31023);
			oldItem3->SetFakeEntry(31017);
			oldItem4->SetFakeEntry(34437);
			oldItem5->SetFakeEntry(31008);
			oldItem6->SetFakeEntry(34542);
			oldItem7->SetFakeEntry(31020);
			oldItem8->SetFakeEntry(34566);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 67: // ��� �6
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 31056); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 31059); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 31057); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 34447); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 31055); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 34557); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 31058); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 34574); // �����

			oldItem1->SetFakeEntry(31059);
			oldItem2->SetFakeEntry(16856);
			oldItem3->SetFakeEntry(31057);
			oldItem4->SetFakeEntry(34447);
			oldItem5->SetFakeEntry(31055);
			oldItem6->SetFakeEntry(34557);
			oldItem7->SetFakeEntry(31058);
			oldItem8->SetFakeEntry(34574);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 68: // ��� �6
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 31051); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 31054); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 31052); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 34436); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 31050); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 34541); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 31053); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 34564); // �����

			oldItem1->SetFakeEntry(31051);
			oldItem2->SetFakeEntry(31054);
			oldItem3->SetFakeEntry(31052);
			oldItem4->SetFakeEntry(34436);
			oldItem5->SetFakeEntry(31050);
			oldItem6->SetFakeEntry(34541);
			oldItem7->SetFakeEntry(31053);
			oldItem8->SetFakeEntry(34564);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 69: // ��� �6
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 31037); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 31047); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 31041); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 34445); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 31032); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 34554); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 31045); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 34571); // �����

			oldItem1->SetFakeEntry(31037);
			oldItem2->SetFakeEntry(31047);
			oldItem3->SetFakeEntry(31041);
			oldItem4->SetFakeEntry(34445);
			oldItem5->SetFakeEntry(31032);
			oldItem6->SetFakeEntry(34554);
			oldItem7->SetFakeEntry(31045);
			oldItem8->SetFakeEntry(34571);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 71: // ��� A1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 24545); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 24546); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 24544); // ����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 ,  24549); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 24547); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // �����

			oldItem1->SetFakeEntry(24545);
			oldItem2->SetFakeEntry(24546);
			oldItem3->SetFakeEntry(24544);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(24549);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(24547);
			//oldItem8->SetFakeEntry(16859);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 72: // ��� A1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 27704); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 27706); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 27702); // ����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 27703); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 27705); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // �����

			oldItem1->SetFakeEntry(27704);
			oldItem2->SetFakeEntry(27706);
			oldItem3->SetFakeEntry(27702);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(27703);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(27705);
			//oldItem8->SetFakeEntry(16859);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 73: // ���� A1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 28331); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 28333); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 28334); // ����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 28335); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 28332); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // �����

			oldItem1->SetFakeEntry(28331);
			oldItem2->SetFakeEntry(28333);
			oldItem3->SetFakeEntry(28334);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(28335);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(28332);
			//oldItem8->SetFakeEntry(16859);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 74: // ��� A1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 25830); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 25832); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 25831); // ����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 25834); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 25833); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // �����

			oldItem1->SetFakeEntry(25830);
			oldItem2->SetFakeEntry(25832);
			oldItem3->SetFakeEntry(25831);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(25834);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(25833);
			//oldItem8->SetFakeEntry(16859);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 75: // ����� A1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 27708); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 27710); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 27711); // ����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 27707); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 27709); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // �����

			oldItem1->SetFakeEntry(27708);
			oldItem2->SetFakeEntry(27710);
			oldItem3->SetFakeEntry(27711);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(27707);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(27709);
			//oldItem8->SetFakeEntry(16859);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 76: // ��� A1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 25998); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 25999); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 25997); // ����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 26000); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 26001); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // �����

			oldItem1->SetFakeEntry(25998);
			oldItem2->SetFakeEntry(25999);
			oldItem3->SetFakeEntry(25997);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(26000);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(26001);
			//oldItem8->SetFakeEntry(16859);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 77: // ��� A1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 25855); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 25854); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 25856); // ����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 25857); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 25858); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // �����

			oldItem1->SetFakeEntry(25855);
			oldItem2->SetFakeEntry(25854);
			oldItem3->SetFakeEntry(25856);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(25857);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(25858);
			//oldItem8->SetFakeEntry(16859);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 78: // ��� A1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 24553); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 24554); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 24552); // ����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 24556); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 24555); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // �����

			oldItem1->SetFakeEntry(24553);
			oldItem2->SetFakeEntry(24554);
			oldItem3->SetFakeEntry(24552);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(24556);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(24555);
			//oldItem8->SetFakeEntry(16859);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 79: // ��� A1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 28127); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 28129); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 28130); // ����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 28126); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 28128); // �����
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // �����

			oldItem1->SetFakeEntry(28127);
			oldItem2->SetFakeEntry(28129);
			oldItem3->SetFakeEntry(28130);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(28126);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(28128);
			//oldItem8->SetFakeEntry(16859);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 81: // ��� A2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 30488); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 30490); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 30486); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 32818); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 30487); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 32805); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 30489); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 32793); // �����

			oldItem1->SetFakeEntry(30488);
			oldItem2->SetFakeEntry(30490);
			oldItem3->SetFakeEntry(30486);
			oldItem4->SetFakeEntry(32818);
			oldItem5->SetFakeEntry(30487);
			oldItem6->SetFakeEntry(32805);
			oldItem7->SetFakeEntry(30489);
			oldItem8->SetFakeEntry(32793);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 82: // ��� A2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 31997); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 31996); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 31992); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 32819); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 31993); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 32806); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 31995); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 32794); // �����

			oldItem1->SetFakeEntry(31997);
			oldItem2->SetFakeEntry(31996);
			oldItem3->SetFakeEntry(31992);
			oldItem4->SetFakeEntry(32819);
			oldItem5->SetFakeEntry(31993);
			oldItem6->SetFakeEntry(32806);
			oldItem7->SetFakeEntry(31995);
			oldItem8->SetFakeEntry(32794);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 83: // ���� A2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 31962); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 31964); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 31960); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 32809); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 31961); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 32797); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 31963); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 32785); // �����

			oldItem1->SetFakeEntry(31962);
			oldItem2->SetFakeEntry(31964);
			oldItem3->SetFakeEntry(31960);
			oldItem4->SetFakeEntry(32809);
			oldItem5->SetFakeEntry(31961);
			oldItem6->SetFakeEntry(32797);
			oldItem7->SetFakeEntry(31963);
			oldItem8->SetFakeEntry(32785);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 84: // ��� A2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 31999); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 32001); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 32002); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 32814); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 31998); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 32801); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 32000); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 32790); // �����

			oldItem1->SetFakeEntry(31999);
			oldItem2->SetFakeEntry(32001);
			oldItem3->SetFakeEntry(32002);
			oldItem4->SetFakeEntry(32814);
			oldItem5->SetFakeEntry(31998);
			oldItem6->SetFakeEntry(32801);
			oldItem7->SetFakeEntry(32000);
			oldItem8->SetFakeEntry(32790);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 85: // ����� A2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 32016); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 32018); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 32019); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 32980); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 32015); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 32979); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 32017); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 32981); // �����

			oldItem1->SetFakeEntry(32016);
			oldItem2->SetFakeEntry(32018);
			oldItem3->SetFakeEntry(32019);
			oldItem4->SetFakeEntry(32980);
			oldItem5->SetFakeEntry(32015);
			oldItem6->SetFakeEntry(32979);
			oldItem7->SetFakeEntry(32017);
			oldItem8->SetFakeEntry(32981);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 86: // ��� A2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 32006); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 32008); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 32004); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 32816); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 32005); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 32803); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 32007); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 32791); // �����

			oldItem1->SetFakeEntry(32006);
			oldItem2->SetFakeEntry(32008);
			oldItem3->SetFakeEntry(32004);
			oldItem4->SetFakeEntry(32816);
			oldItem5->SetFakeEntry(32005);
			oldItem6->SetFakeEntry(32803);
			oldItem7->SetFakeEntry(32007);
			oldItem8->SetFakeEntry(32791);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 87: // ��� A2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 32048); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 32047); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 32050); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 32820); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 32049); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 32807); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 32051); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 32795); // �����

			oldItem1->SetFakeEntry(32048);
			oldItem2->SetFakeEntry(32047);
			oldItem3->SetFakeEntry(32050);
			oldItem4->SetFakeEntry(32820);
			oldItem5->SetFakeEntry(32049);
			oldItem6->SetFakeEntry(32807);
			oldItem7->SetFakeEntry(32051);
			oldItem8->SetFakeEntry(32795);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 88: // ��� A2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 31974); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 31976); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 31977); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 32811); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 31973); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 32799); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 31975); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 32787); // �����

			oldItem1->SetFakeEntry(31974);
			oldItem2->SetFakeEntry(31976);
			oldItem3->SetFakeEntry(31977);
			oldItem4->SetFakeEntry(32811);
			oldItem5->SetFakeEntry(31973);
			oldItem6->SetFakeEntry(32799);
			oldItem7->SetFakeEntry(31975);
			oldItem8->SetFakeEntry(32787);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 89: // ��� A2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 31968); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 31971); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 31972); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 32812); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 31967); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 32800); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 31969); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 32788); // �����

			oldItem1->SetFakeEntry(31968);
			oldItem2->SetFakeEntry(31971);
			oldItem3->SetFakeEntry(31972);
			oldItem4->SetFakeEntry(32812);
			oldItem5->SetFakeEntry(31967);
			oldItem6->SetFakeEntry(32800);
			oldItem7->SetFakeEntry(31969);
			oldItem8->SetFakeEntry(32788);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 91: // ��� A3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 33730); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 33732); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 33728); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 33813); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 33729); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 33811); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 33731); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 33812); // �����

			oldItem1->SetFakeEntry(33730);
			oldItem2->SetFakeEntry(33732);
			oldItem3->SetFakeEntry(33728);
			oldItem4->SetFakeEntry(33813);
			oldItem5->SetFakeEntry(33729);
			oldItem6->SetFakeEntry(33811);
			oldItem7->SetFakeEntry(33731);
			oldItem8->SetFakeEntry(33812);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 92: // ��� A3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 33724); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 33726); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 33722); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 33904); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 33723); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 33903); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 33725); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 33905); // �����

			oldItem1->SetFakeEntry(33724);
			oldItem2->SetFakeEntry(33726);
			oldItem3->SetFakeEntry(33722);
			oldItem4->SetFakeEntry(33904);
			oldItem5->SetFakeEntry(33723);
			oldItem6->SetFakeEntry(33903);
			oldItem7->SetFakeEntry(33725);
			oldItem8->SetFakeEntry(33905);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 93: // ���� A3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 33666); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 33668); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 33664); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 33876); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 33665); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 33877); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 33667); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 33878); // �����

			oldItem1->SetFakeEntry(33666);
			oldItem2->SetFakeEntry(33668);
			oldItem3->SetFakeEntry(33664);
			oldItem4->SetFakeEntry(33876);
			oldItem5->SetFakeEntry(33665);
			oldItem6->SetFakeEntry(33877);
			oldItem7->SetFakeEntry(33667);
			oldItem8->SetFakeEntry(33878);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 94: // ��� A3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 33701); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 33703); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 33704); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 33893); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 33700); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 33891); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 33702); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 33892); // �����

			oldItem1->SetFakeEntry(33701);
			oldItem2->SetFakeEntry(33703);
			oldItem3->SetFakeEntry(33704);
			oldItem4->SetFakeEntry(33893);
			oldItem5->SetFakeEntry(33700);
			oldItem6->SetFakeEntry(33891);
			oldItem7->SetFakeEntry(33702);
			oldItem8->SetFakeEntry(33892);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 95: // ����� A3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 33745); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 33747); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 33748); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 33901); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 33744); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 33900); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 33746); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 33902); // �����

			oldItem1->SetFakeEntry(33745);
			oldItem2->SetFakeEntry(33747);
			oldItem3->SetFakeEntry(33748);
			oldItem4->SetFakeEntry(33901);
			oldItem5->SetFakeEntry(33744);
			oldItem6->SetFakeEntry(33900);
			oldItem7->SetFakeEntry(33746);
			oldItem8->SetFakeEntry(33902);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 96: // ��� A3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 33708); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 33710); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 33706); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 33906); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 33707); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 33907); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 33709); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 33908); // �����

			oldItem1->SetFakeEntry(33708);
			oldItem2->SetFakeEntry(33710);
			oldItem3->SetFakeEntry(33706);
			oldItem4->SetFakeEntry(33906);
			oldItem5->SetFakeEntry(33707);
			oldItem6->SetFakeEntry(33907);
			oldItem7->SetFakeEntry(33709);
			oldItem8->SetFakeEntry(33908);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 97: // ��� A3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 33758); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 33757); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 33760); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 33913); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 33759); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 33912); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 33761); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 33914); // �����

			oldItem1->SetFakeEntry(33758);
			oldItem2->SetFakeEntry(33757);
			oldItem3->SetFakeEntry(33760);
			oldItem4->SetFakeEntry(33913);
			oldItem5->SetFakeEntry(33759);
			oldItem6->SetFakeEntry(33912);
			oldItem7->SetFakeEntry(33761);
			oldItem8->SetFakeEntry(33914);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 98: // ��� A3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 33677); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 33679); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 33680); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 33883); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 33676); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 33882); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 33678); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 33884); // �����

			oldItem1->SetFakeEntry(33677);
			oldItem2->SetFakeEntry(33679);
			oldItem3->SetFakeEntry(33680);
			oldItem4->SetFakeEntry(33883);
			oldItem5->SetFakeEntry(33676);
			oldItem6->SetFakeEntry(33882);
			oldItem7->SetFakeEntry(33678);
			oldItem8->SetFakeEntry(33884);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 99: // ��� A3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 33691); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 33693); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 33694); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 33887); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 33690); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 33885); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 33692); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 33886); // �����

			oldItem1->SetFakeEntry(33691);
			oldItem2->SetFakeEntry(33693);
			oldItem3->SetFakeEntry(33694);
			oldItem4->SetFakeEntry(33887);
			oldItem5->SetFakeEntry(33690);
			oldItem6->SetFakeEntry(33885);
			oldItem7->SetFakeEntry(33692);
			oldItem8->SetFakeEntry(33886);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 101: // ��� A4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 35068); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 35070); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 35066); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 35176); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 35067); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 35161); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 35069); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 35146); // �����

			oldItem1->SetFakeEntry(35068);
			oldItem2->SetFakeEntry(35070);
			oldItem3->SetFakeEntry(35066);
			oldItem4->SetFakeEntry(35176);
			oldItem5->SetFakeEntry(35067);
			oldItem6->SetFakeEntry(35161);
			oldItem7->SetFakeEntry(35069);
			oldItem8->SetFakeEntry(35146);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 102: // ��� A4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 35029); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 35031); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 35027); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 35175); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 35028); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 35160); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 35030); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 35145); // �����

			oldItem1->SetFakeEntry(35029);
			oldItem2->SetFakeEntry(35031);
			oldItem3->SetFakeEntry(35027);
			oldItem4->SetFakeEntry(35175);
			oldItem5->SetFakeEntry(35028);
			oldItem6->SetFakeEntry(35160);
			oldItem7->SetFakeEntry(35030);
			oldItem8->SetFakeEntry(35145);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 103: // ���� A4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 34992); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 34994); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 34990); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 35166); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 34991); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 35151); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 34993); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 35136); // �����

			oldItem1->SetFakeEntry(34992);
			oldItem2->SetFakeEntry(34994);
			oldItem3->SetFakeEntry(34990);
			oldItem4->SetFakeEntry(35166);
			oldItem5->SetFakeEntry(34991);
			oldItem6->SetFakeEntry(35151);
			oldItem7->SetFakeEntry(34993);
			oldItem8->SetFakeEntry(35136);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 104: // ��� A4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 35033); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 35035); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 35036); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 35171); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 35032); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 35156); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 35034); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 35141); // �����

			oldItem1->SetFakeEntry(35033);
			oldItem2->SetFakeEntry(35035);
			oldItem3->SetFakeEntry(35036);
			oldItem4->SetFakeEntry(35171);
			oldItem5->SetFakeEntry(35032);
			oldItem6->SetFakeEntry(35156);
			oldItem7->SetFakeEntry(35034);
			oldItem8->SetFakeEntry(35141);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 105: // ����� A4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 35084); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 35086); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 35087); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 35174); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 35083); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 35159); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 35085); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 35144); // �����

			oldItem1->SetFakeEntry(35084);
			oldItem2->SetFakeEntry(35086);
			oldItem3->SetFakeEntry(35087);
			oldItem4->SetFakeEntry(35174);
			oldItem5->SetFakeEntry(35083);
			oldItem6->SetFakeEntry(35159);
			oldItem7->SetFakeEntry(35085);
			oldItem8->SetFakeEntry(35144);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 106: // ��� A4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 35044); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 35046); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 35042); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 35177); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 35043); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 35162); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 35045); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 35147); // �����

			oldItem1->SetFakeEntry(35044);
			oldItem2->SetFakeEntry(35046);
			oldItem3->SetFakeEntry(35042);
			oldItem4->SetFakeEntry(35177);
			oldItem5->SetFakeEntry(35043);
			oldItem6->SetFakeEntry(35162);
			oldItem7->SetFakeEntry(35045);
			oldItem8->SetFakeEntry(35147);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 107: // ��� A4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 35097); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 35096); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 35099); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 35179); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 35098); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 35164); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 35100); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 35149); // �����

			oldItem1->SetFakeEntry(35097);
			oldItem2->SetFakeEntry(35096);
			oldItem3->SetFakeEntry(35099);
			oldItem4->SetFakeEntry(35179);
			oldItem5->SetFakeEntry(35098);
			oldItem6->SetFakeEntry(35164);
			oldItem7->SetFakeEntry(35100);
			oldItem8->SetFakeEntry(35149);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 108: // ��� A4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 35004); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 35006); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 35007); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 35168); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 35003); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 35153); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 35005); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 35138); // �����

			oldItem1->SetFakeEntry(35004);
			oldItem2->SetFakeEntry(35006);
			oldItem3->SetFakeEntry(35007);
			oldItem4->SetFakeEntry(35168);
			oldItem5->SetFakeEntry(35003);
			oldItem6->SetFakeEntry(35153);
			oldItem7->SetFakeEntry(35005);
			oldItem8->SetFakeEntry(35138);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 109: // ��� A4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 34999); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 35001); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 35002); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 32788); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 34998); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 35154); // ����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 35000); // �����
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 35139); // �����

			oldItem1->SetFakeEntry(34999);
			oldItem2->SetFakeEntry(35001);
			oldItem3->SetFakeEntry(35002);
			oldItem4->SetFakeEntry(32788);
			oldItem5->SetFakeEntry(34998);
			oldItem6->SetFakeEntry(35154);
			oldItem7->SetFakeEntry(35000);
			oldItem8->SetFakeEntry(35139);

			// �������� ���, ����� �����
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney( -sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints(-sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints(-sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount(-sWorld.getConfig(CONFIG_TRANS_ITEM), -sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
	}
}
void AddSC_npc_transmogrification()
{
	Script *newscript;
	newscript = new Script;
	newscript->Name="npc_transmogrification";
	newscript->pGossipHello = &GossipHello_npc_transmogrification;
	newscript->pGossipSelect = &GossipSelect_npc_transmogrification;
	newscript->RegisterSelf();
}