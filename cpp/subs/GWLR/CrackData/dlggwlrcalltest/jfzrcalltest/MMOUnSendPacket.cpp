#include "StdAfx.h"
#include "MMOUnSendPacket.h"
#include "MMOClientTraverse.h"
#include "public/MMOPacket.h"
#include "public/UsefulFns.h"
#include "public/GameStructs.h"

MMOUnSendPacket theMmoUnSendPacket;

MMOUnSendPacket::MMOUnSendPacket(void)
{
}

MMOUnSendPacket::~MMOUnSendPacket(void)
{
}


bool PrintSend(void* pszSendBuf,void* pCallBack)
{
	return theMmoUnSendPacket.MmoPrintSend(pszSendBuf,pCallBack);
}


DWORD GetSendCallJmpAddr()
{
	return MMOCLIENT_REVERSAL_SEND_CALL+GetCryGameBaseAddr();
}

_declspec(naked) void HookSend()
{
	__asm
	{
		pushfd
		pushad

		mov eax, dword ptr[esp+0x24]
		push eax
		mov eax, dword ptr[esp+0x24+8]
		push eax
		call PrintSend
		add esp, 8

		test al,al
		je NOT_SEND_PACKET

		popad
		popfd

		PUSH EBP
		MOV EBP,ESP
		PUSH ESI
		MOV ESI,ECX

		mov eax, GetSendCallJmpAddr
		call eax
		add eax, 0x06
		jmp eax

NOT_SEND_PACKET:

		popad
		popfd
		sete al
		retn 4
	}
}

