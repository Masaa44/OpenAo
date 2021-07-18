// WeaponItemInfo.cpp: implementation of the CWeaponItemInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AtumApplication.h"
#include "ShuttleChild.h"
#include "WeaponItemInfo.h"
#include "ItemInfo.h"
#include "ItemData.h"
#include "SceneData.h"
//#include "ObjectRender.h"
#include "FieldWinSocket.h"
#include "WeaponMineData.h"
#include "MonsterData.h"
#include "INFGameMain.h"
#include "INFGameMainUnitInfoBar.h"
#include "Chat.h"
#include "Camera.h"
#include "Interface.h"
#include "INFTarget.h"
#include "EnemyData.h"
#include "BackGround.h"
#include "AtumSound.h"
#include "ObjRender.h"
#include "Skill.h"
#include "SkillInfo.h"
#include "StoreData.h"
#include "RangeTime.h"
#include "INFInven.h"
#include "dxutil.h"
#include "PkNormalTimer.h"
#include "TutorialSystem.h"
#include "WSlowData.h"
#include "AtumDatabase.h"
// 2010-06-15 by shcho&hslee ��ý��� - �� ���� ����
#include "PetManager.h"
// end 2010-06-15 by shcho&hslee ��ý��� - �� ���� ����

// 2015-11-2, PanKJ FreeWar
#include "FreeWar.h"

#define OVERHEAT_REPAIR_TIME			10.0f	// 10��
#define PRIMARY_NEAR_DISTANCE_IN_NET	50.0f			// 1�� ���Ⱑ ������ ȭ�� ����� �Ÿ�
#define TOGGLE_WEAPON_CLICK_GAP_TIME		1.5f	// 1.5��
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWeaponItemInfo::CWeaponItemInfo(CItemInfo* pItemInfo, 
								 CParamFactor * pParamFactor, 
								 float fOverHeatTime,	// ���� �ð�
								 BOOL bOverHeat)		// �������̸� TRUE
{
	m_pItemInfo				= pItemInfo;
	m_pCharacterParamFactor = pParamFactor;
	
	m_fOverHeatCheckTime	= fOverHeatTime;
	m_bOverHeat				= bOverHeat;
	m_fReattackCheckTime	= 0;
	m_fPrepareCheckTime		= 0;
	m_fAttackCheckTime		= 0;
	m_nAttackCount			= 0;

	if(IS_PRIMARY_WEAPON(pItemInfo->Kind))
	{
		m_nAttackMode = ATT_TYPE_GENERAL_PRI;
	}
	else if(IS_SECONDARY_WEAPON(pItemInfo->Kind))
	{
		// 2006-04-26 by ispark
		if(g_pShuttleChild && g_pShuttleChild->m_bAttackMode == _GROUND)
		{
	 		m_nAttackMode = ATT_TYPE_GROUND_BOMBING_SEC;
		}
		else if(g_pShuttleChild && g_pShuttleChild->m_bAttackMode == _AIRBOMBING)
		{
	 		m_nAttackMode = ATT_TYPE_AIR_BOMBING_SEC;
		}
		else
		{
			m_nAttackMode = ATT_TYPE_GENERAL_SEC;
		}
	}
	// 2010-06-15 by shcho&hslee ��ý��� - �� ���� ����
	else if(pItemInfo->Kind == ITEMKIND_PET_ITEM)
	{
		m_nAttackMode = ATT_TYPE_PET_GENERAL;
	}
	//end 2010-06-15 by shcho&hslee ��ý��� - �� ���� ����
	else
	{
		ASSERT_NEVER_GET_HERE();
	}
	
	m_dwLastAttackTick		= 0;
	m_pMineData				= NULL;

//	if(IS_PRIMARY_WEAPON(pItemInfo->GetItemInfo()->Kind))
//	{
//		m_nServerSyncShotNum = CAtumSJ::GetTotalPrimaryShotCountPerReattackTime(pItemInfo->GetRealItemInfo(),m_pCharacterParamFactor);
//	}
//	else
//	{
//		m_nServerSyncShotNum = pItemInfo->GetRealItemInfo()->ShotNum + m_pCharacterParamFactor->pfp_SHOTNUM_02;
//	}

	if(pItemInfo->GetItemInfo()->Kind == ITEMKIND_MINE)
	{
		m_pMineData = new MINE_DATA;
		m_pMineData->m_nMaxMineNumber = 
			CAtumSJ::GetCountMineAtATime( m_pItemInfo->GetRealItemInfo(), &g_pShuttleChild->m_paramFactor );
	}
	
	m_bUseToggleWeapon = FALSE;
//	m_fAutoSyncReattackOkTime = 0;



	HpCharge = FALSE;				 //2011-10-06 by jhahn ��Ʈ�� ������ �ý���
	ShieldCharge = FALSE;			 //2011-10-06 by jhahn ��Ʈ�� ������ �ý���
	SpCharge = FALSE;				 //2011-10-06 by jhahn ��Ʈ�� ������ �ý���
}

CWeaponItemInfo::~CWeaponItemInfo()
{
	if(m_pMineData)
	{
		vector<CWeaponMineData *>::iterator it = m_pMineData->m_vecMine.begin();
		while(it != m_pMineData->m_vecMine.end() )
		{
			MSG_FC_ITEM_DELETE_DROP_ITEM sMsg;
			sMsg.ItemFieldIndex = (*it)->m_nFieldItemIndex;
			sMsg.DropPosition = (*it)->m_vPos;
			g_pFieldWinSocket->SendMsg( T_FC_ITEM_DELETE_DROP_ITEM, (char*)&sMsg, sizeof(sMsg) );

			(*it)->m_bUsing = FALSE;
			it = m_pMineData->m_vecMine.erase(it);
			
		}
		util::del(m_pMineData);
	}
}

//void CWeaponItemInfo::SetServerSyncReattackOk(BOOL bOK) 
//{ 
//	if(bOK) 
//	{
//		if(IS_PRIMARY_WEAPON(m_pItemInfo->GetItemInfo()->Kind))
//		{
//			m_nServerSyncShotNum = CAtumSJ::GetTotalPrimaryShotCountPerReattackTime(m_pItemInfo->GetRealItemInfo(),m_pCharacterParamFactor); 
//		}
//		else
//		{
//			m_nServerSyncShotNum = m_pItemInfo->GetRealItemInfo()->ShotNum + m_pCharacterParamFactor->pfp_SHOTNUM_02;
//		}
//#ifndef _DEBUG // Release������ ���� ServerSyncReattack�� �ȿ��� ��� �ڵ����� ����
//		m_fAutoSyncReattackOkTime = CAtumSJ::GetShotCountReattackTime(m_pItemInfo->GetRealItemInfo(),m_pCharacterParamFactor)*2;
//#endif
//	}
//}

void CWeaponItemInfo::TickSecondaryWeapon2(float fElapsedTime, BOOL bUse)
{
	switch(m_pItemInfo->Kind)
	{
	case ITEMKIND_SHIELD:// ����� - ���带 �ڵ����� ä����
	case ITEMKIND_DECOY:// ����� - ��밡 ���� Ÿ������ ���� ���ϵ���
		{
			// 2004-11-15 by jschoi
			// ��Ŭ������ ������� �ʴ� m_fReattackCheckTime������ Ȱ���Ͽ� Ŭ�� ���� �ð��� �����Ѵ�.
			m_fReattackCheckTime += fElapsedTime;					
			if(	bUse && !g_pCamera->m_bIsCamControl &&
				g_pD3dApp->m_dwGameState == _GAME &&
				m_fReattackCheckTime > TOGGLE_WEAPON_CLICK_GAP_TIME )
			{
				UseSecondary();
				m_fReattackCheckTime = 0.0f;
			}
		}
		break;
	case ITEMKIND_DUMMY:// ����� - ��Ʋ �ֺ� ����� ���� ����
	case ITEMKIND_FIXER:// ����� - ����� �ӷ��� �ٿ��ִ� ���� 
		{
			TickNormalWeapon(fElapsedTime, bUse);
		}
		break;
	}
}

void CWeaponItemInfo::TickNormalWeapon(float fElapsedTime, BOOL bUse)
{
	CheckInNet();
	ITEM * pITEM = m_pItemInfo->GetRealItemInfo();
	// over heat
	float fOverHeatTime = CAtumSJ::GetOverheatTime(pITEM,m_pCharacterParamFactor);
	// ������ Ÿ��, ����
	float fReattackTime = CAtumSJ::GetShotCountReattackTime(pITEM,m_pCharacterParamFactor);
#if defined(_WARRIOR_ENABLE_OLD_ANTICHEAT)  || defined(_WARRIOR_ENABLE_NEW_ANTICHEAT)
	//2015-04-01 upgrade for float values and checking for zerk
	CSkill	*			m_pSkill;
	m_pSkill = new CSkill;
	if (!m_pSkill->IsSkillUse(7833050) || !m_pSkill->IsSkillUse(7833051) || !m_pSkill->IsSkillUse(7833052) || !m_pSkill->IsSkillUse(7833053) || !m_pSkill->IsSkillUse(7833054) || !m_pSkill->IsSkillUse(7843051))
	{//if its not berseker skill
		if (fReattackTime < 0.01f) {
			MessageBox(NULL, "Hacking client! \n Closing program. Code: 1", "Ares Anti-Cheat", MB_OK);
			exit(1);
		}
	}
	if (fReattackTime > 9500.0f) {
		MessageBox(NULL, "Hacking client! \n Closing program. Code: 2", "Ares Anti-Cheat", MB_OK);
		exit(1);
	}
#endif
	if( m_bOverHeat == FALSE && IsExistBullet() )
	{
		// �ߵ�, 
		float fPrepareTime = CAtumSJ::GetPrepareTime(pITEM,m_pCharacterParamFactor); 
		if( bUse == TRUE )										// ���� �����
		{
			if( m_fOverHeatCheckTime > 0 )						// ���� ���� �ȵƴ�.
			{
				m_fOverHeatCheckTime -= fElapsedTime;
				if( m_fOverHeatCheckTime < 0 )					// ���� �ƴ�.
				{
					m_fOverHeatCheckTime = 0;
					m_bOverHeat = TRUE; 
					ResetWeaponBodyCondition(WEAPON_BODYCON_RELOAD);
				}
			}
			// 2013-04-19 by bhsohn A��� 1������ ������Ʈ �ȵǴ� ���� ����
			else if( pITEM && IS_PRIMARY_WEAPON(pITEM->Kind) && m_fOverHeatCheckTime <= 0 && !IsOverHeat())						
			{
				// �����ΰ� ���׷� ���ؾ��� ���� �ȵƴ�.
				m_fOverHeatCheckTime = 0;
				m_bOverHeat = TRUE; 
				ResetWeaponBodyCondition(WEAPON_BODYCON_RELOAD);
			}
			// END 2013-04-19 by bhsohn A��� 1������ ������Ʈ �ȵǴ� ���� ����

			if(m_fPrepareCheckTime < fPrepareTime )				// ������ �ߵ����̶��
			{
				m_fPrepareCheckTime += fElapsedTime;
				if( m_fPrepareCheckTime > fPrepareTime )
				{
					m_fPrepareCheckTime = fPrepareTime;			// �ߵ� �Ϸ� m_fPrepareCheckTime == fPrepareTime
				}
			}
		}
		else													// ���� ������� �ƴ�
		{
			if( m_fOverHeatCheckTime < fOverHeatTime )			// ������ ������.
			{
				m_fOverHeatCheckTime += fElapsedTime*(fOverHeatTime/OVERHEAT_REPAIR_TIME);
				if( m_fOverHeatCheckTime > fOverHeatTime )
				{
					m_fOverHeatCheckTime = fOverHeatTime;
				}
			}
			if( m_fPrepareCheckTime > 0 )
			{
				m_fPrepareCheckTime -= fElapsedTime;
				if( m_fPrepareCheckTime < 0 )
				{
					m_fPrepareCheckTime = 0;
				}
			}
		}

		if( m_fReattackCheckTime < fReattackTime ) // �� ���ݰ��� �ð��� ��ٸ��� ���̴�.
		{
			m_fReattackCheckTime += fElapsedTime;
		}

		if( m_fReattackCheckTime > fReattackTime )
		{
			m_fReattackCheckTime = fReattackTime;			// �� ���� �����ϴ�.
		}
		
		// 2004-10-27 by jschoi
		// 1��/2�� ����ó��
		if( bUse == TRUE &&
			m_fReattackCheckTime == fReattackTime)				// ���� ������ΰ� �� ������ �����ϴٸ�
		{
			m_nAttackCount = g_pShuttleChild->GetTotalShotNumPerReattackTime(pITEM, &g_pShuttleChild->m_paramFactor);
		}

		if(m_fAttackCheckTime > 0.0f)
		{
			m_fAttackCheckTime-= fElapsedTime;
		}

		if(	m_fPrepareCheckTime == fPrepareTime &&
			m_nAttackCount > 0 &&
			m_fAttackCheckTime <= 0.0f) 
		{
			if((!g_pCamera->m_bIsCamControl || IS_PRIMARY_WEAPON(pITEM->Kind)))	// ���ֶ��� �ƴϰų� 1���� ���
			{
				if(IS_CLIENT_SET_AUTOMATIC_TIMER(pITEM->OrbitType))		// �����ƽ �߻� Ÿ��
				{
					Use();
					m_nAttackCount--;
					float fTempAutomaticAttackTime, fTempNormalAttackTime;
					fTempAutomaticAttackTime = g_pShuttleChild->GetAutomaticAttackTime(pITEM->OrbitType);
					fTempNormalAttackTime = CAtumSJ::GetShotNumReattackTime( pITEM, &g_pShuttleChild->m_paramFactor );
					// ���� �����ƽ ���� Ÿ�Ӻ��� ���Ѹ�����Ÿ���� �� �۴ٸ� �����ƽ ���� Ÿ�Ӵ�� ���Ѹ�����Ÿ���� m_fAttackCheckTime���� �Ѵ�.
					m_fAttackCheckTime = fTempAutomaticAttackTime < fTempNormalAttackTime ? fTempAutomaticAttackTime : fTempNormalAttackTime;
					//				m_fAttackCheckTime = g_pShuttleChild->GetAutomaticAttackTime(pITEM->OrbitType);
				}
				else													// �����ƽ �߻� Ÿ���� �ƴ�
				{
					if( bUse == TRUE)
					{
						Use();
						m_nAttackCount--;
						m_fAttackCheckTime = CAtumSJ::GetShotNumReattackTime( pITEM, &g_pShuttleChild->m_paramFactor );
					}
				}
			}
			else
			{
				m_nAttackCount = 0;
			}
			// 2008-04-01 by bhsohn ������ ��ũ���� ��忡�� �� ���� ������Ÿ�� DBG�� ��� ����
			const auto& myShuttleInfo = g_pShuttleChild->GetMyShuttleInfo();
			if(g_pInterface->IsScreenShotMode() && 
				(COMPARE_RACE(myShuttleInfo.Race, RACE_OPERATION | RACE_GAMEMASTER | RACE_MONITOR)))
			{
				// ������ Ÿ�� üũ
				DbgOutA("[%.2f] [%.2f] \n", m_fReattackCheckTime, fReattackTime);
			}
			// end 2008-04-01 by bhsohn ������ ��ũ���� ��忡�� �� ���� ������Ÿ�� DBG�� ��� ����
		}
	}
	else // OVER_HEAT or IsExistBullet()
	{
		if( m_fOverHeatCheckTime <= fOverHeatTime ) // 2011-12-16 hsson, 1������ ��� ����� ��� ������Ʈ �Ǵ� ���� ����
		{
			m_fOverHeatCheckTime += fElapsedTime*(fOverHeatTime/OVERHEAT_REPAIR_TIME);
			if( m_fOverHeatCheckTime >= fOverHeatTime ) // 2011-12-16 hsson, 1������ ��� ����� ��� ������Ʈ �Ǵ� ���� ����
			{
				m_fOverHeatCheckTime = fOverHeatTime;
				m_bOverHeat = FALSE; // over heat ����
				if(IsExistBullet())	// �Ѿ��� ������ ���� ������ ���� �ʴ´�.
				{
					ResetWeaponBodyCondition(WEAPON_BODYCON_LOADING);
				}
			}
		}
		if( m_fPrepareCheckTime > 0 )
		{
			m_fPrepareCheckTime -= fElapsedTime;
			if( m_fPrepareCheckTime < 0 )
			{
				m_fPrepareCheckTime = 0;
			}
		}
		if( m_fReattackCheckTime < fReattackTime )
		{
			m_fReattackCheckTime += fElapsedTime;
			if( m_fReattackCheckTime > fReattackTime )
			{
				m_fReattackCheckTime = fReattackTime;
			}
		}
		m_nAttackCount = 0;	
	}
}
// 2010-06-15 by shcho&hslee ��ý��� - �� ���� ����
void CWeaponItemInfo::TickPetWeapon(float fElapsedTime, BOOL bUse)
{
	CheckInNet();
	
	CItemInfo* pAllItem = g_pStoreData->FindItemInInventoryByWindowPos( POS_PET ); 
	if( pAllItem == NULL )
	{
		return;
	}

	tPET_CURRENTINFO * tempCurrentInfo = g_pShuttleChild->GetPetManager()->GetPtr_PetCurrentData( pAllItem->UniqueNumber );
	if( tempCurrentInfo == NULL )
	{
		return;
	}

	tPET_LEVEL_DATA* tempLevelData = g_pDatabase->GetPtr_PetLevelData( tempCurrentInfo->PetIndex,tempCurrentInfo->PetLevel );
	if( tempLevelData == NULL )
	{
		return;
	}

	ITEM * pITEM = g_pDatabase->GetServerItemInfo( tempLevelData->UseWeaponIndex );			 //2011-10-06 by jhahn ��Ʈ�� ������ �ý���
	if( pITEM == NULL )
	{
		return;
	}
	float fReattackTime	= ((float)((float)pITEM->ReAttacktime / 1000) / (float)pITEM->ShotNum);

	

	float fPrepareTime	= pITEM->AttackTime;


// 	//2011-10-06 by jhahn ��Ʈ�� ������ �ý���
// 	for (int i = 0 ; i < SIZE_MAX_PETSOCKET_AUTOSKILL_SLOT ; i++)
// 	{
// 		if(tempCurrentInfo->PetAutoSkill.ItemNum[i] && g_pShuttleChild->GetPetManager()->GetSocketOnOff())
// 		{
// 			CSkillInfo* tempskill =  g_pShuttleChild->m_pSkill->FindItemSkill(tempCurrentInfo->PetAutoSkill.ItemNum[i]);
// 			
// 			if (tempskill &&(g_pShuttleChild->m_myShuttleInfo.CurrentSP >= tempskill->ItemInfo->ReqSP ) &&  (tempskill->GetCheckReattackTime() <= 0.0f ))
// 			{
// 				g_pShuttleChild->m_pSkill->UseSkill(tempskill );
// 			}
// 		}		
// 	}
// 
// 	
// 
// 
// 	CItemInfo* pItemInfo = g_pStoreData->FindItemInInventoryByItemNum( tempCurrentInfo->PetKitHP.ItemNum );
// 	if( pItemInfo != NULL )
// 	{
// 		float temp = g_pShuttleChild->m_myShuttleInfo.HP;
// 		float temp2 = temp / 100;
// 		if ( g_pShuttleChild->m_myShuttleInfo.CurrentHP < (temp2 * tempCurrentInfo->PetKitHP.TriggerValue ))
// 		{
// 			HpCharge = TRUE;
// 		}
// 		
// 		if ( HpCharge )
// 		{
// 			if (g_pShuttleChild->m_myShuttleInfo.CurrentHP >= g_pShuttleChild->m_myShuttleInfo.HP)
// 			{
// 				HpCharge = FALSE;
// 			}
// 			else
// 			{
// 				if (tempLevelData->KitLevelHP >= pItemInfo->ItemInfo->ArrParameterValue[1] && g_pShuttleChild->GetPetManager()->GetSocketOnOff())
// 				{
// 					g_pGameMain->m_pInven->SendUseItem( (ITEM_BASE*)pItemInfo );
// 				}
// 				else
// 					pItemInfo = NULL;
// 
// 				
// 			}
// 			
// 		}
// 	}
// 	pItemInfo = g_pStoreData->FindItemInInventoryByItemNum( tempCurrentInfo->PetKitShield.ItemNum );
// 	if( pItemInfo != NULL  )
// 	{
// 		float temp = g_pShuttleChild->m_myShuttleInfo.DP;
// 		float temp2 = temp / 100;
// 		if ( g_pShuttleChild->m_myShuttleInfo.CurrentDP < (temp2 * tempCurrentInfo->PetKitShield.TriggerValue ))
// 		{
// 			ShieldCharge = TRUE;
// 		}
// 		
// 		if ( ShieldCharge )
// 		{
// 			if (g_pShuttleChild->m_myShuttleInfo.CurrentDP >= g_pShuttleChild->m_myShuttleInfo.DP)
// 			{
// 				ShieldCharge = FALSE;
// 			}
// 			else
// 			{
// 				if (tempLevelData->KitLevelShield >= pItemInfo->ItemInfo->ArrParameterValue[1] && g_pShuttleChild->GetPetManager()->GetSocketOnOff())
// 				{
// 					g_pGameMain->m_pInven->SendUseItem( (ITEM_BASE*)pItemInfo );
// 				}
// 				
// 			}
// 			
// 		}
// 	}
// 	pItemInfo = g_pStoreData->FindItemInInventoryByItemNum( tempCurrentInfo->PetKitSP.ItemNum );
// 	if( pItemInfo != NULL  )
// 	{
// 		float temp = g_pShuttleChild->m_myShuttleInfo.SP;
// 		float temp2 = temp / 100;
// 		if ( g_pShuttleChild->m_myShuttleInfo.CurrentSP < (temp2 * tempCurrentInfo->PetKitSP.TriggerValue ))
// 		{
// 			SpCharge = TRUE;
// 		}
// 
// 		if ( SpCharge  )
// 		{
// 			if (g_pShuttleChild->m_myShuttleInfo.CurrentSP >= g_pShuttleChild->m_myShuttleInfo.SP)
// 			{
// 				SpCharge = FALSE;
// 			}
// 			else
// 			{
// 				if (tempLevelData->KitLevelSP  >= pItemInfo->ItemInfo->ArrParameterValue[1] && g_pShuttleChild->GetPetManager()->GetSocketOnOff())
// 				{
// 					g_pGameMain->m_pInven->SendUseItem( (ITEM_BASE*)pItemInfo );
// 				}
// 				
// 			}		
// 		}
// 	}		
// 	//end 2011-10-06 by jhahn ��Ʈ�� ������ �ý���
	

 	if( bUse == TRUE )
 	{
 		if( m_fReattackCheckTime < fReattackTime ) // �� ���ݰ��� �ð��� ��ٸ��� ���̴�.
 		{
 			m_fReattackCheckTime += fElapsedTime;
 		}
 		if( m_fReattackCheckTime > fReattackTime )
 		{
 			m_fReattackCheckTime = fReattackTime;			// �� ���� �����ϴ�.			
 		}

		if(m_fReattackCheckTime == fReattackTime)				// ���� ������ΰ� �� ������ �����ϴٸ�
		{
			m_nAttackCount = pITEM->ShotNum;
		}
 		
		if(m_fAttackCheckTime > 0.0f)
 		{
			m_fAttackCheckTime-= fElapsedTime;
 		}
 	
 		if(	m_nAttackCount > 0 &&
 			m_fAttackCheckTime <= 0.0f) 
 		{
			if( (!g_pCamera->m_bIsCamControl ) )// ���ֶ��� �ƴϰų� 1���� ���			
 			{
				Use();
				m_nAttackCount--;
				m_fAttackCheckTime = fReattackTime;
 			}
 			else
 			{
 				m_nAttackCount = 0;
 			}

 			// 2008-04-01 by bhsohn ������ ��ũ���� ��忡�� �� ���� ������Ÿ�� DBG�� ��� ����
			const auto& myShuttleInfo = g_pShuttleChild->GetMyShuttleInfo();
 			if(	g_pInterface->IsScreenShotMode() && 
				(COMPARE_RACE(myShuttleInfo.Race, RACE_OPERATION | RACE_GAMEMASTER | RACE_MONITOR)))
 			{
 			// ������ Ÿ�� üũ
	 			DbgOutA("[%.2f] [%.2f] \n", m_fReattackCheckTime, fReattackTime);
 			}
 			// end 2008-04-01 by bhsohn ������ ��ũ���� ��忡�� �� ���� ������Ÿ�� DBG�� ��� ����
 		}
 	}
 	else
 	{
 
 	}
}
// end 2010-06-15 by shcho&hslee ��ý��� - �� ���� ����

