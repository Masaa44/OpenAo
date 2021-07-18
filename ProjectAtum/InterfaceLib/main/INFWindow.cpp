// INFWindow.cpp: implementation of the CINFWindow class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RangeTime.h"
#include "INFUnitCreateInfo.h"
#include "INFWindow.h"
#include "AtumApplication.h"
#include "INFCommunity.h"
#include "INFTrade.h"
//#include "INFShop.h"
#include "INFCommunityParty.h"
#include "INFGameMainChat.h"
#include "INFCommunityGuild.h"
#include "INFCommunityChatRoom.h"
#include "INFGameMain.h"
#include "Chat.h"
#include "INFImage.h"
#include "D3DHanFont.h"
// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
#include "IMSocketManager.h"
//#include "IMSocket.h"

#include "FieldWinSocket.h"
#include "INFSelect.h"
#include "INFCreateMenu.h"
#include "Interface.h"
#include "ShuttleChild.h"
#include "CharacterChild.h"				// 2005-07-21 by ispark
#include "ItemInfo.h"
#include "INFInven.h"
#include "GameDataLast.h"
#include "SceneData.h"
#include "EnemyData.h"
#include "INFCityBase.h"
#include "Cinema.h"
#include "INFCitylab.h"
#include "INFCityStore.h"
#include "AtumSound.h"
#include "ClientParty.h"
#include "INFGameHelpDesk.h"
#include "INFCityShop.h"
#include "INFCommunityFriend.h"
#include "INFCommunityReject.h"
// 2008-09-22 by bhsohn EP3 ĳ���� â
//#include "INFCharacterInfo.h"
#include "INFCharacterInfoExtend.h"
#include "INFCityMission.h"
#include "INFCityOccupy.h"
#include "INFOtherCharInfo.h"
#include "QuestData.h"
#include "INFMp3Player.h"
#include "INFScrollBar.h"
#include "dxutil.h"
#include "CInput.h"
#include "INFMissionInfo.h"
#include "INFCommunityVOIP.h"
#include "Skill.h"
#include "SkillInfo.h"
#include "INFCityBazaar.h"
#include "INFCityArena.h"
#include "INFGameArena.h"
#include "INFCityWarPointShop.h"
#include "INFCityLeader.h"
#include "INFGameMainUnitInfoBar.h"
#include "INFCommunityGuildIntroMe.h"
#include "INFCommuPartyCre.h"
#include "AtumDatabase.h"

// 2009. 01. 12 by ckPark ���� ���� �ý���
#include "INFMotherShipManager.h"
// end 2009. 01. 12 by ckPark ���� ���� �ý���

// 2009-02-13 by bhsohn ���� ��ŷ �ý���
#include "WorldRankManager.h"
// end 2009-02-13 by bhsohn ���� ��ŷ �ý���

// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
#include "INFInfinity.h"
#include "INFCityInfinityShop.h"
// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

// 2010. 06. 18 by jskim ��æƮ ��� �޽��� �߰�
#include "INFCityLab.h"
//end 2010. 06. 18 by jskim ��æƮ ��� �޽��� �߰�

// 2010-08-31 by shcho&&jskim, ���� �ý��� ����
#include "INFDissolution.h"
// end 2010-08-31 by shcho&&jskim, ���� �ý��� ����
#include "StoreData.h"				  //2011-10-06 by jhahn ��Ʈ�� ������ �ý���

#include "PetManager.h"				  //2011-10-06 by jhahn ��Ʈ�� ������ �ý���

#include "INFGameMain.h"			  //2011-10-06 by jhahn ��Ʈ�� ������ �ý���
#include "INFGroupImage.h"
#include "INFGroupManager.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define BOX_START_DEFAULT_MIN_X     60                      // 2011. 10. 10 by jskim UI�ý��� ����			   
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	#define SIZE_MSGBOX_BUTTON_X		28
	#define SIZE_MSGBOX_BUTTON_Y		28
#else
#define SIZE_MSGBOX_BUTTON_X		36
#define SIZE_MSGBOX_BUTTON_Y		16
#endif
#define RADIO_BUTTON_Y				50
#define UM_MSGBOX_CLOSE				0x0010
#define OK_CANCEL_BUTTON			_Q_PARTY_INVITE == m_nMsgType ||			\
									_Q_PARTY_CREATE == m_nMsgType ||			\
									_Q_PARTY_BAN_MEMBER == m_nMsgType ||		\
									_Q_PARTY_TRANSFER_MASTER == m_nMsgType ||	\
									_Q_PARTY_SECEDE == m_nMsgType ||			\
									_Q_VOIP_OK == m_nMsgType			||		\
									_Q_TRADE_OK == m_nMsgType			||		\
									_Q_TRADE_CANCEL == m_nMsgType		||		\
									_Q_TRADE_REQUEST == m_nMsgType		||		\
									_Q_PK_REQUEST == m_nMsgType			||		\
									_Q_PK_LOSE_REQUEST_OK == m_nMsgType ||		\
									_Q_ITEM_DELETE == m_nMsgType		||		\
									_Q_SHOP_SELL_ITEM == m_nMsgType		||		\
									_Q_SHOP_MULTI_SELL_ITEM == m_nMsgType ||	\
									_Q_STORE_MULTI_PUT_ITEM == m_nMsgType ||	\
									_Q_STORE_MULTI_GET_ITEM == m_nMsgType ||	\
									_Q_AUCTION_INPUT_ITEM == m_nMsgType	||		\
									_Q_AUCTION_DELETE_ITEM== m_nMsgType	||		\
									_Q_REQUEST_PARTY_BATTLE == m_nMsgType	||	\
									_Q_REQUEST_GUILD_WAR == m_nMsgType	||	\
									_Q_GUILD_BAN_MEMBER == m_nMsgType	||		\
									_Q_GUILD_LEAVE == m_nMsgType		||		\
									_Q_GUILD_DISBAND == m_nMsgType		||		\
									_Q_GUILD_CANCEL == m_nMsgType		||		\
									_Q_GUILD_INVITE_QUESTION == m_nMsgType	||	\
									_Q_OUTDOOR_WARP == m_nMsgType		||		\
									_Q_STORE_PUT_ITEM == m_nMsgType		||		\
									_Q_QUEST_DISCARD == m_nMsgType		||		\
									_Q_PARTYMASTER_VOIP == m_nMsgType	||		\
									_Q_JOIN_PARTY_VOIP == m_nMsgType	||		\
									_Q_GUILDMASTER_VOIP == m_nMsgType	||		\
									_Q_JOIN_GUILD_VOIP == m_nMsgType	||		\
									_Q_USE_HELP_SYSTEM == m_nMsgType	||		\
									_Q_DELETE_FRIEND == m_nMsgType		||		\
									_Q_ITEM_DELETE_SKILL == m_nMsgType	||		\
									_Q_DELETE_REJECT == m_nMsgType		||		\
									_Q_GUILD_VOIP_END == m_nMsgType		||		\
									_Q_PARTY_VOIP_END == m_nMsgType		||		\
									_Q_STORE_USE == m_nMsgType			||		\
									_Q_GET_TEX ==  m_nMsgType			||		\
									_Q_CASHITEM_BUY == m_nMsgType		||		\
									_Q_CASHITEM_SHOP_OPEN == m_nMsgType	||		\
									_Q_USE_SUPER_RESTORE == m_nMsgType	||		\
									_Q_USE_NORMAL_RESTORE == m_nMsgType	||		\
									_Q_MP3_PLAYLIST_DEL == m_nMsgType	||		\
									_Q_UNIT_STOP == m_nMsgType			||		\
									_Q_MISSION_START == m_nMsgType		||		\
									_Q_DEAD_RETURN == m_nMsgType		||		\
									_Q_SKILL_CALLOFHERO == m_nMsgType	||		\
									_Q_EVENT_CALL_WARP_REQUEST == m_nMsgType ||	\
									_Q_BAZAAR_OPEN_SHOP_END == m_nMsgType ||	\
									_Q_BAZAAR_SELL_OK == m_nMsgType		||		\
									_Q_BAZAAR_BUY_OK == m_nMsgType		||		\
									_Q_USEITEM_KILL_MARK == m_nMsgType	||		\
									_Q_QUEST_REQUEST_PARTY_WARP == m_nMsgType ||\
									_Q_UPDATE_SUBLEADER_1 == m_nMsgType	||		\
									_Q_UPDATE_SUBLEADER_2 == m_nMsgType	||		\
									_Q_ARENA_WARP == m_nMsgType			||		\
									_Q_TUTORIAL_START == m_nMsgType		||		\
									_Q_SECOND_PASS_CANCEL_MSG== m_nMsgType ||	\
									_Q_POLL_CANDIDATE_VOTE == m_nMsgType||		\
									_Q_POLL_CANDIDATE_DELETE == m_nMsgType ||	\
									_Q_GIFT_ITEM == m_nMsgType			||	\
									_Q_GUILD_GIVE_SUBLEADER == m_nMsgType||	\
									_Q_GUILD_FALL_SUBLEADER == m_nMsgType||	\
									_Q_GUILD_CHARGE_LEADER == m_nMsgType||	\
									_Q_GUILD_REQUEST == m_nMsgType||	\
									_Q_GUILD_REQUEST_CANCEL == m_nMsgType ||	\
									_Q_CHATROOM_INVITE_FROM == m_nMsgType ||	\
									_Q_CHATROOM_OUT == m_nMsgType			|| \
									_Q_MISSION_MASTER_CANCEL == m_nMsgType	||	\
									_Q_MISSION_MASTER_HELPER == m_nMsgType	||	\
									_Q_FRIEND_LIST_INSERT == m_nMsgType		||	\
									_Q_WAR_DECLARE_GIVE_UP == m_nMsgType	||	\
									_Q_WAR_DECLARE == m_nMsgType			||	\
									_Q_GUILD_CREATE_CONFIRM == m_nMsgType	||	\
									_Q_CREATE_NICKNAME_OKCANCEL == m_nMsgType	||	\
									_Q_MULTI_SEL_WARNING== m_nMsgType		||	\
									_Q_INFINITY_GIVE_UP == m_nMsgType		||	\
									_Q_BUY_INFINITYSHOP_ITEM == m_nMsgType	||	\
									_Q_INFINITY_RETURN_TO_CITY == m_nMsgType||	\
									_Q_RETURN_TO_PROGRESS_INFINITY	== m_nMsgType	||	\
									_Q_PARTNER_NAME_OKCANCLE == m_nMsgType			||	\
									_Q_INVEN_ITEM_SORT == m_nMsgType		||	\
									_Q_INCHANT_ITEM_DELETE == m_nMsgType		||	\
									_Q_SETTING_SOCKET_OKCANCLE == m_nMsgType	||	\
									_Q_USEITEM_NATION_CHANGE == m_nMsgType		// 2015-12-17 Future, Nation Change Card
																

#define	OK_BUTTON					_MESSAGE == m_nMsgType				||		\
									_MESSAGE_ERROR_CREATE == m_nMsgType	||		\
									_MESSAGE_ERROR_NETWORK == m_nMsgType||		\
									_Q_VOIP_USING == m_nMsgType			||		\
									_Q_AGEAR_FUEL_ALLIN == m_nMsgType	||		\
									_Q_VOIP_MENU == m_nMsgType			||		\
									_Q_VOIP_ONE_NAME == m_nMsgType		||		\
									_Q_FUELALLIN_DEAD_RETURN == m_nMsgType ||	\
									_Q_INFLUENCEMAP_DEAD_RETURN == m_nMsgType || \
									_Q_BAZAAR_INVALID_SHOP_END == m_nMsgType ||	\
									_Q_ARENA_RESTART == m_nMsgType			||	\
									_Q_GIFT_ITEM_RING_IN == m_nMsgType		||	\
									_Q_COUPON == m_nMsgType					||	\
									_Q_ALREADY_HAVE_ITEM == m_nMsgType		||	\
									_Q_ENCHANT_PREVENTION	==	m_nMsgType	||  \
									_Q_DIS_BOOM ==	m_nMsgType	||	\
									_Q_APPEARANCE_CHANGE_PREVENTION == m_nMsgType
									// 2012-10-30 by mspark, ���� ���� ��� �޽��� �߰�
									
//

#define	CANCEL_BUTTON				_Q_USE_ENCHANT_ITEM_CARD == m_nMsgType ||	\
									_Q_QUIT_MESSAGE == m_nMsgType			||	\
									_Q_AUTO_KICK == m_nMsgType

//
#define INPUT_MSG_BUTTON			_Q_PARTY_INVITE_USER == m_nMsgType ||		\
									_Q_TRADE_INPUT_NAME == m_nMsgType	||		\
									_Q_GUILD_CREATE == m_nMsgType		||		\
									_Q_GUILD_INVITE == m_nMsgType		||		\
									_Q_GUILD_MARK == m_nMsgType			||		\
									_Q_BATTLE_NAME == m_nMsgType		||		\
									_Q_VOIP_NAME == m_nMsgType			||		\
									_Q_ADD_FRIEND == m_nMsgType			||		\
									_Q_INPUT_AUCTION_PRICE == m_nMsgType||		\
									_Q_ADD_REJECT == m_nMsgType			||		\
									_Q_GREATING_SET == m_nMsgType		||		\
									_Q_SELECT_DELETE == m_nMsgType		||		\
									_Q_INPUT_SERIAL_NUM == m_nMsgType	||		\
									_Q_SUPER_RESTORE == m_nMsgType		||		\
									_Q_MEMBER_SUMMON == m_nMsgType		||		\
									_Q_MP3_DIRECTORY == m_nMsgType		||		\
									_Q_USEITEM_NAME_CHANGE == m_nMsgType||		\
									_Q_ARENA_PASSWORD == m_nMsgType		||		\
									_Q_USEITEM_SPEAKER_MSG == m_nMsgType||		\
									_Q_GIFT_CHARACTER_TEXT == m_nMsgType||		\
									_Q_PARTY_JOIN_PASSWORD == m_nMsgType||		\
									_Q_CHATROOM_INVITE == m_nMsgType	||		\
									_Q_CHATROOM_PASSWORD == m_nMsgType  ||		\
									_Q_GUILD_BATTLE		==	m_nMsgType	||		\
									_Q_PARTY_BATTLE		==	m_nMsgType	||		\
									_Q_JOYSTICK_SETUP	== m_nMsgType	||		\
									_Q_USEITEM_LEADER_BAN_CHAT == m_nMsgType ||		\
									_Q_CREATE_NICKNAME== m_nMsgType		||		\
									_Q_PARTNER_NEW_NAME_CHANGE == m_nMsgType
									

//
#define INPUT_COUNT_BUTTON			_Q_SHOP_SELL_ENERGY == m_nMsgType	||		\
									_Q_STORE_PUT_COUNTABLE_ITEM == m_nMsgType || \
									_Q_ITEM_DELETE_NUM == m_nMsgType	||		\
									_Q_TRADE_ITEM_NUMBER == m_nMsgType  ||		\
									_Q_PUT_ITEM_SPI == m_nMsgType		||		\
									_Q_GET_ITEM_SPI == m_nMsgType		||		\
									_Q_INPUT_AUCTION_PRICE == m_nMsgType||		\
									_Q_STORE_PUSH_ITEM	 == m_nMsgType	||		\
									_Q_TEX_SET == m_nMsgType			||		\
									_Q_DATE_WAR == m_nMsgType			||		\
									_Q_LAB_ITEM_NUMBER == m_nMsgType	||		\
									_Q_INFLUENCE_WAR_EXPENCE_OK_MSG == m_nMsgType	
//
#define INPUT_RADIO_BUTTON			_Q_PART_STAT_RESET == m_nMsgType

// SINGLE_MSGBOX�� �� ���� COMPARE_SINGLE_MSGBOX���� �־�� �Ѵ�.
#define SINGLE_MSGBOX				_Q_TRADE_INPUT_NAME == nType		||		\
									_Q_USE_ENCHANT_ITEM_CARD == nType	||		\
									_Q_ITEM_DELETE_NUM == nType			||		\
									_Q_ITEM_DELETE == nType				||		\
									_Q_GUILD_CREATE == nType			||		\
									_Q_GUILD_LEAVE == nType				||		\
									_Q_GUILD_DISBAND == nType			||		\
									_Q_GUILD_CANCEL == nType			||		\
									_Q_GUILD_INVITE == nType			||		\
									_Q_GUILD_MARK == nType				||		\
									_Q_BATTLE_NAME == nType				||		\
									_Q_OUTDOOR_WARP == nType			||		\
									_MESSAGE_ERROR_NETWORK == nType		||		\
									_Q_QUEST_DISCARD == nType			||		\
									_Q_VOIP_NAME == nType				||		\
									_Q_PARTYMASTER_VOIP == nType		||		\
									_Q_GUILDMASTER_VOIP == nType		||		\
									_Q_PUT_ITEM_SPI == nType			||		\
									_Q_GET_ITEM_SPI == nType			||		\
									_Q_LAB_ITEM_NUMBER == nType			||		\
									_Q_ADD_FRIEND == nType				||		\
									_Q_DELETE_FRIEND == nType			||		\
									_Q_ADD_REJECT == nType				||		\
									_Q_ITEM_DELETE_SKILL == nType		||		\
									_Q_DELETE_REJECT == nType			||		\
									_Q_GUILD_VOIP_END	== nType		||		\
									_Q_PARTY_VOIP_END	== nType		||		\
									_Q_VOIP_USING	== nType			||		\
									_Q_TEX_SET	== nType				||		\
									_Q_DATE_WAR	== nType				||		\
									_Q_GREATING_SET	== nType			||		\
									_Q_STORE_USE 	== nType			||		\
									_Q_GET_TEX 	== nType				||		\
									_Q_CASHITEM_BUY == nType			||		\
									_Q_CASHITEM_SHOP_OPEN == nType		||		\
									_Q_SELECT_DELETE == nType			||		\
									_Q_SUPER_RESTORE == nType			||		\
									_Q_MP3_DIRECTORY == nType			||		\
									_Q_MP3_PLAYLIST_DEL == nType		||		\
									_Q_QUIT_MESSAGE == nType			||		\
									_Q_USEITEM_NAME_CHANGE == nType		||		\
									_Q_UNIT_STOP == nType				||		\
									_Q_MISSION_START == nType			||		\
									_Q_VOIP_MENU == nType				||		\
									_Q_VOIP_ONE_NAME == nType			||		\
									_Q_BAZAAR_OPEN_SHOP_END == nType	||		\
									_Q_BAZAAR_SELL_OK == nType			||		\
									_Q_BAZAAR_BUY_OK == nType			||		\
									_Q_USEITEM_KILL_MARK == nType		||		\
									_Q_QUEST_REQUEST_PARTY_WARP == nType||		\
									_Q_UPDATE_SUBLEADER_1 == nType		||		\
									_Q_UPDATE_SUBLEADER_2 == nType		||		\
									_Q_ARENA_PASSWORD == nType			||		\
									_Q_TUTORIAL_START == nType			||		\
									_Q_USEITEM_SPEAKER_MSG == nType		||		\
									_Q_INFLUENCE_WAR_EXPENCE_OK_MSG == nType		||		\
									_Q_GIFT_CHARACTER_TEXT ==	nType ||	\
									_Q_SECOND_PASS_CANCEL_MSG== nType	||		\
									_Q_POLL_CANDIDATE_VOTE == nType	||			\
									_Q_POLL_CANDIDATE_DELETE == nType		||	\
									_Q_GIFT_ITEM == nType					||	\
									_Q_GIFT_ITEM_RING_IN == nType			|| \
									_Q_GIFT_CHARACTER_TEXT == nType			|| \
									_Q_PARTY_JOIN_PASSWORD == nType			||	\
									_Q_CHATROOM_PASSWORD ==nType			||	\
									_Q_CHATROOM_INVITE_FROM == nType		||	\
									_Q_GUILD_BATTLE == nType				||  \
									_Q_PARTY_BATTLE == nType				||  \
									_Q_JOYSTICK_SETUP== nType				||  \
									_Q_MISSION_MASTER_CANCEL== nType		||	\
									_Q_MISSION_MASTER_HELPER == nType		||	\
									_Q_USEITEM_LEADER_BAN_CHAT == nType		||	\
									_Q_PARTNER_NEW_NAME_CHANGE == nType		||	\
									_Q_INVEN_ITEM_SORT == nType				||	\
									_Q_INCHANT_ITEM_DELETE == nType			||	\
									_Q_AUTO_KICK == nType					||	\
									_Q_USEITEM_NATION_CHANGE == nType  			// 2015-12-17 Future, Nation Change Card

#define COMPARE_SINGLE_MSGBOX		_Q_TRADE_INPUT_NAME == (*it)->m_nMsgType	||\
									_Q_USE_ENCHANT_ITEM_CARD == (*it)->m_nMsgType || \
									_Q_ITEM_DELETE_NUM == (*it)->m_nMsgType		|| \
									_Q_ITEM_DELETE == (*it)->m_nMsgType			|| \
									_Q_GUILD_CREATE == (*it)->m_nMsgType		|| \
									_Q_GUILD_LEAVE == (*it)->m_nMsgType			|| \
									_Q_GUILD_DISBAND == (*it)->m_nMsgType		|| \
									_Q_GUILD_CANCEL == (*it)->m_nMsgType		|| \
									_Q_GUILD_INVITE == (*it)->m_nMsgType		|| \
									_Q_GUILD_MARK == (*it)->m_nMsgType			|| \
									_Q_BATTLE_NAME == (*it)->m_nMsgType			|| \
									_Q_OUTDOOR_WARP == (*it)->m_nMsgType		|| \
									_MESSAGE_ERROR_NETWORK == (*it)->m_nMsgType || \
									_Q_QUEST_DISCARD == (*it)->m_nMsgType		|| \
									_Q_VOIP_NAME == (*it)->m_nMsgType			|| \
									_Q_PARTYMASTER_VOIP == (*it)->m_nMsgType	|| \
									_Q_GUILDMASTER_VOIP == (*it)->m_nMsgType	|| \
									_Q_PUT_ITEM_SPI == (*it)->m_nMsgType		|| \
									_Q_GET_ITEM_SPI == (*it)->m_nMsgType		|| \
									_Q_LAB_ITEM_NUMBER == (*it)->m_nMsgType		|| \
									_Q_ADD_FRIEND == (*it)->m_nMsgType			|| \
									_Q_DELETE_FRIEND == (*it)->m_nMsgType		|| \
									_Q_ADD_REJECT == (*it)->m_nMsgType			|| \
									_Q_ITEM_DELETE_SKILL == (*it)->m_nMsgType	|| \
									_Q_DELETE_REJECT == (*it)->m_nMsgType		|| \
									_Q_GUILD_VOIP_END	== (*it)->m_nMsgType	|| \
									_Q_PARTY_VOIP_END	== (*it)->m_nMsgType	|| \
									_Q_VOIP_USING	== (*it)->m_nMsgType		|| \
									_Q_TEX_SET	== (*it)->m_nMsgType			|| \
									_Q_DATE_WAR	== (*it)->m_nMsgType			|| \
									_Q_GREATING_SET == (*it)->m_nMsgType		|| \
									_Q_STORE_USE  == (*it)->m_nMsgType			|| \
									_Q_GET_TEX  == (*it)->m_nMsgType			|| \
									_Q_CASHITEM_BUY  == (*it)->m_nMsgType		|| \
									_Q_CASHITEM_SHOP_OPEN  == (*it)->m_nMsgType || \
									_Q_SELECT_DELETE  == (*it)->m_nMsgType		|| \
									_Q_SUPER_RESTORE == (*it)->m_nMsgType		|| \
									_Q_MP3_DIRECTORY == (*it)->m_nMsgType		|| \
									_Q_MP3_PLAYLIST_DEL == (*it)->m_nMsgType	|| \
									_Q_QUIT_MESSAGE == (*it)->m_nMsgType		|| \
									_Q_USEITEM_NAME_CHANGE == (*it)->m_nMsgType || \
									_Q_UNIT_STOP == (*it)->m_nMsgType			|| \
									_Q_MISSION_START == (*it)->m_nMsgType		|| \
									_Q_VOIP_MENU == (*it)->m_nMsgType			|| \
									_Q_VOIP_ONE_NAME == (*it)->m_nMsgType		|| \
									_Q_BAZAAR_OPEN_SHOP_END == (*it)->m_nMsgType || \
									_Q_BAZAAR_SELL_OK == (*it)->m_nMsgType		|| \
									_Q_BAZAAR_BUY_OK == (*it)->m_nMsgType		|| \
									_Q_USEITEM_KILL_MARK == (*it)->m_nMsgType	|| \
									_Q_QUEST_REQUEST_PARTY_WARP == (*it)->m_nMsgType || \
									_Q_UPDATE_SUBLEADER_1 == (*it)->m_nMsgType	||	\
									_Q_UPDATE_SUBLEADER_2 == (*it)->m_nMsgType	||	\
									_Q_ARENA_PASSWORD == (*it)->m_nMsgType		|| \
									_Q_TUTORIAL_START == (*it)->m_nMsgType		|| \
									_Q_USEITEM_SPEAKER_MSG == (*it)->m_nMsgType		|| \
									_Q_INFLUENCE_WAR_EXPENCE_OK_MSG== (*it)->m_nMsgType|| \
									_Q_SECOND_PASS_CANCEL_MSG== (*it)->m_nMsgType ||	\
									_Q_POLL_CANDIDATE_VOTE == (*it)->m_nMsgType		||	\
									_Q_POLL_CANDIDATE_DELETE == (*it)->m_nMsgType		||	\
									_Q_GIFT_ITEM == (*it)->m_nMsgType					||	\
									_Q_GIFT_ITEM_RING_IN == (*it)->m_nMsgType			||	\
									_Q_GIFT_CHARACTER_TEXT == (*it)->m_nMsgType			||  \
									_Q_PARTY_JOIN_PASSWORD == (*it)->m_nMsgType			||	\
									_Q_CHATROOM_PASSWORD == (*it)->m_nMsgType			||	\
									_Q_GUILD_BATTLE == (*it)->m_nMsgType				||  \
									_Q_PARTY_BATTLE == (*it)->m_nMsgType				||  \
									_Q_JOYSTICK_SETUP== (*it)->m_nMsgType				||	\
									_Q_MISSION_MASTER_CANCEL== (*it)->m_nMsgType		||	\
									_Q_MISSION_MASTER_HELPER == (*it)->m_nMsgType		||	\
									_Q_USEITEM_LEADER_BAN_CHAT == (*it)->m_nMsgType		||	\
									_Q_GUILD_CREATE_CONFIRM == (*it)->m_nMsgType		||	\
									_Q_CREATE_NICKNAME_OKCANCEL == (*it)->m_nMsgType	||	\
									_Q_CREATE_NICKNAME== (*it)->m_nMsgType				||	\
									_Q_PARTNER_NEW_NAME_CHANGE == (*it)->m_nMsgType		||	\
									_Q_PARTNER_NAME_OKCANCLE == (*it)->m_nMsgType		||	\
									_Q_ENCHANT_PREVENTION	==	(*it)->m_nMsgType		||	\
									_Q_DIS_BOOM				==	(*it)->m_nMsgType		||	\
									_Q_INVEN_ITEM_SORT == (*it)->m_nMsgType				||	\
									_Q_APPEARANCE_CHANGE_PREVENTION == (*it)->m_nMsgType ||  \
									_Q_INCHANT_ITEM_DELETE == (*it)->m_nMsgType






// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
#define NOBUTTON_MSGBOX				_Q_REVIVE_WAIT_5SECOND




// 2007-11-12 by bhsohn ĳ�������� �޽��� �ڽ� ó��
// ������ ����̳�?
#define	IS_BOLD_BK					_Q_CASHITEM_BUY == m_nMsgType		||		\
									_Q_GIFT_CHARACTER_TEXT ==	m_nMsgType ||	\
									_Q_GIFT_ITEM ==	m_nMsgType


// 2007-11-15 by dgwoo �۾��� ����ü���� ���.
#define IS_BOLD						_Q_CASHITEM_BUY == m_nMsgType		||		\
									_Q_GIFT_ITEM == m_nMsgType
									


#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
// ĳ���� ���� �ÿ� ��Ÿ���� �޽���(�����ϴ� �̸�, �߸��� �̸�, �̸��� �Է��ϼ���)
#define ALL_BOX_SIZE_X				125
#define ALL_BOX_SIZE_Y				19
#define ALL_BOX_START_X				(m_nX+(m_nCx/2 - ALL_BOX_SIZE_X/2))
#define ALL_BOX_START_Y				(m_nY+43)
	#define ALL_TEXT_START_X			(ALL_BOX_START_X+70)
	#define ALL_UP_START_X				(ALL_BOX_START_X+77)
	#define ALL_UP_START_Y				(ALL_BOX_START_Y+3)
	#define ALL_DOWN_START_X			(ALL_BOX_START_X+77)
	#define ALL_DOWN_START_Y			(ALL_BOX_START_Y+17)
	#define ALL_UPDOWN_SIZE_X			9
	#define ALL_UPDOWN_SIZE_Y			7
	#define ALL_BUTTON_START_X			(ALL_BOX_START_X+90)
	#define ALL_BUTTON_START_Y			(ALL_BOX_START_Y+1)

	#define ALL_BUTTON_SIZE_X			22
	#define ALL_BUTTON_SIZE_Y			22
#else
	#define ALL_BOX_SIZE_X				125
	#define ALL_BOX_SIZE_Y				19
	#define ALL_BOX_START_X				(m_nX+(m_nCx/2 - ALL_BOX_SIZE_X/2))
	#define ALL_BOX_START_Y				(m_nY+43)
#define ALL_TEXT_START_X			(ALL_BOX_START_X+6)
#define ALL_UP_START_X				(ALL_BOX_START_X+79)
#define ALL_UP_START_Y				(ALL_BOX_START_Y+1)
#define ALL_DOWN_START_X			(ALL_BOX_START_X+79)
#define ALL_DOWN_START_Y			(ALL_BOX_START_Y+11)
#define ALL_UPDOWN_SIZE_X			9
#define ALL_UPDOWN_SIZE_Y			7
#define ALL_BUTTON_START_X			(ALL_BOX_START_X+90)
#define ALL_BUTTON_START_Y			(ALL_BOX_START_Y+1)

#define ALL_BUTTON_SIZE_X			33
#define ALL_BUTTON_SIZE_Y			17
#endif

#define COUNT_ITEM_MAX_NUMBER		11
#define MESSAGE_STRING_LENGTH		400							// �޼��� �ִ� �ȼ�
#define MESSAGE_FONT_LINE_HEIGHT	15							// �� ������ ����

#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
// 2006-03-07 by ispark, �� ���� ��ġ ����
#if defined(LANGUAGE_ENGLISH) || defined(LANGUAGE_VIETNAM)|| defined(LANGUAGE_THAI)// 2008-04-30 by bhsohn �±� ���� �߰�
#define ALL_TEXT_START_Y			(ALL_BOX_START_Y+6)//4)
#define STRING_CULL ::StringCullingUserData_ToBlank
#else
#define STRING_CULL ::StringCullingUserDataEx
#define ALL_TEXT_START_Y			(ALL_BOX_START_Y+6)//4)
#endif
#else
// 2006-03-07 by ispark, �� ���� ��ġ ����
#if defined(LANGUAGE_ENGLISH) || defined(LANGUAGE_VIETNAM)|| defined(LANGUAGE_THAI)// 2008-04-30 by bhsohn �±� ���� �߰�
#define ALL_TEXT_START_Y			(ALL_BOX_START_Y+1)//4)
#define STRING_CULL ::StringCullingUserData_ToBlank
#else
#define STRING_CULL ::StringCullingUserDataEx
#define ALL_TEXT_START_Y			(ALL_BOX_START_Y+1)//4)
#endif
#endif

// 2007-03-26 by bhsohn �޼��� �ڽ��� �ʹ� �۰� ������ ���� ó��
#define	MIN_MSGBOX_WIDTH			150

// 2013-04-05 by bhsohn ������ 5�� ��Ȱ �ý��� �߰�
#define HELLMAP_ALLTIME_DEADMSG_LIVETIME		(300.0f)

CINFMessageBox::CINFMessageBox(CAtumNode* pParent)
{
	FLOG( "CINFMessageBox(CAtumNode* pParent)" );
	m_nMsgType = 0;
	m_nX = g_pD3dApp->GetBackBufferDesc().Width/2-50;
	m_nY = g_pD3dApp->GetBackBufferDesc().Height/2-50;
	m_nCx = 50;
	m_nCy = 50;
	m_pFontMessage = NULL;
	m_pFontInput[0] = NULL;
	m_pFontInput[1] = NULL;

	// 2005-05-09 by jschoi - �ʱ�ȭ �ʿ�
	// 2013-02-13 by mspark, ä��â�� ���� ���� Ư�� ��Ȳ���� ������� ���� �ذ� - �ʱ�ȭ �κ� �ּ�
	//memset(g_pD3dApp->m_inputkey.m_full_str,0x00,SIZE_MAX_CHAT_MESSAGE);
	//g_pD3dApp->m_inputkey.m_str_pos = 0;
	// end 2013-02-13 by mspark, ä��â�� ���� ���� Ư�� ��Ȳ���� ������� ���� �ذ� - �ʱ�ȭ �κ� �ּ�

	memset(m_strInputMessage, 0x00, sizeof(m_strInputMessage));
	memset(m_strMessage,0x00,sizeof(m_strMessage));
	memset(m_strTimeMessage1,0x00,sizeof(m_strTimeMessage1)); // 2013-04-05 by bhsohn ������ 5�� ��Ȱ �ý��� �߰�
	m_pParent = pParent;
	m_nButtonState[0] = BUTTON_STATE_NORMAL;
	m_nButtonState[1] = BUTTON_STATE_NORMAL;
	m_bLockWindow = FALSE;
	m_ptMouse.x = 0; m_ptMouse.y = 0;
	m_strInputMessage[0] = '_';
	m_dwData = 0;
	m_nAllButtonState = 0;
	// 2004-10-18 by jschoi ����� Ŭ���̾�Ʈ ����
	if(g_pD3dApp->m_pSound && g_pShuttleChild)
	{
		g_pD3dApp->m_pSound->PlayD3DSound(SOUND_OPEN_MESSAGE_BOX, g_pShuttleChild->m_vPos, FALSE);
	}
	m_nAllCurrentData = 0;
	m_nAllNumber = 0;
	
	// ���� ��ư ����
	m_nRadioCount = 0;
	m_nSelectRadio = -1;
	m_pFontRadio = NULL;

	// 2007-10-16 by bhsohn Ư�� �۾��� ����� ó��
	m_pFontBold = NULL;

	// 2013-04-23 by ssjung �߿� ������ ������ 2�� ���(����) �˾�â ����
	m_isWillbeDelete = FALSE;
}

CINFMessageBox::~CINFMessageBox()
{
	FLOG( "~CINFMessageBox()" );
	// 2004-10-18 by jschoi ����� Ŭ���̾�Ʈ ����
	if(g_pD3dApp->m_pSound && g_pShuttleChild)
	{
		g_pD3dApp->m_pSound->PlayD3DSound(SOUND_CLOSE_MESSAGE_BOX, g_pShuttleChild->m_vPos, FALSE);
	}
	util::del(m_pFontMessage);
	util::del(m_pFontInput[0]);
	util::del(m_pFontInput[1]);
	util::del(m_pFontRadio);

	// 2007-10-16 by bhsohn Ư�� �۾��� ����� ó��
	util::del(m_pFontBold);	
}

void CINFMessageBox::SetPos(int x, int y, int cx, int cy)
{
	FLOG( "CINFMessageBox::SetPos(int x, int y, int cx, int cy)" );
	m_nX = x;
	m_nY = y;
	m_nCx = cx;
	m_nCy = cy;
}
void CINFMessageBox::SetInputStrName(char * strName)
{
	ClearMessageBoxString();
	strcpy(m_strInputMessage,strName);
}

// 2013-06-26 by bhsohn �Ƹ� �÷��� �߰� ����
//void CINFMessageBox::SetText(char* strText, int nMsgType)
void CINFMessageBox::SetText(char* strText, int nMsgType, BOOL bChRtn/*=FALSE*/)
{
	FLOG( "CINFMessageBox::SetText(char* strText, int nMsgType)" );
	int sizeX = 0;
	char strMessageTemp[1024] = {0,};

	char strMessageTemp1[1024] = {0,}; // 2013-04-05 by bhsohn ������ 5�� ��Ȱ �ý��� �߰�
	// 2006-07-24 by ispark, �ð� ������ �ִٸ�, ��Ʈ�� �߰�
	if(m_fLiveTime)
	{
// 2007-05-15 by dgwoo Ȯ�强 �ֵ��� �Ʒ��� ���� ����.
//		char strTime[256] = {0,};
//		sprintf(strTime, STRMSG_C_060724_0000, (int)(m_fLiveTime) + 1);
//		sprintf(strMessageTemp, "%s %s", strText, strTime);
		
		// 2013-04-05 by bhsohn ������ 5�� ��Ȱ �ý��� �߰�
// 		char strTime[256] = {0,};
// 		sprintf(strTime, m_strTimeMessage, (int)(m_fLiveTime) + 1);
// 		sprintf(strMessageTemp, "%s %s", strText, strTime);
		char strTime[256] = {0,};
		if(strlen(m_strTimeMessage) > 0)
		{			
			sprintf(strTime, m_strTimeMessage, (int)(m_fLiveTime) + 1);			
		}
		sprintf(strMessageTemp, "%s %s", strText, strTime);		

		if(strlen(m_strTimeMessage1) > 0)
		{
			sprintf(strMessageTemp1, m_strTimeMessage1, (int)(m_fLiveTime) + 1);
		}
		// END 2013-04-05 by bhsohn ������ 5�� ��Ȱ �ý��� �߰�
	}
	else
	{
		sprintf(strMessageTemp, "%s", strText);		
	}

	sprintf(m_strMessage, "%s", strText);		

	m_nMsgType = nMsgType;
	// 2009-02-03 by bhsohn â�� �ñ涧 ����Ʈ ���� 1�� ����
	if(INPUT_COUNT_BUTTON)
	{
		m_nAllCurrentData = 1;
		char chBuffTmp[256];
		ZERO_MEMORY(chBuffTmp);					
		wsprintf(chBuffTmp,"%d", m_nAllCurrentData);
		strncpy(m_strInputMessage, chBuffTmp, strlen(chBuffTmp)+1);
		m_strInputMessage[strlen(m_strInputMessage)] = '_';
		m_strInputMessage[strlen(m_strInputMessage)+1] = '\0';

	}
	// end 2009-02-03 by bhsohn â�� �ñ涧 ����Ʈ ���� 1�� ����

	// 2006-10-16 by ispark, ��Ʈ�� �ڸ���
	vector<string> vecstrTotalMessage;
	vecstrTotalMessage.clear();
	if(0 < strlen(strMessageTemp))
	{
		STRING_CULL(strMessageTemp, MESSAGE_STRING_LENGTH, &vecstrTotalMessage, m_pFontInput[1], bChRtn); // 2013-06-26 by bhsohn �Ƹ� �÷��� �߰� ����
	}
	// 2013-04-05 by bhsohn ������ 5�� ��Ȱ �ý��� �߰�
	if(strlen(strMessageTemp1) > 0)
	{
		STRING_CULL(strMessageTemp1, MESSAGE_STRING_LENGTH, &vecstrTotalMessage, m_pFontInput[1], bChRtn);	// 2013-06-26 by bhsohn �Ƹ� �÷��� �߰� ����
	}
	// END 2013-04-05 by bhsohn ������ 5�� ��Ȱ �ý��� �߰�

	// 2006-03-06 by ispark, ���� ���� ��������
	// 2006-10-16 by ispark, ���� ���� ���� ��� ��������
	int nMaxSize = 0;
	for(int i = 0; i < vecstrTotalMessage.size(); i++)
	{
		int nTempSizeX;
		if(IS_BOLD)
		{
			nTempSizeX = m_pFontBold->GetStringSize((char*)vecstrTotalMessage[i].c_str()).cx;
		}
		else
		{
			nTempSizeX = m_pFontMessage->GetStringSize((char*)vecstrTotalMessage[i].c_str()).cx;
		}
		if(nMaxSize < nTempSizeX)
		{
			nMaxSize = nTempSizeX;
		}
	}
	// 2007-03-26 by bhsohn �޼��� �ڽ��� �ʹ� �۰� ������ ���� ó��
	if(nMaxSize < MIN_MSGBOX_WIDTH)
	{
		nMaxSize =  MIN_MSGBOX_WIDTH;
	}
	// end 2007-03-26 by bhsohn �޼��� �ڽ��� �ʹ� �۰� ������ ���� ó��

	// â ����
	sizeX += nMaxSize;
	if(m_nCx < sizeX+19*2)
		m_nCx = sizeX+19*2;
	m_nX = g_pD3dApp->GetBackBufferDesc().Width/2-m_nCx/2;

	if (INPUT_MSG_BUTTON)
	{

		if (m_nCy < 19*3 + 22)
			m_nCy = 19*3 + 22;
		m_nCy = m_nCy + (SIZE_MSGBOX_BUTTON_Y * vecstrTotalMessage.size());
		m_nY = g_pD3dApp->GetBackBufferDesc().Height/2-m_nCy/2;
		g_pD3dApp->m_bChatMode = TRUE;

	}
	else if(INPUT_COUNT_BUTTON)
	{
		if(m_nCy < 19*3 + SIZE_MSGBOX_BUTTON_Y + 30)
			m_nCy = 19*3 + SIZE_MSGBOX_BUTTON_Y + 30;
		m_nY = g_pD3dApp->GetBackBufferDesc().Height/2-m_nCy/2;
		g_pD3dApp->m_bChatMode = TRUE;
	}
	else if(INPUT_RADIO_BUTTON)
	{
		// ���� ��ư ������ ���� ������ ������
		m_nRadioCount = ((CINFWindow*)m_pParent)->m_vecRadioString.size();
		m_nCy = (19*3 + SIZE_MSGBOX_BUTTON_Y + 35)+((m_nRadioCount/((CINFWindow*)m_pParent)->m_nRadioButtonArray)*15);		
		// ��� ������
		m_nY = g_pD3dApp->GetBackBufferDesc().Height/2-m_nCy/2;
	}
	else
	{
		if(m_nCy < 19*2 + SIZE_MSGBOX_BUTTON_Y + 22)
			m_nCy = 19*2 + SIZE_MSGBOX_BUTTON_Y + 22 + ((vecstrTotalMessage.size() - 1) * MESSAGE_FONT_LINE_HEIGHT);
		m_nY = g_pD3dApp->GetBackBufferDesc().Height/2-m_nCy/2;
	}
}

HRESULT CINFMessageBox::InitDeviceObjects()
{
	FLOG( "CINFMessageBox::InitDeviceObjects()" );
	m_pFontMessage = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE,  FALSE,1024,64);
	m_pFontMessage->InitDeviceObjects(g_pD3dDev);
	m_pFontInput[0] = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE,  FALSE,1024,64,FALSE,TRUE);
	m_pFontInput[0]->SetUV(0.0f,0.0f,67/1024.0f, 1.0f);
	m_pFontInput[0]->InitDeviceObjects(g_pD3dDev);
	
	m_pFontInput[1] = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE,  FALSE,1024,64,TRUE);
	m_pFontInput[1]->InitDeviceObjects(g_pD3dDev);
	
	m_pFontRadio = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE,  FALSE,1024,64);
	m_pFontRadio->InitDeviceObjects(g_pD3dDev);


	// 2007-10-16 by bhsohn Ư�� �۾��� ����� ó��	
	// 2008-10-22 by dgwoo �ʺ� ������ 256->1024�� ����.
	//m_pFontBold = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE|D3DFONT_BOLD,  TRUE,256,32);
	m_pFontBold = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE|D3DFONT_BOLD,  TRUE,1024,32);
	m_pFontBold->InitDeviceObjects(g_pD3dDev);

	
	return S_OK;
}

HRESULT CINFMessageBox::RestoreDeviceObjects()
{
	FLOG( "CINFMessageBox::RestoreDeviceObjects()" );
	m_pFontMessage->RestoreDeviceObjects();
	m_pFontInput[0]->RestoreDeviceObjects();
	m_pFontInput[1]->RestoreDeviceObjects();
	m_pFontRadio->RestoreDeviceObjects();
	// 2007-10-16 by bhsohn Ư�� �۾��� ����� ó��
	m_pFontBold->RestoreDeviceObjects();
	return S_OK;
}

HRESULT CINFMessageBox::DeleteDeviceObjects()
{
	FLOG( "CINFMessageBox::DeleteDeviceObjects()" );
	m_pFontMessage->DeleteDeviceObjects();
	util::del(m_pFontMessage);
	m_pFontInput[0]->DeleteDeviceObjects();
	util::del(m_pFontInput[0]);
	m_pFontInput[1]->DeleteDeviceObjects();
	util::del(m_pFontInput[1]);

	// 2007-10-16 by bhsohn Ư�� �۾��� ����� ó��
	m_pFontBold->DeleteDeviceObjects();
	util::del(m_pFontBold);	
	// end 2007-10-16 by bhsohn Ư�� �۾��� ����� ó��

	if (INPUT_MSG_BUTTON)
	{
		g_pD3dApp->m_bChatMode = FALSE;
	}
	m_pFontRadio->DeleteDeviceObjects();
	util::del(m_pFontRadio);

	return S_OK;
}

HRESULT CINFMessageBox::InvalidateDeviceObjects()
{
	FLOG( "CINFMessageBox::InvalidateDeviceObjects()" );
	m_pFontMessage->InvalidateDeviceObjects();
	m_pFontInput[0]->InvalidateDeviceObjects();
	m_pFontInput[1]->InvalidateDeviceObjects();
	m_pFontRadio->InvalidateDeviceObjects();
	// 2007-10-16 by bhsohn Ư�� �۾��� ����� ó��
	m_pFontBold->InvalidateDeviceObjects();
	return S_OK;
}

void CINFMessageBox::Render()
{
	FLOG( "CINFMessageBox::Render()" );
	// 2007-11-12 by bhsohn ĳ�������� �޽��� �ڽ� ó��
	//((CINFWindow*)m_pParent)->RenderCenterWindow(m_nX, m_nY, m_nCx, m_nCy);
	if(IS_BOLD_BK)
	{
		((CINFWindow*)m_pParent)->RenderBlackBK(m_nX, m_nY, m_nCx, m_nCy, FALSE);
	}
	else
	{
		((CINFWindow*)m_pParent)->RenderCenterWindow(m_nX, m_nY, m_nCx, m_nCy);
	}
	
	char strMsg[1024] = {0,};
	vector<string> vecstrMessage;
	// 2006-10-16 by ispark, ��Ʈ�� ���� ���� �����ϰ� �ϱ�
	if(strlen(m_strMessage))
	{
		GetMsgString(strMsg);
		if(strlen(strMsg))
		{
			
			vecstrMessage.clear();
			// 2013-06-26 by bhsohn �Ƹ� �÷��� �߰� ����
//			STRING_CULL(strMsg, MESSAGE_STRING_LENGTH, &vecstrMessage, m_pFontInput[1]);
			STRING_CULL(strMsg, MESSAGE_STRING_LENGTH, &vecstrMessage, m_pFontInput[1], TRUE);

			// 2013-04-05 by bhsohn ������ 5�� ��Ȱ �ý��� �߰�
			char strMsg1[1024] = {0,};
			GetMsg1String(strMsg1);
			STRING_CULL(strMsg1, MESSAGE_STRING_LENGTH, &vecstrMessage, m_pFontInput[1]);
			// END 2013-04-05 by bhsohn ������ 5�� ��Ȱ �ý��� �߰�

			for(int nMessageLine = 0; nMessageLine < vecstrMessage.size(); nMessageLine++)
			{
				// 2007-10-16 by bhsohn Ư�� �۾��� ����� ó��
//				m_pFontMessage->DrawText(m_nX+20, m_nY+24 + (nMessageLine * MESSAGE_FONT_LINE_HEIGHT), 
//						GUI_FONT_COLOR, (char*)vecstrMessage[nMessageLine].c_str(), 0L);
				if(IS_BOLD)
				{
					char *pTxt = (char*)vecstrMessage[nMessageLine].c_str();
					RenderCashMsgBox(m_nX+20, m_nY+24 + (nMessageLine * MESSAGE_FONT_LINE_HEIGHT), pTxt);

				}
				else
				{
					m_pFontMessage->DrawText(m_nX+20, m_nY+24 + (nMessageLine * MESSAGE_FONT_LINE_HEIGHT), 
						GUI_FONT_COLOR, (char*)vecstrMessage[nMessageLine].c_str(), 0L);
				}
				
			}
		}
	}
	if(OK_CANCEL_BUTTON)
	{
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		// ��ư : ok
		((CINFWindow*)m_pParent)->m_pOkButton[m_nButtonState[0]]->Move(m_nX+m_nCx/2-SIZE_MSGBOX_BUTTON_X-5, m_nY + m_nCy - (10+SIZE_MSGBOX_BUTTON_Y));
		((CINFWindow*)m_pParent)->m_pOkButton[m_nButtonState[0]]->Render();
		// ��ư : cancel
		((CINFWindow*)m_pParent)->m_pCancelButton[m_nButtonState[1]]->Move(m_nX+m_nCx/2+5, m_nY + m_nCy - (10+SIZE_MSGBOX_BUTTON_Y));
		((CINFWindow*)m_pParent)->m_pCancelButton[m_nButtonState[1]]->Render();
#else
		// ��ư : ok
		((CINFWindow*)m_pParent)->m_pOkButton[m_nButtonState[0]]->Move(m_nX+m_nCx/2-SIZE_MSGBOX_BUTTON_X-5, m_nY + m_nCy - (19+SIZE_MSGBOX_BUTTON_Y));
		((CINFWindow*)m_pParent)->m_pOkButton[m_nButtonState[0]]->Render();
		// ��ư : cancel
		((CINFWindow*)m_pParent)->m_pCancelButton[m_nButtonState[1]]->Move(m_nX+m_nCx/2+5, m_nY + m_nCy - (19+SIZE_MSGBOX_BUTTON_Y));
		((CINFWindow*)m_pParent)->m_pCancelButton[m_nButtonState[1]]->Render();
#endif
	}
	else if(OK_BUTTON)
	{
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		// ��ư : ok
		((CINFWindow*)m_pParent)->m_pOkButton[m_nButtonState[0]]->Move(m_nX+m_nCx/2-SIZE_MSGBOX_BUTTON_X/2, m_nY + m_nCy - (10+SIZE_MSGBOX_BUTTON_Y));
		((CINFWindow*)m_pParent)->m_pOkButton[m_nButtonState[0]]->Render();
#else
		// ��ư : ok
		((CINFWindow*)m_pParent)->m_pOkButton[m_nButtonState[0]]->Move(m_nX+m_nCx/2-SIZE_MSGBOX_BUTTON_X/2, m_nY + m_nCy - (19+SIZE_MSGBOX_BUTTON_Y));
		((CINFWindow*)m_pParent)->m_pOkButton[m_nButtonState[0]]->Render();
#endif
	}
	else if(CANCEL_BUTTON)
	{
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		// ��ư : cancel
		((CINFWindow*)m_pParent)->m_pCancelButton[m_nButtonState[1]]->Move(m_nX+m_nCx/2-SIZE_MSGBOX_BUTTON_X/2, m_nY + m_nCy - (10+SIZE_MSGBOX_BUTTON_Y));
		((CINFWindow*)m_pParent)->m_pCancelButton[m_nButtonState[1]]->Render();
#else
		// ��ư : cancel
		((CINFWindow*)m_pParent)->m_pCancelButton[m_nButtonState[1]]->Move(m_nX+m_nCx/2-SIZE_MSGBOX_BUTTON_X/2, m_nY + m_nCy - (19+SIZE_MSGBOX_BUTTON_Y));
		((CINFWindow*)m_pParent)->m_pCancelButton[m_nButtonState[1]]->Render();
#endif
	}
	else if(INPUT_MSG_BUTTON)
	{
		if(m_strInputMessage[0])
//			m_pFontInput[1]->DrawText(m_nX+20, m_nY+24+19, RGB(255, 255, 0), m_strInputMessage, 0L);
		{
			if(strlen(m_strInputMessage)<SIZE_MAX_CHAT_MESSAGE)
			{
				char chatbuf[SIZE_MAX_CHAT_MESSAGE+2];
				memset(chatbuf,0x00,SIZE_MAX_CHAT_MESSAGE+2);
				strncpy(chatbuf,m_strInputMessage,SIZE_MAX_CHAT_MESSAGE);
				chatbuf[strlen(m_strInputMessage)+1] = '\0';
				m_pFontInput[1]->SetTextureWidth(m_nCx-22);
				m_pFontInput[1]->DrawText(m_nX+20, m_nY+24+(SIZE_MSGBOX_BUTTON_Y * vecstrMessage.size()), GUI_FONT_COLOR_Y,chatbuf, 0L);
			}
		}
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		// ��ư : ok
		((CINFWindow*)m_pParent)->m_pOkButton[m_nButtonState[0]]->Move(m_nX+m_nCx/2-SIZE_MSGBOX_BUTTON_X-5, m_nY + m_nCy - (10+SIZE_MSGBOX_BUTTON_Y));
		((CINFWindow*)m_pParent)->m_pOkButton[m_nButtonState[0]]->Render();
		// ��ư : cancel
		((CINFWindow*)m_pParent)->m_pCancelButton[m_nButtonState[1]]->Move(m_nX+m_nCx/2+5, m_nY + m_nCy - (10+SIZE_MSGBOX_BUTTON_Y));
		((CINFWindow*)m_pParent)->m_pCancelButton[m_nButtonState[1]]->Render();
		if(SET_MESSAGEBOX_CANDIDATE == g_nRenderCandidate)
			g_pD3dApp->RenderCandidate(m_nX+20, m_nY+24);
				
		// 2007-05-21 by bhsohn China IME Working
		g_pD3dApp->RenderIMEType(m_nX+20, m_nY+24);
#else
		// ��ư : ok
		((CINFWindow*)m_pParent)->m_pOkButton[m_nButtonState[0]]->Move(m_nX+m_nCx/2-SIZE_MSGBOX_BUTTON_X-5, m_nY + m_nCy - (19+SIZE_MSGBOX_BUTTON_Y));
		((CINFWindow*)m_pParent)->m_pOkButton[m_nButtonState[0]]->Render();
		// ��ư : cancel
		((CINFWindow*)m_pParent)->m_pCancelButton[m_nButtonState[1]]->Move(m_nX+m_nCx/2+5, m_nY + m_nCy - (19+SIZE_MSGBOX_BUTTON_Y));
		((CINFWindow*)m_pParent)->m_pCancelButton[m_nButtonState[1]]->Render();
		if(SET_MESSAGEBOX_CANDIDATE == g_nRenderCandidate)
			g_pD3dApp->RenderCandidate(m_nX+20, m_nY+24);

		// 2007-05-21 by bhsohn China IME Working
		g_pD3dApp->RenderIMEType(m_nX+20, m_nY+24);
#endif
	}
	else if(INPUT_COUNT_BUTTON)
	{
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	((CINFWindow*)m_pParent)->m_pAllBox->Move(ALL_BOX_START_X - 2, ALL_BOX_START_Y + 1 );
		((CINFWindow*)m_pParent)->m_pAllBox->Render();
		if( m_nAllButtonState == BUTTON_STATE_DOWN )
		{
			((CINFWindow*)m_pParent)->m_pAllButton[1]->Move(ALL_BUTTON_START_X, ALL_BUTTON_START_Y);
			((CINFWindow*)m_pParent)->m_pAllButton[1]->Render();
		}
		else
		{
			((CINFWindow*)m_pParent)->m_pAllButton[0]->Move(ALL_BUTTON_START_X, ALL_BUTTON_START_Y);
			((CINFWindow*)m_pParent)->m_pAllButton[0]->Render();
		}

		if(m_strInputMessage[0])
		{
			char chatbuf[COUNT_ITEM_MAX_NUMBER];
			memset(chatbuf,0x00,COUNT_ITEM_MAX_NUMBER);
			
			if(strlen(m_strInputMessage) > COUNT_ITEM_MAX_NUMBER || m_nAllNumber < atoi(g_pD3dApp->m_inputkey.m_full_str)  )
			{
				int temp = strlen(m_strInputMessage) - COUNT_ITEM_MAX_NUMBER;
						
				strncpy(chatbuf,&m_strInputMessage[temp],COUNT_ITEM_MAX_NUMBER);
				chatbuf[COUNT_ITEM_MAX_NUMBER]='\0';
			    m_nAllCurrentData = m_nAllNumber;
				wsprintf(g_pD3dApp->m_inputkey.m_full_str, "%d", m_nAllCurrentData );
				g_pD3dApp->m_inputkey.m_str_pos = strlen(g_pD3dApp->m_inputkey.m_full_str);
				memset(m_strInputMessage,0x00,SIZE_MAX_CHAT_MESSAGE);
				strncpy(m_strInputMessage,g_pD3dApp->m_inputkey.m_full_str,strlen(g_pD3dApp->m_inputkey.m_full_str));
				m_strInputMessage[strlen(m_strInputMessage)] = '_';
				m_strInputMessage[strlen(m_strInputMessage)+1] = '\0';
			}
// 			if(strlen(m_strInputMessage) > COUNT_ITEM_MAX_NUMBER)
// 			{
// 				int temp = strlen(m_strInputMessage) - COUNT_ITEM_MAX_NUMBER;
// 				
// 				strncpy(chatbuf,&m_strInputMessage[temp],COUNT_ITEM_MAX_NUMBER);
// 				chatbuf[COUNT_ITEM_MAX_NUMBER]='\0';
// 			}
			else
			{
				strncpy(chatbuf,m_strInputMessage,COUNT_ITEM_MAX_NUMBER);
			}
			SIZE Size = m_pFontInput[0]->GetStringSize(chatbuf);
			m_pFontInput[0]->DrawText(ALL_TEXT_START_X - Size.cx, ALL_TEXT_START_Y, GUI_FONT_COLOR_Y, chatbuf, 0L);	
		}
		// ��ư : ok
		((CINFWindow*)m_pParent)->m_pOkButton[m_nButtonState[0]]->Move(m_nX+m_nCx/2-SIZE_MSGBOX_BUTTON_X-5, m_nY + m_nCy - (10+SIZE_MSGBOX_BUTTON_Y));
		((CINFWindow*)m_pParent)->m_pOkButton[m_nButtonState[0]]->Render();
		// ��ư : cancel
		((CINFWindow*)m_pParent)->m_pCancelButton[m_nButtonState[1]]->Move(m_nX+m_nCx/2+5, m_nY + m_nCy - (10+SIZE_MSGBOX_BUTTON_Y));
		((CINFWindow*)m_pParent)->m_pCancelButton[m_nButtonState[1]]->Render();

#else
		((CINFWindow*)m_pParent)->m_pAllBox->Move(ALL_BOX_START_X, ALL_BOX_START_Y );
		((CINFWindow*)m_pParent)->m_pAllBox->Render();
		if(m_nAllButtonState < 2)
		{
			((CINFWindow*)m_pParent)->m_pAllButton[m_nAllButtonState]->Move(ALL_BUTTON_START_X, ALL_BUTTON_START_Y);
			((CINFWindow*)m_pParent)->m_pAllButton[m_nAllButtonState]->Render();
		}

		if(m_strInputMessage[0])
		{
			char chatbuf[COUNT_ITEM_MAX_NUMBER];
			memset(chatbuf,0x00,COUNT_ITEM_MAX_NUMBER);
			
			if(strlen(m_strInputMessage) > COUNT_ITEM_MAX_NUMBER)
			{
				int temp = strlen(m_strInputMessage) - COUNT_ITEM_MAX_NUMBER;
				
				strncpy(chatbuf,&m_strInputMessage[temp],COUNT_ITEM_MAX_NUMBER);
				chatbuf[COUNT_ITEM_MAX_NUMBER]='\0';
			}
			else
			{
				strncpy(chatbuf,m_strInputMessage,COUNT_ITEM_MAX_NUMBER);
			}		
			m_pFontInput[0]->DrawText(ALL_TEXT_START_X, ALL_TEXT_START_Y, GUI_FONT_COLOR_Y, chatbuf, 0L);			
		}
		// ��ư : ok
		((CINFWindow*)m_pParent)->m_pOkButton[m_nButtonState[0]]->Move(m_nX+m_nCx/2-SIZE_MSGBOX_BUTTON_X-5, m_nY + m_nCy - (19+SIZE_MSGBOX_BUTTON_Y));
		((CINFWindow*)m_pParent)->m_pOkButton[m_nButtonState[0]]->Render();
		// ��ư : cancel
		((CINFWindow*)m_pParent)->m_pCancelButton[m_nButtonState[1]]->Move(m_nX+m_nCx/2+5, m_nY + m_nCy - (19+SIZE_MSGBOX_BUTTON_Y));
		((CINFWindow*)m_pParent)->m_pCancelButton[m_nButtonState[1]]->Render();
#endif
	}
	else if(INPUT_RADIO_BUTTON)
	{
		// ���� ��ư
		BOOL bTemp = TRUE;
		int  nTemp = 0;
		int bSelect = 1;
		for(int i=0; i<m_nRadioCount; i++)
		{
//			for(int j=0; j<m_nRadioButtonArray; j++)
			{
				// ���� ���� ��ư�� ���� 2���� ���� ���� ��ġ ����
				if(i == m_nSelectRadio)
					bSelect = 0;
				else
					bSelect = 1;

				if(bTemp)
				{
					((CINFWindow*)m_pParent)->m_pRadioButton[bSelect]->Move(m_nX+25,
						m_nY+RADIO_BUTTON_Y+nTemp);
					((CINFWindow*)m_pParent)->m_pRadioButton[bSelect]->Render();
					bTemp = !bTemp;
					m_pFontRadio->DrawText(m_nX+45, m_nY+RADIO_BUTTON_Y+nTemp, GUI_FONT_COLOR, 
						(char*)((CINFWindow*)m_pParent)->m_vecRadioString[i].c_str());
					
				}
				else
				{
					((CINFWindow*)m_pParent)->m_pRadioButton[bSelect]->Move((m_nX+m_nCx/2)+5,
						m_nY+RADIO_BUTTON_Y+nTemp);
					((CINFWindow*)m_pParent)->m_pRadioButton[bSelect]->Render();
					m_pFontRadio->DrawText((m_nX+m_nCx/2)+25, m_nY+RADIO_BUTTON_Y+nTemp, GUI_FONT_COLOR, 
						(char*)((CINFWindow*)m_pParent)->m_vecRadioString[i].c_str());

					bTemp = !bTemp;
					nTemp = nTemp+17;
				}				
			}			
		}		
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����		
		// ��ư : ok
		((CINFWindow*)m_pParent)->m_pOkButton[m_nButtonState[0]]->Move(m_nX+m_nCx/2-SIZE_MSGBOX_BUTTON_X-5, m_nY + m_nCy - (10+SIZE_MSGBOX_BUTTON_Y));
		((CINFWindow*)m_pParent)->m_pOkButton[m_nButtonState[0]]->Render();
		// ��ư : cancel
		((CINFWindow*)m_pParent)->m_pCancelButton[m_nButtonState[1]]->Move(m_nX+m_nCx/2+5, m_nY + m_nCy - (10+SIZE_MSGBOX_BUTTON_Y));
		((CINFWindow*)m_pParent)->m_pCancelButton[m_nButtonState[1]]->Render();
#else
		// ��ư : ok
		((CINFWindow*)m_pParent)->m_pOkButton[m_nButtonState[0]]->Move(m_nX+m_nCx/2-SIZE_MSGBOX_BUTTON_X-5, m_nY + m_nCy - (19+SIZE_MSGBOX_BUTTON_Y));
		((CINFWindow*)m_pParent)->m_pOkButton[m_nButtonState[0]]->Render();
		// ��ư : cancel
		((CINFWindow*)m_pParent)->m_pCancelButton[m_nButtonState[1]]->Move(m_nX+m_nCx/2+5, m_nY + m_nCy - (19+SIZE_MSGBOX_BUTTON_Y));
		((CINFWindow*)m_pParent)->m_pCancelButton[m_nButtonState[1]]->Render();
#endif
	}
}
void CINFMessageBox::SetMessageBoxTitleChange(char *strTitle)
{
	memset(m_strMessage,0x00,sizeof(m_strMessage));
	strncpy(m_strMessage, strTitle, strlen(strTitle));
}

void CINFMessageBox::Tick()
{
	FLOG( "CINFMessageBox::Tick()" );
}

void CINFMessageBox::ResetMessageString()
{
	g_pD3dApp->m_bChatMode = TRUE;

	ZERO_MEMORY(m_strInputMessage);
	g_pD3dApp->CleanText();

	m_strInputMessage[strlen(m_strInputMessage)] = '_';
	m_strInputMessage[strlen(m_strInputMessage)+1] = '\0';
}
int CINFMessageBox::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)// return value 0 : close, 1: normal, 2 : message Proc break;
{
	FLOG( "CINFMessageBox::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)" );
	switch(uMsg)
	{
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);

			CheckMouseReverse(&pt);
			/////////////////////////////////////////////////////////////////
			//
			if(INPUT_RADIO_BUTTON)
			{
			}
			//
			////////////////////////////////////////////////////////////////

			if(OK_CANCEL_BUTTON || INPUT_MSG_BUTTON || INPUT_COUNT_BUTTON || INPUT_RADIO_BUTTON)
			{
				if(pt.y > m_nY + m_nCy - (19+SIZE_MSGBOX_BUTTON_Y) && pt.y < m_nY + m_nCy - 19)
				{
					if(pt.x > m_nX+m_nCx/2-SIZE_MSGBOX_BUTTON_X-5 && pt.x < m_nX+m_nCx/2-5)
					{
						if(m_nButtonState[0] != BUTTON_STATE_DOWN)
						{
							m_nButtonState[0] = BUTTON_STATE_UP;
						}
						return INF_MSGPROC_BREAK;
					}
					else
					{
						m_nButtonState[0] = BUTTON_STATE_NORMAL;
					}
					if(pt.x > m_nX+m_nCx/2+5 && pt.x < m_nX+m_nCx/2+5+SIZE_MSGBOX_BUTTON_X)
					{
						if(m_nButtonState[1] != BUTTON_STATE_DOWN)
						{
							m_nButtonState[1] = BUTTON_STATE_UP;
						}
						return INF_MSGPROC_BREAK;
					}
					else
					{
						m_nButtonState[1] = BUTTON_STATE_NORMAL;
					}
				}
				else
				{
					m_nButtonState[0] = BUTTON_STATE_NORMAL;
					m_nButtonState[1] = BUTTON_STATE_NORMAL;
				}
			}
			if(OK_BUTTON)
			{
				if(pt.y > m_nY + m_nCy - (19+SIZE_MSGBOX_BUTTON_Y) && pt.y < m_nY + m_nCy - 19)
				{
					if(pt.x > m_nX+m_nCx/2-SIZE_MSGBOX_BUTTON_X/2 && pt.x < m_nX+m_nCx/2+SIZE_MSGBOX_BUTTON_X/2)
					{
						if(m_nButtonState[0] != BUTTON_STATE_DOWN)
						{
							m_nButtonState[0] = BUTTON_STATE_UP;
						}
						return INF_MSGPROC_BREAK;
					}
					else
					{
						m_nButtonState[0] = BUTTON_STATE_NORMAL;
					}
				}
				else
				{
					m_nButtonState[0] = BUTTON_STATE_NORMAL;
				}
			}
			if(CANCEL_BUTTON)
			{
				if(pt.y > m_nY + m_nCy - (19+SIZE_MSGBOX_BUTTON_Y) && pt.y < m_nY + m_nCy - 19)
				{
					if(pt.x > m_nX+m_nCx/2-SIZE_MSGBOX_BUTTON_X/2 && pt.x < m_nX+m_nCx/2+SIZE_MSGBOX_BUTTON_X/2)
					{
						if(m_nButtonState[1] != BUTTON_STATE_DOWN)
						{
							m_nButtonState[1] = BUTTON_STATE_UP;
						}
						return INF_MSGPROC_BREAK;
					}
					else
					{
						m_nButtonState[1] = BUTTON_STATE_NORMAL;
					}
				}
				else
				{
					m_nButtonState[1] = BUTTON_STATE_NORMAL;
				}

			}
			if(INPUT_COUNT_BUTTON)
			{
				if( pt.x > ALL_BUTTON_START_X &&
					pt.x < ALL_BUTTON_START_X+ALL_BUTTON_SIZE_X &&
					pt.y > ALL_BUTTON_START_Y &&
					pt.y < ALL_BUTTON_START_Y+ALL_BUTTON_SIZE_Y)
				{
					m_nAllButtonState = BUTTON_STATE_UP;
				}
				else
				{
					m_nAllButtonState = BUTTON_STATE_NORMAL;
				}

			}
			if(m_bLockWindow)
			{
				m_nX += pt.x - m_ptMouse.x;
				m_nY += pt.y - m_ptMouse.y;
				if(m_nX < 0) m_nX = 0;
				if(m_nX > g_pD3dApp->GetBackBufferDesc().Width)
					m_nX = g_pD3dApp->GetBackBufferDesc().Width;
				if(m_nY < 0) m_nY = 0;
				if(m_nY > g_pD3dApp->GetBackBufferDesc().Height-19)
					m_nY = g_pD3dApp->GetBackBufferDesc().Height-19;
				m_ptMouse = pt;
				return INF_MSGPROC_BREAK;
			}
			// select, create menu�ÿ� �޽��� ����
			if(m_nMsgType == _Q_SELECT_DELETE || m_nMsgType == _MESSAGE_ERROR_CREATE || m_nMsgType == _MESSAGE_ERROR_NETWORK)
			{
				return INF_MSGPROC_BREAK;
			}

			// 2006-08-04 by ispark, â�ȿ� ������ �ٸ� �޼��� ��ȿ
			if(pt.x > m_nX && 
				pt.y > m_nY &&
			    pt.x < m_nX + m_nCx && 
			    pt.y < m_nY + m_nCy 
				&& g_pGameMain)// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
			{
				g_pGameMain->SetItemInfo( 0, 0, 0, 0); 
				return INF_MSGPROC_BREAK;
			}

		}
		break;
	case WM_LBUTTONDBLCLK:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);

			CheckMouseReverse(&pt);

			// 2013-02-28 by bhsohn Windowâ�ȿ��� �ڿ�â �޽��� ó�� �Ǵ� ���� ����
// 			if(pt.x > m_nX && pt.y > m_nY &&
// 			   pt.x < m_nX+m_nCx-14 && pt.y < m_nY+95) // 19: title bar height
			if(pt.x > m_nX && pt.y > m_nY &&
			   pt.x < m_nX+m_nCx-14 && pt.y < m_nY+m_nCy) // 19: title bar height			   
			{
				g_pInterface->SetWindowOrder(WNDInfWindow);
				return INF_MSGPROC_BREAK;
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);

			CheckMouseReverse(&pt);
			
			/////////////////////////////////////////////////////////////////////////////
			//
			if(INPUT_RADIO_BUTTON)
			{
				BOOL bTemp = TRUE;
				int  nTemp = 0;
				for(int i=0; i<m_nRadioCount; i++)
				{
					// ���� ���� ��ư�� ���� 2���� ���� ���� ��ġ ����
					if(bTemp)
					{
						if(pt.x> m_nX+25 && pt.x <m_nX+45)
						{
							if(pt.y >m_nY+RADIO_BUTTON_Y+nTemp && pt.y <m_nY+RADIO_BUTTON_Y+nTemp+12)
							{
								g_pInterface->SetWindowOrder(WNDInfWindow);
								m_nSelectRadio = i;
							}
						}
						bTemp = !bTemp;
					}
					else
					{
						if(pt.x> (m_nX+m_nCx/2)+5 && pt.x <(m_nX+m_nCx/2)+25)
						{
							if(pt.y >m_nY+RADIO_BUTTON_Y+nTemp && pt.y <m_nY+RADIO_BUTTON_Y+nTemp+12)
							{
								g_pInterface->SetWindowOrder(WNDInfWindow);
								m_nSelectRadio = i;
							}
						}
						bTemp = !bTemp;
						nTemp = nTemp+17;
					}
				}		
			}
			//
			/////////////////////////////////////////////////////////////////////////////
			
			if(INPUT_COUNT_BUTTON)
			{
				if(pt.x > ALL_UP_START_X && pt.x < ALL_UP_START_X+ALL_UPDOWN_SIZE_X)
				{
					if(pt.y > ALL_UP_START_Y && pt.y < ALL_UP_START_Y+ALL_UPDOWN_SIZE_Y)
					{
						if( m_nAllCurrentData < m_nAllNumber )
						{
							g_pInterface->SetWindowOrder(WNDInfWindow);
							m_nAllCurrentData ++;
							
							// 2009-02-03 by bhsohn â�� �ñ涧 ����Ʈ ���� 1�� ����
// 							wsprintf(g_pD3dApp->m_inputkey.m_full_str, "%d", m_nAllCurrentData );
// 							g_pD3dApp->m_inputkey.m_str_pos = strlen(g_pD3dApp->m_inputkey.m_full_str);
// 							memset(m_strInputMessage,0x00,SIZE_MAX_CHAT_MESSAGE);
// 							strncpy(m_strInputMessage,g_pD3dApp->m_inputkey.m_full_str,strlen(g_pD3dApp->m_inputkey.m_full_str));
							char chBuffTmp[256];
							ZERO_MEMORY(chBuffTmp);					
							wsprintf(chBuffTmp,"%d", m_nAllCurrentData);
							strncpy(m_strInputMessage, chBuffTmp, strlen(chBuffTmp)+1);
							// end 2009-02-03 by bhsohn â�� �ñ涧 ����Ʈ ���� 1�� ����
							m_strInputMessage[strlen(m_strInputMessage)] = '_';
							m_strInputMessage[strlen(m_strInputMessage)+1] = '\0';
							
						}
					}
					else if(pt.y > ALL_DOWN_START_Y && pt.y < ALL_DOWN_START_Y+ALL_UPDOWN_SIZE_Y)
					{
						if(m_nAllCurrentData > 0)
						{
							g_pInterface->SetWindowOrder(WNDInfWindow);
							m_nAllCurrentData --;
							// 2009-02-03 by bhsohn â�� �ñ涧 ����Ʈ ���� 1�� ����
// 							wsprintf(g_pD3dApp->m_inputkey.m_full_str, "%d", m_nAllCurrentData );
// 							g_pD3dApp->m_inputkey.m_str_pos = strlen(g_pD3dApp->m_inputkey.m_full_str);
// 							memset(m_strInputMessage,0x00,SIZE_MAX_CHAT_MESSAGE);
// 							strncpy(m_strInputMessage,g_pD3dApp->m_inputkey.m_full_str,strlen(g_pD3dApp->m_inputkey.m_full_str));
							char chBuffTmp[256];
							ZERO_MEMORY(chBuffTmp);					
							wsprintf(chBuffTmp,"%d", m_nAllCurrentData);
							strncpy(m_strInputMessage, chBuffTmp, strlen(chBuffTmp)+1);
							// end 2009-02-03 by bhsohn â�� �ñ涧 ����Ʈ ���� 1�� ����
							m_strInputMessage[strlen(m_strInputMessage)] = '_';
							m_strInputMessage[strlen(m_strInputMessage)+1] = '\0';
						}
					}
				}
			}
			if(OK_CANCEL_BUTTON || INPUT_MSG_BUTTON || INPUT_COUNT_BUTTON || INPUT_RADIO_BUTTON)
			{
				if(pt.y > m_nY + m_nCy - (19+SIZE_MSGBOX_BUTTON_Y) && pt.y < m_nY + m_nCy - 19)
				{
					if(pt.x > m_nX+m_nCx/2-SIZE_MSGBOX_BUTTON_X-5 && pt.x < m_nX+m_nCx/2-5)
					{
						g_pInterface->SetWindowOrder(WNDInfWindow);
						m_nButtonState[0] = BUTTON_STATE_DOWN;
						return INF_MSGPROC_BREAK;
					}
					else
					{
						g_pInterface->SetWindowOrder(WNDInfWindow);
						m_nButtonState[0] = BUTTON_STATE_NORMAL;
					}
					if(pt.x > m_nX+m_nCx/2+5 && pt.x < m_nX+m_nCx/2+5+SIZE_MSGBOX_BUTTON_X)
					{
						g_pInterface->SetWindowOrder(WNDInfWindow);
						m_nButtonState[1] = BUTTON_STATE_DOWN;
						return INF_MSGPROC_BREAK;
					}
					else
					{
						m_nButtonState[1] = BUTTON_STATE_NORMAL;
					}
				}
			}
			if(OK_BUTTON)
			{
				if(pt.y > m_nY + m_nCy - (19+SIZE_MSGBOX_BUTTON_Y) && pt.y < m_nY + m_nCy - 19)
				{
					if(pt.x > m_nX+m_nCx/2-SIZE_MSGBOX_BUTTON_X/2 && pt.x < m_nX+m_nCx/2+SIZE_MSGBOX_BUTTON_X/2)
					{
						g_pInterface->SetWindowOrder(WNDInfWindow);
						m_nButtonState[0] = BUTTON_STATE_DOWN;
						return INF_MSGPROC_BREAK;
					}
					else
					{
						m_nButtonState[0] = BUTTON_STATE_NORMAL;
					}
				}
			}

			if(CANCEL_BUTTON)
			{
				if(pt.y > m_nY + m_nCy - (19+SIZE_MSGBOX_BUTTON_Y) && pt.y < m_nY + m_nCy - 19)
				{
					if(pt.x > m_nX+m_nCx/2-SIZE_MSGBOX_BUTTON_X/2 && pt.x < m_nX+m_nCx/2+SIZE_MSGBOX_BUTTON_X/2)
					{
						g_pInterface->SetWindowOrder(WNDInfWindow);
						m_nButtonState[1] = BUTTON_STATE_DOWN;
						return INF_MSGPROC_BREAK;
					}
					else
					{
						m_nButtonState[1] = BUTTON_STATE_NORMAL;
					}
				}

			}
			if(INPUT_COUNT_BUTTON)
			{
				if( pt.x > ALL_BUTTON_START_X &&
					pt.x < ALL_BUTTON_START_X+ALL_BUTTON_SIZE_X &&
					pt.y > ALL_BUTTON_START_Y &&
					pt.y < ALL_BUTTON_START_Y+ALL_BUTTON_SIZE_Y)
				{
					g_pInterface->SetWindowOrder(WNDInfWindow);
					m_nAllButtonState = BUTTON_STATE_DOWN;
					return INF_MSGPROC_BREAK;
				}
				else
				{
					m_nAllButtonState = BUTTON_STATE_NORMAL;
				}

			}
			if(pt.x > m_nX && pt.y > m_nY &&
			   pt.x < m_nX+m_nCx-14 && pt.y < m_nY+19) // 19: title bar height
			{
				// 2008-09-22 by dgwoo ���콺�� Ŭ���� ��ġ�� �޽��� �ڽ��̸� chatmode�� ����.
				if(INPUT_MSG_BUTTON)
				{
					ResetMessageString();
				}

				m_bLockWindow = TRUE;
				m_ptMouse = pt;
				g_pInterface->SetWindowOrder(WNDInfWindow);
				return INF_MSGPROC_BREAK;
			}
			// x close
			if(pt.x > m_nX+m_nCx-14 && pt.y > m_nY+5 &&
			   pt.x < m_nX+m_nCx-5 && pt.y < m_nY+15)
			{
				if((m_nMsgType == _Q_INFLUENCEMAP_DEAD_RETURN ||
					m_nMsgType == _Q_DEAD_RETURN ||
					m_nMsgType == _Q_AGEAR_FUEL_ALLIN) &&						// 2005-08-19 by ispark
					// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
					g_pGameMain && !g_pGameMain->m_pCommunity->GetParty()->m_bEnablePartyMenu)
					return INF_MSGPROC_NORMAL;

				// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
				// ���Ǵ�Ƽ 5�� ��Ȱ
				if( m_nMsgType == _Q_REVIVE_WAIT_5SECOND )
					return INF_MSGPROC_NORMAL;
				// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

				OnButtonClick(1);
				return INF_MSGPROC_CLOSE;
			}
			// select, create menu�ÿ� �޽��� ����
			if( m_nMsgType == _Q_SELECT_DELETE || 
				m_nMsgType == _MESSAGE_ERROR_CREATE || 
				m_nMsgType == _MESSAGE_ERROR_NETWORK)
			{
				return INF_MSGPROC_BREAK;
			}

			// 2013-02-28 by bhsohn Windowâ�ȿ��� �ڿ�â �޽��� ó�� �Ǵ� ���� ����
// 			if(pt.x > m_nX && pt.y > m_nY &&
// 			   pt.x < m_nX+m_nCx-14 && pt.y < m_nY+95) // 19: title bar height
			if(pt.x > m_nX && pt.y > m_nY &&
			   pt.x < m_nX+m_nCx-14 && pt.y < m_nY+m_nCy) // 19: title bar height
			{
				// 2008-09-22 by dgwoo ���콺�� Ŭ���� ��ġ�� �޽��� �ڽ��̸� chatmode�� ����.
				if(INPUT_MSG_BUTTON)
				{
					ResetMessageString();
				}
				g_pInterface->SetWindowOrder(WNDInfWindow);
				return INF_MSGPROC_BREAK;
			}

			
		}
		break;
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);

			CheckMouseReverse(&pt);
			D3DXVECTOR2 vPos1 = D3DXVECTOR2(pt.x,pt.y);

			////////////////////////////////////////////////////////////////////////////////////
			//
			if(INPUT_RADIO_BUTTON)
			{
			}
			//
			////////////////////////////////////////////////////////////////////////////////////

 			if(OK_CANCEL_BUTTON || INPUT_MSG_BUTTON || INPUT_COUNT_BUTTON || INPUT_RADIO_BUTTON)
			{
				if(pt.y > m_nY + m_nCy - (19+SIZE_MSGBOX_BUTTON_Y) && pt.y < m_nY + m_nCy - 19)
				{
					if(pt.x > m_nX+m_nCx/2-SIZE_MSGBOX_BUTTON_X-5 && pt.x < m_nX+m_nCx/2-5)
					{
						if(m_nButtonState[0] == BUTTON_STATE_DOWN)
						{
							OnButtonClick(0);
							return INF_MSGPROC_CLOSE;
						}
						m_nButtonState[0] = BUTTON_STATE_UP;
						return INF_MSGPROC_BREAK;
					}
					else
					{
						m_nButtonState[0] = BUTTON_STATE_NORMAL;
					}
					if(pt.x > m_nX+m_nCx/2+5 && pt.x < m_nX+m_nCx/2+5+SIZE_MSGBOX_BUTTON_X)
					{
						if(m_nButtonState[1] == BUTTON_STATE_DOWN)
						{
							OnButtonClick(1);
							return INF_MSGPROC_CLOSE;
						}
						m_nButtonState[1] = BUTTON_STATE_UP;
						return INF_MSGPROC_BREAK;
					}
					else
					{
						m_nButtonState[1] = BUTTON_STATE_NORMAL;
					}
				}
/////////////////////////////////���� define : Ŭ���ÿ� ���̵� ��������/////////////////////////////////////////////////////////////////////////
				if(m_nMsgType == _Q_PARTY_INVITE_USER)
				{
					g_pGameMain->m_pCommunity->GetParty()->PartyQuestionInviteUser(this, pt.x, pt.y);
				}
				if(m_nMsgType == _Q_TRADE_INPUT_NAME)
				{
					((CINFGameMain*)m_pParent->m_pParent)->m_pTrade->TradeQuestionInviteUser(this, pt.x, pt.y);
				}
				if(m_nMsgType == _Q_BATTLE_NAME)
				{					
					// Enemy �߿��� Ÿ���� �ִ��� �˻�
					CEnemyData * pTp = NULL;
					pTp = g_pScene->GetEnemyCharaterID(vPos1);

					if(pTp)
					{
						strcpy(m_strInputMessage,pTp->m_infoCharacter.CharacterInfo.CharacterName);
						strcat(m_strInputMessage, "_");
						return TRUE;
					}
				}
				if( m_nMsgType == _Q_GUILD_INVITE)
				{
					g_pGameMain->m_pCommunity->GetGuild()->pGuildQuestionInviteUser(this, pt.x, pt.y);
				}

				if( m_nMsgType == _Q_VOIP_NAME)
				{					
					CEnemyData * pcp = NULL;					
					pcp = g_pScene->GetEnemyCharaterID(vPos1);
					
					if(pcp)
					{
						strcpy(m_strInputMessage,pcp->m_infoCharacter.CharacterInfo.CharacterName);
						strcat(m_strInputMessage, "_");
						return TRUE;
					}
				}
				if(m_nMsgType == _Q_SUPER_RESTORE)
				{		
					// ���� ���� Ÿ������ �˻�
					if(g_pShuttleChild->m_nObjScreenW > 0)
					{
						float fLength = 50.0f;
						D3DXVECTOR2 vPos2 = D3DXVECTOR2(g_pShuttleChild->m_nObjScreenX, g_pShuttleChild->m_nObjScreenY);
						if(D3DXVec2Length(&(vPos1 - vPos2)) < fLength)
						{
							strcpy(m_strInputMessage,g_pShuttleChild->m_myShuttleInfo.CharacterName);
							strcat(m_strInputMessage, "_");
							return TRUE;	
						}
					}					
					CEnemyData * pTp = NULL;
					pTp = g_pScene->GetEnemyCharaterID(vPos1);

					if(pTp)
					{
						strcpy(m_strInputMessage,pTp->m_infoCharacter.CharacterInfo.CharacterName);
						strcat(m_strInputMessage, "_");
						return TRUE;
					}
				}
				if(m_nMsgType == _Q_MEMBER_SUMMON)
				{		
					// ���ܿ� �� �� ��ȯ - ���콺 Ŭ������ ���� ����.
				}				
			}
			if(OK_BUTTON)
			{
				if(pt.y > m_nY + m_nCy - (19+SIZE_MSGBOX_BUTTON_Y) && pt.y < m_nY + m_nCy - 19)
				{
					if(pt.x > m_nX+m_nCx/2-SIZE_MSGBOX_BUTTON_X/2 && pt.x < m_nX+m_nCx/2+SIZE_MSGBOX_BUTTON_X/2)
					{
						if(m_nButtonState[0] == BUTTON_STATE_DOWN)
						{
							if((m_nMsgType == _Q_INFLUENCEMAP_DEAD_RETURN ||
								m_nMsgType == _Q_DEAD_RETURN ||
								m_nMsgType == _Q_AGEAR_FUEL_ALLIN) &&						// 2005-08-19 by ispark
								!g_pGameMain->m_pCommunity->GetParty()->m_bEnablePartyMenu)
								return INF_MSGPROC_NORMAL;
							OnButtonClick(0);
							return INF_MSGPROC_CLOSE;
						}
						m_nButtonState[0] = BUTTON_STATE_UP;
						return INF_MSGPROC_BREAK;
					}
					else
					{
						m_nButtonState[0] = BUTTON_STATE_NORMAL;
					}
				}
			}
			if(CANCEL_BUTTON)
			{
				if(pt.y > m_nY + m_nCy - (19+SIZE_MSGBOX_BUTTON_Y) && pt.y < m_nY + m_nCy - 19)
				{
					if(pt.x > m_nX+m_nCx/2-SIZE_MSGBOX_BUTTON_X/2 && pt.x < m_nX+m_nCx/2+SIZE_MSGBOX_BUTTON_X/2)
					{
						if(m_nButtonState[1] == BUTTON_STATE_DOWN)
						{
							OnButtonClick(1);
							return INF_MSGPROC_CLOSE;
						}
						m_nButtonState[1] = BUTTON_STATE_UP;
						return INF_MSGPROC_BREAK;
					}
					else
					{
						m_nButtonState[1] = BUTTON_STATE_NORMAL;
					}
				}
				else
				{
					m_bLockWindow = FALSE;
				}
			}
			if(INPUT_COUNT_BUTTON)
			{
				if( pt.x > ALL_BUTTON_START_X &&
					pt.x < ALL_BUTTON_START_X+ALL_BUTTON_SIZE_X &&
					pt.y > ALL_BUTTON_START_Y &&
					pt.y < ALL_BUTTON_START_Y+ALL_BUTTON_SIZE_Y)
				{
					// 2008-07-31 by dgwoo All ��ư�� ��������� ��ü ������ ������ �ȵǴ� ����. �ּ�ó��.
					//if(m_nAllButtonState == BUTTON_STATE_DOWN)
					{
						m_nAllCurrentData = m_nAllNumber;
						wsprintf(g_pD3dApp->m_inputkey.m_full_str, "%d", m_nAllCurrentData );
						g_pD3dApp->m_inputkey.m_str_pos = strlen(g_pD3dApp->m_inputkey.m_full_str);
						memset(m_strInputMessage,0x00,SIZE_MAX_CHAT_MESSAGE);
						strncpy(m_strInputMessage,g_pD3dApp->m_inputkey.m_full_str,strlen(g_pD3dApp->m_inputkey.m_full_str));
						m_strInputMessage[strlen(m_strInputMessage)] = '_';
						m_strInputMessage[strlen(m_strInputMessage)+1] = '\0';
					}
					m_nAllButtonState = BUTTON_STATE_UP;
					return INF_MSGPROC_BREAK;
				}
				else
				{
					m_nAllButtonState = BUTTON_STATE_NORMAL;
				}

			}
//			if(pt.x > m_nX && pt.y > m_nY &&
//			   pt.x < m_nX+m_nCx-14 && pt.y < m_nY+19) // 19: title bar height
			{
				m_bLockWindow = FALSE;
			}
			// select, create menu�ÿ� �޽��� ����
			if( m_nMsgType == _Q_SELECT_DELETE || 
				m_nMsgType == _MESSAGE_ERROR_CREATE || 
				m_nMsgType == _MESSAGE_ERROR_NETWORK)
			{
				return INF_MSGPROC_BREAK;
			}
		}
		break;
	case WM_KEYDOWN:
		{
			if(wParam == VK_ESCAPE)
			{
				if((m_nMsgType == _Q_INFLUENCEMAP_DEAD_RETURN ||
					m_nMsgType == _Q_DEAD_RETURN ||
					m_nMsgType == _Q_AGEAR_FUEL_ALLIN) &&						// 2005-08-19 by ispark
					!g_pGameMain->m_pCommunity->GetParty()->m_bEnablePartyMenu)
					return INF_MSGPROC_NORMAL;

				// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
				// ���Ǵ�Ƽ 5�� ��Ȱ
				if( m_nMsgType == _Q_REVIVE_WAIT_5SECOND )
					return INF_MSGPROC_NORMAL;
				// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

				OnButtonClick(1);
				return INF_MSGPROC_CLOSE;
			}
			if(wParam == VK_RETURN)
			{
				if (EnterMsgbox())
				{
					OnButtonClick(0);
					return INF_MSGPROC_CLOSE;
				}
				// 2013-04-08 by jhseol, �̺�Ʈ ������ ���� �˸���� ���� - ���� �޾����� �˷��ִ� MSG �ڽ��� Ȯ�ι�ư ����Ű �����ϵ��� ����
#ifdef C_ITEM_EVENT_NOTIFY_MSG_CHANGE_JHSEOL
				// ENTER_MSGBOX ���⿡ ������ �����ؼ� ����Ʈ�� �߰��ϴ°� ����
				// �ٷ� #ifdef C_ITEM_EVENT_NOTIFY_MSG_CHANGE_JHSEOL �߰��ؼ� �����ϴ°� ����ؼ� �ٷ� �۾��� ��.
				if ( _Q_GIFT_ITEM_RING_IN == m_nMsgType )
				{
					OnButtonClick(0);
					return INF_MSGPROC_CLOSE;
				}
#endif
				// end 2013-04-08 by jhseol, �̺�Ʈ ������ ���� �˸���� ���� - ���� �޾����� �˷��ִ� MSG �ڽ��� Ȯ�ι�ư ����Ű �����ϵ��� ����
				return INF_MSGPROC_NORMAL;
			}
			
			// 2009-02-03 by bhsohn â�� �ñ涧 ����Ʈ ���� 1�� ����
			if(INPUT_COUNT_BUTTON)
			{				
				DWORD dwCode = lParam;
				int nNumber = g_pGameMain->GetKeyDownToNumber(dwCode);
				if(nNumber != -1)
				{
					int nTmpAllCurrentData  = m_nAllCurrentData;
					nTmpAllCurrentData *= 10;
					nTmpAllCurrentData += nNumber;
					
					m_nAllCurrentData = nTmpAllCurrentData;
					
					char chBuffTmp[256];
					ZERO_MEMORY(chBuffTmp);					
					wsprintf(chBuffTmp,"%d", m_nAllCurrentData);
					strncpy(m_strInputMessage, chBuffTmp, strlen(chBuffTmp)+1);
					m_strInputMessage[strlen(m_strInputMessage)] = '_';
					m_strInputMessage[strlen(m_strInputMessage)+1] = '\0';
				}
				else if(0x000e0001 == dwCode)
				{
					m_nAllCurrentData /= 10;
					
					char chBuffTmp[256];
					ZERO_MEMORY(chBuffTmp);					
					wsprintf(chBuffTmp,"%d", m_nAllCurrentData);
					strncpy(m_strInputMessage, chBuffTmp, strlen(chBuffTmp)+1);
					m_strInputMessage[strlen(m_strInputMessage)] = '_';
					m_strInputMessage[strlen(m_strInputMessage)+1] = '\0';
				}
			}
			
			// end 2009-02-03 by bhsohn â�� �ñ涧 ����Ʈ ���� 1�� ����
			
			// select, create menu�ÿ� �޽��� ����
			if( (m_nMsgType == _Q_SELECT_DELETE || 
				m_nMsgType == _MESSAGE_ERROR_CREATE ||
				m_nMsgType == _MESSAGE_ERROR_NETWORK ||
				(INPUT_MSG_BUTTON) ||
				(INPUT_COUNT_BUTTON))&& g_pInterface->GetWindowFirstOrder()==WNDInfWindow )
			{
				return INF_MSGPROC_BREAK;
			}
		}
		break;
/*	case WM_ENTERKEY:
		{
			OnButtonClick(0);
			return 0;
		}
		break;
*/	case UM_MSGBOX_CLOSE:
		{
			if(INPUT_MSG_BUTTON || INPUT_COUNT_BUTTON)
			{
				g_pD3dApp->CleanText();
				g_pD3dApp->m_bChatMode = FALSE;
				g_pD3dApp->m_inputkey.SetMaxLength(SIZE_MAX_CHAT_MESSAGE);
			}
			return INF_MSGPROC_CLOSE;
		}
		break;
	case WM_IME_STARTCOMPOSITION:
	case WM_IME_NOTIFY:
	case WM_IME_COMPOSITION:
	case WM_INPUTLANGCHANGE:	
	case WM_IME_ENDCOMPOSITION:
	case WM_CHAR:
		{
			if(g_pInterface->GetWindowFirstOrder() == WNDInfWindow
				|| g_pD3dApp->m_dwGameState == _SELECT
				|| g_pD3dApp->m_dwGameState == _CREATE
				|| g_pD3dApp->m_dwGameState == _OPTION)
			{
				if(INPUT_MSG_BUTTON || INPUT_COUNT_BUTTON)
				{
					if(m_nMsgType == _Q_SELECT_DELETE)
					{
						g_nRenderCandidate =  SET_DELETEMENU_CANDIDATE;
						GetInputMessage(uMsg, wParam, lParam);
					}
					else
					{
						g_nRenderCandidate = SET_MESSAGEBOX_CANDIDATE;
						GetInputMessage(uMsg, wParam, lParam);
					}

						return INF_MSGPROC_BREAK;
				}
				// select, create menu�ÿ� �޽��� ����
				if( m_nMsgType == _Q_SELECT_DELETE || 
					m_nMsgType == _MESSAGE_ERROR_CREATE ||
					m_nMsgType == _MESSAGE_ERROR_NETWORK)
				{				
					return INF_MSGPROC_BREAK;
				}
			}
		}
		break;		
	}
/*
// select, create menu�ÿ� �ٸ� �޽��� ���� ����, ����� ���� ���α׷� ����
	if(m_nMsgType == _Q_SELECT_DELETE || m_nMsgType == _MESSAGE_ERROR_CREATE || m_nMsgType == _MESSAGE_ERROR_NETWORK)
	{
		return INF_MSGPROC_BREAK;
	}
*/	

	return INF_MSGPROC_NORMAL;
}

void CINFMessageBox::GetInputMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	FLOG( "CINFMessageBox::GetInputMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)" );

#ifdef LANGUAGE_VIETNAM
	// 2007-10-05 by bhsohn ��Ʈ�� �޽��� �ڽ����� ��Ʈ���� �������� ���� �ذ�
	//g_pD3dApp->m_inputkey.SetInputLanguage(INPUT_LANGUAGE_ENG);
#endif
	g_pD3dApp->m_inputkey.KeyMapping(g_pD3dApp->GetHwnd(), uMsg, wParam, lParam);
	if(g_pD3dApp->m_inputkey.m_str_pos > 57)
	{
		g_pD3dApp->m_inputkey.m_str_pos = 58;
		g_pD3dApp->m_inputkey.m_full_str[g_pD3dApp->m_inputkey.m_str_pos] = NULL;
	}
	if(strlen(g_pD3dApp->m_inputkey.m_full_str)!=0)
	{
		memset(m_strInputMessage,0x00,SIZE_MAX_CHAT_MESSAGE);		
		if(wParam == 34 && g_pD3dApp->m_pShuttleChild->m_bOldPToPPos != 200 && g_pD3dApp->m_inputkey.m_str_pos == 1)
		{
			strncpy(g_pD3dApp->m_inputkey.m_full_str+1,
				g_pD3dApp->m_pShuttleChild->m_strChatPToP[g_pD3dApp->m_pShuttleChild->m_bOldPToPPos],
			strlen(g_pD3dApp->m_pShuttleChild->m_strChatPToP[g_pD3dApp->m_pShuttleChild->m_bOldPToPPos]));
			g_pD3dApp->m_inputkey.m_full_str[strlen(g_pD3dApp->m_pShuttleChild->m_strChatPToP[g_pD3dApp->m_pShuttleChild->m_bOldPToPPos])+1] = ' ';
			g_pD3dApp->m_inputkey.m_str_pos += strlen(g_pD3dApp->m_pShuttleChild->m_strChatPToP[g_pD3dApp->m_pShuttleChild->m_bOldPToPPos]) + 1;
		}		
		strncpy(m_strInputMessage,g_pD3dApp->m_inputkey.m_full_str,strlen(g_pD3dApp->m_inputkey.m_full_str));
		CheckStringMsg();
		m_strInputMessage[strlen(m_strInputMessage)] = '_';
		m_strInputMessage[strlen(m_strInputMessage)+1] = '\0';
	}
	else
	{
		memset(m_strInputMessage,0x00,sizeof(m_strInputMessage));
		m_strInputMessage[strlen(m_strInputMessage)] = '_';
		m_strInputMessage[strlen(m_strInputMessage)+1] = '\0';
	}	
	
	// 2009-02-03 by bhsohn â�� �ñ涧 ����Ʈ ���� 1�� ����
// 	if(INPUT_COUNT_BUTTON)
// 	{
// 		m_nAllCurrentData = atoi(g_pD3dApp->m_inputkey.m_full_str);
// 		if(m_nAllCurrentData == 0)
// 		{
// 			memset(m_strInputMessage,0x00,SIZE_MAX_CHAT_MESSAGE);
// 			strncpy(m_strInputMessage,g_pD3dApp->m_inputkey.m_full_str,strlen(g_pD3dApp->m_inputkey.m_full_str));
// 			m_strInputMessage[strlen(m_strInputMessage)] = '_';
// 			m_strInputMessage[strlen(m_strInputMessage)+1] = '\0';
// 		}
// 	}
	if(INPUT_COUNT_BUTTON)
	{
		if(m_nAllCurrentData == 0)
		{
			memset(m_strInputMessage,0x00,SIZE_MAX_CHAT_MESSAGE);			
			m_strInputMessage[strlen(m_strInputMessage)] = '_';
			m_strInputMessage[strlen(m_strInputMessage)+1] = '\0';
		}
		else
		{
			char chBuffTmp[256];
			ZERO_MEMORY(chBuffTmp);					
			wsprintf(chBuffTmp,"%d", m_nAllCurrentData);
			strncpy(m_strInputMessage, chBuffTmp, strlen(chBuffTmp)+1);
			m_strInputMessage[strlen(m_strInputMessage)] = '_';
			m_strInputMessage[strlen(m_strInputMessage)+1] = '\0';
		}
 	}
	// end 2009-02-03 by bhsohn â�� �ñ涧 ����Ʈ ���� 1�� ����
}


// 2013-04-05 by bhsohn ������ 5�� ��Ȱ �ý��� �߰�
//void CINFMessageBox::OnButtonClick(int i)// if i==0 then ok, if i==1 then cancel
void CINFMessageBox::OnButtonClick(int i, BOOL bTimerClick/*=FALSE*/)// if i==0 then ok, if i==1 then cancel
{
	FLOG( "CINFMessageBox::OnButtonClick(int i)" );
	switch(m_nMsgType)
	{
	case _Q_PART_STAT_RESET:
		{
			if(i == 0)
			{
				// m_nSelectRadio; ���� ��ư ����
				MSG_FC_ITEM_USE_ENERGY sMsg;
				sMsg.ClientIndex = g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.ClientIndex;
				sMsg.ItemUniqueNumber = m_UniqueNumber;
				
				// ����� ������ ������ ���߱� ���� ���Ǻ���
				if(m_nSelectRadio == 4)
					sMsg.nParam1 = 5;
				else if(m_nSelectRadio == 5)
					sMsg.nParam1 = 4;
				else
				sMsg.nParam1 = m_nSelectRadio;

				g_pFieldWinSocket->SendMsg( T_FC_ITEM_USE_ENERGY, (char*)&sMsg, sizeof(sMsg) );
			}
		}
		break;
	case _Q_PARTY_INVITE:// ��뿡 ���� �ʴ���� ���
		{
			if(i == 0 && ((CINFWindow*)m_pParent)->IsExistMsgBox(_Q_PARTY_CREATE))
			{
				((CINFWindow*)m_pParent)->DeleteMsgBox(_Q_PARTY_CREATE);
			}
			// 2009. 12. 03 by jskim ��Ƽ ������ ��Ƽ�� ���ԵǾ� �ִ��� üũ
			//g_pGameMain->m_pCommunity->GetParty()->PartyRecvInvite(i);
			g_pGameMain->m_pCommunity->GetParty()->PartyRecvInvite(i, m_UniqueNumber);
			//end 2009. 12. 03 by jskim ��Ƽ ������ ��Ƽ�� ���ԵǾ� �ִ��� üũ
		}
		break;
	case _Q_PARTY_CREATE:
		{
			if(i == 0)
			{
				if(((CINFWindow*)m_pParent)->IsExistMsgBox(_Q_PARTY_INVITE))
				{
					g_pGameMain->m_pCommunity->GetParty()->PartyRecvInvite(1);//����
					((CINFWindow*)m_pParent)->DeleteMsgBox(_Q_PARTY_INVITE);
				}
				g_pGameMain->m_pCommunity->GetParty()->PartySendCreate();
			}
		}
		break;
	case _Q_PARTY_INVITE_USER:// ���� �Է�
		{
			if(i == 0)
			{
				m_strInputMessage[strlen(m_strInputMessage)-1] = NULL;// '_'���� ����
				strcpy(g_pGameMain->m_pCommunity->GetParty()->m_strInviteUser, m_strInputMessage);
				g_pGameMain->m_pCommunity->GetParty()->PartySendInviteUser();
			}
		}
		break;
	// 2008-06-25 by dgwoo ä�ù濡 ���� �ʴ�.
	case _Q_CHATROOM_INVITE:			// "�ʴ��� ������ �Է��Ͻÿ�."
		{
			if(i == 0)
			{
				m_strInputMessage[strlen(m_strInputMessage)-1] = NULL;// '_'���� ����
				// 2008-07-14 by bhsohn EP3 ���� ó��
				if(g_pGameMain->IsRejectUser(m_strInputMessage))
				{
					g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080714_0207,COLOR_ERROR);//"\\y�ź� ��Ͽ� ��ϵ� ����Դϴ�."
					break;
				}
				// end 2008-07-14 by bhsohn EP3 ���� ó��

				MSG_IC_CHATROOM_REQUEST_INVITE sMsg;
				sMsg.ChatRoomNum = m_dwData;
				strcpy(sMsg.InviteeCharacterName,m_strInputMessage);
				g_pIMSocket->SendMsg( T_IC_CHATROOM_REQUEST_INVITE, (char*)&sMsg, sizeof(sMsg) );
			}
		}
		break;
	case _Q_CHATROOM_INVITE_FROM:
		{
			if(i == 0)
			{
				MSG_IC_CHATROOM_ACCEPT_INVITE sMsg;
				sMsg.ChatRoomNum = m_UniqueNumber;
				g_pIMSocket->SendMsg(T_IC_CHATROOM_ACCEPT_INVITE, (char*)&sMsg, sizeof(sMsg) );
			}else
			{
				MSG_IC_CHATROOM_REJECT_INVITE sMsg;
				sMsg.ChatRoomNum = m_UniqueNumber;
				g_pIMSocket->SendMsg(T_IC_CHATROOM_REJECT_INVITE, (char*)&sMsg, sizeof(sMsg) );
			}
		}
		break;
	case _Q_CHATROOM_OUT:
		{
			if(i == 0)
			{
				MSG_IC_CHATROOM_LEAVE sMsg;
				sMsg.ChatRoomNum = g_pGameMain->m_pCommunity->GetChatRoomNum();
				memcpy(sMsg.LeaveCharacterName,g_pShuttleChild->m_myShuttleInfo.CharacterName,SIZE_MAX_CHARACTER_NAME);
				g_pIMSocket->SendMsg(T_IC_CHATROOM_LEAVE, (char*)&sMsg, sizeof(sMsg));
			}
		}
		break;
/*	case _Q_PARTY_INVITE_USER_OK:// �ʴ��� ���� Ȯ��, ���� ������. ���� ����
		{
			if(i == 0)
			{
				g_pGameMain->m_pCommunity->GetParty()->PartySendInviteUser();
			}
		}
		break;
*/	case _Q_PARTY_SECEDE:
		{
			if( i == 0 )
			{
				g_pGameMain->m_pCommunity->GetParty()->PartySendSecede();
			}
		}
		break;
	case _Q_PARTY_BAN_MEMBER:
		{
			if( i == 0 )
			{
				// 2008-04-04 by bhsohn Ep3 Ŀ�´�Ƽ â
				// �߹�
				//g_pGameMain->m_pCommunity->GetParty()->PartySendBanUser();
				g_pGameMain->m_pCommunity->PartySendBanUser();
			}
		}
		break;
	case _Q_PARTY_TRANSFER_MASTER:
		{
			if( i == 0 )
			{
				// 2008-04-04 by bhsohn Ep3 Ŀ�´�Ƽ â
				// ����
				//g_pGameMain->m_pCommunity->GetParty()->PartySendTransferMaster();
				g_pGameMain->m_pCommunity->PartySendTransferMaster();
			}
		}
		break;

	// 2016-07-19 panoskj disabled this
	//case _Q_VOIP_OK:
	//	{
	//		if( i == 0 )
	//		{
	//			MSG_IC_VOIP_1to1_DIAL_OK sMsg;
	//			sMsg.nCalledAccountUniqueNumber = g_pShuttleChild->m_myShuttleInfo.AccountUniqueNumber;
	//			sMsg.nCallerAccountUniqueNumber = g_pD3dApp->m_VOIPState.nCalledAccountUniqueNumber;
	//			g_pGameMain->m_pChat->UpdateVoiceChatType(VOICE_ONE);
	//			g_pIMSocket->SendMsg( T_IC_VOIP_1to1_DIAL_OK, (char*)&sMsg, sizeof(sMsg) );
	//		}
	//		else
	//		{
	//			// UNREGISTER
	//			COPYDATASTRUCT	copyData;
	//			memset(&copyData, 0x00, sizeof(COPYDATASTRUCT));
	//			AV_MSG_WM_COPYDATA voIP(_BothCall, AV_MT_UNREGISTER, 0);
	//			copyData.dwData = (DWORD)voIP;
	//			copyData.lpData = NULL;
	//			copyData.cbData = 0;
	//			::SendMessage( g_pD3dApp->m_VOIPState.m_hWndAtumVoIPClient, WM_COPYDATA,
	//							(WPARAM)g_pD3dApp->GetHwnd(), 
	//							(LPARAM)&copyData);
	//			// REJECT
	//			MSG_IC_VOIP_ERROR sMsg;
	//			sMsg.nErrorNum = VOIPERR_1to1_REJECT;
	//			sMsg.nSend2AccountUniqueNumber = g_pD3dApp->m_VOIPState.nCalledAccountUniqueNumber;
	//			g_pIMSocket->SendMsg( T_IC_VOIP_ERROR, (char*)&sMsg, sizeof(sMsg) );
	//			// State �ʱ�ȭ
	//			g_pD3dApp->m_VOIPState.nVOIPState = _VOIP_NOTLOGIN;
	//			g_pD3dApp->m_VOIPState.bCaller = FALSE;
	//		}
	//	}
	//	break;
	case _Q_TRADE_INPUT_NAME:
		{
			if(i == 0)
			{
				m_strInputMessage[strlen(m_strInputMessage)-1] = NULL;// '_'���� ����
				CMapEnemyIterator itEnemy = g_pScene->m_mapEnemyList.begin();
				while(itEnemy != g_pScene->m_mapEnemyList.end())
				{
					// 2006-05-22 by ispark, strcmp -> stricmp
					if(!stricmp(itEnemy->second->m_infoCharacter.CharacterInfo.CharacterName, m_strInputMessage))
					{
						// 2006-01-07 by ispark, ���� ��
#ifdef FREEWAR_
						if (!IsInfluenceCharacter(g_pShuttleChild->m_myShuttleInfo.InfluenceType, itEnemy->second->m_infoCharacter.CharacterInfo.InfluenceType, 1, g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex))
#else
						if(!IsInfluenceCharacter(g_pShuttleChild->m_myShuttleInfo.InfluenceType, itEnemy->second->m_infoCharacter.CharacterInfo.InfluenceType))
#endif
						{
							// 2006-01-07 by ispark, ���� �ٸ� ���³��� ���� �ȵ�
							g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_051208_0102, COLOR_ERROR);// "���� �ٸ� ���³��� ������ �� �� �����ϴ�."
							break;
						}

						((CINFGameMain*)m_pParent->m_pParent)->m_pTrade->SendTradeRequest(m_strInputMessage);
						break;
					}
					itEnemy++;
				}
			}
			// 2009. 08. 19 by jsKim ���� �� �޴� ������ ��� Ŀ���� ������ �ʴ� ����
			//g_pGameMain->m_bChangeMousePoint = FALSE;
			// 2012-12-17 by jhjang ������ ���콺 Ŀ���� ����� �������� �ʴ� ���� ����
			//g_INFCnt--;
			//if(g_INFCnt==0)
			if(g_pD3dApp->RemoveINFCnt() == 0)
			{
				g_pGameMain->m_bChangeMousePoint = FALSE;
			}		
			// end 2009. 08. 19 by jsKim ���� �� �޴� ������ ��� Ŀ���� ������ �ʴ� ����
			// end 2012-12-17 by jhjang ������ ���콺 Ŀ���� ����� �������� �ʴ� ���� ����
		}
		break;
	case _Q_TRADE_REQUEST:
		{
			if(i == 0)
			{
				// 2007-11-01 by bhsohn ���� �̿��߿� ���� ó��
				// ���� ������ �����ִٸ� ������ �ݰ��Ѵ�.
				g_pInterface->CloseVisitShop();

				((CINFGameMain*)m_pParent->m_pParent)->m_pTrade->SendTradeAccept();
			}
			else
			{
				((CINFGameMain*)m_pParent->m_pParent)->m_pTrade->SendTradeReject();
			}
		}
		break;
	case _Q_TRADE_CANCEL:
		{
			if(i == 0)
			{
				((CINFGameMain*)m_pParent->m_pParent)->m_pTrade->SendTradeCancel();
			}
		}
		break;
	case _Q_TRADE_OK:
		{
			if(i==0)
			{
				((CINFGameMain*)m_pParent->m_pParent)->m_pTrade->SendTradeOk();
			}

		}
		break;
	case _Q_ITEM_DELETE_NUM:
		{
			if(i == 0)
			{
				int count = atoi(m_strInputMessage);
				if( count > 0 )
				{
					((CINFGameMain*)m_pParent->m_pParent)->m_pInven->DeleteSelectItem(count);
				}
				else
				{
					// 2007-06-20 by bhsohn ������ ������, �޸� ���� ����
					//((CINFGameMain*)m_pParent->m_pParent)->m_pInven->m_pDeleteItem = NULL;
					((CINFGameMain*)m_pParent->m_pParent)->m_pInven->InitDeleteItemInfo();
				}
			}
			else
			{
				// 2007-06-20 by bhsohn ������ ������, �޸� ���� ����
				//((CINFGameMain*)m_pParent->m_pParent)->m_pInven->m_pDeleteItem = NULL;
				((CINFGameMain*)m_pParent->m_pParent)->m_pInven->InitDeleteItemInfo();
			}
		}
		break;
		// 2007-09-05 by bhsohn ���� ������
	case _Q_INFLUENCE_WAR_EXPENCE_OK_MSG:
		{
			if(i == 0)
			{
				// OKŬ�� 
				int count = atoi(m_strInputMessage);
				OnSendRequestExpence(count);
			}
			else
			{

			}

		}
		break;
		// end 2007-09-05 by bhsohn ���� ������
	case _Q_ITEM_DELETE:
		{
			if(i == 0)
			{
				((CINFGameMain*)m_pParent->m_pParent)->m_pInven->DeleteSelectItem(1);
			}
			else
			{
				// 2007-06-20 by bhsohn ������ ������, �޸� ���� ����
				//((CINFGameMain*)m_pParent->m_pParent)->m_pInven->m_pDeleteItem = NULL;
				((CINFGameMain*)m_pParent->m_pParent)->m_pInven->InitDeleteItemInfo();
			}
		}
		break;
	case _Q_ITEM_DELETE_SKILL:
		{
			if(i == 0)
			{
				g_pGameMain->m_pCharacterInfo->SendDeleteSelectItemSkill();
			}
			else
			{
				g_pGameMain->m_pCharacterInfo->m_pDeleteSkill = NULL;
			}

		}
		break;
	case _Q_TRADE_ITEM_NUMBER:
		{
			if(i == 0)
			{
				int count = atoi(m_strInputMessage);
				if( count > 0 )
				{
					((CINFGameMain*)m_pParent->m_pParent)->m_pTrade->SendTradeTrans(count);
				}

			}
		}
		break;
	case _Q_PUT_ITEM_SPI:
		{
			if( i==0)
			{
				int count = atoi(m_strInputMessage);
				if( count > 0 && 
					g_pGameMain->m_pInven->GetItemSpi()-count>=30)
				{
					CINFCityStore* pStore = (CINFCityStore*)g_pInterface->m_pCityBase->FindBuildingShop(BUILDINGKIND_STORE);
					if(pStore)
					{
						pStore->FieldSocketSendItemToStore(g_pGameMain->m_pInven->GetItemSpiUniqueNumber(), count);
					}
				}
				else
				{
					g_pD3dApp->m_pChat->CreateChatChild(STRERR_ERROR_0103,COLOR_ERROR);	// "SPI�� �����Ͽ� â�� �̿� �� �� �����ϴ�."
				}
			}
		}
		break;
	case _Q_GET_ITEM_SPI:
		{
			if(i==0)
			{
				int count = atoi(m_strInputMessage);
				if( count > 0 )
				{
					CINFCityStore* pStore = (CINFCityStore*)g_pInterface->m_pCityBase->FindBuildingShop(BUILDINGKIND_STORE);
					if(pStore)
					{
						pStore->FieldSocketSendItemToCharacter(pStore->GetItemSpiUniqueNumber(), count);
					}
				}

			}
		}
		break;
	case _Q_PK_REQUEST:
		{
			// 2015-06-27 Future, remove the User Info again
			g_pGameMain->m_pCommunity->HideUserInfo();

			if(i == 0)
			{
				MSG_FC_BATTLE_ACCEPT_REQUEST_P2P_PK sMsg;
				memset(&sMsg,0x00,sizeof(sMsg));
				char buffer[SIZE_MAX_PACKET];
				int nType = T_FC_BATTLE_ACCEPT_REQUEST_P2P_PK;
				sMsg.SourceClientIndex = m_dwData;
				memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
				memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
				g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
				if(g_pGameMain->m_pOtherCharInfo != NULL)
					g_pGameMain->m_pOtherCharInfo->m_bRenderInfo = FALSE;
			}
			else
			{
				MSG_FC_BATTLE_REJECT_REQUEST_P2P_PK sMsg;
				memset(&sMsg,0x00,sizeof(sMsg));
				char buffer[SIZE_MAX_PACKET];
				int nType = T_FC_BATTLE_REJECT_REQUEST_P2P_PK;
				sMsg.SourceClientIndex = m_dwData;
				memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
				memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
				g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
				m_dwData = 0;
				if(g_pGameMain->m_pOtherCharInfo != NULL)
					g_pGameMain->m_pOtherCharInfo->m_bRenderInfo = FALSE;
			}
		}
		break;

	case _Q_PK_LOSE_REQUEST_OK:
		{
			if(i == 0)
			{
				MSG_FC_BATTLE_ACCEPT_SURRENDER_P2P_PK sMsg;
				memset(&sMsg,0x00,sizeof(sMsg));
				char buffer[SIZE_MAX_PACKET];
				int nType = T_FC_BATTLE_ACCEPT_SURRENDER_P2P_PK;
				sMsg.SourceClientIndex = m_dwData;
				memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
				memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
				g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
			}
			else
			{
				MSG_FC_BATTLE_REJECT_SURRENDER_P2P_PK sMsg;
				memset(&sMsg,0x00,sizeof(sMsg));
				char buffer[SIZE_MAX_PACKET];
				int nType = T_FC_BATTLE_REJECT_SURRENDER_P2P_PK;
				sMsg.SourceClientIndex = m_dwData;
				memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
				memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
				g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
			}
		}
		break;
	case _Q_DEAD_RETURN:
		{
			g_pShuttleChild->m_bIsCameraPattern = FALSE;
			if(g_pShuttleChild->m_bAttackMode == _SIEGE)			// ������� ������ �Ϲݻ��·� ���� 
			{
				g_pShuttleChild->m_pEngine->ChangeBodyCondition(BODYCON_SIEGE_OFF_MASK);
				g_pShuttleChild->m_bAttackMode = _AIR;
//				g_pShuttleChild->m_bPrimaryAttackMode = 0;//(BYTE)fValue;
//				g_pShuttleChild->m_bSecondaryAttackMode = 0;//(BYTE)fValue;
			}
			
			// 2010. 03. 25 by ckPark ����� 5���̻� �߶��ϸ� ��Ȱ�޼��� �߰�
			//if(COMPARE_BODYCON_BIT(g_pShuttleChild->GetCurrentBodyCondition(),BODYCON_DEAD_MASK|BODYCON_EXPLOSION_MASK) )
			if( g_pShuttleChild->m_dwState == _FALLING ||
				COMPARE_BODYCON_BIT(g_pShuttleChild->GetCurrentBodyCondition(), BODYCON_DEAD_MASK|BODYCON_EXPLOSION_MASK) )
			// end 2010. 03. 25 by ckPark ����� 5���̻� �߶��ϸ� ��Ȱ�޼��� �߰�
			{
				MSG_FC_CHARACTER_DEAD_GAMESTART sMsg;
				memset(&sMsg,0x00,sizeof(sMsg));
				char buffer[SIZE_MAX_PACKET];
				int nType = T_FC_CHARACTER_DEAD_GAMESTART;
				sMsg.ClientIndex = g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.ClientIndex;
				sMsg.CharacterUniqueNumber = g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.CharacterUniqueNumber;
				sMsg.bRebirthInCityMap		= FALSE;
				if(i == 0)
				{
					sMsg.bRebirthInCityMap	= TRUE;
				}
				memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
				memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
				g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
			}			
		}
		break;
	case _Q_SHOP_SELL_ENERGY:
		{
			if(i == 0)
			{
				int count = atoi(m_strInputMessage);
				if( count >0 )
				{
					CItemInfo* pItem = (CItemInfo*)m_dwData;
					if( count <= pItem->CurrentCount )
					{
//						((CINFGameMain*)m_pParent->m_pParent)->m_pShop->SellItem(pItem->UniqueNumber, count, pItem->Kind);
						if( g_pInterface->m_pCityBase->GetCurrentBuildingNPC() &&
							(IS_ITEM_SHOP_TYPE(g_pInterface->m_pCityBase->GetCurrentBuildingNPC()->buildingInfo.BuildingKind)
							|| IS_WARPOINT_SHOP_TYPE(g_pInterface->m_pCityBase->GetCurrentBuildingNPC()->buildingInfo.BuildingKind)))
						{
							CINFCityShop * pCityShop = (CINFCityShop*)g_pInterface->m_pCityBase->FindBuildingShop(g_pInterface->m_pCityBase->GetCurrentBuildingNPC()->buildingInfo.BuildingKind);
							pCityShop->SellItem(pItem->UniqueNumber, count, pItem->Kind);
						}
					}
				}
			}
		}
		break;
	case _Q_STORE_PUT_COUNTABLE_ITEM:
		{
			if(i == 0)
			{
				int count = atoi(m_strInputMessage);
				if( count >0 )
				{
					CItemInfo* pItem = (CItemInfo*)m_dwData;
					if( count <= pItem->CurrentCount )
					{
						CINFCityStore* pStore = (CINFCityStore*)g_pInterface->m_pCityBase->FindBuildingShop(BUILDINGKIND_STORE);
						if(pStore)
						{
							// 2006-08-08 by ispark, �ѹ� �� �������� ���� ������ �Ǵ�
							if(pItem->Wear == WEAR_NOT_ATTACHED )
							{
								pStore->FieldSocketSendItemToStore(pItem->UniqueNumber, count);
							}
							else
							{
								g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_STORE_0006,COLOR_ERROR);	// "������ �������� �ñ� �� �����ϴ�."
							}
						}
					}
				}
			}
		}
		break;
	case _Q_INPUT_AUCTION_PRICE:
		{
			if(i == 0)
			{
				int count = atoi(m_strInputMessage);
				if( count >0 )
				{
					MSG_FC_AUCTION_REGISTER_ITEM sMsg;
					sMsg.ItemUID = m_dwData;
					sMsg.Price	= count;
					g_pFieldWinSocket->SendMsg( T_FC_AUCTION_REGISTER_ITEM, (char*)&sMsg, sizeof(sMsg) );					
				}
				else
				{
					g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_AUCTION_0009,COLOR_SYSTEM);//"��� ������ �ٽ� �Է��Ͻʽÿ�"
				}
			}			
		}
		break;
	case _Q_STORE_PUSH_ITEM:
		{
			if(i == 0)
			{
				int count = atoi(m_strInputMessage);
				if( count >0 )
				{
					CItemInfo* pItem = (CItemInfo*)m_dwData;
					if( count <= pItem->CurrentCount )
					{
						CINFCityStore* pStore = (CINFCityStore*)g_pInterface->m_pCityBase->FindBuildingShop(BUILDINGKIND_STORE);
						MSG_FC_STORE_MOVE_ITEM sMsg;
						sMsg.ItemUniqueNumber = pItem->UniqueNumber;
						sMsg.ToItemStorage = ITEM_IN_CHARACTER;
						g_pD3dApp->m_bRequestEnable = FALSE;
						// 2006-09-14 by dgwoo ���� â��.
						
						if(pStore->GetActTab() < SELECT_MODE)
						{// â���� ĳ���ͷ� ������ �̵�.
							sMsg.FromItemStorage	= ITEM_IN_STORE;
							
						}else
						{// ���� â���� ĳ���ͷ� ������ �̵�.
							sMsg.FromItemStorage		= ITEM_IN_GUILD_STORE;
						}
						sMsg.Count = count;
						g_pFieldWinSocket->SendMsg( T_FC_STORE_MOVE_ITEM, (char*)&sMsg, sizeof(sMsg) );
					}
					else
					{
						// �Է� ī���Ͱ� Ŭ��
						g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_060512_0000,COLOR_SYSTEM);//"������ ���� �����Դϴ�."
					}
				}
			}
		}
		break;
	case _Q_SHOP_SELL_ITEM:
		{
			if(i == 0)
			{
				CItemInfo* pItem = (CItemInfo*)m_dwData;
//				((CINFGameMain*)m_pParent->m_pParent)->m_pShop->SellItem(pItem->UniqueNumber, 1/*pItem->Count*/, pItem->Kind);
				if( g_pInterface->m_pCityBase->GetCurrentBuildingNPC() &&
					(IS_ITEM_SHOP_TYPE(g_pInterface->m_pCityBase->GetCurrentBuildingNPC()->buildingInfo.BuildingKind)
					|| IS_WARPOINT_SHOP_TYPE(g_pInterface->m_pCityBase->GetCurrentBuildingNPC()->buildingInfo.BuildingKind)))
				{
					CINFCityShop * pCityShop = (CINFCityShop*)g_pInterface->m_pCityBase->FindBuildingShop(g_pInterface->m_pCityBase->GetCurrentBuildingNPC()->buildingInfo.BuildingKind);
					pCityShop->SellItem(pItem->UniqueNumber, 1, pItem->Kind);
				}
			}
		}
		break;

		// 2007-02-12 by bhsohn Item ���� ���� ó��
	case _Q_SHOP_MULTI_SELL_ITEM:
		{
			// ���� 
			if(i == 0)
			{
				GUI_BUILDINGNPC* pGui = g_pInterface->m_pCityBase->GetCurrentBuildingNPC();
				if(  pGui &&
					(IS_ITEM_SHOP_TYPE(pGui->buildingInfo.BuildingKind)|| IS_WARPOINT_SHOP_TYPE(pGui->buildingInfo.BuildingKind)))
				{					
					g_pD3dApp->StartSellMultiItem();
				}
			}
		}
		break;
	case _Q_STORE_MULTI_PUT_ITEM:
		{
			if(i==0)
			{				
				CINFCityStore* pStore = (CINFCityStore*)g_pInterface->m_pCityBase->FindBuildingShop(BUILDINGKIND_STORE);
				if(pStore)
				{
					g_pD3dApp->StartToStoreMultiItem();					
				}				
			}
		}
		break;
	case _Q_STORE_MULTI_GET_ITEM:
		{
			if(i==0)
			{				
				CINFCityStore* pStore = (CINFCityStore*)g_pInterface->m_pCityBase->FindBuildingShop(BUILDINGKIND_STORE);
				if(pStore)
				{
					g_pD3dApp->StartFromStoreMultiItem();					
				}	

			}
		}
		break;
		// end 2007-02-12 by bhsohn Item ���� ���� ó��
	case _Q_AUCTION_INPUT_ITEM:
		{
			char buf[512];
			if(i == 0)
			{				
				wsprintf( buf, STRMSG_C_AUCTION_0010);//"��ǰ��������� �ø� ������ �󸶷� �Ͻðڽ��ϱ�?[����:(����)]"
				((CINFWindow*)m_pParent)->AddMsgBox(buf, _Q_INPUT_AUCTION_PRICE,
					m_dwData);
				
			}
		}
		break;
	case _Q_AUCTION_DELETE_ITEM:
		{
			if(i == 0)
			{
				MSG_FC_AUCTION_CANCEL_REGISTER sMsg;
				sMsg.ItemUID =  m_dwData;
				g_pFieldWinSocket->SendMsg( T_FC_AUCTION_CANCEL_REGISTER, (char*)&sMsg, sizeof(sMsg) );
			}
		}
		break;
	case _Q_STORE_PUT_ITEM:
		{
			if(i == 0)
			{
				CItemInfo* pItem = (CItemInfo*)m_dwData;
				CINFCityStore* pStore = (CINFCityStore*)g_pInterface->m_pCityBase->FindBuildingShop(BUILDINGKIND_STORE);
				if(pStore)
				{
					// 2006-08-08 by ispark, �ѹ� �� �������� ���� ������ �Ǵ�
					if(pItem->Wear == WEAR_NOT_ATTACHED )
					{
						// 2013-06-13 by ssjung ���� ���� �÷��� ����ó�� �߰�(���� ������ �ȵǾ� �� �κп� ���� ������ �ȵ� �� �ֵ���)
#ifdef SC_COLLECTION_ARMOR_JHSEOL_BCKIM
						if(pItem->FixedTermShape.nStatShapeItemNum && pItem->FixedTermShape.nStatLevel)
						{
							g_pStoreData->RqCollectionShapeChange(pItem->UniqueNumber,0);
						}
#endif
						//end 2013-06-13 by ssjung ���� ���� �÷��� ����ó�� �߰�(���� ������ �ȵǾ� �� �κп� ���� ������ �ȵ� �� �ֵ���)

						pStore->FieldSocketSendItemToStore(pItem->UniqueNumber, 1);
					}
					else
					{
						g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_STORE_0006,COLOR_ERROR);	// "������ �������� �ñ� �� �����ϴ�."
					}
				}
			}
		}
		break;
	case _Q_USE_ENCHANT_ITEM_CARD:
		{
			if(i == 1)//���
			{
				((CINFGameMain*)m_pParent->m_pParent)->m_pInven->m_bEnchantState = FALSE;
				((CINFGameMain*)m_pParent->m_pParent)->m_pInven->m_pEnchantItem = NULL;
//				((CINFGameMain*)m_pParent->m_pParent)->m_pInven->m_pSelectIcon = NULL;
			}
		}
		break;
	case _Q_REQUEST_PARTY_BATTLE:
		{
			if(i == 0)
			{
				MSG_FC_REQUEST_ACCEPT_REQUEST sMsg;
				memset(&sMsg,0x00,sizeof(sMsg));
				char buffer[SIZE_MAX_PACKET];
				int nType = T_FC_REQUEST_ACCEPT_REQUEST;
				sMsg.SourceClientIndex = m_dwData;
				sMsg.RequestType = REQUEST_TYPE_PARTY_BATTLE;
				memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
				memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
				g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
			}
			else if(i == 1)//���
			{
				MSG_FC_REQUEST_REJECT_REQUEST sMsg;
				memset(&sMsg,0x00,sizeof(sMsg));
				char buffer[SIZE_MAX_PACKET];
				int nType = T_FC_REQUEST_REJECT_REQUEST;
				sMsg.SourceClientIndex = m_dwData;
				sMsg.RequestType = REQUEST_TYPE_PARTY_BATTLE;
				memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
				memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
				g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
				// ����� �޴� ��� �� ����
				g_pGameMain->m_pCommunity->GetParty()->SetEnablePartyMenu(TRUE);		
			}
		}
		break;
	case _Q_REQUEST_GUILD_WAR:
		{
			if(i == 0)
			{
				MSG_FC_REQUEST_ACCEPT_REQUEST sMsg;
				memset(&sMsg,0x00,sizeof(sMsg));
				sMsg.SourceClientIndex = m_dwData;
				sMsg.RequestType = REQUEST_TYPE_GUILD_WAR;
				g_pFieldWinSocket->SendMsg( T_FC_REQUEST_ACCEPT_REQUEST, (char*)&sMsg, sizeof(sMsg) );
			}
			else if(i == 1)//���
			{
				MSG_FC_REQUEST_REJECT_REQUEST sMsg;
				memset(&sMsg,0x00,sizeof(sMsg));
				sMsg.SourceClientIndex = m_dwData;
				sMsg.RequestType = REQUEST_TYPE_GUILD_WAR;
				g_pFieldWinSocket->SendMsg( T_FC_REQUEST_REJECT_REQUEST, (char*)&sMsg, sizeof(sMsg) );
				// ����� �޴� ��� �� ����
				g_pGameMain->m_pCommunity->GetParty()->SetEnablePartyMenu(TRUE);
			}
		}
		break;
	case _Q_SELECT_DELETE:
		{
			g_pSelect->m_bDelete = FALSE;
			m_strInputMessage[strlen(m_strInputMessage)-1] = NULL;// '_'���� ����
			// 2006-05-22 by ispark, strcmp -> stricmp
			if(i == 0 && 0 == stricmp(g_pSelect->m_strDeleteCharacterName, m_strInputMessage))
			{
				MSG_FC_CHARACTER_DELETE sMsg;
				memset(&sMsg,0x00,sizeof(sMsg));
				char buffer[SIZE_MAX_PACKET];
				sMsg.AccountUniqueNumber = g_pD3dApp->m_accountUniqueNumber;
				int select = m_dwData;
				sMsg.CharacterUniqueNumber = g_pD3dApp->m_pInterface->m_pSelect->m_character[select].CharacterUniqueNumber;
				int nType = T_FC_CHARACTER_DELETE;
				memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
				memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
				g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));

				g_pD3dApp->m_bRequestEnable = FALSE;
			}
		}
		break;
	case _MESSAGE_ERROR_CREATE:
		{
			g_pSelect->m_pCreateMenu->m_bBlocking = FALSE;// ���� �Ŀ� ����Ű�� ������ Ǯ���ش�.
			g_pSelect->m_pCreateMenu->m_nFocus = -1;
		}
		break;
	case _MESSAGE_ERROR_NETWORK:
		{
			g_pD3dApp->ChangeGameState( _GAMEOVER );
		}
		break;
	case _Q_GUILD_CREATE:				// ����� ����
		{
			if(i == 0)
			{
				m_strInputMessage[strlen(m_strInputMessage)-1] = NULL;// '_'���� ����
				// ��,�� ' ' ���� ����
				int k = 0;
				while( m_strInputMessage[k] == ' ' )
				{
					k++;
				}
				if( k != 0 )
				{
					char buf[256];
					memset( buf, 0x00, 256 );
					memcpy( buf, m_strInputMessage+k, 256-k );
					memcpy( m_strInputMessage, buf, 256 );
				}
				k = strlen(m_strInputMessage)-1;
				if( k <= 0 )
				{
					break;
				}
				while( m_strInputMessage[k] == ' ' )
				{
					m_strInputMessage[k] = NULL;
					k--;
				}
				////////////////////////////

				// 2007-12-10 by bhsohn ���ܸ� ������ ��� �߰�
				BOOL bFilter = TRUE;
				char strInputMessageTmp[256];
				memset(strInputMessageTmp, 0x00, 256);
				strncpy(strInputMessageTmp, m_strInputMessage, 255);
				int temp,temp2;
				temp = temp2 = 0;
				g_pD3dApp->CheckReadyStringFiltering(strInputMessageTmp,&temp,&temp2);				
				
				if(temp2 > 0)
				{
					// ������ �ν�
					bFilter = FALSE;
				}
				// end 2007-12-10 by bhsohn ���ܸ� ������ ��� �߰�

				if(strlen(m_strInputMessage) < SIZE_MAX_GUILD_NAME && strlen(m_strInputMessage) > 0)				
				{
					if(bFilter)
					{
						// 2009-02-02 by bhsohn ���� ������ Ȯ��â �߰�
						char	szGuildName[SIZE_MAX_GUILD_NAME];
						util::strncpy(szGuildName, m_strInputMessage,SIZE_MAX_GUILD_NAME);						

						char chMsgBuff[256];
						ZERO_MEMORY(chMsgBuff);
						wsprintf(chMsgBuff, STRMSG_C_090203_0201, szGuildName);	//"[%s]���ܸ����� ������ ����ðڽ��ϱ�?"
						((CINFWindow*)m_pParent)->AddMsgBox(chMsgBuff, _Q_GUILD_CREATE_CONFIRM,0,0,0,0,szGuildName);
						
// 						MSG_IC_GUILD_CREATE sMsg;
// 						strcpy( sMsg.GuildName, m_strInputMessage );
// 						g_pIMSocket->SendMsg( T_IC_GUILD_CREATE, (char*)&sMsg, sizeof(sMsg));
						// end 2009-02-02 by bhsohn ���� ������ Ȯ��â �߰�
					}					
					else
					{						
						((CINFWindow*)m_pParent)->AddMsgBox( STRMSG_C_060412_0001, _MESSAGE );
					}
				}
				else
				{
					((CINFWindow*)m_pParent)->AddMsgBox( STRERR_C_GUILD_0001, _MESSAGE );
				}
			}
		}
		break;
		// 2009-02-02 by bhsohn ���� ������ Ȯ��â �߰�
	case _Q_GUILD_CREATE_CONFIRM:
		{
			if(i ==0)
			{
				MSG_IC_GUILD_CREATE sMsg;
				util::strncpy( sMsg.GuildName, m_strInputMessage, SIZE_MAX_GUILD_NAME);
				g_pIMSocket->SendMsg( T_IC_GUILD_CREATE, (char*)&sMsg, sizeof(sMsg));
			}
		}
		break;
		// end 2009-02-02 by bhsohn ���� ������ Ȯ��â �߰�
	case _Q_GUILD_INVITE:				// ����� �ʴ�, 
		{
			if( i == 0 )
			{
				m_strInputMessage[strlen(m_strInputMessage)-1] = NULL;// '_'���� ����
				// 2008-07-14 by bhsohn EP3 ���� ó��
				if(g_pGameMain->IsRejectUser(m_strInputMessage))
				{
					g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080714_0207,COLOR_ERROR);//"\\y�ź� ��Ͽ� ��ϵ� ����Դϴ�."
					break;
				}
				// end 2008-07-14 by bhsohn EP3 ���� ó��

				MSG_IC_GUILD_REQUEST_INVITE sMsg;
				strncpy( sMsg.InviteeCharacterName, m_strInputMessage, SIZE_MAX_CHARACTER_NAME );
				g_pIMSocket->SendMsg( T_IC_GUILD_REQUEST_INVITE, (char*)&sMsg, sizeof(sMsg));
			}
		}
		break;
	case _Q_GUILD_MARK:				// ��� ���� ����(���� �̸� �Է�) ���� �������� ����
		{
			if( i == 0 )
			{
				m_strInputMessage[strlen(m_strInputMessage)-1] = NULL;// '_'���� ����
				((CINFCommunityGuild*)m_dwData)->IMSocketSendGuildMark(m_strInputMessage);
			}
		}
		break;
	case _Q_GUILD_INVITE_QUESTION:
		{
			if( i == 0 )// �ʴ� ����
			{
				MSG_IC_GUILD_ACCEPT_INVITE sMsg;
				sMsg.GuildUniqueNumber = (UINT)m_dwData;
				g_pIMSocket->SendMsg( T_IC_GUILD_ACCEPT_INVITE, (char*)&sMsg, sizeof(sMsg));
			}
			else// ����
			{
				MSG_IC_GUILD_REJECT_INVITE sMsg;
				sMsg.GuildUniqueNumber = (UINT)m_dwData;
				g_pIMSocket->SendMsg( T_IC_GUILD_REJECT_INVITE, (char*)&sMsg, sizeof(sMsg));
			}
		}
		break;
	case _Q_GUILD_BAN_MEMBER:			// �߹�, m_dwData:�߹��� ����
		{
			if( i == 0 )
			{
				MSG_IC_GUILD_BAN_MEMBER sMsg;
				sMsg.MemberUniqueNumber = (UINT)m_dwData;
				g_pIMSocket->SendMsg( T_IC_GUILD_BAN_MEMBER, (char*)&sMsg, sizeof(sMsg));
			}
		}
		break;
	case _Q_GUILD_LEAVE:				// Ż��
		{
			if( i == 0 )
			{
				MSG_IC_GUILD_LEAVE sMsg;
				sMsg.GuildUniqueNumber = (UINT)m_dwData;
				g_pIMSocket->SendMsg( T_IC_GUILD_LEAVE, (char*)&sMsg, sizeof(sMsg));
			}
		}
		break;
	case _Q_GUILD_DISBAND:			// ����� ��ü
		{
			if( i == 0 )
			{
				MSG_IC_GUILD_DISMEMBER sMsg;
				sMsg.GuildUniqueNumber = (UINT)m_dwData;
// 2007-11-12 by dgwoo T_IC_GUILD_DISMEMBER -> T_FC_GUILD_DISMEMBER ����.
//				g_pIMSocket->SendMsg( T_IC_GUILD_DISMEMBER, (char*)&sMsg, sizeof(sMsg));
				g_pFieldWinSocket->SendMsg( T_FC_GUILD_DISMEMBER, (char*)&sMsg, sizeof(sMsg));
			}
		}
		break;
	case _Q_GUILD_CANCEL:			// ����� ��ü ���
		{
			if( i == 0 )
			{
				MSG_IC_GUILD_CANCEL_DISMEMBER sMsg;
				sMsg.GuildUniqueNumber = (UINT)m_dwData;
				g_pIMSocket->SendMsg( T_IC_GUILD_CANCEL_DISMEMBER, (char*)&sMsg, sizeof(sMsg));
			}
		}
		break;
	case _Q_BATTLE_NAME:
		{
			if(i == 0)
			{
				// 2009-01-12 by bhsohn �Ϻ� �߰� ��������
				BOOL bRqPvP = FALSE;
				// end 2009-01-12 by bhsohn �Ϻ� �߰� ��������

				m_strInputMessage[strlen(m_strInputMessage)-1] = NULL;// '_'���� ����
				CMapEnemyIterator itEnemy = g_pScene->m_mapEnemyList.begin();
				while(itEnemy != g_pScene->m_mapEnemyList.end())
				{
					// 2006-05-22 by ispark, strcmp -> stricmp
					if(!stricmp(itEnemy->second->m_infoCharacter.CharacterInfo.CharacterName, m_strInputMessage))
					{
						// 2009-01-12 by bhsohn �Ϻ� �߰� ��������
						bRqPvP = TRUE;
						// end 2009-01-12 by bhsohn �Ϻ� �߰� ��������

						// 2006-01-07 by ispark, ���� ��
#ifdef FREEWAR_
						if (!IsInfluenceCharacter(g_pShuttleChild->m_myShuttleInfo.InfluenceType, itEnemy->second->m_infoCharacter.CharacterInfo.InfluenceType, 1, g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex))
#else
						if(!IsInfluenceCharacter(g_pShuttleChild->m_myShuttleInfo.InfluenceType, itEnemy->second->m_infoCharacter.CharacterInfo.InfluenceType))
#endif
						{
							// 2006-01-07 by ispark, ���� �ٸ� ���³��� ���� �ȵ�
							g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_051208_0102, COLOR_ERROR);// "���� �ٸ� ���³��� ������ �� �� �����ϴ�."
							break;
						}

						// 2005-11-03 by ispark
						// ���� ĳ���Ͱ� �ٸ� ���¶�� 1:1��û ��ȿ.
						if((g_pD3dApp->m_bCharacter == FALSE && itEnemy->second->m_infoCharacter.CharacterInfo.CharacterMode0 == FALSE) ||
							(g_pD3dApp->m_bCharacter == TRUE && itEnemy->second->m_infoCharacter.CharacterInfo.CharacterMode0 == TRUE))
						{
							MSG_FC_BATTLE_REQUEST_P2P_PK sMsg;
							sMsg.TargetClientIndex =  itEnemy->second->m_infoCharacter.CharacterInfo.ClientIndex;
							sMsg.AdditionalParameter = g_pD3dApp->m_nPVPoption;
							g_pFieldWinSocket->SendMsg(T_FC_BATTLE_REQUEST_P2P_PK, (char*)&sMsg, sizeof(sMsg) );
							g_fSendMovePacket = max(g_fSendMovePacket,20.0f);
							break;
						}
						else
						{
							g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_051102_0002, COLOR_ERROR);//"PVP �� ��밡 ĳ�����̰ų� �� �ڽ��� ĳ�����̹Ƿ� ����� �Ұ����մϴ�."
							break;
						}
					}
					itEnemy++;
				}
				// 2009-01-12 by bhsohn �Ϻ� �߰� ��������
				if(!bRqPvP)
				{
					g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_090112_0201, COLOR_ERROR);//"PVP �� ��밡 ĳ�����̰ų� �� �ڽ��� ĳ�����̹Ƿ� ����� �Ұ����մϴ�."							
				}
				// end 2009-01-12 by bhsohn �Ϻ� �߰� ��������
			}
			g_pD3dApp->m_bChatMode = FALSE;

			if(g_pD3dApp->RemoveINFCnt() == 0)
			{
				g_pGameMain->m_bChangeMousePoint = FALSE;
			}		
		}
		break;
	case _Q_OUTDOOR_WARP:
		{
			if(i == 0)
			{
				// 2004-10-25 by jschoi
				// �Ʒ� ��� ����� ��� �����Ѱ� ������ ��û�Ѵ�.
				// �������� Ȯ���� ������ �Ʒ� ���� �κ��� �����ϵ��� �Ѵ�.
				// �������� ������ �������ų� ��� �Ұ����� ������ ���� ������ ����Ѵ�.
				g_pShuttleChild->m_nEventType = EVENT_CITY_OUTDOOR;
				g_pFieldWinSocket->SendMsg(T_FC_CITY_CHECK_WARP_STATE, NULL, 0);

			}
		}
		break;
	case _Q_LAB_ITEM_NUMBER:
		{
			if(i == 0)
			{
				m_strInputMessage[strlen(m_strInputMessage)-1] = NULL;// '_'���� ����
				int nCount = atoi(m_strInputMessage);
				//pItem = g_pGameMain->m_pInven->m_pSelectItem;
				//((CINFCityLab*)m_dwData)->m_vecSource.push_back(pItem);
				if( nCount > 0 &&
					((CINFCityLab*)m_dwData)->m_pSelectItem->CurrentCount >= nCount)
				{
					((CINFCityLab*)m_dwData)->InvenToSourceItem(((CINFCityLab*)m_dwData)->m_pSelectItem, nCount);
				}
			}
			((CINFCityLab*)m_dwData)->m_pSelectItem = NULL;
			g_pD3dApp->m_bChatMode = FALSE;

				
		}
		break;
	case _Q_QUEST_DISCARD:
		{
			if(i == 0)
			{
				MSG_FC_QUEST_DISCARD_QUEST sMsg;
				sMsg.QuestIndex = (INT)m_dwData;
				g_pFieldWinSocket->SendMsg( T_FC_QUEST_DISCARD_QUEST, (char*)&sMsg, sizeof(sMsg) );
				if(g_pInterface->m_pCityBase->m_pMission->m_nCancerSelect < CITY_MISSION_MAX_NUMBER)
				g_pInterface->m_pCityBase->m_pMission->m_bProgressMission[g_pInterface->m_pCityBase->m_pMission->m_nCancerSelect] = FALSE;				

				// 2008-06-17 by bhsohn ��� ���� ó��
				// ����Ʈ ����
				if(g_pShuttleChild->m_pClientParty 
					&& g_pShuttleChild->m_pClientParty->GetPartyInfo().bPartyType == _PARTYMASTER 
					&& g_pShuttleChild->m_pClientParty->IsFormationFlight())
				{
					g_pShuttleChild->m_pClientParty->TempPartyFormation(FLIGHT_FORM_NONE);
				}
				// end 2008-06-17 by bhsohn ��� ���� ó��

			}
		}
		break;
	case _Q_USE_HELP_SYSTEM:
		{
			if(i == 0)
			{
				g_pGameMain->InitHelpSystem(TRUE);
			}
		}
		break;
	case _Q_ADD_FRIEND:
		{
			if(i == 0)
			{
				m_strInputMessage[strlen(m_strInputMessage)-1] = '\0';// '_'���� ����
				//g_pGameMain->m_pCommunity->GetFriend()->AddFriendList(m_strInputMessage);
				// 2006-05-22 by ispark, strcmp -> stricmp
				if(stricmp(g_pShuttleChild->m_myShuttleInfo.CharacterName, m_strInputMessage) == 0)
				{
					g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_COMMUNITY_0005,COLOR_SYSTEM);//"�ڽ��� ĳ���� �̸��� ģ���� ��� �� �� �����ϴ�."
				}
				else if(strlen(m_strInputMessage) == 0)
				{
					g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_COMMUNITY_0006,COLOR_SYSTEM);//"ģ���� ����Ͻ� ĳ���� �̸��� �Է��ϼ���."
				}				
				// 2008-07-14 by bhsohn EP3 ���� ó��
				else if(g_pGameMain->IsRejectUser(m_strInputMessage))
				{
					g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080714_0207,COLOR_ERROR);//"\\y�ź� ��Ͽ� ��ϵ� ����Դϴ�."					
				}
				// end 2008-07-14 by bhsohn EP3 ���� ó��
				else
				{
					MSG_IC_CHAT_FRIENDLIST_INSERT sMsg;
					strncpy(sMsg.szCharacterName, m_strInputMessage, SIZE_MAX_CHARACTER_NAME);
					g_pIMSocket->SendMsg( T_IC_CHAT_FRIENDLIST_INSERT, (char*)&sMsg, sizeof(sMsg) );
				}
			}
		}
		break;
	case _Q_DELETE_FRIEND:
		{
			if(i == 0)
			{
				// 2008-04-04 by bhsohn Ep3 Ŀ�´�Ƽ â
				//g_pGameMain->m_pCommunity->GetFriend()->m_bDeleteOK = TRUE;
				g_pGameMain->m_pCommunity->GetFriend()->SendFriendDelete();
			}			
		}
		break;
	case _Q_ADD_REJECT:
		{
			if(i == 0)
			{
				m_strInputMessage[strlen(m_strInputMessage)-1] = '\0';// '_'���� ����
				//g_pGameMain->m_pCommunity->GetReject()->AddRejectList(m_strInputMessage);
				// 2006-05-22 by ispark, strcmp -> stricmp
				if(stricmp(g_pShuttleChild->m_myShuttleInfo.CharacterName, m_strInputMessage) == 0)
				{
					g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_COMMUNITY_0007,COLOR_SYSTEM);//"�ڽ��� ĳ���� �̸��� �źη� ��� �� �� �����ϴ�"
				}
				else if(strlen(m_strInputMessage) == 0)
				{
					g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_COMMUNITY_0008,COLOR_SYSTEM);//"�źη� ����Ͻ� ĳ���� �̸��� �Է��ϼ���."
				}				
				else
				{
				MSG_IC_CHAT_REJECTLIST_INSERT sMsg;
				strncpy(sMsg.szCharacterName, m_strInputMessage, SIZE_MAX_CHARACTER_NAME);
				g_pIMSocket->SendMsg( T_IC_CHAT_REJECTLIST_INSERT, (char*)&sMsg, sizeof(sMsg) );
				}
			}			
		}
		break;
		
	case _Q_DELETE_REJECT:
		
		if(i == 0) g_pGameMain->m_pCommunity->GetReject()->SendDeleteRejectList();
		
		break;
		
	case _Q_TEX_SET:
		{
			if(i == 0)
			{
				if(m_nAllCurrentData > (int)(CITYWAR_MAXIMUM_TEX_PERCENT))
				{
					g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_OCCUPY_0021, COLOR_SYSTEM);//"������ �ʹ� ���� ���� �Ͽ����ϴ�."
					break;
				}
				else if(m_nAllCurrentData < (int)(CITYWAR_MINIMUM_TEX_PERCENT))
				{
					g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_OCCUPY_0022, COLOR_SYSTEM);//"�ּ� ������ 2% �Դϴ�."
					break;
				}

				float ftemp = (float)m_nAllCurrentData;

				MSG_FC_CITYWAR_SET_TEX sMsg;
				sMsg.fSetTex		= ftemp;
				g_pFieldWinSocket->SendMsg( T_FC_CITYWAR_SET_TEX, (char*)&sMsg, sizeof(sMsg) );
			}
		}
		break;
	case _Q_DATE_WAR:
		{
			if(i == 0)
			{
				if(strlen(m_strInputMessage) != 13)
				{
					g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_OCCUPY_0023, COLOR_SYSTEM);//"��¥�� �߸��ԷµǾ����ϴ�."
					break;
				}
				char strtemp[SIZE_MAX_CHAT_MESSAGE];
				char tempDay[5][16];
				memset(strtemp, 0x00, SIZE_MAX_CHAT_MESSAGE);
				memset(tempDay, 0x00, 5*16);

				CINFCityOccupy* pCityOccupy = NULL;
				CMapCityShopIterator it = g_pInterface->m_pCityBase->m_mapCityShop.find(BUILDINGKIND_CITY_OCCUPY_INFO);
				if(it != g_pInterface->m_pCityBase->m_mapCityShop.end())
				{
					pCityOccupy = ((CINFCityOccupy*)it->second);		
				}
				if(pCityOccupy == NULL)
					return;			

				strncpy(strtemp, m_strInputMessage, strlen(m_strInputMessage)-1);
				ATUM_DATE_TIME tempTime;
				tempTime = pCityOccupy->m_pTimeDef; // ����Ʈ Ÿ��
				tempTime.AddDateTime(0, 0, 0, TIMEGAP_CITYWAR_CHANGEABLE_TERM_HOUR, 0, 0);

				memcpy(tempDay[0], m_strInputMessage, 4);
				memcpy(tempDay[1], m_strInputMessage+4, 2);
				memcpy(tempDay[2], m_strInputMessage+6, 2);
				memcpy(tempDay[3], m_strInputMessage+8, 2);
				memcpy(tempDay[4], m_strInputMessage+10, 2);

				ATUM_DATE_TIME setTime;
				setTime.Year	= atoi(tempDay[0]);		// ��
				setTime.Month	= atoi(tempDay[1]);		// ��
				setTime.Day		= atoi(tempDay[2]);		// ��
				setTime.Hour	= atoi(tempDay[3]);		// ��
				setTime.Minute	= atoi(tempDay[4]);		// ��

				if(setTime < pCityOccupy->m_pTimeDef 
					|| setTime > tempTime)
				{
					g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_OCCUPY_0023, COLOR_SYSTEM);
					break;
				}

				MSG_FC_CITYWAR_SET_SETTINGTIME sMsg;
				memset(&sMsg, 0x00, sizeof(MSG_FC_CITYWAR_SET_SETTINGTIME));
				sMsg.atimeSetCityWarSettingTime = setTime;
				g_pFieldWinSocket->SendMsg( T_FC_CITYWAR_SET_SETTINGTIME, (char*)&sMsg, sizeof(sMsg) );
			}
		}
		break;
	case _Q_STORE_USE:
		{
			if(i == 0)
			{
			}
		}
		break;
	case _Q_GREATING_SET:
		{
			if(i == 0)
			{
				MSG_FC_CITYWAR_SET_BRIEFING sMsg;
				memset(&sMsg, 0x00, sizeof(MSG_FC_CITYWAR_SET_BRIEFING));
				strncpy(sMsg.szSetBriefing, m_strInputMessage, strlen(m_strInputMessage)-1);
				g_pFieldWinSocket->SendMsg( T_FC_CITYWAR_SET_BRIEFING, (char*)&sMsg, sizeof(sMsg) );
			}
		}
		break;
	case _Q_INPUT_SERIAL_NUM:
		{
			if(i == 0)
			{
				char buff[SIZE_MAX_COUPON_NUMBER];
				memset(buff, 0x00, SIZE_MAX_COUPON_NUMBER);
				strncpy(buff, m_strInputMessage, strlen(m_strInputMessage)-1);
				if(strlen(buff)<=0|| strlen(buff)>SIZE_MAX_COUPON_NUMBER)
				{
					g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_ETC_0004, COLOR_ERROR);//"���� ��ȣ �Է��� �߸��Ǿ����ϴ�."
					break;
				}
				g_pQuestData->SendFieldSocketQuestRequestStart(m_dwData,0,FALSE,buff);
			}
		}
		break;
	case _Q_MP3_PLAYLIST_DEL:
		{
			if( i ==0 )
			{
				g_pGameMain->m_pMp3Player->DeleteSelectPlayList();
			}
		}
		break;
	case _Q_QUIT_MESSAGE:
		{
			g_pGameMain->m_pSystem->m_bQuitGameMessage = FALSE;
			g_pGameMain->m_pSystem->m_fTickSecTime = 0.0f;
			g_pGameMain->m_pSystem->m_fLastTickSecTime = 0.0f;

			// 2012-12-21 by bhsohn ��Ʈ�� ���� ���� �ȵǴ� ���� �ذ�
			g_pD3dApp->SetClientLogOff(FALSE);
			// END 2012-12-21 by bhsohn ��Ʈ�� ���� ���� �ȵǴ� ���� �ذ�
			
			if(TRUE == g_pGameMain->m_pSystem->m_bLogOffGameMessage)
				g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_INTERFACE_0042, COLOR_SYSTEM);//"�α׿����� ��� �Ǿ����ϴ�."
			else					
				g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_INTERFACE_0043, COLOR_SYSTEM);//"�������ᰡ ��� �Ǿ����ϴ�."
			
			g_pGameMain->m_pSystem->m_bLogOffGameMessage = FALSE;
		}
		break;
	case _Q_MP3_DIRECTORY:
		{
			if( i ==0 )
			{
				char buff[MAX_PATH];
				memset(buff, 0x00, MAX_PATH);

				if(strlen(m_strInputMessage)>0)
				{
					char temp[MAX_PATH];
					memset(temp, 0x00, MAX_PATH);

					strncpy(buff, m_strInputMessage, strlen(m_strInputMessage)-1);
					int nCnt=0;
					for(int i=0; i<strlen(buff); i++) 
					{						
						if(buff[i] == '/')
						{
							strncpy(&temp[nCnt], "\\", 1);							
						}
						else
						{
							temp[nCnt] = buff[i];							
						}
						nCnt++;
					}

					strcat(temp, "\\*.mp3");
					strncpy(buff, temp, strlen(temp));
				}
				else
				{
					GetCurrentDirectory( MAX_PATH, buff );
					strcat(buff, "\\*.mp3");
				}
				g_pGameMain->m_pMp3Player->SetMp3Directory(buff);
				g_pGameMain->m_pMp3Player->FindMp3File();
				g_pGameMain->m_pMp3Player->RandomPlayList();
				g_pGameMain->m_pMp3Player->m_pScroll->SetNumberOfData( g_pGameMain->m_pMp3Player->m_vecMp3FileNames.size() );
			}
		}
		break;
	case _Q_GET_TEX:
		{
			if(i == 0)
			{
				g_pFieldWinSocket->SendMsg( T_FC_CITYWAR_BRING_SUMOFTEX, NULL, 0 );
			}
		}
		break;
	case _Q_CASHITEM_BUY:
		{
			if(i == 0)
			{
				g_pGameMain->m_bSendCashItemBuy = TRUE;
			}
			// 2008-08-13 by dgwoo ���� �޽���â�� ��������쿣 ��ũ�� �� �ٸ� ��Ʈ���� �ȵǵ��� ����.
			g_pGameMain->m_bBuyMessage		= FALSE;

		}
		break;
	case  _Q_CASHITEM_SHOP_OPEN:
		{
			if(i == 0)
			{
				g_pGameMain->m_pChat->m_bCashShopOpen = TRUE;
				g_pGameMain->m_pChat->EnterCashShop();
			}
		}
		break;
	case _Q_SUPER_RESTORE:
		{
			if(i == 0)
			{
				// 2005-03-25 by jschoi - ���� ��Ȱ ī�带 �����
				m_strInputMessage[strlen(m_strInputMessage)-1] = NULL;// '_'���� ����				
				MSG_FC_ITEM_USE_CARDITEM_RESTORE sMsg;
				memset(&sMsg,0x00,sizeof(sMsg));
				sMsg.ItemUniqueNumber = m_UniqueNumber;
				strncpy(sMsg.szCharacterName10, m_strInputMessage, strlen(m_strInputMessage));
				g_pFieldWinSocket->SendMsg( T_FC_ITEM_USE_CARDITEM_RESTORE, (char*)&sMsg, sizeof(sMsg) );

				g_pD3dApp->m_bChatMode = FALSE;
				g_pGameMain->m_bChangeMousePoint = FALSE;

			}
		}
		break;
	case _Q_USEITEM_NAME_CHANGE:
		{
			if(i == 0)
			{
				m_strInputMessage[strlen(m_strInputMessage)-1] = NULL;// '_'���� ����
				// 2007-12-13 by bhsohn ĳ���� �̸� ���� ī�� ���� ����
				//if(TRUE == g_pSelect->m_pCreateMenu->ErrCheckCharacterName(m_strInputMessage) && strlen(m_strInputMessage)<SIZE_MAX_CHARACTER_NAME)
				if(strlen(m_strInputMessage)<SIZE_MAXUSE_CHARACTER_NAME
					&& TRUE == g_pSelect->m_pCreateMenu->ErrCheckCharacterName(m_strInputMessage))
				{
					MSG_FC_ITEM_USE_CARDITEM_CHANGECHARACTERNAME sMsg;
					sMsg.ItemUniqueNumber = m_UniqueNumber;
					strcpy(sMsg.szChangeCharacterName, m_strInputMessage);
					g_pFieldWinSocket->SendMsg( T_FC_ITEM_USE_CARDITEM_CHANGECHARACTERNAME, (char*)&sMsg, sizeof(sMsg) );
				}
				else
				{
					// 2008-03-19 by bhsohn ĳ���͸� ����ī�� ���� ��Ʈ�� �߰�
					//g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_CARD_0009, COLOR_ERROR);//"ĳ���� �̸��� �߸� �Ǿ����ϴ�.(�ִ� �ѱ�9����, ���� 18����)"
					if(strlen(m_strInputMessage)>=SIZE_MAXUSE_CHARACTER_NAME)
					{						
						g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080320_0200, COLOR_ERROR);//"\yĳ���� ���� 14Byte�� �ʰ� �� �� �����ϴ�."
					}
					else
					{
						g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_CARD_0009, COLOR_ERROR);//"ĳ���� �̸��� �߸� �Ǿ����ϴ�.(�ִ� �ѱ�9����, ���� 18����)"
					}
					
					
				}
			}
		}
		break;

	// 2015-12-17 Future, Nation Change Card
	case _Q_USEITEM_NATION_CHANGE:
	{
		if (i == 0)
		{
			MSG_FC_ITEM_USE_CARDITEM_CHANGE_NATION_REQUEST sMsg;
			sMsg.ItemUniqueNumber = m_UniqueNumber;
			g_pFieldWinSocket->SendMsg(T_FC_ITEM_USE_CARDITEM_CHANGE_NATION_REQUEST, (char*)&sMsg, sizeof(sMsg));
		}
	}
	break;

		// 2008-12-30 by bhsohn ������ ä�� ���� ī�� ��ȹ��
	case _Q_USEITEM_LEADER_BAN_CHAT:
		{
			if(i == 0)
			{
				m_strInputMessage[strlen(m_strInputMessage)-1] = NULL;// '_'���� ����
			}
			UseLeaderBanChatTItem(i, m_strInputMessage);			
		}
		break;
		// end 2008-12-30 by bhsohn ������ ä�� ���� ī�� ��ȹ��
		// 2007-08-07 by bhsohn ����Ŀ ������ �߰�
	case _Q_USEITEM_SPEAKER_MSG:
		{
			if(i == 0)
			{
				m_strInputMessage[strlen(m_strInputMessage)-1] = NULL;// '_'���� ����				
			}
			UseSpeakerItem(i, m_strInputMessage);
		}
		break;
		// end 2007-08-07 by bhsohn ����Ŀ ������ �߰�
	case _Q_MEMBER_SUMMON:
		{
			if(i == 0)
			{
				// 2005-03-25 by jschoi - ���ܿ� �� �� ��ȯ
				m_strInputMessage[strlen(m_strInputMessage)-1] = NULL;// '_'���� ����
				MSG_FC_ITEM_USE_CARDITEM_GUILDSUMMON sMsg;
				memset(&sMsg,0x00,sizeof(sMsg));
				sMsg.ItemUniqueNumber = m_UniqueNumber;
				strncpy(sMsg.szCharacterName10, m_strInputMessage, strlen(m_strInputMessage));
				g_pFieldWinSocket->SendMsg( T_FC_ITEM_USE_CARDITEM_GUILDSUMMON, (char*)&sMsg, sizeof(sMsg) );
				
				g_pD3dApp->m_bChatMode = FALSE;				

			}
			g_pGameMain->m_bChangeMousePoint = FALSE;
		}
		break;
	case _Q_USE_SUPER_RESTORE:
		{
			if(i == 0)
			{// ���� ��Ȱ ī�� ��� ��
				// ������ ���� ��Ȱ ī�� ����Ѵ�.				
				MSG_FC_ITEM_USE_CARDITEM_RESTORE sMsg;
				memset(&sMsg,0x00,sizeof(sMsg));
				sMsg.ItemUniqueNumber = m_UniqueNumber;
				strncpy(sMsg.szCharacterName10, g_pShuttleChild->m_myShuttleInfo.CharacterName, strlen(g_pShuttleChild->m_myShuttleInfo.CharacterName));
				g_pFieldWinSocket->SendMsg( T_FC_ITEM_USE_CARDITEM_RESTORE, (char*)&sMsg, sizeof(sMsg) );

			}
			else
			{// ��� �� �Ϲ����� ���� ��ȯ�� �̷����.
				g_pShuttleChild->m_bIsCameraPattern = FALSE;
				if(g_pShuttleChild->m_bAttackMode == _SIEGE)			// ������� ������ �Ϲݻ��·� ���� 
				{
					g_pShuttleChild->m_pEngine->ChangeBodyCondition(BODYCON_SIEGE_OFF_MASK);
					g_pShuttleChild->m_bAttackMode = _AIR;
				}
				
				// 2010. 03. 25 by ckPark ����� 5���̻� �߶��ϸ� ��Ȱ�޼��� �߰�
				//if(COMPARE_BODYCON_BIT(g_pShuttleChild->GetCurrentBodyCondition(),BODYCON_DEAD_MASK|BODYCON_EXPLOSION_MASK) )
				if( g_pShuttleChild->m_dwState == _FALLING ||
				COMPARE_BODYCON_BIT(g_pShuttleChild->GetCurrentBodyCondition(), BODYCON_DEAD_MASK|BODYCON_EXPLOSION_MASK) )
				// end 2010. 03. 25 by ckPark ����� 5���̻� �߶��ϸ� ��Ȱ�޼��� �߰�
				{
					MSG_FC_CHARACTER_DEAD_GAMESTART sMsg;
					memset(&sMsg,0x00,sizeof(sMsg));
					char buffer[SIZE_MAX_PACKET];
					int nType = T_FC_CHARACTER_DEAD_GAMESTART;
					sMsg.ClientIndex = g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.ClientIndex;
					sMsg.CharacterUniqueNumber = g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.CharacterUniqueNumber;
					memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
					memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
					g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
				}
			}			
		}
		break;
	case _Q_USE_NORMAL_RESTORE:
		{
			if(i == 0)
			{// �Ϲ� ��Ȱ ī�� ��� ��
				// ������ �Ϲ� ��Ȱ ī�� ����Ѵ�.
				MSG_FC_ITEM_USE_CARDITEM_RESTORE sMsg;
				memset(&sMsg,0x00,sizeof(sMsg));
				sMsg.ItemUniqueNumber = m_UniqueNumber;
				g_pFieldWinSocket->SendMsg( T_FC_ITEM_USE_CARDITEM_RESTORE, (char*)&sMsg, sizeof(sMsg) );				
			}
			else
			{
				// 2013-04-05 by bhsohn ������ 5�� ��Ȱ �ý��� �߰�
				// 2006-04-10 by ispark, ��ҽ� �Ϲ� �޼����� ���´�.
//				g_pShuttleChild->SendDeadMsg();
				if(!bTimerClick)				
				{
					g_pShuttleChild->SendDeadMsg();
				}
				else
				{
					// Ÿ�̸ӷ� ����� ���̵� ��Ű�� 					
					// õ���� ��ȣ�ߵ��ÿ� ���� ó��
					SendCharacterDeadGameStart(FALSE);
				}

				// END 2013-04-05 by bhsohn ������ 5�� ��Ȱ �ý��� �߰�

				// ��� �� �Ϲ����� ���� ��ȯ�� �̷����.
//				g_pShuttleChild->m_bIsCameraPattern = FALSE;
//				if(g_pShuttleChild->m_bAttackMode == _SIEGE)			// ������� ������ �Ϲݻ��·� ���� 
//				{
//					g_pShuttleChild->m_pEngine->ChangeBodyCondition(BODYCON_SIEGE_OFF_MASK);
//					g_pShuttleChild->m_bAttackMode = _AIR;
//				}
//				
//				if(COMPARE_BODYCON_BIT(g_pShuttleChild->GetCurrentBodyCondition(),BODYCON_DEAD_MASK|BODYCON_EXPLOSION_MASK) )
//				{
//					MSG_FC_CHARACTER_DEAD_GAMESTART sMsg;
//					memset(&sMsg,0x00,sizeof(sMsg));
//					char buffer[SIZE_MAX_PACKET];
//					int nType = T_FC_CHARACTER_DEAD_GAMESTART;
//					sMsg.ClientIndex = g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.ClientIndex;
//					sMsg.CharacterUniqueNumber = g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.CharacterUniqueNumber;
//					memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
//					memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
//					g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
//				}
			}			
		}
		break;
	case _Q_UNIT_STOP:			// 2005-08-09 by ispark �������� �޼��� â
		{
			if(i == 0)
			{
				g_pShuttleChild->UnitStop();
// 2007-05-11 by dgwoo
//				g_pShuttleChild->m_bUnitStop = !g_pShuttleChild->m_bUnitStop;
//				g_pShuttleChild->m_bMouseLock = TRUE;
//				g_pShuttleChild->m_bMouseMoveLock = TRUE;
//				g_pD3dApp->m_bFixUnitDirMode = TRUE;
			}
		}
		break;
	case _Q_AGEAR_FUEL_ALLIN:	// 2005-08-19 by ispark ���ᰡ �Ҹ�Ǿ� ���÷� ����
		{
			g_pShuttleChild->m_bIsCameraPattern = FALSE;
			if(g_pShuttleChild->m_bAttackMode == _SIEGE)			// ������� ������ �Ϲݻ��·� ���� 
			{
				g_pShuttleChild->m_pEngine->ChangeBodyCondition(BODYCON_SIEGE_OFF_MASK);
				g_pShuttleChild->m_bAttackMode = _AIR;
			}
			g_pFieldWinSocket->WriteMessageType(T_FC_CHARACTER_WARP_BY_AGEAR_LANDING_FUEL_ALLIN);
		}
		break;
	case _Q_MISSION_START:
		{
			if(i == 0)
			{
				// 2007-06-12 by bhsohn �̼� �������̽� ������
				//g_pGameMain->m_pMissionInfo->MissionStart((int)m_dwData);
				g_pGameMain->MissionStart((int)m_dwData);
			}
		}
		break;
	case _Q_SKILL_CALLOFHERO:
		{
			// 2013-02-13 by mspark, ä��â�� ���� ���� Ư�� ��Ȳ���� ������� ���� �ذ�
			if(i == 0)
			{
				// 2013-06-20 by bhsohn Ư�� ��Ȳ ä�� ���� ���󰡴� ���� ����
//				if( strlen(g_pGameMain->m_pChat->m_strInputMessage) )
				BOOL bModeChat = FALSE;
				if(1 == strlen(g_pGameMain->m_pChat->m_strInputMessage) 
					&& (g_pGameMain->m_pChat->ChatModeChack(g_pGameMain->m_pChat->m_strInputMessage[0]))) // Ư�� ��� ä��
				{
					bModeChat = TRUE;
				}
				if( strlen(g_pGameMain->m_pChat->m_strInputMessage) > 0 && !bModeChat)
				{
					g_pD3dApp->m_pIMSocket->SendChat(T_IC_CHAT_REGION, g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.CharacterName, g_pGameMain->m_pChat->m_strInputMessage);
					g_pGameMain->m_pChat->m_bChatMode = FALSE;
					g_pD3dApp->m_bChatMode = FALSE;
					g_pD3dApp->CleanText();
					g_pGameMain->m_pChat->InitChatMsgBuff();
					memset(g_pGameMain->m_pChat->m_strInputMessage,0x00,SIZE_MAX_CHAT_MESSAGE);
				}
			}
			// end 2013-02-13 by mspark, ä��â�� ���� ���� Ư�� ��Ȳ���� ������� ���� �ذ�
			// 2008-08-27 by bhsohn �ݿ��� ����� ���� ��� ���� ����
			if(g_pShuttleChild 						
						&& g_pShuttleChild->m_pClientParty->IsFormationFlight())
			{
				if(g_pShuttleChild->m_pClientParty->GetPartyInfo().bPartyType == _PARTYMASTER )
				{
					// ������ ���� ��������
					g_pShuttleChild->m_pClientParty->TempPartyFormation(FLIGHT_FORM_NONE);					
				}
				else
				{
					// ��� ���� ����
					g_pShuttleChild->CheckFormationMoveDelete();
				}
			}
			// end 2008-08-27 by bhsohn �ݿ��� ����� ���� ��� ���� ����


			g_pShuttleChild->m_pSkill->UseSkillConfirm(i);
		}	
		break;
		// 2009-01-12 by bhsohn ģ�� ��� ���ϴ� ���� �޽���â ��� �߰�
	case _Q_FRIEND_LIST_INSERT:
		{
			// 2013-02-13 by mspark, ä��â�� ���� ���� Ư�� ��Ȳ���� ������� ���� �ذ�
			if(i == 0)
			{
				// 2013-06-20 by bhsohn Ư�� ��Ȳ ä�� ���� ���󰡴� ���� ����
//				if( strlen(g_pGameMain->m_pChat->m_strInputMessage) )
				BOOL bModeChat = FALSE;
				if(1 == strlen(g_pGameMain->m_pChat->m_strInputMessage) 
					&& (g_pGameMain->m_pChat->ChatModeChack(g_pGameMain->m_pChat->m_strInputMessage[0]))) // Ư�� ��� ä��
				{
					bModeChat = TRUE;
				}
				if( strlen(g_pGameMain->m_pChat->m_strInputMessage) && !bModeChat)
				{
					g_pD3dApp->m_pIMSocket->SendChat(T_IC_CHAT_REGION, g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.CharacterName, g_pGameMain->m_pChat->m_strInputMessage);
					g_pGameMain->m_pChat->m_bChatMode = FALSE;
					g_pD3dApp->m_bChatMode = FALSE;
					g_pD3dApp->CleanText();
					g_pGameMain->m_pChat->InitChatMsgBuff();
					memset(g_pGameMain->m_pChat->m_strInputMessage,0x00,SIZE_MAX_CHAT_MESSAGE);
				}
			}
			// end 2013-02-13 by mspark, ä��â�� ���� ���� Ư�� ��Ȳ���� ������� ���� �ذ�
			// ģ�� ��� ��û �޾Ҵ�.
			if(i == 0)
			{
				CINFCommunityFriend*  pFriend = g_pGameMain->m_pCommunity->GetFriend();	
				MSG_IC_CHAT_FRIENDLIST_INSERT sMsg;
				strncpy(sMsg.szCharacterName, pFriend->GetRqFriend(), SIZE_MAX_CHARACTER_NAME);
				g_pIMSocket->SendMsg( T_IC_CHAT_FRIENDLIST_INSERT, (char*)&sMsg, sizeof(sMsg) );

				char chBuffBlank[SIZE_MAX_CHARACTER_NAME];
				memset(chBuffBlank, 0x00, SIZE_MAX_CHARACTER_NAME);
				pFriend->SetRqFriend(chBuffBlank);
			}
		}
		break;
		// end 2009-01-12 by bhsohn ģ�� ��� ���ϴ� ���� �޽���â ��� �߰�
	case _Q_FUELALLIN_DEAD_RETURN:
		{
			g_pShuttleChild->m_bIsCameraPattern = FALSE;
			if(g_pShuttleChild->m_bAttackMode == _SIEGE)			// ������� ������ �Ϲݻ��·� ���� 
			{
				g_pShuttleChild->m_pEngine->ChangeBodyCondition(BODYCON_SIEGE_OFF_MASK);
				g_pShuttleChild->m_bAttackMode = _AIR;
//				g_pShuttleChild->m_bPrimaryAttackMode = 0;//(BYTE)fValue;
//				g_pShuttleChild->m_bSecondaryAttackMode = 0;//(BYTE)fValue;
			}
			
			// 2010. 03. 25 by ckPark ����� 5���̻� �߶��ϸ� ��Ȱ�޼��� �߰�
			//if(COMPARE_BODYCON_BIT(g_pShuttleChild->GetCurrentBodyCondition(),BODYCON_DEAD_MASK|BODYCON_EXPLOSION_MASK) )
			if( g_pShuttleChild->m_dwState == _FALLING ||
				COMPARE_BODYCON_BIT(g_pShuttleChild->GetCurrentBodyCondition(), BODYCON_DEAD_MASK|BODYCON_EXPLOSION_MASK) )
			// end 2010. 03. 25 by ckPark ����� 5���̻� �߶��ϸ� ��Ȱ�޼��� �߰�
			{
				MSG_FC_CHARACTER_DEAD_GAMESTART sMsg;
				memset(&sMsg,0x00,sizeof(sMsg));
				char buffer[SIZE_MAX_PACKET];
				int nType = T_FC_CHARACTER_DEAD_GAMESTART;
				sMsg.ClientIndex = g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.ClientIndex;
				sMsg.CharacterUniqueNumber = g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.CharacterUniqueNumber;
				sMsg.bRebirthInCityMap		= TRUE;	// ������ ���ø����� �̵�
				memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
				memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
				g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
			}			
		}
		break;
	case _Q_INFLUENCEMAP_DEAD_RETURN:	// 2006-01-02 by ispark, �ٸ� ���¸ʿ����� �ڱ� ���� ���ø����� �̵�
		{
			g_pShuttleChild->m_bIsCameraPattern = FALSE;
			if(g_pShuttleChild->m_bAttackMode == _SIEGE)			// ������� ������ �Ϲݻ��·� ���� 
			{
				g_pShuttleChild->m_pEngine->ChangeBodyCondition(BODYCON_SIEGE_OFF_MASK);
				g_pShuttleChild->m_bAttackMode = _AIR;
//				g_pShuttleChild->m_bPrimaryAttackMode = 0;//(BYTE)fValue;
//				g_pShuttleChild->m_bSecondaryAttackMode = 0;//(BYTE)fValue;
			}
			
			// 2010. 03. 25 by ckPark ����� 5���̻� �߶��ϸ� ��Ȱ�޼��� �߰�
			//if(COMPARE_BODYCON_BIT(g_pShuttleChild->GetCurrentBodyCondition(),BODYCON_DEAD_MASK|BODYCON_EXPLOSION_MASK) )
			if( g_pShuttleChild->m_dwState == _FALLING ||
				COMPARE_BODYCON_BIT(g_pShuttleChild->GetCurrentBodyCondition(), BODYCON_DEAD_MASK|BODYCON_EXPLOSION_MASK) )
			// end 2010. 03. 25 by ckPark ����� 5���̻� �߶��ϸ� ��Ȱ�޼��� �߰�
			{
				MSG_FC_CHARACTER_DEAD_GAMESTART sMsg;
				memset(&sMsg,0x00,sizeof(sMsg));
				char buffer[SIZE_MAX_PACKET];
				int nType = T_FC_CHARACTER_DEAD_GAMESTART;
				sMsg.ClientIndex = g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.ClientIndex;
				sMsg.CharacterUniqueNumber = g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.CharacterUniqueNumber;
				sMsg.bRebirthInCityMap		= FALSE;
				sMsg.bRebirthInCityMap	= TRUE;
				memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
				memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
				g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
			}			
		}
		break;
	case _Q_EVENT_CALL_WARP_REQUEST:	// 2006-07-24 by ispark, �̺�Ʈ �� ���
		{
			if(i == 0)
			{
				MSG_FC_EVENT_CALL_WARP_EVENT_REQUEST_ACK sMsg;
				memset(&sMsg,0x00,sizeof(sMsg));
				char buffer[SIZE_MAX_PACKET];
				int nType = T_FC_EVENT_CALL_WARP_EVENT_REQUEST_ACK;
				sMsg.dwCallWarpEventID0 = m_dwData;
				memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
				memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
				g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
			}
		}
		break;
	case _Q_BAZAAR_OPEN_SHOP_END:		// 2006-07-30 by ispark, ���� ���� ������ ���� 
		{
			if(i == 0)
			{
				CSkillInfo* pSkillInfo = (CSkillInfo*)m_dwData;
				if(pSkillInfo)
					pSkillInfo->SetbApprovalEnd(TRUE);
				g_pInterface->ReadyCloseBazaarShop();
			}
			else
			{
				// ��ҽ�
				if(g_pInterface->m_pBazaarShop)
					g_pInterface->m_pBazaarShop->SetbBazaarShopEnd(FALSE);
			}
		}
		break;
	case _Q_BAZAAR_INVALID_SHOP_END:
		{
			if(g_pInterface->m_pBazaarShop)
				g_pInterface->m_pBazaarShop->SetbBazaarShopEnd(TRUE);
		}
		break;
	case _Q_BAZAAR_SELL_OK:
		{
			if(i == 0)
			{
				g_pInterface->m_pBazaarShop->Send_SellBuyItem(TRUE);
			}
		}
		break;
	case _Q_BAZAAR_BUY_OK:
		{
			if(i == 0)
			{
				g_pInterface->m_pBazaarShop->Send_SellBuyItem(TRUE);
			}
		}
		break;
	case _Q_USEITEM_KILL_MARK:
		{
			if(i == 0)
			{
				MSG_FC_ITEM_USE_ITEM sMsg;
				memset(&sMsg,0x00,sizeof(sMsg));
				char buffer[SIZE_MAX_PACKET];
				sMsg.ClientIndex = g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.ClientIndex;
				sMsg.ItemUniqueNumber = m_UniqueNumber;
				int nType = T_FC_ITEM_USE_ITEM;
				memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
				memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
				g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
			}
		}
		break;
	case _Q_QUEST_REQUEST_PARTY_WARP:
		{
			if(i == 0)
			{
				INIT_MSG_WITH_BUFFER(MSG_FC_QUEST_REQUEST_PARTY_WARP_ACK, T_FC_QUEST_REQUEST_PARTY_WARP_ACK, pRequestPartyWarpAck, Sendbuf);
				pRequestPartyWarpAck->callerCharacterUID = m_UniqueNumber;
				pRequestPartyWarpAck->warpMapChannIndex.MapIndex = m_dwData;
				pRequestPartyWarpAck->warpMapChannIndex.ChannelIndex = m_nAllNumber;
				g_pD3dApp->m_pFieldWinSocket->Write(Sendbuf, MSG_SIZE(MSG_FC_QUEST_REQUEST_PARTY_WARP_ACK));
				// 2008-06-17 by bhsohn ��� ���� ó��
				// �̼� ����̽� ������ ���� ��������
				if(g_pShuttleChild->m_pClientParty 
					&& g_pShuttleChild->m_pClientParty->GetPartyInfo().bPartyType == _PARTYMASTER 
					&& g_pShuttleChild->m_pClientParty->IsFormationFlight())
				{
					g_pShuttleChild->m_pClientParty->TempPartyFormation(FLIGHT_FORM_NONE);
				}
				// end 2008-06-17 by bhsohn ��� ���� ó��
			}
		}
		break;

	case _Q_UPDATE_SUBLEADER_1:
		{// 2007-02-15 by dgwoo �������� ���� â.
			if(i == 0)
			{
				INIT_MSG_WITH_BUFFER(MSG_FC_CHARACTER_UPDATE_SUBLEADER,T_FC_CHARACTER_UPDATE_SUBLEADER,pRequestSubLeader,Sendbuf);
				pRequestSubLeader->InflType					= g_pShuttleChild->m_myShuttleInfo.InfluenceType;
				pRequestSubLeader->SubLeaderRank			= 1;
				strcpy(pRequestSubLeader->CharacterName,m_strInputMessage);
				g_pD3dApp->m_pFieldWinSocket->Write(Sendbuf,  MSG_SIZE(MSG_FC_CHARACTER_UPDATE_SUBLEADER));
			}
			else
			{
				//g_pD3dApp->m_pChat->CreateChatChild(STRCMD_CS_COMMAND_SUBLEADER_RESULT_ERROR, COLOR_ERROR);
			}
		}
		break;
	case _Q_UPDATE_SUBLEADER_2:
		{// 2007-02-15 by dgwoo �������� ���� â.
			if(i == 0)
			{
				INIT_MSG_WITH_BUFFER(MSG_FC_CHARACTER_UPDATE_SUBLEADER,T_FC_CHARACTER_UPDATE_SUBLEADER,pRequestSubLeader,Sendbuf);
				pRequestSubLeader->InflType = g_pShuttleChild->m_myShuttleInfo.InfluenceType;
				pRequestSubLeader->SubLeaderRank			= 2;
				strcpy(pRequestSubLeader->CharacterName,m_strInputMessage);
				g_pD3dApp->m_pFieldWinSocket->Write(Sendbuf,  MSG_SIZE(MSG_FC_CHARACTER_UPDATE_SUBLEADER));
			}
			else
			{
				//g_pD3dApp->m_pChat->CreateChatChild(STRCMD_CS_COMMAND_SUBLEADER_RESULT_ERROR, COLOR_ERROR);
			}
		}
		break;
	case _Q_ARENA_PASSWORD:
		{
			if(i == 0)
			{
				CINFCityArena* pCityArena = NULL;
				CMapCityShopIterator it = g_pInterface->m_pCityBase->m_mapCityShop.find(BUILDINGKIND_ARENA);
				if(it != g_pInterface->m_pCityBase->m_mapCityShop.end())
				{
					pCityArena = ((CINFCityArena*)it->second);		
				}
				// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
//				INIT_MSG_WITH_BUFFER(MSG_FC_ARENA_ENTER_TEAM,T_FC_ARENA_ENTER_TEAM,pRequest,Sendbuf);
//				if(NULL == pCityArena)
//					break;
//				SARENA_TEAM_INFO* tempTeamInfo = pCityArena->GetSelectListTeam();
//				pRequest->ArenaMode = tempTeamInfo->ArenaMode;
//				pRequest->ClientIndex = g_pShuttleChild->m_myShuttleInfo.ClientIndex;
//				pRequest->TeamNum = tempTeamInfo->TeamNum;
				m_strInputMessage[strlen(m_strInputMessage)-1] = NULL;// '_'���� ����
//				strcpy(pRequest->TeamPW,m_strInputMessage);
//				g_pD3dApp->m_pFieldWinSocket->Write(Sendbuf,  MSG_SIZE(MSG_FC_ARENA_ENTER_TEAM));
				if(NULL == pCityArena)
					break;
				pCityArena->SendArenaEnterRoom(m_strInputMessage);
				
				// end 2007-11-22 by bhsohn �Ʒ��� ���ռ���
			}
			else
			{
				
			}
		}
		break;
	case _Q_ARENA_WARP:
		{
			if(i == 0)
			{// �Ʒ��� ������ �̵�.
				// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
				//g_pFieldWinSocket->SendMsg(T_FC_ARENA_ENTER_ROOM_WARP,NULL,NULL);
				g_pInterface->m_pCityBase->CloseCurrentEnterBuilding();// ��� ������ �ݴ´�.
				g_pD3dApp->SendAreneEnterRoomWarp();				
			}
			else
			{// ���.
				// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
//				MSG_FC_ARENA_REAVE_TEAM sMsg;
//				sMsg.ArenaMode = g_pInterface->m_pGameArena->m_nArenaMode;
//				sMsg.ClientIndex = g_pShuttleChild->m_myShuttleInfo.ClientIndex;
//				sMsg.TeamNum = g_pInterface->m_pGameArena->GetTeamNum();
//				g_pFieldWinSocket->SendMsg(T_FC_ARENA_REAVE_TEAM,(char*)&sMsg,sizeof(sMsg));
				if(FALSE == g_pD3dApp->IsGmModeConnect())
				{
					// �Ϲ������� ��Ż���û 
					g_pInterface->m_pGameArena->SendArenaLeaveTeam(g_pInterface->m_pGameArena->m_nArenaMode);
				}
			}
		}
		break;
	case _Q_TUTORIAL_START:
		{
			g_pInterface->m_pCityBase->CloseCurrentEnterBuilding();
			((CINFWindow*)m_pParent)->DeleteMsgBox(_Q_TUTORIAL_START);
			if(i == 0)
			{// ���� 
				g_pFieldWinSocket->SendMsg(T_FC_TUTORIAL_WARP,NULL,0);
				
			}
			else
			{//���.
			}

		}
		break;
	case _Q_ARENA_RESTART:
		{
			MSG_FC_CHARACTER_DEAD_GAMESTART sMsg;
			memset(&sMsg,0x00,sizeof(sMsg));
			char buffer[SIZE_MAX_PACKET];
			int nType = T_FC_CHARACTER_DEAD_GAMESTART;
			sMsg.ClientIndex = g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.ClientIndex;
			sMsg.CharacterUniqueNumber = g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.CharacterUniqueNumber;
			sMsg.bRebirthInCityMap		= FALSE;
			memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
			memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
			g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));			
		}
		break;
		// 2007-09-27 by bhsohn 2�� �н����� �߰� ��ȹ��
	case _Q_SECOND_PASS_CANCEL_MSG:
		{
			if(i == 0)
			{
				g_pGameMain->ShowSecondPassword();				
			}
		}
		break;
		// end 2007-09-27 by bhsohn 2�� �н����� �߰� ��ȹ��
	case _Q_POLL_CANDIDATE_VOTE:
		{
			if(i == 0)
			{
				CINFCityLeader* pCityLeader = NULL;
				CMapCityShopIterator it = g_pInterface->m_pCityBase->m_mapCityShop.find(BUILDINGKIND_CITYLEADER_LEADER);
				if(it != g_pInterface->m_pCityBase->m_mapCityShop.end())
				{
					pCityLeader = ((CINFCityLeader*)it->second);		
				}
				MSG_FC_CITY_POLL_VOTE sMsg;
				sMsg.LeaderCandidateNum		= pCityLeader->GetCandidateNum();
				sMsg.CharacterUID			= pCityLeader->GetCandidateInfo()->CharacterUID;
				sMsg.VoteCharacterUID		= g_pShuttleChild->GetMyShuttleInfo().CharacterUniqueNumber;
				g_pFieldWinSocket->SendMsg(T_FC_CITY_POLL_VOTE,(char*)&sMsg,sizeof(sMsg));

			}
		}
		break;
	case _Q_POLL_CANDIDATE_DELETE:
		{
			if(i == 0)
			{
				MSG_FC_CITY_POLL_DELETE_LEADER_CANDIDATE sMsg;
				sMsg.CharacterUID = g_pShuttleChild->GetMyShuttleInfo().CharacterUniqueNumber;
				g_pFieldWinSocket->SendMsg(T_FC_CITY_POLL_DELETE_LEADER_CANDIDATE,(char*)&sMsg,sizeof(sMsg));
			}

		}
		break;
	case _Q_GIFT_CHARACTER_TEXT:
		{
			if(i == 0)
			{
				m_strInputMessage[strlen(m_strInputMessage)-1] = '\0';// '_'���� ����
				//g_pGameMain->m_pCommunity->GetFriend()->AddFriendList(m_strInputMessage);
				// 2006-05-22 by ispark, strcmp -> stricmp
				if(strlen(m_strInputMessage) == 0)
				{
				
				}				
				else
				{
					g_pD3dApp->m_bRequestEnable = FALSE;
					MSG_FC_SHOP_CHECK_GIVE_TARGET sMsg;
					sMsg.GiveItemNum = m_UniqueNumber;
					strncpy(sMsg.GiveTargetCharName, m_strInputMessage, SIZE_MAX_CHARACTER_NAME);
					g_pFieldWinSocket->SendMsg( T_FC_SHOP_CHECK_GIVE_TARGET, (char*)&sMsg, sizeof(sMsg) );

					// 2009. 08. 21 by ckPark ĳ�������� �����ϱ⿡ ������ üũ
					g_pGameMain->SetCashGiftSendCharacterName( m_strInputMessage );
					// end 2009. 08. 21 by ckPark ĳ�������� �����ϱ⿡ ������ üũ
				}
				// 2009-03-02 by bhsohn ĳ���� ���� ����
				// 2008-12-09 by dgwoo ���� �޽���â�� ��������쿣 ��ũ�� �� �ٸ� ��Ʈ���� �ȵǵ��� ����.
				//g_pGameMain->m_bBuyMessage		= FALSE;
			}
			// 2009-03-02 by bhsohn ĳ���� ���� ����
			g_pGameMain->m_bBuyMessage		= FALSE;
			// end 2009-03-02 by bhsohn ĳ���� ���� ����
		}
		break;
	case _Q_GIFT_ITEM:
		{
			if(i == 0)
			{
				g_pGameMain->m_bSendCashItemBuy = TRUE;
			}
			// 2008-08-13 by dgwoo ���� �޽���â�� ��������쿣 ��ũ�� �� �ٸ� ��Ʈ���� �ȵǵ��� ����.
			g_pGameMain->m_bBuyMessage		= FALSE;
		}
		break;
	case _Q_GIFT_ITEM_RING_IN:
		{// 2007-11-28 by dgwoo �������� Ŭ��
			if(i == 0)
			{
				MSG_FC_EVENT_NOTIFY_MSG_DELETE sMsg;
				sMsg.NotifyMsgUID = m_UniqueNumber;
				g_pFieldWinSocket->SendMsg(T_FC_EVENT_NOTIFY_MSG_DELETE,(char*)&sMsg,sizeof(sMsg));
				g_pGameMain->m_pUnitInfoBar->DeleteGiftMsg();
			}
		}
		break;
	case _Q_COUPON:
		{
		}
		break;
		// 2008-04-04 by bhsohn Ep3 Ŀ�´�Ƽ â		
	case _Q_GUILD_GIVE_SUBLEADER:	// "\\y%s\\y���� �ο��������� �Ӹ��Ͻðڽ��ϱ�?"
		{
			if(i == 0)
			{
				UINT dwTmp = (UINT)m_dwData;
			}
		}
		break;	
	case _Q_GUILD_FALL_SUBLEADER:	// "�ο����� ������ �������� ����νðڽ��ϱ�?"
		{
			
		}
		break;
	case _Q_GUILD_CHARGE_LEADER:	// "\\y%s\\y�Կ��� �������� �����Ͻðڽ��ϱ�?"
		{
			if(i == 0)
			{
				UINT dwTmp = (UINT)m_dwData;
				
				MSG_IC_GUILD_NEW_COMMANDER sMsg;
				memset(&sMsg, 0x00, sizeof(MSG_IC_GUILD_NEW_COMMANDER));
				sMsg.NewCommanderUID = (UINT)m_dwData;
				g_pIMSocket->SendMsg( T_IC_GUILD_NEW_COMMANDER, (char*)&sMsg, sizeof(sMsg));
			}
		}
		break;	
	case _Q_GUILD_REQUEST:			// "\\y%s\\y���ܿ� ���� ��û �Ͻðڽ��ϱ�?"
		{
			if(i == 0)
			{
				CINFCommunityGuildIntroMe* pIntro = g_pGameMain->m_pCommunity->GetGuildIntroMe();
				pIntro->RqGuildIntroMe();				
			}
		}
		break;
	case _Q_GUILD_REQUEST_CANCEL:	// "\\y%s\\y���ܿ� ���� ��û�� ����Ͻðڽ��ϱ�?"
		{
			if(i == 0)
			{				
				g_pGameMain->m_pCommunity->RqCancelMyGuildIntro();				
			}
		}
		break;
	case _Q_PARTY_JOIN_PASSWORD:	// ��й�ȣ�� �Է��Ͻʽÿ�.
		{
			if(i == 0)
			{
				m_strInputMessage[strlen(m_strInputMessage)-1] = NULL;// '_'���� ����
				g_pGameMain->m_pCommunity->GetParty()->RqClickJoinBtn(m_strInputMessage);	// ���ο�û
			}
		}
		break;
		// end 2008-04-04 by bhsohn Ep3 Ŀ�´�Ƽ â
	case _Q_CHATROOM_PASSWORD:
		{
			if(i == 0)
			{
				MSG_IC_CHATROOM_JOIN sMsg;
				sMsg.ChatRoomNum = m_dwData;
				sMsg.ChatRoomLock = TRUE;
				m_strInputMessage[strlen(m_strInputMessage)-1] = NULL;
				strncpy(sMsg.ChatRoomPW,m_strInputMessage,SIZE_MAX_TEAM_PW);
				g_pIMSocket->SendMsg(T_IC_CHATROOM_JOIN, (char*)&sMsg, sizeof(sMsg));

			}
		}
		break;
	// 2008-09-17 by dgwoo ��� �������� ��ư ��ȹ�� 
	case _Q_GUILD_BATTLE:
		{
			if(i == 0)
			{
				m_strInputMessage[strlen(m_strInputMessage)-1] = NULL;// '_'���� ����]
				char name[SIZE_MAX_CHARACTER_NAME];
				memset(name,0x00,SIZE_MAX_CHARACTER_NAME);	
				memcpy(name,m_strInputMessage,strlen(m_strInputMessage));

				// 2008-02-27 by bhsohn ���� �Ʒ��� ����
				if(g_pD3dApp->GetArenaState() == ARENA_STATE_ARENA_GAMING )
				{
					// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

// 					//"�Ʒ��������� �̿��� �� �����ϴ�."
// 					g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."
					if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_ARENA )
						g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."
					else if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_INFINITY )
						g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_091103_0322,COLOR_ERROR);//"\y���Ǵ�Ƽ �ʵ忡���� ��� �� �� �����ϴ�\y"

					// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
					
					break;
				}
				// end 2008-02-27 by bhsohn ���� �Ʒ��� ����
				// 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��
				if(!g_pD3dApp->IsOptionEtc(OPTION_RADIO_GUILD_WAR))
				{
					g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080922_0100,COLOR_ERROR,CHAT_TAB_SYSTEM);
					break;
				}
				// end 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��

				MSG_IC_GUILD_GET_GUILD_INFO_OK * pGuild = g_pGameMain->m_pCommunity->GetGuild()->GetGuildInfo();
				if( g_pShuttleChild->m_myShuttleInfo.GuildUniqueNumber != 0 && pGuild)
				{
					if(pGuild->GuildCommanderUniqueNumber == g_pShuttleChild->m_myShuttleInfo.CharacterUniqueNumber )
					{
 						//memcpy(name,m_strInputMessage+n+1,strlen(m_strInputMessage));
						// 2008-07-14 by bhsohn EP3 ���� ó��										
						if( g_pGameMain->IsRejectUser(name))
						{
							g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080714_0207,COLOR_ERROR);//"\\y�ź� ��Ͽ� ��ϵ� ����Դϴ�."
						}
						// end 2008-07-14 by bhsohn EP3 ���� ó��									

						//if( strlen(name) > 0 )
						if( strlen(name) > 0 && !g_pGameMain->IsRejectUser(name))
						{
							MSG_FC_REQUEST_REQUEST sMsg;
							memset( &sMsg, 0x00, sizeof(sMsg) );
							sMsg.RequestType = REQUEST_TYPE_GUILD_WAR;
							strcpy(sMsg.TargetCharacterName, name );
							g_pFieldWinSocket->SendMsg( T_FC_REQUEST_REQUEST, (char*)&sMsg, sizeof(sMsg) );
						}
					}
					else
					{
						g_pD3dApp->m_pChat->CreateChatChild( STRMSG_C_GUILD_0034, COLOR_CHAT_GUILD);//"�������� �����常 ��û�� �� �ֽ��ϴ�."
					}
				}
				
			}
		}
		break;
	case _Q_PARTY_BATTLE:
		{
			if(i == 0)
			{
				m_strInputMessage[strlen(m_strInputMessage)-1] = NULL;// '_'���� ����]
				char name[SIZE_MAX_CHARACTER_NAME];
				memset(name,0x00,SIZE_MAX_CHARACTER_NAME);									// ������� ��û
 				memcpy(name,m_strInputMessage,strlen(m_strInputMessage));
				CEnemyData * pPK = NULL;
				CMapEnemyIterator itEnemy = g_pD3dApp->m_pScene->m_mapEnemyList.begin();
				while(itEnemy != g_pD3dApp->m_pScene->m_mapEnemyList.end())
				{
					if( !stricmp(itEnemy->second->m_infoCharacter.CharacterInfo.CharacterName, name))// &&
						//itEnemy->second == g_pD3dApp->m_pShuttleChild->m_pTarget)
					{
						pPK = itEnemy->second;
					}
					itEnemy++;
				}
				// 2008-02-27 by bhsohn ���� �Ʒ��� ����
				if(g_pD3dApp->GetArenaState() == ARENA_STATE_ARENA_GAMING )
				{
					// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

// 					//"�Ʒ��������� �̿��� �� �����ϴ�."
// 					g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."
					if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_ARENA )
						g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."
					else if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_INFINITY )
						g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_091103_0322,COLOR_ERROR);//"\y���Ǵ�Ƽ �ʵ忡���� ��� �� �� �����ϴ�\y"

					// end  2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

					break;
				}

				// 2008-07-14 by bhsohn EP3 ���� ó��
				if(pPK && g_pGameMain->IsRejectUser(pPK->m_infoCharacter.CharacterInfo.CharacterName))
				{
					g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080714_0207,COLOR_ERROR);//"\\y�ź� ��Ͽ� ��ϵ� ����Դϴ�."
					break;										
				}
				// end 2008-07-14 by bhsohn EP3 ���� ó��

				// 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��
				if(!g_pD3dApp->IsOptionEtc(OPTION_RADIO_FORMATIONWAR))
				{
					g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080922_0101,COLOR_ERROR,CHAT_TAB_SYSTEM);
					break;
				}
				// end 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��

				if(pPK)
				{
					MSG_FC_REQUEST_REQUEST sMsg;
					memset(&sMsg,0x00,sizeof(sMsg));
					char buffer[SIZE_MAX_PACKET];
					int nType = T_FC_REQUEST_REQUEST;
					sMsg.TargetClientIndex = pPK->m_infoCharacter.CharacterInfo.ClientIndex;
					sMsg.RequestType = REQUEST_TYPE_PARTY_BATTLE;
					memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
					memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
					g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
					

					// ����� ��û�� ����� �޴� ��� �Ұ� ����
					g_pGameMain->m_pCommunity->GetParty()->SetEnablePartyMenu(FALSE);
				}
			}

		}
		break;
	// 2008-09-17 by dgwoo ��� �������� ��ư ��ȹ�� 
		// 2008-11-13 by bhsohn ���̽�ƽ �۾�
	case _Q_JOYSTICK_SETUP:				// ��� ���� ����(���� �̸� �Է�) ���� �������� ����
		{
			if( i == 0 )
			{
				m_strInputMessage[strlen(m_strInputMessage)-1] = NULL;// '_'���� ����
				if(g_pGameMain)
				{
					g_pGameMain->SaveAsJoysticSetupInfo(m_strInputMessage);
				}

			}
		}
		break;
		// end 2008-11-13 by bhsohn ���̽�ƽ �۾�
// 2008-12-09 by dgwoo �̼Ǹ�����.
	case _Q_MISSION_MASTER_CANCEL:
		{
			if(i == 0)
			{
				g_pGameMain->m_pCommunity->SetMissionMasterOption(FALSE);
			}
		}
		break;
	case _Q_MISSION_MASTER_HELPER:
		{
			if(i == 0)
			{
				if(g_pShuttleChild->m_pClientParty->IsParty())
				{
					g_pShuttleChild->m_pClientParty->ISendPartyLeave();
					// 2008-12-16 by dgwoo ��Ƽ Leave�޽����� ������ T_FC_QUEST_MISSIONMASTER_HELP_INVITE
					// ó���� �ϱ� ���� �ڵ�.
					CINFCommuPartyCre*	pPartyCre = g_pGameMain->m_pCommunity->GetPartyCreate();
					if(NULL != pPartyCre)
					{
						pPartyCre->SetMissionMaster(TRUE);
						pPartyCre->SetMissionMasterUID(m_UniqueNumber);
					}
					
				
				}
				// 2010. 02. 03 by jskim ��Ƽ �߿� �̼Ǹ����� ���� ��û ���� �� ��Ƽ�� Ż��Ǵ� �簡�� �ȵǴ� ���� ����
				//else
				//{
					MSG_FC_QUEST_MISSIONMASTER_HELP_INVITE sMsg;
					sMsg.CharacterUID = m_UniqueNumber;
					g_pFieldWinSocket->SendMsg(T_FC_QUEST_MISSIONMASTER_HELP_INVITE,(char*)&sMsg,sizeof(sMsg));
				//}
				//end 2010. 02. 03 by jskim ��Ƽ �߿� �̼Ǹ����� ���� ��û ���� �� ��Ƽ�� Ż��Ǵ� �簡�� �ȵǴ� ���� ����
				
			}
			else
			{
				MSG_FC_QUEST_MISSIONMASTER_HELP_REJECT sMsg;
				sMsg.CharacterUID = m_UniqueNumber;
				g_pFieldWinSocket->SendMsg(T_FC_QUEST_MISSIONMASTER_HELP_REJECT,(char*)&sMsg,sizeof(sMsg));
			}
		}
		break;		
// end 2008-12-09 by dgwoo �̼Ǹ�����.


	// 2009. 01. 12 by ckPark ���� ���� �ý���
	case _Q_WAR_DECLARE_GIVE_UP:
		{
			// �������� �����
			if(i == 0)
			{
				MSG_FC_INFO_DECLARATION_MSWAR_SET sMsg;
				
				sMsg.GiveUp			= TRUE;
				sMsg.MSWarStep		= g_pGameMain->GetINFMotherShipManager()->GetWarDeclareWindow()->GetMSWarStep();
				// ��¥�� �������
				memset(&sMsg.MSWarStartTime, 0, sizeof(ATUM_DATE_TIME));

				g_pD3dApp->EnterLock(FALSE);
				
				g_pFieldWinSocket->SendMsg(T_FC_INFO_DECLARATION_MSWAR_SET, (char*)&sMsg, sizeof(sMsg));
			}
		}
		break;

	case _Q_WAR_DECLARE:
		{
			// ���������
			if(i == 0)
			{
				// ���� ����
				MSG_FC_INFO_DECLARATION_MSWAR_SET sMsg;

				sMsg.GiveUp			= (!g_pGameMain->GetINFMotherShipManager()->GetWarDeclareWindow()->GetWarDeclareDateView().Year) ? TRUE : FALSE;
				sMsg.MSWarStep		= g_pGameMain->GetINFMotherShipManager()->GetWarDeclareWindow()->GetMSWarStep();
				sMsg.MSWarStartTime	= g_pGameMain->GetINFMotherShipManager()->GetWarDeclareWindow()->GetWarDeclareDateView();
				
				g_pD3dApp->EnterLock(FALSE);
				
				g_pFieldWinSocket->SendMsg(T_FC_INFO_DECLARATION_MSWAR_SET, (char*)&sMsg, sizeof(sMsg));
			}
		}
		break;
	// end 2009. 01. 12 by ckPark ���� ���� �ý���
		// 2009-02-13 by bhsohn ���� ��ŷ �ý���
	case _Q_CREATE_NICKNAME_OKCANCEL:
		{
			if(0 == i)
			{
				char chMsgBuff[256];
				ZERO_MEMORY(chMsgBuff);
				wsprintf(chMsgBuff, STRMSG_C_090224_0202);	//"[%s]���ܸ����� ������ ����ðڽ��ϱ�?"
				((CINFWindow*)m_pParent)->AddMsgBox(chMsgBuff, _Q_CREATE_NICKNAME);
			}
		}
		break;
	case _Q_CREATE_NICKNAME:
		{
			if (0 == i)
			{
				m_strInputMessage[strlen(m_strInputMessage)-1] = NULL;// '_'���� ����			
						

				CWorldRankManager*	pWorldRankManager = g_pD3dApp->GetWorldRankManager();
				if(strlen(m_strInputMessage) > 10)
				{
					g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_090224_0204, COLOR_ERROR);// "\\y�г����� ������ ���� ���� 10�ڷ� ���ѵ˴ϴ�."
				}
				else if(pWorldRankManager->IsValidNickName(m_strInputMessage))
				{
					UID32_t	myCharacterUniqueNumber = g_pShuttleChild->GetMyShuttleInfo().CharacterUniqueNumber;
					pWorldRankManager->RqCreateMyNickName(m_strInputMessage, myCharacterUniqueNumber);
				}
				else
				{
					g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_090224_0203, COLOR_ERROR);// "\\y�г����� ������ ���� �������θ� ���� �� �ֽ��ϴ�."
				}
			}
		}
		break;
		// end 2009-02-13 by bhsohn ���� ��ŷ �ý���
		// 2009-04-08 by bhsohn ���� ���ý�, ����ũ �� ��æƮ �� ������ �ǸŽ� ��� �޽��� ��� ��ȹ ����(K0000174)
	case _Q_MULTI_SEL_WARNING:	// "%s �������� \\y����ũ\\y �������Դϴ�. ������ ���� �Ͻðڽ��ϱ�?"
		{
			if(i == 0)
			{
				g_pD3dApp->AddMultiSelWarningMsg(m_UniqueNumber);				
			}
		}
		break;	
		// end 2009-04-08 by bhsohn ���� ���ý�, ����ũ �� ��æƮ �� ������ �ǸŽ� ��� �޽��� ��� ��ȹ ����(K0000174)

	// 2009. 10. 08 by ckPark �ʵ� â�� ������ �ߺ� �Ұ� ó��
	case _Q_ALREADY_HAVE_ITEM:
		{
			if( i == 0 )
			{
			}
		}
		break;
	// end 2009. 10. 08 by ckPark �ʵ� â�� ������ �ߺ� �Ұ� ó��

	// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
	case _Q_INFINITY_GIVE_UP:
		{
			if( i == 0 )
			{
				g_pD3dApp->m_pInterface->m_pInfinity->SetInfinityEnd();

				g_pFieldWinSocket->SendMsg( T_FC_INFINITY_LEAVE, 0, 0 );
			}
		}
		break;

	case _Q_REVIVE_WAIT_5SECOND:
		{
			if( i == 1 )
			{
				::PostMessage( g_pD3dApp->GetHwnd(), WM_ADDMSGBOX, _Q_ARENA_RESTART, reinterpret_cast<long>(STRMSG_C_070507_0100) );
			}
		}
		break;

	case _Q_BUY_INFINITYSHOP_ITEM:
		{
			if( i == 0 )
			{
				CMapCityShopList::iterator it = g_pInterface->m_pCityBase->m_mapCityShop.find( BUILDINGKIND_INFINITY_SHOP );
				if( it != g_pInterface->m_pCityBase->m_mapCityShop.end() )
				{
					MSG_FC_SHOP_INFINITY_BUY_ITEM msg;
					msg.InfinityShopUID	= ((CINFCityInfinityShop*)(it->second))->GetBuyInfo().ItemUID;
					// 2010. 03. 08 by ckPark ���Ǵ�Ƽ ���Ի��� �ּ� ���Ű��� 1�� ����
					//msg.Amount			= ((CINFCityInfinityShop*)(it->second))->GetBuyInfo().ItemCount;
					msg.Amount			= max( ((CINFCityInfinityShop*)(it->second))->GetBuyInfo().ItemCount, 1 );
					// end 2010. 03. 08 by ckPark ���Ǵ�Ƽ ���Ի��� �ּ� ���Ű��� 1�� ����

					g_pFieldWinSocket->SendMsg( T_FC_SHOP_INFINITY_BUY_ITEM, (char*)(&msg), sizeof(MSG_FC_SHOP_INFINITY_BUY_ITEM) );
				}
			}
		}
		break;

	case _Q_INFINITY_RETURN_TO_CITY:
		{
			if( i == 0 )
			{
				g_pD3dApp->m_pInterface->m_pInfinity->SetInfinityEnd();

				g_pFieldWinSocket->SendMsg( T_FC_INFINITY_FIN_OK, 0, 0 );
			}
		}
		break;

	case _Q_RETURN_TO_PROGRESS_INFINITY:
		{
			if( i == 0 )
				g_pD3dApp->OnClickInfinityField();
			else
				g_pD3dApp->m_bInfinityRestart	= FALSE;
		}
		break;
	// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
	// 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
	case _Q_PARTNER_NEW_NAME_CHANGE:
		{
			// 2010-06-15 by shcho&hslee ��ý��� - �� �̸� ���� ���� ����.
			if ( i == 0 )
			{
				CWorldRankManager*	pWorldRankManager = g_pD3dApp->GetWorldRankManager();

				m_strInputMessage[strlen(m_strInputMessage)-1] = NULL;

				if ( strlen ( m_strInputMessage ) > SIZE_MAX_PET_NAME/2 )
				{	// Size Check.

				}
// 				else if ( pWorldRankManager && !pWorldRankManager->IsValidNickName(m_strInputMessage) )
// 				{	// ��ȿ�� ���� üũ.
// 					//2011-10-06 by jhahn ��Ʈ�� ������ �ý���
// 					g_pGameMain->m_pInfWindow->AddMsgBox( STRMSG_C_100608_0409, _Q_PARTNER_NAME_OKCANCLE, 0,0,0,0,m_strInputMessage );//"��Ʈ�� �̸��� �����Ͻðڽ��ϱ�?			
//                  //end 2011-10-06 by jhahn ��Ʈ�� ������ �ý���
// 				}
// 				else
// 				{
// 					g_pGameMain->m_pInfWindow->AddMsgBox( STRMSG_C_100608_0409, _Q_PARTNER_NAME_OKCANCLE );//"��Ʈ�� �̸��� �����Ͻðڽ��ϱ�?
// 				}
				// 2012-10-31 by msaprk, ��Ʈ�� �̸� ���� ����
				else
				{
					g_pGameMain->m_pInfWindow->AddMsgBox( STRMSG_C_100608_0409, _Q_PARTNER_NAME_OKCANCLE, 0,0,0,0,m_strInputMessage );//"��Ʈ�� �̸��� �����Ͻðڽ��ϱ�?
				}
			}
			
		}
		break;
//2011-10-06 by jhahn ��Ʈ�� ������ �ý���		
	case _Q_SETTING_SOCKET_OKCANCLE:
		{
			switch ( i )
			{
			case 0 :
				{
					CItemInfo* pAllItem = g_pStoreData->FindItemInInventoryByWindowPos( POS_PET ); 				
					tPET_CURRENTINFO * tempCurrentInfo = g_pShuttleChild->GetPetManager()->GetPtr_PetCurrentData( pAllItem->UniqueNumber );
				
					if (g_pShuttleChild->GetPetManager()->GetSocketNum() <= tempCurrentInfo->PetEnableSocketCount-1)
 					{
 						MSG_FC_ITEM_PET_SET_SOCKET msg;					
 						msg.ItemUniqueNumber = pAllItem->UniqueNumber;
 						msg.SocketIndex = g_pShuttleChild->GetPetManager()->GetSocketNum();		
 						msg.PetSocketItemUID = g_pShuttleChild->GetPetManager()->GetSocketUidNumber();
 						g_pFieldWinSocket->SendMsg( T_FC_ITEM_PET_SET_SOCKET, (char*)(&msg), sizeof(MSG_FC_ITEM_PET_SET_SOCKET) );	

						g_pShuttleChild->GetPetManager()->SetrenderOnOff(TRUE);
					}					
 				}
				break;
			default :
				{
					g_pShuttleChild->GetPetManager()->SetrenderOnOff(FALSE);
				}
				
				break;
			}
		}
		break;
//end 2011-10-06 by jhahn ��Ʈ�� ������ �ý���	

	case _Q_PARTNER_NAME_OKCANCLE:
		{
			switch ( i )
			{
//2011-10-06 by jhahn ��Ʈ�� ������ �ý���
				case 0 :
					{
						MSG_FC_ITEM_PET_SET_NAME msg;					
						CItemInfo* pAllItem = g_pStoreData->FindItemInInventoryByWindowPos( POS_PET );		
						strncpy(msg.PetName,m_strInputMessage,40);
						msg.ItemUniqueNumber = pAllItem->UniqueNumber;										
						g_pFieldWinSocket->SendMsg( T_FC_ITEM_PET_SET_NAME, (char*)(&msg), sizeof(MSG_FC_ITEM_PET_SET_NAME) );							
					}
					break;				  
//end 2011-10-06 by jhahn ��Ʈ�� ������ �ý���
				default :
					break;
			}
		}
		break;
	// 2010. 06. 18 by jskim ��æƮ ��� �޽��� �߰�
	case _Q_ENCHANT_PREVENTION:
		{
			CINFCityLab * pCityLab = (CINFCityLab*)g_pD3dApp->m_pInterface->m_pCityBase->FindBuildingShop(BUILDINGKIND_LABORATORY);
 			pCityLab->m_bIsEnchantCheck = TRUE;	
		}
		break;
	//end 2010. 06. 18 by jskim ��æƮ ��� �޽��� �߰�
	// 2010-08-31 by shcho&&jskim, ���� �ý��� ����
	case _Q_DIS_BOOM:
		{
			CINFDissolution * pCityDis = (CINFDissolution*)g_pD3dApp->m_pInterface->m_pCityBase->FindBuildingShop(BUILDINGKIND_DISSOLUTION);
			pCityDis->ResetInfo();
		}
		break;
	// end 2010-08-31 by shcho&&jskim, ���� �ý��� ����
	// 2012-08-13 by mspark, �κ��丮 �ڵ� ���� Ȯ��â �߰� �۾�
	case _Q_INVEN_ITEM_SORT:
		{
			if( i == 0 )
			{
				g_pStoreData->ResortingItemInInventorySort();

				// 2013-07-24 by bhsohn �ŷ����ϋ� ������ ���� ��ɽ� ���� ����
// 				g_pGameMain->m_pInven->ShowInven(NULL, NULL, TRUE);
// 				g_pGameMain->LeftWindowShow(TRUE, 1);
				if(g_pGameMain && g_pGameMain->m_pTrade && g_pGameMain->m_pTrade->m_bTrading)
				{
					g_pGameMain->m_pInven->SetAllIconInfo();					
				}
				else
				{
					g_pGameMain->m_pInven->ShowInven(NULL, NULL, TRUE);
					g_pGameMain->LeftWindowShow(TRUE, 1);
				}				
				// END 2013-07-24 by bhsohn �ŷ����ϋ� ������ ���� ��ɽ� ���� ����
			}			
		}
		break;
	// end 2012-08-13 by mspark, �κ��丮 �ڵ� ���� Ȯ��â �߰� �۾�
// 2012-10-30 by mspark, ���� ���� ��� �޽��� �߰�
#ifdef C_WARNING_APPEARANCE_CHANGE
	case _Q_APPEARANCE_CHANGE_PREVENTION:
		{
			CINFCityLab * pCityLab = (CINFCityLab*)g_pD3dApp->m_pInterface->m_pCityBase->FindBuildingShop(BUILDINGKIND_FACTORY);
			pCityLab->m_bIsAppearanceChangeCheck = TRUE;	
		}
		break;		
#endif
// end 2012-10-30 by mspark, ���� ���� ��� �޽��� �߰�

// 2013-04-23 by ssjung �߿� ������ ������ 2�� ���(����) �˾�â ���� - // _Q_INCHANT_ITEM_DELETE	
		case _Q_INCHANT_ITEM_DELETE:
		{
			char buf[256] = {0,};
			if(i == 0)
			{
				wsprintf(buf, STRMSG_C_130423_0005, m_strInputMessage);//"������ %s ��(��)  �����ðڽ��ϱ�?"
				m_isWillbeDelete = TRUE;
				g_pGameMain->m_pInfWindow->AddMsgBox(buf, _Q_ITEM_DELETE);
			}
			else
			{
				// 2007-06-20 by bhsohn ������ ������, �޸� ���� ����
				//((CINFGameMain*)m_pParent->m_pParent)->m_pInven->m_pDeleteItem = NULL;
			//	((CINFGameMain*)m_pParent->m_pParent)m_pInven->InitDeleteItemInfo();
					g_pGameMain->m_pInven->InitDeleteItemInfo();
			}
		}
		break;
// 2013-04-23 by ssjung �߿� ������ ������ 2�� ���(����) �˾�â ���� - // _Q_INCHANT_ITEM_DELETE

		// 2015-09-25 Future, inactivity system
#ifdef C_DISCONNECT_INACTIVE_PLAYERS
		case _Q_AUTO_KICK:
		{
			if (bTimerClick)
			{
				// Timer expired, close the game
				g_pD3dApp->EndGame(FALSE);
			}
			else
			{
				// Doesn't matter what was pressed, cancel the auto logoff
				g_pGameMain->CancelInactivityKick();
			}
		}
		break;
#endif // C_DISCONNECT_INACTIVE_PLAYERS

	default :
		break;
	}
	//end 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â


	if (INPUT_MSG_BUTTON || INPUT_COUNT_BUTTON)
	{
		g_pD3dApp->CleanText();
		g_pD3dApp->m_bChatMode = FALSE;
		g_pD3dApp->m_inputkey.SetMaxLength(SIZE_MAX_CHAT_MESSAGE);
	}
}

// 2013-04-05 by bhsohn ������ 5�� ��Ȱ �ý��� �߰�
// õ���� ��ȣ�ߵ��ÿ� ���� ó��
void CINFMessageBox::SendCharacterDeadGameStart(BOOL bGoCityMap)
{
	g_pShuttleChild->m_bIsCameraPattern = FALSE;
	if(g_pShuttleChild->m_bAttackMode == _SIEGE)			// ������� ������ �Ϲݻ��·� ���� 
	{
		g_pShuttleChild->m_pEngine->ChangeBodyCondition(BODYCON_SIEGE_OFF_MASK);
		g_pShuttleChild->m_bAttackMode = _AIR;
	}
		
	if( g_pShuttleChild->m_dwState == _FALLING ||
		COMPARE_BODYCON_BIT(g_pShuttleChild->GetCurrentBodyCondition(), BODYCON_DEAD_MASK|BODYCON_EXPLOSION_MASK) )	
	{
		MSG_FC_CHARACTER_DEAD_GAMESTART sMsg;
		memset(&sMsg,0x00,sizeof(sMsg));
		char buffer[SIZE_MAX_PACKET];
		int nType = T_FC_CHARACTER_DEAD_GAMESTART;
		sMsg.ClientIndex = g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.ClientIndex;
		sMsg.CharacterUniqueNumber = g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.CharacterUniqueNumber;
		sMsg.bRebirthInCityMap		= FALSE;
		if(bGoCityMap)
		{
			sMsg.bRebirthInCityMap	= TRUE;
		}
		memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
		memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
		g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
	}			
}

void CINFMessageBox::SetData(DWORD dwData1, DWORD dwData2,UID64_t UniqueNumber)
{
	m_dwData = dwData1; 
	m_nAllNumber = dwData2;
	m_UniqueNumber = UniqueNumber;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CINFWindow::CINFWindow(CAtumNode* pParent)
{
	FLOG( "CINFWindow(CAtumNode* pParent)" );
/*
	//ģ��
	m_pCutdis	= NULL;
	m_pCutOver = NULL;
	m_pCutPush = NULL;
	m_pDeldis = NULL;
	m_pDelOver = NULL;
	m_pDelPush = NULL ;
	m_pResdis = NULL ;
	m_pResOver= NULL;
	m_pResPush = NULL;
	m_pFriend = NULL;
	m_pScrol = NULL;
	//�ź�
	m_pDetdis = NULL;
	m_pDetOver = NULL ;
	m_pDetPush = NULL ;
	m_pRtdis = NULL;
	m_pRtOver = NULL;
	m_pRtPush = NULL;
	m_pReject = NULL;
*/
	int i;
	for(i=0;i<9;i++)
		m_pBoxImage[i] = NULL;

	// 2007-11-12 by bhsohn ĳ�������� �޽��� �ڽ� ó��
	for(i=0;i<9;i++)
		m_pBoldBoxImage[i] = NULL;


	for(i=0;i<4;i++)
	{
#ifndef C_EPSODE4_UI_CHANGE_JSKIM						 // 2011. 10. 10 by jskim UI�ý��� ����
		m_pRollImage[i] = NULL;
#endif
		m_pOkButton[i] = NULL;
		m_pCancelButton[i] = NULL;
	}
	m_pGameData = NULL;
	m_pXclose = NULL;
	m_pAllBox = NULL;
	m_pAllButton[0] = NULL;
	m_pAllButton[1] = NULL;

	m_bLeftWindow = FALSE;
	m_bRightWindow = FALSE;
	m_pParent = pParent;
	m_bLockWindowPosY[0] = FALSE;
	m_bLockWindowPosY[1] = FALSE;
	m_pRadioButton[0] = NULL;
	m_pRadioButton[1] = NULL;
	m_pTradeBase = NULL;
	
	m_vecRadioString.clear();
	m_nRadioButtonArray = 2;
	m_bMessageBoxFlag = FALSE;
	m_vecMessageBox.clear();

/*
	m_bShowItemInfo = FALSE;
	memset( m_strClickItemTitle, 0x00, INFO_LINE*SIZE_MAX_CHAT_MESSAGE);
	memset( m_strClickItemInfo,0x00, INFO_LINE*SIZE_MAX_CHAT_MESSAGE);
	memset( m_strClickEnchantInfo,0x00, INFO_LINE*SIZE_MAX_CHAT_MESSAGE);
	memset( m_pFontClickItemTitle, 0x00, INFO_LINE);
	memset( m_pFontClickItemInfo, 0x00, INFO_LINE);
	memset( m_pFontClickEnchantInfo, 0x00, INFO_LINE);
	m_ptItemInfo.x = 0;
	m_ptItemInfo.y = 0;

	for(i=0;i<INFO_LINE;i++)
	{
		m_pFontClickItemTitle[i] = NULL;
		m_pFontClickItemInfo[i] = NULL;
		m_pFontClickEnchantInfo[i] = NULL;
	}*/
	// 2013-04-05 by bhsohn ������ 5�� ��Ȱ �ý��� �߰�
	m_fAllHallMapLiveWndTime = HELLMAP_ALLTIME_DEADMSG_LIVETIME;
}

BOOL CINFWindow::IsExistMsgBox( int nType)
{
	FLOG( "CINFWindow::IsExistMsgBox( int nType)" );
	vector<CINFMessageBox*>::iterator it = m_vecMessageBox.begin();
	while(it != m_vecMessageBox.end())
	{
		if((*it)->m_nMsgType == nType)
			return TRUE;
		it++;
	}
	return FALSE;
}

// 2008-07-14 by bhsohn EP3 ���� ó��
BOOL CINFWindow::IsExistMsgBoxString( int nType, char* pInputMessage)
{
	FLOG( "CINFWindow::IsExistMsgBox( int nType)" );
	vector<CINFMessageBox*>::iterator it = m_vecMessageBox.begin();
	while(it != m_vecMessageBox.end())
	{
		if(((*it)->m_nMsgType == nType)
			&&(0 == strcmp(pInputMessage, (*it)->m_strInputMessage)))
		{
			return TRUE;
		}
		it++;
	}
	return FALSE;
}

// 2013-06-26 by bhsohn �Ƹ� �÷��� �߰� ����
//void CINFWindow::AddMsgBox(char* strMsg, int nType, DWORD dwData1, DWORD dwData2, int nLiveTime,UID64_t UniqueNumber, char* strName)
void CINFWindow::AddMsgBox(char* strMsg, int nType, DWORD dwData1, DWORD dwData2, int nLiveTime,UID64_t UniqueNumber, char* strName, BOOL bChRtn/*=FALSE*/)
{
	FLOG( "CINFWindow::AddMsgBox(char* strMsg, int nType, DWORD dwData1, DWORD dwData2)" );

	if(nType == _MESSAGE || (SINGLE_MSGBOX))
	{
		vector<CINFMessageBox*>::iterator it = m_vecMessageBox.begin();
		while(it != m_vecMessageBox.end())
		{
			if((*it)->m_nMsgType == _MESSAGE)
			{
				CINFMessageBox* pMsgBox = *it;
				it = m_vecMessageBox.erase(it);
				pMsgBox->InvalidateDeviceObjects();
				pMsgBox->DeleteDeviceObjects();
				util::del(pMsgBox);
				continue;
			}	
			// 2013-04-23 by ssjung �߿� ������ ������ 2�� ���(����) �˾�â ����
			if((*it)->GetWillbeDeleteFlag())
			{
				it++;
				continue;
			}
			// end 2013-04-23 by ssjung �߿� ������ ������ 2�� ���(����) �˾�â ����

			if((SINGLE_MSGBOX))			
			{
				return;
			}
			it++;
		}
	}
//	if(nType == _MESSAGE || (SINGLE_MSGBOX) || (FORCED_SINGLE_MSGBOX))
//	{
//		vector<CINFMessageBox*>::iterator it = m_vecMessageBox.begin();
//		while(it != m_vecMessageBox.end())
//		{
//			if((*it)->m_nMsgType == _MESSAGE || 
//				((FORCED_SINGLE_MSGBOX) && !(NOT_FORCED_COMPARE_SINGLE_MSGBOX)))
//			{
//				CINFMessageBox* pMsgBox = *it;
//				it = m_vecMessageBox.erase(it);
//				pMsgBox->InvalidateDeviceObjects();
//				pMsgBox->DeleteDeviceObjects();
//				util::del(pMsgBox);
//				break;
//			}
//			if((!(FORCED_SINGLE_MSGBOX) && (COMPARE_SINGLE_MSGBOX)) ||				// ���� �޼����� �ƴѵ� ���� �̱� �޼����� ������.
//				((FORCED_SINGLE_MSGBOX) && (NOT_FORCED_COMPARE_SINGLE_MSGBOX)) ||	// ���� �޼����ε� ���� ���� �޼����� ������ �ʴ� �̱� �޼����� ������.
//				((SINGLE_MSGBOX) && (FORCED_COMPARE_SINGLE_MSGBOX)))				// �̱۸޼����ε� ���� ���� �޼��� ��� ���̸� ������.
//			{
//				return;
//			}
//			it++;
//		}
//	}
	// â�ѱ�, â���� �ɼ� ó��
	g_pInterface->SetWindowOrder(WNDInfWindow);

	// 2008-10-29 by bhsohn â���� ��� �ϋ� �ý���â�� �ȴݰ� ����
	BOOL bClose = TRUE;
	if(_Q_QUIT_MESSAGE == nType)
	{
		bClose = FALSE;
	}
	// end 2008-10-29 by bhsohn â���� ��� �ϋ� �ý���â�� �ȴݰ� ����
	
	//if(TRUE == m_bMessageBoxFlag)
	if(TRUE == m_bMessageBoxFlag && bClose)
	{
		MessageBoxProgressOption(nType,dwData1,dwData2,strName);
		return;
	}

	CINFMessageBox* pMsgBox = new CINFMessageBox(this);
	pMsgBox->InitDeviceObjects();
	pMsgBox->RestoreDeviceObjects();

	// 2013-04-05 by bhsohn ������ 5�� ��Ȱ �ý��� �߰�
//	pMsgBox->m_fLiveTime = nLiveTime;
	float fLiveTime = CheckHellMapLiveTime(nType, nLiveTime, pMsgBox);
	pMsgBox->m_fLiveTime = fLiveTime;
	// END 2013-04-05 by bhsohn ������ 5�� ��Ȱ �ý��� �߰�
	
	// 2013-06-26 by bhsohn �Ƹ� �÷��� �߰� ����
//	pMsgBox->SetText(strMsg, nType);
	pMsgBox->SetText(strMsg, nType, bChRtn);
	// END 2013-06-26 by bhsohn �Ƹ� �÷��� �߰� ����	
	pMsgBox->SetData(dwData1, dwData2,UniqueNumber);
	// 2007-02-15 by dgwoo strName�� �޽��� �ڽ��� �˾ƾ��� ������ �ִٸ� CINFMessageBox class�� 
	//					m_strInputMessage�� �����Ѵ�.
	if(strName != NULL)
	{
		pMsgBox->SetInputStrName(strName);
	}
	
	m_vecMessageBox.push_back(pMsgBox);
	g_input.ResetFontBuffer();
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2013-04-05 by bhsohn ������ 5�� ��Ȱ �ý��� �߰�
/// \date		2013-04-05 ~ 2013-04-05
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
float CINFWindow::CheckHellMapLiveTime(int nType, int nLiveTime, CINFMessageBox* pMsgBox)
{
	float fRtnLiveTime = nLiveTime;

	MAP_INFO* pMapInfo = g_pDatabase->GetMapInfo(g_pD3dApp->GetMyShuttleMapChannelIndex().MapIndex);
	if(!pMapInfo || !pMsgBox)
	{
		return fRtnLiveTime;
	}
	
	if(!IS_MAP_INFLUENCE_HELL(pMapInfo->MapInfluenceType))
	{
		// �������� �ƴϸ� ����
		return fRtnLiveTime;
	}
	else if(0 != nLiveTime)
	{
		return fRtnLiveTime;
	}
	switch(nType)
	{
	case _Q_INFLUENCEMAP_DEAD_RETURN:
	case _Q_DEAD_RETURN:
	case _Q_USE_SUPER_RESTORE:
	case _Q_USE_NORMAL_RESTORE:
	case _Q_FUELALLIN_DEAD_RETURN:
		{				
			fRtnLiveTime = max(1.00f, m_fAllHallMapLiveWndTime);	// �ּ� 0.01f�ʴ� ����			

			char chTimer[256] = {0,};
			// 2013-04-12 by bhsohn ������ 5�� ��Ȱ �ý��� ��Ʈ�� ����
//			strncpy(chTimer, STRMSG_C_060724_0000, 256); // "\\r%d �� �� ������ϴ�.\\w"			
			strncpy(chTimer, STRMSG_C_130412_0001, 256); // "\\r%d �� �� ������ϴ�.\\w"			
			pMsgBox->SetTimeMessage1(chTimer) ;			

			DbgOutA("nType[%d] fRtnLiveTime[%.2f] \n", nType, fRtnLiveTime);
		}
		break;
	}
	
	return fRtnLiveTime;
}

void CINFWindow::InitHellMapLiveTime()
{
	m_fAllHallMapLiveWndTime = HELLMAP_ALLTIME_DEADMSG_LIVETIME; // 300��
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void AddTimeMsgBox(char* strMsg, int nType, int nLiveTime, char* strTime, DWORD dwData1 = 0, DWORD dwData2 = 0,UID64_t UniqueNumber = 0);
/// \brief		���� �ð��� �����ϴ� �޽���.
/// \author		dgwoo
/// \date		2007-05-15 ~ 2007-05-15
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFWindow::AddTimeMsgBox(char* strMsg, int nType, int nLiveTime, char* strTime, DWORD dwData1, DWORD dwData2,UID64_t UniqueNumber)
{
	FLOG( "CINFWindow::AddMsgBox(char* strMsg, int nType, DWORD dwData1, DWORD dwData2)" );
	if(nType == _MESSAGE || (SINGLE_MSGBOX))
	{
		vector<CINFMessageBox*>::iterator it = m_vecMessageBox.begin();
		while(it != m_vecMessageBox.end())
		{
			if((*it)->m_nMsgType == _MESSAGE)
			{
				CINFMessageBox* pMsgBox = *it;
				it = m_vecMessageBox.erase(it);
				pMsgBox->InvalidateDeviceObjects();
				pMsgBox->DeleteDeviceObjects();
				util::del(pMsgBox);
				continue;
			}
			if((SINGLE_MSGBOX))			
			{
				return;
			}
			it++;
		}
	}
//	if(nType == _MESSAGE || (SINGLE_MSGBOX) || (FORCED_SINGLE_MSGBOX))
//	{
//		vector<CINFMessageBox*>::iterator it = m_vecMessageBox.begin();
//		while(it != m_vecMessageBox.end())
//		{
//			if((*it)->m_nMsgType == _MESSAGE || 
//				((FORCED_SINGLE_MSGBOX) && !(NOT_FORCED_COMPARE_SINGLE_MSGBOX)))
//			{
//				CINFMessageBox* pMsgBox = *it;
//				it = m_vecMessageBox.erase(it);
//				pMsgBox->InvalidateDeviceObjects();
//				pMsgBox->DeleteDeviceObjects();
//				util::del(pMsgBox);
//				break;
//			}
//			if((!(FORCED_SINGLE_MSGBOX) && (COMPARE_SINGLE_MSGBOX)) ||				// ���� �޼����� �ƴѵ� ���� �̱� �޼����� ������.
//				((FORCED_SINGLE_MSGBOX) && (NOT_FORCED_COMPARE_SINGLE_MSGBOX)) ||	// ���� �޼����ε� ���� ���� �޼����� ������ �ʴ� �̱� �޼����� ������.
//				((SINGLE_MSGBOX) && (FORCED_COMPARE_SINGLE_MSGBOX)))				// �̱۸޼����ε� ���� ���� �޼��� ��� ���̸� ������.
//			{
//				return;
//			}
//			it++;
//		}
//	}
	// â�ѱ�, â���� �ɼ� ó��
	g_pInterface->SetWindowOrder(WNDInfWindow);
	CINFMessageBox* pMsgBox = new CINFMessageBox(this);
	pMsgBox->InitDeviceObjects();
	pMsgBox->RestoreDeviceObjects();
	//pMsgBox->m_strTimeMessage = strTime;
	if(strTime != NULL && strlen(strTime) > 0)
		memcpy(pMsgBox->m_strTimeMessage,strTime,256);
	pMsgBox->m_fLiveTime = nLiveTime;
	pMsgBox->SetText(strMsg, nType);

	pMsgBox->SetData(dwData1, dwData2,UniqueNumber);
	// 2007-02-15 by dgwoo strName�� �޽��� �ڽ��� �˾ƾ��� ������ �ִٸ� CINFMessageBox class�� 
	//					m_strInputMessage�� �����Ѵ�.
//	if(strName != NULL)
//	{
//		pMsgBox->SetInputStrName(strName);
//	}
	
	m_vecMessageBox.push_back(pMsgBox);
	// 2013-02-13 by mspark, ä��â�� ���� ���� Ư�� ��Ȳ���� ������� ���� �ذ� - g_input.ResetFontBuffer() �ּ�
	//g_input.ResetFontBuffer();
	// end 2013-02-13 by mspark, ä��â�� ���� ���� Ư�� ��Ȳ���� ������� ���� �ذ� - g_input.ResetFontBuffer() �ּ�
}

void CINFWindow::DeleteMsgBox(int nType)
{
	FLOG( "CINFWindow::DeleteMsgBox(int nType)" );
	vector<CINFMessageBox*>::iterator it = m_vecMessageBox.begin();
	while(it != m_vecMessageBox.end())
	{
		if((*it)->m_nMsgType == nType)
			break;
		else
			it++;
	}
	if(it != m_vecMessageBox.end())
	{
		CINFMessageBox* pMsgBox = *it;
		m_vecMessageBox.erase(it);
		pMsgBox->InvalidateDeviceObjects();
		pMsgBox->DeleteDeviceObjects();
		delete pMsgBox;
		pMsgBox = NULL;
	}
}

CINFWindow::~CINFWindow()
{
	FLOG( "~CINFWindow()" );
/*	//ģ��
	util::del(m_pCutdis);
	util::del(m_pCutOver);
	util::del(m_pCutPush);
	util::del(m_pDeldis );
	util::del(m_pDelOver)
	util::del(m_pDelPush)
	util::del(m_pResdis);
	util::del(m_pResOver);
	util::del(m_pResPush );
	util::del(m_pFriend );
	util::del(m_pScrol ) ;

	//�ź�
	util::del(m_pDetdis );
	util::del(m_pDetOver);
	util::del(m_pDetPush);
	util::del(m_pRtdis);
	util::del(m_pRtOver);
	util::del(m_pRtPush);
	util::del(m_pReject);
	*/


//	util::del(m_pGameData);
	util::del(m_pXclose);
	util::del(m_pAllBox);
	util::del(m_pAllButton[0]);
	util::del(m_pAllButton[1]);
	int i;
	for(i=0;i<9;i++)
		util::del(m_pBoxImage[i]);

	// 2007-11-12 by bhsohn ĳ�������� �޽��� �ڽ� ó��
	for(i=0;i<9;i++)
		util::del(m_pBoldBoxImage[i]);	


	for(i=0;i<4;i++)
	{
#ifndef C_EPSODE4_UI_CHANGE_JSKIM                                 // 2011. 10. 10 by jskim UI�ý��� ����
		util::del(m_pRollImage[i]);
#endif
		util::del(m_pOkButton[i]);
		util::del(m_pCancelButton[i]);
	}
	util::del(m_pRadioButton[0]);
	util::del(m_pRadioButton[1]);
	util::del(m_pTradeBase);

	m_vecRadioString.clear();
	m_vecMessageBox.clear();
}


HRESULT CINFWindow::InitDeviceObjects()
{
	FLOG( "CINFWindow::InitDeviceObjects()" );
	int i;
	for(i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			char buf[12];
			wsprintf(buf, "box%d%d",i,j);
// 2011. 10. 10 by jskim UI�ý��� ����
			m_pBoxImage[i*3+j] = new CINFImageEx;
			DataHeader* pDataHeader = FindResource(buf);
			m_pBoxImage[i*3+j]->InitDeviceObjects(pDataHeader);
// end 2011. 10. 10 by jskim UI�ý��� ����
		}
	}

	// 2007-11-12 by bhsohn ĳ�������� �޽��� �ڽ� ó��
	for(i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			char buf[12];
			wsprintf(buf, "bbox%d%d",i,j);
			DataHeader* pDataHeader = FindResource(buf);
			if(pDataHeader)
			{
// 2011. 10. 10 by jskim UI�ý��� ����
				m_pBoldBoxImage[i*3+j] = new CINFImageEx;			
				m_pBoldBoxImage[i*3+j]->InitDeviceObjects(pDataHeader);
// end 2011. 10. 10 by jskim UI�ý��� ����
			}
			
		}
	}	
	// end 2007-11-12 by bhsohn ĳ�������� �޽��� �ڽ� ó��

// 2011. 10. 10 by jskim UI�ý��� ����
#ifndef C_EPSODE4_UI_CHANGE_JSKIM
	for(i=0;i<2;i++)
	{
		for(int j=0;j<2;j++)
		{
			char buf[12];
			wsprintf(buf, "roll%d%d",i,j);
 			m_pRollImage[i*2+j] = new CINFImageEx;
			DataHeader* pDataHeader = FindResource(buf);
 			m_pRollImage[i*2+j]->InitDeviceObjects(pDataHeader);
 		}
 	}
#endif

#ifdef C_EPSODE4_UI_CHANGE_JSKIM	   
    m_pXclose = new CINFImageEx;
	DataHeader* pDataHeader = FindResource("close");
	m_pXclose->InitDeviceObjects(pDataHeader) ;
    m_pAllBox = new CINFImageEx;
	pDataHeader = FindResource("msgAll");
	m_pAllBox->InitDeviceObjects(pDataHeader) ;
	m_pAllButton[0] = new CINFImageEx;
	pDataHeader = FindResource("Mallbtn_1");
	m_pAllButton[0]->InitDeviceObjects(pDataHeader) ;
	m_pAllButton[1] = new CINFImageEx;
	pDataHeader = FindResource("Mallbtn_2");
	m_pAllButton[1]->InitDeviceObjects(pDataHeader) ;
#else 
    m_pXclose = new CINFImageEx;
	DataHeader* pDataHeader = FindResource("xclose");
	m_pXclose->InitDeviceObjects(pDataHeader) ;
	m_pAllBox = new CINFImageEx;
	pDataHeader = FindResource("msgAll");
	m_pAllBox->InitDeviceObjects(pDataHeader) ;
	m_pAllButton[0] = new CINFImageEx;
	pDataHeader = FindResource("all_over");
	m_pAllButton[0]->InitDeviceObjects(pDataHeader) ;
	m_pAllButton[1] = new CINFImageEx;
	pDataHeader = FindResource("all_push");
	m_pAllButton[1]->InitDeviceObjects(pDataHeader) ;
#endif
						 
#ifdef C_EPSODE4_UI_CHANGE_JSKIM
// 2005-09-20 by ispark
	m_pOkButton[0] = new CINFImageEx;
	pDataHeader = FindResource("oks00");
	m_pOkButton[0]->InitDeviceObjects(pDataHeader);

	m_pOkButton[1] = new CINFImageEx;
	pDataHeader = FindResource("oks01");
	m_pOkButton[1]->InitDeviceObjects(pDataHeader);

	m_pOkButton[2] = new CINFImageEx;
	pDataHeader = FindResource("oks02");
	m_pOkButton[2]->InitDeviceObjects(pDataHeader);

	m_pOkButton[3] = new CINFImageEx;
	pDataHeader = FindResource("oks03");
	m_pOkButton[3]->InitDeviceObjects(pDataHeader);

// 2005-09-20 by ispark
	m_pCancelButton[0] = new CINFImageEx;
	pDataHeader = FindResource("cans00");
	m_pCancelButton[0]->InitDeviceObjects(pDataHeader);

	m_pCancelButton[1] = new CINFImageEx;
	pDataHeader = FindResource("cans01");
	m_pCancelButton[1]->InitDeviceObjects(pDataHeader);

	m_pCancelButton[2] = new CINFImageEx;
	pDataHeader = FindResource("cans02");
	m_pCancelButton[2]->InitDeviceObjects(pDataHeader);

	m_pCancelButton[3] = new CINFImageEx;
	pDataHeader = FindResource("cans03");
	m_pCancelButton[3]->InitDeviceObjects(pDataHeader);	 
#else  
	m_pOkButton[0] = new CINFImageEx;
	pDataHeader = FindResource("sok0");
	m_pOkButton[0]->InitDeviceObjects(pDataHeader);

		m_pOkButton[1] = new CINFImageEx;
	pDataHeader = FindResource("sok1");
	m_pOkButton[1]->InitDeviceObjects(pDataHeader);

		m_pOkButton[2] = new CINFImageEx;
	pDataHeader = FindResource("sok2");
	m_pOkButton[2]->InitDeviceObjects(pDataHeader);

		m_pOkButton[3] = new CINFImageEx;
	pDataHeader = FindResource("sok3");
	m_pOkButton[3]->InitDeviceObjects(pDataHeader);

// 2005-09-20 by ispark
	m_pCancelButton[0] = new CINFImageEx;
	pDataHeader = FindResource("glcan00");
	m_pCancelButton[0]->InitDeviceObjects(pDataHeader);

	m_pCancelButton[1] = new CINFImageEx;
	pDataHeader = FindResource("glcan01");
	m_pCancelButton[1]->InitDeviceObjects(pDataHeader);

	m_pCancelButton[2] = new CINFImageEx;
	pDataHeader = FindResource("glcan02");
	m_pCancelButton[2]->InitDeviceObjects(pDataHeader);

	m_pCancelButton[3] = new CINFImageEx;
	pDataHeader = FindResource("glcan03");
	m_pCancelButton[3]->InitDeviceObjects(pDataHeader);
#endif
		
	m_pRadioButton[0] = new CINFImageEx;
	pDataHeader = FindResource("radio_a");
	m_pRadioButton[0]->InitDeviceObjects(pDataHeader);

	m_pRadioButton[1] = new CINFImageEx;
	pDataHeader = FindResource("radio_b");
	m_pRadioButton[1]->InitDeviceObjects(pDataHeader);
	
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	pDataHeader = g_pGameMain->m_GruopImagemanager->FindResource("trade");
	m_pTradeBase = g_pGameMain->m_GruopImagemanager->GetGroupImage( pDataHeader );
	m_pTradeBase->InitDeviceObjects( g_pD3dApp->m_pImageList );
#else
	m_pTradeBase = new CINFImageEx;
	pDataHeader = FindResource("tradebs");
	m_pTradeBase->InitDeviceObjects(pDataHeader);
#endif
// end 2011. 10. 10 by jskim UI�ý��� ����
	return S_OK ;
}

HRESULT CINFWindow::RestoreDeviceObjects()
{
	FLOG( "CINFWindow::RestoreDeviceObjects()" );
	int i;
	for(i=0;i<9;i++)
		m_pBoxImage[i]->RestoreDeviceObjects();
	// 2007-11-12 by bhsohn ĳ�������� �޽��� �ڽ� ó��
	for(i=0;i<9;i++)
	{
		if(m_pBoldBoxImage[i])
		{
			m_pBoldBoxImage[i]->RestoreDeviceObjects();	
		}
	}
	// end 2007-11-12 by bhsohn ĳ�������� �޽��� �ڽ� ó��

	for(i=0;i<4;i++)
	{
#ifndef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		m_pRollImage[i]->RestoreDeviceObjects();
#endif
		m_pOkButton[i]->RestoreDeviceObjects();
		m_pCancelButton[i]->RestoreDeviceObjects();
	}
	if(m_pXclose )
		m_pXclose->RestoreDeviceObjects();
	if(m_pAllBox )
		m_pAllBox->RestoreDeviceObjects();
	if(m_pAllButton[0] )
		m_pAllButton[0]->RestoreDeviceObjects();
	if(m_pAllButton[1] )
		m_pAllButton[1]->RestoreDeviceObjects();
	if(m_pRadioButton[0])
		m_pRadioButton[0]->RestoreDeviceObjects();
	if(m_pRadioButton[1])
		m_pRadioButton[1]->RestoreDeviceObjects();
	if(m_pTradeBase)
		m_pTradeBase->RestoreDeviceObjects();
	vector<CINFMessageBox*>::iterator it = m_vecMessageBox.begin();
	while(it != m_vecMessageBox.end())
	{
		(*it)->RestoreDeviceObjects();
		it++;
	}
	return S_OK ;
}

HRESULT CINFWindow::DeleteDeviceObjects()
{
	FLOG( "CINFWindow::DeleteDeviceObjects()" );
	int i;
	for(i=0;i<9;i++)
	{
		m_pBoxImage[i]->DeleteDeviceObjects();
		util::del(m_pBoxImage[i] ) ;
	}
	// 2007-11-12 by bhsohn ĳ�������� �޽��� �ڽ� ó��
	for(i=0;i<9;i++)
	{
		if(m_pBoldBoxImage[i])
		{
			m_pBoldBoxImage[i]->DeleteDeviceObjects();
			util::del(m_pBoldBoxImage[i] ) ;
		}
	}	
	// end 2007-11-12 by bhsohn ĳ�������� �޽��� �ڽ� ó��


	for(i=0;i<4;i++)
	{
#ifndef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		m_pRollImage[i]->DeleteDeviceObjects();
        util::del(m_pRollImage[i] );
#endif
		m_pOkButton[i]->DeleteDeviceObjects();
		m_pCancelButton[i]->DeleteDeviceObjects();
		util::del(m_pOkButton[i]);
		util::del(m_pCancelButton[i]);
	}
	if(m_pXclose )
		m_pXclose->DeleteDeviceObjects();
	util::del(m_pXclose );

	if(m_pAllBox )
		m_pAllBox->DeleteDeviceObjects();
	util::del(m_pAllBox );
	if(m_pAllButton[0] )
		m_pAllButton[0]->DeleteDeviceObjects();
	util::del(m_pAllButton[0] );
	if(m_pAllButton[1] )
		m_pAllButton[1]->DeleteDeviceObjects();
	util::del(m_pAllButton[1] );

	if(m_pRadioButton[0])
		m_pRadioButton[0]->DeleteDeviceObjects();
	util::del(m_pRadioButton[0]);	
	if(m_pRadioButton[1])
		m_pRadioButton[1]->DeleteDeviceObjects();
	util::del(m_pRadioButton[1]);

	if(m_pTradeBase)
		m_pTradeBase->DeleteDeviceObjects();
	util::del(m_pTradeBase);
	vector<CINFMessageBox*>::iterator it = m_vecMessageBox.begin();
	while(it != m_vecMessageBox.end())
	{
		CINFMessageBox* pMsgBox = *it;
		pMsgBox->DeleteDeviceObjects();
		util::del(pMsgBox);
		it = m_vecMessageBox.erase(it);
		// �ڵ����� it++�ȴ�.
	}
	return S_OK ;
}


HRESULT CINFWindow::InvalidateDeviceObjects()
{
	FLOG( "CINFWindow::InvalidateDeviceObjects()" );
	int i;
	for(i=0;i<9;i++)
		m_pBoxImage[i]->InvalidateDeviceObjects();
	// 2007-11-12 by bhsohn ĳ�������� �޽��� �ڽ� ó��
	for(i=0;i<9;i++)
	{
		if(m_pBoldBoxImage[i])
		{
			m_pBoldBoxImage[i]->InvalidateDeviceObjects();
		}
	}
	// end 2007-11-12 by bhsohn ĳ�������� �޽��� �ڽ� ó��

	for(i=0;i<4;i++)
	{
#ifndef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		m_pRollImage[i]->InvalidateDeviceObjects();
#endif
		m_pOkButton[i]->InvalidateDeviceObjects();
		m_pCancelButton[i]->InvalidateDeviceObjects();
	}
	if(m_pXclose )
		m_pXclose->InvalidateDeviceObjects();
	if(m_pAllBox )
		m_pAllBox->InvalidateDeviceObjects();
	if(m_pAllButton[0] )
		m_pAllButton[0]->InvalidateDeviceObjects();
	if(m_pAllButton[1] )
		m_pAllButton[1]->InvalidateDeviceObjects();
	if(m_pRadioButton[0])
		m_pRadioButton[0]->InvalidateDeviceObjects();
	if(m_pRadioButton[1])
		m_pRadioButton[1]->InvalidateDeviceObjects();
	if(m_pTradeBase)
		m_pTradeBase->InvalidateDeviceObjects();
	vector<CINFMessageBox*>::iterator it = m_vecMessageBox.begin();
	while(it != m_vecMessageBox.end())
	{
		(*it)->InvalidateDeviceObjects();
		it++;
	}
	return S_OK ;
}

HRESULT CINFWindow::InitMsgBoxObjects()
{
	FLOG( "CINFWindow::InitMsgBoxObjects()" );
	int i;
	for(i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			char buf[12];
			wsprintf(buf, "box%d%d",i,j);
// 2011. 10. 10 by jskim UI�ý��� ����
			m_pBoxImage[i*3+j] = new CINFImageEx;
			DataHeader* pDataHeader = FindResource(buf);
			m_pBoxImage[i*3+j]->InitDeviceObjects(pDataHeader);
// end 2011. 10. 10 by jskim UI�ý��� ����
		}
	}
	// 2007-11-12 by bhsohn ĳ�������� �޽��� �ڽ� ó��
	for(i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			char buf[12];
			wsprintf(buf, "bbox%d%d",i,j);
			DataHeader* pDataHeader = FindResource(buf);
			if(pDataHeader)
			{
// 2011. 10. 10 by jskim UI�ý��� ����
				m_pBoldBoxImage[i*3+j] = new CINFImageEx;			
				m_pBoldBoxImage[i*3+j]->InitDeviceObjects(pDataHeader);
// end 2011. 10. 10 by jskim UI�ý��� ����
			}		
		}
	}	
	// end 2007-11-12 by bhsohn ĳ�������� �޽��� �ڽ� ó��

// 2011. 10. 10 by jskim UI�ý��� ����
	m_pXclose = new CINFImageEx;
	DataHeader* pDataHeader = FindResource("xclose");
	m_pXclose->InitDeviceObjects(pDataHeader) ;

	m_pOkButton[0] = new CINFImageEx;
	pDataHeader = FindResource("Appover");
	m_pOkButton[0]->InitDeviceObjects(pDataHeader);

	m_pOkButton[1] = new CINFImageEx;
	pDataHeader = FindResource("Apppush");
	m_pOkButton[1]->InitDeviceObjects(pDataHeader);
	m_pOkButton[2] = new CINFImageEx;
	pDataHeader = FindResource("Appdis");
	m_pOkButton[2]->InitDeviceObjects(pDataHeader);

	m_pOkButton[3] = new CINFImageEx;
	pDataHeader = FindResource("Appnor");
	m_pOkButton[3]->InitDeviceObjects(pDataHeader);

	m_pCancelButton[0] = new CINFImageEx;
	pDataHeader = FindResource("Canover");
	m_pCancelButton[0]->InitDeviceObjects(pDataHeader);

	m_pCancelButton[1] = new CINFImageEx;
	pDataHeader = FindResource("Canpush");
	m_pCancelButton[1]->InitDeviceObjects(pDataHeader);

	m_pCancelButton[2] = new CINFImageEx;
	pDataHeader = FindResource("Candis");
	m_pCancelButton[2]->InitDeviceObjects(pDataHeader);

	m_pCancelButton[3] = new CINFImageEx;
	pDataHeader = FindResource("Cannor");
	m_pCancelButton[3]->InitDeviceObjects(pDataHeader);
// end 2011. 10. 10 by jskim UI�ý��� ����
	return S_OK ;
}

HRESULT CINFWindow::RestoreMsgBoxObjects()
{
	FLOG( "CINFWindow::RestoreMsgBoxObjects()" );
	int i;
	for(i=0;i<9;i++)
		m_pBoxImage[i]->RestoreDeviceObjects();
	// 2007-11-12 by bhsohn ĳ�������� �޽��� �ڽ� ó��
	for(i=0;i<9;i++)
	{
		if(m_pBoldBoxImage[i])
		{
			m_pBoldBoxImage[i]->RestoreDeviceObjects();
		}
	}
	// end 2007-11-12 by bhsohn ĳ�������� �޽��� �ڽ� ó��

	for(i=0;i<4;i++)
	{
		m_pOkButton[i]->RestoreDeviceObjects();
		m_pCancelButton[i]->RestoreDeviceObjects();
	}
	if(m_pXclose )
		m_pXclose->RestoreDeviceObjects();
	if(m_pRadioButton[0])
		m_pRadioButton[0]->RestoreDeviceObjects();
	if(m_pRadioButton[1])
		m_pRadioButton[1]->RestoreDeviceObjects();
	vector<CINFMessageBox*>::iterator it = m_vecMessageBox.begin();
	while(it != m_vecMessageBox.end())
	{
		(*it)->RestoreDeviceObjects();
		it++;
	}
	return S_OK ;
}

HRESULT CINFWindow::InvalidateMsgBoxObjects()
{
	FLOG( "CINFWindow::InvalidateMsgBoxObjects()" );
	int i;
	for(i=0;i<9;i++)
		m_pBoxImage[i]->InvalidateDeviceObjects();
	// 2007-11-12 by bhsohn ĳ�������� �޽��� �ڽ� ó��
	for(i=0;i<9;i++)
	{
		if(m_pBoldBoxImage[i])
		{
			m_pBoldBoxImage[i]->InvalidateDeviceObjects();
		}
	}
	// end 2007-11-12 by bhsohn ĳ�������� �޽��� �ڽ� ó��
	for(i=0;i<4;i++)
	{
		m_pOkButton[i]->InvalidateDeviceObjects();
		m_pCancelButton[i]->InvalidateDeviceObjects();
	}
	if(m_pXclose )
		m_pXclose->InvalidateDeviceObjects();
	if(m_pRadioButton[0])
		m_pRadioButton[0]->InvalidateDeviceObjects();
	if(m_pRadioButton[1])
		m_pRadioButton[1]->InvalidateDeviceObjects();
	
	vector<CINFMessageBox*>::iterator it = m_vecMessageBox.begin();
	while(it != m_vecMessageBox.end())
	{
		(*it)->InvalidateDeviceObjects();
		it++;
	}
	return S_OK ;

}

HRESULT CINFWindow::DeleteMsgBoxObjects()
{
	FLOG( "CINFWindow::DeleteMsgBoxObjects()" );
	int i;
	for(i=0;i<9;i++)
	{
		m_pBoxImage[i]->DeleteDeviceObjects();
		util::del(m_pBoxImage[i] ) ;
	}
	// 2007-11-12 by bhsohn ĳ�������� �޽��� �ڽ� ó��
	for(i=0;i<9;i++)
	{
		if(m_pBoldBoxImage[i])
		{
			m_pBoldBoxImage[i]->DeleteDeviceObjects();
			util::del(m_pBoldBoxImage[i] ) ;
		}
	}		
	// end 2007-11-12 by bhsohn ĳ�������� �޽��� �ڽ� ó��

	for(i=0;i<4;i++)
	{
		m_pOkButton[i]->DeleteDeviceObjects();
		m_pCancelButton[i]->DeleteDeviceObjects();
		util::del(m_pOkButton[i]);
		util::del(m_pCancelButton[i]);
	}
	if(m_pXclose )
		m_pXclose->DeleteDeviceObjects();
	util::del(m_pXclose );
	if(m_pRadioButton[0])
		m_pRadioButton[0]->DeleteDeviceObjects();
	util::del(m_pRadioButton[0]);
	if(m_pRadioButton[1])
		m_pRadioButton[1]->DeleteDeviceObjects();
	util::del(m_pRadioButton[1]);

	vector<CINFMessageBox*>::iterator it = m_vecMessageBox.begin();
	while(it != m_vecMessageBox.end())
	{
		CINFMessageBox* pMsgBox = *it;
		pMsgBox->DeleteDeviceObjects();
		util::del(pMsgBox);
		it = m_vecMessageBox.erase(it);
		// �ڵ����� it++�ȴ�.
	}
	return S_OK ;
}

void CINFWindow::Tick()
{
	FLOG( "CINFWindow::Tick()" );
	vector<CINFMessageBox*>::iterator it = m_vecMessageBox.begin();
	while(it != m_vecMessageBox.end())
	{
		CINFMessageBox* pMsgBox = *it;
		if(pMsgBox->m_fLiveTime != 0)
		{
			pMsgBox->m_fLiveTime -= g_pD3dApp->GetElapsedTime();

			if(pMsgBox->m_fLiveTime <= 0)
			{
				// 2013-04-05 by bhsohn ������ 5�� ��Ȱ �ý��� �߰�
//				pMsgBox->OnButtonClick(1);
				pMsgBox->OnButtonClick(1, TRUE);
				// END 2013-04-05 by bhsohn ������ 5�� ��Ȱ �ý��� �߰�
				pMsgBox->DeleteDeviceObjects();
				util::del(pMsgBox);
				it = m_vecMessageBox.erase(it);
				continue;
			}
		}
		it++;
	}	

	if(m_vecMessageBox.empty() == TRUE)
	{
		g_pD3dApp->m_bMessageBox = FALSE;
	}
	else
	{
		g_pD3dApp->m_bMessageBox = TRUE;
		// 2013-04-05 by bhsohn ������ 5�� ��Ȱ �ý��� �߰�
		if(m_fAllHallMapLiveWndTime > 0)
		{
			m_fAllHallMapLiveWndTime -= g_pD3dApp->GetCheckElapsedTime();
		}
		// END 2013-04-05 by bhsohn ������ 5�� ��Ȱ �ý��� �߰�
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2009-01-16 by bhsohn ���̽�ƽ �߰� ����/��� �߰�
/// \date		2009-01-16 ~ 2009-01-16
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFWindow::OnButtonClick(int i)
{
	vector<CINFMessageBox*>::iterator it = m_vecMessageBox.begin();
	if(it == m_vecMessageBox.end())
	{
		return;
	}
	CINFMessageBox* pMsgBox = *it;
	if(0 == i)
	{
		if(!pMsgBox->IsPossiblOkCancel())
		{
			// ���� ��ư ���
			return;
		}
	}	
	pMsgBox->OnButtonClick(i);

	{
		// ������ ����� 
		vector<CINFMessageBox*>::iterator itErase = m_vecMessageBox.begin();
		while(itErase != m_vecMessageBox.end())
		{
			if(*itErase == pMsgBox)
			{
				m_vecMessageBox.erase(itErase);
				//					m_vecMessageBox.erase(it);
				pMsgBox->InvalidateDeviceObjects();
				pMsgBox->DeleteDeviceObjects();
				util::del(pMsgBox);
				break;
			}
			itErase++;
		}
	}
}

void CINFWindow::RenderMessaegBox()
{
	FLOG( "CINFWindow::RenderMessaegBox()" );
	vector<CINFMessageBox*>::iterator it = m_vecMessageBox.begin();
	while(it != m_vecMessageBox.end())
	{
		(*it)->Render();
		it++;
	}
}

void CINFWindow::SetMessageBoxTitleChange(char *strTitle, int nMsgType)
{
	FLOG( "CINFWindow::RenderMessaegBox()" );
	vector<CINFMessageBox*>::iterator it = m_vecMessageBox.begin();
	while(it != m_vecMessageBox.end())
	{
		if(nMsgType == (*it)->m_nMsgType)
			(*it)->SetMessageBoxTitleChange(strTitle);
		it++;
	}
}

void CINFWindow::Render()
{
	FLOG( "CINFWindow::Render()" );
	int nWindowPosY = g_pGameMain->m_nLeftWindowY;

//	if(((CINFGameMain*)m_pParent)->m_nLeftWindowInfo == LEFT_WINDOW_TRANS || 
//		((CINFGameMain*)m_pParent)->m_nLeftWindowInfo == LEFT_WINDOW_SHOP )
	if(((CINFGameMain*)m_pParent)->m_nLeftWindowInfo == LEFT_WINDOW_SHOP )
	{
//		// �ŷ�, ���� â
//		if(((CINFGameMain*)m_pParent)->m_nLeftWindowInfo == LEFT_WINDOW_TRANS)
//		{
//			m_pTradeBase->Move(445,nWindowPosY);
//			m_pTradeBase->Render();
//			
//			DrawLeftWindow(0, nWindowPosY, ((float)g_pGameMain->m_nLeftWindowScaleSize/(float)SIZE_NORMAL_WINDOW_Y*SIZE_BIG_WINDOW_X),
//						   ((CINFGameMain*)m_pParent)->m_nLeftWindowScaleSize, TRUE);
//		}
//		else
		{
			DrawLeftWindow(0, nWindowPosY, ((float)g_pGameMain->m_nLeftWindowScaleSize/(float)SIZE_NORMAL_WINDOW_Y*SIZE_BIG_WINDOW_X),
						   ((CINFGameMain*)m_pParent)->m_nLeftWindowScaleSize, TRUE);
		}
	}
	else
	{
		// ���� �ӽ� ��ȣ �ο�
		// 2006-07-20 by dgwoo ������ â�� �������� �ٸ鼭 0���� �۾����� �׸��� �̻��� ��ġ�� ������ ������ �ִ�.
		// �װ� ���� ���� �Ʒ��� ���� ������ �߰�.
		int oldLeftWindowScaleSize = ((CINFGameMain*)m_pParent)->m_nLeftWindowScaleSize;
		if(oldLeftWindowScaleSize < 0)
			oldLeftWindowScaleSize = GetPositionInvenScreenMode();
		/*--------------------------------------------------------------------------*/
		// 2006-08-17 by ispark, ��� ������ ���ؼ� ���� ��� �Ѵ�.
		float fScaleSizeTemp = (float)((CINFGameMain*)m_pParent)->m_nLeftWindowScaleSize / (float)SIZE_NORMAL_WINDOW_Y;
		if(m_nLeftWindowInfo == 1)	// �κ��丮
		{
//			DrawLeftWindow(0, nWindowPosY, (int)((float)(((CINFGameMain*)m_pParent)->m_nLeftWindowScaleSize/(float)SIZE_NORMAL_WINDOW_Y)*SIZE_RNORMAL_WINDOW_X),
//				oldLeftWindowScaleSize, TRUE);
			DrawLeftWindow(0, nWindowPosY, (int)(fScaleSizeTemp * SIZE_RNORMAL_WINDOW_X),
				oldLeftWindowScaleSize, TRUE);
		}		
		// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
		else if(((CINFGameMain*)m_pParent)->m_nLeftWindowInfo == LEFT_WINDOW_TRANS)		
		{
			// 2008-10-20 by bhsohn �ŷ��� â���� ����
			//nWindowPosY += 52;
			nWindowPosY = (DEAULT_WINDOW_POS_Y-125);
			// end 2008-10-20 by bhsohn �ŷ��� â���� ����
			m_pTradeBase->Move((int)((float)((CINFGameMain*)m_pParent)->m_nLeftWindowScaleSize/(float)SIZE_NORMAL_WINDOW_Y*SIZE_RNORMAL_WINDOW_X),nWindowPosY);
			m_pTradeBase->Render();	
		}
		// end 2008-08-22 by bhsohn EP3 �κ��丮 ó��
		else			
		{
			//��Ƽâ 
//			DrawLeftWindow(0, nWindowPosY, (int)((float)((CINFGameMain*)m_pParent)->m_nLeftWindowScaleSize/(float)SIZE_NORMAL_WINDOW_Y*SIZE_NORMAL_WINDOW_X),
//				oldLeftWindowScaleSize);
			DrawLeftWindow(0, nWindowPosY, (int)(fScaleSizeTemp * SIZE_NORMAL_WINDOW_X),
				oldLeftWindowScaleSize);
		}
		// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
		// �ŷ�, ���� �κ��丮 â
//		if(((CINFGameMain*)m_pParent)->m_nLeftWindowInfo == LEFT_WINDOW_TRANS)
//		{//426
//			m_pTradeBase->Move((int)((float)((CINFGameMain*)m_pParent)->m_nLeftWindowScaleSize/(float)SIZE_NORMAL_WINDOW_Y*SIZE_RNORMAL_WINDOW_X),nWindowPosY);
//			m_pTradeBase->Render();			
//		}
		// end 2008-08-22 by bhsohn EP3 �κ��丮 ó��
	}

	// 2008-09-22 by bhsohn EP3 ĳ���� â
//	nWindowPosY = g_pGameMain->m_nRightWindowY;	
//	DrawRightWindow(g_pD3dApp->GetBackBufferDesc().Width - (int)((float)((CINFGameMain*)m_pParent)->m_nRightWindowScaleSize/(float)SIZE_NORMAL_WINDOW_Y*SIZE_NORMAL_WINDOW_X),
//		nWindowPosY,
//		(int)((float)((CINFGameMain*)m_pParent)->m_nRightWindowScaleSize/(float)SIZE_NORMAL_WINDOW_Y*SIZE_NORMAL_WINDOW_X),
//		((CINFGameMain*)m_pParent)->m_nRightWindowScaleSize);

}

int CINFWindow::MsgBoxWndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	FLOG( "CINFWindow::MsgBoxWndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)" );
	vector<CINFMessageBox*>::iterator it = m_vecMessageBox.begin();
	while(it != m_vecMessageBox.end())
	{
		CINFMessageBox* pMsgBox = *it;
		int re = pMsgBox->WndProc(uMsg, wParam, lParam);
		if( re == INF_MSGPROC_CLOSE )
		{
			// 2006-06-01 by ispark
			vector<CINFMessageBox*>::iterator itErase = m_vecMessageBox.begin();
			while(itErase != m_vecMessageBox.end())
			{
				if(*itErase == pMsgBox)
				{
					m_vecMessageBox.erase(itErase);
//					m_vecMessageBox.erase(it);
					pMsgBox->InvalidateDeviceObjects();
					pMsgBox->DeleteDeviceObjects();
					util::del(pMsgBox);
					break;
				}
				itErase++;
			}
			return INF_MSGPROC_BREAK;
		}
		else if( re == INF_MSGPROC_BREAK )
		{
			return INF_MSGPROC_BREAK;
		}
		else
		{
			it++;
		}
	}
	return INF_MSGPROC_NORMAL;
}

int CINFWindow::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)// 1: normal, 2:message proc break;
{
	FLOG( "CINFWindow::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)" );
	if(MsgBoxWndProc(uMsg, wParam, lParam) == INF_MSGPROC_BREAK)
		return INF_MSGPROC_BREAK;
	switch(uMsg)
	{
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);

			CheckMouseReverse(&pt);
			// 2005-10-05 by ispark
			// �����ÿ��� ����ϵ��� ����
//			if(g_pD3dApp->m_bCharacter == FALSE && (g_pShuttleChild->m_bUnitStop == FALSE && g_pShuttleChild->m_bLandedMove == FALSE))
			if(!g_pShuttleChild->GetIsUseInterface())
				break;
			
			if(m_bLockWindowPosY[0])
			{
				int nMove = pt.y - m_ptMouse[0].y;
				int nOldNumber = ((CINFGameMain*)m_pParent)->m_nLeftWindowPosY;
				((CINFGameMain*)m_pParent)->m_nLeftWindowPosY += nMove;

				int nWindowPosY = g_pGameMain->m_nLeftWindowY;
				if(abs(((CINFGameMain*)m_pParent)->m_nLeftWindowPosY - DEAULT_WINDOW_POS_Y) < g_pD3dApp->GetBackBufferDesc().Height/80)
					((CINFGameMain*)m_pParent)->m_nLeftWindowPosY = DEAULT_WINDOW_POS_Y;
				else
					m_ptMouse[0] = pt;
			}
			else if(m_bLockWindowPosY[1])
			{
				int nMove = pt.y - m_ptMouse[1].y;
				int nOldNumber = ((CINFGameMain*)m_pParent)->m_nRightWindowPosY;
				((CINFGameMain*)m_pParent)->m_nRightWindowPosY += nMove;
				int nWindowPosY = g_pGameMain->m_nRightWindowY;

				if(abs(((CINFGameMain*)m_pParent)->m_nRightWindowPosY - DEAULT_WINDOW_POS_Y) < g_pD3dApp->GetBackBufferDesc().Height/80)
					((CINFGameMain*)m_pParent)->m_nRightWindowPosY = DEAULT_WINDOW_POS_Y;
				else
					m_ptMouse[1] = pt;
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);

			CheckMouseReverse(&pt);
			int nWindowPosY = g_pGameMain->m_nLeftWindowY;
			if(((CINFGameMain*)m_pParent)->m_nLeftWindowInfo == LEFT_WINDOW_TRANS || ((CINFGameMain*)m_pParent)->m_nLeftWindowInfo == LEFT_WINDOW_SHOP)
			{
				// x-close
				if(LEFT_WINDOW_WEAPON != ((CINFGameMain*)m_pParent)->m_nLeftWindowInfo &&
				   pt.x > (int)((float)((CINFGameMain*)m_pParent)->m_nLeftWindowScaleSize/(float)SIZE_NORMAL_WINDOW_Y*SIZE_BIG_WINDOW_X) - 14 &&
				   pt.y > nWindowPosY+5 &&
				   pt.x < (int)((float)((CINFGameMain*)m_pParent)->m_nLeftWindowScaleSize/(float)SIZE_NORMAL_WINDOW_Y*SIZE_BIG_WINDOW_X) - 7 &&
				   pt.y < nWindowPosY+15)
				{
					if(((CINFGameMain*)m_pParent)->m_pTrade->m_bTrading &&
						((CINFGameMain*)m_pParent)->m_nLeftWindowInfo == LEFT_WINDOW_TRANS)
					{
						((CINFGameMain*)m_pParent)->m_pInfWindow->AddMsgBox(STRMSG_C_TRADE_0008, _Q_TRADE_CANCEL);//"�ŷ��� ����Ͻðڽ��ϱ�?"
					}
					else
					{
						((CINFGameMain*)m_pParent)->LeftWindowShow(TRUE,LEFT_WINDOW_WEAPON);
					}
					return INF_MSGPROC_BREAK;
				}
				if(pt.x > 0 &&
				   pt.y > nWindowPosY &&
				   pt.x < (int)((float)((CINFGameMain*)m_pParent)->m_nLeftWindowScaleSize/(float)SIZE_NORMAL_WINDOW_Y*SIZE_BIG_WINDOW_X) &&
				   pt.y < nWindowPosY+19) // 19: title bar height
				{
					m_bLockWindowPosY[0] = TRUE;
					m_ptMouse[0] = pt;
					return INF_MSGPROC_BREAK;
				}
			}
			else
			{
				// x-close
				if(LEFT_WINDOW_WEAPON != ((CINFGameMain*)m_pParent)->m_nLeftWindowInfo &&
				   pt.x > (int)((float)((CINFGameMain*)m_pParent)->m_nLeftWindowScaleSize/(float)SIZE_NORMAL_WINDOW_Y*SIZE_RNORMAL_WINDOW_X) - 14 &&
				   pt.y > nWindowPosY+5 &&
				   pt.x < (int)((float)((CINFGameMain*)m_pParent)->m_nLeftWindowScaleSize/(float)SIZE_NORMAL_WINDOW_Y*SIZE_RNORMAL_WINDOW_X) - 7 &&
				   pt.y < nWindowPosY+15 && g_pShuttleChild->GetRenderInvenFlag())
				{
					((CINFGameMain*)m_pParent)->LeftWindowShow(TRUE, LEFT_WINDOW_WEAPON);
					return INF_MSGPROC_BREAK;
				}
				else if(LEFT_WINDOW_WEAPON != ((CINFGameMain*)m_pParent)->m_nLeftWindowInfo &&
				   pt.x > (int)((float)((CINFGameMain*)m_pParent)->m_nLeftWindowScaleSize/(float)SIZE_NORMAL_WINDOW_Y*SIZE_NORMAL_WINDOW_X) - 14 &&
				   pt.y > nWindowPosY+5 &&
				   pt.x < (int)((float)((CINFGameMain*)m_pParent)->m_nLeftWindowScaleSize/(float)SIZE_NORMAL_WINDOW_Y*SIZE_NORMAL_WINDOW_X) - 7 &&
				   pt.y < nWindowPosY+15 && !g_pShuttleChild->GetRenderInvenFlag())
				{
					((CINFGameMain*)m_pParent)->LeftWindowShow(TRUE, LEFT_WINDOW_WEAPON);
					return INF_MSGPROC_BREAK;
				}
				
				if(pt.x > 0 &&
				   pt.y > nWindowPosY &&
				   pt.x < (int)((float)((CINFGameMain*)m_pParent)->m_nLeftWindowScaleSize/(float)SIZE_NORMAL_WINDOW_Y*SIZE_RNORMAL_WINDOW_X) &&
				   pt.y < nWindowPosY+19 && g_pShuttleChild->GetRenderInvenFlag()) // 19: title bar height
				{
//					m_bLockWindowPosY[0] = TRUE;
//					m_ptMouse[0] = pt;
//					return INF_MSGPROC_BREAK;
				}
				else if(pt.x > 0 &&
				   pt.y > nWindowPosY &&
				   pt.x < (int)((float)((CINFGameMain*)m_pParent)->m_nLeftWindowScaleSize/(float)SIZE_NORMAL_WINDOW_Y*SIZE_NORMAL_WINDOW_X) &&
				   pt.y < nWindowPosY+19)
				{
					// 2005-12-01 by ispark, 1������ �̵��ϱ� ���Ѱ�... �׷��� ���� ������ ����
					m_bLockWindowPosY[0] = TRUE;
					m_ptMouse[0] = pt;
//					return INF_MSGPROC_BREAK;
					return INF_MSGPROC_NORMAL;
				}

			}
			
			// x-close
			nWindowPosY = g_pGameMain->m_nRightWindowY;
			if(RIGHT_WINDOW_WEAPON != ((CINFGameMain*)m_pParent)->m_nRightWindowInfo &&
			   pt.x > g_pD3dApp->GetBackBufferDesc().Width - 14 &&
			   pt.y > nWindowPosY+5 &&
			   pt.x < g_pD3dApp->GetBackBufferDesc().Width - 7 &&
			   pt.y < nWindowPosY+15) // 19: title bar height
			{
				// 2008-09-22 by bhsohn EP3 ĳ���� â
//				((CINFGameMain*)m_pParent)->RightWindowShow(TRUE, RIGHT_WINDOW_WEAPON);
//				return INF_MSGPROC_BREAK;
			}
			
			if(pt.x > g_pD3dApp->GetBackBufferDesc().Width - (int)((float)((CINFGameMain*)m_pParent)->m_nRightWindowScaleSize/(float)SIZE_NORMAL_WINDOW_Y*SIZE_RNORMAL_WINDOW_X) &&
			   pt.y > nWindowPosY &&
			   pt.x < g_pD3dApp->GetBackBufferDesc().Width &&
			   pt.y < nWindowPosY+19 && g_pShuttleChild->GetRenderInvenFlag())
			{
//				m_bLockWindowPosY[1] = TRUE;
//				m_ptMouse[1] = pt;
//				return INF_MSGPROC_BREAK;
			}
			else if(pt.x > g_pD3dApp->GetBackBufferDesc().Width - (int)((float)((CINFGameMain*)m_pParent)->m_nRightWindowScaleSize/(float)SIZE_NORMAL_WINDOW_Y*SIZE_NORMAL_WINDOW_X) &&
			   pt.y > nWindowPosY &&
			   pt.x < g_pD3dApp->GetBackBufferDesc().Width &&
			   pt.y < nWindowPosY+19 && !g_pShuttleChild->GetRenderInvenFlag())
			{
				// 2005-12-01 by ispark, 2������ �̵��ϱ� ���Ѱ�... ������
				if(g_pShuttleChild->GetIsUseInterface())
				{
					m_bLockWindowPosY[1] = TRUE;
					m_ptMouse[1] = pt;
					return INF_MSGPROC_BREAK;
				}
				else
				{
					return INF_MSGPROC_NORMAL;
				}
			}

		}
		break;
	case WM_LBUTTONUP:
		{
			m_bLockWindowPosY[0] = FALSE;
			m_bLockWindowPosY[1] = FALSE;
		}
		break;
	}
	return INF_MSGPROC_NORMAL;

}

void CINFWindow::DrawLeftWindow(int x, int y, int cx, int cy, BOOL bInven)// cx > 39, cy > 39 , x = 0
{
	FLOG( "CINFWindow::DrawLeftWindow(int x, int y, int cx, int cy)" );
	if(m_bLeftWindow && g_pD3dApp->m_dwGameState != _SHOP)
	{
		// �κ��丮 ������ ���� ����
		g_pShuttleChild->SetRenderInven(TRUE);

// 2011. 10. 10 by jskim UI�ý��� ����
#ifdef C_EPSODE4_UI_CHANGE_JSKIM

		m_pBoxImage[0]->Move(x,y);
		m_pBoxImage[0]->Render();
		
		int nPosX = x + m_pBoxImage[0]->GetImgSize().x;
		int nImageSizeX = BOX_START_DEFAULT_MIN_X;
		
		m_pBoxImage[1]->Move( nPosX, y );
		m_pBoxImage[1]->SetRect( 0, 0, nImageSizeX, m_pBoxImage[1]->GetImgSize().y );
		m_pBoxImage[1]->SetScale( 1, 1 );
		m_pBoxImage[1]->Render();
		
		nPosX += nImageSizeX;
 		m_pBoxImage[1]->Move( nPosX, y );
 		m_pBoxImage[1]->SetRect( nImageSizeX, 0,  nImageSizeX + 1 , m_pBoxImage[1]->GetImgSize().y );
 		m_pBoxImage[1]->SetScale( cx - ( nImageSizeX + m_pBoxImage[0]->GetImgSize().x ) * 2, 1 );
 		m_pBoxImage[1]->Render();
 		
		nPosX += cx - ( nImageSizeX + m_pBoxImage[0]->GetImgSize().x ) * 2;
  		m_pBoxImage[1]->Move( nPosX, y );
  		m_pBoxImage[1]->SetRect( m_pBoxImage[1]->GetImgSize().x - nImageSizeX, 0, m_pBoxImage[1]->GetImgSize().x, m_pBoxImage[1]->GetImgSize().y );
		m_pBoxImage[1]->SetScale( 1, 1 );
  		m_pBoxImage[1]->Render();

		nPosX += nImageSizeX;
		m_pBoxImage[2]->Move( nPosX, y );
		m_pBoxImage[2]->Render();
		
		nPosX = x;
		m_pBoxImage[3]->Move(nPosX, y + m_pBoxImage[0]->GetImgSize().y );
		m_pBoxImage[3]->SetScale(1, (float)( cy - (m_pBoxImage[0]->GetImgSize().y) ) / m_pBoxImage[3]->GetImgSize().y );
		m_pBoxImage[3]->Render();
		
  		nPosX += m_pBoxImage[3]->GetImgSize().x;
 		m_pBoxImage[4]->Move(nPosX,  y + m_pBoxImage[1]->GetImgSize().y - 4);
 		m_pBoxImage[4]->SetRect( 0, 0, (int)(cx - m_pBoxImage[3]->GetImgSize().x * 2 - 1 ),  (( cy - (m_pBoxImage[0]->GetImgSize().y) ) / m_pBoxImage[3]->GetImgSize().y) + 9 );
 		m_pBoxImage[4]->Render();
 		
		nPosX += cx - m_pBoxImage[5]->GetImgSize().x;
 		m_pBoxImage[5]->Move( nPosX - 1, y + m_pBoxImage[2]->GetImgSize().y );
 		m_pBoxImage[5]->SetScale(1, (float)( cy - (m_pBoxImage[0]->GetImgSize().y) ) / m_pBoxImage[3]->GetImgSize().y );
 		m_pBoxImage[5]->Render();
 		
		nPosX = x;
		m_pBoxImage[6]->Move( nPosX , y + cy );
		m_pBoxImage[6]->Render();
		
		nPosX += m_pBoxImage[6]->GetImgSize().x;
		m_pBoxImage[7]->Move( nPosX, y + cy  );
		m_pBoxImage[7]->SetRect( 0, 0, nImageSizeX, m_pBoxImage[7]->GetImgSize().y );
		m_pBoxImage[7]->SetScale( 1, 1 );
		m_pBoxImage[7]->Render();
		
		nPosX += nImageSizeX;
 		m_pBoxImage[7]->Move( nPosX, y + cy );
 		m_pBoxImage[7]->SetRect( nImageSizeX, 0,  nImageSizeX + 1 , m_pBoxImage[7]->GetImgSize().y );
 		m_pBoxImage[7]->SetScale( cx - ( nImageSizeX + m_pBoxImage[6]->GetImgSize().x ) * 2, 1 );
 		m_pBoxImage[7]->Render();
		
		nPosX += cx - ( nImageSizeX + m_pBoxImage[6]->GetImgSize().x ) * 2;
		m_pBoxImage[7]->Move( nPosX, y + cy );
		m_pBoxImage[7]->SetRect( m_pBoxImage[7]->GetImgSize().x - nImageSizeX, 0, m_pBoxImage[7]->GetImgSize().x, m_pBoxImage[7]->GetImgSize().y );
		m_pBoxImage[7]->SetScale( 1, 1 );
  		m_pBoxImage[7]->Render();
		
		nPosX += nImageSizeX;
		m_pBoxImage[8]->Move( nPosX, y + cy );
		m_pBoxImage[8]->Render();

		m_pXclose->Move(x+cx-14,y+6);
		m_pXclose->Render();
//	}
//
//	if()
//	{
		//m_pRollImage[0]->Move(x,y-36);
		//m_pRollImage[0]->Render();
		//m_pRollImage[1]->Move(x,y+cy);
		//m_pRollImage[1]->Render();
	}						 
#else
		m_pBoxImage[0]->Move(x,y);
		m_pBoxImage[0]->Render();
		m_pBoxImage[1]->Move(x+19, y);
		m_pBoxImage[1]->SetScale(cx-38, 1);
		m_pBoxImage[1]->Render();
		m_pBoxImage[2]->Move(x+cx-19,y);
		m_pBoxImage[2]->Render();

		m_pBoxImage[3]->Move(x, y+19);
		m_pBoxImage[3]->SetScale(1, cy-38);
		m_pBoxImage[3]->Render();
		
		if(bInven == FALSE)
		{
			g_pShuttleChild->SetRenderInven(FALSE);
			m_pBoxImage[4]->Move(x+19, y+19);
			m_pBoxImage[4]->SetScale(cx-38,cy-38);
			m_pBoxImage[4]->Render();			
		}
		
		m_pBoxImage[5]->Move(x+cx-19, y+19);
		m_pBoxImage[5]->SetScale(1, cy-38);
		m_pBoxImage[5]->Render();

		m_pBoxImage[6]->Move(x,y+cy-19);
		m_pBoxImage[6]->Render();
		m_pBoxImage[7]->Move(x+19,y+cy-19);
		m_pBoxImage[7]->SetScale(cx-38, 1);
		m_pBoxImage[7]->Render();
		m_pBoxImage[8]->Move(x+cx-19,y+cy-19);
		m_pBoxImage[8]->Render();
		m_pXclose->Move(x+cx-14,y+6);
		m_pXclose->Render();
//	}
//
//	if()
//	{
		m_pRollImage[0]->Move(x,y-36);
		m_pRollImage[0]->Render();
		m_pRollImage[1]->Move(x,y+cy);
		m_pRollImage[1]->Render();
	}
#endif
// end 2011. 10. 10 by jskim UI�ý��� ����
}


void CINFWindow::DrawRightWindow(int x, int y, int cx, int cy)// cx > 39, cy > 39, x = GetBackBuffer().Width - cx
{
	FLOG( "CINFWindow::DrawRightWindow(int x, int y, int cx, int cy)" );
	if(m_bRightWindow && g_pD3dApp->m_dwGameState != _SHOP)
	{
		m_pBoxImage[0]->Move(x,y);
		m_pBoxImage[0]->Render();
// 2011. 10. 10 by jskim UI�ý��� ����		  
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		int nPosX = x + m_pBoxImage[0]->GetImgSize().x;
		int nImageSizeX = BOX_START_DEFAULT_MIN_X;
		
		m_pBoxImage[1]->Move( nPosX, y );
		m_pBoxImage[1]->SetRect( 0, 0, nImageSizeX, m_pBoxImage[1]->GetImgSize().y );
		m_pBoxImage[1]->SetScale( 1, 1 );
		m_pBoxImage[1]->Render();
		
		nPosX += nImageSizeX;
 		m_pBoxImage[1]->Move( nPosX, y );
 		m_pBoxImage[1]->SetRect( nImageSizeX, 0,  nImageSizeX + 1 , m_pBoxImage[1]->GetImgSize().y );
 		m_pBoxImage[1]->SetScale( cx - ( nImageSizeX + m_pBoxImage[0]->GetImgSize().x ) * 2, 1 );
 		m_pBoxImage[1]->Render();
 		
		nPosX += cx - ( nImageSizeX + m_pBoxImage[0]->GetImgSize().x ) * 2;
  		m_pBoxImage[1]->Move( nPosX, y );
  		m_pBoxImage[1]->SetRect( m_pBoxImage[1]->GetImgSize().x - nImageSizeX, 0, m_pBoxImage[1]->GetImgSize().x, m_pBoxImage[1]->GetImgSize().y );
		m_pBoxImage[1]->SetScale( 1, 1 );
  		m_pBoxImage[1]->Render();

		nPosX += nImageSizeX;
		m_pBoxImage[2]->Move( nPosX, y );
		m_pBoxImage[2]->Render();
		
		nPosX = x;
		m_pBoxImage[3]->Move(nPosX, y + m_pBoxImage[0]->GetImgSize().y );
		m_pBoxImage[3]->SetScale(1, (float)( cy - (m_pBoxImage[0]->GetImgSize().y) ) / m_pBoxImage[3]->GetImgSize().y );
		m_pBoxImage[3]->Render();
		
  		nPosX += m_pBoxImage[3]->GetImgSize().x;
 		m_pBoxImage[4]->Move(nPosX,  y + m_pBoxImage[1]->GetImgSize().y - 4);
 		m_pBoxImage[4]->SetRect( 0, 0, (int)(cx - m_pBoxImage[3]->GetImgSize().x * 2 - 1 ),  (( cy - (m_pBoxImage[0]->GetImgSize().y) ) / m_pBoxImage[3]->GetImgSize().y) + 9 );
 		m_pBoxImage[4]->Render();
 		
		nPosX += cx - m_pBoxImage[5]->GetImgSize().x;
 		m_pBoxImage[5]->Move( nPosX - 1, y + m_pBoxImage[2]->GetImgSize().y );
 		m_pBoxImage[5]->SetScale(1, (float)( cy - (m_pBoxImage[0]->GetImgSize().y) ) / m_pBoxImage[3]->GetImgSize().y );
 		m_pBoxImage[5]->Render();
 		
		nPosX = x;
		m_pBoxImage[6]->Move( nPosX , y + cy );
		m_pBoxImage[6]->Render();
		
		nPosX += m_pBoxImage[6]->GetImgSize().x;
		m_pBoxImage[7]->Move( nPosX, y + cy  );
		m_pBoxImage[7]->SetRect( 0, 0, nImageSizeX, m_pBoxImage[7]->GetImgSize().y );
		m_pBoxImage[7]->SetScale( 1, 1 );
		m_pBoxImage[7]->Render();
		
		nPosX += nImageSizeX;
 		m_pBoxImage[7]->Move( nPosX, y + cy );
 		m_pBoxImage[7]->SetRect( nImageSizeX, 0,  nImageSizeX + 1 , m_pBoxImage[7]->GetImgSize().y );
 		m_pBoxImage[7]->SetScale( cx - ( nImageSizeX + m_pBoxImage[6]->GetImgSize().x ) * 2, 1 );
 		m_pBoxImage[7]->Render();
		
		nPosX += cx - ( nImageSizeX + m_pBoxImage[6]->GetImgSize().x ) * 2;
		m_pBoxImage[7]->Move( nPosX, y + cy );
		m_pBoxImage[7]->SetRect( m_pBoxImage[7]->GetImgSize().x - nImageSizeX, 0, m_pBoxImage[7]->GetImgSize().x, m_pBoxImage[7]->GetImgSize().y );
		m_pBoxImage[7]->SetScale( 1, 1 );
  		m_pBoxImage[7]->Render();
		
		nPosX += nImageSizeX;
		m_pBoxImage[8]->Move( nPosX, y + cy );
		m_pBoxImage[8]->Render();
		m_pXclose->Move(g_pD3dApp->GetBackBufferDesc().Width-14,y+6);
		m_pXclose->Render();
//	}
//
//	if(g_pD3dApp->m_dwGameState != _SHOP)
//	{
// 		m_pRollImage[2]->Move(g_pD3dApp->GetBackBufferDesc().Width-25,y-36);
// 		m_pRollImage[2]->Render();
// 		m_pRollImage[3]->Move(g_pD3dApp->GetBackBufferDesc().Width-25,y+cy);
// 		m_pRollImage[3]->Render();
#else
		m_pBoxImage[1]->Move(x+19, y);
		m_pBoxImage[1]->SetScale(cx-38, 1);
		m_pBoxImage[1]->Render();
		m_pBoxImage[2]->Move(x+cx-19,y);
		m_pBoxImage[2]->Render();

		m_pBoxImage[3]->Move(x, y+19);
		m_pBoxImage[3]->SetScale(1, cy-38);
		m_pBoxImage[3]->Render();
		m_pBoxImage[4]->Move(x+19, y+19);
		m_pBoxImage[4]->SetScale(cx-38,cy-38);
		m_pBoxImage[4]->Render();
		m_pBoxImage[5]->Move(x+cx-19, y+19);
		m_pBoxImage[5]->SetScale(1, cy-38);
		m_pBoxImage[5]->Render();

		m_pBoxImage[6]->Move(x,y+cy-19);
		m_pBoxImage[6]->Render();
		m_pBoxImage[7]->Move(x+19,y+cy-19);
		m_pBoxImage[7]->SetScale(cx-38, 1);
		m_pBoxImage[7]->Render();
		m_pBoxImage[8]->Move(x+cx-19,y+cy-19);
		m_pBoxImage[8]->Render();
		m_pXclose->Move(g_pD3dApp->GetBackBufferDesc().Width-14,y+6);
		m_pXclose->Render();
//	}
//
//	if(g_pD3dApp->m_dwGameState != _SHOP)
//	{
		m_pRollImage[2]->Move(g_pD3dApp->GetBackBufferDesc().Width-25,y-36);
		m_pRollImage[2]->Render();
		m_pRollImage[3]->Move(g_pD3dApp->GetBackBufferDesc().Width-25,y+cy);
		m_pRollImage[3]->Render();
#endif
// end 2011. 10. 10 by jskim UI�ý��� ����
	}
}

void CINFWindow::RenderCenterWindow(int x, int y, int cx, int cy, BOOL bRenderClose)
{
	FLOG( "CINFWindow::RenderCenterWindow(int x, int y, int cx, int cy, BOOL bRenderClose)" );

	m_pBoxImage[0]->Move(x,y);
	m_pBoxImage[0]->Render();
										   
// 2011. 10. 10 by jskim UI�ý��� ����
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	int nPosX = x + m_pBoxImage[0]->GetImgSize().x;
	int nImageSizeX = BOX_START_DEFAULT_MIN_X;
	
	m_pBoxImage[1]->Move( nPosX, y );
	m_pBoxImage[1]->SetRect( 0, 0, nImageSizeX, m_pBoxImage[1]->GetImgSize().y );
	m_pBoxImage[1]->SetScale( 1, 1 );
	m_pBoxImage[1]->Render();
	
	nPosX += nImageSizeX;
 	m_pBoxImage[1]->Move( nPosX, y );
 	m_pBoxImage[1]->SetRect( nImageSizeX, 0,  nImageSizeX + 1 , m_pBoxImage[1]->GetImgSize().y );
 	m_pBoxImage[1]->SetScale( cx - ( nImageSizeX + m_pBoxImage[0]->GetImgSize().x ) * 2, 1 );
 	m_pBoxImage[1]->Render();
 	
	nPosX += cx - ( nImageSizeX + m_pBoxImage[0]->GetImgSize().x ) * 2;
  	m_pBoxImage[1]->Move( nPosX, y );
  	m_pBoxImage[1]->SetRect( m_pBoxImage[1]->GetImgSize().x - nImageSizeX, 0, m_pBoxImage[1]->GetImgSize().x, m_pBoxImage[1]->GetImgSize().y );
	m_pBoxImage[1]->SetScale( 1, 1 );
  	m_pBoxImage[1]->Render();

	nPosX += nImageSizeX;
	m_pBoxImage[2]->Move( nPosX, y );
	m_pBoxImage[2]->Render();
	
	nPosX = x;
	m_pBoxImage[3]->Move(nPosX, y + m_pBoxImage[0]->GetImgSize().y );
	m_pBoxImage[3]->SetScale(1, (float)( cy - (m_pBoxImage[0]->GetImgSize().y) ) / m_pBoxImage[3]->GetImgSize().y );
	m_pBoxImage[3]->Render();
	
  	nPosX += m_pBoxImage[3]->GetImgSize().x;
 	m_pBoxImage[4]->Move(nPosX,  y + m_pBoxImage[1]->GetImgSize().y);
 	m_pBoxImage[4]->SetRect( 0, 0, (int)(cx - m_pBoxImage[3]->GetImgSize().x - m_pBoxImage[5]->GetImgSize().x),  (( cy - (m_pBoxImage[0]->GetImgSize().y) ) / m_pBoxImage[3]->GetImgSize().y) );
 	m_pBoxImage[4]->Render();
 	
	nPosX += cx - m_pBoxImage[5]->GetImgSize().x;
 	m_pBoxImage[5]->Move( nPosX - 1, y + m_pBoxImage[2]->GetImgSize().y );
 	m_pBoxImage[5]->SetScale(1, (float)( cy - (m_pBoxImage[0]->GetImgSize().y) ) / m_pBoxImage[3]->GetImgSize().y );
 	m_pBoxImage[5]->Render();
 	
	nPosX = x;
	m_pBoxImage[6]->Move( nPosX , y + cy );
	m_pBoxImage[6]->Render();
	
	nPosX += m_pBoxImage[6]->GetImgSize().x;
	m_pBoxImage[7]->Move( nPosX, y + cy  );
	m_pBoxImage[7]->SetRect( 0, 0, nImageSizeX, m_pBoxImage[7]->GetImgSize().y );
	m_pBoxImage[7]->SetScale( 1, 1 );
	m_pBoxImage[7]->Render();
	
	nPosX += nImageSizeX;
 	m_pBoxImage[7]->Move( nPosX, y + cy );
 	m_pBoxImage[7]->SetRect( nImageSizeX, 0,  nImageSizeX + 1 , m_pBoxImage[7]->GetImgSize().y );
 	m_pBoxImage[7]->SetScale( cx - ( nImageSizeX + m_pBoxImage[6]->GetImgSize().x ) * 2, 1 );
 	m_pBoxImage[7]->Render();
	
	nPosX += cx - ( nImageSizeX + m_pBoxImage[6]->GetImgSize().x ) * 2;
	m_pBoxImage[7]->Move( nPosX, y + cy );
	m_pBoxImage[7]->SetRect( m_pBoxImage[7]->GetImgSize().x - nImageSizeX, 0, m_pBoxImage[7]->GetImgSize().x, m_pBoxImage[7]->GetImgSize().y );
	m_pBoxImage[7]->SetScale( 1, 1 );
  	m_pBoxImage[7]->Render();
	
	nPosX += nImageSizeX;
	m_pBoxImage[8]->Move( nPosX, y + cy );
	m_pBoxImage[8]->Render();
	if(bRenderClose)
	{
		m_pXclose->Move(x+cx-16,y - 2);
		m_pXclose->Render();
	}
#else 
	m_pBoxImage[1]->Move(x+19, y);
	m_pBoxImage[1]->SetScale(cx-38, 1);
	m_pBoxImage[1]->Render();
	m_pBoxImage[2]->Move(x+cx-19,y);
	m_pBoxImage[2]->Render();

	m_pBoxImage[3]->Move(x, y+19);
	m_pBoxImage[3]->SetScale(1, cy-38);
	m_pBoxImage[3]->Render();
	m_pBoxImage[4]->Move(x+19, y+19);
	m_pBoxImage[4]->SetScale(cx-38,cy-38);
	m_pBoxImage[4]->Render();
	m_pBoxImage[5]->Move(x+cx-19, y+19);
	m_pBoxImage[5]->SetScale(1, cy-38);
	m_pBoxImage[5]->Render();

	m_pBoxImage[6]->Move(x,y+cy-19);
	m_pBoxImage[6]->Render();
	m_pBoxImage[7]->Move(x+19,y+cy-19);
	m_pBoxImage[7]->SetScale(cx-38, 1);
	m_pBoxImage[7]->Render();
	m_pBoxImage[8]->Move(x+cx-19,y+cy-19);
	m_pBoxImage[8]->Render();
	if(bRenderClose)
	{
		m_pXclose->Move(x+cx-14,y+6);
		m_pXclose->Render();
	}
#endif
// end 2011. 10. 10 by jskim UI�ý��� ����
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			ĳ�������� �޽��� �ڽ� ó��
/// \brief		
/// \author		// 2007-11-12 by bhsohn ĳ�������� �޽��� �ڽ� ó��
/// \date		2007-11-12 ~ 2007-11-12
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFWindow::RenderBlackBK(int x, int y, int cx, int cy, BOOL bRenderClose)
{
	FLOG( "CINFWindow::RenderCenterWindow(int x, int y, int cx, int cy, BOOL bRenderClose)" );
// 2011. 10. 10 by jskim UI�ý��� ����
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	m_pBoxImage[0]->Move(x,y);
	m_pBoxImage[0]->Render();
	
	int nPosX = x + m_pBoxImage[0]->GetImgSize().x;
	int nImageSizeX = BOX_START_DEFAULT_MIN_X;
	
	m_pBoxImage[1]->Move( nPosX, y );
	m_pBoxImage[1]->SetRect( 0, 0, nImageSizeX, m_pBoxImage[1]->GetImgSize().y );
	m_pBoxImage[1]->SetScale( 1, 1 );
	m_pBoxImage[1]->Render();
	
	nPosX += nImageSizeX;
	m_pBoxImage[1]->Move( nPosX, y );
	m_pBoxImage[1]->SetRect( nImageSizeX, 0,  nImageSizeX + 1 , m_pBoxImage[1]->GetImgSize().y );
	m_pBoxImage[1]->SetScale( cx - ( nImageSizeX + m_pBoxImage[0]->GetImgSize().x ) * 2, 1 );
	m_pBoxImage[1]->Render();
	
	nPosX += cx - ( nImageSizeX + m_pBoxImage[0]->GetImgSize().x ) * 2;
	m_pBoxImage[1]->Move( nPosX, y );
	m_pBoxImage[1]->SetRect( m_pBoxImage[1]->GetImgSize().x - nImageSizeX, 0, m_pBoxImage[1]->GetImgSize().x, m_pBoxImage[1]->GetImgSize().y );
	m_pBoxImage[1]->SetScale( 1, 1 );
	m_pBoxImage[1]->Render();
	
	nPosX += nImageSizeX;
	m_pBoxImage[2]->Move( nPosX, y );
	m_pBoxImage[2]->Render();
	
	nPosX = x;
	m_pBoxImage[3]->Move(nPosX, y + m_pBoxImage[0]->GetImgSize().y );
	m_pBoxImage[3]->SetScale(1, (float)( cy - (m_pBoxImage[0]->GetImgSize().y) ) / m_pBoxImage[3]->GetImgSize().y );
	m_pBoxImage[3]->Render();
	
	nPosX += m_pBoxImage[3]->GetImgSize().x;
	m_pBoxImage[4]->Move(nPosX,  y + m_pBoxImage[1]->GetImgSize().y - 4);
	m_pBoxImage[4]->SetRect( 0, 0, (int)(cx - m_pBoxImage[3]->GetImgSize().x * 2 - 1 ),  (( cy - (m_pBoxImage[0]->GetImgSize().y) ) / m_pBoxImage[3]->GetImgSize().y) + 9 );
	m_pBoxImage[4]->Render();
	
	nPosX += cx - m_pBoxImage[5]->GetImgSize().x;
	m_pBoxImage[5]->Move( nPosX - 1, y + m_pBoxImage[2]->GetImgSize().y );
	m_pBoxImage[5]->SetScale(1, (float)( cy - (m_pBoxImage[0]->GetImgSize().y) ) / m_pBoxImage[3]->GetImgSize().y );
	m_pBoxImage[5]->Render();
	
	nPosX = x;
	m_pBoxImage[6]->Move( nPosX , y + cy );
	m_pBoxImage[6]->Render();
	
	nPosX += m_pBoxImage[6]->GetImgSize().x;
	m_pBoxImage[7]->Move( nPosX, y + cy  );
	m_pBoxImage[7]->SetRect( 0, 0, nImageSizeX, m_pBoxImage[7]->GetImgSize().y );
	m_pBoxImage[7]->SetScale( 1, 1 );
	m_pBoxImage[7]->Render();
	
	nPosX += nImageSizeX;
	m_pBoxImage[7]->Move( nPosX, y + cy );
	m_pBoxImage[7]->SetRect( nImageSizeX, 0,  nImageSizeX + 1 , m_pBoxImage[7]->GetImgSize().y );
	m_pBoxImage[7]->SetScale( cx - ( nImageSizeX + m_pBoxImage[6]->GetImgSize().x ) * 2, 1 );
	m_pBoxImage[7]->Render();
	
	nPosX += cx - ( nImageSizeX + m_pBoxImage[6]->GetImgSize().x ) * 2;
	m_pBoxImage[7]->Move( nPosX, y + cy );
	m_pBoxImage[7]->SetRect( m_pBoxImage[7]->GetImgSize().x - nImageSizeX, 0, m_pBoxImage[7]->GetImgSize().x, m_pBoxImage[7]->GetImgSize().y );
	m_pBoxImage[7]->SetScale( 1, 1 );
	m_pBoxImage[7]->Render();
	
	nPosX += nImageSizeX;
	m_pBoxImage[8]->Move( nPosX, y + cy );
	m_pBoxImage[8]->Render();

	if(bRenderClose)
	{
		m_pXclose->Move(x+cx-16,y - 2);
		m_pXclose->Render();
	}
#else
	m_pBoldBoxImage[0]->Move(x,y);
	m_pBoldBoxImage[0]->Render();
	m_pBoldBoxImage[1]->Move(x+19, y);
	m_pBoldBoxImage[1]->SetScale(cx-38, 1);
	m_pBoldBoxImage[1]->Render();
	m_pBoldBoxImage[2]->Move(x+cx-19,y);
	m_pBoldBoxImage[2]->Render();

	m_pBoldBoxImage[3]->Move(x, y+19);
	m_pBoldBoxImage[3]->SetScale(1, cy-38);
	m_pBoldBoxImage[3]->Render();
	m_pBoldBoxImage[4]->Move(x+19, y+19);
	m_pBoldBoxImage[4]->SetScale(cx-38,cy-38);
	m_pBoldBoxImage[4]->Render();
	m_pBoldBoxImage[5]->Move(x+cx-19, y+19);
	m_pBoldBoxImage[5]->SetScale(1, cy-38);
	m_pBoldBoxImage[5]->Render();

	m_pBoldBoxImage[6]->Move(x,y+cy-19);
	m_pBoldBoxImage[6]->Render();
	m_pBoldBoxImage[7]->Move(x+19,y+cy-19);
	m_pBoldBoxImage[7]->SetScale(cx-38, 1);
	m_pBoldBoxImage[7]->Render();
	m_pBoldBoxImage[8]->Move(x+cx-19,y+cy-19);
	m_pBoldBoxImage[8]->Render();
	if(bRenderClose)
	{
		m_pXclose->Move(x+cx-14,y+6);
		m_pXclose->Render();
	}
#endif
// end 2011. 10. 10 by jskim UI�ý��� ����
}

void CINFWindow::RenderItemInfoBox(int x, int y, int cx, int cy)
{
	FLOG( "CINFWindow::RenderItemInfoBox(int x, int y, int cx, int cy)" );
	m_pBoxImage[4]->Move(x, y);
	m_pBoxImage[4]->SetScale(cx,cy);
	m_pBoxImage[4]->Render();
}

void CINFWindow::AddRadioOption(char *strRadio,  int nRadioArrayType)
{
	m_vecRadioString.push_back(strRadio);
	m_nRadioButtonArray = nRadioArrayType;
	g_input.ResetFontBuffer();
}

void CINFWindow::ClearAllMessageString()
{
	for (auto msgbox : m_vecMessageBox)
	{
		int m_nMsgType = msgbox->m_nMsgType;
		
		if (INPUT_MSG_BUTTON || INPUT_COUNT_BUTTON)
		{			
			g_pD3dApp->m_bChatMode = FALSE;
			msgbox->ClearMessageBoxString();			
		}
	}
}

void CINFWindow::ResetMessageString()
{
	for (auto msgbox : m_vecMessageBox)
	{
		int m_nMsgType = msgbox->m_nMsgType;
		
		if (INPUT_MSG_BUTTON || INPUT_COUNT_BUTTON)
		{
			msgbox->ResetMessageString();
			break;
		}
	}
}


void CINFWindow::MessageBoxProgressOption(int nType, DWORD dwData1, DWORD dwData2, char* strName)
{
	//////////////////////////////////////////////////////////////////////////
	// â�ѱ� â���� �ɼ� - 2005-08-12 by ydkim -
	// �ɼ� �߰��� ���� �Ʒ� �κп� �߰� �Ѵ�
	//////////////////////////////////////////////////////////////////////////	
	
	switch(nType)
	{
	case _Q_PARTY_INVITE:
		{
			g_pGameMain->m_pCommunity->GetParty()->PartyRecvInvite(1);
			char buf[256];
			ZERO_MEMORY(buf);
			// 2008-02-26 by bhsohn ���� �Ʒ��� ���� ���� ����
			//wsprintf(buf, STRMSG_C_050812_0002, strName); //"[%s]������ ������ ��Ƽ�ʴ� ��û��"
			char szCharName[SIZE_MAX_ARENA_FULL_NAME];
			util::strncpy(szCharName, strName, SIZE_MAX_ARENA_FULL_NAME);	
			g_pD3dApp->ConevertArenaRenderUserName(g_pD3dApp->GetArenaState(), szCharName);
			wsprintf(buf, STRMSG_C_050812_0002, szCharName); //"[%s]������ ������ ��Ƽ�ʴ� ��û��"

			g_pD3dApp->m_pChat->CreateChatChild(buf,COLOR_HELP);

			g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_050812_0001,COLOR_HELP); // "â����ɼ����� ��ҵǾ����ϴ�."
		}
		break;
	case _Q_TRADE_REQUEST:
		{
			g_pGameMain->m_pTrade->SendTradeReject();
			char buf[256];
			ZERO_MEMORY(buf);
			wsprintf(buf, STRMSG_C_050812_0003, strName); //"[%s]������ ������ �ŷ� ��û��"
			g_pD3dApp->m_pChat->CreateChatChild(buf,COLOR_HELP);

			g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_050812_0001,COLOR_HELP);
		}
		break;
	case _Q_VOIP_OK:
		{		
			char buf[256];
			ZERO_MEMORY(buf);
			wsprintf(buf, STRMSG_C_050812_0004, strName); //"[%s]������ ������ ����ä�� ��û��"
			g_pD3dApp->m_pChat->CreateChatChild(buf,COLOR_HELP);

			g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_050812_0001,COLOR_HELP);
		}
		break;
	case _Q_PK_REQUEST:
		{
			MSG_FC_BATTLE_REJECT_REQUEST_P2P_PK sMsg;
			memset(&sMsg,0x00,sizeof(sMsg));
			char buffer[SIZE_MAX_PACKET];
			int nType = T_FC_BATTLE_REJECT_REQUEST_P2P_PK;
			sMsg.SourceClientIndex = dwData1;
			memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
			memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
			g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));			
			if(g_pGameMain->m_pOtherCharInfo != NULL)
				g_pGameMain->m_pOtherCharInfo->m_bRenderInfo = FALSE;
			char buf[256];
			ZERO_MEMORY(buf);
			wsprintf(buf, STRMSG_C_050812_0005, strName); //"[%s]������ ������ 1:1��� ��û��"
			g_pD3dApp->m_pChat->CreateChatChild(buf,COLOR_HELP);
			
			g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_050812_0001,COLOR_HELP);
		}
		break;
	case _Q_PK_LOSE_REQUEST_OK:
		{
			MSG_FC_BATTLE_REJECT_SURRENDER_P2P_PK sMsg;
			memset(&sMsg,0x00,sizeof(sMsg));
			char buffer[SIZE_MAX_PACKET];
			int nType = T_FC_BATTLE_REJECT_SURRENDER_P2P_PK;
			sMsg.SourceClientIndex = dwData1;
			memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
			memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
			g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
			char buf[256];
			ZERO_MEMORY(buf);
			wsprintf(buf, STRMSG_C_050812_0006, strName); //"[%s]������ ������ �׺� ��û��"
			g_pD3dApp->m_pChat->CreateChatChild(buf,COLOR_HELP);
			
			g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_050812_0001,COLOR_HELP);
		}
		break;
	case _Q_REQUEST_PARTY_BATTLE:
		{
			MSG_FC_REQUEST_REJECT_REQUEST sMsg;
			memset(&sMsg,0x00,sizeof(sMsg));
			char buffer[SIZE_MAX_PACKET];
			int nType = T_FC_REQUEST_REJECT_REQUEST;
			sMsg.SourceClientIndex = dwData1;
			sMsg.RequestType = REQUEST_TYPE_PARTY_BATTLE;
			memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
			memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
			g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
			// ����� �޴� ��� �� ����
			g_pGameMain->m_pCommunity->GetParty()->SetEnablePartyMenu(TRUE);
			
			g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_050812_0007,COLOR_HELP); //"��Ƽ���� ��û�� â����ɼ����� ��ҵǾ����ϴ�."
		}
		break;
	case _Q_REQUEST_GUILD_WAR:
		{
			MSG_FC_REQUEST_REJECT_REQUEST sMsg;
			memset(&sMsg,0x00,sizeof(sMsg));
			sMsg.SourceClientIndex = dwData1;
			sMsg.RequestType = REQUEST_TYPE_GUILD_WAR;
			g_pFieldWinSocket->SendMsg( T_FC_REQUEST_REJECT_REQUEST, (char*)&sMsg, sizeof(sMsg) );
			// ����� �޴� ��� �� ����
			g_pGameMain->m_pCommunity->GetParty()->SetEnablePartyMenu(TRUE);
			
			g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_050812_0008,COLOR_HELP); //"������ ��û�� â����ɼ����� ��ҵǾ����ϴ�."
		}
		break;
	case _Q_JOIN_PARTY_VOIP:
		{
			g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_050812_0009,COLOR_HELP); //"�����ȭ ��û�� â����ɼ����� ��ҵǾ����ϴ�."
		}
		break;
	case _Q_JOIN_GUILD_VOIP:
		{
			g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_050812_0010,COLOR_HELP); //"������ȭ ��û�� â����ɼ����� ��ҵǾ����ϴ�."
		}
		break;
		}
		
		
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			CINFMessageBox::CheckStringMsg()
/// \brief		��Ʈ�� üũ
/// \author		ispark
/// \date		2006-04-17 ~ 2006-04-17
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFMessageBox::CheckStringMsg()
{
	if(m_nMsgType == _Q_GUILD_CREATE)
	{
		int nCount = ReSetRemoveString(SPECIAL_STRING, m_strInputMessage);
		if(nCount > 0)
		{
			// �齺���̽�
			for(int i = 0; i < nCount; i++)
			{
				g_pD3dApp->m_inputkey.KeyMapping(g_pD3dApp->GetHwnd(), 258, 8, 917505);
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			CINFWindow::SearchMsgBox(int nType)
/// \brief		Ÿ������ �޼��� �ڽ� ã��
/// \author		ispark
/// \date		2006-04-17 ~ 2006-04-17
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFWindow::SearchMsgBox(int nType)
{
	vector<CINFMessageBox*>::iterator it = m_vecMessageBox.begin();
	while(it != m_vecMessageBox.end())
	{
		if((*it)->m_nMsgType == nType)
			return TRUE;
		it++;
	}
	
	return FALSE;
}

char* CINFMessageBox::GetMsgString(char* strMsg)
{
	char strTime[1024] = {0,};

	if(m_fLiveTime)
	{
		sprintf(strTime, m_strTimeMessage, (int)(m_fLiveTime) + 1);
		sprintf(strMsg, "%s %s", m_strMessage, strTime);

		return strMsg;
	}
	else
	{
		sprintf(strMsg, "%s", m_strMessage);
		return strMsg;
	}
}
// 2013-04-05 by bhsohn ������ 5�� ��Ȱ �ý��� �߰�
void  CINFMessageBox::GetMsg1String(char* strMsg)
{
	char strTime[1024] = {0,};
	
	if(m_fLiveTime && strlen(m_strTimeMessage1) > 0)
	{
		sprintf(strTime, m_strTimeMessage1, (int)(m_fLiveTime) + 1);
		sprintf(strMsg, "%s", strTime);		
	}
}
void CINFMessageBox::SetTimeMessage1(char* pMsg) 
{
	strncpy(m_strTimeMessage1, pMsg, 256);
}	

///////////////////////////////////////////////////////////////////////////////
/// \fn			����Ŀ ������ ���
/// \brief		
/// \author		// 2007-08-07 by bhsohn ����Ŀ ������ �߰�
/// \date		2007-08-07 ~ 2007-08-07
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFMessageBox::UseSpeakerItem(int nNotOk, char* strInputMessage)
{
	if(0 == nNotOk)
	{
		INIT_MSG_WITH_BUFFER(MSG_FC_ITEM_USE_ITEM, T_FC_ITEM_USE_ITEM, pSMsg, SendBuf);

		pSMsg->ClientIndex = g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.ClientIndex;
		pSMsg->ItemUniqueNumber = m_UniqueNumber;				
		util::strncpy(pSMsg->str256ChatMsg, strInputMessage, SIZE_MAX_STRING_256);
		
		g_pD3dApp->m_pFieldWinSocket->Write(SendBuf, MSG_SIZE(MSG_FC_ITEM_USE_ITEM));	
	}
	g_pD3dApp->m_bChatMode = FALSE;								

	g_pGameMain->m_bChangeMousePoint = FALSE;

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			ȯ�� ���� �׼��� �Է��Ѵ�.
/// \brief		
/// \author		// 2007-09-05 by bhsohn ���� ������
/// \date		2007-09-10 ~ 2007-09-10
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFMessageBox::OnSendRequestExpence(int nCout)
{
	INIT_MSG_WITH_BUFFER(MSG_FC_INFO_EXPEDIENCYFUND_PAYBACK, T_FC_INFO_EXPEDIENCYFUND_PAYBACK, pSMsg, SendBuf);	
	pSMsg->ExpediencyFundPayBackCount = nCout;

	g_pFieldWinSocket->Write(SendBuf, MSG_SIZE(MSG_FC_INFO_EXPEDIENCYFUND_PAYBACK));	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			Ư�� �۾��� ����� ó��
/// \brief		
/// \author		// 2007-10-16 by bhsohn Ư�� �۾��� ����� ó��
/// \date		2007-10-16 ~ 2007-10-16
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFMessageBox::RenderCashMsgBox(int nX, int nY, char* pTxt)
{
	char * pFind = strstr(pTxt, m_strInputMessage);
	if(0 == strcmp(m_strInputMessage, "")
		|| NULL == pFind)
	{
		m_pFontMessage->DrawText(nX, nY, GUI_FONT_COLOR, pTxt, 0L);
		return;
	}

	int nStartGap = pFind - pTxt;
	if(0 < nStartGap)
	{
		char szLString[512] = {0x00,};
		memcpy(szLString, pTxt, nStartGap);
		m_pFontMessage->DrawText(nX, nY, GUI_FONT_COLOR, szLString,0L);
		nX += m_pFontMessage->GetStringSize(szLString).cx;
	}

	// ����ü�� ó���� �� ���.
	m_pFontBold->DrawText(nX, nY, GUI_FONT_COLOR_Y, m_strInputMessage, 0L);
	nX += m_pFontBold->GetStringSize(m_strInputMessage).cx;

	int nRemainCnts = strlen(pTxt) - (nStartGap + strlen(m_strInputMessage));
	if(0 < nRemainCnts)
	{// ����ü�� �߰��̳� �ڿ� �������.

		char szRString[512] = {0x00,};
		memcpy(szRString, &pTxt[nStartGap + strlen(m_strInputMessage)], nRemainCnts);
		m_pFontMessage->DrawText(nX, nY, GUI_FONT_COLOR, szRString,0L);
	}
}

bool CINFMessageBox::EnterMsgbox() const
{
	switch (m_nMsgType)
	{
	case _Q_SHOP_SELL_ITEM:
	case _Q_SHOP_MULTI_SELL_ITEM:
	case _Q_STORE_MULTI_PUT_ITEM:
	case _Q_STORE_MULTI_GET_ITEM:
	case _Q_ITEM_DELETE_NUM:
	case _Q_PARTY_INVITE_USER:
	case _Q_TRADE_ITEM_NUMBER:
	case _Q_SHOP_SELL_ENERGY:
	case _Q_TRADE_INPUT_NAME:
	case _Q_GUILD_CREATE:
	case _Q_GUILD_INVITE:
	case _Q_GUILD_MARK:
	case _Q_BATTLE_NAME:
	case _Q_VOIP_NAME:
	case _Q_STORE_PUT_COUNTABLE_ITEM:
	case _Q_INPUT_AUCTION_PRICE:
	case _Q_STORE_PUSH_ITEM:
	case _Q_PUT_ITEM_SPI:
	case _Q_GET_ITEM_SPI:
	case _Q_LAB_ITEM_NUMBER:
	case _Q_ADD_FRIEND:
	case _Q_ADD_REJECT:
	case _Q_TEX_SET:
	case _Q_DATE_WAR:
	case _Q_STORE_USE:
	case _Q_GREATING_SET:
	case _Q_GET_TEX:
	case _Q_CASHITEM_BUY:
	case _Q_CASHITEM_SHOP_OPEN:
	case _Q_INPUT_SERIAL_NUM:
	case _Q_SUPER_RESTORE:
	case _Q_MEMBER_SUMMON:
	case _Q_MP3_DIRECTORY:
	case _Q_MP3_PLAYLIST_DEL:
	case _Q_QUIT_MESSAGE:
	case _Q_USEITEM_NAME_CHANGE:
	case _Q_UNIT_STOP:
	case _Q_MISSION_START:
	case _Q_SKILL_CALLOFHERO:
	case _Q_UPDATE_SUBLEADER_1:
	case _Q_UPDATE_SUBLEADER_2:
	case _Q_ARENA_PASSWORD:
	case _Q_USEITEM_SPEAKER_MSG:
	case _Q_GIFT_CHARACTER_TEXT:
	case _Q_INFLUENCE_WAR_EXPENCE_OK_MSG:
	case _Q_PARTY_JOIN_PASSWORD:
	case _Q_CHATROOM_INVITE:
	case _Q_CHATROOM_PASSWORD:
	case _Q_GUILD_BATTLE:
	case _Q_PARTY_BATTLE:
	case _Q_JOYSTICK_SETUP:
	case _Q_USEITEM_LEADER_BAN_CHAT:
	case _Q_FRIEND_LIST_INSERT:
	case _Q_CREATE_NICKNAME:
	case _Q_PARTNER_NEW_NAME_CHANGE:
	case _Q_TRADE_REQUEST:
	case _Q_AUTO_KICK:

		return true;

	default:
		
		return false;
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-12-30 by bhsohn ������ ä�� ���� ī�� ��ȹ��
/// \date		2008-12-30 ~ 2008-12-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFMessageBox::UseLeaderBanChatTItem(int nNotOk, char* strInputMessage)
{
	if(0 == nNotOk)
	{
		MSG_FC_ITEM_USE_ITEM sMsg;
		memset(&sMsg,0x00,sizeof(sMsg));
		
		sMsg.ClientIndex = g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.ClientIndex;
		sMsg.ItemUniqueNumber = m_UniqueNumber;	
		strncpy(sMsg.str256ChatMsg, strInputMessage, SIZE_MAX_STRING_256);
		
		g_pFieldWinSocket->SendMsg( T_FC_ITEM_USE_ITEM, (char*)&sMsg, sizeof(sMsg) );

	}
	g_pD3dApp->m_bChatMode = FALSE;								
	
	// 2007.04.24 by bhsohn China IME Working
#ifdef LANGUAGE_CHINA	
	g_pD3dApp->m_inputkey.EnableIMEControl(g_pD3dApp->m_bChatMode);	
#endif
	g_pGameMain->m_bChangeMousePoint = FALSE;

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-12-30 by bhsohn ������ ä�� ���� ī�� ��ȹ��
/// \date		2008-12-30 ~ 2008-12-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFMessageBox::IsPossiblOkCancel()
{
	if(OK_CANCEL_BUTTON || INPUT_MSG_BUTTON || INPUT_COUNT_BUTTON || INPUT_RADIO_BUTTON)
	{
		return TRUE;
	}
	return FALSE;

}