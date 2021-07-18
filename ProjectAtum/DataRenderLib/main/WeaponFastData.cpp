// WeaponFastData.cpp: implementation of the CWeaponFastData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WeaponFastData.h"
#include "AtumProtocol.h"
#include "EnemyData.h"
#include "MonsterData.h"
#include "AtumApplication.h"
#include "ShuttleChild.h"
#include "SceneData.h"
#include "Background.h"
#include "INFGameMain.h"
#include "INFAttackDirection.h"
#include "Camera.h"
#include "ObjRender.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����
// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
// CWeaponFastData::CWeaponFastData(CAtumData * pAttack, 
// 								 ITEM * pWeaponITEM, 
// 								 ATTACK_DATA & attackData )
//CWeaponFastData::CWeaponFastData( CAtumData* pAttack, ITEM* pWeaponITEM, ATTACK_DATA& attackData, ITEM* pEffectItem /* = NULL */)
CWeaponFastData::CWeaponFastData( CAtumData* pAttack, ITEM* pWeaponITEM, ATTACK_DATA& attackData, ITEM* pEffectItem, int LoadingPriority)
// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
//end 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����
{
// 2010. 11. 25 by jskim A��� ������� �߻� ��ġ ���� : ī�޶��� ��ġ�� ���� ���鿡�� ��� ����
	D3DXMATRIX temp, temp2, temp3;
	D3DXMatrixIdentity(&temp);
	D3DXMatrixIdentity(&temp2);
	D3DXMatrixIdentity(&temp3);
// end 2010. 11. 25 by jskim A��� ������� �߻� ��ġ ���� : ī�޶��� ��ġ�� ���� ���鿡�� ��� ����

	m_pAttacker = pAttack;
	m_pCharacterInfo = NULL;
	
	m_fWeaponSpeed = MAX_WEAPON_SPEED;
	
	m_dwPartType = _FASTDATA;
	m_fWeaponLifeTime = 2.0f;
	m_nSkillNum = attackData.AttackData.SkillNum;
	
	m_pTarget = (CAtumData*)g_pScene->FindUnitDataByClientIndex( attackData.AttackData.TargetInfo.TargetIndex );
	m_bFireType = attackData.bZigZagWeapon;
	
	if(m_bFireType==0)
	{
		// 2010-06-15 by shcho&hslee ��ý��� - ���� ��ġ
		if(g_pShuttleChild->m_bAttackMode != _SIEGE)
		{
			if(attackData.AttackData.AttackType == ATT_TYPE_PET_GENERAL)
			{
				m_vPos = m_pAttacker->m_vPetLeftPos;
			}
			else
			{
				m_vPos = m_pAttacker->m_vLWPos;
			}		
		}
		else
		{
			// 2010. 12. 27 by jskim A��� ������� �߻� ��ġ ���� : ���� ����ȭ ���� ����
			if( m_pAttacker->m_dwPartType == _SHUTTLE )
			{
				D3DXMatrixIdentity(&temp);
				D3DXMatrixIdentity(&temp2);
				D3DXMatrixIdentity(&temp3);
				// 2010. 11. 25 by jskim A��� ������� �߻� ��ġ ���� : ī�޶��� ��ġ�� ���� ���鿡�� ��� ����
				g_pCamera->m_vCamCurrentPos;
				D3DXMatrixLookAtRH( &temp, &(g_pD3dApp->m_pCamera->GetEyePt()), &(g_pD3dApp->m_pCamera->GetEyePt() + g_pShuttleChild->m_vMouseDir), &g_pShuttleChild->m_vUp);
				// end 2010. 11. 25 by jskim A��� ������� �߻� ��ġ ���� : ī�޶��� ��ġ�� ���� ���鿡�� ��� ����
				D3DXMatrixInverse( &temp, NULL, &temp );
				
				if(attackData.AttackData.AttackType == ATT_TYPE_PET_GENERAL)
				{
					m_vPos = m_pAttacker->m_vPetLeftPos;
				}
				else
				{
				// 2010. 11. 25 by jskim A��� ������� �߻� ��ġ ���� : ī�޶��� ��ġ�� ���� ���鿡�� ��� ����
					temp3._41 = g_pShuttleChild->m_PrimaryAttack.vSideBackPos.x;
					temp3._42 = g_pShuttleChild->m_PrimaryAttack.vSideBackPos.y;
					temp3._43 = g_pShuttleChild->m_PrimaryAttack.vSideBackPos.z;
					temp2 = temp3 * temp;
				// end 2010. 11. 25 by jskim A��� ������� �߻� ��ġ ���� : ī�޶��� ��ġ�� ���� ���鿡�� ��� ����
					m_vPos.x = temp2._41;
					m_vPos.y = temp2._42;
					m_vPos.z = temp2._43;
				}
			}
			else
			{
				D3DXMATRIX temp, temp2;
				D3DXMatrixIdentity(&temp);
				D3DXMatrixIdentity(&temp2);		
				
				D3DXMatrixLookAtRH( &temp, &(g_pShuttleChild->m_vPos), &(g_pShuttleChild->m_vPos + g_pShuttleChild->m_vMouseDir), &g_pShuttleChild->m_vUp);
				D3DXMatrixInverse( &temp, NULL, &temp );
				
				if(attackData.AttackData.AttackType == ATT_TYPE_PET_GENERAL)
				{
					m_vPos = m_pAttacker->m_vPetLeftPos;
				}
				else
				{
					m_vPos = m_pAttacker->m_vLWPos;
				}
			}

		}
	}
	else
	{	
		if(g_pShuttleChild->m_bAttackMode != _SIEGE)
		{
			if(attackData.AttackData.AttackType == ATT_TYPE_PET_GENERAL)
			{
				m_vPos = m_pAttacker->m_vPetRightPos;	
			}
			else
			{
				m_vPos = m_pAttacker->m_vRWPos;
			}		
		}
		else
		{
			// 2010. 11. 25 by jskim A��� ������� �߻� ��ġ ���� : ���� ����ȭ ���� ����
			if( m_pAttacker->m_dwPartType == _SHUTTLE )
			{
				D3DXMatrixIdentity(&temp);
				D3DXMatrixIdentity(&temp2);
				D3DXMatrixIdentity(&temp3);

				// 2010. 11. 25 by jskim A��� ������� �߻� ��ġ ���� : ī�޶��� ��ġ�� ���� ���鿡�� ��� ����
				D3DXMatrixLookAtRH( &temp, &(g_pD3dApp->m_pCamera->GetEyePt()), &(g_pD3dApp->m_pCamera->GetEyePt() + g_pShuttleChild->m_vMouseDir), &g_pShuttleChild->m_vUp);
				// end 2010. 11. 25 by jskim A��� ������� �߻� ��ġ ���� : ī�޶��� ��ġ�� ���� ���鿡�� ��� ����
				D3DXMatrixInverse( &temp, NULL, &temp );	
				if(attackData.AttackData.AttackType == ATT_TYPE_PET_GENERAL)
				{
		 			temp2 = g_pShuttleChild->m_pMatPetPosition[1] * temp;
				}
				else
				{
					// 2010. 11. 25 by jskim A��� ������� �߻� ��ġ ���� : ī�޶��� ��ġ�� ���� ���鿡�� ��� ����
 					temp3._41 = -g_pShuttleChild->m_PrimaryAttack.vSideBackPos.x;
 					temp3._42 = g_pShuttleChild->m_PrimaryAttack.vSideBackPos.y;
 					temp3._43 = g_pShuttleChild->m_PrimaryAttack.vSideBackPos.z;
					temp2 = temp3 * temp;
					// end 2010. 11. 25 by jskim A��� ������� �߻� ��ġ ���� : ī�޶��� ��ġ�� ���� ���鿡�� ��� ����
				}
				m_vPos.x = temp2._41;
				m_vPos.y = temp2._42;
				m_vPos.z = temp2._43;
			}
			else
			{
				D3DXMatrixIdentity(&temp);
				D3DXMatrixIdentity(&temp2);
				
				D3DXMatrixLookAtRH( &temp, &(g_pShuttleChild->m_vPos), &(g_pShuttleChild->m_vPos + g_pShuttleChild->m_vMouseDir), &g_pShuttleChild->m_vUp);
				D3DXMatrixInverse( &temp, NULL, &temp );	
				if(attackData.AttackData.AttackType == ATT_TYPE_PET_GENERAL)
				{
					m_vPos = m_pAttacker->m_vPetRightPos;
				}
				else
				{
					m_vPos = m_pAttacker->m_vRWPos;
				}
			}
		}
	}
	// end 2010-06-15 by shcho&hslee ��ý��� - ���� ��ġ
	// end 2010. 12. 27 by jskim A��� ������� �߻� ��ġ ���� : ���� ����ȭ ���� ����
	
	// 2004-10-12 by jschoi
	m_vEffectPos = m_pAttacker->m_vPos;
	
	// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
	D3DXVECTOR3 nMultiPos;
	// 2011. 09. 28 by jskim �� Ÿ�� �ý��� ���� ����( �ɽ��� ���� )
	//if(m_pTarget && ((CMonsterData*)m_pTarget)->m_vecvmultiData.size() > 0)
	if(m_pTarget &&
		m_pTarget->m_dwPartType == _MONSTER &&
		((CMonsterData*)m_pTarget)->m_vecvmultiData.size() > 0)
	// end 2011. 09. 28 by jskim �� Ÿ�� �ý��� ���� ����( �ɽ��� ���� )
	{
		nMultiPos = ((CMonsterData*)m_pTarget)->GetMultiPos( attackData.AttackData.TargetInfo.MultiTargetIndex );
	}
	else if(m_pTarget)
	{
		nMultiPos = m_pTarget->m_vPos;
	}
	// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
	if(m_pTarget)
	{
		// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
		//m_vTargetPos = m_pTarget->m_vPos + m_vPos - m_pAttacker->m_vPos;
		m_vTargetPos = nMultiPos + m_vPos - m_pAttacker->m_vPos;
		// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
		m_bNeedCheckCollision = TRUE;
	}
	else if(m_pAttacker->m_dwPartType == _SHUTTLE)
	{
		if(IS_DT(((CShuttleChild *)m_pAttacker)->m_myShuttleInfo.UnitKind))
		{
			m_vTargetPos = m_vPos + 5000.0f*((CShuttleChild *)m_pAttacker)->m_vWeaponVel;
		}
		else
		{
			m_vTargetPos = m_vPos + 5000.0f*((CShuttleChild *)m_pAttacker)->m_vVel;
		}
		m_bNeedCheckCollision = TRUE;
	}
	else if(m_pAttacker->m_dwPartType == _ENEMY)
	{
		if(IS_DT(((CEnemyData *)m_pAttacker)->m_infoCharacter.CharacterInfo.UnitKind))
		{
			// ������ ���߿� m_vWeaponVel �߰��� m_vWeaponVel �Ʒ� �ڵ�� ������ ��
			m_vTargetPos = m_vPos + 5000.0f*((CEnemyData *)m_pAttacker)->m_vWeaponVel;
			m_bNeedCheckCollision = TRUE;			
			//m_vTargetPos = A2DX(attackData.AttackData.TargetInfo.TargetPosition) + m_vPos - m_pAttacker->m_vPos;
			//m_bNeedCheckCollision = FALSE;			
		}
		else
		{
			m_vTargetPos = m_vPos + 5000.0f*((CEnemyData *)m_pAttacker)->m_vVel;
			m_bNeedCheckCollision = TRUE;
		}
	}
	else
	{
		m_vTargetPos = A2DX(attackData.AttackData.TargetInfo.TargetPosition) + m_vPos - m_pAttacker->m_vPos;
		m_bNeedCheckCollision = FALSE;
	}

// 2010-06-15 by shcho&hslee ��ý��� - ���� ��ġ	
	if( m_pAttacker->m_dwPartType == _SHUTTLE && 
		IS_DT(((CShuttleChild *)m_pAttacker)->m_myShuttleInfo.UnitKind) &&
		attackData.AttackData.AttackType != ATT_TYPE_PET_GENERAL &&
		g_pShuttleChild->m_bAttackMode != _SIEGE)
	{
		D3DXVec3Normalize(&((CShuttleChild *)m_pAttacker)->m_vWeaponVel,&((CShuttleChild *)m_pAttacker)->m_vWeaponVel);
		CAppEffectData * pEffect = new CAppEffectData(m_pAttacker,RC_EFF_AGEAR_FIRE,m_vPos);
		pEffect = (CAppEffectData *)g_pD3dApp->m_pEffectList->AddChild(pEffect);
	}
// 	if( m_pAttacker->m_dwPartType == _SHUTTLE && attackData.AttackData.AttackType == ATT_TYPE_PET_GENERAL)
// 	{
// 		m_pCharacterInfo->GetEffectMatrix(BODYCON_MON_PREATTACK2_MASK, RC_EFF_PRIMARY_RIGHT_POSITION)
// 		D3DXVec3Normalize(&((CShuttleChild *)m_pAttacker)->m_vWeaponVel,&((CShuttleChild *)m_pAttacker)->m_vWeaponVel);
// 		CAppEffectData * pEffect = new CAppEffectData(m_pAttacker,RC_EFF_PET_FIRE,m_vPos);
// 		pEffect = (CAppEffectData *)g_pD3dApp->m_pEffectList->AddChild(pEffect);
// 	} 
// end 2010-06-15 by shcho&hslee ��ý��� - ���� ��ġ	

	if( (
		 m_pAttacker->m_dwPartType == _SHUTTLE && 
		 IS_DT(((CShuttleChild *)m_pAttacker)->m_myShuttleInfo.UnitKind) &&
		 g_pShuttleChild->m_bAttackMode != _SIEGE
		)
		||
		(
		 m_pAttacker->m_dwPartType == _ENEMY &&
		 IS_DT(((CEnemyData *)m_pAttacker)->m_infoCharacter.CharacterInfo.UnitKind)
		) 
	  )
	{
		D3DXVec3Normalize(&((CAtumData *)m_pAttacker)->m_vWeaponVel,&((CAtumData *)m_pAttacker)->m_vWeaponVel);
		// 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����
		//CAppEffectData * pEffect = new CAppEffectData(m_pAttacker,RC_EFF_AGEAR_FIRE,m_vPos);
// 		CAppEffectData * pEffect = new CAppEffectData(m_pAttacker,RC_EFF_AGEAR_FIRE,m_vPos, 0, LoadingPriority);
// 		//end 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����
// 		pEffect = (CAppEffectData *)g_pD3dApp->m_pEffectList->AddChild(pEffect);
	}


	// 2009. 07. 07 by ckPark �κ���� ��û����(�Ѹ�, ����ȭ��, ����, A�������)
	// �κ� �Ƹ� BMI���� �߻� ����Ʈ
	if( 
		(
			m_pAttacker->m_dwPartType == _SHUTTLE && 
			!( IS_DT( ( (CShuttleChild*)m_pAttacker )->m_myShuttleInfo.UnitKind) ) &&
			( (CShuttleChild*)m_pAttacker )->IsRobotArmor()
		)
		||
		(
			m_pAttacker->m_dwPartType == _ENEMY &&
			!( IS_DT( ( (CEnemyData*)m_pAttacker )->m_infoCharacter.CharacterInfo.UnitKind ) ) &&
			( (CEnemyData*)m_pAttacker )->IsRobotArmor()
		) 
	)
	{
		D3DXVec3Normalize(&((CAtumData *)m_pAttacker)->m_vWeaponVel, &((CAtumData *)m_pAttacker)->m_vWeaponVel);
		// 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����
		//CAppEffectData* pEffect = new CAppEffectData(m_pAttacker, RC_EFF_ROBOTAMOR_FIRE_EFFECT, m_vPos);
		CAppEffectData* pEffect = new CAppEffectData(m_pAttacker, RC_EFF_ROBOTAMOR_FIRE_EFFECT, m_vPos, 0, LoadingPriority);
		//end 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����
		pEffect = (CAppEffectData*)g_pD3dApp->m_pEffectList->AddChild(pEffect);

		DbgOutA( "Effect Error : RC_EFF_ROBOTAMOR_FIRE_EFFECT		1100084\n" );

		if(m_bFireType==0)
			pEffect->m_nFirePos = CAppEffectData::LEFT;
		else
			pEffect->m_nFirePos = CAppEffectData::RIGHT;
	}
	// end 2009. 07. 07 by ckPark �κ���� ��û����(�Ѹ�, ����ȭ��, ����, A�������)


	m_vStartPos = m_vPos;
	m_vVel = m_vTargetPos - m_vPos;
	
	D3DXVec3Normalize(&m_vVel,&m_vVel);
	
	m_fTargetDistance = D3DXVec3Length(&(m_vStartPos - m_vTargetPos));
	
	// �߽ɺ��� �ణ �տ� �±� ���ؼ�...
	if(m_fTargetDistance > 5.0f)
		m_fTargetDistance -= 5.0f;
	m_dwWeaponState=_NORMAL;
	m_nItemIndex = 0;
	m_nWeaponItemNumber = pWeaponITEM->SourceIndex;							// 2005-08-23 by ispark

	// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����

	// ����Ʈ �������� �ִٸ� �װ����� ����
	if( pEffectItem )
		m_nWeaponItemNumber = pEffectItem->SourceIndex;

	// end  2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
	
	m_vUp = D3DXVECTOR3(0,1,0);
	D3DXMatrixLookAtRH( &m_mMatrix, &(m_vPos), &(m_vPos + m_vVel), &m_vUp);
	D3DXMatrixInverse( &m_mMatrix, NULL, &m_mMatrix );
	
	char buf[256];
	// 2004-10-12 by jschoi
	if(m_nSkillNum != 0)
	{
		ChangeBodyConditionForSkillEffect(m_nSkillNum,BODYCON_BULLET_MASK);
	}
	else
	{
		wsprintf(buf,"%08d",m_nWeaponItemNumber);
		LoadCharacterEffect(buf);
		if(m_pCharacterInfo)
		{
 			// 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����
			m_pCharacterInfo->m_LoadingPriority = LoadingPriority;
 			//end 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����
			m_pCharacterInfo->SetAllBodyConditionMatrix(m_mMatrix);
			m_pCharacterInfo->ChangeBodyCondition(BODYCON_BULLET_MASK);
		}
		else
		{
			// 2005-08-03 by ispark
//			// temporary item
//			LoadCharacterEffect("01200016");
//			if(m_pCharacterInfo)
//			{
//				m_pCharacterInfo->SetAllBodyConditionMatrix(m_mMatrix);
//				m_pCharacterInfo->ChangeBodyCondition(BODYCON_BULLET_MASK);
//			}
//			else
//			{
//				g_pD3dApp->NetworkErrorMsgBox(STRMSG_C_050512_0001);
//				return;
//			}		
			m_bUsing = FALSE;
		}
		// 2009-03-30 by bhsohn ��¡�� ����Ʈ ���� ����
		//DeleteChargingStateSkillEffect();
	}
//	wsprintf(buf,"%08d",m_nWeaponItemNumber);
//	LoadCharacterEffect(buf);
//	if(m_pCharacterInfo)
//	{
//		m_pCharacterInfo->SetAllBodyConditionMatrix(m_mMatrix);
//		m_pCharacterInfo->ChangeBodyCondition(BODYCON_BULLET_MASK);
//		// 2004-10-12 by jschoi
//		if(m_nSkillNum != 0)
//		{
//			ChangeBodyConditionForSkillEffect(m_nSkillNum,BODYCON_BULLET_MASK);
//		}
//	}
	SetShuttleChildOrderTarget();	
}