///////////////////////////////////////////////////////////////////////////////
/// \fn			CWeaponItemInfo::Tick(float fElapsedTime, BOOL bUse)
/// \brief		����, ������Ÿ��, �ߵ��ð�, �����ð� üũ
/// \author		dhkwon
/// \date		2004-07-20 ~ 2004-07-20
/// \warning	
///
/// \param		bUse : ������ ������(1��:��Ŭ��, 2��:��Ŭ��,'E')
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CWeaponItemInfo::Tick(float fElapsedTime, BOOL bUse)
{
	if(IS_SECONDARY_WEAPON_2(m_pItemInfo->Kind))
	{
		TickSecondaryWeapon2( fElapsedTime, bUse );
	}
	// 2010-06-15 by shcho&hslee ��ý��� - �� ���� ó��
	else if(m_pItemInfo->Kind == ITEMKIND_PET_ITEM)
	{
		TickPetWeapon( fElapsedTime, bUse );
	}
	// end 2010-06-15 by shcho&hslee ��ý��� - �� ���� ó��
	else
	{
		TickNormalWeapon( fElapsedTime, bUse );
	}
}

BOOL CWeaponItemInfo::IsExistBullet()
{
	if(IS_PRIMARY_WEAPON_2(m_pItemInfo->Kind))
	{
		if(g_pShuttleChild->m_myShuttleInfo.CurrentEP > 0)
		{
			return TRUE;
		}
	}
	else if(m_pItemInfo->CurrentCount > 0)
	{
		return TRUE;
	}
	return FALSE;
}

void CWeaponItemInfo::Use() // ���⸦ ����Ѵ�.
{
	// �ѹ߾�(�׷��Ȼ�ι߷� ����)�������·θ� �߻�ȴ�.-�ٹ߷� �ѹ��� ��°� ����ؾ���
	m_dwLastAttackTick = timeGetTime();

	// 2006-11-28 by dgwoo ���彺ų�� �ߵ����϶� ������ �ϸ� �ڵ����� Ǯ����.
	if(g_pShuttleChild->GetUnitAlphaState())
		g_pShuttleChild->m_pSkill->ReleseSkill(DES_SKILL_CAMOUFLAGE);
//2011-10-06 by jhahn ��Ʈ�� ������ �ý���
	CItemInfo* pAllItem = g_pStoreData->FindItemInInventoryByWindowPos( POS_PET ); 
	if (pAllItem)
	{
		tPET_CURRENTINFO * tempCurrentInfo = g_pShuttleChild->GetPetManager()->GetPtr_PetCurrentData( pAllItem->UniqueNumber );
	}
//end 2011-10-06 by jhahn ��Ʈ�� ������ �ý���	

	

	if(IS_PRIMARY_WEAPON(m_pItemInfo->Kind))
	{
		if( g_pD3dApp->m_dwGameState == _GAME &&
			g_pGameMain->m_bMenuLock == FALSE&&	// �޴�����Ʈ ���� �Ѿ� �ȳ���
			IsMousePosClientArea())
		{
			// 2005-04-08 by jschoi - Tutorial
			// 2005-10-06 by ispark - Tutorial
			// 2006-09-11 by ispark - Tutorial
			if(g_pTutorial->IsTutorialMode() == FALSE || 
				(g_pTutorial->IsTutorialMode() == TRUE && g_pTutorial->GetLesson() >= L7 && g_pTutorial->GetLesson() != L8))
			{
				if(g_pTutorial->GetLesson() == L7)
				{
					g_pTutorial->m_Lesson7State.bFire = TRUE;
				}

				
				// 2009. 09. 21 by ckPark ���Ǵ�Ƽ �ʵ� ���� ��ų ����

				// 1�� ħ���� �Ѿ� �߻� ����
				if( g_pShuttleChild->m_pSkill->IsExistDesParamSKill( DES_SKILL_MON_SILENCE_PRIMARY ) )
				{
					m_fReattackCheckTime = 0;
					return;
				}

				// end 2009. 09. 21 by ckPark ���Ǵ�Ƽ �ʵ� ���� ��ų ����


				UsePrimary();
				m_fReattackCheckTime = 0;
			}
		}
	}
	else if(IS_SECONDARY_WEAPON(m_pItemInfo->Kind))
	{
		if( g_pD3dApp->m_dwGameState == _GAME &&
			g_pCamera->m_bIsCamControl == FALSE )	// ī�޶� ���۽� �Ѿ� �ȳ���
		{
			// 2005-04-08 by jschoi - Tutorial
			// 2005-10-06 by ispark - Tutorial
			// 2006-09-11 by ispark - Tutorial
			if(g_pTutorial->IsTutorialMode() == FALSE ||
				(g_pTutorial->IsTutorialMode() == TRUE && g_pTutorial->GetLesson() >= L8 && g_pTutorial->GetLesson() != L7))
			{
				if(g_pTutorial->GetLesson() == L8)
				{
					g_pTutorial->m_Lesson8State.nCount++;
				}


				// 2009. 09. 21 by ckPark ���Ǵ�Ƽ �ʵ� ���� ��ų ����

				// 2�� ħ���� �̻��� �߻� ����
				if( g_pShuttleChild->m_pSkill->IsExistDesParamSKill( DES_SKILL_MON_SILENCE_SECOND ) )
				{
					m_fReattackCheckTime = 0;
					return;
				}

				// end 2009. 09. 21 by ckPark ���Ǵ�Ƽ �ʵ� ���� ��ų ����


				UseSecondary();
				m_fReattackCheckTime = 0;
			}
		}
	} 
	// 2010-06-15 by shcho&hslee ��ý��� - �� ���� ����
	else if(ITEMKIND_PET_ITEM == m_pItemInfo->Kind)
	{
		if( g_pD3dApp->m_dwGameState == _GAME &&
			g_pGameMain->m_bMenuLock == FALSE&&	// �޴�����Ʈ ���� �Ѿ� �ȳ���
			IsMousePosClientArea())
		{
			UsePetAttack();
		}
	}
	// end 2010-06-15 by shcho&hslee ��ý��� - �� ���� ����
}


void CWeaponItemInfo::UsePrimary()
{
	// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
	//if( m_vecTargetIndex.empty())
	if( m_vecTargetIndexData.empty())
	// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
	{
		SendBattleAttackPrimary(0,0,D3DXVECTOR3(0,0,0));
	}
	else
	{
		// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
// 		vector<int>::iterator it = m_vecTargetIndex.begin();
// 		while(it != m_vecTargetIndex.end())
 		vector<TARGET_DATA>::iterator it = m_vecTargetIndexData.begin();
 		while(it != m_vecTargetIndexData.end())
		// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
		{
			// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
			//CUnitData* pTarget = g_pScene->FindUnitDataByClientIndex( *it);
			CUnitData* pTarget = g_pScene->FindUnitDataByClientIndex( (*it).nTargetIndex );
			// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
			// 2005-08-17 by ispark
			// 1������ ��Ÿ��� �ȵŸ� Ÿ���� ������ �ʴ´�.
//			float fPrimaryRange = g_pShuttleChild->m_pRadarItemInfo->ItemInfo->AbilityMin;
			float fPrimaryRange = g_pShuttleChild->m_pRadarItemInfo?CAtumSJ::GetPrimaryRadarRange(g_pShuttleChild->m_pRadarItemInfo->ItemInfo, m_pCharacterParamFactor):0;
			float fDistance = NULL;
			if (pTarget)
				fDistance = D3DXVec3Length(&(g_pShuttleChild->m_vPos - pTarget->m_vPos));
			
//			if( pTarget && pTarget == g_pShuttleChild->m_pTarget && fPrimaryRange >= fDistance)
			if( pTarget && pTarget == g_pShuttleChild->m_pOrderTarget && fPrimaryRange >= fDistance)		// 2006-01-19 by ispark
			{
				if( pTarget->m_dwPartType != _ENEMY ||									// 1. Ÿ���� ENEMY�� �ƴϰų�
					pTarget->IsPkAttackEnable()		||									// 2. ���� ������ �ƴϰų�
//					(g_pShuttleChild->m_pPkNormalTimer->IsPkEnableNormalOrderTarget() &&	// 3. Delay Time �� ���ų�
					// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
					//(g_pShuttleChild->IsEnemyPKAttackTime(*it) &&		// 2005-11-03 by ispark	  Delay Time �� ����
					//g_pShuttleChild->IsEnemyPKTarget(*it)))
					(g_pShuttleChild->IsEnemyPKAttackTime((*it).nTargetIndex) &&		// 2005-11-03 by ispark	  Delay Time �� ����
					g_pShuttleChild->IsEnemyPKTarget((*it).nTargetIndex)))
					// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
				{																		// ���� ������ ������ �ϳ��� �����ϸ� ���� ����
					CItemData *pItem = g_pScene->FindFieldItemByPartTypeAndParent( _DUMMY, (CAtumNode*)pTarget );
					if(pItem)
					{
						// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
						//SendBattleAttackPrimary(*it, pItem->m_nItemIndex, pItem->m_vPos);
						SendBattleAttackPrimary((*it).nTargetIndex, pItem->m_nItemIndex, pItem->m_vPos, (*it).nTargetMultiIndex);
						// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
					}
					else
					{
						// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
						SendBattleAttackPrimary((*it).nTargetIndex, 0, pTarget->m_vPos, (*it).nTargetMultiIndex);
						// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
					}
				}
				else
				{
					SendBattleAttackPrimary(0,0,D3DXVECTOR3(0,0,0));	// �� ������ ���ǿ� ��� ���� ������ ����� �߻�
				}
			}
			else
			{
				SendBattleAttackPrimary(0,0,D3DXVECTOR3(0,0,0));
			}
			it++;
		}
	}
}