bool MMOUnSendPacket::MmoPrintSend(void* pszSendBuf,void* pCallBack)
{
	try
	{
		WORD wMsgId = *(WORD*)pszSendBuf;
		switch(wMsgId)
		{
		case 0x00:
		case 0x28d:
		case 0x504:
		case 0x286:
		case 0x251:
		case 0x291:
		case 0x2A9:
		case 0x293:
		case 0x2c5:
			{
				return true;
			}
		}
		char szPrint[256] = {0};
		sprintf_s(szPrint,"[LOG]zhp call = 0x%p msg id = %p",pCallBack,wMsgId);
		OutputDebugStringA(szPrint);
		switch(wMsgId)
		{
		case MMOCLIENT_REVERSAL_PACKET_SYN_COOR_DINATES___:		//	 ͬ��������
			{
				/*sprintf_s(szPrint,"[LOG] call = 0x%p msg id = %p",pCallBack,wMsgId);
				OutputDebugString(szPrint);*/
// 				return false;
			}
			break;

		default:
			{
				/*sprintf_s(szPrint,"[LOG] call = 0x%p msg id = %p",pCallBack,wMsgId);
				OutputDebugString(szPrint);*/

				switch (wMsgId)
				{
				case MMOCLIENT_REVERSAL_PACKET_MSG_ID_HIT___:		
					{
						return theMmoUnSendPacket.MmoPacketHit(pszSendBuf);
					}
					break;
				case MMOCLIENT_REVERSAL_PACKET_MSG_ID_WALK___:
					{
						return true;
					}
					break;
				case MMOCLIENT_REVERSAL_PACKET_MSG_ID_GUO_TU___:		// ������Ϸ�Ĺ�ͼ���
					{
						return theMmoUnSendPacket.MmoPacketGuoTu(pszSendBuf);
					}
					break;
				case MMOCLIENT_REVERSAL_PACKET_MSG_ID_CITY_GUO_TU___:	// �����ͼ���
					{
						return theMmoUnSendPacket.MmoPacketCityGuoTu(pszSendBuf);
					}
					break;
				case MMOCLIENT_REVERSAL_PACKET_MSG_ID_MOVE_TO___:
					{
						return true;
					}
 				case 0x00000C01:
					{
						sprintf_s(szPrint,"[LOG] call = 0x%p msg id = %p collect id = 0x%p",pCallBack,wMsgId,*(DWORD*)((DWORD)pszSendBuf+0x10));
						OutputDebugStringA(szPrint);
					}
					break;
				case 0x00000251:		// ��ɫ����ͬ��
					{
						
					}
					break;
				case MMOCLIENT_REVERSAL_PACKET_MSG_ID_FACTURE___:		// ������Ʒ
					{
						
					}
					break;	
				case MMOCLIENT_REVERSAL_PACKET_MSG_ID_BUY_REQ_ITEM___:			// ����������Ʒ
					{	
						
					}
					break;
				case MMOCLIENT_REVERSAL_PACKET_MSG_ID_SHANG_JIA_AUCTION_ITEM___:		// �����ϼ���Ʒ
					{
						
					}
					break;
				case MMOCLIENT_REVERSAL_PACKET_MSG_ID_REQ_ITEM_BY_TYPE___:
					{
						return theMmoUnSendPacket.MmoPacketReqItembyType(pszSendBuf);
					}
				case MMOCLIENT_REVERSAL_PACKET_MSG_ID_UP_EQUIP___:		// ����װ��
					{
						return false;
					}
					break;
				case MMOCLIENT_REVERSAL_PACKET_MSG_ID_GOTO_FB2___:
					{
						DWORD dwFbId = *(DWORD*)((DWORD)pszSendBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);
						sprintf_s(szPrint,"[LOG] ��ʼ���ظ��� id = 0x%p",dwFbId);
						OutputDebugStringA(szPrint);
					}
					break;
				case 0x00000705:
				case 0x00000033:
				case 0x0000000F:
					{
						
					}
					break;
				default:
					{
						
					}
				}
			}
		}
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}

void MMOUnSendPacket::MmoHookSend(void)
{
	Hook(MMOCLIENT_REVERSAL_SEND_CALL+GetCryGameBaseAddr(),HookSend);
}

void MMOUnSendPacket::MmoUnHookSend(void)
{
// 	0070CEB0    56                   PUSH ESI
// 	0070CEB1    8BF1                 MOV ESI,ECX
// 	0070CEB3    83BE 24010000 00     CMP DWORD PTR DS:[ESI+0x124],0x0

	byte bCode[] = {0x55 ,0x8B ,0xEC ,0x56 ,0x8B};
	_WriteProcessMemory(MMOCLIENT_REVERSAL_SEND_CALL+GetCryGameBaseAddr(),bCode,sizeof(bCode));
}

bool MMOUnSendPacket::MmoPacketHit(void* pszSendBuf)
{
//	PMMO_HIT ptheHit = NULL;
	try
	{
		OutputDebugStringA("[LOG] �������!");
//		MMOActor theActor;
//		theActor.ReadActor();
//		MMO_Hit(pszSendBuf,theActor.m_thePos,theActor.m_theDir);
// 		MMO_Hit(pszSendBuf,theActor.m_thePos,theActor.m_theDir);
// 		MMO_Hit(pszSendBuf,theActor.m_thePos,theActor.m_theDir);
// 		MMO_Hit(pszSendBuf,theActor.m_thePos,theActor.m_theDir);
// 		MMO_Hit(pszSendBuf,theActor.m_thePos,theActor.m_theDir);
// 		MMO_Hit(pszSendBuf,theActor.m_thePos,theActor.m_theDir);
// 		MMO_Hit(pszSendBuf,theActor.m_thePos,theActor.m_theDir);
// 		MMO_Hit(pszSendBuf,theActor.m_thePos,theActor.m_theDir);
// 		MMO_Hit(pszSendBuf,theActor.m_thePos,theActor.m_theDir);
// 		MMO_Hit(pszSendBuf,theActor.m_thePos,theActor.m_theDir);
// 		MMO_Hit(pszSendBuf,theActor.m_thePos,theActor.m_theDir);
// 		MMO_Hit(pszSendBuf,theActor.m_thePos,theActor.m_theDir);
//		return false;

		
		
//		ptheHit = (PMMO_HIT)((DWORD)pszSendBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);

// 		ptheHit->llDynamic = GetDynamicValue();
// 		ptheHit->llRand = GetRand(ptheHit->llDynamic);
// 
// 		ptheHit->dir.dir_x = theActor.m_theDir.dir_x;
// 		ptheHit->dir.dir_y = theActor.m_theDir.dir_y;
// 
// 		ptheHit->scr_pos.fx = theActor.m_thePos.fx;
// 		ptheHit->scr_pos.fy = theActor.m_thePos.fy;
// 		ptheHit->scr_pos.fz = theActor.m_thePos.fz;
// 
// 		ptheHit->wUnKnow1 = 0x2C2;
// 		ptheHit->fHitTime = 0.1572972f;
// 		ptheHit->wUnKnow3 = 0x204;;

// 		static bool bFalg = false;
// 
// 		if( bFalg == false )
// 		{
// 			//bFalg = true;
// 			mmo_copy(pszSendBuf);
// 		}

// 		for (int i=0; i<100; i++)
// 		{
// 			MMO_gamehooksend(pszSendBuf);
// 		}
		
		//return false;
	}
	catch (...)
	{
		assert(false);
	}

	return true;
}


bool MMOUnSendPacket::MmoPacketGuoTu(void* pszSendBuf)
{
	try
	{
		PMMO_PACKET_GOTO_DOOR ptheGotoDoor = (PMMO_PACKET_GOTO_DOOR)((DWORD)pszSendBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);

		char szPrint[256] = {0};
		sprintf_s(szPrint,"[LOG] ��ͼ��� : coord = %f %f %f cmd = %s",
			ptheGotoDoor->theDoorCoord.fx,
			ptheGotoDoor->theDoorCoord.fy,
			ptheGotoDoor->theDoorCoord.fz,
			ptheGotoDoor->szDoorCmd);
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{
		
	}

	return true;
}


bool MMOUnSendPacket::MmoPacketCityGuoTu(void* pszSendBuf)
{
	try
	{
		MMOActor theActor;
		char* pszCityGuoTuCmd = (char*)((DWORD)pszSendBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);
		char szPrint[256] = {0};
		sprintf_s(szPrint,"[LOG] �����ͼ��� cmd = %s name = %s",pszCityGuoTuCmd,theActor.GetRoleInMap());
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{

	}

	return true;
}



bool MMOUnSendPacket::MmoPacketReqItembyType(void* pszSendBuf)
{
	try
	{
		char szPrint[256];

		sprintf_s(szPrint,"[LOG] MmoPacketReqItembyType %d %d %d",
		*(byte*)((DWORD)pszSendBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___+4),
		*(byte*)((DWORD)pszSendBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___+5),
		*(byte*)((DWORD)pszSendBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___+6)
		);
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{
		
	}

	return true;
}


//////////////////////////////////////////////////////////////////////////
// hook �հ�
MMOUnRecvPacket theMmoUnRecvPacket;

MMOUnRecvPacket::MMOUnRecvPacket(void)
{

}

MMOUnRecvPacket::~MMOUnRecvPacket(void)
{

}

void TestRecv(void* pszRecvBuf)
{
	PMMO_PACKET_HEADER pthePacketHeader = (PMMO_PACKET_HEADER)pszRecvBuf;

	try
	{
		for (DWORD i = 0; i<(DWORD)pthePacketHeader->dwPacketMsgLen; i+=1 )
		{
			DWORD dwValue = *(DWORD*)((DWORD)pszRecvBuf+i+sizeof(MMO_PACKET_HEADER));
			if( dwValue == 0x058E3460 )
			{
				char szPrint[256] = {0};
				sprintf_s(szPrint,"[LOG] �������ķ��id: 0x%p ƫ��:0x%p",pthePacketHeader->wPacketMsgId,i+sizeof(MMO_PACKET_HEADER));
				OutputDebugStringA(szPrint);
			}
		}
	}
	catch (...)
	{
		
	}
}


bool PrintRecv(void* pszRecvBuf, int nLen)
{
// 	byte bCmdType = *(byte*)pszRecvBuf;
// 
// 	if( bCmdType != 0 )
// 	{
// 		return true;
// 	}
// 
// 	*(int*)&pszRecvBuf +=1;
// 
// 	if( nLen == 0 )
// 		nLen = *(int*)((DWORD)pszRecvBuf+0x4);
// 
// 
// 	WORD wMssageId = *(WORD*)pszRecvBuf;

	WORD wMssageId = *(WORD*)pszRecvBuf;

	nLen = *(int*)((DWORD)pszRecvBuf+0x4);

	//TestRecv(pszRecvBuf);
	

	switch(wMssageId)
	{
// 	case 0x508:		// �������˷��
 	case 0x506:
// 	case 0x280:
// 	case 0x2d1:
// 	case 0x2ea:
// 	case 0x281:
// 	case 0x402:
// 	case 0x290:
// 	case 0x504:
// 	case 0x264:
// 	case 0x295:
// 	case 0x274:
// 	case 0x26d:
// 	case 0x403:
// 	case 0x2701:
		{

		}
		break;
 	case 0x2ef:			// ������˷��
 	case 0x509:
 	case 0x104:
	case 0x25e:
	case 0x261:
	case 0x3043:
	case 0x1702:
	case 0x1727:
	case 0x263:
	case 0x299:
	case 0x3403:
	case 0x2162:
	case 0x2161:
	case 0x288:
	case 0x28A:
	case 0x262:
	case 0x505:
	case 0x2d1:
	case 0x403:
	case 0x402:
		{
			//*(WORD*)pszRecvBuf = 0;
		}
		break;
	case 0x56F:
#if _DEBUG
		OutputDebugStringA("[LOG] �����ʾ�ͷ");
#endif
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_ROLE_HP_STATE_RET___:		// ���ж����״̬��   
						
		{
			//*(WORD*)pszRecvBuf = 0;
			int nRet = (int)(*(WORD*)((DWORD)pszRecvBuf+0x10));
			if( 
// 				nRet == 0x1F ||
//  			nRet == 0x20 ||
				nRet == 0x2B 
//				nRet == 0x34 

// 				nRet == 0x38 || 
// 				nRet == 0x44 ||
// 				nRet == 0x48 || 
// 				nRet == 0x4C 

// 				nRet == 0x5c || 
// 				nRet == 0x56 ||
// 				nRet == 0x88 || 
// 				nRet == 0xBB || 
// 				nRet == 0xE6 || 
// 				nRet == 0x114 
				)
			{
				char* pszRecvBuffer[256] = {0};
				memcpy(pszRecvBuffer,(char*)((DWORD)pszRecvBuf+0x10+0x4),0x2a);
				//memset(pszRecvBuffer,0,0x2A);

				byte bRet = *(byte*)((DWORD)pszRecvBuf+0x3E);
				*(byte*)((DWORD)pszRecvBuf+0x3E) = 0;

				DWORD dwRet = *(DWORD*)((DWORD)pszRecvBuf+0x10+0x4);

				char szPrint[256] = {0};
				sprintf_s(szPrint,"[LOG] �յ� recv id = 0x%p len = 0x%p ret = 0x%p ret2 = 0x%p %s ret = %d",wMssageId,nLen,nRet,dwRet,pszRecvBuffer,bRet);
				OutputDebugStringA(szPrint);

				//*(WORD*)pszRecvBuf = 0;
			}
			else
			{
				char szPrint[256] = {0};
				sprintf_s(szPrint,"[LOG] ��� recv id = 0x%p len = 0x%p ret = 0x%p",wMssageId,nLen,nRet);
				//OutputDebugStringA(szPrint);
				
			}
		
		}
		break;
	case 0x274:
	case 0x295:
	case 0x504:
	case 0x280:
	case 0x281:
	case 0x26D:
	case 0x264:
	case 0xD03:
	case 0x25F:
	case 0x2EA:
	case 0x2e9:
	case 0x258:
	case 0x290:
		{
			
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_MSG_PLAYER_LIST___:			// ��ɫ������ֵ
		{
			return theMmoUnRecvPacket.MmoRecvPlayerList(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_MSG_DELETE_PLAYER_RET___:	// ɾ����ɫ���ر�
		{
			return theMmoUnRecvPacket.MmoRecvDeletePlayer(pszRecvBuf);
		}
		break;
	case 0x2d3:
		{
			//OutputDebugStringA("[LOG] ������0x2d3");
		}
		break;
	case 0x29d:	// ���ٶ���
		{

		}
		break;
	//case 0x2A1:
	//case 0x258:
		{
			
// 			char szPrint[256] = {0};
// 			sprintf_s(szPrint,"[LOG] ��� recv id = 0x%p len = 0x%p",wMssageId,nLen);
// 			OutputDebugStringA(szPrint);
// 
//  			*(WORD*)pszRecvBuf = 0;
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_MSG_MOSTER_SIWANG___:		// ������
		{
			char szPrint[256] = {0};
		
			DWORD packet_id = *(DWORD*)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_MSG_MOSTER_SIWANG_PACKET_ID);

			sprintf_s(szPrint,"[LOG] ��������id ��0x%p",	packet_id);
			OutputDebugStringA(szPrint);

			//*(DWORD*)((DWORD)pszRecvBuf+0x18) = 0x100014AC;
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_MSG_PLAYER_SIWANG___:
		{
			char szPrint[256] = {0};
			DWORD packet_id = *(DWORD*)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_RECV_PACKET_DATA_OFFSET___);
			sprintf_s(szPrint,"[LOG] �������id ��0x%p",	packet_id);
			OutputDebugStringA(szPrint);
			//assert(false);
		}
		break;
	case MMOCLIENT_REVERSAL_ACCEPT_TASK_MSG_ID___:
		{
			return theMmoUnRecvPacket.MmoAcceptTask(pszRecvBuf);		// �������񷵻�ֵ
		}
		break;
	case MMOCLIENT_REVERSAL_GIVE_UP_TASK_MSG_ID___:
		{
			return theMmoUnRecvPacket.MmoGiveUpTask(pszRecvBuf);		// �������񷵻�ֵ
		}
		break;
	case MMOCLIENT_REVERSAL_ACCEPT_MAIL_VALUE_RET_MSG_ID___:			// �����ʼ��ķ���ֵ
		{
			return theMmoUnRecvPacket.MmoAcceptMailRetValue(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_MSG_LINE___:		// ѡ���ɫ����·�ķ���ֵ
		{
			return theMmoUnRecvPacket.MmoRecvPlayerLine(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_MSG_CREATE_ROLE_RET___:	// ������ɫ�ķ���ֵ
		{
			return theMmoUnRecvPacket.MmoRecvCreateRole(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_MSG_IN_FB_RET___:		// ���븱���ķ���ֵ
		{
			return theMmoUnRecvPacket.MmoRecvDoFbRet(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_MSG_FB_SERVER_FULL_RET___:	// ���������������ķ���ֵ
		{
			return theMmoUnRecvPacket.MmoRecvFbServerFullRet(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_REQ_ITEM_BY_TYPE___:			// ��ѯ������Ʒ����ֵ
		{
			return theMmoUnRecvPacket.MmoRecvReqItemBytype(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_REQ_ITEM_BY_TYPE_MY___:			// ˢ���ҵ���������ֵ
		{
			return theMmoUnRecvPacket.MmoRecvMyReqItemBytype(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_INVITE_TEAM_FAIL___:			// ������ӵķ���ֵ ==�� ���ʧ�ܣ�xx�ܾ�������������
		{
			return theMmoUnRecvPacket.MmoRecvInviteTeamFail(pszRecvBuf);
		}
	case MMOCLIENT_REVERSAL_PACKET_RECV_TEAM_INFO___:			// �ڽ�ɫ���Ƕӳ��������������Ӻʹ������鷵��ֵ  ==�� ��һ�λ�ȡ������Ϣ���д˷��ذ�
		{
			return theMmoUnRecvPacket.MmoRecvTeamInfo(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_JOIN_TEAM_INFO___:			// �ڽ�ɫΪ�ӳ�������£����¼���Ķ�Ա����ֵ
		{
			return theMmoUnRecvPacket.MmoRecvJoinTeamInfo(pszRecvBuf);
		}
		break;	
	case MMOCLIENT_REVERSAL_PACKET_RECV_LEAVE_TEAM___:		// �ж�Ա�뿪����  
		{
			return theMmoUnRecvPacket.MmoRecvleaveTeam(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_BE_LEAVE_TEAM___:	// �ж�Ա���߳�����
		{
			return theMmoUnRecvPacket.MmoRecvBeleaveTeam(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_DISS_TEAM___ :		// �ӳ��˳�����
		{
			return theMmoUnRecvPacket.MmoRecvDisTeam(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_TEAM_ERROR___:		// ��ӵĴ�����
		{
			return theMmoUnRecvPacket.MmoRecvTeamRetError(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_TASK_FB_INFO___:	// �������񸱱���ǧ�����������������ķ���ֵ
		{
			return theMmoUnRecvPacket.MmoRecvTaskFbInfo(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_AN_QUAN_BAO_HU_TIME___:			// ��ȫ����ʱ��	
		{
			int nTime = *(int*)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);

			// ���������������̵꣬����Ҫʱ�����Ƶģ����᷵�������
			char szPrint[256] = {0};
			sprintf_s(szPrint,"[LOG] recv �����ڴ��ڰ�ȫ����ʱ���ڣ����Ժ��Դ˲�����ʣ��%d��",nTime);
			OutputDebugStringA(szPrint);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_REQ_BUY_ITEM_RET___:			// ����������Ʒ�ķ���ֵ
		{
			return theMmoUnRecvPacket.MmoRecvReqBuyItemRet(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_JI_YUN_FB_RET___:			// ����
		{
			return theMmoUnRecvPacket.MmoRecvJiYunFbRet(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_OPEN_NPC_RET___:			// ��npc����ֵ
		{
			return theMmoUnRecvPacket.MmoRecvOpenNpcRet(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_SHANG_JIA_ITEM_RET___:		// �ϼ�������Ʒ�ķ���ֵ
		{
			return theMmoUnRecvPacket.MmoRecvShangJiaAuctionItemRet(pszRecvBuf);
		}
		break;	
	case MMOCLIENT_REVERSAL_PACKET_RECV_SELL_ITEM_RET___:	// ������Ʒ�ķ���ֵ
		{
			return theMmoUnRecvPacket.MmoRecvSellItemRet(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_COMPLETE_TASK_RET___:		// �ύ����ɹ��ķ���ֵ
		{
			return theMmoUnRecvPacket.MmoRecvCompleteTaskRet(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_COMPLETE_TASK_FAIL_RET___:			// �ύ����ʧ�ܵķ���ֵ
		{
			return theMmoUnRecvPacket.MmoRecvCompleteTaskFailRet(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_NPC_CHAT_RET___:		// ��̸����npc����ֵ
		{
			return theMmoUnRecvPacket.MmoRecvTaskNpcChatRet(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_FRAM_SEED_RET___:		// ��ֲ���ӵķ���ֵ
		{
			return theMmoUnRecvPacket.MmoRecvFramSeedRet(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_FEEB_HP_RET___:			// ������Ѫ�ķ��ذ��������ж��Ƿ��ж�
		{
			return theMmoUnRecvPacket.MmoRecvFeebHpRet(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_SEND_MAIL_RET___:		// �����ʼ��ķ���ֵ
		{
			return theMmoUnRecvPacket.MmoRecvSendMailRet(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_USE_ITEM_RET___:			// ʹ����Ʒ�ķ���ֵ
		{
			return theMmoUnRecvPacket.MmoRecvUseItemRet(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_USE_ITEM_RET2___:		// ʹ����Ʒ��û��ʣ����Ʒ�ķ���ֵ
		{
			return theMmoUnRecvPacket.MmoRecvUseItemRet2(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_BUY_ITEM_RET___:		// ������Ʒ�ķ���ֵ
		{
			return theMmoUnRecvPacket.MmoRecvBuyItemRet(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_GET_GFIT_BAG_RET___:	// ��ȡ���
		{
			return theMmoUnRecvPacket.MmoRecvGetGfitBagRet(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_COLLECT_ITEM_BAG_FULL_RET___:	// �ɼ���Ʒ���������ķ���ֵ
		{
			return theMmoUnRecvPacket.MmoRecvCollectItemBagFullRet(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_TIDY_INVENTORY_ITEM_RET___:		// ��������ֿ�ķ���ֵ
		{
			return theMmoUnRecvPacket.MmoRecvTidyInventoryItemRet(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_SEND_MAIL_RET2___:			// �����ʼ�Ƶ���ķ���ֵ
		{
			return theMmoUnRecvPacket.MmoRecvSendMailRet2(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_GUOTU_RET___:
		{
			return theMmoUnRecvPacket.MmoRecvSendGuoTuRet(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_REQUEST_DEAL_RET___:	// �����׷���ֵ �ɹ�
		{
			return theMmoUnRecvPacket.MmoRecvRequestDealRet(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_REQUEST_DEAL_FIAL_RET___:	// �����׷���ֵ �ܾ�
		{
			return theMmoUnRecvPacket.MmoRecvRequestDealFailRet(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_ACCEPT_DEAL_RET___:		// ���ܵ������׵ķ���ֵ
		{
			return theMmoUnRecvPacket.MmoRecvAcceptDealRet(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_QUXIAO_DEAL_RET___:	// ȡ�����׷���ֵ
		{
			return theMmoUnRecvPacket.MmoRecvQuXiaoDealRet(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_DEAL_FAIL_RET1___:	// ˫����ȷ�Ͻ��׺�ķ���ֵ ����ʧ�� ��Ʒ����Я������ �Է��Ѿ��ڽ�����
		{
			return theMmoUnRecvPacket.MmoRecvDealFailRet(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_MOVE_DEAL_ITEM_RET___:	// �ƶ���Ʒ���������ɹ���ķ���ֵ
		{
			return theMmoUnRecvPacket.MmoRecvMoveDealItemRet(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_MOVE_DEAL_GOLD_RET___:	// ���׽�ҵķ���ֵ
		{
			return theMmoUnRecvPacket.MmoRecvMoveDealGoldRet(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_DEAL_STATUS_RET___:		// ����״̬����ֵ ==�� �����������ķ���ֵ �Է������������ķ���ֵ �Է�ȷ�Ͻ��׵ķ���ֵ�Ͻ��׵ķ���ֵ
		{
			return theMmoUnRecvPacket.MmoRecvDealStatusRet(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_DEAL_SUCESS_RET___:	// ˫����ȷ�Ͻ��׺�ķ���ֵ ���׽���
		{
			return theMmoUnRecvPacket.MmoRecvDealSucessRet(pszRecvBuf);
		}
		break;
	case MMOCLIENT_REVERSAL_PACKET_RECV_EMIAL_INFO_RET___:
		{
			char szPrint[256] = {0};

			DWORD packet_id = *(DWORD*)((DWORD)pszRecvBuf+0x14);

			sprintf_s(szPrint,"[LOG] �����ʼ���Ϣid ��0x%p",	packet_id);
			OutputDebugStringA(szPrint);
			
		}
		break;
	default:
		{
			char szPrint[256] = {0};
			sprintf_s(szPrint,"[LOG] recv id = 0x%p len = 0x%p",wMssageId,nLen);
			OutputDebugStringA(szPrint);
		}
	}
	return true;
}



_declspec(naked) void HookRecv()
{
	__asm
	{

		pushfd
		pushad

		push 0
		push edi
		call PrintRecv
		add esp, 8

		popad
		popfd

		pop edi
		pop esi
		POP EBX
		MOV ESP,EBP
		POP EBP
		RETN
	}
}


void MMOUnRecvPacket::MmoHookRecv()
{
	Hook(MMOCLIENT_REVERSAL_RECV_HOOK+GetCryGameBaseAddr(),HookRecv);
}

void MMOUnRecvPacket::MmoUnHookRecv()
{
	byte bCode[] = {0x5F ,0x5E ,0x5B ,0x8B ,0xE5 };
	_WriteProcessMemory(MMOCLIENT_REVERSAL_RECV_HOOK+GetCryGameBaseAddr(),bCode,5);

}

bool MMOUnRecvPacket::MmoAcceptTask(void* pszRecvBuf)
{
	PMMO_ACCEPT_TASK ptheAcceptTask = (PMMO_ACCEPT_TASK)pszRecvBuf;
	char szPrint[256] = {0};
	sprintf_s(szPrint,"[LOG] ��������: 0x%p",ptheAcceptTask->dwTaskId);
	OutputDebugStringA(szPrint);

	return true;
}

bool MMOUnRecvPacket::MmoGiveUpTask(void* pszRecvBuf)
{
	PMMO_GIVE_UP_TASK ptheGiveUpTask = (PMMO_GIVE_UP_TASK)pszRecvBuf;
	char szPrint[256] = {0};
	sprintf_s(szPrint,"[LOG] ��������: 0x%p",ptheGiveUpTask->dwTaskId);
	OutputDebugStringA(szPrint);

	return true;
}

bool MMOUnRecvPacket::MmoAcceptMailRetValue(void* pszRecvBuf)
{
	PMM0_ACCEPT_MAIL_RET_VALUE ptheMailRet = (PMM0_ACCEPT_MAIL_RET_VALUE)pszRecvBuf;

	char szPrint[256] = {0};
	sprintf_s(szPrint,"[LOG] �����ʼ�����ֵ: id = 0x%p 0x%p ret = %d %d",ptheMailRet->dwMailId1,ptheMailRet->dwMailId2,ptheMailRet->nRetValue,ptheMailRet->nRetError);
	OutputDebugStringA(szPrint);
	return true;
}



bool MMOUnRecvPacket::MmoRecvPlayerList(void* pszRecvBuf)
{
	try
	{
		char szPrint[256];
		sprintf_s(szPrint,"[LOG] �����հ���ַ=%p �ṹ��С=%p",(DWORD)pszRecvBuf,sizeof(MM0_PLAYER_LIST));
		OutputDebugStringA(szPrint);

		int nPlayerCount = (int)(*(WORD*)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_RECV_PLAYER_LIST_COUNT___));

		PMM0_PLAYER_LIST pthePlayerList = PMM0_PLAYER_LIST((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_RECV_PLAYER_INFO_OFFSET___);
		for(int i=0; i<nPlayerCount; i++)
		{
			sprintf_s(szPrint,"[LOG] player id = 0x%p level = %d name = %s\r\n",pthePlayerList->dwPlayerId,pthePlayerList->nPlayerLevel,pthePlayerList->szPlayerName);
			OutputDebugStringA(szPrint);
			pthePlayerList++;
		}
	}
	catch (...)
	{
		assert(false);
	}

	return true;
}


bool MMOUnRecvPacket::MmoRecvDeletePlayer(void* pszRecvBuf)
{
	try
	{
		PMMO_RECV_DELETE_PLAYER ptheDeletePlayer = (PMMO_RECV_DELETE_PLAYER)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_RECV_PACKET_DATA_OFFSET___);

		/*++
			�� ptheDeletePlayer->nRet = 0 ʱ�����ʾɾ���ɹ�
			�� ptheDeletePlayer->nRet = 2 ʱ�����ʾɾ��ʧ�ܣ�ptheDeletePlayer->nRetParamer = n���˷��ذ���ʾ��ǰ���ڵ�½����״̬����nΪʣ����

		--*/
		char szPrint[256];
		sprintf_s(szPrint,"[LOG] delete ret = 0x%p paramer = 0x%p\r\n",ptheDeletePlayer->nRet,ptheDeletePlayer->nRetParamer);
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{
		assert(false);
	}

	return true;
}


bool MMOUnRecvPacket::MmoRecvPlayerLine(void* pszRecvBuf)
{
	try
	{
		int nLineCount = (int)*(WORD*)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_RECV_PACKET_DATA_OFFSET___);

		PMMO_GAME_LINE ptheGameLine = (PMMO_GAME_LINE)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_RECV_PACKET_DATA_OFFSET___+sizeof(WORD));

		char szPrint[256];
		for (int i=0; i<nLineCount; i++)
		{
			// ���� = 1�� ���� = 2����ɫ��æ = 3����ɫ��æ = 4
			
			char szLineLevelStr[256] = {0};

			switch (ptheGameLine->bLineLevel)
			{
			case 1:
				{
					memcpy_s(szLineLevelStr,sizeof(szLineLevelStr),"����",strlen("����")+1);
				}
				break;
			case 2:
				{
					memcpy_s(szLineLevelStr,sizeof(szLineLevelStr),"����",strlen("����")+1);
				}
				break;
			case 3:
				{
					memcpy_s(szLineLevelStr,sizeof(szLineLevelStr),"��ɫ��æ",strlen("��ɫ��æ")+1);
				}
				break;
			case 4:
				{
					memcpy_s(szLineLevelStr,sizeof(szLineLevelStr),"��ɫ��æ",strlen("��ɫ��æ")+1);
				}
				break;
			default:
				{
					memcpy_s(szLineLevelStr,sizeof(szLineLevelStr),"δ֪",strlen("δ֪")+1);
				}
			}
			sprintf_s(szPrint,"[LOG] game line Index = %d level = %d %s\r\n",ptheGameLine->wLineIndex,ptheGameLine->bLineLevel,szLineLevelStr);
			OutputDebugStringA(szPrint);

			ptheGameLine++;
		}
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}

bool MMOUnRecvPacket::MmoRecvCreateRole(void* pszRecvBuf)
{
	try
	{
		DWORD dwRet = *(DWORD*)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_RECV_PACKET_DATA_OFFSET___);

		char szPrint[256];
		sprintf_s(szPrint,"[LOG] ������ɫ����ֵ: 0x%p",dwRet);   // �ɹ� = 0�� �Ѿ���ע�� = 4
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{
		assert(false);
	}

	return true;
}



// ����������Ʒ���
bool MMOUnRecvPacket::MmoRecvReqItemBytype(void* pszRecvBuf)
{
	try
	{
		char szPrint[256];
		PMMO_RECV_REQ_ITEM_BY_HEADER ptheRecvReqItemByHeader = (PMMO_RECV_REQ_ITEM_BY_HEADER)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);

		sprintf_s(szPrint,"[LOG] ������Ʒ ret = 0x%p ��Ʒ������ = %d ��ǰҳ��Ʒ���� = %d",ptheRecvReqItemByHeader->dwRet,ptheRecvReqItemByHeader->nReqItemCount,ptheRecvReqItemByHeader->wCurPageCount);
		OutputDebugStringA(szPrint);
		if( ptheRecvReqItemByHeader->wCurPageCount != 0 )
		{
			PMM0_RECV_REQ_ITEM_BY_TYPE ptheReqItenByType = (PMM0_RECV_REQ_ITEM_BY_TYPE)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___+sizeof(MMO_RECV_REQ_ITEM_BY_HEADER));

			
			for (int i=0; i<ptheRecvReqItemByHeader->wCurPageCount; i++)
			{
				/*++
					��Ϸ��������߼�

					����һ����Ϸ�ı�keyֵ = dwReqItemById �� dwReqItemByKey
					recv��ȡ��������Ʒ��Ϣʱ�����Ȳ�����û�У�����ý��ܺ��� GetReqItemAddr �����뵽���У���Ϸ���ÿһ����Ʒ������һ�ν��ܣ�֮���ٴη��ʵ��˶���ʱ�����ڽ���
				--*/
				DWORD dwItemAddr = GetReqItemAddr((DWORD)ptheReqItenByType);
				assert(dwItemAddr);
				DWORD dwItemId = 0;
				int nItemCount = 0;

				if( dwItemAddr != 0 )
				{
					nItemCount = *(int*)(dwItemAddr+MMOCLIENT_REVERSAL_RECV_REQ_ITEM_BY_GET_ITEM_COUNT_OFFSET___);

					DWORD dwItemAddr2 = *(DWORD*)(dwItemAddr+MMOCLIENT_REVERSAL_RECV_REQ_ITEM_BY_GET_ITEM_ID_OFFSET3___);
					if( dwItemAddr2 != 0 )
					{
						dwItemId = *(DWORD*)(dwItemAddr2+MMOCLIENT_REVERSAL_ITEM_PACKET_ID_OFFSET___);
					}
					
				}

				sprintf_s(szPrint,"[LOG] addr = 0x%p req id = 0x%p key = 0x%p Item Id = 0x%p count = %d by name = %s ���ļ�: %d һ�ڼ�: %d ���ļ�: %d",
							dwItemAddr,
							ptheReqItenByType->dwReqItemById,
							ptheReqItenByType->dwReqItemByKey,
							dwItemId,
							nItemCount,		// �������Ʒ�����ڵ����������������������0�����Ǵ���Ʒ�Ǵ��ڵģ�������һ��
							ptheReqItenByType->szReqItemByPlayerName,
							ptheReqItenByType->nReqItemByPrice1,
							ptheReqItenByType->nReqItemByPrice2,
							ptheReqItenByType->nReqItemByPrice3);
				OutputDebugStringA(szPrint);

				ptheReqItenByType++;
			}
		}
		else
		{
			OutputDebugStringA("[LOG] ������������Ʒ!");
		}
	}
	catch (...)
	{
		assert(false);
	}

	return true;
}



// �����ҵ�������Ʒ���
bool MMOUnRecvPacket::MmoRecvMyReqItemBytype(void* pszRecvBuf)
{
	try
	{
		int nCount = (int)*(WORD*)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___+MMOCLIENT_REVERSAL_PACKET_RECV_MSG_MY_REQ_COUNT_OFFSET___);
		if( nCount != 0 )
		{
			PMM0_RECV_REQ_ITEM_BY_TYPE ptheReqItenByType = (PMM0_RECV_REQ_ITEM_BY_TYPE)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___+MMOCLIENT_REVERSAL_PACKET_RECV_MSG_MY_REQ_DATA_OFFSET___);

			char szPrint[256];
			for (int i=0; i<nCount; i++)
			{
				DWORD dwItemAddr = GetReqItemAddr((DWORD)ptheReqItenByType);
				DWORD dwItemId = 0;
				int nItemCount = 0;

				if( dwItemAddr != 0 )
				{
					nItemCount = *(int*)(dwItemAddr+MMOCLIENT_REVERSAL_RECV_REQ_ITEM_BY_GET_ITEM_COUNT_OFFSET___);

					DWORD dwItemAddr2 = *(DWORD*)(dwItemAddr+MMOCLIENT_REVERSAL_RECV_REQ_ITEM_BY_GET_ITEM_ID_OFFSET3___);
					if( dwItemAddr2 != 0 )
					{
						dwItemId = *(DWORD*)(dwItemAddr2+MMOCLIENT_REVERSAL_ITEM_PACKET_ID_OFFSET___);
					}

				}

				sprintf_s(szPrint,"[LOG] req id = 0x%p key = 0x%p Item Id = 0x%p count = %d by name = %s ���ļ�: %d һ�ڼ�: %d ���ļ�: %d",
					ptheReqItenByType->dwReqItemById,
					ptheReqItenByType->dwReqItemByKey,
					dwItemId,
					nItemCount,
					ptheReqItenByType->szReqItemByPlayerName,
					ptheReqItenByType->nReqItemByPrice1,
					ptheReqItenByType->nReqItemByPrice2,
					ptheReqItenByType->nReqItemByPrice3);
				OutputDebugStringA(szPrint);

				ptheReqItenByType++;
			}
		}
	}
	catch (...)
	{
		assert(false);
	}

	return true;
}

// ������ӵķ���ֵ ==�� ���ʧ�ܣ�xx�ܾ�������������
bool MMOUnRecvPacket::MmoRecvInviteTeamFail(void* pszRecvBuf)
{
	try
	{
		PMMO_INVITE_TEAM_FAIL ptheInviteTeamFail = (PMMO_INVITE_TEAM_FAIL)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);

		char szPrint[256];
		sprintf_s(szPrint,"[LOG] ���ʧ�ܣ�%s �ܾ�������������!",ptheInviteTeamFail->szActorName);
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{
		
	}
	return true;
}


// �ڽ�ɫ���Ƕӳ��������������Ӻʹ������鷵��ֵ  ==�� ��һ�λ�ȡ������Ϣ���д˷��ذ�
bool MMOUnRecvPacket::MmoRecvTeamInfo(void* pszRecvBuf)
{
	try
	{
		PMMO_TEAM_INFO ptheTeamInfo = (PMMO_TEAM_INFO)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);

		char szPrint[256];
		sprintf_s(szPrint,"[LOG] ��������ɹ� ==> team title = %s pwd = %s member count = %d",ptheTeamInfo->szTeamTitle,ptheTeamInfo->szTeamPwd,ptheTeamInfo->nMemberCount);
		OutputDebugStringA(szPrint);
		for (int i=0; i<ptheTeamInfo->nMemberCount; i++ )
		{
			sprintf_s(szPrint,"[LOG] team member name = %s id = 0x%p level = %d",ptheTeamInfo->theTeamMemberInfo[i].szTeamMemberName,ptheTeamInfo->theTeamMemberInfo[i].dwActorPacketId,ptheTeamInfo->theTeamMemberInfo[i].nMemberLevel);
			OutputDebugStringA(szPrint);
		}
	}
	catch (...)
	{

	}
	return true;
}

// �ڽ�ɫΪ�ӳ�������£����¼���Ķ�Ա����ֵ
bool MMOUnRecvPacket::MmoRecvJoinTeamInfo(void* pszRecvBuf)
{
	try
	{
		PMMO_TEAM_MEMBER_INFO ptheTeamInfo = (PMMO_TEAM_MEMBER_INFO)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);
		char szPrint[256];
		sprintf_s(szPrint,"[LOG] ���³�Ա���� ==> team member name = %s id = 0x%p level = %d",ptheTeamInfo->szTeamMemberName,ptheTeamInfo->dwActorPacketId,ptheTeamInfo->nMemberLevel);
		OutputDebugStringA(szPrint);

	}
	catch (...)
	{

	}
	return true;
}

// �ж�Ա�뿪����
bool MMOUnRecvPacket::MmoRecvleaveTeam(void* pszRecvBuf)
{
	try
	{
		DWORD dwLeaveActorPacketId = *(DWORD*)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);
		char szPrint[256];
		sprintf_s(szPrint,"[LOG] �ж�Ա�뿪���� ==> id = 0x%p",dwLeaveActorPacketId);
		OutputDebugStringA(szPrint);

	}
	catch (...)
	{
		assert(false);
	}
	return true;
}

// �ж�Ա���ӳ��߳�����
bool MMOUnRecvPacket::MmoRecvBeleaveTeam(void* pszRecvBuf)
{
	try
	{
		DWORD dwLeaveActorPacketId = *(DWORD*)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);
		char szPrint[256];
		sprintf_s(szPrint,"[LOG] �ж�Ա���ӳ��߳����� ==> id = 0x%p",dwLeaveActorPacketId);
		OutputDebugStringA(szPrint);

	}
	catch (...)
	{
		assert(false);
	}
	return true;
}

// �ӳ��˳�����
bool MMOUnRecvPacket::MmoRecvDisTeam(void* pszRecvBuf)
{
	try
	{
		OutputDebugStringA("[LOG] �ӳ��˳�����!!!");
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}

// ��ӵĴ��󷵻�ֵ
bool MMOUnRecvPacket::MmoRecvTeamRetError(void* pszRecvBuf)
{
	try
	{
		DWORD dwTeamError1 = *(DWORD*)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);
		DWORD dwTeamError2 = *(DWORD*)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___+4);
		char szPrint[256];
		sprintf_s(szPrint,"[LOG] ������������� ==> 0x%p 0x%p",dwTeamError1,dwTeamError2);
		OutputDebugStringA(szPrint);

		/*++
			��û�ж��飬�����˳�����	����ֵ�� 6 �� 0x0C
			��������ʧ�ܣ����Ѿ����ڶ���	����ֵ�� 5 �� 5
			���Ѿ����ڶ��飬���ɼ�����˵Ķ���	����ֵ�� 3 �� 5
			���ʧ�ܣ��ö��鲻����	����ֵ�� 3 �� 0x0C
			���ʧ�ܣ�������֤����	����ֵ�� 3 �� 0x10
			�㲻�Ƕӳ�������û�ж��飬�޷��߳���Ա	����ֵ��7 �� 0x0C
			�������ʧ�ܣ��Է��Ѿ��ж���	����ֵ��1 �� 9
		--*/
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}

// �������񸱱���ǧ����������������
bool MMOUnRecvPacket::MmoRecvTaskFbInfo(void* pszRecvBuf)
{
	try
	{
		PMMO_TASK_FB_INFO ptheTaskFbInfo = (PMMO_TASK_FB_INFO)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);

		char szPrint[256];

// 		switch(ptheTaskFbInfo->dwTaskFbType)
// 		{
// 		case MMOCLIENT_REVERSAL_PACKET_MSG_ID_GONG_HUI_INDEX___:
// 			{
// 				sprintf_s(szPrint,"[LOG] ���ḱ�� ==> task fb type = 0x%p count = %d ",ptheTaskFbInfo->dwTaskFbType,ptheTaskFbInfo->wCount);
// 			}
// 			break;
// 		case MMOCLIENT_REVERSAL_PACKET_MSG_ID_QIAN_SHOU_INDEX___:
// 			{
// 				sprintf_s(szPrint,"[LOG] ǧ������ ==> task fb type = 0x%p count = %d ",ptheTaskFbInfo->dwTaskFbType,ptheTaskFbInfo->wCount);
// 			}
// 			break;
// 		case MMOCLIENT_REVERSAL_PACKET_MSG_ID_MIAO_MIAO_INDEX___:
// 			{
// 				sprintf_s(szPrint,"[LOG] �������� ==> task fb type = 0x%p count = %d ",ptheTaskFbInfo->dwTaskFbType,ptheTaskFbInfo->wCount);
// 			}
// 			break;
// 		default:
// 			{
// 				sprintf_s(szPrint,"[LOG] δ֪���� ==> task fb type = 0x%p count = %d ",ptheTaskFbInfo->dwTaskFbType,ptheTaskFbInfo->wCount);
// 			}
// 		}

		sprintf_s(szPrint,"[LOG] ��ѯ��������ֵ ==> fb ret = 0x%p count = %d ",ptheTaskFbInfo->dwRetValue,ptheTaskFbInfo->wCount);
		
		OutputDebugStringA(szPrint);

		PMMO_TASK_FB_INFO_	ptheTaskFbInfo_ = (PMMO_TASK_FB_INFO_)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___+sizeof(MMO_TASK_FB_INFO));

		for (int i=0; i<ptheTaskFbInfo->wCount; i++ )
		{
			for (int j=0; j<ptheTaskFbInfo_->wCount; j++)
			{
				sprintf_s(szPrint,"[LOG] task fb id = 0x%p fb type = 0x%p",ptheTaskFbInfo_->dwTaskFbId[j],ptheTaskFbInfo_->dwFbType);	
				OutputDebugStringA(szPrint);
			}
			ptheTaskFbInfo_++;
		}
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}

bool MMOUnRecvPacket::MmoRecvReqBuyItemRet(void* pszRecvBuf)
{
	try
	{
		PMMO_RECV_REQ_BUY_ITEM_RET ptheRecvReqItemRet = (PMMO_RECV_REQ_BUY_ITEM_RET)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_RECV_PACKET_DATA_OFFSET___);
		
		char szPrint[256];
		sprintf_s(szPrint,"[LOG] ����������Ʒ����ֵ ==> ret = 0x%p id = 0x%p",ptheRecvReqItemRet->dwBuyItemRet,ptheRecvReqItemRet->dwBuyReqItemId);
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}


bool MMOUnRecvPacket::MmoRecvJiYunFbRet(void* pszRecvBuf)
{
	try
	{
		PMMO_RECV_JI_YUN_FB ptheRecvJiYunFb = (PMMO_RECV_JI_YUN_FB)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_RECV_PACKET_DATA_OFFSET___);

		char szPrint[256];
		sprintf_s(szPrint,"[LOG] ���˸�������ֵ ==> ret = 0x%p id = 0x%p count = %d time = %d",
						ptheRecvJiYunFb->nRet,
						ptheRecvJiYunFb->dwFbId,
						ptheRecvJiYunFb->nFbCount,
						ptheRecvJiYunFb->nShuaXinTime);
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}

bool MMOUnRecvPacket::MmoRecvDoFbRet(void* pszRecvBuf)
{
	try
	{
		PMMO_GAME_IN_FB_RET_PACKET ptheGameInFbRetPacket = (PMMO_GAME_IN_FB_RET_PACKET)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);
		char szPrint[256] = {0};
		sprintf_s(szPrint,"[LOG] ������������ֵ ==> role packet id = 0x%p error = 0x%p",
					ptheGameInFbRetPacket->dwRolePacketId,ptheGameInFbRetPacket->nError);
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}



bool MMOUnRecvPacket::MmoRecvFbServerFullRet(void* pszRecvBuf)
{
	try
	{
		// ֻҪ�˰����֣���Ȼʧ��
		PMMO_FB_SERVER_FULL_RET ptheFbServerFullRet = (PMMO_FB_SERVER_FULL_RET)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);
		char szPrint[256] = {0};
		sprintf_s(szPrint,"[LOG] ���븱��ʧ�ܵķ���ֵ ==> role packet id = 0x%p error = 0x%p name = %s",
			ptheFbServerFullRet->dwRolePacketId,ptheFbServerFullRet->dwRetValue,ptheFbServerFullRet->szRoleName);
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}

bool MMOUnRecvPacket::MmoRecvOpenNpcRet(void* pszRecvBuf)
{
	try
	{
		PMMO_RECV_OPEN_NPC_RET ptheOpenNpcRet = (PMMO_RECV_OPEN_NPC_RET)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);
		char szPrint[256] = {0};
		sprintf_s(szPrint,"[LOG] ��NPC����ֵ ==> ret = 0x%p npc id = 0x%p player id = 0x%p",
							ptheOpenNpcRet->wRet,ptheOpenNpcRet->theOpenNpcRet[0].dwObjPacketId,ptheOpenNpcRet->theOpenNpcRet[1].dwObjPacketId);
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}

// �ϼ�������Ʒ����ֵ
bool MMOUnRecvPacket::MmoRecvShangJiaAuctionItemRet(void* pszRecvBuf)
{
	try
	{
		PMMO_RECV_SHANG_JIA_ITEM_RET ptheShangJiaItemRet = (PMMO_RECV_SHANG_JIA_ITEM_RET)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);
		char szPrint[256] = {0};
		sprintf_s(szPrint,"[LOG] �ϼ���Ʒ����ֵ ==> ret1 = 0x%p ret2 = 0x%p ret3 = 0x%p",
			ptheShangJiaItemRet->dwRetValue,ptheShangJiaItemRet->dwUnKnow1,ptheShangJiaItemRet->dwUnKnow2);
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}

bool MMOUnRecvPacket::MmoRecvSellItemRet(void* pszRecvBuf)
{
	try
	{
		PMMO_RECV_SELL_ITEM_RET ptheSellItemRet = (PMMO_RECV_SELL_ITEM_RET)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);
		char szPrint[256] = {0};
		sprintf_s(szPrint,"[LOG] ������Ʒ�ķ���ֵ ==> ret = 0x%p Sell Item Id = 0x%p",
			ptheSellItemRet->nRet,ptheSellItemRet->dwSellItemId);
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}

bool MMOUnRecvPacket::MmoRecvCompleteTaskRet(void* pszRecvBuf)
{
	try
	{
		// �ύ����ɹ��ķ���ֵΪ�ύ�����id
		DWORD dwCompleteTaskRet = *(DWORD*)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);
		char szPrint[256] = {0};
		sprintf_s(szPrint,"[LOG] �ύ����ɹ��ķ���ֵ ==> ret = 0x%p",dwCompleteTaskRet);
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}

bool MMOUnRecvPacket::MmoRecvCompleteTaskFailRet(void* pszRecvBuf)
{
	try
	{
		// �ύ����ʧ�ܵķ���ֵ �� ���ͽ������Ѵ����޵ķ���ֵ
		PMMO_RECV_COMPLETE_TASK_GAIL_RET ptheCompleteTaskFailRet = (PMMO_RECV_COMPLETE_TASK_GAIL_RET)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);
		char szPrint[256] = {0};
		sprintf_s(szPrint,"[LOG] �ύ����ʧ�ܵķ���ֵ ==> ret = 0x%p task id = 0x%p",ptheCompleteTaskFailRet->nRet,ptheCompleteTaskFailRet->dwTaskId);
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}

bool MMOUnRecvPacket::MmoRecvTaskNpcChatRet(void* pszRecvBuf)
{
	try
	{
		// ��̸������񷵻�ֵ : ��ǰ�����id
		DWORD dwChatNpcRet = *(DWORD*)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);
		char szPrint[256] = {0};
		sprintf_s(szPrint,"[LOG] ��̸�������ķ���ֵ ==> task id = 0x%p",dwChatNpcRet);
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}

bool MMOUnRecvPacket::MmoRecvFramSeedRet(void* pszRecvBuf)
{
	try
	{
		// ��ֲ���ӵķ���ֵ  �ɹ�=0 �Ѿ�����=0x14
		DWORD dwFramSeedRet = *(DWORD*)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);
		char szPrint[256] = {0};
		sprintf_s(szPrint,"[LOG] ��ֲ���ӵķ���ֵ ==> ret = 0x%p",dwFramSeedRet);
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}

bool MMOUnRecvPacket::MmoRecvFeebHpRet(void* pszRecvBuf)
{
	try
	{
		// �ж������䣬����
		PMMO_RECV_FEEB_HP_RET ptheFeebHpRet = (PMMO_RECV_FEEB_HP_RET)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);
		char szPrint[256] = {0};
		sprintf_s(szPrint,"[LOG] ��ɫ���ڶ��ӻ����ķ���ֵ ==> id = 0x%p ret = 0x%p 0x%p 0x%p 0x%p 0x%p",
			ptheFeebHpRet->dwActorPacketId,
			ptheFeebHpRet->dwUnKnow1,
			ptheFeebHpRet->dwUnKnow2,
			ptheFeebHpRet->dwUnKnow3,
			ptheFeebHpRet->dwUnKnow4,
			ptheFeebHpRet->dwPoisoningFeebHpFlag
			);
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}

bool MMOUnRecvPacket::MmoRecvSendMailRet(void* pszRecvBuf)
{
	try
	{
		// ���ͳɹ�����ֵ=0
		DWORD dwSendMailRet = *(DWORD*)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);
		char szPrint[256] = {0};
		sprintf_s(szPrint,"[LOG] �����ʼ��ķ���ֵ ==> ret = 0x%p",dwSendMailRet);
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}

bool MMOUnRecvPacket::MmoRecvUseItemRet(void* pszRecvBuf)
{
	try
	{
		// ʹ����Ʒ����ֵ
		PMMO_RECV_USE_ITEM_RET ptheUseItemRet = (PMMO_RECV_USE_ITEM_RET)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);
		char szPrint[256] = {0};
		sprintf_s(szPrint,"[LOG] ʹ����Ʒ��ʣ�෵��ֵ ==> ret = %d Item id = 0x%p slot = %d",ptheUseItemRet->bRet,ptheUseItemRet->dwItemId,ptheUseItemRet->wSlotIndex);
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}

bool MMOUnRecvPacket::MmoRecvUseItemRet2(void* pszRecvBuf)
{
	try
	{
		// ʹ����Ʒ����ֵ
		PMMO_RECV_USE_ITEM_RET2 ptheUseItemRet = (PMMO_RECV_USE_ITEM_RET2)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);
		char szPrint[256] = {0};
		sprintf_s(szPrint,"[LOG] ʹ����Ʒ��û����Ʒ�ķ���ֵ ==> key1 = 0x%p key2 = 0x%p Slot = %d ",(DWORD)ptheUseItemRet->llItemKey,(DWORD)(ptheUseItemRet->llItemKey>>32),ptheUseItemRet->wItemSlotIndex);
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}

bool MMOUnRecvPacket::MmoRecvBuyItemRet(void* pszRecvBuf)
{
	try
	{
		// ʹ����Ʒ����ֵ
		PMMO_RECV_BUY_ITEM_RET ptheBuyItemRet = (PMMO_RECV_BUY_ITEM_RET)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);
		char szPrint[256] = {0};
		sprintf_s(szPrint,"[LOG] ������Ʒ�ķ���ֵ ==> ret = 0x%p shop id = 0x%p count = %d",ptheBuyItemRet->nRet,ptheBuyItemRet->dwShopItemId,ptheBuyItemRet->nCount);
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}

bool MMOUnRecvPacket::MmoRecvGetGfitBagRet(void* pszRecvBuf)
{
	try
	{
		// ��ȡ����ķ���ֵ
		DWORD dwGfitBagId = *(DWORD*)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);
		char szPrint[256] = {0};
		sprintf_s(szPrint,"[LOG] ��ȡ����ķ���ֵ ==> id = 0x%p",dwGfitBagId);
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}

bool MMOUnRecvPacket::MmoRecvCollectItemBagFullRet(void* pszRecvBuf)
{
	try
	{
		PMMO_RECV_COLLECT_ITEM_BAG_FULL_RET ptheBagFullRet =(PMMO_RECV_COLLECT_ITEM_BAG_FULL_RET)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);
		char szPrint[256] = {0};
		sprintf_s(szPrint,"[LOG] �ɼ���Ʒ���������ķ���ֵ ==> ret = 0x%p �ɼ��Ķ���id = 0x%p �ɼ��õ�����Ʒid = 0x%p",ptheBagFullRet->nRet,ptheBagFullRet->dwCollectObjPacketId,ptheBagFullRet->dwCollectItemId);
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}

bool MMOUnRecvPacket::MmoRecvTidyInventoryItemRet(void* pszRecvBuf)
{
	try
	{
		// ���صķ���ͷ��͵Ľṹ��һ���ģ��������µ���Ʒλ��
		WORD wTabSlotIndex = *(WORD*)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);
		char szPrint[256] = {0};
		sprintf_s(szPrint,"[LOG] ����ֿ�򱳰��ķ���ֵ ==> ret = 0x%p",wTabSlotIndex);		// ���ֵ���Ϊ2����˵������ֿ�ɹ������Ϊ0��˵�������ɹ�
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}


bool MMOUnRecvPacket::MmoRecvSendMailRet2(void* pszRecvBuf)
{
	try
	{
		// ���صķ���ͷ��͵Ľṹ��һ���ģ��������µ���Ʒλ��
		PMMO_RECV_SEND_MAIL_RET2 ptheSendMailRet2 = (PMMO_RECV_SEND_MAIL_RET2)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);
		char szPrint[256] = {0};

		switch (ptheSendMailRet2->dwErrorValue)
		{
		case 0x00046CE4:
			{
				sprintf_s(szPrint,"[LOG] �����ʼ�ʧ�ܷ���ֵ ==> ret = 0x%p ��ȫʱ�� error = 0x%p",ptheSendMailRet2->nRet,ptheSendMailRet2->dwErrorValue);		// �����ʼ�Ƶ������ֵ = 1	
			}
			break;
		case 0x00046CD4:
			{
				sprintf_s(szPrint,"[LOG] �����ʼ�ʧ�ܷ���ֵ ==> ret = 0x%p �����ڵĽ�ɫ�� error = 0x%p",ptheSendMailRet2->nRet,ptheSendMailRet2->dwErrorValue);		// �����ʼ�Ƶ������ֵ = 1	
			}
			break;
		case 0x00046CE2:
			{
				sprintf_s(szPrint,"[LOG] �����ʼ�ʧ�ܷ���ֵ ==> ret = 0x%p �����ʼ�Ƶ�� error = 0x%p",ptheSendMailRet2->nRet,ptheSendMailRet2->dwErrorValue);		// �����ʼ�Ƶ������ֵ = 1	
			}
			break;
		default:
			{
				sprintf_s(szPrint,"[LOG] �����ʼ�ʧ�ܷ���ֵ ==> ret = 0x%p δ֪������ error = 0x%p",ptheSendMailRet2->nRet,ptheSendMailRet2->dwErrorValue);		// �����ʼ�Ƶ������ֵ = 1	
			}
		}

		
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}


bool MMOUnRecvPacket::MmoRecvSendGuoTuRet(void* pszRecvBuf)
{
	try
	{
		PGUO_TU_RET ptheGuoTuRet = (PGUO_TU_RET)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);

		char szPrint[256] = {0};
		sprintf_s(szPrint,"[LOG] ��ͼ���ذ� ==> packet id = 0x%p dir x = %f y = %f vector x = %f y = %f z = %f",	
																								ptheGuoTuRet->dwRolePacketId,
																								ptheGuoTuRet->theRoleDirection.dir_x,
																								ptheGuoTuRet->theRoleDirection.dir_y,
																								ptheGuoTuRet->theRoleVector.fx,
																								ptheGuoTuRet->theRoleVector.fy,
																								ptheGuoTuRet->theRoleVector.fx
																								);
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}



// �����׷���ֵ ����
// ͬ����ܶԷ������׵ķ���ֵ
bool MMOUnRecvPacket::MmoRecvRequestDealRet(void* pszRecvBuf)
{
	try
	{
		PMMO_RECV_REQUEST_DEAL_RET ptheRequestDealRet = (PMMO_RECV_REQUEST_DEAL_RET)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);

		char szPrint[256] = {0};
		sprintf_s(szPrint,"[LOG] �����׷���ֵ �� ͬ����ܶԷ������׵ķ���ֵ �ɹ� ==> request id = 0x%p by request id = 0x%p",	
			ptheRequestDealRet->dwRequestDealRoleId,
			ptheRequestDealRet->dwByRequestDealRoleId
			);
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}


// �����׷���ֵ �ܾ�
bool MMOUnRecvPacket::MmoRecvRequestDealFailRet(void* pszRecvBuf)
{
	try
	{
		PMMO_RECV_REQUEST_DEAL_FIAL_RET ptheRequestDealFailRet = (PMMO_RECV_REQUEST_DEAL_FIAL_RET)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);

		char szPrint[256] = {0};
		sprintf_s(szPrint,"[LOG] �����׷���ֵ �ܾ� ==> ret = 0x%p role name = %s",	
			ptheRequestDealFailRet->dwRequestDealFailValue,
			ptheRequestDealFailRet->szRoleName
			);
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}


// ���ܵ������׵ķ���ֵ
bool MMOUnRecvPacket::MmoRecvAcceptDealRet(void* pszRecvBuf)
{
	try
	{
		DWORD dwAcceptDealValue = *(DWORD*)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);

		char szPrint[256] = {0};
		sprintf_s(szPrint,"[LOG] ���ܵ������׵ķ���ֵ ret = 0x%p",dwAcceptDealValue);
		OutputDebugStringA(szPrint);

		MMO_Accept_Deal(dwAcceptDealValue);	// ����������
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}

// ȡ�����׷���ֵ
bool MMOUnRecvPacket::MmoRecvQuXiaoDealRet(void* pszRecvBuf)
{
	try
	{
		DWORD dwQuXiaoDealRoleId = *(DWORD*)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);

		char szPrint[256] = {0};
		sprintf_s(szPrint,"[LOG] ȡ�����׷���ֵ ret = 0x%p",dwQuXiaoDealRoleId);	// ˭ȡ��������˭��id�����Ϊ0�����ʾ����ʧ��
		OutputDebugStringA(szPrint);

	}
	catch (...)
	{
		assert(false);
	}
	return true;
}

// �ƶ���Ʒ���������ɹ���ķ���ֵ
bool MMOUnRecvPacket::MmoRecvMoveDealItemRet(void* pszRecvBuf)
{
	try
	{
		PMMO_RECV_DEAL_MOVE_ITEM_RET ptheDealMoveItemRet = (PMMO_RECV_DEAL_MOVE_ITEM_RET)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);

		char szPrint[256] = {0};
		sprintf_s(szPrint,"[LOG] �ƶ���Ʒ���������ɹ���ķ���ֵ ==> scr tab = 0x%d slot = %d Item count = %d Deal slot = %d",	
				ptheDealMoveItemRet->wScrItemTabIndex,
				ptheDealMoveItemRet->wScrItemSlotIndex,
				ptheDealMoveItemRet->wMoveItemCount,
				ptheDealMoveItemRet->wDealSlotaIndex
			);
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}


// ���׽�ҵķ���ֵ
bool MMOUnRecvPacket::MmoRecvMoveDealGoldRet(void* pszRecvBuf)
{
	try
	{
		PMMO_RECV_MOVE_DEAL_GOLD_RET ptheMoveDealGoldRet = (PMMO_RECV_MOVE_DEAL_GOLD_RET)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);

		char szPrint[256] = {0};
		sprintf_s(szPrint,"[LOG] ���׽�ҵķ���ֵ ==> Role id = 0x%p Gold = %d",	
			ptheMoveDealGoldRet->dwMoveDealGoldRoleId,
			ptheMoveDealGoldRet->nMoveDealGoldValue
			);
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}


// ����״̬����ֵ ==�� �����������ķ���ֵ �Է������������ķ���ֵ �Է�ȷ�Ͻ��׵ķ���ֵ ȷ�Ͻ��׵ķ���ֵ
bool MMOUnRecvPacket::MmoRecvDealStatusRet(void* pszRecvBuf)
{
	try
	{
		PMMO_RECV_DEAL_STATUS_RET ptheDealStatusRet = (PMMO_RECV_DEAL_STATUS_RET)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);

		char szPrint[256] = {0};
		sprintf_s(szPrint,"[LOG] ����״̬����ֵ ==�� �����������ķ���ֵ �Է������������ķ���ֵ �Է�ȷ�Ͻ��׵ķ���ֵ ȷ�Ͻ��׵ķ���ֵ ==> do deal role id = 0x%p, deal index = %d",	
					ptheDealStatusRet->dwDoDealRoleId,
					ptheDealStatusRet->bDoDealIndex
			);
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}




// ˫����ȷ�Ͻ��׺�ķ���ֵ ����ʧ�� ��Ʒ����Я������
bool MMOUnRecvPacket::MmoRecvDealFailRet(void* pszRecvBuf)
{
	try
	{
		PMMO_RECV_DEAL_FAIL_RET ptheDealFailRet = (PMMO_RECV_DEAL_FAIL_RET)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);

		char szPrint[256] = {0};
		sprintf_s(szPrint,"[LOG] ˫����ȷ�Ͻ��׺�ķ���ֵ ����ʧ�� ��Ʒ����Я������ ==> ret = 0x%p Deal Role id = 0x%p",	
					ptheDealFailRet->dwDealFailRet,
					ptheDealFailRet->dwDealRoleId
			);
		OutputDebugStringA(szPrint);
	}
	catch (...)
	{
		assert(false);
	}
	return true;
}

// ˫����ȷ�Ͻ��׺�ķ���ֵ ���׽���
bool MMOUnRecvPacket::MmoRecvDealSucessRet(void* pszRecvBuf)
{
	try
	{
		DWORD dwDealSucessRet = *(DWORD*)((DWORD)pszRecvBuf+MMOCLIENT_REVERSAL_PACKET_HEADER_VALUE_OFFSET___);

		char szPrint[256] = {0};
		sprintf_s(szPrint,"[LOG] ˫����ȷ�Ͻ��׺�ķ���ֵ ���׽��� ret = 0x%p",dwDealSucessRet);
		OutputDebugStringA(szPrint);

	}
	catch (...)
	{
		assert(false);
	}
	return true;
}