CWeaponFastData::~CWeaponFastData()
{
	FLOG( "~CWeaponFastData()" );
	if(m_pCharacterInfo)//�߰�
	{
		m_pCharacterInfo->InvalidateDeviceObjects();
		m_pCharacterInfo->DeleteDeviceObjects();
		util::del(m_pCharacterInfo);
	}
}

void CWeaponFastData::Tick()
{
	FLOG( "CWeaponFastData::Tick()" );
	float fElapsedTime = g_pD3dApp->GetElapsedTime();
	// 2007-02-02 by bhsohn 1�� ���� ���� ������ �� �������� ���� ó��
	if(g_pSOption->sLowQuality)
	{		
		if((m_nSkillNum == 0)
			&& !(m_pAttacker == g_pShuttleChild || m_pTarget == g_pShuttleChild))
		{
			m_bUsing = FALSE;
			return;
		}
	}
 // end 2007-02-02 by bhsohn 1�� ���� ���� ������ �� �������� ���� ó��
	if(m_pAttacker == NULL)
	{
		m_bUsing = FALSE;
		return;
	}
	if( m_dwWeaponState == _EXPLODING ) // exploding state
	{
		if(m_pTarget == g_pShuttleChild)
		{
			//			if(m_pTarget == g_pShuttleChild)
			//			{
			D3DXPLANE xyPlane,yzPlane;
			float distance,distance2;
			
			D3DXVECTOR3 vPlayerPos = g_pShuttleChild->m_vPos;
			D3DXVECTOR3 vCheckVec = m_pAttacker->m_vPos - vPlayerPos;
			//D3DXVec3Normalize( &vCheckVec, &vCheckVec);
			D3DXVECTOR3 vUp = g_pD3dApp->m_pCamera->GetUpVec();
			D3DXVECTOR3 vView = g_pD3dApp->m_pCamera->GetViewDir();
			D3DXVECTOR3 vSide = g_pD3dApp->m_pCamera->GetCross();
			
			xyPlane.a = vView.x;
			xyPlane.b = vView.y;
			xyPlane.c = vView.z;
			xyPlane.d = (vPlayerPos.x*vView.x)+(vPlayerPos.y*vView.y)+(vPlayerPos.z*vView.z);
			
			yzPlane.a = vSide.x;
			yzPlane.b = vSide.y;
			yzPlane.c = vSide.z;
			yzPlane.d = (vPlayerPos.x*vSide.x)+(vPlayerPos.y*vSide.y)+(vPlayerPos.z*vSide.z);
			
			
			
			distance =  xyPlane.a * m_pAttacker->m_vPos.x + 
				xyPlane.b * m_pAttacker->m_vPos.y + 
				xyPlane.c * m_pAttacker->m_vPos.z - xyPlane.d;
			
			distance2 = yzPlane.a * m_pAttacker->m_vPos.x + 
				yzPlane.b * m_pAttacker->m_vPos.y + 
				yzPlane.c * m_pAttacker->m_vPos.z - yzPlane.d;
			
			
			if( distance < 0 )
			{
				D3DXVECTOR2 v2Up, v2Check;
				v2Up.x = vUp.x;
				v2Up.y = vUp.y;
				
				v2Check.x = vCheckVec.x;
				v2Check.y = vCheckVec.y;
				
				D3DXVec2Normalize( &v2Up, &v2Up );
				D3DXVec2Normalize( &v2Check, &v2Check );
				//D3DXVec2Normalize
				
				float fDot = D3DXVec2Dot(&v2Up, &v2Check);
				float fAngle = ACOS( fDot );
				
				
				if( distance2 < 0 ) // ����
				{
					if( fAngle >= 0 && fAngle <= PI/8)
					{
						g_pGameMain->m_pAttackDirection->OnAttackDirection( 0 );
					}
					else if( fAngle > PI/8 && fAngle <= PI/8*3 )
					{
						g_pGameMain->m_pAttackDirection->OnAttackDirection( 1 );
					}
					else if( fAngle > PI/8*3 && fAngle <= PI/8*5  )
					{
						g_pGameMain->m_pAttackDirection->OnAttackDirection( 2 );
					}
					else if( fAngle > PI/8*5 && fAngle <= PI/8*7 )
					{
						g_pGameMain->m_pAttackDirection->OnAttackDirection( 3 );
					}
					else if( fAngle > PI/8*7 && fAngle <= PI )
					{
						g_pGameMain->m_pAttackDirection->OnAttackDirection( 4 );
					}
					else
					{
						int j=0;
						j++;
					}
					
				}
				else				// ������
				{
					if( fAngle >= 0 && fAngle <= PI/8)
					{
						g_pGameMain->m_pAttackDirection->OnAttackDirection( 0 );
					}
					else if( fAngle > PI/8 && fAngle <= PI/8*3 )
					{
						g_pGameMain->m_pAttackDirection->OnAttackDirection( 7 );
					}
					else if( fAngle > PI/8*3 && fAngle <= PI/8*5  )
					{
						g_pGameMain->m_pAttackDirection->OnAttackDirection( 6 );
					}
					else if( fAngle > PI/8*5 && fAngle <= PI/8*7 )
					{
						g_pGameMain->m_pAttackDirection->OnAttackDirection( 5 );
					}
					else if( fAngle > PI/8*7 && fAngle <= PI )
					{
						g_pGameMain->m_pAttackDirection->OnAttackDirection( 4 );
					}
					else
					{
						int j=0;
						j++;
					}
				}
				//				}
			}
		}
		if(m_pTarget)
		{
			if(!m_pTarget->m_bShielding)
			{
				// �����ϰ� ��ġ�� �����Ѵ�.
				D3DXVECTOR3 vVel;
				D3DXVec3Normalize(&vVel, &(m_pAttacker->m_vPos - m_pTarget->m_vPos));
				vVel = D3DXVECTOR3( vVel.x*((float)RANDI(0, 4)),vVel.y*((float)RANDI(0, 4)),vVel.z*((float)RANDI(0, 4)));
				m_vPos = m_pTarget->m_vPos + vVel;
				// 2004-10-12 by jschoi
				m_vEffectPos = m_vPos;
			}
			else	// ���� �ߵ� ���ΰ�� ��ǥ�� ����ũ�� ��ŭ���� �����Ѵ�.
			{// ���� �ߵ� ���϶� ���� Hit ����Ʈ �߰�
				D3DXVECTOR3 vVel;
				D3DXVec3Normalize(&vVel, &(m_pAttacker->m_vPos - m_pTarget->m_vPos));
				m_vPos = m_pTarget->m_vPos + vVel*SIZE_OF_SHIELD_EFFECT;
				// 2004-10-12 by jschoi
				m_vEffectPos = m_vPos;
				((CUnitData*)m_pTarget)->CreateSecondaryShieldDamage(m_pAttacker->m_vPos);
			}
		}
		SetBodyCondition(BODYCON_HIT_MASK);
		
		// 2004-10-12 by jschoi
		if(m_nSkillNum != 0)
		{
			ChangeBodyConditionForSkillEffect(m_nSkillNum,BODYCON_HIT_MASK);
		}

		m_dwWeaponState = _EXPLODED;
	} 
	else if(m_dwWeaponState == _NORMAL)
	{
		if(m_fWeaponLifeTime > 0.0f)
		{
			m_fWeaponLifeTime -= fElapsedTime;
		}
		
		if(m_fWeaponLifeTime <= 0.0f)
		{
			m_dwWeaponState = _EXPLODED;
			m_bUsing = FALSE;

			// 2004-10-12 by jschoi ��ų ����Ʈ �Ҹ�(���ܻ�Ȳ)
			if(m_nSkillNum != 0)
			{
				DeleteSkillEffect(m_nSkillNum);
			}
		}
		else
		{
			D3DXVECTOR3 vSide,vCamPos;
			D3DXMATRIX matTemp;
			D3DXVECTOR3 vDistance = m_vStartPos - m_vPos;
			if(m_pTarget)
			{
				if(m_pTarget->m_bShielding)
				{
					D3DXVECTOR3 vVel;
					D3DXVec3Normalize(&vVel, &(m_pAttacker->m_vPos - m_pTarget->m_vPos));
					vDistance += vVel*SIZE_OF_SHIELD_EFFECT;
				}
			}

			if(m_bNeedCheckCollision) 
			{
				float fMovingDistance = m_fWeaponSpeed*fElapsedTime;
				CheckWeaponCollision(vDistance, fMovingDistance);
			}

			if(m_fTargetDistance <= D3DXVec3Length(&vDistance))
			{
				m_vPos = m_vTargetPos;
				// 2004-10-12 by jschoi
				m_vEffectPos = m_vTargetPos;
				m_dwWeaponState = _EXPLODING;
			}
			m_vPos += m_fWeaponSpeed*m_vVel*fElapsedTime;
			m_vEffectPos += m_fWeaponSpeed*m_vVel*fElapsedTime;

//			if(m_fTargetDistance <= D3DXVec3Length(&vDistance))
//			{
//				m_vPos = m_vTargetPos;
//				m_dwWeaponState = _EXPLODING;
//				if(g_pScene->m_byMapType == MAP_TYPE_TUTORIAL)
//				{// ���� ��� �̹Ƿ� ���Ϳ� ������ ���
//					CMapMonsterIterator itMon = g_pScene->m_mapMonsterList.begin();
//					while(itMon != g_pScene->m_mapMonsterList.end())
//					{
//						if(D3DXVec3Length(&(m_vPos - itMon->second->m_vPos)) < 10.0f)
//						{
//							itMon->second->m_info.CurrentHP -= 10.0f;
//							if(itMon->second->m_info.CurrentHP <= 0.0f)
//							{
//								if(!COMPARE_BODYCON_BIT(itMon->second->GetCurrentBodyCondition(),BODYCON_DEAD_MASK))
//								{
//									if(g_pShuttleChild->m_pOrderTarget == itMon->second)
//										g_pShuttleChild->m_pOrderTarget = NULL;
//									//itMon->second->m_info.BodyCondition = BODYCON_DEAD_MASK;
//									itMon->second->ChangeBodyConditionFromServer(BODYCON_DEAD_MASK | BODYCON_EXPLOSION_MASK);
//									itMon->second->ChangeUnitState( _EXPLODING );
//									//itMon->second->m_dwState = _EXPLODING;
//								}
//							}
//							break;
//						}
//						itMon++;
//					}
//				}
//			}
//			// ������ �浹 ó��
//			if(m_vPos.y < g_pGround->CheckHeightMap(m_vPos))
//			{
//				m_pTarget = NULL;
//				m_dwWeaponState = _EXPLODING;
//			}
		}
	}
	else if(m_dwWeaponState == _EXPLODED)
	{
//		if(m_pTarget)//EXPLODING���� ó��
//			m_vPos = m_pTarget->m_vPos;
		if(m_pCharacterInfo)
		{
			if(!m_pCharacterInfo->IsUsing())
			{
				m_bUsing = FALSE;
			}
		}
		else
		{
			m_bUsing = FALSE;
		}
	}
	D3DXMatrixLookAtRH( &m_mMatrix, &(m_vPos), &(m_vPos + m_vVel), &m_vUp);
	if(m_dwWeaponState == _EXPLODED)
		m_mMatrix = m_matColl;
	D3DXMatrixInverse( &m_mMatrix, NULL, &m_mMatrix );
	// effect matrix & ticking
	if(m_pCharacterInfo)
	{
		m_pCharacterInfo->SetAllBodyConditionMatrix(m_mMatrix );
/*		if(m_bFireType==0)
		{
			D3DXMatrixLookAtRH( &m_mFireMatrix, &(m_pAttacker->m_vLWPos), &(m_pAttacker->m_vLWPos + m_pAttacker->m_vVel), &m_pAttacker->m_vUp);
			D3DXMatrixInverse( &m_mFireMatrix, NULL, &m_mFireMatrix );
		}
		else if(m_bFireType==1)
		{
			D3DXMatrixLookAtRH( &m_mFireMatrix, &(m_pAttacker->m_vRWPos), &(m_pAttacker->m_vRWPos + m_pAttacker->m_vVel), &m_pAttacker->m_vUp);
			D3DXMatrixInverse( &m_mFireMatrix, NULL, &m_mFireMatrix );
		}
		else if(m_bFireType==2)
		{
			D3DXMatrixLookAtRH( &m_mFireMatrix, &(m_pAttacker->m_vPos + 5.0f*m_pAttacker->m_vVel), &(m_pAttacker->m_vPos + 6.0f*m_pAttacker->m_vVel), &m_pAttacker->m_vUp);
			D3DXMatrixInverse( &m_mFireMatrix, NULL, &m_mFireMatrix );
		}

		m_pCharacterInfo->SetSingleBodyConditionMatrix( BODYCON_FIRE_MASK,m_mFireMatrix );
*/		m_pCharacterInfo->Tick(fElapsedTime);
	}

	// SKILL EFFECT
	D3DXMatrixLookAtRH( &m_mMatrix, &(m_vEffectPos), &(m_vEffectPos + m_vVel), &m_vUp);
	D3DXMatrixInverse( &m_mMatrix, NULL, &m_mMatrix );
	SetBodyConditionMatrixForSkillEffect(m_bodyCondition,m_mMatrix);
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			CWeaponFastData::CheckWeaponCollision()
/// \brief		���� �浹ó��
/// \author		dhkwon
/// \date		2004-05-28 ~ 2004-05-28
/// \warning	���Ŀ� �ϳ��� ���� ����
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CWeaponFastData::CheckWeaponCollision(D3DXVECTOR3 vDistance, float fMovingDistance)
{

	BOOL bCollision = FALSE;

//	D3DXVECTOR3 vVel = m_vPos-m_vOldPos;
	D3DXVECTOR3 vSide,vUpTemp;
	D3DXMATRIX mat;
	D3DXVec3Cross(&vSide,&m_vUp,&m_vVel);
	D3DXVec3Cross(&vUpTemp,&m_vVel,&vSide);
	D3DXMatrixLookAtLH( &mat, &m_vPos, &(m_vPos+m_vVel), &vUpTemp);
//	float fDist;

	// �浹 �˻� - ���� / ����
	if( m_pTarget )
	{
		CMonsterData* pMonster = (CMonsterData*)m_pTarget;
		if( m_pTarget->m_dwPartType == _MONSTER && pMonster && pMonster->m_pMonMesh)
		{
			// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
			//float fMonsterRadius = pMonster->m_pMonMesh->m_fRadius;
			float fMonsterRadius;
			if(pMonster->m_pMonMesh->m_fRadius < SHUTTLE_ATTACK_CENTER_RADIUS)
			{
				fMonsterRadius = pMonster->m_pMonMesh->m_fRadius;
			}
			else
			{
				fMonsterRadius = SHUTTLE_ATTACK_CENTER_RADIUS;
			}			
			// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
			if(m_fTargetDistance <= D3DXVec3Length(&vDistance) + fMonsterRadius)
			{
				// 2006-01-14 by ispark, �̺κ��� �ʿ䰡 ������.
				// �ؿ��� �浹 �˻簡 ����� ���� �ʴ´�. �� ������ ����... �𸥴�.
				// 1���� 2���� �ٸ��� �浹 �˻縦 �ؼ� Ÿ���� �ִ� ���� �ƴ϶� 
				// �����Ÿ� �ȿ� ��� �浹�� ó���ϰ� �־���.
				// �� �κ��� Tick()���� �ϰ� �־���.
//				pMonster->m_pMonMesh->Tick(pMonster->m_fCurrentTime);
//				pMonster->m_pMonMesh->SetWorldMatrix(pMonster->m_mMatrix);
//				float fcollDist = pMonster->m_pMonMesh->CheckCollision(m_mMatrix,m_vPos,DEFAULT_COLLISION_DISTANCE,TRUE,FALSE).fDist;
//				if(m_pAttacker == g_pShuttleChild)
//				if(fcollDist < fMovingDistance )
//				{
				 	m_vPos = m_vTargetPos;
					bCollision = TRUE;
//				}
			}		
		}
		else // Enemy
		{
			if(m_fTargetDistance <= D3DXVec3Length(&vDistance))
			{
			 	m_vPos = m_vTargetPos;
				bCollision = TRUE;
			}
		}
	}

	//���� �浹
	if(!bCollision)
	{
		COLLISION_RESULT collMesh;
		collMesh = g_pScene->m_pObjectRender->CheckCollMeshRangeObject(mat,m_vPos,fMovingDistance);
//		fDist = g_pScene->m_pObjectRender->CheckCollMeshRangeObject(mat,m_vPos,fMovingDistance).fDist;
		if(collMesh.fDist < fMovingDistance) 
		{
			bCollision = TRUE;
			m_pTarget = NULL;
			vUpTemp = collMesh.vNormalVector;
		}
		if(!bCollision &&
			IsTileMapRenderEnable(g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex)) // 2005-12-07 by ispark, �ٴ��� �������� �ϸ� �浹 �˻�)
		{
			// �ٴ� �浹
			float fHeight = 0.0f;
			D3DXVECTOR3 vNor;
			g_pGround->CheckCollMap(m_vPos + m_vVel*fMovingDistance, &fHeight, &vNor);
			if(fHeight >= m_vPos.y)
			{
				m_pTarget = NULL;
				bCollision = TRUE;
				vUpTemp = vNor;
			}
		}
	}
	if(bCollision)
	{
		//m_pTarget = NULL;
		D3DXMatrixIdentity(&m_matColl);
		D3DXMatrixLookAtRH(&m_matColl, &m_vPos, &(m_vPos+m_vVel), &vUpTemp);
		m_dwWeaponState = _EXPLODING;
	}

}