// 2010-06-15 by shcho&hslee ��ý��� - �� ���� ����
void CWeaponItemInfo::UsePetAttack()
{
	// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
	//if( m_vecTargetIndex.empty())
	if( m_vecTargetIndexData.empty())
	// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
	{
		SendBattleAttackPet(0,0,D3DXVECTOR3(0,0,0));
	}
	else
	{
		// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
// 		vector<int>::iterator it = m_vecTargetIndex.begin();
// 		while(it != m_vecTargetIndex.end())
 		vector<TARGET_DATA>::iterator it = m_vecTargetIndexData.begin();
 		while(it != m_vecTargetIndexData.end())
		// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
		{
			// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
			//CUnitData* pTarget = g_pScene->FindUnitDataByClientIndex( (*it) );
			CUnitData* pTarget = g_pScene->FindUnitDataByClientIndex( (*it).nTargetIndex );
			// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���

			//float fPrimaryRange = pITEM->Range; // 1�� ����Ÿ��� ������� �Ѵ�.
			float fPrimaryRange = g_pShuttleChild->m_pRadarItemInfo?CAtumSJ::GetPrimaryRadarRange(g_pShuttleChild->m_pRadarItemInfo->ItemInfo, m_pCharacterParamFactor):0;
			float fDistance = NULL;
			if (pTarget)			
				fDistance = D3DXVec3Length(&(g_pShuttleChild->m_vPos - pTarget->m_vPos));
			
			if( pTarget && pTarget == g_pShuttleChild->m_pOrderTarget && fPrimaryRange >= fDistance)		// 2006-01-19 by ispark
			{
				if( pTarget->m_dwPartType != _ENEMY ||									// 1. Ÿ���� ENEMY�� �ƴϰų�
					pTarget->IsPkAttackEnable()		||									// 2. ���� ������ �ƴϰų�
					// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
// 					(g_pShuttleChild->IsEnemyPKAttackTime(*it) &&
// 					g_pShuttleChild->IsEnemyPKTarget(*it)))
 					(g_pShuttleChild->IsEnemyPKAttackTime((*it).nTargetIndex) &&
 					g_pShuttleChild->IsEnemyPKTarget((*it).nTargetIndex)))
					// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
				{																		// ���� ������ ������ �ϳ��� �����ϸ� ���� ����
					CItemData *pItem = g_pScene->FindFieldItemByPartTypeAndParent( _DUMMY, (CAtumNode*)pTarget );
					if(pItem)
					{
						// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
						//SendBattleAttackPet(*it, pItem->m_nItemIndex, pItem->m_vPos);
						SendBattleAttackPet((*it).nTargetIndex, pItem->m_nItemIndex, pItem->m_vPos, (*it).nTargetMultiIndex);
						// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
					}
					else
					{
						// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
						//SendBattleAttackPet(*it, 0, pTarget->m_vPos);
						SendBattleAttackPet((*it).nTargetIndex, 0, pTarget->m_vPos, (*it).nTargetMultiIndex);
						// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
					}
				}
				else
				{
					SendBattleAttackPet(0,0,D3DXVECTOR3(0,0,0));	// �� ������ ���ǿ� ��� ���� ������ ����� �߻�
				}
			}
			else
			{
				SendBattleAttackPet(0,0,D3DXVECTOR3(0,0,0));
			}
			it++;
		}
	}
}
// end 2010-06-15 by shcho&hslee ��ý��� - �� ���� ����

///////////////////////////////////////////////////////////////////////////////
/// \fn			CWeaponItemInfo::SendBattleAttackPrimary(int nTargetIndex, int nItemIndex, D3DXVECTOR3 vPos)
/// \brief		1. nTagetIndex�� �ִ°�� Ÿ�� ����
///				2. nItemIndex�� �ִ°�� ����� Ÿ�� ����
///				3. nTargetIndex�� nItemIndex�� �Ѵ� ������ Ÿ���� �������� ����
///				4. �Ѵ� ���� ��� 0,0 �ΰ�� Ÿ���� ����
/// \author		dhkwon
/// \date		2004-09-03 ~ 2004-09-03
/// \warning				
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
// void CWeaponItemInfo::SendBattleAttackPrimary(int nTargetIndex, 
// 											  int nItemIndex, 
// 											  D3DXVECTOR3 vTargetPos)
void CWeaponItemInfo::SendBattleAttackPrimary(int nTargetIndex, 
											  int nItemIndex, 
											  D3DXVECTOR3 vTargetPos,
											  int nMultiIndex)
// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
{
	D3DXVECTOR3 vShuttlePos = g_pShuttleChild->m_vPos;
	D3DXVECTOR3 vShuttleUp = g_pShuttleChild->m_vUp;
	D3DXVECTOR3 vTargetVel;
	D3DXVECTOR3 vTargetPosObject,vTargetPosGround;

	if(nTargetIndex == 0 && nItemIndex == 0)
	{	// Ÿ���� ���� ���
		if(m_nAttackMode == ATT_TYPE_SEIGE_PRI)
		{
			vTargetVel = g_pShuttleChild->m_vWeaponVel;
		}
		else
		{
			vTargetVel = g_pShuttleChild->m_vVel;
//			if(IS_DT(g_pShuttleChild->m_myShuttleInfo.UnitKind))
//			{
//				vTargetVel = g_pShuttleChild->m_vMouseDir;
//			}
//			else
//			{
//				vTargetVel = g_pShuttleChild->m_vVel;
//			}
		}
		// 2006-12-01 by ispark, �ǹ� ���� Ÿ�� ��ġ�� 1000 -> 3000 ���� ����
		// �������� �� �񱳸� ���ؼ� ���� ũ�� �ش�.
		vTargetPos = vShuttlePos+3000.0f*vTargetVel;
	}
	else
	{	// Ÿ���� �ִ� ���
		D3DXVec3Normalize(&vTargetVel,&(vTargetPos - vShuttlePos));
	}

	
	CUnitData* pTarget = g_pScene->FindUnitDataByClientIndex( nTargetIndex );
	CMonsterData* pMonster = NULL;
	if(pTarget && pTarget->m_dwPartType == _MONSTER)
	{
		pMonster = (CMonsterData*)pTarget;
	}

	// �ʱⰪ ����
	vTargetPosObject = vTargetPos;
	vTargetPosGround = vTargetPos;

	D3DXMATRIX mat;
	D3DXMatrixLookAtLH(&mat,&vShuttlePos,&(vShuttlePos+vTargetVel),&vShuttleUp);	

	float fDistance = D3DXVec3Length(&(vShuttlePos - vTargetPos));
	float fMovingDistance = MAX_WEAPON_SPEED * g_pD3dApp->GetElapsedTime();
//	float fCheckDistance = g_pScene->m_pObjectRender->CheckCollMeshRangeObject(mat,vShuttlePos,fMovingDistance,pMonster).fDist;
	float fCheckDistance = g_pScene->m_pObjectRender->CheckCollMeshRangeObject(mat,vShuttlePos,fDistance,pMonster).fDist;

	// ������Ʈ�� �浹�˻�
	if(fDistance > fCheckDistance)
	{
		vTargetPosObject = vShuttlePos+fCheckDistance*vTargetVel;
		nTargetIndex = 0;
		nItemIndex = 0;
	}

	// 2006-06-02 by ispark
	// ������ �浹�˻�
	if(IsTileMapRenderEnable(g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex))
	{
		float fTempDistance = 0.0f;
		D3DXVECTOR3 vTempPos;
		while (fTempDistance < fDistance)	// ���� �� ���� �浹 �˻�
		{
			vTempPos = vShuttlePos + vTargetVel * fTempDistance;
			if(g_pGround->CheckHeightMap(vTempPos) > vTempPos.y)
			{	// ���� �� ���� �浹 �ߴ�.
 				vTargetPosGround = vTempPos;
				nTargetIndex = 0;	
				nItemIndex = 0;
				break;
			}
			fTempDistance += TILE_SIZE;
		}
	}

	if(D3DXVec3Length(&(vTargetPosObject - vShuttlePos)) > D3DXVec3Length(&(vTargetPosGround - vShuttlePos))) 
	{ // ������ ���� �浹�Ѵ�.
		vTargetPos = vTargetPosGround;
	}
	else
	{ // ������Ʈ�� ���� �浹�Ѵ�.
		vTargetPos = vTargetPosObject;
	}

	// ��¡���� üũ�ϰ� ������� ��¡�� ��ų�ѹ��� ���Ѵ�.
	UINT nSkillNum = g_pShuttleChild->m_pSkill->GetChargingShotTypeSkillNum();
	if(nSkillNum != 0) // ��¡������ ������Ÿ���� 0���� ���� ���簡 �ȵǰ� �Ѵ�.
	{
		m_fReattackCheckTime = 0;
	}
	
	MEX_TARGET_INFO target;
	target.TargetIndex = nTargetIndex;
	target.TargetItemFieldIndex = nItemIndex;
	target.TargetPosition = vTargetPos;
	// 2011. 09. 28 by jskim �� Ÿ�� �ý��� ���� ����( �ɽ��� ���� )
	// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
// 	//if(pTarget)
// 	{
// 		target.MultiTargetIndex = ((CMonsterData*)pTarget)->m_nMultiIndex;
// 	}
	// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
	if(pTarget &&
		pTarget->m_dwPartType == _MONSTER )
	{
		target.MultiTargetIndex = ((CMonsterData*)pTarget)->m_nMultiIndex;
	}	
	else
	{
		target.MultiTargetIndex = 0;
	}
	// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
	
	// end 2011. 09. 28 by jskim �� Ÿ�� �ý��� ���� ����( �ɽ��� ���� )
	
	// 2004-10-26 by jschoi
	// 1�� ���� �߻� ���� ����
	// 1�� ������ ��� �̰����� �Ѿ��� �����ϰ� ������ ���������� ������.
	g_pShuttleChild->m_PrimaryAttack.AttackData.SkillNum = nSkillNum;
	g_pShuttleChild->m_PrimaryAttack.AttackData.AttackType = m_nAttackMode;
	g_pShuttleChild->m_PrimaryAttack.AttackData.TargetInfo = target;
	g_pShuttleChild->m_PrimaryAttack.AttackData.FirePosition = D3DXVECTOR3(0,0,0);
	// 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����
	//g_pShuttleChild->CreateWeapon( g_pShuttleChild->m_PrimaryAttack,m_pItemInfo->GetRealItemInfo());
	// 2010. 05. 25 by jskim ���� ���� ī�带 ���� �Ѿ� ����Ʈ ����ǵ��� ����
	ITEM* pEffectItem = g_pDatabase->GetServerItemInfo(	GetItemGeneral()->ColorCode );
	//end 2010. 05. 25 by jskim ���� ���� ī�带 ���� �Ѿ� ����Ʈ ����ǵ��� ����
	g_pShuttleChild->CreateWeapon( g_pShuttleChild->m_PrimaryAttack,m_pItemInfo->GetRealItemInfo(), pEffectItem, _MY_CHARACTER_PRIORITY);
	//end 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����
	
	SendBattleAttack(target, nSkillNum ,D3DXVECTOR3(0,0,0));

	// 2006-12-06 by ispark, ����
	g_pShuttleChild->m_pSkill->CheckChargingShotSkill();
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			CWeaponItemInfo::SendBattleAttackSecondary(int nTargetIndex, int nItemIndex, D3DXVECTOR3 vTargetPos , D3DXVECTOR3 vFirePos)
/// \brief		1. nTagetIndex�� �ִ°�� Ÿ�� ����
///				2. nItemIndex�� �ִ°�� ����� Ÿ�� ����
///				3. nTargetIndex�� nItemIndex�� �Ѵ� ������ Ÿ���� �������� ����
///				4. �Ѵ� ���� ��� 0,0 �ΰ�� Ÿ���� ����
/// \author		dhkwon
/// \date		2004-09-03 ~ 2004-09-03
/// \warning				
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
// void CWeaponItemInfo::SendBattleAttackSecondary(int nTargetIndex,
// 												int nItemIndex, 
// 												D3DXVECTOR3 vTargetPos,
// 												D3DXVECTOR3 vFirePos)
void CWeaponItemInfo::SendBattleAttackSecondary(int nTargetIndex,
												int nItemIndex, 
												D3DXVECTOR3 vTargetPos,
												D3DXVECTOR3 vFirePos,
												int nMultiIndex)

// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���

{
	int nSkillNum;
	if(m_nAttackMode == ATT_TYPE_GROUND_BOMBING_SEC ||
		m_nAttackMode == ATT_TYPE_AIR_BOMBING_SEC)
	{ // ���� ���� ��� 
		CSkillInfo* pSkillInfo = g_pShuttleChild->m_pSkill->GetSecondarySkill();
		if(pSkillInfo)
		{
			nSkillNum = pSkillInfo->ItemNum;
		}

		if(m_nAttackMode == ATT_TYPE_GROUND_BOMBING_SEC)
		{
			float fTargetRadius = D3DXVec3Length(&(g_pShuttleChild->m_vPos - g_pShuttleChild->GetGroundTargetPos()))/GetRealItemInfo()->Range * 100.0f;
			vTargetPos.x = g_pShuttleChild->GetGroundTargetPos().x + Random(fTargetRadius,-fTargetRadius); // ���⿡ ���� ���� �����Ѵ�.
			vTargetPos.y = g_pShuttleChild->GetGroundTargetPos().y;
			vTargetPos.z = g_pShuttleChild->GetGroundTargetPos().z + Random(fTargetRadius,-fTargetRadius);
		}
		else if(m_nAttackMode == ATT_TYPE_AIR_BOMBING_SEC)
		{
			float fTargetRadius = 50.0f;
			vTargetPos.x = g_pShuttleChild->GetGroundTargetPos().x + Random(fTargetRadius,-fTargetRadius); // ���⿡ ���� ���� �����Ѵ�.
			vTargetPos.y = g_pShuttleChild->GetGroundTargetPos().y + Random(fTargetRadius,-fTargetRadius);
		    vTargetPos.z = g_pShuttleChild->GetGroundTargetPos().z + Random(fTargetRadius,-fTargetRadius);
		}
		nTargetIndex = 0;
	}
	else 
	{ // �Ϲ� 2�� ����
		if(nTargetIndex == 0)
		{
			vTargetPos = g_pShuttleChild->m_vPos + 1000.0f*g_pShuttleChild->m_vVel;
		}
		else
		{
			vTargetPos = vTargetPos;
		}
		nSkillNum = 0;
	}

	MEX_TARGET_INFO target;
	target.TargetIndex = nTargetIndex;
	target.TargetItemFieldIndex = nItemIndex;
	target.TargetPosition = vTargetPos;
	// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
	target.MultiTargetIndex = nMultiIndex;
	// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
	SendBattleAttack(target, nSkillNum, vFirePos);
}
// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
// 2010-06-15 by shcho&hslee ��ý��� - �� ���� ����
//void CWeaponItemInfo::SendBattleAttackPet(int nTargetIndex, int nItemIndex, D3DXVECTOR3 vTargetPos)
void CWeaponItemInfo::SendBattleAttackPet(int nTargetIndex, int nItemIndex, D3DXVECTOR3 vTargetPos, int nMultiIndex)
// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
{
	D3DXVECTOR3 vShuttlePos = g_pShuttleChild->m_vPos;
	D3DXVECTOR3 vShuttleUp = g_pShuttleChild->m_vUp;
	D3DXVECTOR3 vTargetVel;
	D3DXVECTOR3 vTargetPosObject,vTargetPosGround;

	if(nTargetIndex == 0 && nItemIndex == 0)
	{	// Ÿ���� ���� ���
		vTargetVel = g_pShuttleChild->m_vVel;
		vTargetPos = vShuttlePos+3000.0f*vTargetVel;
		//m_nAttackMode = ATT_TYPE_NONE;
	}
	else
	{	// Ÿ���� �ִ� ���
		D3DXVec3Normalize(&vTargetVel,&(vTargetPos - vShuttlePos));
	}

	CUnitData* pTarget = g_pScene->FindUnitDataByClientIndex( nTargetIndex );
	CMonsterData* pMonster = NULL;
	if(pTarget && pTarget->m_dwPartType == _MONSTER)
	{
		pMonster = (CMonsterData*)pTarget;
	}

	// �ʱⰪ ����
	vTargetPosObject = vTargetPos;
	vTargetPosGround = vTargetPos;

	D3DXMATRIX mat;
	D3DXMatrixLookAtLH(&mat,&vShuttlePos,&(vShuttlePos+vTargetVel),&vShuttleUp);	

	float fDistance = D3DXVec3Length(&(vShuttlePos - vTargetPos));
	float fMovingDistance = MAX_WEAPON_SPEED * g_pD3dApp->GetElapsedTime();
	float fCheckDistance = g_pScene->m_pObjectRender->CheckCollMeshRangeObject(mat,vShuttlePos,fDistance,pMonster).fDist;

	// ������Ʈ�� �浹�˻�
	if(fDistance > fCheckDistance)
	{
		vTargetPosObject = vShuttlePos+fCheckDistance*vTargetVel;
		nTargetIndex = 0;
		nItemIndex = 0;
	}

	// 2006-06-02 by ispark
	// ������ �浹�˻�
	if(IsTileMapRenderEnable(g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex))
	{
		float fTempDistance = 0.0f;
		D3DXVECTOR3 vTempPos;
		while (fTempDistance < fDistance)	// ���� �� ���� �浹 �˻�
		{
			vTempPos = vShuttlePos + vTargetVel * fTempDistance;
			if(g_pGround->CheckHeightMap(vTempPos) > vTempPos.y)
			{	// ���� �� ���� �浹 �ߴ�.
 				vTargetPosGround = vTempPos;
				nTargetIndex = 0;	
				nItemIndex = 0;
				break;
			}
			fTempDistance += TILE_SIZE;
		}
	}

	if(D3DXVec3Length(&(vTargetPosObject - vShuttlePos)) > D3DXVec3Length(&(vTargetPosGround - vShuttlePos))) 
	{ // ������ ���� �浹�Ѵ�.
		vTargetPos = vTargetPosGround;
	}
	else
	{ // ������Ʈ�� ���� �浹�Ѵ�.
		vTargetPos = vTargetPosObject;
	}

	// ��¡���� üũ�ϰ� ������� ��¡�� ��ų�ѹ��� ���Ѵ�.
	UINT nSkillNum = g_pShuttleChild->m_pSkill->GetChargingShotTypeSkillNum();
	if(nSkillNum != 0) // ��¡������ ������Ÿ���� 0���� ���� ���簡 �ȵǰ� �Ѵ�.
	{
		m_fReattackCheckTime = 0;
	}
	
	MEX_TARGET_INFO target;
	target.TargetIndex = nTargetIndex;
	target.TargetItemFieldIndex = nItemIndex;
	target.TargetPosition = vTargetPos;	
	// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
	target.MultiTargetIndex = nMultiIndex;
	// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
	
 	g_pShuttleChild->m_PetAttack.AttackData.SkillNum = nSkillNum;
 	g_pShuttleChild->m_PetAttack.AttackData.AttackType = m_nAttackMode;
 	g_pShuttleChild->m_PetAttack.AttackData.TargetInfo = target;
 	g_pShuttleChild->m_PetAttack.AttackData.FirePosition = D3DXVECTOR3(0,0,0);

	CItemInfo* pAllItem = g_pStoreData->FindItemInInventoryByWindowPos( POS_PET ); 

	if( pAllItem == NULL )
	{
		return;
	}

	tPET_CURRENTINFO * tempCurrentInfo = g_pShuttleChild->GetPetManager()->GetPtr_PetCurrentData( pAllItem->UniqueNumber );
	if( tempCurrentInfo == NULL )
	{
		return;
	}

	tPET_LEVEL_DATA* tempLevelData = g_pDatabase->GetPtr_PetLevelData( tempCurrentInfo->PetIndex,tempCurrentInfo->PetLevel );
	if( tempLevelData == NULL )
	{
		return;
	}

	ITEM * pITEM = g_pDatabase->GetServerItemInfo( tempLevelData->UseWeaponIndex );				 //2011-10-06 by jhahn ��Ʈ�� ������ �ý���
	if( pITEM == NULL )
	{
		return;
	}

	ATTACK_DATA tempAtk = g_pShuttleChild->m_PetAttack;

	g_pShuttleChild->CreateWeapon(tempAtk, pITEM);

	SendBattleAttack(target, nSkillNum ,D3DXVECTOR3(0,0,0));

	// 2006-12-06 by ispark, ����
	g_pShuttleChild->m_pSkill->CheckChargingShotSkill();
}
// end 2010-06-15 by shcho&hslee ��ý��� - �� ���� ����
/*
void CWeaponItemInfo::SendBattleDropBundle()
{
	D3DXVECTOR3 vTargetVel;
	vTargetVel.x = g_pShuttleChild->m_mMatrix._31;
	vTargetVel.y = g_pShuttleChild->m_mMatrix._32;
	vTargetVel.z = g_pShuttleChild->m_mMatrix._33;
	D3DXVec3Normalize(&vTargetVel,&-vTargetVel);

	MSG_FC_BATTLE_DROP_BUNDLE sMsg;
	sMsg.AttackClientIndex = g_pShuttleChild->m_myShuttleInfo.ClientIndex;
	sMsg.ItemUniqueNumber = m_pItemInfo->UniqueNumber;
	if( m_vecTargetIndex.empty() )
	{
		sMsg.TargetClientIndex = 0;
	}
	else
	{
		sMsg.TargetClientIndex = m_vecTargetIndex[0];
	}
	sMsg.DropPosition = g_pShuttleChild->m_vPos + 70.0f*vTargetVel - 30.0f*g_pShuttleChild->m_vUp;
	g_pFieldWinSocket->SendMsg( T_FC_BATTLE_DROP_BUNDLE, (char*)&sMsg, sizeof(sMsg) );
}
*/
void CWeaponItemInfo::AddMine(CWeaponMineData *pMine)
{
	m_pMineData->m_nMaxMineNumber = 
		CAtumSJ::GetCountMineAtATime( m_pItemInfo->GetRealItemInfo(), &g_pShuttleChild->m_paramFactor );
	int nMineCount = 0;
	vector<CWeaponMineData *>::iterator it = m_pMineData->m_vecMine.begin();
	while(it != m_pMineData->m_vecMine.end() )
	{
		if((*it)->m_dwWeaponState == _NORMAL )
		{
			nMineCount++;
		}
		it++;
	}
//	ASSERT_ASSERT(m_pMineData->m_vecMine.size() < m_pMineData->m_nMaxMineNumber);
	ASSERT_ASSERT(nMineCount < m_pMineData->m_nMaxMineNumber);
	m_pMineData->m_vecMine.push_back( pMine );
}

void CWeaponItemInfo::DeleteMine(CWeaponMineData *pMine)
{
	if( m_pMineData != NULL )
	{
	vector<CWeaponMineData *>::iterator it = m_pMineData->m_vecMine.begin();
	while(it != m_pMineData->m_vecMine.end() )
	{
		if( pMine == *it )
		{
			m_pMineData->m_vecMine.erase( it );
			return;
		}
		it++;
		}
	}
}

void CWeaponItemInfo::SendBattleDropMine()
{
	int nMultiNum = CAtumSJ::GetSecondaryMultiNumCount(m_pItemInfo->GetRealItemInfo(), m_pCharacterParamFactor);
	ASSERT_ASSERT( nMultiNum > 0 );
	// ���η��� ����
	int nSize = m_pMineData->m_vecMine.size();
	m_pMineData->m_nMaxMineNumber = 
		CAtumSJ::GetCountMineAtATime( m_pItemInfo->GetRealItemInfo(), &g_pShuttleChild->m_paramFactor );
	if(m_pMineData->m_nMaxMineNumber - m_pMineData->m_vecMine.size() < nMultiNum)
	{
		int count = nMultiNum - (m_pMineData->m_nMaxMineNumber - m_pMineData->m_vecMine.size());
		vector<CWeaponMineData *>::iterator it = m_pMineData->m_vecMine.begin();
		for(int i=0; i<count; i++)
		{
			CWeaponMineData * pMine = *it;
			if(pMine->m_dwWeaponState != _NORMAL )
			{
				i--;
				it++;
				if( it == m_pMineData->m_vecMine.end())
				{
					break;
				}
				continue;
			}
			MSG_FC_ITEM_DELETE_DROP_ITEM sMsg;
			sMsg.ItemFieldIndex = pMine->m_nFieldItemIndex;
			sMsg.DropPosition = pMine->m_vPos;
			g_pFieldWinSocket->SendMsg( T_FC_ITEM_DELETE_DROP_ITEM, (char*)&sMsg, sizeof(sMsg) );
			pMine->m_dwWeaponState = _EXPLODED;
			pMine->m_nFieldItemIndex = 0xFFFFFFFF;
			pMine->m_bUsing = FALSE;
			it = m_pMineData->m_vecMine.erase( it );
			if( it == m_pMineData->m_vecMine.end())
			{
				break;
			}
		}
	}
	MSG_FC_BATTLE_DROP_MINE sMsg;
	memset(&sMsg,0x00,sizeof(sMsg));
	char buffer[SIZE_MAX_PACKET];
	int nType = T_FC_BATTLE_DROP_MINE;
	sMsg.NumOfMines = (BYTE)nMultiNum;

	float fDistance = 0;
	float fDist;
	D3DXVECTOR3 vPos = g_pShuttleChild->m_vPos;
	D3DXVECTOR3 vTempPos,vTargetVel,vTempVel;
	vTargetVel = g_pShuttleChild->m_vWeaponVel;

	// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
	//vector<int>::iterator it = m_vecTargetIndex.begin();
	//while( it != m_vecTargetIndex.end() )
	vector<TARGET_DATA>::iterator it = m_vecTargetIndexData.begin();
	while( it != m_vecTargetIndexData.end() )
	// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
	{
		// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
		//CUnitData* pTarget = g_pScene->FindUnitDataByClientIndex( *it );
		CUnitData* pTarget = g_pScene->FindUnitDataByClientIndex( (*it).nTargetIndex );
		// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
		if( pTarget )
		{
			if( pTarget->m_dwPartType != _ENEMY ||										// 1. Ÿ���� ENEMY�� �ƴϰų�
				pTarget->IsPkAttackEnable()		||										// 2. ���� ������ �ƴϰų�
				(	pTarget->m_dwPartType == _ENEMY &&									// 3. Enemy �̰�
					g_pShuttleChild->m_pOrderTarget == pTarget &&						//    OrderTarget�̰�
//					(g_pShuttleChild->m_pPkNormalTimer->IsPkEnableNormalOrderTarget() && //	  Delay Time �� ����
					// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
// 					(g_pShuttleChild->IsEnemyPKAttackTime(*it) &&		// 2005-11-03 by ispark	  Delay Time �� ����
// 					g_pShuttleChild->IsEnemyPKTarget(*it))))
					(g_pShuttleChild->IsEnemyPKAttackTime((*it).nTargetIndex) &&		// 2005-11-03 by ispark	  Delay Time �� ����
					g_pShuttleChild->IsEnemyPKTarget((*it).nTargetIndex))))
					// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
			{
				// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
				sMsg.TargetIndex = (*it).nTargetIndex;
				// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
				vTargetVel = pTarget->m_vPos - vPos;
				fDistance = D3DXVec3Length(&vTargetVel);
				D3DXVec3Normalize(&vTargetVel,&vTargetVel);
				break;
			}
		}
		it++;

	}
//	if( m_vecTargetIndex.empty() == false)
//	{
//		CUnitData* pTarget = g_pScene->FindUnitDataByClientIndex( m_vecTargetIndex[0] );
//		if( pTarget )
//		{
//			sMsg.TargetIndex = m_vecTargetIndex[0];
//			vTargetVel = pTarget->m_vPos - vPos;
//			fDistance = D3DXVec3Length(&vTargetVel);
//			D3DXVec3Normalize(&vTargetVel,&vTargetVel);
//		}
//	}
	memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
	memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));

	for(int i=0;i<nMultiNum;i++)
	{
		USHORT nReactionRange = CAtumSJ::GetReactionRange( m_pItemInfo->GetRealItemInfo(), &g_pShuttleChild->m_paramFactor );
		if(fDistance == 0)
		{
			vTargetVel.x = Random(1.0f, -1.0f);
			vTargetVel.y = Random(1.0f, -1.0f);
			vTargetVel.z = Random(1.0f, -1.0f);
			D3DXVec3Normalize(&vTargetVel,&vTargetVel);
			vTempPos = vPos + nReactionRange*vTargetVel;
		}
		else
		{
			vTempPos.x = RANDI(0, nReactionRange - 1) - (m_pItemInfo->GetRealItemInfo()->ReactionRange)/2;
			vTempPos.y = RANDI(0, nReactionRange - 1) - (m_pItemInfo->GetRealItemInfo()->ReactionRange)/2;
			vTempPos.z = RANDI(0, nReactionRange - 1) - (m_pItemInfo->GetRealItemInfo()->ReactionRange)/2;
			vTempPos = vPos + fDistance*vTargetVel + vTempPos;
		}
		D3DXVec3Normalize(&vTempVel,&(vTempPos - vPos));
		fDist = g_pShuttleChild->CheckMapIsColl(vPos, vTempVel,(int)(fDistance/TILE_SIZE));
		if(fDist > 0.0f && fDist < fDistance + 30.0f)
			vTempPos = vPos + (fDist-30.0f)*vTempVel;
		AVECTOR3 vAPos;
		vAPos = vTempPos;
		memcpy(buffer+SIZE_FIELD_TYPE_HEADER+sizeof(sMsg)+i*sizeof(AVECTOR3), &vAPos, sizeof(AVECTOR3));
	}
	g_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg) + nMultiNum*sizeof(AVECTOR3));
}

void CWeaponItemInfo::SendUseMissileAndRocket()
{
	int nMultiNum = CAtumSJ::GetSecondaryMultiNumCount(m_pItemInfo->GetRealItemInfo(), m_pCharacterParamFactor);
	int nDir = nMultiNum/2;
	int nAttackCont = 0;	// �������� ���������� ����
	float fDist;
	const float fDistanceFirePos = 4.0f;	// �߻���ġ�� ����(2.0f)

	// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
// 	if( m_vecTargetIndex.empty() == false )
// 	{
// 		int nWeaponAmount = nMultiNum/m_vecTargetIndex.size();
// 		int nRestWeaponAmount = nMultiNum%m_vecTargetIndex.size();
// 		int temp = nWeaponAmount;
// 		vector<int>::iterator it = m_vecTargetIndex.begin();
// 		while( it != m_vecTargetIndex.end() )
	if( m_vecTargetIndexData.empty() == false )
	{
		int nWeaponAmount = nMultiNum/m_vecTargetIndexData.size();
		int nRestWeaponAmount = nMultiNum%m_vecTargetIndexData.size();
		int temp = nWeaponAmount;
		vector<TARGET_DATA>::iterator it = m_vecTargetIndexData.begin();
		while( it != m_vecTargetIndexData.end() )
	// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
		{
			// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
			//CUnitData* pTarget = g_pScene->FindUnitDataByClientIndex( (*it));
			CUnitData* pTarget = g_pScene->FindUnitDataByClientIndex( (*it).nTargetIndex );
			// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
			if( pTarget )
			{
				CItemData *pItem = g_pScene->FindFieldItemByPartTypeAndParent( _DUMMY, pTarget );
				int nRestTemp = 0;
				if(nRestWeaponAmount>0) nRestTemp = 1;
				nRestWeaponAmount--;						// 2005-08-12 by ispark
				int nAttackCount = nWeaponAmount + nRestTemp;//nRestWeaponAmount;
				while(nAttackCount>0)
				{
					fDist = fDistanceFirePos*(nAttackCont/2);
					if(nAttackCont%2==0)
						fDist *= -1.0f;
					nAttackCont++;
					
					if( pTarget->m_dwPartType != _ENEMY ||										// 1. Ÿ���� ENEMY�� �ƴϰų�
						pTarget->IsPkAttackEnable()		||										// 2. ���� ������ �ƴϰų�
						(	pTarget->m_dwPartType == _ENEMY &&									// 3. Enemy �̰�
							g_pShuttleChild->m_pOrderTarget == pTarget &&						//    OrderTarget�̰�
//							(g_pShuttleChild->m_pPkNormalTimer->IsPkEnableNormalOrderTarget() &&//	  Delay Time �� ����
							// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
// 							(g_pShuttleChild->IsEnemyPKAttackTime(*it) &&		// 2005-11-03 by ispark	  Delay Time �� ����
// 							g_pShuttleChild->IsEnemyPKTarget(*it))))
							(g_pShuttleChild->IsEnemyPKAttackTime((*it).nTargetIndex) &&		// 2005-11-03 by ispark	  Delay Time �� ����
							g_pShuttleChild->IsEnemyPKTarget((*it).nTargetIndex))))
							// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
					{																			// ���� ������ ������ �ϳ��� �����ϸ� ���� ����
						if( pItem )
						{
	//						SendBattleAttackSecondary( *it, pItem->m_nItemIndex, pItem->m_vPos,g_pShuttleChild->m_vSideVel*fDist );
							// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
							SendBattleAttackSecondary( (*it).nTargetIndex, pItem->m_nItemIndex, pItem->m_vPos, D3DXVECTOR3(fDist,0,0), (*it).nTargetMultiIndex );
							// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
						}
						else
						{
	//						SendBattleAttackSecondary( *it, 0, pTarget->m_vPos, g_pShuttleChild->m_vSideVel*fDist );
							// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
							//SendBattleAttackSecondary( (*it), 0, pTarget->m_vPos, D3DXVECTOR3(fDist,0,0) );

							// 2013-07-12 by bhsohn ��Ƽ Ÿ�� ���� 2�� Ÿ�� �߸� ������ ���� ����
//							SendBattleAttackSecondary( (*it).nTargetIndex, 0, pTarget->m_vPos, D3DXVECTOR3(fDist,0,0), (*it).nTargetMultiIndex );
							D3DXVECTOR3	 vTargetPos = pTarget->m_vPos;
							if( pTarget && 
								_MONSTER == pTarget->m_dwPartType)
								// end 2011. 09. 28 by jskim �� Ÿ�� �ý��� ���� ����( �ɽ��� ���� )
							{
								CMonsterData* pTargetMonster = (CMonsterData*)pTarget;
								if(pTargetMonster->m_nindexSize > 0 )
								{
									vTargetPos = pTargetMonster->GetMultiPos( pTargetMonster->m_nMultiIndex );
								}															
							}

							SendBattleAttackSecondary( (*it).nTargetIndex, 0, vTargetPos, D3DXVECTOR3(fDist,0,0), (*it).nTargetMultiIndex );
							// END 2013-07-12 by bhsohn ��Ƽ Ÿ�� ���� 2�� Ÿ�� �߸� ������ ���� ����
							// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
						}
					}
					else
					{	// �� ������ ���ǿ� ��� ���� ������ ����� �߻�
						SendBattleAttackSecondary( 0, 0, g_pShuttleChild->m_vPos + g_pShuttleChild->m_vVel*5000.0f , D3DXVECTOR3(fDist,0,0));
					}

					nMultiNum--;
					nAttackCount--;
				}
				nAttackCount = nWeaponAmount;
				if(nMultiNum == 0)
				{
					break;
				}
			}
			it++;
		}
	}
	else
	{
		while(nMultiNum > 0)
		{
			fDist = fDistanceFirePos*(nAttackCont/2);
			if(nAttackCont%2==0)
				fDist *= -1.0f;
			nAttackCont++;
			
//			SendBattleAttackSecondary(0, NULL, (USHORT)(fDist+128));
			SendBattleAttackSecondary( 0, 0, g_pShuttleChild->m_vPos + g_pShuttleChild->m_vVel*5000.0f , D3DXVECTOR3(fDist,0,0));
			nMultiNum--;
		}
	}
}

void CWeaponItemInfo::SendUseShield()
{
	g_pFieldWinSocket->SendMsg( T_FC_BATTLE_TOGGLE_SHIELD, NULL, 0);
}

void CWeaponItemInfo::SendUseDecoy()
{
	g_pFieldWinSocket->SendMsg( T_FC_BATTLE_TOGGLE_DECOY, NULL, 0);
}

void CWeaponItemInfo::SendUseDummy()
{
	MSG_FC_BATTLE_DROP_DUMMY sMsg;
	sMsg.ItemUniqueNumber = m_pItemInfo->UniqueNumber;
	g_pFieldWinSocket->SendMsg( T_FC_BATTLE_DROP_DUMMY, (char*)&sMsg, sizeof(sMsg));
}

void CWeaponItemInfo::SendUseFixer()
{
	MSG_FC_BATTLE_DROP_FIXER sMsg;
	sMsg.ItemUniqueNumber = m_pItemInfo->UniqueNumber;

	// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
// 	vector<int>::iterator it = m_vecTargetIndex.begin();
// 	while( it != m_vecTargetIndex.end() )
	vector<TARGET_DATA>::iterator it = m_vecTargetIndexData.begin();
	while( it != m_vecTargetIndexData.end() )
	// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
	{
		// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
		//CUnitData* pTarget = g_pScene->FindUnitDataByClientIndex( *it );
		CUnitData* pTarget = g_pScene->FindUnitDataByClientIndex( (*it).nTargetIndex );
		// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
		if( pTarget )
		{
			if( pTarget->m_dwPartType != _ENEMY ||										// 1. Ÿ���� ENEMY�� �ƴϰų�
				pTarget->IsPkAttackEnable()		||										// 2. ���� ������ �ƴϰų�
				(	pTarget->m_dwPartType == _ENEMY &&									// 3. Enemy �̰�
					g_pShuttleChild->m_pOrderTarget == pTarget &&						//    OrderTarget�̰�
//					g_pShuttleChild->m_pPkNormalTimer->IsPkEnableNormalOrderTarget() ) )//	  Delay Time �� ����
					// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
					//g_pShuttleChild->IsEnemyPKAttackTime(*it)))		// 2005-11-03 by ispark	  Delay Time �� ����
					g_pShuttleChild->IsEnemyPKAttackTime((*it).nTargetIndex)))		// 2005-11-03 by ispark	  Delay Time �� ����
					// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
			{
				// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
				//sMsg.TargetIndex = *it;
				sMsg.TargetIndex = (*it).nTargetIndex;
				// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
				g_pFieldWinSocket->SendMsg( T_FC_BATTLE_DROP_FIXER, (char*)&sMsg, sizeof(sMsg) );
				return;
			}
		}
		it++;
	}

	char message[256];
	wsprintf(message,STRERR_C_TARGET_0001);
	g_pD3dApp->m_pChat->CreateChatChild(message,COLOR_SYSTEM);

//	if(m_vecTargetIndex.empty() == false)
//	{
//		sMsg.TargetIndex = m_vecTargetIndex[0];
//		g_pFieldWinSocket->SendMsg( T_FC_BATTLE_DROP_FIXER, (char*)&sMsg, sizeof(sMsg) );
//	}
//	else
//	{
//		char message[256];
//		wsprintf(message,"������ ����� �����ϴ�.");
//		g_pD3dApp->m_pChat->CreateChatChild(message,COLOR_SYSTEM);
//	}
}

void CWeaponItemInfo::UseSecondary()
{
	switch(m_pItemInfo->Kind)
	{
	case ITEMKIND_BUNDLE:
		{
			SendUseMissileAndRocket();
			//SendBattleDropBundle();
		}
		break;
	case ITEMKIND_MINE:
		{
			SendBattleDropMine();
		}
		break;
	case ITEMKIND_MISSILE:
		{
			SendUseMissileAndRocket();
		}
		break;
	case ITEMKIND_ROCKET:
		{
			SendUseMissileAndRocket();
		}
		break;
	case ITEMKIND_SHIELD:
		{
			SendUseShield();
		}
		break;
	case ITEMKIND_DECOY:
		{
			SendUseDecoy();
		}
		break;
	case ITEMKIND_DUMMY:
		{
			SendUseDummy();
		}
		break;
	case ITEMKIND_FIXER:
		{
			SendUseFixer();
		}
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			CWeaponItemInfo::CheckInNet()
/// \brief		ȭ���� ���� Ÿ�� ����Ʈ ���� (multitarget, range, angle)
/// \author		dhkwon
/// \date		2004-07-21 ~ 2004-07-21
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CWeaponItemInfo::CheckInNet()
{
	if(IS_SECONDARY_WEAPON(m_pItemInfo->Kind))
	{
		// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
		//m_vecSoundCheck = m_vecTargetIndex;
		for(int i=0; i< m_vecTargetIndexData.size(); i++)
		{
			m_vecSoundCheck.push_back(m_vecTargetIndexData[i].nTargetIndex);
		}
		// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
	}
	// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
	m_vecTargetIndexData.clear();
	// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
	m_vecTargetOrderList.clear();
	if( g_pShuttleChild->m_bTurnCamera )
	{
		return;
	}
	// 2005-08-16 by ispark
	// ���̴� �������� Ÿ�� ������, ���⼭ �ϴ� ������ ������ TargetIndex�� clear�� �ϱ� �����̴�.
	if(g_pShuttleChild->m_pRadarItemInfo == NULL)
	{
		return;
	}
	// multi taget ���� ��ŭ
	// 2005-08-12 by ispark 
	// ��Ƽ Ÿ�� ���� - MultiTarget(Item->Multitarget + ParamFactor->pfp_MULTITAGET)�� nMultiNum�� �ּ� �ѹ��� �Ѵ�.
	// 2010-06-15 by shcho&hslee ��ý��� - �� ���� ����
	//int nMultiTarget = CAtumSJ::GetMultiTargetNum(m_pItemInfo->GetRealItemInfo(), m_pCharacterParamFactor);
	//int nMultiNum = CAtumSJ::GetSecondaryMultiNumCount(m_pItemInfo->GetRealItemInfo(), m_pCharacterParamFactor);
	int nMultiTarget, nMultiNum;
	ITEM * pITEM = NULL;						 //2011-10-06 by jhahn ��Ʈ�� ������ �ý���

	if(m_pItemInfo->Kind == ITEMKIND_PET_ITEM )
	{
		tPET_CURRENTINFO * tempCurrentInfo = g_pShuttleChild->GetPetManager()->GetPtr_PetCurrentData( m_pItemInfo->UniqueNumber );
		if(tempCurrentInfo)
		{	
			tPET_LEVEL_DATA* tempLevelData = g_pDatabase->GetPtr_PetLevelData( tempCurrentInfo->PetIndex,tempCurrentInfo->PetLevel );
			if(tempLevelData)
			{
				pITEM = g_pDatabase->GetServerItemInfo( tempLevelData->UseWeaponIndex );	//2011-10-06 by jhahn ��Ʈ�� ������ �ý���
			}
		}

		nMultiTarget	= CAtumSJ::GetMultiTargetNum(pITEM, m_pCharacterParamFactor);			
		nMultiNum		= CAtumSJ::GetSecondaryMultiNumCount(pITEM, m_pCharacterParamFactor);
	}
	else
	{
		nMultiTarget	= CAtumSJ::GetMultiTargetNum(m_pItemInfo->GetRealItemInfo(), m_pCharacterParamFactor);
		nMultiNum		= CAtumSJ::GetSecondaryMultiNumCount(m_pItemInfo->GetRealItemInfo(), m_pCharacterParamFactor);
	}	
	// end 2010-06-15 by shcho&hslee ��ý��� - �� ���� ����

	nMultiTarget = (nMultiTarget > nMultiNum) ? nMultiNum : nMultiTarget;
	int nTotalMultiTarget = nMultiTarget;

	BOOL bWarpGate = FALSE;
	BOOL bLockOn = FALSE;
	
	if(	(g_pShuttleChild->GetPkState() & PK_PVP ||		// 1. �ϴ��� �̰ų�
		g_pShuttleChild->GetPkState() & PK_FVF ||		// 2. ����� �̰ų�
		g_pShuttleChild->IsWarpGateZone() == FALSE) &&	// 3. ��������Ʈ ���� �ƴϸ�
		g_pShuttleChild->m_bySkillStateFlag != CL_SKILL_INVISIBLE)	// 4. �κ����� ��ų ����� �ƴ϶��
	{													// Ÿ���� ���� �� �ִ� �����̴�.
//		CMapEnemyIterator it = g_pScene->m_mapEnemyList.begin();
		// 2006-01-03 by ispark, ������ ����Ʈ������ �˻�
		CVecEnemyIterator it = g_pScene->m_vecEnemyRenderList.begin();
		while( it != g_pScene->m_vecEnemyRenderList.end() )
		{
#ifdef FREEWAR_
			if (isFreeForAllMap(g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex) || (*it)->IsPkEnable()) //this
#else
			if((*it)->IsPkEnable())
#endif
			{
				if( (((*it)->GetPkState() & PK_PVP ) ||		// 1. �ϴ��� �̰ų�
					((*it)->GetPkState() & PK_FVF ) ||		// 2. ����� �̰ų�
					CheckWarpGateZone((*it)->m_vPos)) &&	// 3. ��������Ʈ ���� �ƴϸ�
					(*it)->m_bEnemyCharacter == FALSE &&	// 4. ĳ���� ���°� �ƴϸ�
					// 2007-02-08 by dgwoo
					(*it)->m_nAlphaValue != SKILL_OBJECT_ALPHA_OTHER_INFLUENCE)	// 5. ���� �����Լ� 
				{											// Ÿ���� ���� �� �ִ� �����̴�.
					if(ATTACK_AVAILABLE_STATE((*it)->m_dwState))
					{
						BOOL bEqualTarget2Enemy = FALSE;				
						ClientIndex_t TargetClient = g_pShuttleChild->GetTargetClientIndext();
						if(  TargetClient == (*it)->m_infoCharacter.CharacterInfo.ClientIndex)
						{
							bEqualTarget2Enemy = TRUE;
						}
						
						float length = 0.0f;

						if(nMultiTarget == 0)
						{
							break;
						}
						if( IS_PRIMARY_WEAPON(m_pItemInfo->Kind) )
						{
							length = CheckPrimaryInNet( (*it), bEqualTarget2Enemy);
							if( length != -1 )
							{
								stTargetList TargetList;
								TargetList.nTargetIndex = (*it)->m_infoCharacter.CharacterInfo.ClientIndex;
								TargetList.fTargetLength = length;

								m_vecTargetOrderList.push_back(TargetList);

								bLockOn = TRUE;
							}
						}
						else if( IS_SECONDARY_WEAPON(m_pItemInfo->Kind) &&	nTotalMultiTarget > 1)			// nTotalMultiTarget�� 1�̸� �̰����� ������� �ʰ� �ؿ��� shuttle�� Ÿ�� ���ñ�� �Ѵ�.
						{
#ifdef FREEWAR_
						    if( CheckSecondaryInNet( (*it) ) )
#else
							if( CheckSecondaryInNet( (*it) ) && (((g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex - 4000) / 100) != 1) )
#endif

							{
								// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
								TARGET_DATA TargetData;
								memset(&TargetData,0x00,sizeof(TARGET_DATA)); 

								TargetData.nTargetIndex = (*it)->m_infoCharacter.CharacterInfo.ClientIndex;
								TargetData.nTargetMultiIndex = 0;
								m_vecTargetIndexData.push_back( TargetData );
								// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
								nMultiTarget--;
							}
						}
						// 2010-06-15 by shcho&hslee ��ý��� - �� ���� ����
						else if( m_pItemInfo->Kind == ITEMKIND_PET_ITEM )
						{
							length = CheckPrimaryInNet( (*it), bEqualTarget2Enemy);
							if( length != -1 )
							{
								stTargetList TargetList;
								TargetList.nTargetIndex = (*it)->m_infoCharacter.CharacterInfo.ClientIndex;
								TargetList.fTargetLength = length;

								m_vecTargetOrderList.push_back(TargetList);

								bLockOn = TRUE;
							}
						}
						// end 2010-06-15 by shcho&hslee ��ý��� - �� ���� ����
					}
					else
					{
						//DBGOUT("Enemy (%s) State is (%d)..  so Unable Attack .\n",(*it)->m_infoCharacter.CharacterInfo.CharacterName,(*it)->m_dwState);
					}
				}
				else
				{
					bWarpGate = TRUE;
				}
			}
			it++;
		}
	}
	else
	{
		bWarpGate = TRUE;
	}

	if(	bWarpGate == TRUE && 
		bLockOn == FALSE &&
		g_pShuttleChild->m_bCtrlKey == TRUE &&
		g_pShuttleChild && 
		g_pShuttleChild->m_pPkNormalTimer &&
		(IsPkEnableMap(g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex) || 
			g_pShuttleChild->m_pPkNormalTimer->IsCityWar()) )
	{
		g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_PK_0003,COLOR_ERROR);//"��������Ʈ �ֺ� ���������Դϴ�."
		g_pShuttleChild->m_bCtrlKey = FALSE;
	}

	// ���� �߿� ȭ���� �ɸ� �͵� �̱�
//	CMapMonsterIterator itMon = g_pScene->m_mapMonsterList.begin();
	// 2006-01-03 by ispark, ������ ����Ʈ������ �˻�
	// 2006-12-07 by ispark, Ÿ�� ���� �� �ִ� ���� üũ
	if(g_pShuttleChild->m_bySkillStateFlag != CL_SKILL_INVISIBLE)			// 1. �κ������� �ƴ϶��
	{
		CVecMonsterIterator itMon = g_pScene->m_vecMonsterRenderList.begin();
		while( itMon != g_pScene->m_vecMonsterRenderList.end() )
		{
			if(nMultiTarget == 0)
			{
				break;
			}

			int nType = (*itMon)->m_pMonsterInfo->Belligerence;
			char tmep[256];
			ZERO_MEMORY(tmep);
			strcpy(tmep, (*itMon)->m_pMonsterInfo->MonsterName);

			if(ATTACK_AVAILABLE_STATE((*itMon)->m_dwState) && 
				// 2010. 03. 18 by ckPark ���Ǵ�Ƽ �ʵ� 2��(���� ��ų �߰�)
				// ������ BELL_INFINITY_DEFENSE_MONSTER�� ���ͳ�
				// ���ϸ����� �������� ���ʹ� Ÿ���� ���������� �Ѵ�
				!(
					( (*itMon)->m_pMonsterInfo->Belligerence == BELL_INFINITY_DEFENSE_MONSTER )
					||
					(
						COMPARE_MPOPTION_BIT((*itMon)->m_pMonsterInfo->MPOption, MPOPTION_BIT_PATTERN_MONSTER )
						&& COMPARE_BODYCON_BIT((*itMon)->GetCurrentBodyCondition(), BODYCON_CREATION_MASK)
					)
				)
				&&
				// end 2010. 03. 18 by ckPark ���Ǵ�Ƽ �ʵ� 2��(���� ��ų �߰�)
				!IS_SAME_CHARACTER_MONSTER_INFLUENCE(g_pShuttleChild->m_myShuttleInfo.InfluenceType, (*itMon)->m_pMonsterInfo->Belligerence))
			{
				BOOL bEqualTarget2Enemy = FALSE;
				ClientIndex_t TargetClient = g_pShuttleChild->GetTargetClientIndext();
				if(  TargetClient == (*itMon)->m_info.MonsterIndex)
				{
					bEqualTarget2Enemy = TRUE;
				}

				float length = 0.0f;
				// 2010-06-15 by shcho&hslee ��ý��� - �� ���� ����
				//if( IS_PRIMARY_WEAPON(m_pItemInfo->Kind) )
				if( IS_PRIMARY_WEAPON(m_pItemInfo->Kind) ||  m_pItemInfo->Kind == ITEMKIND_PET_ITEM )
				// end 2010-06-15 by shcho&hslee ��ý��� - �� ���� ����
				{
					// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
					if((*itMon)->m_nindexSize)
					{
						vector<stTargetList> vecTargetList;
						for(int i=0; i< (*itMon)->m_nindexSize; i++)
						{
							length = CheckPrimaryMultiInNet( (CUnitData*)(*itMon), bEqualTarget2Enemy, i);
							if( length != -1)
							{
								stTargetList TargetList;
								TargetList.nTargetIndex = (*itMon)->m_info.MonsterIndex;
								TargetList.fTargetLength = length;
								TargetList.nMultiIndex = i;
								vecTargetList.push_back(TargetList);
							}
						}
						if(vecTargetList.size() > 0)
						{
							sort(vecTargetList.begin(), vecTargetList.end(), sort_List());
							m_vecTargetOrderList.push_back(vecTargetList.front());	

							(*itMon)->m_nMultiIndex = vecTargetList.front().nMultiIndex;

							if(g_pShuttleChild->m_bAttackMode == _SIEGE)
							{
								if( (*itMon)->m_bSiegeMode == FALSE )
								{
									(*itMon)->m_nSiegeIndex = (*itMon)->m_nMultiIndex;
									(*itMon)->m_bSiegeMode = TRUE;
								}
								
								if((*itMon)->m_bSiegeMode == TRUE && (*itMon)->m_nMultiIndex != (*itMon)->m_nSiegeIndex)
								{								
									(*itMon)->m_nMultiIndex = (*itMon)->m_nSiegeIndex;				
								}	
							}							
							vecTargetList.clear();							
						}
					}
					else
					{
						// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
						length = CheckPrimaryInNet( (CUnitData*)(*itMon), bEqualTarget2Enemy);
						if( length != -1 )   // (*itMon)->m_bRenderState == TRUE
						{
							stTargetList TargetList;
							TargetList.nTargetIndex = (*itMon)->m_info.MonsterIndex;
							TargetList.fTargetLength = length;
							TargetList.nMultiIndex = 0;
							m_vecTargetOrderList.push_back(TargetList);
							
							//					m_vecTargetIndex.push_back( (*itMon)->m_info.MonsterIndex );
							//					nMultiTarget--;
						}
					}
					// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
				}
				// 2005-08-12 by ispark
				// nTotalMultiTarget�� 1�̸� �̰����� ������� �ʰ� �ؿ��� shuttle�� Ÿ�� ���ñ�� �Ѵ�.
				else if(IS_SECONDARY_WEAPON(m_pItemInfo->Kind) &&	
						nTotalMultiTarget > 1)
				{
					// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
					if((*itMon)->m_vecvmultiData.size())
					{
						for (int i=1; i < (*itMon)->m_vecvmultiData.size(); i++)
						{
							if(nMultiTarget >= 1 && CheckMultiInNet(*itMon, i) )
							{

								// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
								//m_vecTargetIndexDa.push_back( (*itMon)->m_info.MonsterIndex );
								TARGET_DATA TargetData;
								memset(&TargetData,0x00,sizeof(TARGET_DATA));
								
								TargetData.nTargetIndex = (*itMon)->m_info.MonsterIndex;
								TargetData.nTargetMultiIndex = i;
								m_vecTargetIndexData.push_back( TargetData );
								// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
								nMultiTarget--;								
							}						
						}
					}
// 					// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
					if(nMultiTarget >= 1 && CheckSecondaryInNet( (CUnitData*)(*itMon) ) )  // (*itMon)->m_bRenderState == TRUE
					{
						// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
						//m_vecTargetIndex.push_back( (*itMon)->m_info.MonsterIndex );
						TARGET_DATA TargetData;
						memset(&TargetData,0x00,sizeof(TARGET_DATA));
						
						TargetData.nTargetIndex = (*itMon)->m_info.MonsterIndex;
						TargetData.nTargetMultiIndex = 0;
						m_vecTargetIndexData.push_back( TargetData );
						// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���						
						nMultiTarget--;
					}
				}
			}
			itMon++;
		}
	}

	// 2006-02-01 by ispark, Ÿ�� �Ÿ� ���ļ����� �Է�
	SortTargetList();
	// 2007-05-16 by bhsohn 1������ Ÿ�� ó��
	// 2010-06-15 by shcho&hslee ��ý��� - �� ���� ����
	//if( IS_PRIMARY_WEAPON(m_pItemInfo->Kind) )
	if( IS_PRIMARY_WEAPON(m_pItemInfo->Kind) ||  m_pItemInfo->Kind == ITEMKIND_PET_ITEM )
	// end 2010-06-15 by shcho&hslee ��ý��� - �� ���� ����
	{
		// 1�� ���� �϶��� ���� Ÿ�� ��� �ִ� �� �ε����� ���� ������ �ű��.
		PrimarySortTargetList();
	}	
	
	vector<stTargetList> :: iterator itList = m_vecTargetOrderList.begin();
	while(itList != m_vecTargetOrderList.end())
	{
		stTargetList tempList = *itList;
		// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
		TARGET_DATA tempData;
		tempData.nTargetIndex =tempList.nTargetIndex;
		tempData.nTargetMultiIndex = tempList.nMultiIndex;
		m_vecTargetIndexData.push_back( tempData );
		// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���

		nMultiTarget--;
		if(nMultiTarget == 0)
			break;

		itList++;
	}
	
	// shuttle�� Ÿ�� ���ñ���� �˻�
	if(g_pShuttleChild->m_pOrderTarget && ATTACK_AVAILABLE_STATE(g_pShuttleChild->m_pOrderTarget->m_dwState))
	{
		int index = g_pScene->FindClientIndexByUnitData((CUnitData*)g_pShuttleChild->m_pOrderTarget);
		ASSERT_ASSERT( index > 0 );
		// 2010-06-15 by shcho&hslee ��ý��� - �� ���� ����
		//if( IS_PRIMARY_WEAPON(m_pItemInfo->Kind) )
		if( IS_PRIMARY_WEAPON(m_pItemInfo->Kind) ||  m_pItemInfo->Kind == ITEMKIND_PET_ITEM )
		// end 2010-06-15 by shcho&hslee ��ý��� - �� ���� ����
		{
			// 2005-03-25 by jschoi - ������� Ÿ���� ������ ������ ����
			if(g_pD3dApp->m_dwTargetting == NEW_TARGETTING)
			{	// NEW_TARGETTING
				if( CheckPrimaryInNet( (CUnitData*)g_pShuttleChild->m_pOrderTarget ) )
				{
					PutTargetIndex( nMultiTarget, index );
				}
			}
			else if(g_pD3dApp->m_dwTargetting == OLD2_TARGETTING)
			{	// OLD2_TARGETTING
				if( nMultiTarget > 0 && CheckPrimaryInNet( (CUnitData*)g_pShuttleChild->m_pOrderTarget ) != -1)
				{
					PutTargetIndex( nMultiTarget, index );
				}
			}
			else
			{	// OLD_TARGETTING
				if( nMultiTarget > 0 && CheckPrimaryInNet( (CUnitData*)g_pShuttleChild->m_pOrderTarget ) != -1)
				{
					PutTargetIndex( nMultiTarget, index );
				}
			}
		}
		else if( IS_SECONDARY_WEAPON(m_pItemInfo->Kind) &&
				nTotalMultiTarget <= 1)
		{
			// nTotalMultiTarget�� 1 ���ϸ�(OrderTarget�� ���� �� ����) ���⼭ Ÿ�� �˻�,

			// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
			// 2011. 09. 28 by jskim �� Ÿ�� �ý��� ���� ����( �ɽ��� ���� )
			//if(((CMonsterData*)g_pShuttleChild->m_pOrderTarget)->m_vecvmultiData.size())
			if(g_pShuttleChild->m_pOrderTarget &&
				g_pShuttleChild->m_pOrderTarget->m_dwPartType == _MONSTER &&
				((CMonsterData*)g_pShuttleChild->m_pOrderTarget)->m_vecvmultiData.size())
			// end 2011. 09. 28 by jskim �� Ÿ�� �ý��� ���� ����( �ɽ��� ���� )
			{
				for (int i=0; i < ((CMonsterData*)g_pShuttleChild->m_pOrderTarget)->m_nindexSize ; i++)
				{
 					if( CheckMultiInNet((CUnitData*)g_pShuttleChild->m_pOrderTarget, i ) )
 					{						
 						PutTargetIndex( nMultiTarget, index, i );						
 					}						
// 					if(CheckPrimaryMultiInNet( (CUnitData*)g_pShuttleChild->m_pOrderTarget, FALSE, i) )
// 					{
// 						PutTargetIndex( nMultiTarget, index, i );		
// 					}	
				}
				// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
			}
 			else if( nMultiTarget > 0 && g_pShuttleChild->m_pOrderTarget && CheckSecondaryInNet( (CUnitData*)g_pShuttleChild->m_pOrderTarget ))
			{
				PutTargetIndex( nMultiTarget, index );
			}
		}
 	}
}

// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
//void CWeaponItemInfo::PutTargetIndex( int nRemainedTarget, int index )
void CWeaponItemInfo::PutTargetIndex( int nRemainedTarget, int index, int MultiIndex /* = 0 */ )
// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
{
	// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
// 	vector<int>::iterator it = m_vecTargetIndex.begin();
// 	while( it != m_vecTargetIndex.end() )
// 	{
// 		if( index == *it )
// 		{
// 			return ;
// 		}
// 		it++;
// 	}
// 	if( nRemainedTarget == 0 )
// 	{
// 		it = m_vecTargetIndex.begin();
// 		m_vecTargetIndex.erase( it );
// 	}
// 
// 	// 2005-03-25 by jschoi - Ÿ���� ���� ���� ����
// 	if(g_pD3dApp->m_dwTargetting == NEW_TARGETTING)
// 	{
// 		m_vecTargetIndex.insert(m_vecTargetIndex.begin(), index );
// 	}
// 	else if(g_pD3dApp->m_dwTargetting == OLD2_TARGETTING)
// 	{
// 		m_vecTargetIndex.push_back( index );
// 	}
// 	else
// 	{
// 		m_vecTargetIndex.push_back( index );
// 	}
	vector<TARGET_DATA>::iterator it = m_vecTargetIndexData.begin();
	while( it != m_vecTargetIndexData.end() )
	{
		if( index == (*it).nTargetIndex )
		{
			return ;
		}
		it++;
	}
	if( nRemainedTarget == 0 )
	{
		it = m_vecTargetIndexData.begin();
		m_vecTargetIndexData.erase( it );
	}

	// 2005-03-25 by jschoi - Ÿ���� ���� ���� ����
	if(g_pD3dApp->m_dwTargetting == NEW_TARGETTING)
	{
		TARGET_DATA tempData;
		tempData.nTargetIndex = index;
		// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
		tempData.nTargetMultiIndex = MultiIndex;
		// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
		m_vecTargetIndexData.insert(m_vecTargetIndexData.begin(), tempData );
	}
	else if(g_pD3dApp->m_dwTargetting == OLD2_TARGETTING)
	{
		TARGET_DATA tempData;
		tempData.nTargetIndex = index;
		// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
		tempData.nTargetMultiIndex = MultiIndex;
		// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
		m_vecTargetIndexData.push_back( tempData );
	}
	else
	{
		TARGET_DATA tempData;
		tempData.nTargetIndex = index;
		// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
		tempData.nTargetMultiIndex = MultiIndex;
		// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
	 	m_vecTargetIndexData.push_back( tempData );
	}
	// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���

}

float CWeaponItemInfo::CheckPrimaryInNet(CUnitData* pTarget, BOOL bEqualTarget2Enemy)
{
	if(g_pInterface->m_pTarget->GetMouseType() == MOUSE_TYPE_1)
	{
		if( g_pShuttleChild->m_pOrderTarget != NULL &&
			g_pShuttleChild->m_pOrderTarget != pTarget )
		{
			return -1.0f;
		}
	}

	float length = 0.0f;

	if(g_pD3dApp->m_dwTargetting == NEW_TARGETTING)
	{	// NEW_TARGETTING
		
		// 2005-03-24 by jschoi - ���ο� Ÿ���� ���
		D3DXPLANE plane;
		D3DXPlaneFromPointNormal( &plane, &g_pShuttleChild->m_vPos, &g_pCamera->GetViewDir() );
		if(D3DXPlaneDotCoord(&plane, &pTarget->m_vPos) < 0.0f)
		{
			return -1.0f;
		}

		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
		CheckMouseReverse(&pt);
		
		D3DXVECTOR2 v1, v2;
		v1 = D3DXVECTOR2(pt.x,pt.y);
		v2 = D3DXVECTOR2(pTarget->m_nObjScreenX,pTarget->m_nObjScreenY);
		length = D3DXVec3Length(&(g_pShuttleChild->m_vPos - pTarget->m_vPos));
		if( D3DXVec2Length(&(v1 - v2)) < SHUTTLE_TARGET_MOUSE_CIRCLE_RADIUS*((float)g_pD3dApp->GetBackBufferDesc().Width/(float)800) /*||
			g_pShuttleChild->CheckPickingTarget(pTarget)*/)
		{
			return length;
		}

		return -1.0f;
	}
	else if(g_pD3dApp->m_dwTargetting == OLD2_TARGETTING)
	{	// OLD2_TARGETTING

		// 2005-03-24 by jschoi - ���� Ÿ���� ���
//		if(IS_DT(g_pShuttleChild->m_myShuttleInfo.UnitKind)== FALSE || g_pShuttleChild->m_bAttackMode == _SIEGE || g_pShuttleChild->m_bIsAir == TRUE)
		if(IS_DT(g_pShuttleChild->m_myShuttleInfo.UnitKind)== FALSE || g_pShuttleChild->m_bIsAir == TRUE)
		{
			D3DXPLANE plane;
			D3DXPlaneFromPointNormal( &plane, &g_pShuttleChild->m_vPos, &g_pCamera->GetViewDir() );
			if(D3DXPlaneDotCoord(&plane, &pTarget->m_vPos) < 0.0f)
			{
				return -1.0f;
			}
			// �����
			D3DXVECTOR2 v1 = D3DXVECTOR2(pTarget->m_nObjScreenX, pTarget->m_nObjScreenY);
			D3DXVECTOR2 v2 = D3DXVECTOR2(g_pD3dApp->GetBackBufferDesc().Width/2, g_pD3dApp->GetBackBufferDesc().Height/2);
			length = D3DXVec3Length(&(g_pShuttleChild->m_vPos - pTarget->m_vPos));
			
			// 2007-04-20 by bhsohn ���� ����� ����� �� ���� ���ϴ� ����ó��
			//if(D3DXVec2Length(&(v1 - v2)) > SHUTTLE_ATTACK_CENTER_RADIUS*((float)g_pD3dApp->GetBackBufferDesc().Width/(float)800))			
			BOOL bAGearFollowEnemy = FALSE;
			if((TRUE == bEqualTarget2Enemy)
				&&(IS_DT(g_pShuttleChild->m_myShuttleInfo.UnitKind)== TRUE))
			{
				bAGearFollowEnemy = g_pShuttleChild->IsAGearFollowEnemy();
			}
			if((D3DXVec2Length(&(v1 - v2)) > SHUTTLE_ATTACK_CENTER_RADIUS*((float)g_pD3dApp->GetBackBufferDesc().Width/(float)800))
				&& (FALSE == bAGearFollowEnemy) )
			{
				return -1.0f;
			}
		}
		else	// A��� (������ ����)
		{
			// 2013-02-05 by bhsohn A��� 1�� ����� �ڿ� �ִ� ��, ���ݵǴ� ���� ����
			if(IS_DT(g_pShuttleChild->m_myShuttleInfo.UnitKind))
			{
				D3DXPLANE plane;
				D3DXPlaneFromPointNormal( &plane, &g_pShuttleChild->m_vPos, &g_pCamera->GetViewDir() );
				if(D3DXPlaneDotCoord(&plane, &pTarget->m_vPos) < 0.0f)
				{
//					DBGOUT("(D3DXPlaneDotCoord(&plane, &pTarget->m_vPos) < 0.0f) \n");
					return -1.0f;
				}
			}
			// END 2013-02-05 by bhsohn A��� 1�� ����� �ڿ� �ִ� ��, ���ݵǴ� ���� ����

			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
			CheckMouseReverse(&pt);

			D3DXVECTOR2 v1, v2;
			v1 = D3DXVECTOR2(pt.x,pt.y);
			v2 = D3DXVECTOR2(pTarget->m_nObjScreenX,pTarget->m_nObjScreenY);
			length = D3DXVec3Length(&(g_pShuttleChild->m_vPos - pTarget->m_vPos));

			// 2007-04-17 by bhsohn ����� �Ÿ������� ������� ������ �ȵ��� ���� ó��			
			//if( D3DXVec2Length(&(v1 - v2)) > 25.0f*((float)g_pD3dApp->GetBackBufferDesc().Width/(float)800) )
			BOOL bAGearFollowEnemy = FALSE;
			if(bEqualTarget2Enemy)
			{
				bAGearFollowEnemy = g_pShuttleChild->IsAGearFollowEnemy();
			}
			if(( D3DXVec2Length(&(v1 - v2)) > 25.0f*((float)g_pD3dApp->GetBackBufferDesc().Width/(float)800) )
				&& (FALSE == bAGearFollowEnemy))
			{
				return -1.0f;
			}			
		}
		return length;
	}
	else
	{	// OLD_TARGETTING

		// 2005-03-24 by jschoi - ���� Ÿ���� ���
//		if(IS_DT(g_pShuttleChild->m_myShuttleInfo.UnitKind)== FALSE || g_pShuttleChild->m_bAttackMode == _SIEGE)
		if(IS_DT(g_pShuttleChild->m_myShuttleInfo.UnitKind)== FALSE || g_pShuttleChild->m_bIsAir == TRUE)
		{
			D3DXPLANE plane;
			D3DXPlaneFromPointNormal( &plane, &g_pShuttleChild->m_vPos, &g_pCamera->GetViewDir() );
			if(D3DXPlaneDotCoord(&plane, &pTarget->m_vPos) < 0.0f)
			{
				return -1.0f;
			}
			// �����
			D3DXVECTOR2 v1 = D3DXVECTOR2(pTarget->m_nObjScreenX, pTarget->m_nObjScreenY);
			D3DXVECTOR2 v2 = D3DXVECTOR2(g_pD3dApp->GetBackBufferDesc().Width/2, g_pD3dApp->GetBackBufferDesc().Height/2);
			length = D3DXVec3Length(&(g_pShuttleChild->m_vPos - pTarget->m_vPos));
			if(D3DXVec2Length(&(v1 - v2)) > SHUTTLE_ATTACK_CENTER_RADIUS*((float)g_pD3dApp->GetBackBufferDesc().Width/(float)800))
			{
				return -1.0f;
			}
		}
		else	// A��� 
		{
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
			CheckMouseReverse(&pt);

			D3DXVECTOR2 v1, v2;
			v1 = D3DXVECTOR2(pt.x,pt.y);
			v2 = D3DXVECTOR2(pTarget->m_nObjScreenX,pTarget->m_nObjScreenY);
			length = D3DXVec3Length(&(g_pShuttleChild->m_vPos - pTarget->m_vPos));
			if( D3DXVec2Length(&(v1 - v2)) > 25.0f*((float)g_pD3dApp->GetBackBufferDesc().Width/(float)800) )
			{
				return -1.0f;
			}
		}
		return length;
	}
}

// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
float CWeaponItemInfo::CheckPrimaryMultiInNet(CUnitData* pTarget, BOOL bEqualTarget2Enemy, int nMultiIndex)
{
	if(g_pInterface->m_pTarget->GetMouseType() == MOUSE_TYPE_1)
	{
		if( g_pShuttleChild->m_pOrderTarget != NULL &&
			g_pShuttleChild->m_pOrderTarget != pTarget )
		{
			return -1.0f;
		}
	}
	if(((CMonsterData*)pTarget)->m_nindexSize <= 0)
	{
		return -1.0f;
	}
		
	float length = 0.0f;
	D3DXVECTOR3 vScreenposition = D3DXVECTOR3(0,0,0);
	int x,y,w;
	
	// 2011. 09. 28 by jskim �� Ÿ�� �ý��� ���� ����( �ɽ��� ���� )
// 	// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
// 	vScreenposition = ((CMonsterData*)pTarget)->GetMultiPos(nMultiIndex);
// 	((CMonsterData*)pTarget)->GetScreenPos(vScreenposition, x, y, w);
// 	// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
	if(pTarget &&
		pTarget->m_dwPartType == _MONSTER )
	{
	vScreenposition = ((CMonsterData*)pTarget)->GetMultiPos(nMultiIndex);
	((CMonsterData*)pTarget)->GetScreenPos(vScreenposition, x, y, w);
	}
	// end 2011. 09. 28 by jskim �� Ÿ�� �ý��� ���� ����( �ɽ��� ���� )

	if(IS_DT(g_pShuttleChild->m_myShuttleInfo.UnitKind)== FALSE || g_pShuttleChild->m_bIsAir == TRUE)
	{
		D3DXPLANE plane;
		
		D3DXPlaneFromPointNormal( &plane, &g_pShuttleChild->m_vPos, &g_pCamera->GetViewDir() );
		if(D3DXPlaneDotCoord(&plane, &pTarget->m_vPos) < 0.0f)
		{
			return -1.0f;
		}		
		// �����
		D3DXVECTOR2 v1 = D3DXVECTOR2(x, y);
		D3DXVECTOR2 v2 = D3DXVECTOR2(g_pD3dApp->GetBackBufferDesc().Width/2, g_pD3dApp->GetBackBufferDesc().Height/2);
		length = D3DXVec3Length(&(g_pShuttleChild->m_vPos - vScreenposition));
		
		BOOL bAGearFollowEnemy = FALSE;
		if((TRUE == bEqualTarget2Enemy)
			&&(IS_DT(g_pShuttleChild->m_myShuttleInfo.UnitKind)== TRUE))
		{
			bAGearFollowEnemy = g_pShuttleChild->IsAGearFollowEnemy();
		}
		if((D3DXVec2Length(&(v1 - v2)) > SHUTTLE_ATTACK_CENTER_RADIUS*((float)g_pD3dApp->GetBackBufferDesc().Width/(float)800))
			&& (FALSE == bAGearFollowEnemy) )
		{
			return -1.0f;
		}
	}
	else	// A��� (������ ����)
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
		CheckMouseReverse(&pt);
			
		D3DXVECTOR2 v1, v2;
		v1 = D3DXVECTOR2(pt.x,pt.y);
		v2 = D3DXVECTOR2(x,y);
		length = D3DXVec3Length(&(g_pShuttleChild->m_vPos - vScreenposition));
			
		BOOL bAGearFollowEnemy = FALSE;
		if(bEqualTarget2Enemy)
		{
			bAGearFollowEnemy = g_pShuttleChild->IsAGearFollowEnemy();
		}
		if(( D3DXVec2Length(&(v1 - v2)) > 25.0f*((float)g_pD3dApp->GetBackBufferDesc().Width/(float)800) )
			&& (FALSE == bAGearFollowEnemy))
		{
			return -1.0f;
		}			
	}
	return length;
}
// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���

BOOL CWeaponItemInfo::CheckSecondaryInNet(CUnitData* pTarget)
{
	float fLength = D3DXVec3Length(&(g_pShuttleChild->m_vPos - pTarget->m_vPos));
	float fSecondaryRage = CAtumSJ::GetSecondaryRadarRange(g_pShuttleChild->m_pRadarItemInfo->ItemInfo, m_pCharacterParamFactor);
//	if( fLength > CAtumSJ::GetAttackRange(m_pItemInfo->GetRealItemInfo(), m_pCharacterParamFactor) )	// 2005-08-16 by ispark
//	if(fLength > g_pShuttleChild->m_pRadarItemInfo->ItemInfo->AbilityMax)
	if(fLength > fSecondaryRage)
	{
		return FALSE;
	}
	// ����
	D3DXVECTOR3 vTargetVel;
	D3DXVec3Normalize(&vTargetVel,&(pTarget->m_vPos - g_pShuttleChild->m_vPos));
	float fAngle = ACOS(D3DXVec3Dot(&g_pShuttleChild->m_vWeaponVel,&vTargetVel));
	if( fAngle > CAtumSJ::GetAttackRangeAngle(m_pItemInfo->GetRealItemInfo(), m_pCharacterParamFactor) )
	{
		return FALSE;
	}
	// ���� �÷���
	int index = g_pScene->FindClientIndexByUnitData(pTarget);
	vector<int>::iterator it = m_vecSoundCheck.begin();
	while( it != m_vecSoundCheck.end() )  
	{
		if( index == *it )
		{
			break ;
		}
		it++;
	}
	if( it == m_vecSoundCheck.end() )
	{
		g_pD3dApp->m_pSound->PlayD3DSound(SOUND_LOCKON_SECONDARY, g_pShuttleChild->m_vPos, FALSE);
	}

	return TRUE;

}

// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
BOOL CWeaponItemInfo::CheckMultiInNet( CUnitData* pTarget, int nMultiIndex )
{
	D3DXVECTOR3 tempposition;

	tempposition = ((CMonsterData*)pTarget)->GetMultiPos(nMultiIndex);

	float fLength = D3DXVec3Length(&(g_pShuttleChild->m_vPos - tempposition));
	float fSecondaryRage = CAtumSJ::GetSecondaryRadarRange(g_pShuttleChild->m_pRadarItemInfo->ItemInfo, m_pCharacterParamFactor);

	if(fLength > fSecondaryRage)
	{
		return FALSE;
	}
	float length = 0.0f;

	D3DXVECTOR3 vTargetVel;
	D3DXVec3Normalize(&vTargetVel,&(tempposition - g_pShuttleChild->m_vPos));
	float fAngle = ACOS(D3DXVec3Dot(&g_pShuttleChild->m_vWeaponVel,&vTargetVel));
	if( fAngle > CAtumSJ::GetAttackRangeAngle(m_pItemInfo->GetRealItemInfo(), m_pCharacterParamFactor) )
	{
		return FALSE;
	}
	return TRUE;
}
// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���



///////////////////////////////////////////////////////////////////////////////
/// \fn			CWeaponItemInfo::SetWeaponCount(INT nCount)
/// \brief		���� �Ѿ� �߼� ����
/// \author		dhkwon
/// \date		2004-07-21 ~ 2004-07-21
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////

void CWeaponItemInfo::SetWeaponCount(INT nCount)
{
	if(IS_PRIMARY_WEAPON_1(m_pItemInfo->Kind))
	{
		if(g_pTutorial->IsTutorialMode() == TRUE)
		{
			if(m_pItemInfo->CurrentCount <= 10)
				m_pItemInfo->CurrentCount = 200;
			if(IS_DT(g_pShuttleChild->m_myShuttleInfo.UnitKind))
			{
				m_pItemInfo->CurrentCount -= 1;
			}
			else
			{
				m_pItemInfo->CurrentCount -= 1;
			}
			
			return;
		}
		m_pItemInfo->CurrentCount = nCount;
		if(nCount <= 0)
		{
			ResetWeaponBodyCondition(WEAPON_BODYCON_RELOAD);
			CItemInfo* pItemInfo = g_pStoreData->FindBulletItem( m_pItemInfo->ItemInfo->Caliber );
			if( pItemInfo != NULL )
			{
				g_pGameMain->m_pInven->SendUseItem( (ITEM_BASE*)pItemInfo );
			}
//			UsePrimary(); // ������
		}
	}
	else if(IS_PRIMARY_WEAPON_2(m_pItemInfo->Kind))
	{
		g_pShuttleChild->m_myShuttleInfo.CurrentEP = nCount;
//		ASSERT_ASSERT(g_pShuttleChild->m_myShuttleInfo.CurrentEP>=0);
		g_pShuttleChild->m_fNextEP = g_pShuttleChild->m_myShuttleInfo.CurrentEP;
		if(g_pGameMain->m_pUnitInfoBar)
		{
			g_pGameMain->m_pUnitInfoBar->SetEP( g_pShuttleChild->m_myShuttleInfo.CurrentEP, 
				(float)g_pShuttleChild->m_myShuttleInfo.EP);
		}
		if(g_pShuttleChild->m_myShuttleInfo.CurrentEP <= 0)
		{
			ResetWeaponBodyCondition(WEAPON_BODYCON_RELOAD);
		}
	}
	else if(IS_SECONDARY_WEAPON(m_pItemInfo->Kind))
	{
		if(g_pTutorial->IsTutorialMode() == TRUE)
		{
			if(m_pItemInfo->CurrentCount <= 10)
				m_pItemInfo->CurrentCount = 200;
			if(IS_DT(g_pShuttleChild->m_myShuttleInfo.UnitKind))
			{
				m_pItemInfo->CurrentCount -= 1;
			}
			else
			{
				m_pItemInfo->CurrentCount -= 1;
			}
			return;
		}
		m_pItemInfo->CurrentCount = nCount;
		if(m_pItemInfo->CurrentCount <= 0)
		{
			ResetWeaponBodyCondition(WEAPON_BODYCON_RELOAD);
			CItemInfo* pItemInfo = g_pStoreData->FindBulletItem( m_pItemInfo->ItemInfo->Caliber );
			if( pItemInfo != NULL )
			{
				g_pGameMain->m_pInven->SendUseItem( (ITEM_BASE*)pItemInfo );
			}

		}
	}
}

void CWeaponItemInfo::BulletReloaded(MSG_FC_BATTLE_PRI_BULLET_RELOADED* pMsg)
{		
	char message[256];
	m_fReattackCheckTime = 0;
	m_pItemInfo->CurrentCount = pMsg->BulletCount;

	// 2007-08-07 by bhsohn �Ѿ� ������ �߰�
//	wsprintf(message,STRMSG_C_INTERFACE_0004,pMsg->BulletCount);//"ź�� %d�� ������"
//	g_pD3dApp->m_pChat->CreateChatChild(message,COLOR_SYSTEM);
	if(BULLET_RECHARGE_TYPE_BULLET_ITEM == pMsg->RechargeType)	
	{		
		wsprintf(message,STRMSG_C_070808_0201,m_pItemInfo->GetRealItemInfo()->ItemName, pMsg->BulletCount);//"ź�� %d�� ������"		
	}
	else
	{
		wsprintf(message,STRMSG_C_INTERFACE_0004,pMsg->BulletCount);//"ź�� %d�� ������"
	}
	g_pD3dApp->m_pChat->CreateChatChild(message,COLOR_SYSTEM);
	// end 2007-08-07 by bhsohn �Ѿ� ������ �߰�
	ResetWeaponBodyCondition(WEAPON_BODYCON_LOADING);
	g_pD3dApp->m_pSound->PlayD3DSound(SOUND_WEAPON_RELOAD, D3DXVECTOR3(0,0,0), FALSE);
}

void CWeaponItemInfo::ResetWeaponBodyCondition(BodyCond_t hyBody)
{
	if(IS_PRIMARY_WEAPON(m_pItemInfo->Kind))
	{
		g_pShuttleChild->ResetPrimaryWeaponBodyCondition(hyBody);
	}
	else if(IS_SECONDARY_WEAPON(m_pItemInfo->Kind))
	{
		g_pShuttleChild->ResetSecondaryWeaponBodyCondition(hyBody);
		g_pShuttleChild->ResetSecondaryWeaponBodyCondition(hyBody, FALSE);
	}
	else
	{
		// 2010-06-15 by shcho&hslee ��ý��� - ���� ����Ʈ �߰�
		g_pShuttleChild->ResetPetWeaponBodyCondition(hyBody);
		// end 2010-06-15 by shcho&hslee ��ý��� - ���� ����Ʈ �߰�
	}
}

void CWeaponItemInfo::SendBattleAttack(MEX_TARGET_INFO TargetInfo, UINT nSkillNum,
									   D3DXVECTOR3 FirePosition)
{
	// 2016-01-02 by St0rmy, prevent sending Attack packets in cities to prevent crashes 
	if (IS_CITY_MAP_INDEX(g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex))
		return;

	MSG_FC_BATTLE_ATTACK sMsg;
	sMsg.SkillNum = nSkillNum;
	sMsg.AttackType = m_nAttackMode;
	sMsg.TargetInfo = TargetInfo;
	sMsg.FirePosition = FirePosition;
	g_pFieldWinSocket->SendMsg(T_FC_BATTLE_ATTACK, (char*)&sMsg, sizeof(sMsg));
}

void CWeaponItemInfo::ReleaseAllUsingToggleWeapon()
{
	if( m_bUseToggleWeapon )
	{ 
		if(m_pItemInfo->Kind == ITEMKIND_SHIELD)
		{
			SendUseShield();
		}
		else if(m_pItemInfo->Kind == ITEMKIND_DECOY )
		{
			SendUseDecoy();
		}
	}	
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			CWeaponItemInfo::CheckWarpGateZone(D3DXVECTOR3 vPos)
/// \brief		����� �Ÿ��� ��������Ʈ�� ���°�?
/// \author		jschoi
/// \date		2005-03-08 ~ 2005-03-08
/// \warning	
///				
/// \param		PK���ɸ��̰ų� ������������ �ƴϸ� ������ ��������Ʈ ���õ�. TRUE
/// \return		vPos ��ó�� ��������Ʈ�� ������ TRUE, ��������Ʈ�� ������ FALSE
///////////////////////////////////////////////////////////////////////////////
BOOL CWeaponItemInfo::CheckWarpGateZone(D3DXVECTOR3 vPos)
{
	if( g_pShuttleChild &&
		g_pShuttleChild->m_pPkNormalTimer &&
		(IsPkEnableMap(g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex) ||
		g_pShuttleChild->m_pPkNormalTimer->IsCityWar()) )
	{
		CObjectChild* pObj = g_pScene->FindWarpGateByPosition(vPos,CHECK_WARP_GATE_DISTANCE);
		if(pObj == NULL)
		{
			return TRUE;
		}
		return FALSE;	
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			CWeaponItemInfo::SortTargetList()
/// \brief		Ÿ�� ����Ʈ ����
/// \author		ispark
/// \date		2006-02-01 ~ 2006-02-01
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CWeaponItemInfo::SortTargetList()
{
	sort(m_vecTargetOrderList.begin(), m_vecTargetOrderList.end(), sort_List());
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		1�� ���� Ÿ�� ����Ʈ ����
/// \author		// 2007-05-16 by bhsohn 1������ Ÿ�� ó��
/// \date		2007-05-16 ~ 2007-05-16
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CWeaponItemInfo::PrimarySortTargetList()
{
	if(g_pShuttleChild->m_pOrderTarget && ATTACK_AVAILABLE_STATE(g_pShuttleChild->m_pOrderTarget->m_dwState))
	{
		int nTargetIdx = g_pScene->FindClientIndexByUnitData((CUnitData*)g_pShuttleChild->m_pOrderTarget);
		ASSERT_ASSERT( nTargetIdx > 0 );

		// �ӽ� ���� �ʱ�ȭ
		m_vecTmpTargetOrderList.clear();	

		vector<stTargetList> :: iterator itList = m_vecTargetOrderList.begin();
		while(itList != m_vecTargetOrderList.end())
		{
			// ���� Ÿ�� ��� �ִ°��� ���� ������ �ű��.
			if(nTargetIdx == itList->nTargetIndex)
			{
				m_vecTmpTargetOrderList.push_front(*itList);
			}
			else
			{
				m_vecTmpTargetOrderList.push_back(*itList);
			}
			itList++;
		}

		m_vecTargetOrderList.clear();

		deque<stTargetList> :: iterator itTmpList = m_vecTmpTargetOrderList.begin();
		
		while(itTmpList != m_vecTmpTargetOrderList.end())
		{
			m_vecTargetOrderList.push_back(*itTmpList);

			itTmpList++;
		}
	}	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CWeaponItemInfo::DelTargetSecondary()
/// \brief		2�� ���� Ÿ�� ����
/// \author		ispark
/// \date		2006-09-08 ~ 2006-09-08
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CWeaponItemInfo::DelTargetSecondary()
{
	if(!g_pScene->m_pWeaponData)
		return;
	CWeapon * pNode = (CWeapon *)g_pScene->m_pWeaponData->m_pChild;
	while(pNode)
	{
		if( (pNode->m_dwPartType == _MISSILE || pNode->m_dwPartType == _ROCKET ) &&
			g_pShuttleChild->m_myShuttleInfo.ClientIndex == ((CWSlowData*)pNode)->m_nClientIndex)
		{
			((CWSlowData*)pNode)->m_pTarget = NULL;
		}

		pNode = (CWeapon *)pNode->m_pNext;
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CWeaponItemInfo::DelTargetIndex(int nTargetIndex)
/// \brief		
/// \author		ispark
/// \date		2006-12-08 ~ 2006-12-08
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CWeaponItemInfo::DelTargetIndex(int nTargetIndex)
{
	// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
// 	vector<int>::iterator it = m_vecTargetIndex.begin();
// 	while( it != m_vecTargetIndex.end() )
// 	{
// 		if(*it == nTargetIndex)
// 		{
// 			m_vecTargetIndex.erase(it);
// 			break;
// 		}
// 
// 		it++;
// 	}
	 	vector<TARGET_DATA>::iterator it = m_vecTargetIndexData.begin();
	 	while( it != m_vecTargetIndexData.end() )
	 	{
			if((*it).nTargetIndex == nTargetIndex)
	 		{
	 			m_vecTargetIndexData.erase(it);
			break;
		}

		it++;
	}
	// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CWeaponItemInfo::DelTargetIndex(int nTargetIndex)
/// \brief		
/// \author		// 2008-09-22 by bhsohn EP3 ĳ���� â
/// \date		2008-09-22 ~ 2008-09-22
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
CItemInfo *	CWeaponItemInfo::GetClassItemInfo()
{
	return m_pItemInfo;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CWeaponItemInfo::DelTargetIndex(int nTargetIndex)
/// \brief		�Ǿ�� = ���Ȱ�+�����Ǿ
/// \author		// 2008-09-22 by bhsohn EP3 ĳ���� â
/// \date		2008-09-22 ~ 2008-09-22
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
float CWeaponItemInfo::GetStatPierce()
{
	Stat_t	nAttackPart = g_pShuttleChild->m_myShuttleInfo.TotalGearStat.AttackPart;	
	float fStatPierce = CAtumSJ::GetLevelStatValue(min(COUNT_MAX_STAT_POINT,nAttackPart))->AttackPart_PierceAttackProbability;
	
	//2011-11-03 by hsson �ڷ��� ���� ���� �Ǿ�� ����� �ȳ����� ���� ����
	//float fStatPierceRate = ((float)fStatPierce / (float)PROB256_MAX_VALUE *100.0f);
	float fStatPierceRate = fStatPierce;
	//end 2011-11-03 by hsson �ڷ��� ���� ���� �Ǿ�� ����� �ȳ����� ���� ����

	float fResistance = 0.0f;
	float fResistanceRate = 0.0f;
	float fTotPierceRate = 0.0f;
	ITEM* pItem = m_pItemInfo->GetRealItemInfo();
	if(pItem)	
	{
		fResistance = pItem->FractionResistance;
		// 2010-07-28 by dgwoo Ȯ�� ���� ���� (255 => 100%)
		//fResistanceRate = ((float)fResistance / (float)PROB256_MAX_VALUE *100.0f);	
		fResistanceRate = FloatSecRangeSharp(fResistance);// 2008-03-19 by bhsohn FLOAT�� ������ �Ͽ� ���

	}	
	// 2008-03-19 by bhsohn FLOAT�� ������ �Ͽ� ���
	fStatPierceRate = FloatSecRangeSharp(fStatPierceRate);	

	fTotPierceRate = fStatPierceRate+fResistanceRate;	

	if(fTotPierceRate > 0)
	{
		return fTotPierceRate;
	}
	return 0.0;

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		����, ���� �Ǿ�� üũ
/// \author		// 2009-02-16 by bhsohn ����, ���� �Ǿ �� �Ⱥ��̴� ���� ó��
/// \date		2009-02-16 ~ 2009-02-16
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
float CWeaponItemInfo::GetPreSufFixItemInfoRate(int nDesParameter)
{
	if(NULL == m_pItemInfo)
	{
		return 0.0f;
	}
	float fPreSufFixPierce = 0.0f;
	float fPreSufFixPierceRate = 0.0f;
	RARE_ITEM_INFO *pRefPrefixRareInfo = m_pItemInfo->GetPrefixRareInfo();
	RARE_ITEM_INFO *pRefSuffixRareInfo = m_pItemInfo->GetSuffixRareInfo();

	if(pRefPrefixRareInfo)
	{
		for(int i=0; i<SIZE_DES_PARAM_PER_RARE_ITEM_INFO; i++)
		{
			if( pRefPrefixRareInfo->DesParameter[i] == nDesParameter)
			{
				fPreSufFixPierce += pRefPrefixRareInfo->ParameterValue[i];
			}
		}

	}
	if(pRefSuffixRareInfo)
	{
		for(int i=0; i<SIZE_DES_PARAM_PER_RARE_ITEM_INFO; i++)
		{
			if( pRefSuffixRareInfo->DesParameter[i] == nDesParameter)
			{
				fPreSufFixPierce += pRefSuffixRareInfo->ParameterValue[i];
			}
		}
	}
	if(fPreSufFixPierce > 0)
	{
		// 2010-07-28 by dgwoo Ȯ�� ���� ���� (255 => 100%)
		//fPreSufFixPierceRate = ((float)fPreSufFixPierce / (float)PROB256_MAX_VALUE *100.0f);	
		fPreSufFixPierceRate = FloatSecRangeSharp(fPreSufFixPierce);// FLOAT�� ������ �Ͽ� ���

	}	
	if(fPreSufFixPierceRate > 0)
	{
		return fPreSufFixPierceRate;
	}
	return 0.0;

}


///////////////////////////////////////////////////////////////////////////////
/// \fn			void CWeaponItemInfo::DelTargetIndex(int nTargetIndex)
/// \brief		
/// \author		// 2008-09-22 by bhsohn EP3 ĳ���� â
/// \date		2008-09-22 ~ 2008-09-22
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
float CWeaponItemInfo::GetPrimaryEnchantPierce()
{
	if(NULL == m_pItemInfo)
	{
		return 0.0f;
	}
	CItemInfo* pSelectItem = g_pStoreData->FindItemInInventoryByUniqueNumber( m_pItemInfo->UniqueNumber);

	if(NULL == pSelectItem)
	{
		return 0.0f;
	}	
	CParamFactor *	pRefEnchant = pSelectItem->GetEnchantParamFactor();
	if(NULL == pRefEnchant)
	{		
		return 0.0f;
	}
	
	float fPierce = pRefEnchant->pfm_PIERCE_UP_01;
	// 2010-07-28 by dgwoo Ȯ�� ���� ���� (255 => 100%)
	//fPierce = ((float)fPierce / (float)PROB256_MAX_VALUE *100.0f);
	// 2008-03-19 by bhsohn FLOAT�� ������ �Ͽ� ���	
	fPierce = FloatSecRangeSharp(fPierce);
	if(fPierce > 0)
	{
		return fPierce;
	}
	return 0.0;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CWeaponItemInfo::DelTargetIndex(int nTargetIndex)
/// \brief		
/// \author		// 2008-09-22 by bhsohn EP3 ĳ���� â
/// \date		2008-09-22 ~ 2008-09-22
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
float CWeaponItemInfo::GetSecondaryEnchantPierce()
{
	if(NULL == m_pItemInfo)
	{
		return 0.0f;
	}
	CItemInfo* pSelectItem = g_pStoreData->FindItemInInventoryByUniqueNumber( m_pItemInfo->UniqueNumber);

	if(NULL == pSelectItem)
	{
		return 0.0f;
	}	
	CParamFactor *	pRefEnchant = pSelectItem->GetEnchantParamFactor();
	if(NULL == pRefEnchant)
	{
		return 0.0f;
	}

	float fPierce = pRefEnchant->pfm_PIERCE_UP_02;
	// 2010-07-28 by dgwoo Ȯ�� ���� ���� (255 => 100%)
	//fPierce = ((float)fPierce / (float)PROB256_MAX_VALUE *100.0f);
	// 2008-03-19 by bhsohn FLOAT�� ������ �Ͽ� ���		
	fPierce = FloatSecRangeSharp(fPierce);
	if(fPierce > 0)
	{
		return fPierce;
	}
	return 0.0;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			void CWeaponItemInfo::DelTargetIndex(int nTargetIndex)
/// \brief		
/// \author		// 2008-09-22 by bhsohn EP3 ĳ���� â
/// \date		2008-09-22 ~ 2008-09-22
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
float CWeaponItemInfo::GetTotalPierce(BOOL bIsPrimary)
{	
	if (!m_pCharacterParamFactor) return 0.0f;	

	auto fStatPierceRate = GetStatPierce();
	
	auto fEqPierceRate = bIsPrimary ?
		g_pShuttleChild->GetShuttleParamFactor()->pfm_PIERCE_UP_01:
		g_pShuttleChild->GetShuttleParamFactor()->pfm_PIERCE_UP_02;


	// 2010-07-28 by dgwoo Ȯ�� ���� ���� (255 => 100%)
	//fEqPierceRate = ((float)fEqPierce / (float)PROB256_MAX_VALUE *100.0f);
	

	// ������ ���� �Ǿ ��
	auto fItemPierceRate = 0.0f;
	
	if(m_pItemInfo)
	{
		auto pSelectItem = g_pStoreData->FindItemInInventoryByUniqueNumber(m_pItemInfo->UniqueNumber);
			
		if (pSelectItem)
		{
			auto pRefEnchant = pSelectItem->GetEnchantParamFactor();
				
			if (pRefEnchant)
			{
				fItemPierceRate = bIsPrimary ? pRefEnchant->pfm_PIERCE_UP_01 : pRefEnchant->pfm_PIERCE_UP_02;

				// 2010-07-28 by dgwoo Ȯ�� ���� ���� (255 => 100%)
				//fItemPierceRate = ((float)fItemPierce / (float)PROB256_MAX_VALUE *100.0f);
				// 2008-03-19 by bhsohn FLOAT�� ������ �Ͽ� ���			

				fItemPierceRate = FloatSecRangeSharp(fItemPierceRate);
			}
		}				
	}				

	// 2008-03-19 by bhsohn FLOAT�� ������ �Ͽ� ���												
	fStatPierceRate = FloatSecRangeSharp(fStatPierceRate);
	fEqPierceRate = FloatSecRangeSharp(fEqPierceRate);	

	// 2009-02-16 by bhsohn ����, ���� �Ǿ �� �Ⱥ��̴� ���� ó��	
	//fTotalPeierceRate = fStatPierceRate+fEqPierceRate+fItemPierceRate;	

	auto fPreSufPierceRate = bIsPrimary ? GetPreSufFixItemInfoRate(DES_PIERCE_UP_01) : GetPreSufFixItemInfoRate(DES_PIERCE_UP_02);
	
	auto fTotalPeierceRate = fStatPierceRate+fEqPierceRate + fItemPierceRate+ fPreSufPierceRate;


	return fTotalPeierceRate;

}